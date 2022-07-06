//quiz sobre o PAC
const quizData = [
    {
        question: "Em que pais o Arduino foi criado?",
        a: "EUA",
        b: "Canada",
        c: "India",
        d: "Italia",
        correct: "d",
    },
    {
        question: "Qual a linguagem adequada para programar o Arduino?",
        a: "C",
        b: "C++",
        c: "Java",
        d: "JavaScript",
        correct: "b",
    },
    {
        question: "O que significa HTML?",
        a: "Hypertext Markup Language",
        b: "Cascading Style Sheet",
        c: "Jason Object Notation",
        d: "Helicopters Terminals Motorboats Lamborghinis",
        correct: "a",
    },
    {
        question: "Na linguagem C, como podemos declarar um variável que seja um número real? ",
        a: "Int",
        b: "Float",
        c: "String",
        d: "Char",
        correct: "b",
    },
];

const quiz = document.getElementById("quiz");
const answerEls = document.querySelectorAll(".answer");
const questionEl = document.getElementById("question");
const a_text = document.getElementById("a_text");
const b_text = document.getElementById("b_text");
const c_text = document.getElementById("c_text");
const d_text = document.getElementById("d_text");
const submitBtn = document.getElementById("submit");

let currentQuiz = 0;
let score = 0;

loadQuiz();

function loadQuiz() {
    deselectAnswers();

    const currentQuizData = quizData[currentQuiz];

    questionEl.innerText = currentQuizData.question;
    a_text.innerText = currentQuizData.a;
    b_text.innerText = currentQuizData.b;
    c_text.innerText = currentQuizData.c;
    d_text.innerText = currentQuizData.d;
}

function getSelected() {
    let answer = undefined;

    answerEls.forEach((answerEl) => {
        if (answerEl.checked) {
            answer = answerEl.id;
        }
    });

    return answer;
}

function deselectAnswers() {
    answerEls.forEach((answerEl) => {
        answerEl.checked = false;
    });
}

submitBtn.addEventListener("click", () => {
    // confere a resposta
    const answer = getSelected();

    if (answer) {
        if (answer === quizData[currentQuiz].correct) {
            score++;
        }

        currentQuiz++;
        if (currentQuiz < quizData.length) {
            loadQuiz();
        } else {
            quiz.innerHTML = `
                <h2>Você respondeu ${score}/${quizData.length} questões corretas.</h2>
                
                <button onclick="location.reload()">Reload</button>
            `;
        }
    }
});
