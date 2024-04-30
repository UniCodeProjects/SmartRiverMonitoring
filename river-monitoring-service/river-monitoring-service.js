const mqtt = require("mqtt");
const WaterLevel = require("./water-level");
const SystemState = require("./system-state");
const Serial = require("./serial");
const { SerialPort } = require("serialport");

const client = mqtt.connect("mqtt://broker.mqtt-dashboard.com");
const waterLevelTopic = "water-level";
const samplePeriodTopic = "sample-period";

const port = Serial.getArduinoPort().then(portPath => {
    return new SerialPort({ path: portPath, baudRate: 9600 });
});

client.on("connect", () => {
    client.subscribe(waterLevelTopic, err => {
        if (err) {
            throw err;
        }
    });
    client.publish(samplePeriodTopic, `${SystemState.Normal.samplePeriod}\n`, { retain: true });
});

client.on("message", (topic, message) => {
    if (topic.toString() != waterLevelTopic) {
        throw new Error(`Unknown topic: ${topic.toString()}`);
    }
    const currentWaterLevel = parseFloat(message.toString());
    if (isNaN(currentWaterLevel)) {
        throw new Error(`Received water level was NaN: ${message.toString()}`);
    }
    if (currentWaterLevel >= WaterLevel.WL1 && currentWaterLevel <= WaterLevel.WL2) {
        client.publish(samplePeriodTopic, `${SystemState.Normal.samplePeriod}\n`);
        Serial.serialWrite(port, SystemState.Normal.name);
    } else if (currentWaterLevel < WaterLevel.WL1) {
        client.publish(samplePeriodTopic, `${SystemState.AlarmTooLow.samplePeriod}\n`);
        Serial.serialWrite(port, SystemState.AlarmTooLow.name);
    } else if (currentWaterLevel > WaterLevel.WL2) {
        if (currentWaterLevel <= WaterLevel.WL3) {
            client.publish(samplePeriodTopic, `${SystemState.PreAlarmTooHigh.samplePeriod}\n`);
        } else if (currentWaterLevel > WaterLevel.WL3 && currentWaterLevel <= WaterLevel.WL4) {
            client.publish(samplePeriodTopic, `${SystemState.AlarmTooHigh.samplePeriod}\n`);
            Serial.serialWrite(port, SystemState.AlarmTooHigh.name);
        } else if (currentWaterLevel > WaterLevel.WL4) {
            client.publish(samplePeriodTopic, `${SystemState.AlarmTooHighCritic.samplePeriod}\n`);
            Serial.serialWrite(port, SystemState.AlarmTooHighCritic.name);
        }
    }
});
