#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <ctime>
#include<iomanip>
#include<windows.h>
#pragma warning(disable : 4996) 

using namespace std;

struct player
{
	string id, name;
	int score;

}p1, p2;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

ofstream History;
char ans;
int noOfGames;
time_t t = time(NULL);
tm* timePtr = localtime(&t);
string winner;

string board[8][8] = {
	{ "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |" },
	{ "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |" },
	{ "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |" },
	{ "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |" },
	{ "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |" },
	{ "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |" },
	{ "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |" },
	{ "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |", "| _ |" } };

string boardXO[3][3] =
{
	{ "|_____|", "|_____|", "|_____|" },
	{ "|_____|", "|_____|", "|_____|" },
	{ "|_____|", "|_____|", "|_____|" } };

void file();

void nameInput();

void draw();

bool check(player, int rows, int col);

void filling();

bool gameover();

void restart();

bool checkFour;

bool gover;

void drawXO();

void restartXO();

bool checkkXO;

void fillingXO();

bool checkXO(player);

bool gameoverXO();

bool goverXO;

bool enter = false;

int main()
{
	SetConsoleTextAttribute(hConsole, 0x0B);

	int option;
	noOfGames = 0; p1.score = 0; p2.score = 0;
	cout << "\n PLEASE CHOOSE AN OPTION ^_^\n\n";
	SetConsoleTextAttribute(hConsole, 0x0F);

	cout << " 1 - Play CONNECT FOUR\n 2 - Play TIC-TAC-TOE\n 3 - Exit\n ";
	cin >> option;

	if (option == 1) {
		History.open("History.txt", ios::app);

		p1.id = "| 1 |"; p2.id = "| 2 |";
		system("cls");
		SetConsoleTextAttribute(hConsole, 0x0F);

		cout << endl << endl << right << setw(77) << "WELCOME TO CONNECT FOUR GAME ^_^ \n\n";


		nameInput();

		draw();

		filling();
	}

	else if (option == 2) {
		p1.id = "|  X  |"; p2.id = "|  O  |";
		system("cls");
		cout << endl << endl << right << setw(72) << "WELCOME TO TIC-TAC-TOE GAME ^_^" << endl << endl;

		nameInput();

		drawXO();

		fillingXO();

	}
	else if (option == 3) {
		cout << " Goodbye ^_^\n\n "; system("pause"); exit(0);
	}
	else {
		cin.clear();
		cin.ignore(10000, '\n');
		system("cls");
		SetConsoleTextAttribute(hConsole, 0x04);

		cout << "\n Invalid!\n"; main();
		SetConsoleTextAttribute(hConsole, 0x0F);

	}
	system("pause");
	return 0;
}

void nameInput() {

	SetConsoleTextAttribute(hConsole, 0x0c);

	cout << " Please Enter Player 1's Name : "; cin >> p1.name;

	SetConsoleTextAttribute(hConsole, 0x09);

	cout << " Please Enter Player 2's Name : "; cin >> p2.name;
	SetConsoleTextAttribute(hConsole, 0x0F);


}

