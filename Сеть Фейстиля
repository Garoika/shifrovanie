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

const word = "qwer" // Ввести слово с четным кол-вом букв

const n = 2
const letterInfo = []
let firstHalf = []
let secondHalf = []

if(n >= word.length * 5) {
    console.log("Нельзя использовать такое большое число раундов для этого слова! (Не должно быть больше чем СЛОВО * 5)")
    return;
}

if (word.length % 2 !== 0 || word.length === 0) {
    console.log("Нельзя шифровать слова с нечетным кол-вом слов!")
    return;
};

word.split("").map(item => {
    letterInfo.push(getLetter(item))
})

for (let i = 0; i < word.length / 2; i++) {
    firstHalf.push(letterInfo[i])
}

for (let i = word.length / 2; i < word.length; i++) {
    secondHalf.push(letterInfo[i])
}

console.log("Было:", firstHalf.join(" ") + " | " + secondHalf.join(" "))

for (let i = 1; i <= n; i++) {
    let newNumbers = blockFeistel(firstHalf, secondHalf, i)
    let divide = divideString(newNumbers)
    firstHalf = divide[0].split("")
    secondHalf = divide[1].split("")
}

console.log("Ответ:", firstHalf.join("") + " | " + secondHalf.join(""))

function getLetter(letter) {
    const letArray = letters[letter.toLowerCase()]
    return letArray
}

function blockFeistel(numberLeft, numberRight, key) {
    let left = "";
    let right = "";

    numberLeft.map(item => { left += item });
    numberRight.map(item => { right += item });

    let leftSplit = left.split("");

    left = moveElements(leftSplit, key).join("")
    left = XOR(left, right)

    return right + left
}

function moveElements(arr, n) {
    if (n >= arr.length) {
        return arr;
    }

    return arr.slice(n).concat(arr.slice(0, n));
}

function XOR(a, b) {
    let result = "";
    for (let i = 0; i < a.length; i++) {
        result += a[i] === b[i] ? "0" : "1";
    }
    return result;
}

function divideString(str) {
    const length = str.length;
    const halfLength = Math.ceil(length / 2);

    return [str.slice(0, halfLength), str.slice(halfLength)];
}
