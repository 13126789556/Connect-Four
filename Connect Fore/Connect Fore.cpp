#include<iostream>
//#include<string>

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
bool isWarpMode = false;
bool isRemoveMode = false;
bool isVSCom = false;

void Init();
void UpdateGrid();
bool WinJudge(int r, int c);
void Insert();
void Remove();
bool DrawCheck();
void CustomRule();
bool InputCheck(int num, int min, int max);
int InputInt(int min, int max);
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
			if (isRemoveMode) {
				cout << "Remove a piece?";
				if (Confirm()) {
					cout << "Input column number to remove piece: ";
					Remove();
				}
			}
			cout << "Select column to insert piece. ";
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
	col = InputInt(1, colNum);
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

void Remove() {
	col = InputInt(1, colNum);
	col--;
	if (currentPlayer && grid[rowNum][col] == 'O') { //check if piece can be removed
		for (int i = rowNum; i >= 0; i--) {
			grid[i][col] = grid[i - 1][col];
		}
	}
	else if (grid[rowNum][col] == 'X') {
		for (int i = rowNum; i >= 0; i--) {
			grid[i][col] = grid[i - 1][col];
		}
	}
	else {
		currentPlayer = !currentPlayer;
		cout << "You can only choose the column whit your piece in bottom.\n";
	}
	currentPlayer = !currentPlayer;
}

void CustomRule() {
	while (true) {
		cout << "Reset grid and win condition?";
		if (Confirm()) {
			cout << "Set row number.";
			rowNum = InputInt(4, 20);
			cout << "Set column number.";
			colNum = InputInt(4, 20);
			cout << "Set number required to win.";
			winNum = InputInt(3, 20);
			return;
		}
		else return;
	}
}

int InputInt(int min, int max) {
	while (true) {
		char input[20];
		cout << "Please input an integer between " << min << " and " << max << ":";
		cin >> input;
		int num;
		if (input[0] >= '0' && input[0] <= '9' && input[1] == NULL) {
			num = input[0] - 48;
			if (num >= min && num <= max) {
				return num;
			}
		}
		else if (input[0] >= '0' && input[0] <= '9' && input[1] >= '0' && input[1] <= '9' && input[2] == NULL) {
			num = (input[0] - 48) * 10 + input[1] - 48;
			if (num >= min && num <= max) {
				return num;
			}
		}
		else {
			cout << "Invalid input!";
			continue;
		}
	}
}

bool Confirm() {
	while (true) {
		char input[20];
		cout << " Please input Y/N";
		cin >> input;
		if (input[0] == 'Y' || input[0] == 'y' && input[1] == NULL) {
			return true;
		}
		else if (input[0] == 'N' || input[0] == 'n' && input[1] == NULL) {
			return false;
		}
		else {
			cout << "Invalid input!";
			continue;
		}
	}
}