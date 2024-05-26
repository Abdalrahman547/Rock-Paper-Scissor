#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoise { Rock = 1, Paper = 2, Scssior = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoise Player1Choise;
	enGameChoise ComputerChoise;
	enWinner RoundWinner;
	string WinnerName;
};
struct stGameResults
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

short HowManyRounds()
{
	short rounds = 1;
	do
	{
		cout << "How many rounds from 1 to 10 ?\n";
		cin >> rounds;
	} while (rounds < 1 || rounds > 10);
	return rounds;
}

int RandomNumber(int from, int to)
{
	int randNum = rand() % (to - from + 1) + from;
	return randNum;
}

enGameChoise ReadPlayer1Choise()
{
	short choise = 1;
	do
	{
		cout << "Your choise: " << "[1] Rock, [2] Paper, [3] Scssior\n";
		cin >> choise;
	} while (choise < 1 || choise > 3);
	return (enGameChoise)choise;
}
enGameChoise ComputerChoise()
{
	return (enGameChoise)RandomNumber(1, 3);
}

string ChoiseName(enGameChoise choise)
{
	string arrChoise[3] = { "Rock", "Paper", "Scssior" };
	return arrChoise[choise - 1];
}
string WinnerName(enWinner winner)
{
	string arrWinner[3] = { "Player1", "Computer", "Draw" };
	return arrWinner[winner - 1];
}

enWinner WhoWomTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choise == RoundInfo.ComputerChoise)
		return enWinner::Draw;

	switch (RoundInfo.Player1Choise)
	{
	case enGameChoise::Rock:
		if (RoundInfo.ComputerChoise == enGameChoise::Paper)
			return enWinner::Computer;
		break;

	case enGameChoise::Paper:
		if (RoundInfo.ComputerChoise == enGameChoise::Scssior)
			return enWinner::Computer;
		break;

	case enGameChoise::Scssior:
		if (RoundInfo.ComputerChoise == enGameChoise::Rock)
			return enWinner::Computer;
		break;
	}

	return enWinner::Player1;
}
enWinner WhoWomTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;

	else if (Player1WinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

void SetWinnerScreenColor(enWinner winner)
{
	switch (winner)
	{
	case enWinner::Player1:
		system("color 2f");		  // green
		break;

	case enWinner::Computer:
		system("color 4f");		  // red
		cout << "\a";
		break;

	default:
		system("color 6f");		  // yellow
		break;
	}

}

void PrintRoundInfo(stRoundInfo RoundInfo)
{
	cout << "\n____________Round [" << RoundInfo.RoundNumber << "]____________\n\n";
	cout << "Player1 choise: " << ChoiseName(RoundInfo.Player1Choise) << endl;
	cout << "Computer choise: " << ChoiseName(RoundInfo.ComputerChoise) << endl;
	cout << "Winner name: [" << WinnerName(RoundInfo.RoundWinner) << "]" << endl;
	cout << "__________________________________\n" << endl;
	SetWinnerScreenColor(RoundInfo.RoundWinner);
}

stGameResults FillGameResults(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWomTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);
	return GameResults;
}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i < NumberOfTabs; i++)
	{
		t += "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) <<
		"__________________________________________________________\n\n";
	cout << Tabs(2) << " +++ G a m e O v e r +++ \n";
	cout << Tabs(2) <<
		"__________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "_____________________ [Game Results]_____________________\n\n";
	cout << Tabs(2) << "Game Rounds : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner : " << GameResults.WinnerName << endl;
	cout << Tabs(2) <<
		"___________________________________________________________\n";
	SetWinnerScreenColor(GameResults.GameWinner);
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choise = ReadPlayer1Choise();
		RoundInfo.ComputerChoise = ComputerChoise();
		RoundInfo.RoundWinner = WhoWomTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;
		PrintRoundInfo(RoundInfo);
	}
	return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

void ResetScreen()
{
	system("cls");
	system("color 0f");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(HowManyRounds());
		ShowGameOverScreen;
		ShowFinalGameResults(GameResults);

		cout << "Do you want to play again? Y/N ?\n";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