void draw() {
	system("cls");
	SetConsoleTextAttribute(hConsole, 0x0b);

	cout << endl; cout << right << setw(38);
	for (int mycolumns = 0; mycolumns <= 7; mycolumns++)
		cout << "    " << mycolumns + 1;
	SetConsoleTextAttribute(hConsole, 0x0f);

	cout << endl;
	for (int boardRows = 0; boardRows < 8; ++boardRows) {
		//	cout << right << setw(25);
		//	cout << right << setw(76) << "|   ||   ||   ||   ||   ||   ||   ||   |" << endl;
		cout << right << setw(35);
		SetConsoleTextAttribute(hConsole, 0x0b);

		cout << boardRows + 1 << " ";
		SetConsoleTextAttribute(hConsole, 0x0f);

		for (int boardColumns = 0; boardColumns < 8; ++boardColumns) {

			if (board[boardRows][boardColumns] == p1.id) {
				SetConsoleTextAttribute(hConsole, 0x04);

				cout << board[boardRows][boardColumns];

				SetConsoleTextAttribute(hConsole, 0x0F);

			}
			else if (board[boardRows][boardColumns] == p2.id) {
				SetConsoleTextAttribute(hConsole, 0x01);

				cout << board[boardRows][boardColumns];
				SetConsoleTextAttribute(hConsole, 0x0F);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 0x0F);

				cout << board[boardRows][boardColumns];

			}

		}
		cout << endl;

	}

	if (checkFour == false && gover == false) {

		cout << endl;
		SetConsoleTextAttribute(hConsole, 0x0b);
		cout << right << setw(65) << "Available Cells : " << endl << endl;
		SetConsoleTextAttribute(hConsole, 0x0F);

		for (int availableRows = 0; availableRows < 8; availableRows++) {

			cout << right << setw(20);
			SetConsoleTextAttribute(hConsole, 0x0b);

			cout << "| ";
			SetConsoleTextAttribute(hConsole, 0x0f);

			for (int availableColumns = 0; availableColumns < 8; availableColumns++) {

				if (board[availableRows][availableColumns] == "| _ |") {

					cout << "(" << availableRows + 1 << " , " << availableColumns + 1 << ")";

				}
				else

					cout << "_______";
				SetConsoleTextAttribute(hConsole, 0x0b);

				cout << " | ";
				SetConsoleTextAttribute(hConsole, 0x0f);

			}
			cout << endl;

		}


	}
	cout << endl << endl;
	SetConsoleTextAttribute(hConsole, 0x0F);

}

