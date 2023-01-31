
// math game


#include <iostream>
using namespace std;

enum enLevels{Easy=1,Medium=2,Hard=3,MixLevels=4};
enum enOperatinType{Add=1,Sub=2,Mul=3,Div=4,Mix=5};

struct stQuestion {
    int Number1 = 0;
    int Number2 = 0;
    enLevels QuestionLevel;
    enOperatinType OperationType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
     
};
struct stQuiz {
    stQuestion QuestionList[100];
    short NumberOfQuestions ;
    enLevels questionLevel;
    enOperatinType operationType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
   
};

string GetOpTypeSymbol(enOperatinType OpType) {
    switch (OpType) {
        case enOperatinType::Add:
            return"+"; 
            case enOperatinType::Sub: 
            return "-";
            case enOperatinType::Mul:
            return "x"; 
            case enOperatinType::Div: 
                return"/";
    default:
        return "Mix";
    }
}

string GetQuestionLevelText(enLevels QuestionLevel) { 
    string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
    return arrQuestionLevelText[QuestionLevel - 1];
}

enLevels ReadQuestuinLevel() {
    short QuestionLevel = 0;
    do {
        cout << " choose question level [1]easy [2]medium [3]hard [4]mix \n";
        cin >> QuestionLevel;
    } while (QuestionLevel <1 || QuestionLevel>4);
    return (enLevels)QuestionLevel;
}

void SetScreenColor(bool Right) {
    if (Right)
        system("color 2F");
    else {
        system("color 4F");
        cout << "\a";
    }
}

int ReadHowManyNumber() {
    int Number = 0;
    do {
        cout << "how many questions do you want? \n";
        cin >> Number;
    } while (Number <= 0);
    return Number;
}

enOperatinType ReadOperationType() {
    short operationType = 0;
    do {
        cout << " choose operation type [1]Add [2]Sub [3]Mul [4]Div [5]Mix \n";
        cin >> operationType;
    } while (operationType < 1 || operationType>5);
    return (enOperatinType)operationType;
}


int SimpleCalculator(int Number1, int Number2, enOperatinType OpType) {
    switch (OpType) {
    case enOperatinType::Add:
        return Number1 + Number2;
    case enOperatinType::Sub:
        return Number1 - Number2;
    case enOperatinType::Mul:
        return Number1 * Number2;
    case enOperatinType::Div:
        return Number1 / Number2;
    default :
        return Number1 + Number2;
}
}
int RandomNumber(int From , int To) {
    return rand() % (To - From + 1) + From;
}
enOperatinType GetRandomOperationType() {
    int Op = RandomNumber(1, 4);
    return (enOperatinType)Op;
}
stQuestion GenerateQuestion(enLevels QuestionLevel, enOperatinType OperationType) {
    stQuestion Question;
    if (QuestionLevel == enLevels::MixLevels) {
        QuestionLevel = (enLevels)RandomNumber(1, 3);
    }
    if (OperationType == enOperatinType::Mix) {
        OperationType = GetRandomOperationType();
    }
    Question.OperationType = OperationType;
    switch (QuestionLevel) {
    case enLevels::Easy:
       Question.Number1 = RandomNumber(1, 10);
       Question.Number2 = RandomNumber(1, 10);

       Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
       Question.QuestionLevel = QuestionLevel;

    case enLevels::Medium:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;

    case enLevels::Hard:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
    }
    return Question;
}

int ReadQuestionAnswer() {
    int Answer = 0;
    cin >> Answer;
    return Answer;
}
 
void PrintTheQuestion(stQuiz& Quiz, short QuestionNumber) { 
    cout << "\n";   
    cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "] \n\n";   
    cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;  
    cout << Quiz.QuestionList[QuestionNumber].Number2 << " ";   
    cout << GetOpTypeSymbol(Quiz.QuestionList[QuestionNumber].OperationType);
    cout << "\n_________" << endl;
               
}

void CorrectTheQuestionAnswer(stQuiz& Quiz, short QuestionNumber) {
    if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].CorrectAnswer) {
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
        Quiz.NumberOfWrongAnswers++;
        cout << "Worng Answer :-( \n";
        cout << "The right answer is: ";
        cout << Quiz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }
    else {
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
        Quiz.NumberOfRightAnswers++;
        cout << "Right Answer :-) \n";
    }
    cout << endl;
    SetScreenColor(Quiz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectListAnswers(stQuiz& Quiz){
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++) {
        PrintTheQuestion(Quiz,QuestionNumber);
        Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quiz, QuestionNumber);
    }
    Quiz.isPass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

void GenerateQuizQuestion(stQuiz& Quiz) {
    for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++) {
        Quiz.QuestionList[Question] = GenerateQuestion(Quiz.questionLevel, Quiz.operationType);
    }
}

string GetFinalResultsText(bool pass){
    if (pass)
        return "Pass -)";
    else
        return "Fail -(";
}

void PrintQuizResult(stQuiz Quiz){
    cout << "\n";     
    cout << "______________________________\n\n";
    cout << " Final Resutls is " << GetFinalResultsText(Quiz.isPass);   
    cout << "\n______________________________\n\n";
    cout << "Number of Questions: " << Quiz.NumberOfQuestions << endl;  
    cout << "Questions Level    : " << GetQuestionLevelText(Quiz.questionLevel) << endl;  
    cout << "OpType             : " << GetOpTypeSymbol(Quiz.operationType) << endl;   
    cout << "Number of Right Answers: " << Quiz.NumberOfRightAnswers << endl;  
    cout << "Number of Wrong Answers: " << Quiz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n";
}

void PlayMathGame(){
    stQuiz Quiz;
    Quiz.NumberOfQuestions = ReadHowManyNumber();
    Quiz.questionLevel = ReadQuestuinLevel();
    Quiz.operationType = ReadOperationType();

    GenerateQuizQuestion(Quiz);
    AskAndCorrectListAnswers(Quiz);
    PrintQuizResult(Quiz);
}
void ResetScreen(){
    system("cls");
    system("color 0F");
}
void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        PlayMathGame();

        cout << "do you want to play again Y/N ? \n" ;
        cin >> PlayAgain;
    } while (PlayAgain ==  'Y' || PlayAgain == 'y');
}
int main()
{
    srand((unsigned)time(NULL));

    StartGame();

   
}

