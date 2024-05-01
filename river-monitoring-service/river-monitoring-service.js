const express = require('express');
const mqtt = require("mqtt");
const path = require("path")
const WaterLevel = require("./water-level");
const SystemState = require("./system-state");

const server = express();
const port = 3000;
const client = mqtt.connect("mqtt://broker.mqtt-dashboard.com");
const waterLevelTopic = "water-level";
const samplePeriodTopic = "sample-period";

// Server setup.
server.set('view engine', 'ejs');
server.set('views', path.resolve("../river-monitoring-dashboard"))    // ejs file location.
server.use(express.static(path.resolve("../river-monitoring-dashboard")))

server.listen(port, _ => {
    console.log(`Server listening on port ${port}`);
});

server.get('/', (req, res) => {
    res.render('index', { status: SystemState.Normal.Badge, progress: 0, range: 0 })
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
        server.get('/update', (req, res) => res.json({ update: SystemState.Normal.Badge }))
    } else if (currentWaterLevel < WaterLevel.WL1) {
        client.publish(samplePeriodTopic, `${SystemState.AlarmTooLow.samplePeriod}\n`);
        server.get('/update', (req, res) => res.json({ update: SystemState.AlarmTooLow.Badge }))
    } else if (currentWaterLevel > WaterLevel.WL2) {
        if (currentWaterLevel <= WaterLevel.WL3) {
            client.publish(samplePeriodTopic, `${SystemState.PreAlarmTooHigh.samplePeriod}\n`);
            server.get('/update', (req, res) => res.json({ update: SystemState.PreAlarmTooHigh.Badge }))
        } else if (currentWaterLevel > WaterLevel.WL3 && currentWaterLevel <= WaterLevel.WL4) {
            client.publish(samplePeriodTopic, `${SystemState.AlarmTooHigh.samplePeriod}\n`);
            server.get('/update', (req, res) => res.json({ update: SystemState.AlarmTooHigh.Badge }))
        } else if (currentWaterLevel > WaterLevel.WL4) {
            client.publish(samplePeriodTopic, `${SystemState.AlarmTooHighCritic.samplePeriod}\n`);
            server.get('/update', (req, res) => res.json({ update: SystemState.AlarmTooHighCritic.Badge }))
        }
    }
});