void filling() {
	int i, j;
	while (true) {
		SetConsoleTextAttribute(hConsole, 0x04);
		cout << " " << p1.name;
		SetConsoleTextAttribute(hConsole, 0x0F);
		cout << "'s Turn, Please Enter Index Of The Desired Cell as ( row column ), ( Your ID Is '1' )\n To go to menu: enter 0 0\n ";


		while (true) {
			cin >> i >> j;
			if (i == 0 && j == 0) { system("cls"); restart(); main(); }
			if (cin.fail() || i - 1 > 7 || j - 1 > 7 || board[i - 1][j - 1] != "| _ |" || i - 1 < 0 || j - 1 < 0) {
				cin.clear();
				cin.ignore(10000, '\n');
				draw();
				cout << " Invalid Entry!! :( , Please ";
				SetConsoleTextAttribute(hConsole, 0x04);
				cout << p1.name;
				SetConsoleTextAttribute(hConsole, 0x0F);
				cout << " Try Again :) (Your ID Is '1' ) :\n To go to menu: enter 0 0\n ";

				continue;

			}
			else if (board[i][j - 1] == "| _ |") {

				draw();

				cout << " The cell (" << i + 1 << " , " << j << ") isn't full yet :(\n Please ";
				SetConsoleTextAttribute(hConsole, 0x04);
				cout << p1.name;
				SetConsoleTextAttribute(hConsole, 0x0F);
				cout << " Try Again :) (Your ID Is '1' ) :\n To go to menu: enter 0 0\n ";


				continue;

			}
			else break;

		}

		board[i - 1][j - 1] = p1.id;

		checkFour = check(p1, i - 1, j - 1);

		gover = gameover();

		draw();

		if (checkFour) {

			p1.score++; noOfGames++;

			cout << right << setw(40) << "Congratulations!! ";
			SetConsoleTextAttribute(hConsole, 0x04);
			cout << p1.name;
			SetConsoleTextAttribute(hConsole, 0x0F);
			cout << ", You Connected Four (1)s -- > You're the Winner ^_^\n\n";

		label: cout << right << setw(70) << " Would you like to continue Connect Four? (y/n)\n To go to menu: enter 0\n "; cin >> ans;
			if (ans == 'y') {
				restart();
				draw();
				continue;
			}
			else if (ans == 'n') {

				cout << endl << " Goodbye ^_^\n "; break;
			}
			else if (ans == '0') {
				system("cls"); file(); restart(); main();
			}
			else {
				system("cls");
				cout << " Invalid\n"; goto label;
			}


		}

		if (gover) {

			noOfGames++;
			cout << right << setw(70) << "None of the players has won :(\n";
		label2: cout << right << setw(70) << " Would you like to restart Connect Four? (y/n)\n To go to menu: enter 0\n "; cin >> ans;
			if (ans == 'y') {
				restart();
				draw();
				continue;
			}
			else if (ans == 'n') {

				cout << endl << " Goodbye ^_^ " << endl; break;
			}
			else if (ans == '0') {
				system("cls"); file(); restart(); main();
			}
			else {
				system("cls");
				cout << " Invalid\n"; goto label2;
			}


		}
		SetConsoleTextAttribute(hConsole, 0x01);
		cout << " " << p2.name;
		SetConsoleTextAttribute(hConsole, 0x0F);
		cout << "'s Turn, Please Enter Index Of The Desired Cell as ( row column ), ( Your ID Is '2' )\n To go to menu: enter 0 0\n ";


		while (true) {

			cin >> i >> j;

			if (i == 0 && j == 0) { system("cls"); restart(); main(); }
			if (cin.fail() || i - 1 > 7 || j - 1 > 7 || board[i - 1][j - 1] != "| _ |" || i - 1 < 0 || j - 1 < 0) {

				cin.clear();
				cin.ignore(1, '\n');
				draw();

				cout << " Invalid Entry!! :( , Please ";
				SetConsoleTextAttribute(hConsole, 0x01);
				cout << p2.name;
				SetConsoleTextAttribute(hConsole, 0x0F);
				cout << " Try Again :) (Your ID Is '2' ) :\n To go to menu: enter 0 0\n ";

				continue;

			}
			else if (board[i][j - 1] == "| _ |") {

				system("cls");

				draw();

				cout << " The cell (" << i + 1 << " , " << j << ") isn't full yet :(\n Please ";
				SetConsoleTextAttribute(hConsole, 0x01);
				cout << p2.name;
				SetConsoleTextAttribute(hConsole, 0x0F);
				cout << " Try Again :) (Your ID Is '2' ) :\n To go to menu: enter 0 0\n ";


				continue;

			}
			else break;

		}
		board[i - 1][j - 1] = p2.id;

		checkFour = check(p2, i - 1, j - 1);

		gover = gameover();

		draw();

		if (checkFour) {

			p2.score++; noOfGames++;

			cout << right << setw(40) << "Congratulations!! ";
			SetConsoleTextAttribute(hConsole, 0x01);
			cout << p2.name;
			SetConsoleTextAttribute(hConsole, 0x0F);
			cout << ", You Connected Four (2)s -- > You're the Winner ^_^\n" << endl;
		label3: cout << right << setw(70) << " Would you like to continue Connect Four? (y/n)\n To go to menu: enter 0\n "; cin >> ans;
			if (ans == 'y') {
				restart();
				draw();
				continue;
			}
			else if (ans == 'n') {

				cout << endl << " Goodbye ^_^\n "; break;
			}
			else if (ans == '0') {
				file(); system("cls"); restart(); main();
			}
			else {
				system("cls");
				cout << " Invalid\n"; goto label3;
			}


		}

		if (gover) {

			noOfGames++;
			cout << right << setw(70) << "None of the players has won :(\n";
		label4: cout << right << setw(70) << " Would you like to restart Connect Four? (y/n)\n To go to menu: enter 0\n "; cin >> ans;
			if (ans == 'y') {
				restart();
				draw();
				continue;
			}
			else if (ans == 'n') {

				cout << endl << " Goodbye ^_^ " << endl; break;
			}
			else if (ans == '0') {
				system("cls"); restart(); main();
			}
			else {
				system("cls");
				cout << " Invalid\n"; goto label4;
			}

		}
	}
	file();
}

