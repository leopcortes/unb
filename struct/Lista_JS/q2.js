// Estava dando um erro no import, por isso coloquei o array aqui.
alunos = [
    {
        nome: "Aluno1",
        idade: 18,
        mediaFinal: 7,
    },
    {
        nome: "Aluno2",
        idade: 17,
        mediaFinal: 10,
    },
    {
        nome: "Aluno3",
        idade: 16,
        mediaFinal: 3,
    },
    {
        nome: "Aluno4",
        idade: 19,
        mediaFinal: 8,
    },
    {
        nome: "Aluno5",
        idade: 21,
        mediaFinal: 5,
    },
    {
        nome: "Aluno6",
        idade: 35,
        mediaFinal: 6,
    }
]

function calcMedia(array) {
    let soma = 0;
    for(let i=0; i<array.length; i++) {
        soma += array[i];
    }
    return soma / array.length;
}

function calcDesvioPadrao(array) {
    const media = calcMedia(array);
    let aux = 0;
    
    for(let i=0; i<array.length; i++) {
        aux += (array[i] - media)**2;
    }
    
    return (aux / array.length)**(1/2)
}

function classStatistics(turma) {
    const notas = [];
    const alunosReprovados = [];
    const alunosAprovados = [];
  
    for (let i=0; i<turma.length; i++) {
        const aluno = turma[i];
        notas.push(aluno.mediaFinal);
    
        if(aluno.mediaFinal < 5) {
            alunosReprovados.push(aluno);
        } else {
            alunosAprovados.push(aluno);
        }
    }
  
    const mediaTurma = calcMedia(notas);
    const desvioPadraoTurma = calcDesvioPadrao(notas);

    console.log('Média da turma:', mediaTurma.toFixed(2));
    console.log('Desvio padrão da turma:', desvioPadraoTurma.toFixed(2));
    console.log('Alunos reprovados:', alunosReprovados.map(aluno => aluno.nome));
    console.log('Alunos aprovados:', alunosAprovados.map(aluno => aluno.nome));
}

function addMencao(turma) {
    const turmaComMencao = [];

    for (let i=0; i<turma.length; i++) {
        let mencao = '';
        const aluno = turma[i];

        if (aluno.mediaFinal < 5) {
            mencao = 'RR';
        } else if (aluno.mediaFinal < 7) {
            mencao = 'MM';
        } else if (aluno.mediaFinal < 9) {
            mencao = 'MS';
        } else {
            mencao = 'SS';
        }

        const alunoComMencao = { ...aluno, mencao };

        turmaComMencao.push(alunoComMencao);
    }
    return turmaComMencao;
}

classStatistics(alunos);
console.log(addMencao(alunos));
