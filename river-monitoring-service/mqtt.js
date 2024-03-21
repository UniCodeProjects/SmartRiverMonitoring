const mqtt = require("mqtt");
const client = mqtt.connect("mqtt://broker.mqtt-dashboard.com");

client.on("connect", () => {
  client.subscribe("esiot-2023", (err) => {
    if (!err) {
      console.log("connected");
    }
  });
});

client.on("message", (topic, message) => {
    console.log(topic.toString());
    console.log(message.toString());
});
