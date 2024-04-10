const { autoDetect } = require('@serialport/bindings-cpp');
const { SerialPort } = require('serialport');

async function getArduinoPort() {
    const list = await autoDetect().list();
    const filtered = list.filter(port => port.manufacturer.toLowerCase().includes('arduino'))
    if (filtered.length === 0) {
        throw new Error("Arduino port not found");
    }
    return filtered[0].path;
}

function serialWrite(port, content) {
    port.then(actualPort => {
        if (!actualPort instanceof SerialPort) {
            throw new Error("Not a SerialPort object.");
        }
        if (!content.endsWith('\n')) {
            content += '\n';
        }
        actualPort.write(content);
    });
}

function serialRead(port) {
    return new Promise((resolve, reject) => {
        let buffer = '';
        port.then(actualPort => {
            const onDataReceived = data => {
                buffer += data.toString();
                if (buffer.endsWith('\n')) {
                    resolve(buffer);
                    actualPort.off('data', onDataReceived);
                }
            };
            actualPort.on('data', onDataReceived);
        }).catch(error => reject(error));
    });
}

module.exports = { getArduinoPort, serialWrite, serialRead }
