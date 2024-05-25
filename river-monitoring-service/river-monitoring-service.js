const express = require('express');
const mqtt = require("mqtt");
const path = require("path")
const WaterLevel = require("./water-level");
const SystemState = require("./system-state");
const Serial = require("./serial");
const { SerialPort } = require("serialport");
const bodyParser = require("body-parser");

const server = express();
const serverPort = 3000;
const client = mqtt.connect("mqtt://broker.mqtt-dashboard.com");
const waterLevelTopic = "water-level";
const samplePeriodTopic = "sample-period";
let currentWaterLevel = NaN;
let currentSystemState = null;
let currentValveLevel = NaN;
let isRemoteControl = false;
let isManualModeSwitchDisabled = false;
let existsLocalManualModeListener = false;

// Server setup.
server.set('view engine', 'ejs');
server.set('views', path.resolve("../river-monitoring-dashboard"))    // ejs file location.
server.use(express.static(path.resolve("../river-monitoring-dashboard")))
server.use(bodyParser.json());

server.listen(serverPort, _ => {
    console.log(`Server listening on port ${serverPort}`);
});

server.get('/', (req, res) => {
    res.render('index', { status: SystemState.Normal.Badge, progress: 0, range: 0 })
})

server.get('/update/chart', (req, res) => {
    res.json({ badge: currentSystemState.Badge, waterLevel: currentWaterLevel })
});

server.get('/update/valve', (req, res) => {
    res.json({ valveLevel: currentValveLevel });
})

server.post('/remote-control', (req, res) => {
    isRemoteControl = req.body.isManual;
    currentValveLevel = isRemoteControl ? null : currentValveLevel;
    Serial.serialWrite(serialPort, "Remote control: " + (isRemoteControl ? "ON" : "OFF"));
    res.sendStatus(200);
});

server.post('/valve', (req, res) => {
    if (isRemoteControl) {
        const rangeValue = req.body.valveRangeValue;
        Serial.serialWrite(serialPort, rangeValue);
    }
    res.sendStatus(200);
})

server.post('/manual-mode-switch', (req, res) => {
    res.json({ isDisabled: isManualModeSwitchDisabled });
});

// MQTT setup.
client.on("connect", () => {
    client.subscribe(waterLevelTopic, err => {
        if (err) {
            throw err;
        }
    });
    client.publish(samplePeriodTopic, `${SystemState.Normal.samplePeriod}\n`, { retain: true });
});

// Serial setup.
const serialPort = Serial.getArduinoPort().then(portPath => {
    return new SerialPort({ path: portPath, baudRate: 9600 });
});

function checkForLocalManualMode() {
    /*
     * This check assures that only one listener on the serial is created, avoiding memory leaks.
     * When a listener is destroyed, the variable "existsLocalManualModeListener" is set to false: in this
     * way, a new listener will be created at the next execution of this function.
     */
    if (!existsLocalManualModeListener) {
        Serial.serialRead(serialPort).then(data => {
            data = data.trim();
            if (data === "Local manual mode: ON") {
                isManualModeSwitchDisabled = true;
            } else if (data === "Local manual mode: OFF") {
                isManualModeSwitchDisabled = false;
            } else if (data.includes("VALVE_LVL=")) {
                currentValveLevel = parseInt(data.replace("VALVE_LVL=", ""));
            }
            existsLocalManualModeListener = false;
        });
        existsLocalManualModeListener = true;
    }
}

setInterval(checkForLocalManualMode, 500);

// Server logic.
client.on("message", (topic, message) => {
    if (topic.toString() != waterLevelTopic) {
        throw new Error(`Unknown topic: ${topic.toString()}`);
    }
    currentWaterLevel = parseFloat(message.toString());
    if (isNaN(currentWaterLevel)) {
        throw new Error(`Received water level was NaN: ${message.toString()}`);
    }
    if (currentWaterLevel >= WaterLevel.WL1 && currentWaterLevel <= WaterLevel.WL2) {
        currentSystemState = SystemState.Normal;
    } else if (currentWaterLevel < WaterLevel.WL1) {
        currentSystemState = SystemState.AlarmTooLow;
    } else if (currentWaterLevel > WaterLevel.WL2) {
        if (currentWaterLevel <= WaterLevel.WL3) {
            currentSystemState = SystemState.PreAlarmTooHigh;
        } else if (currentWaterLevel > WaterLevel.WL3 && currentWaterLevel <= WaterLevel.WL4) {
            currentSystemState = SystemState.AlarmTooHigh;
        } else if (currentWaterLevel > WaterLevel.WL4) {
            currentSystemState = SystemState.AlarmTooHighCritic;
        }
    }
    client.publish(samplePeriodTopic, `${currentSystemState.samplePeriod}\n`);
    if (!isRemoteControl) {
        Serial.serialWrite(serialPort, currentSystemState.name);
    }
});