bool check(player activePlayer, int rows, int col)
{
	bool win = false;

	string ID = activePlayer.id;


	if (rows >= 0 && rows <= 7 && col >= 0 && col <= 4) {
		if (board[rows][col] == ID&&
			board[rows][col + 1] == ID&&
			board[rows][col + 2] == ID&&
			board[rows][col + 3] == ID)
			win = true;
	}

	if (rows >= 0 && rows <= 7 && col >= 1 && col <= 5) {
		if (board[rows][col - 1] == ID&&
			board[rows][col] == ID&&
			board[rows][col + 1] == ID&&
			board[rows][col + 2] == ID)
			win = true;
	}

	if (rows >= 0 && rows <= 7 && col >= 2 && col <= 6) {
		if (board[rows][col - 2] == ID&&
			board[rows][col - 1] == ID&&
			board[rows][col] == ID&&
			board[rows][col + 1] == ID)
			win = true;
	}
	if (rows >= 0 && rows <= 7 && col >= 3 && col <= 7) {
		if (board[rows][col - 3] == ID&&
			board[rows][col - 2] == ID&&
			board[rows][col - 1] == ID&&
			board[rows][col] == ID)
			win = true;
	}

	if (rows >= 0 && rows <= 4 && col >= 0 && col <= 7) {
		if (board[rows][col] == ID&&
			board[rows + 1][col] == ID&&
			board[rows + 2][col] == ID&&
			board[rows + 3][col] == ID)
			win = true;
	}

	if (rows >= 0 && rows <= 4 && col >= 0 && col <= 4) {
		if (board[rows][col] == ID&&
			board[rows + 1][col + 1] == ID&&
			board[rows + 2][col + 2] == ID&&
			board[rows + 3][col + 3] == ID)
			win = true;
	}

	if (rows >= 1 && rows <= 5 && col >= 1 && col <= 5) {
		if (board[rows - 1][col - 1] == ID&&
			board[rows][col] == ID&&
			board[rows + 1][col + 1] == ID&&
			board[rows + 2][col + 2] == ID
			)
			win = true;
	}

	if (rows >= 2 && rows <= 6 && col >= 2 && col <= 6) {
		if (board[rows - 2][col - 2] == ID&&
			board[rows - 1][col - 1] == ID  &&
			board[rows][col] == ID&&
			board[rows + 1][col + 1] == ID)
			win = true;
	}

	if (rows >= 3 && rows <= 7 && col >= 3 && col <= 7) {
		if (board[rows - 3][col - 3] == ID&&
			board[rows - 2][col - 2] == ID&&
			board[rows - 1][col - 1] == ID&&
			board[rows][col] == ID)
			win = true;
	}

	if (rows >= 0 && rows <= 4 && col >= 3 && col <= 7) {
		if (board[rows][col] == ID&&
			board[rows + 1][col - 1] == ID&&
			board[rows + 2][col - 2] == ID&&
			board[rows + 3][col - 3] == ID)
			win = true;
	}

	if (rows >= 1 && rows <= 5 && col >= 2 && col <= 6) {
		if (board[rows - 1][col + 1] == ID&&
			board[rows][col] == ID&&
			board[rows + 1][col - 1] == ID&&
			board[rows + 2][col - 2] == ID)
			win = true;
	}

	if (rows >= 2 && rows <= 6 && col >= 1 && col <= 5) {
		if (board[rows - 2][col + 2] == ID&&
			board[rows - 1][col + 1] == ID&&
			board[rows][col] == ID&&
			board[rows + 1][col - 1] == ID)
			win = true;
	}

	if (rows >= 3 && rows <= 7 && col >= 0 && col <= 4) {
		if (board[rows - 3][col + 3] == ID&&
			board[rows - 2][col + 2] == ID&&
			board[rows - 1][col + 1] == ID&&
			board[rows][col] == ID)
			win = true;
	}

	return win;
}

bool gameover() {

	bool gover = true;

	for (int rows = 0; rows < 8; rows++) {

		for (int column = 0; column < 8; column++) {

			if (board[rows][column] == "| _ |") {

				gover = false;

				break;
			}

		}
		if (gover == false)break;
	}
	return gover;
}

void restart() {

	gover = false; checkFour = false;

	for (int newRows = 0; newRows < 8; newRows++)
	{
		for (int newCols = 0; newCols <8; newCols++)
		{

			board[newRows][newCols] = "| _ |";
		}

	}
}

void drawXO() {
	system("cls");

	SetConsoleTextAttribute(hConsole, 0x0F);
	SetConsoleTextAttribute(hConsole, 0x0b);

	cout << endl; cout << right << setw(47);
	for (int j = 0; j < 3; j++)
		cout << "        " << j + 1 << " ";
	SetConsoleTextAttribute(hConsole, 0x0F);

	cout << endl;
	for (int boardRows = 0; boardRows < 3; ++boardRows) {

		//cout << right << setw(25);
		cout << right << setw(72) << "|     |   |     |   |     |\n";
		cout << right << setw(40);
		SetConsoleTextAttribute(hConsole, 0x0b);

		cout << boardRows + 1 << " ";
		SetConsoleTextAttribute(hConsole, 0x0f);

		for (int boardColumns = 0; boardColumns < 3; ++boardColumns) {

			if (boardXO[boardRows][boardColumns] == p1.id) {
				SetConsoleTextAttribute(hConsole, 0x04);

				cout << "   " << boardXO[boardRows][boardColumns];
				SetConsoleTextAttribute(hConsole, 0x0F);

			}
			else if (boardXO[boardRows][boardColumns] == p2.id) {
				SetConsoleTextAttribute(hConsole, 0x01);

				cout << "   " << boardXO[boardRows][boardColumns];
				SetConsoleTextAttribute(hConsole, 0x0F);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 0x0F);

				cout << "   " << boardXO[boardRows][boardColumns];

			}

		}
		cout << endl;

	}

	cout << endl;
}

