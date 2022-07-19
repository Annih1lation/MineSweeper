#include <iostream>
#include <ctime>
#include <Windows.h>
#include <cmath>
using namespace std;

enum objects : char {
	bomb = 'X',
	empt = '_',
	fog = '#',
	flag = '!',
};

enum colors : int {
	blue = 1,
	green = 2,
	red = 4,
	dark_blue = 5,
	brown = 6,
	light_blue = 9,
	grey = 8,
	pink = 12,
	original = 7,
};

enum game_progress {
	in_progress,
	lost,
	won
};

struct field_coord {
	short int x{ 0 };
	short int y{ 0 };
};

struct minesweeper {
	const short size_field{ 12 };
	objects** field;
	objects** fog_field;
	objects player;
	game_progress status{ in_progress };
};

void clear_field() {
	system("cls");
}

void init_game(minesweeper& ms) {
	ms.field = new objects*[ms.size_field];
	for (short i = 0; i < ms.size_field; i++)
		ms.field[i] = new objects[ms.size_field];
	
	srand(time(0));
	
	for (short int x = 0; x < ms.size_field; x++) 
		for (short int y = 0; y < ms.size_field; y++) 
			if ((rand() % 5) > 0)
				ms.field[x][y] = empt;
			else
				ms.field[x][y] = bomb;
		
	ms.fog_field = new objects * [ms.size_field];
	for (short i = 0; i < ms.size_field; i++)
		ms.fog_field[i] = new objects[ms.size_field];

	for (short int x = 0; x < ms.size_field; x++)
		for (short int y = 0; y < ms.size_field; y++)
				ms.fog_field[x][y] = fog;
}

void color(int x)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, x);
}

void print_field(const minesweeper& ms) {
	
	cout << "     ";
	for (short x = 0; x < ms.size_field; x++) {
		if (x < 9) {
			cout << x + 1 << " | ";
		}
		else {
			cout << x + 1 << "| ";
		}

	}
	cout << endl;
	
	for (short y = 0; y < ms.size_field; y++) {
		if (y < 9) {
			cout << " " << y + 1 << " | ";
		}
		else {
			cout << " " << y + 1 << "| ";
		}
		for (short x = 0; x < ms.size_field; x++) {
				if (ms.fog_field[x][y] == static_cast<objects>(49)) {
					color(blue);
					cout << ms.fog_field[x][y];
					color(original);
					cout << " | ";
				}
				else if (ms.fog_field[x][y] == static_cast<objects>(50)) {
					color(green);
					cout << ms.fog_field[x][y];
					color(original);
					cout << " | ";
				}
				else if (ms.fog_field[x][y] == static_cast<objects>(51)) {
					color(red);
					cout << ms.fog_field[x][y];
					color(original);
					cout << " | ";
				}
				else if (ms.fog_field[x][y] == static_cast<objects>(52)) {
					color(dark_blue);
					cout << ms.fog_field[x][y];
					color(original);
					cout << " | ";
				}
				else if (ms.fog_field[x][y] == static_cast<objects>(53)) {
					color(brown);
					cout << ms.fog_field[x][y]; 
					color(original);
					cout << " | ";
				}
				else if (ms.fog_field[x][y] == static_cast<objects>(54)) {
					color(light_blue);
					cout << ms.fog_field[x][y]; 
					color(original);
					cout << " | ";
				}
				else if (ms.fog_field[x][y] == static_cast<objects>(55)) {
					color(grey);
					cout << ms.fog_field[x][y];
					color(original);
					cout << " | ";
				}
				else if (ms.fog_field[x][y] == static_cast<objects>(56)) {
					color(pink);
					cout << ms.fog_field[x][y];
					color(original);
					cout << " | ";
				}
				else {
					cout << ms.fog_field[x][y] << " | ";
				}
		}				
		cout << endl;
	}
}

