const { autoDetect } = require('@serialport/bindings-cpp');

async function getArduinoPort() {
    const list = await autoDetect().list();
    const filtered = list.filter(port => port.manufacturer.toLowerCase().includes('arduino'))
    if (filtered.length === 0) {
        throw new Error("Arduino port not found");
    }
    return filtered[0].path;
}

module.exports = { getArduinoPort }
