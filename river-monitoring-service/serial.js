const { autoDetect } = require('@serialport/bindings-cpp');
const { SerialPort } = require('serialport');

/**
 * Detects the serial port where Arduino is plugged in.
 * This function only handles one Arduino. Multiple Arduinos will be ignored, and
 * only the first detected port will be returned.
 * @async
 * @example
 * const port = getArduinoPort().then(portPath => {
 *     return new SerialPort({ path: portPath, baudRate: 9600 });
 * });
 * @returns the detected port path
 */
async function getArduinoPort() {
    const list = await autoDetect().list();
    const filtered = list.filter(port => port.manufacturer.toLowerCase().includes('arduino'))
    if (filtered.length === 0) {
        throw new Error("Arduino port not found");
    }
    return filtered[0].path;
}

/**
 * Writes the given content on the serial port.
 * If the content does not contain a \n, it will be added by this function.
 * @param {Promise<SerialPort>} port the serial port to write on
 * @param {string} content the content to send on the serial port
 */
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

/**
 * Reads the data sent on the serial port until a \n is found.
 * @param {Promise<SerialPort>} port the serial port to read from
 * @example
 * // Save data in a variable for later use.
 * const dataPromise = serialRead(myPort).then(data => {
 *     return data;
 * });
 * // Or...
 * serialRead(myPort).then(data => {
 *     // Handle data.
 * });
 * @returns {Promise<string>} the read data
 */
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