void print_field_clear(const minesweeper& ms) {
	cout << "     ";
	for (short x = 0; x < ms.size_field; x++) {
		if (x < 9) {
			
			cout << x + 1 << " | ";
		}
		else {
		cout << x + 1 << "| ";
		}
	
	}
	cout << endl;

	for (short y = 0; y < ms.size_field; y++) {
		if (y < 9) {
			cout << " " << y + 1 << " | ";
		}
		else {
			cout << " " << y + 1 << "| ";
		}
		for (short x = 0; x < ms.size_field; x++) {		
			if (ms.field[x][y] == static_cast<objects>(49)) {
				color(blue);
				cout << ms.field[x][y];
				color(original);
				cout << " | ";
			}
			else if (ms.field[x][y] == static_cast<objects>(50)) {
				color(green);
				cout << ms.field[x][y];
				color(original);
				cout << " | ";
			}
			else if (ms.field[x][y] == static_cast<objects>(51)) {
				color(red);
				cout << ms.field[x][y];
				color(original);
				cout << " | ";
			}
			else if (ms.field[x][y] == static_cast<objects>(52)) {
				color(dark_blue);
				cout << ms.field[x][y];
				color(original);
				cout << " | ";
			}
			else if (ms.field[x][y] == static_cast<objects>(53)) {
				color(brown);
				cout << ms.field[x][y];
				color(original);
				cout << " | ";
			}
			else if (ms.field[x][y] == static_cast<objects>(54)) {
				color(light_blue);
				cout << ms.field[x][y];
				color(original);
				cout << " | ";
			}
			else if (ms.field[x][y] == static_cast<objects>(55)) {
				color(grey);
				cout << ms.field[x][y];
				color(original);
				cout << " | ";
			}
			else if (ms.field[x][y] == static_cast<objects>(56)) {
				color(pink);
				cout << ms.field[x][y];
				color(original);
				cout << " | ";
			}
			else {
				cout << ms.field[x][y] << " | ";
			}			
		}
		cout << endl;
	}
}

void deinit_game(minesweeper& ms) {
	for (short i = 0; i < ms.size_field; i++)
		delete[] ms.field[i];

	delete[] ms.field;
	ms.field = nullptr;

	for (short i = 0; i < ms.size_field; i++)
		delete[] ms.fog_field[i];

	delete[] ms.fog_field;
	ms.fog_field = nullptr;
}

field_coord get_coord(minesweeper& ms) {
	field_coord c;
	do {
		cout << "Enter X: ";
		cin >> c.x;
		cout << "Enter Y: ";
		cin >> c.y;
		c.x--;
		c.y--;
		
	} while (c.x > ms.size_field || c.y > ms.size_field);
	return c;
}

void results(const minesweeper& ms) {
	if (ms.status == lost)
		cout << "KABOOOOM, YOU LOST";
	
	if (ms.status == won)
		cout << "You are a lucky one or just a profi";
}

bool is_safe(const short x, const short y, minesweeper& ms) {
	if ((x >= 0 && x <= ms.size_field - 1) && (y >= 0 && y <= ms.size_field - 1)) {
		return true;
	}
	else {
		return false;
	}
}

void number(minesweeper& ms) {
	for(short x = 0; x < ms.size_field; x++)
		for (short y = 0; y < ms.size_field; y++) {
			if (ms.field[x][y] == bomb) continue;
			short n = 0;
			for (short g = y-1; g <= y+1; g++) {
				if (is_safe(x - 1, g, ms) && ms.field[x-1][g] == bomb) n++;
				if (ms.field[x][g] == bomb) n++;
				if (is_safe(x+1, g, ms) && ms.field[x + 1][g] == bomb) n++;
				if (n == 0) continue;
				ms.field[x][y] = static_cast<objects>(n + 48);
			}
			
		}
}

void emptiness(int x, int y, minesweeper& ms){
	if ((x >= 0) && (x < ms.size_field)){
		if ((x >= 0) && (y < ms.size_field)){
			if (ms.fog_field[x][y] == fog && ms.field[x][y] == empt) {
				ms.fog_field[x][y] = ms.field[x][y];
				for (short g = y - 1; g <= y + 1; g++) {
					if (is_safe(x, g, ms)) emptiness(x, g, ms);
					if (is_safe(x - 1, g, ms)) emptiness(x - 1, g, ms);
					if (is_safe(x + 1, g, ms)) emptiness(x + 1, g, ms);
				}
			}
			for (short n = 1; n <= 3; n++) {
				if (ms.field[x][y] == static_cast <objects>(n + 48)) ms.fog_field[x][y] = ms.field[x][y];
			}
		}
	}
}