void fillingXO() {
	int i, j;

	while (true) {
		SetConsoleTextAttribute(hConsole, 0x04);
		cout << " " << p1.name;
		SetConsoleTextAttribute(hConsole, 0x0F);
		cout << "'s Turn, Please Enter Index Of The Desired Cell as ( row column ), ( Your ID Is 'X' )\n To go to menu: enter 0 0\n ";

		while (true) {
			cin >> i >> j;
			if (i == 0 && j == 0) { system("cls"); restartXO(); main(); }
			if (cin.fail() || i - 1 > 2 || j - 1 > 2 || boardXO[i - 1][j - 1] != "|_____|" || i - 1 < 0 || j - 1 < 0) {
				cin.clear();
				cin.ignore(10000, '\n');
				drawXO();
				cout << " Invalid Entry!! :( , Please ";
				SetConsoleTextAttribute(hConsole, 0x04);
				cout << p1.name;
				SetConsoleTextAttribute(hConsole, 0x0F);
				cout << " Try Again :) (Your ID Is 'X' ) :\n To go to menu: enter 0 0\n ";

				continue;

			}
			else break;

		}

		boardXO[i - 1][j - 1] = p1.id;

		checkkXO = checkXO(p1);

		goverXO = gameoverXO();

		drawXO();

		if (checkkXO) {
			cout << endl << right << setw(40) << "Congratulations!! ";
			SetConsoleTextAttribute(hConsole, 0x04);
			cout << p1.name;
			SetConsoleTextAttribute(hConsole, 0x0F);
			cout << ", You Acheieved three (X)s -- > You're the Winner ^_^\n" << endl;

		labelXO: cout << right << setw(70) << " Would you like to continue Tic-Tac-Toe? (y/n)\n To go to menu: enter 0\n "; cin >> ans;
			if (ans == 'y') {
				restartXO();
				drawXO();
				continue;
			}
			else if (ans == 'n') {

				cout << endl << " Goodbye ^_^\n "; break;
			}
			else if (ans == '0') {
				system("cls"); restartXO(); main();
			}
			else {
				system("cls");
				cout << " Invalid\n"; goto labelXO;
			}


		}

		if (goverXO) {

			cout << " None of the players has won :(\n";
		labelXO2: cout << " Would you like to restart Tic-Tac-Toe? (y/n)\n To go to menu: enter 0\n "; cin >> ans;
			if (ans == 'y') {
				restartXO();
				drawXO();
				continue;
			}
			else if (ans == 'n') {

				cout << endl << " Goodbye ^_^\n "; break;
			}
			else if (ans == '0') {
				system("cls"); restartXO(); main();
			}
			else {
				system("cls");
				cout << " Invalid\n"; goto labelXO2;
			}


		}
		SetConsoleTextAttribute(hConsole, 0x01);
		cout << " " << p2.name;
		SetConsoleTextAttribute(hConsole, 0x0F);
		cout << "'s Turn, Please Enter Index Of The Desired Cell as ( row column ), ( Your ID Is 'O' )\n To go to menu: enter 0 0\n ";


		while (true) {

			cin >> i >> j;

			if (i == 0 && j == 0) { system("cls"); restartXO(); main(); }
			if (cin.fail() || i - 1 > 2 || j - 1 > 2 || boardXO[i - 1][j - 1] != "|_____|" || i - 1 < 0 || j - 1 < 0) {

				cin.clear();
				cin.ignore(10000, '\n');
				drawXO();

				cout << " Invalid Entry!! :( , Please ";
				SetConsoleTextAttribute(hConsole, 0x01);
				cout << p2.name;
				SetConsoleTextAttribute(hConsole, 0x0F);
				cout << " Try Again :) (Your ID Is 'O' ) :\n To go to menu: enter 0 0\n ";

				continue;

			}
			else break;

		}
		boardXO[i - 1][j - 1] = p2.id;

		checkkXO = checkXO(p2);

		goverXO = gameoverXO();

		drawXO();
		char choice;

		if (checkkXO) {

			cout << right << setw(40) << "Congratulations!! ";
			SetConsoleTextAttribute(hConsole, 0x01);
			cout << p2.name;
			SetConsoleTextAttribute(hConsole, 0x0F);
			cout << ", You Acheieved Three (O)s -- > You're the Winner ^_^\n" << endl;
		labelXO3: cout << right << setw(70) << " Would you like to continue Tic-Tac-Toe? (y/n)\n To go to menu: enter 0\n "; cin >> choice;
			if (choice == 'y') {
				restartXO();
				drawXO();
				continue;
			}
			else if (choice == 'n') {

				cout << endl << " Goodbye ^_^\n "; break;
			}
			else if (choice == '0') {
				system("cls"); restartXO(); main();
			}
			else {
				system("cls");
				cout << " Invalid\n"; goto labelXO3;
			}


		}

		if (goverXO) {
			cout << " None of the players has won :(\n";
		labelXO4: cout << " Would you like to restart Tic-Tac-Toe? (y/n)\n To go to menu: enter 0\n "; cin >> choice;
			if (choice == 'y') {
				restartXO();
				drawXO();
				continue;
			}
			else if (choice == 'n') {

				cout << endl << " Goodbye ^_^\n "; break;
			}
			else if (choice == '0') {
				system("cls"); restartXO(); main();
			}
			else {
				system("cls");
				cout << " Invalid\n"; goto labelXO4;
			}

		}
	}

}

