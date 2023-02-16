let numbers = [...prompt("Введи уже хочь че то: ").toString()].map(Number)
if(numbers.length != 3) throw new Error("Чисел должно быть ровно 3!");

numbers.map(item => {
    if(item != 0 && item != 1) throw new Error("Числа должны быть равны 1 или 0!");
}); 

console.log(numbers[0], numbers[1], numbers[2]);

let lastGamma;

for(let i = 0; i < 8; i++) {
    let result = getGamma(numbers);
    console.log(result[0], result[1], result [2], result[3])
    numbers = result.slice(0, 3)
}


function getGamma(numbers) {
    let newA, newB, newC, gamma;
    gamma = numbers[2];
    if(numbers[0] == numbers[2]) newX = 0;
    if(numbers[0] != numbers[2]) newX = 1;
    
    newY = numbers[0];
    newC = numbers[1];
    
    let newArray = [newX, newY, newC, gamma];
    return newArray;
}
