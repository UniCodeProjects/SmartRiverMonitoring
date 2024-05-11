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

server.get('/update', (req, res) => {
    res.json({ badge: currentSystemState, waterLevel: currentWaterLevel })
});

server.post('/manual-mode-switch', (req, res) => {
    const isManual = req.body.isManual;
    Serial.serialWrite(serialPort, isManual ? "ON" : "OFF");
    res.sendStatus(200);
});

server.post('/valve', (req, res) => {
    const rangeValue = req.body.valveRangeValue;
    console.log("Valve range value: " + rangeValue);
    // Serial.serialWrite(serialPort, rangeValue); // TODO: uncomment when the remote control is implemented in Arduino
    res.sendStatus(200);
})

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
        client.publish(samplePeriodTopic, `${SystemState.Normal.samplePeriod}\n`);
        currentSystemState = SystemState.Normal.Badge;
        Serial.serialWrite(serialPort, SystemState.Normal.name);
    } else if (currentWaterLevel < WaterLevel.WL1) {
        client.publish(samplePeriodTopic, `${SystemState.AlarmTooLow.samplePeriod}\n`);
        currentSystemState = SystemState.AlarmTooLow.Badge;
        Serial.serialWrite(serialPort, SystemState.AlarmTooLow.name);
    } else if (currentWaterLevel > WaterLevel.WL2) {
        if (currentWaterLevel <= WaterLevel.WL3) {
            client.publish(samplePeriodTopic, `${SystemState.PreAlarmTooHigh.samplePeriod}\n`);
            currentSystemState = SystemState.PreAlarmTooHigh.Badge;
        } else if (currentWaterLevel > WaterLevel.WL3 && currentWaterLevel <= WaterLevel.WL4) {
            client.publish(samplePeriodTopic, `${SystemState.AlarmTooHigh.samplePeriod}\n`);
            currentSystemState = SystemState.AlarmTooHigh.Badge;
            Serial.serialWrite(serialPort, SystemState.AlarmTooHigh.name);
        } else if (currentWaterLevel > WaterLevel.WL4) {
            client.publish(samplePeriodTopic, `${SystemState.AlarmTooHighCritic.samplePeriod}\n`);
            currentSystemState = SystemState.AlarmTooHighCritic.Badge;
            Serial.serialWrite(serialPort, SystemState.AlarmTooHighCritic.name);
        }
    }
});