bool checkXO(player activePlayerXO) {
	bool win = false;
	string ID = activePlayerXO.id;
	if (boardXO[0][0] == ID && boardXO[0][1] == ID && boardXO[0][2] == ID)
		win = true;
	if (boardXO[1][0] == ID && boardXO[1][1] == ID && boardXO[1][2] == ID)
		win = true;
	if (boardXO[2][0] == ID && boardXO[2][1] == ID && boardXO[2][2] == ID)
		win = true;
	if (boardXO[0][0] == ID && boardXO[1][0] == ID && boardXO[2][0] == ID)
		win = true;
	if (boardXO[0][1] == ID && boardXO[1][1] == ID && boardXO[2][1] == ID)
		win = true;
	if (boardXO[0][2] == ID && boardXO[1][2] == ID && boardXO[2][2] == ID)
		win = true;
	if (boardXO[0][2] == ID && boardXO[1][1] == ID && boardXO[2][0] == ID)
		win = true;
	if (boardXO[0][0] == ID && boardXO[1][1] == ID && boardXO[2][2] == ID)
		win = true;
	return win;
}

bool gameoverXO() {
	bool gover = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; ++j) {
			if (boardXO[i][j] == "|_____|") {
				gover = false;
				break;
			}
		}
		if (gover == false)
			break;
	}

	return gover;
}

void restartXO() {

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			boardXO[i][j] = "|_____|";
		}
	}

}

void file() {
	if (p1.score > p2.score) winner = p1.name;
	else if (p1.score < p2.score) winner = p2.name;
	else if (p1.score == 0 && p2.score == 0) winner = "Neither";
	else winner = "TIE";
	History << "Names\t\tScores\t\tGames\t\tWinner\t\tDate\t\t\tTime\n__________________________________________________________________________________________________\n";
	History << p1.name << "\t\t"
		<< p1.score << endl
		<< p2.name << "\t\t"
		<< p2.score << "\t\t"
		<< noOfGames << "\t\t"
		<< winner << "\t\t"
		<< (timePtr->tm_mday) << "/"
		<< (timePtr->tm_mon) + 1 << "/" << (timePtr->tm_year) + 1900 << "\t\t"
		<< (timePtr->tm_hour) << ":" << (timePtr->tm_min) << ":" << (timePtr->tm_sec) << endl
		<< "__________________________________________________________________________________________________" << endl;
}