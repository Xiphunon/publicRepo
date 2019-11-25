function getInputVal() {
    return document.getElementById("dnaBases").value;
}

function setInputVal(val) {
    document.getElementById("dnaBases").value = val;
}

function getOutputVal() {
    return document.getElementById("compl").value;
}

function setOutputVal(val) {
    document.getElementById("compl").value = val;
}

function resizeTextInput() {
    let dnaBases = document.getElementById("dnaBases");
    setInputVal(getInputVal().toUpperCase().replace(/[^ACGT]/, ""));
    calcPairs();
    paintPairs();
}

function calcPairs() {
    let complimentaryChain = "";
    for (let base of getInputVal()) {
        switch (base) {
            case "A":
                complimentaryChain += "T";
                break;
            case "C":
                complimentaryChain += "G";
                break;
            case "G":
                complimentaryChain += "C";
                break;
            case "T":
                complimentaryChain += "A";
                break;
            default:
                break;
        }
    }
    setOutputVal(complimentaryChain);
}

function paintPairs() {
    let dnaBases = getInputVal();
    for (let i = 0; i < dnaBases.length - (dnaBases.length % 3); i += 3) {
        let rgb = { red: "", green: "", blue: "" };
        //First
        switch (dnaBases[i]) {
            case "A":
                rgb.red = 256;
                break;
            case "C":
                rgb.red = 171;
                break;
            case "G":
                rgb.red = 85;
                break;
            case "T":
                rgb.red = 0;
                break;
            default:
                throw "Out of Bounds Letter";
                break;
        }
        //Second
        switch (dnaBases[i + 1]) {
            case "A":
                rgb.green = 256;
                break;
            case "C":
                rgb.green = 171;
                break;
            case "G":
                rgb.green = 85;
                break;
            case "T":
                rgb.green = 0;
                break;
            default:
                throw "Out of Bounds Letter";
                break;
        }
        //Third
        switch (dnaBases[i + 2]) {
            case "A":
                rgb.blue = 256;
                break;
            case "C":
                rgb.blue = 171;
                break;
            case "G":
                rgb.blue = 85;
                break;
            case "T":
                rgb.blue = 0;
                break;
            default:
                throw "Out of Bounds Letter";
                break;
        }
        console.log(rgb);
    }

}

function clearResult() {
    setOutputVal(getOutputVal().substr(0, getOutputVal().length - 1));
}