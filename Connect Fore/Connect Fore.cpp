#include<iostream>

using namespace std;

char grid[20][20] = {};
char confirm;
int col = 0;
int rowNum = 6;
int colNum = 7;
int winNum = 4;
bool gameover = false;
bool currentPlayer = false;
bool gameloop = true;
bool isWarpMode;
bool isDropMode;
bool isVSCom;

void Init();
void UpdateGrid();
void WinJudge(int r, int c);
void Insert();
void Replay();
void DrawCheck();
void CustomRule(); 
bool IntInputCheck(int num, int min, int max);

int main() {
	while (gameloop) {
		CustomRule();
		Init();
		while (!gameover) {
			Insert();
		}
		//cout << "Player" << currentPlayer + 1 << " win!\n";
		Replay();
	}
	return 0;
}



void Init() {
	system("CLS");
	gameover = false;
	currentPlayer = false;
	for (int i = 0; i < colNum; i++) {
		if (i >= 9) {
			cout << i + 1 << " ";
		}
		else cout << i + 1 << "  ";
	}
	cout << "\n\n";
	for (int i = 0; i < rowNum; i++) {
		for (int j = 0; j < colNum; j++) {
			grid[i][j] = '.';
			cout << grid[i][j] << "  ";
		}
		cout << "\n\n";
	}
}

void UpdateGrid() {
	system("CLS");
	for (int i = 0; i < colNum; i++) {
		if (i >= 9) {
			cout << i + 1 << " ";
		}
		else cout << i + 1 << "  ";
	}
	cout << "\n\n";
	for (int i = 0; i < rowNum; i++) {
		for (int j = 0; j < colNum; j++) {
			cout << grid[i][j] << "  ";
		}
		cout << "\n\n";
	}
}

void WinJudge(int r, int c) {
	int combo = 1;
	int currentR = r;
	int currentC = c;

	while (true) { //judge vertical
		r++;
		if (grid[currentR][currentC] == grid[r][currentC] && r < rowNum) {
			combo++;
		}
		else {
			if (combo >= winNum) {
				cout << "Player" << currentPlayer + 1 << " win!\n";
				gameover = true;
			}
			r = currentR;
			combo = 1;
			break;
		}
	}

	while (true) { //judge horizontal left
		c--;
		if (grid[currentR][currentC] == grid[currentR][c] && c >= 0) {
			combo++;
		}
		else {
			c = currentC;
			break;
		}
	}
	while (true) { //judge horizontal right
		c++;
		if (grid[currentR][currentC] == grid[currentR][c] && c < colNum) {
			combo++;
		}
		else {
			c = currentC;
			if (combo >= winNum) {
				cout << "Player" << currentPlayer + 1 << " win!\n";
				gameover = true;
			}
			combo = 1;
			break;
		}
	}

	while (true) { //judge diagonal1 lower left 
		c--;
		r++;
		if (grid[currentR][currentC] == grid[r][c] && c >= 0 && r < rowNum) {
			combo++;
		}
		else {
			c = currentC;
			r = currentR;
			break;
		}
	}
	while (true) { //judge diagonal1 upper right
		c++;
		r--;
		if (grid[currentR][currentC] == grid[r][c] && c < colNum && r >= 0) {
			combo++;
		}
		else {
			if (combo >= winNum) {
				cout << "Player" << currentPlayer + 1 << " win!\n";
				gameover = true;
			}
			c = currentC;
			r = currentR;
			combo = 1;
			break;
		}
	}

	while (true) { //judge diagonal2 upper left 
		c--;
		r--;
		if (grid[currentR][currentC] == grid[r][c] && c >= 0 && r >= 0) {
			combo++;
		}
		else {
			c = currentC;
			r = currentR;
			break;
		}
	}
	while (true) { //judge diagonal2 lower right
		c++;
		r++;
		if (grid[currentR][currentC] == grid[r][c] && c < colNum && r < rowNum) {
			combo++;
		}
		else {
			if (combo >= winNum) {
				cout << "Player" << currentPlayer + 1 << " win!\n";
				gameover = true;
			}
			c = currentC;
			r = currentR;
			combo = 1;
			break;
		}
	}
}

void DrawCheck() {
	for (int i = 0; i < 7; i++) { //check 1st row only
		if (grid[0][i] == '.') {
			return;
		}
	}
	cout << "Draw!\n";
	gameover = true;
}

void Insert() {
	cout << "Player" << currentPlayer + 1 << "'s turn!\n";
	cout << "Input column number:";
	cin >> col;
	if (!IntInputCheck(col, 1, colNum)) return;
	col--;
	for (int i = rowNum-1; i >= 0; i--) {
		if (grid[i][col] == '.') {
			if (currentPlayer) {
				grid[i][col] = 'X';
				UpdateGrid();
				WinJudge(i, col);
				DrawCheck();
				break;
			}
			else {
				grid[i][col] = 'O';
				UpdateGrid();
				WinJudge(i, col);
				DrawCheck();
				break;
			}
		}
		else if (i == 0) {
			currentPlayer = !currentPlayer;
			cout << "Column is full, choose another one\n";
		}
	}
	currentPlayer = !currentPlayer;
}

void Replay() {
	while (true) {
		cout << "Play again? Input Y/N";
		cin >> confirm;
		if (confirm == 'Y' || confirm == 'y') {
			break;
		}
		else if (confirm == 'N' || confirm == 'n') {
			gameloop = false;
			break;
		}
	}
}

void CustomRule() {
	while (true) {
		cout << "Reset grid and win required? Input Y/N";
		cin >> confirm;
		if (confirm == 'Y' || confirm == 'y') {
			while (true) {
				cout << "Input row number(4~20):";
				cin >> rowNum;
				if (!IntInputCheck(rowNum, 4, 20)) {
					continue;
				}
				else break;
			}
			while (true) {
				cout << "Input colunm number(4~20):";
				cin >> colNum;
				if (!IntInputCheck(colNum, 4, 20)) {
					continue;
				}
				else break;
			}
			while (true) {
				cout << "Input number required to win(3~20):";
				cin >> winNum;
				if (!IntInputCheck(winNum, 3, 20)) {
					continue;
				}
				else break;
			}
			return;
		}
		else if (confirm == 'N' || confirm == 'n') {
			return;
		}
	}
}

bool IntInputCheck(int num, int min, int max) {
	if (cin.fail()) { //check input
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Please input number!\n";
		return false;
	}
	else if (num<min || num>max) {
		cout << "Invalid number!\n";
		return false;
	}
	else return true;
}