function k() {}
k.toggle = () => {
    let menu = document.getElementById("menu");
    menu.style.left = (menu.style.left == "0px") ? "-255px" : "0px"
}
k.toggleCam = () => {
    document.getElementById("camGroup").style.display = "block";
    document.getElementById("3drepGroup").style.display = "none";
    document.getElementById("editGroup").style.display = "none";
};
k.toggle3D = () => {
    document.getElementById("camGroup").style.display = "none";
    document.getElementById("3drepGroup").style.display = "block";
    document.getElementById("editGroup").style.display = "none";
};
k.toggleEdit = () => {
    document.getElementById("camGroup").style.display = "none";
    document.getElementById("3drepGroup").style.display = "none";
    document.getElementById("editGroup").style.display = "block";
};
module.exports = k;