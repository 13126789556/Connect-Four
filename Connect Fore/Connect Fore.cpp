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
bool isRemoveMode;
bool isVSCom;

void Init();
void UpdateGrid();
bool WinJudge(int r, int c);
void Insert();
void Remove(float col);
bool DrawCheck();
void CustomRule();
bool InputCheck(int num, int min, int max);
bool Confirm();

int main() {
	while (gameloop) {
		CustomRule();
		cout << "Activate warp mode?";
		isWarpMode = Confirm();
		cout << "Activate remove mode?";
		isRemoveMode = Confirm();
		Init();
		while (!gameover) {
			cout << "Player" << currentPlayer + 1 << "'s turn!\n";
			Insert();
		}
		//cout << "Player" << currentPlayer + 1 << " win!\n";
		cout << "Play again?";
		if (!Confirm()) gameloop = false;
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

bool WinJudge(int r, int c) {
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
				return true;
			}
			r = currentR;
			combo = 1;
			break;
		}
	}

	while (true) { //judge horizontal left
		c--;
		if (isWarpMode && c < 0) {
			c += colNum;
		}
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
		if (isWarpMode && c >= colNum) {
			c -= colNum;
		}
		if (grid[currentR][currentC] == grid[currentR][c] && c < colNum) {
			combo++;
		}
		else {
			c = currentC;
			if (combo >= winNum) {
				return true;
			}
			combo = 1;
			break;
		}
	}

	while (true) { //judge diagonal1 lower left 
		c--;
		r++;
		if (isWarpMode && c < 0) {
			c += colNum;
		}
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
		if (isWarpMode && c >= colNum) {
			c -= colNum;
		}
		if (grid[currentR][currentC] == grid[r][c] && c < colNum && r >= 0) {
			combo++;
		}
		else {
			if (combo >= winNum) {
				return true;
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
		if (isWarpMode && c < 0) {
			c += colNum;
		}
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
		if (isWarpMode && c >= colNum) {
			c -= colNum;
		}
		if (grid[currentR][currentC] == grid[r][c] && c < colNum && r < rowNum) {
			combo++;
		}
		else {
			if (combo >= winNum) {
				return true;
			}
			c = currentC;
			r = currentR;
			combo = 1;
			break;
		}
	}
	return false;
}

bool DrawCheck() {
	for (int i = 0; i < 7; i++) { //check 1st row only
		if (grid[0][i] == '.') {
			return false;
		}
	}
	cout << "Draw!\n";
	return true;
}

void Insert() {
	cout << "Input column number:";
	cin >> col;
	if (!InputCheck(col, 1, colNum)) return;
	col--;
	for (int i = rowNum-1; i >= 0; i--) {
		if (grid[i][col] == '.') {
			if (currentPlayer) {
				grid[i][col] = 'X';
				UpdateGrid();
				if (DrawCheck()) {
					gameover = true;
				}
				if (WinJudge(i, col)) {
					cout << "Player" << currentPlayer + 1 << " win!\n";
					gameover = true;
				}
				break;
			}
			else {
				grid[i][col] = 'O';
				UpdateGrid();
				if (DrawCheck()) {
					gameover = true;
				}
				if (WinJudge(i, col)) {
					cout << "Player" << currentPlayer + 1 << " win!\n";
					gameover = true;
				}
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

void Remove(float num) {

}

void CustomRule() {
	while (true) {
		cout << "Reset grid and win condition?";
		if (Confirm()) {
			while (true) {
				cout << "Input row number(4~20):";
				cin >> rowNum;
				if (!InputCheck(rowNum, 4, 20)) {
					continue;
				}
				else break;
			}
			while (true) {
				cout << "Input colunm number(4~20):";
				cin >> colNum;
				if (!InputCheck(colNum, 4, 20)) {
					continue;
				}
				else break;
			}
			while (true) {
				cout << "Input number required to win(3~20):";
				cin >> winNum;
				if (!InputCheck(winNum, 3, 20)) {
					continue;
				}
				else break;
			}
			return;
		}
		else return;
	}
}

bool InputCheck(int num, int min, int max) {
	if (cin.fail()) {
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

bool Confirm() {
	char input;
	while (true) {
		cout << " Please input Y/N";
		cin >> input;
		if (input == 'Y' || input == 'y') {
			return true;
		}
		else if (input == 'N' || input == 'n') {
			return false;
		}
		else {
			cout << "Invalid input!";
			continue;
		}
	}
}