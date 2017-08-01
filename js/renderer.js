// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.

const SerialPort = require('serialport');
const Dialogs = require('dialogs');
var dialogs = Dialogs();
const ReadLine = SerialPort.parsers.ReadLine;
var path = dialogs.prompt("Enter Arduino serial path", "/dev/cu.usbmodem1411", (path) => {
    const port = new SerialPort(path);

    var floatCoords = new Float32Array(3);
    floatCoords[0] = 1; floatCoords[1] = 1; floatCoords[2] = 0;

    var coordsBytes = new Uint8Array(floatCoords.buffer);
    var command = new Uint8Array(coordsBytes.length + 1);
    command[0] = 0x02;
    for(var i = 0; i < coordsBytes.length; i++) {
        command[1+i] = coordsBytes[i];
    }

    port.write(Buffer.from(command), () => {dialogs.alert('done')});
    console.log(command);
});

