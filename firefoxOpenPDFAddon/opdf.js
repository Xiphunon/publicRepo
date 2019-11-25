let allObjects = document.getElementsByTagName('object');
let resourceobject;
let found = false;

searchForPDF();

function searchForPDF() {
    for (let i = 0; i < allObjects.length && !found; i++) {
        if (allObjects[i].id = "resourceobject") {
            resourceobject = allObjects[i].data;
            found = true;
        }
    }
    if (found) {
        if (resourceobject.search('.pdf') != -1) {
            getConfirm();
        }
    }
}

function getConfirm() {
    var retVal = confirm('PDF Found. Do you want to open it?');
    if (retVal == true) {
        window.open(resourceobject, '', 'width=620,height=450,toolbar=no,location=no,menubar=no,copyhistory=no,status=no,directories=no,scrollbars=yes,resizable=yes');
    }
}