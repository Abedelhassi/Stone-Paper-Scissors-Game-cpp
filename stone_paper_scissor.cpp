#include<iostream>
#include<cstdlib>
using namespace std;
enum enGameChoise{Stone=1,Paper=2,Scissors=3};
enum enWinner{Player1=1,Computer=2,Draw=3};
struct stRoundInfo {
	short RoundNumber = 0;
	enGameChoise Player1Choise;
	enGameChoise ComputerChoise;
	enWinner Winner;
	string WinnerName; 
};
struct stGameResults {
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short Computer2WinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};
int RandomNumber(int From, int To) {
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}
string WinnerName(enWinner Winner) {
	string arrWinnerName[3] = { "Player1", "Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}
enWinner WhoWonTheRond(stRoundInfo RoundInfo) {
	if (RoundInfo.Player1Choise == RoundInfo.ComputerChoise) {
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choise) {
	case enGameChoise::Stone:
		if (RoundInfo.ComputerChoise == enGameChoise::Paper) {
			return enWinner::Computer;
		}
		break;
	case enGameChoise::Paper:
		if (RoundInfo.ComputerChoise == enGameChoise::Scissors) {
			return enWinner::Computer;
		}
		break;
	case enGameChoise::Scissors:
		if (RoundInfo.ComputerChoise == enGameChoise::Stone) {
			return enWinner::Computer;
		}
		break;
	}// switch case t3 computer 
	return enWinner::Player1; //player winner
}
string ChoiseName(enGameChoise Choise) {
	string arrGameChoises[3] = { "Stone","Paper", "Scissors" };
	return arrGameChoises[Choise - 1];
}
void SetWinnerScreenColor(enWinner Winner) {
	switch (Winner) {
	case enWinner::Player1:
		system("color 2F"); // turn system to green 
		break;
	case enWinner::Computer:
		system("color 4F");// Red
		break;
	default: 
		system("color 6F");//yellow 
		break;
	}
}
void PrintRoundResults(stRoundInfo RoundInfo) {
	cout << "\n ____________Round[" << RoundInfo.RoundNumber << "] ____________________\n\n";
	cout << " Player1 Choise : " << ChoiseName(RoundInfo.Player1Choise) << endl;
	cout << " Computer Choise : " << ChoiseName(RoundInfo.ComputerChoise) << endl;
	cout << "Round Winner  : [" << RoundInfo.WinnerName << "]\n";
	cout << "_______________________________________\n" << endl;
	SetWinnerScreenColor(RoundInfo.Winner);
}
 
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}
stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes) {
	stGameResults GameResults;
	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.Computer2WinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);
	return GameResults;

}
enGameChoise ReadPlayer1Choise() {
	short Choise = 1;
	do { 
		cout << "\nYour choise : [1]:stone , [2]:paper , [3]:scissors ? ";
		cin >> Choise; 
 
	} while (Choise < 1 || Choise >3); 
	return (enGameChoise)Choise; 
}
enGameChoise GetComputerChoise (){
	return (enGameChoise)RandomNumber(1, 3);
}
stGameResults PlayGame(short HowManyRounds) {
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
		cout << "\n Round [ " << GameRound << " ] begins :\n ";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choise = ReadPlayer1Choise();
		RoundInfo.ComputerChoise = GetComputerChoise();
		RoundInfo.Winner = WhoWonTheRond(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;
		PrintRoundResults(RoundInfo);
	}
	return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);

}
string Tabs(short NumbrOfTabs) {
	string t = "";
	for (int i = 1; i < NumbrOfTabs; i++) {
		t = t + "\t";
		cout << t;
	}
	return t;
}
void ShowGameOverScreen() {
	cout << Tabs(2) << "_____________________________________\n\n";
	cout << Tabs(2) << "                          +++ Game Over +++\n";
	cout << Tabs(2) << "_____________________________________________________\n\n ";
}
void ShowFinalGameReslts(stGameResults GameResults) {
	cout << Tabs(2) << "___________________________[Game Resuts ]_______________________________\n\n";
	cout << Tabs(2) << "Game Rounds          :" << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times   : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "computer won times : " << GameResults.Computer2WinTimes << endl;
	cout << Tabs(2) << "Draw times            : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner             : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "______________________________________________________\n";
	SetWinnerScreenColor(GameResults.GameWinner);
}
short ReadHowManyRounds() {
	short GameRounds = 1;
	do {
		cout << " how many rounds 1 to 10 ?? \n ";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds>10);
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
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameReslts(GameResults);
		cout << endl << Tabs(3) << " do you wanna play again? Y/N";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main() {
	srand((unsigned)time(NULL));
	StartGame();
	return 0; 
}   
