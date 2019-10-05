#include<iostream>

using namespace std;

char grid[6][7] = {};
char confirm;
int col = 0;
bool gameover = false;
bool currentPlayer = false;
bool gameloop = true;

void Init();
void UpdateGrid();
void WinJudge(int r, int c);
void Insert();
void Replay();
void DrawCheck();

int main() {
	while (gameloop) {
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
	for (int i = 0; i < 7; i++) {
		cout << i + 1 << " ";
	}
	cout << "\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			grid[i][j] = '.';
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}

void UpdateGrid() {
	system("CLS");
	for (int i = 0; i < 7; i++) {
		cout << i + 1 << " ";
	}
	cout << "\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}

void WinJudge(int r, int c) {
	int combo = 1;
	int currentR = r;
	int currentC = c;

	while (true) { //judge vertical
		r++;
		if (grid[currentR][currentC] == grid[r][currentC] && r < 6) {
			combo++;
		}
		else {
			if (combo == 4) {
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
		if (grid[currentR][currentC] == grid[currentR][c] && c < 7) {
			combo++;
		}
		else {
			c = currentC;
			if (combo >= 4) {
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
		if (grid[currentR][currentC] == grid[r][c] && c >= 0 && r < 6) {
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
		if (grid[currentR][currentC] == grid[r][c] && c < 7 && r >= 0) {
			combo++;
		}
		else {
			if (combo >= 4) {
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
		if (grid[currentR][currentC] == grid[r][c] && c < 7 && r < 6) {
			combo++;
		}
		else {
			if (combo >= 4) {
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

void Insert() {
	cout << "Player" << currentPlayer + 1 << "'s turn!\n";
	cout << "Input column number:";
	cin >> col;
	if (cin.fail()) { //check input
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Please input number!\n";
		return;
	}
	if (col < 1 || col > 7) {
		cout << "Invalid number!\n";
		return;
	}
	col--;
	for (int i = 5; i >= 0; i--) {
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

void DrawCheck() {
	for (int i = 0; i < 7; i++) {
		if (grid[0][i] == '.') {
			return;
		}
	}
	cout << "Draw!\n";
	gameover = true;
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