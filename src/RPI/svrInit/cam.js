const cv = require("opencv");
const ImageCapture = require("image-capture").ImageCapture;
var imgStream = new cv.ImageStream();
const photo = document.getElementById("faceview");
navigator.mediaDevices.getUserMedia({
    audio: false,
    video: {
        width: 1920,
        height: 1080
    }
}).then((mStream) => {
    let ic = new ImageCapture(mStream.getVideoTracks()[0]);
    var video = document.getElementById('faceview');
    video.srcObject = mStream;
    video.play();
    //streamLoop(ic);
}).catch(console.log);

function streamLoop(ic) {
    ic.takePhoto().then((k) => {
        let arrayBuffer;
        let matrix;
        let fileReader = new FileReader();
        fileReader.onload = function() {
            arrayBuffer = this.result;
            cv.readImage(new Buffer(arrayBuffer, 'binary'), (err, l) => matrix = l);
            matrix.detectObject(cv.FACE_CASCADE, {}, function(err, faces) {
                for (var i = 0; i < faces.length; i++) {
                    var x = faces[i]
                    matrix.ellipse(x.x + x.width / 2, x.y + x.height / 2, x.width / 2, x.height / 2);
                }
                let buf = matrix.toBuffer({ ext: ".bmp" })
                let blb = new Blob([buf], { type: "image/bmp" })
                photo.src = window.URL.createObjectURL(blb);
                setTimeout(streamLoop, 10, ic);
            });
        };
        fileReader.readAsArrayBuffer(k);
    }).catch(console.log);
}
photo.addEventListener('load', function() {
    window.URL.revokeObjectURL(this.src);
});