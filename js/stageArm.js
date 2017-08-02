const SerialPort = require('serialport');
const Dialogs = require('dialogs');

class armController {
    constructor (/*USB File Descriptor*/fd) {
        this.port = 
    }
    relMove(x, y, z) {
        var floatCoords = new Float32Array(3);
        floatCoords[0] = x;
        floatCoords[1] = y;
        floatCoords[2] = z;

        var coordsBytes = new Uint8Array(floatCoords.buffer);
        var command = new Uint8Array(coordsBytes.length + 1);
        command[0] = 0x02;
        
        for(var i = 0; i < coordsBytes.length; i++) {
            command[1+i] = coordsBytes[i];
        }
        console.log(command);

        this.port.write(Buffer.from(command), 'utf-8', () => {
            console.log('done');
        });
    }
    relMoveX(x) {
        relMove(x, 0, 0);
    }
    relMoveY(y) {
        relMove(0, y, 0);
    }
    relMoveZ(z) {
        relMove(0, 0, z);
    }
}


module.exports = armController;