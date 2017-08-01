// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.

function isNumeric(n) {
    return !isNaN(parseFloat(n)) && isFinite(n);
}

const SerialPort = require('serialport');
const Dialogs = require('dialogs');
var dialogs = Dialogs();
const ReadLine = SerialPort.parsers.ReadLine;
var port;

var stepSize = 2;
var stepSizeInput = document.getElementById('step-size-input');
stepSizeInput.onchange = function() {
    var newStepSize = stepSizeInput.value;
    console.log(newStepSize);
    if(isNumeric(newStepSize)) {
        stepSize = newStepSize;
        document.getElementById('step-size-disp').innerHTML = stepSize;
    }
}

var path = dialogs.prompt("Enter Arduino serial path", "/dev/cu.usbmodem1411", (path) => {
    port = new SerialPort(path);

    port.on('open', () => {
        console.log('open');
        
        document.addEventListener('keydown', (event) => {   
            switch(event.keyCode) {
            case 75: //k
            case 38: //up
                relMov(0, stepSize, 0);
                break;
            case 74: //j
            case 40: //down
                relMov(0, -stepSize, 0);
            break;
            case 72: //h
            case 37: //left
                relMov(-stepSize, 0, 0);
                break;
            case 76: //l
            case 39: //right
                relMov(stepSize, 0, 0);
                break;
            default:
                console.log("error bad keycode");
            }

        })
    });
});

function relMov(x, y, z) {
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

    port.write(Buffer.from(command), 'utf-8', () => {
        console.log('done');
    })
}

