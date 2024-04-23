const mqtt = require("mqtt");
const WaterLevel = require("./water-level");
const SystemState = require("./system-state");

const client = mqtt.connect("mqtt://broker.mqtt-dashboard.com");
const waterLevelTopic = "water-level";
const samplePeriodTopic = "sample-period";

client.on("connect", () => {
    client.subscribe(waterLevelTopic, err => {
        if (err) {
            throw err;
        }
    });
    client.publish(samplePeriodTopic, SystemState.Normal.samplePeriod + '\n', { retain: true });
});

client.on("message", (topic, message) => {
    if (topic != waterLevelTopic) {
        throw new Error(`Unknown topic: ${topic}`);
    }
    const currentWaterLevel = Number(message);
    if (currentWaterLevel === NaN) {
        throw new Error(`Received water level was NaN: ${message}`);
    }
    if (currentWaterLevel >= WaterLevel.WL1 && currentWaterLevel <= WaterLevel.WL2) {
        client.publish(samplePeriodTopic, SystemState.Normal.samplePeriod);
    } else if (currentWaterLevel < WaterLevel.WL1) {
        client.publish(samplePeriodTopic, SystemState.AlarmTooLow.samplePeriod);
    } else if (currentWaterLevel > WaterLevel.WL2) {
        if (currentWaterLevel <= WaterLevel.WL3) {
            client.publish(samplePeriodTopic, SystemState.PreAlarmTooHigh.samplePeriod);
        } else if (currentWaterLevel > WaterLevel.WL3 && currentWaterLevel <= WaterLevel.WL4) {
            client.publish(samplePeriodTopic, SystemState.AlarmTooHigh.samplePeriod);
        } else if (currentWaterLevel > WaterLevel.WL4) {
            client.publish(samplePeriodTopic, SystemState.AlarmTooHighCritic.samplePeriod);
        }
    }
});
