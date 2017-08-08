// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.

function isNumeric(n) {
    return !isNaN(parseFloat(n)) && isFinite(n);
}

const Dialogs = require('dialogs');
//const SerialPort = require('serialport');
//const Stage = require('./libStageArm.js');

var dialogs = Dialogs();
var stage;

var stepSize = 2;
var stepSizeInput = document.getElementById('stepSizeInput');
stepSizeInput.onchange = function() {
        var newStepSize = stepSizeInput.value;
        console.log(newStepSize);
        if (isNumeric(newStepSize)) {
            stepSize = newStepSize;
        }
    }
    /*
    var path = dialogs.prompt("Enter Arduino serial path", "/dev/cu.usbmodem1411", (path) => {
        stage = new Stage(path);

        stage.port.on('open', () => {
            console.log('open');

            document.addEventListener('keydown', (event) => {
                switch (event.keyCode) {
                    case 75: //k
                    case 38: //up
                        stage.relMove(0, stepSize, 0);
                        break;
                    case 74: //j
                    case 40: //down
                        stage.relMove(0, -stepSize, 0);
                        break;
                    case 72: //h
                    case 37: //left
                        stage.relMove(-stepSize, 0, 0);
                        break;
                    case 76: //l
                    case 39: //right
                        stage.relMove(stepSize, 0, 0);
                        break;
                    case 17: //ctrl
                    case 83: //s
                        stage.relMove(0, 0, -stepSize);
                        break;
                    case 16: //shift
                    case 87: //w
                        stage.relMove(0, 0, stepSize);
                        break;
                    default:
                        console.log("error bad keycode");
                }

            })
        });
    });*/