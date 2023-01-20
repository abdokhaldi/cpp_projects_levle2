 /*
            #################  project 1 _ stone-paper-scisors game ###################

    * Using  progrmming language : C++

    Requierments  :

 # ask how many rounds the game will be 
 # start each round player vs computer
 # show the results with each rounds 
 # if computer wins the round ring a bill , and screed red
 # if player won the round show green screen
 # after all rounds show  game over the print game results ,
   # then ask the user if s/he want to play again ?


*/

#include <iostream>
using namespace std;

enum enGameChoice{Stone=1,Paper=2,Scissors=3};
enum enWinner{Player=1, Computer=2, Draw=3};

struct stRoundInfo {
    short RoundNumber = 0;
    enGameChoice Player1Choice ;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName = "";
};
struct stGameResults {
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short Computer2WinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string  WinnerName = "";

};

int RandomNumber(int From, int To) {
    int rnd = rand() % (To - From + 1) + From;
    return rnd;
}

string WinnerName(enWinner winner) {
    string arrWinnerName[3] = { "player" , "computer" , "no winner" };
    return arrWinnerName[winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice) {
        return enWinner::Draw;
    }
    switch (RoundInfo.Player1Choice) {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
        
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;

    }

    return enWinner::Player;
    
}

string ChoiceName(enGameChoice Choice) {
    string arrGameChoices[3] = { "stone" , "paper" , "scissors" };
    return arrGameChoices[Choice - 1];
}

void setWinnerScreenColor(enWinner winner) {
    switch (winner) {
    case enWinner::Player:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default :
        system("color 6F");
        break;
   }
}

void PrintRoundResults(stRoundInfo RoundInfo) {
    cout << "\n_________________ round [ " << RoundInfo.RoundNumber << "] _________________\n\n";
    cout << " player1 choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << " computer choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << " round winner : [ " << RoundInfo.WinnerName << " ] \n";
    cout << "__________________________________ \n";
}

enWinner WhoWonTheGame(short playerWinTimes, short computerWinTimes) {
        if (playerWinTimes > computerWinTimes)
            return enWinner::Player;
        else if (computerWinTimes > playerWinTimes)
            return enWinner::Computer;
        else
            return enWinner::Draw;
    
}

stGameResults FillGameResults(int GameRounds, short player1Times, short computerTimes, short drawTimes) 
    {
        stGameResults GameResults;

        GameResults.GameRounds = GameRounds;
        GameResults.Player1WinTimes = player1Times;
        GameResults.Computer2WinTimes = computerTimes;
        GameResults.DrawTimes = drawTimes;
        GameResults.GameWinner = WhoWonTheGame(player1Times, computerTimes);
        GameResults.WinnerName = WinnerName(GameResults.GameWinner);
        return GameResults;
    }
    
enGameChoice ReadPlayer1Choice(){
    short Choice = 1; 
    do { 
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";    
        cin >> Choice; 
    } while (Choice < 1 || Choice >3);
    return (enGameChoice)Choice;

} 

enGameChoice getComputerChoice(){
    return (enGameChoice)RandomNumber(1, 3);
}


stGameResults PlayGame(short howManyRounds) {
    stRoundInfo RoundInfo;
    short player1WinTimes = 0, computerWinTimes = 0, drawTimes = 0;

    for (short GameRound = 1; GameRound <= howManyRounds; GameRound++) {
        cout << "Round [" << GameRound << "] Begins : \n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = getComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player)
        {
            player1WinTimes++;
            }
        else if (RoundInfo.Winner == enWinner::Computer)
        {
            computerWinTimes++;
        }
        else {
            drawTimes++;
        }
        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(howManyRounds, player1WinTimes,computerWinTimes,drawTimes);
}





string Tabs(short numberOfTab) {
    string t = "";
    for (short i = 0; i <= numberOfTab; i++)
        t = t + "\t";
    return t;
}

void ShowGameOverScreen() {
    cout << Tabs(2) << "______________________________________________\n\n";
    cout << Tabs(2) << "             ++++ G a m e O v e r  ++++ \n";
    cout << Tabs(2) << "______________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults) {
    cout << "____________[ Game Results ]____________\n";
    cout << "game rounds : " << GameResults.GameRounds << endl;
    cout << "player win times : " << GameResults.Player1WinTimes << endl;
    cout << "computer win times : " << GameResults.Computer2WinTimes << endl;
    cout << "draw times : " << GameResults.DrawTimes << endl;
    cout << "final winner : " << GameResults.WinnerName << endl;
    cout << "__________________________________________ \n";

    setWinnerScreenColor(GameResults.GameWinner);
    }

short ReadHowManuRounds() {
    short GameRounds = 0;
    do {
        cout << "How many round 1 to 10 \n ";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds >10);
    return GameRounds;
}



void ResetScreen() {
    system("cls");
    system("color 0F");
}

void StartGame() {
    char PlayAgain = 'Y';
           
    do {
        ResetScreen();
        stGameResults GameResults=PlayGame(ReadHowManuRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << " Do you want to play again ? Y/N ? ";
        cin >> PlayAgain;
    } while (PlayAgain=='Y' || PlayAgain=='y');
    }
 
int main()
{
    srand((unsigned)time(NULL));
    
    StartGame();
}

