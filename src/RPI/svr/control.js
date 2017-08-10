// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.

function isNumeric(n) {
    return !isNaN(parseFloat(n)) && isFinite(n);
}

const Dialogs = require('dialogs');
const SerialPort = require('serialport');
const Stage = require('./libStageArm.js');

var dialogs = Dialogs();
var stage;

var stepSize = 2;
let stepSizeInput = document.getElementById('stepSizeInput');
stepSizeInput.onchange = function() {
    stepSize = stepSizeInput.value;
    console.log("New Step Size: " + stepSize);

}
let stepPerInput = document.getElementById('stepPeriodInput');
stepPerInput.onchange = function() {
    var newStepPeriod = stepPerInput.value;
    console.log("New Step Size: " + newStepPeriod);
    stage.setPeriod(newStepPeriod);
}
var path = dialogs.prompt("Enter Arduino serial path", "/dev/ttyACM0", (path) => {
    stage = new Stage(path);

    stage.port.on('open', () => {
        console.log('open');
        stage.setPeriod(1000);
        document.addEventListener('keydown', (event) => {
            switch (event.keyCode) {
                case 13:
                    document.getElementById("defocus").focus();
                    break;
                case 75: //k
                case 38: //up
                    if (!((document.activeElement == document.getElementById("stepSizeInput")) || (document.activeElement == document.getElementById("stepPeriodInput")))) {
                        stage.relMove(0, stepSize, 0);
                    }
                    break;
                case 74: //j
                case 40: //down
                    if (!((document.activeElement == document.getElementById("stepSizeInput")) || (document.activeElement == document.getElementById("stepPeriodInput")))) {
                        stage.relMove(0, -stepSize, 0);
                    }
                    break;
                case 72: //h
                case 37: //left
                    if (!((document.activeElement == document.getElementById("stepSizeInput")) || (document.activeElement == document.getElementById("stepPeriodInput")))) {
                        stage.relMove(-stepSize, 0, 0);
                    }
                    break;
                case 76: //l
                case 39: //right
                    if (!((document.activeElement == document.getElementById("stepSizeInput")) || (document.activeElement == document.getElementById("stepPeriodInput")))) {
                        stage.relMove(stepSize, 0, 0);
                    }
                    break;
                case 17: //ctrl
                case 83: //s
                    if (!((document.activeElement == document.getElementById("stepSizeInput")) || (document.activeElement == document.getElementById("stepPeriodInput")))) {
                        stage.relMove(0, 0, -stepSize);
                    }
                    break;
                case 16: //shift
                case 87: //w
                    if (!((document.activeElement == document.getElementById("stepSizeInput")) || (document.activeElement == document.getElementById("stepPeriodInput")))) {
                        stage.relMove(0, 0, stepSize);
                    }
                    break;
                default:
                    console.log("error bad keycode");
            }

        })
    });
});