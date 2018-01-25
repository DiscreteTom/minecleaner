#include <iostream>
#include <conio.h>
#include "map.h"

using namespace std;

enum SIGNAL{START, SET, EXIT};

SIGNAL start();
void set(int & height, int & width, int & bomb);

int main() {
	SIGNAL sig = start();
	int height, width, bomb;
	while (sig != EXIT){
		if (sig == SET){
			set(height, width, bomb);
		} else {
			height = width = bomb = 10;
		}

		Map map = Map(width, height, bomb);
		bool died = 0;

		while (!map.win() && !died){
			system("cls");
			map.show();
			cout << "\nPress WASD to move\n"
			     << "Press J to open a block\n"
					 << "Press K to set a flag\n";
			char x = getch();
			switch (x){
				case 'W':
				case 'w':
					map.move(UP);
					break;
				case 'A':
				case 'a':
					map.move(LEFT);
					break;
				case 'S':
				case 's':
					map.move(DOWN);
					break;
				case 'D':
				case 'd':
					map.move(RIGHT);
					break;
				case 'J':
				case 'j':
					if (!map.open()){
						died = 1;
					}
					break;
				case 'K':
				case 'k':
					map.setFlag();
					break;
			}
		}

		map.showAll();
		if (died){
			cout << "YOU DIED!!!\n";
		} else {
			cout << "YOU WIN !!!\n";
		}

		system("pause");
		sig = start();
	}
	return 0;
}
SIGNAL start(){
	char x = 0;
	while (x != 'j' && x != 'J' && x != 'k' && x != 'K' && x != 'l' && x != 'L'){
		system("cls");
		cout << "*****************************\n"
				<< "        MINE CLEANER\n"
				<< "\n"
				<< "      PRESS J TO START\n"
				<< "      PRESS K TO SET MAP\n"
				<< "      PRESS L TO EXIT\n"
				<< "*****************************\n";
		x = getch();
	}
	if (x == 'j' || x == 'J'){
		return START;
	} else if (x == 'k' || x == 'K'){
		return SET;
	} else {
		return EXIT;
	}
}
void set(int & height, int & width, int & bomb){
	height = width = bomb = 0;
	while (!height){
		system("cls");
		cout << "Please input the height of your map\n";
		cin.sync();
		cin.clear();
		cin >> height;
		if (height < 5 || height > 30){
			height = 0;
		}
	}
	while (!width){
		system("cls");
		cout << "Please input the width of your map\n";
		cin.sync();
		cin.clear();
		cin >> width;
		if (width < 5 || width > 30){
			width = 0;
		}
	}
	while (!bomb){
		system("cls");
		cout << "Please input the bomb number of your map\n";
		cin.sync();
		cin.clear();
		cin >> bomb;
		if (bomb < 10 || bomb > height * width - 10){
			bomb = 0;
		}
	}
}