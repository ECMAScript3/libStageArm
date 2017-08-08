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
    let cam = document.getElementById("camview");
    cam.setAttribute('crossorigin', 'anonymous');
    cam.src = window.URL.createObjectURL(mStream);
    console.log(mStream.getVideoTracks()[0]);
    cam.play();
    let ic = new ImageCapture(mStream.getVideoTracks()[0]);
    streamLoop(ic);
}).catch(console.log);

function streamLoop(ic) {
    console.log(ic)
    ic.takePhoto().then((k) => {
        let arrayBuffer;
        let matrix;
        let fileReader = new FileReader();
        fileReader.onload = function() {
            arrayBuffer = this.result;
            console.log(arrayBuffer);
            cv.readImage(new Buffer(arrayBuffer, 'binary'), (err, l) => matrix = l);
            console.log(matrix);
            matrix.detectObject(cv.FACE_CASCADE, {}, function(err, faces) {
                console.log(faces.length);
                for (var i = 0; i < faces.length; i++) {
                    var x = faces[i]
                    matrix.ellipse(x.x + x.width / 2, x.y + x.height / 2, x.width / 2, x.height / 2);
                }
                let buf = matrix.toBuffer({ ext: ".bmp" })
                console.log(buf)
                let blb = new Blob([buf], { type: "image/bmp" })
                console.log(blb.type)
                console.log(blb)
                photo.src = window.URL.createObjectURL(blb);
                setTimeout(streamLoop, 50, ic);
            });
        };
        fileReader.readAsArrayBuffer(k);
    }).catch(console.log);
}
photo.addEventListener('load', function() {
    window.URL.revokeObjectURL(this.src);
});