game_progress check_win(minesweeper& ms,int x, int y) {
	if (ms.fog_field[x][y] == bomb)	return lost;
	
	short n = 0;
	for (short x = 0; x < ms.size_field; x++) {
		for (short y = 0; y < ms.size_field; y++) {
			if (ms.fog_field[x][y] == fog) {
				return in_progress;
			}
			else if(ms.fog_field[x][y] != fog) {
				n++;
			}		
		}
	}
	if (n == pow(ms.size_field, 2)) {
		return won;
	}
}

void number_has_chosen(minesweeper& ms, int x, int y) {
	short n = 0;
	short check = 0;
	
	for (short g = y - 1; g <= y + 1; g++) {
		if (is_safe(x - 1, g, ms) && (ms.field[x - 1][g] == bomb && ms.fog_field[x-1][g] == flag)) n++;
		if (ms.field[x][g] == bomb && ms.fog_field[x][g] == flag) n++;
		if (is_safe(x + 1, g, ms) && (ms.field[x + 1][g] == bomb && ms.fog_field[x+1][g] == flag)) n++;
		if (n == 0) continue;
		check = static_cast<objects>(n + 48);
	}
	if (check == ms.field[x][y] && ms.fog_field[x][y] != fog) {
		for (short g = y - 1; g <= y + 1; g++) {
			if (is_safe(x, g, ms) && ms.field[x][g] != bomb) {
				if (ms.field[x][g] == empt) {
					emptiness(x, g, ms);
				}
				else {
					ms.fog_field[x][g] = ms.field[x][g];
				}				
			}
			if (is_safe(x - 1, g, ms) && ms.field[x - 1][g] != bomb) {
				if (ms.field[x - 1][g] == empt) {
					emptiness(x-1, g, ms);
				}
				else {
					ms.fog_field[x - 1][g] = ms.field[x - 1][g];
				}
			}
			if (is_safe(x + 1, g, ms) && ms.field[x + 1][g] != bomb) {
				if (ms.field[x + 1][g] == empt) {
					emptiness(x+1, g, ms);
				}
				else {
					ms.fog_field[x + 1][g] = ms.field[x + 1][g];
				}
			}
		}
	}
}

int main(void) {
	minesweeper ms;
	init_game(ms);
	number(ms);
	print_field(ms);
	ms.status = in_progress;
	do {
		field_coord c = get_coord(ms);
		short action = 0;
		cout << "1 - open cell" << endl << "2 - put the flag\n";
		cin >> action;
		switch (action) {
		case 2:
			if (ms.fog_field[c.x][c.y] != flag || ms.fog_field[c.x][c.y] != fog) break;
			if (ms.fog_field[c.x][c.y] == flag) {
				ms.fog_field[c.x][c.y] = fog;
				break;
			}
			ms.fog_field[c.x][c.y] = flag;
			break;
		case 1:
			if (ms.fog_field[c.x][c.y] == flag) {
				ms.fog_field[c.x][c.y] = fog;
				break;
			}
			if (ms.field[c.x][c.y] == bomb) {
				ms.fog_field[c.x][c.y] = ms.field[c.x][c.y];
				break;
			}
			if (ms.field[c.x][c.y] == empt) {
				emptiness(c.x, c.y, ms);	
				break;
			}
			if (ms.field[c.x][c.y] != bomb && ms.field[c.x][c.y] != empt) {
				for (short k = 1; k <= 9; k++) {
					if (ms.fog_field[c.x][c.y] == static_cast<objects>(k + 48)) {
						number_has_chosen(ms, c.x, c.y);
					}
						ms.fog_field[c.x][c.y] = ms.field[c.x][c.y];				
				}	
				break;
			}
		}
			ms.status = check_win(ms, c.x, c.y);
			clear_field();
			if (ms.status == in_progress) {
				print_field(ms);
			}
			else {
				print_field_clear(ms);
			}
		} while (ms.status == in_progress);
		deinit_game(ms);
		results(ms);
}