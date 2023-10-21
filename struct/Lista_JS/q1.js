const calculateIMC = (peso, altura) => peso/(altura**2);

console.log("IMC: " + calculateIMC(70, 1.80))

function generateUser(nome, idade, email) {
    return {nome, idade, email}
}

console.log(generateUser("joao", 30, "joao@gmail.com"))


function paresArray(array){
    var pares = [];
    
    for(var i=0; i<array.length; i++) {
        if(array[i] % 2 === 0) {
            pares.push(array[i]);
        }
    }
    return pares;
}

const array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
console.log(paresArray(array))
