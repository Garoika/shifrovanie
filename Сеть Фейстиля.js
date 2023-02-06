const letters = {
    "a": "00011",
    "b": "11001",
    "c": "01110",
    "d": "01001",
    "e": "00001",
    "f": "01101",
    "g": "11010",
    "h": "10100",
    "i": "00110",
    "j": "01011",
    "k": "01111",
    "l": "10010",
    "m": "11100",
    "n": "01100",
    "o": "11000",
    "p": "10110",
    "q": "10111",
    "r": "01010",
    "s": "00101",
    "t": "10000",
    "u": "00111",
    "v": "11110",
    "w": "10011",
    "x": "11101",
    "y": "10101",
    "z": "10001"
};

const word = "qwerty";
const n = 1;

if(n >= word.length * 5) {
    console.log("Нельзя использовать такое большое число раундов для этого слова! (Не должно быть больше чем СЛОВО * 5)")
    return;
}

if (word.length % 2 !== 0 || word.length === 0) {
    console.log("Нельзя шифровать слова с нечетным кол-вом букв!");
    return;
}

const letterInfo = word.split("").map(letter => letters[letter.toLowerCase()]);

let firstHalf = letterInfo.slice(0, letterInfo.length / 2);
let secondHalf = letterInfo.slice(letterInfo.length / 2);

console.log("Было:", firstHalf.join(" ") + " | " + secondHalf.join(" "));

for (let i = 1; i <= n; i++) {
    let newNumbers = secondHalf.join("") + XOR(firstHalf.join(""), secondHalf.join(""));
    let [left, right] = divideString(newNumbers);
    firstHalf = left.split("");
    secondHalf = right.split("");
}

console.log("Ответ:", firstHalf.join("") + " | " + secondHalf.join(""));

function XOR(a, b) {
    let result = "";
    for (let i = 0; i < a.length; i++) {
        result += a[i] === b[i] ? "0" : "1";
    }
    return result;
}

function divideString(str) {
    const halfLength = Math.ceil(str.length / 2);
    return [str.slice(0, halfLength), str.slice(halfLength)];
}
