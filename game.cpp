#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "map.h"
#include "player.h"

#define WALL 1
#define PLAYER 2
#define PLAT 3
#define DEST 4

void gameOver(int consoleHeight, int consoleWidth, int score) {
	clear();
	system("xset r rate");
		
	attron(COLOR_PAIR(WALL));
	mvprintw(consoleHeight / 2 - 1, consoleWidth / 2 - 9, "GAME OVER");
	mvprintw(consoleHeight / 2 + 1, consoleWidth / 2 - 10, "Score: %d", score);
	attroff(COLOR_PAIR(WALL));

	std::ifstream highscore("score");
	std::string line;
	getline(highscore, line);
	int oldscore = atoi(line.c_str());
	highscore.close();
	if (score > oldscore) {
		std::ofstream highscore("score");
		highscore << std::to_string(score);
		highscore.close();
	}

	move(consoleHeight - 1, consoleWidth - 1);
	timeout(-1);
	getch();
}

void game(int consoleHeight, int consoleWidth, int diff)
{
	nodelay(stdscr, true);
	timeout(1);
	int mapHeight, mapWidth, mapHeightOffset, mapWidthOffset;
	mapHeightOffset = 2;
	mapWidthOffset = 10;
	mapHeight = consoleHeight - 2 * mapHeightOffset;
	mapWidth = consoleWidth - 2 * mapWidthOffset;

	attron(COLOR_PAIR(WALL));
	for (int i = mapHeightOffset; i < mapHeight + mapHeightOffset; i++)	{
		mvprintw(i, mapWidthOffset - 2, "||");	
		mvprintw(i, mapWidth + mapWidthOffset + 2, "||");	
		mvprintw(consoleHeight - 1, consoleWidth - 1, "_");
	}
	attroff(COLOR_PAIR(WALL));

	Player p(mapWidth/2, 0, mapWidthOffset, mapHeight + mapHeightOffset, 
			 mapWidth, mapHeight);
	Map m(mapHeight, mapWidth, mapHeightOffset, mapWidthOffset, diff);
	int score = 0;
	int scoremult = 2000 / (consoleHeight + 10) / (diff + 3) ;

	system("xset r rate 10 40");
	char c;
	while(1) {
		attron(COLOR_PAIR(WALL));
		mvprintw(0, 0, "Score: %d         ", score);
		attroff(COLOR_PAIR(WALL));
		move(consoleHeight - 1, consoleWidth - 1);
		c = getch();
		switch(c) {
		case 'a':
			p.moveLeft();
			break;
		case 'D':
			p.moveLeft();
			break;
		case 'd':
			p.moveRight();
			break;
		case 'C':
			p.moveRight();
			break;
		case 'w':
			p.jump(false);
			break;
		case 'A':
			p.jump(false);
			break;
		}

		if (p.falling() && m.colision(p.getX(), p.getY()))
			p.jump(true);

		if (p.upscroll()) {
			m.clear();
			m.upscroll();
			score += scoremult;
		}

		if (!p.update())
			break;
		m.update();
		move(consoleHeight - 1, consoleWidth - 1);
		refresh();
		sleep(0.2);
	}
	gameOver(consoleHeight, consoleWidth, score);
}


int main()
{
	initscr();
	int consoleHeight, consoleWidth, difficulty = 20;
	getmaxyx(stdscr, consoleHeight, consoleWidth);

	srand(time(NULL));
	start_color();
	use_default_colors();
	init_pair(PLAYER, COLOR_MAGENTA, -1);
	init_pair(WALL, COLOR_RED, -1);
	init_pair(PLAT, COLOR_GREEN, -1);
	init_pair(DEST, COLOR_YELLOW, -1);

	int choice = 0;

	while(1) {
		clear();
		
		attron(COLOR_PAIR(PLAYER));
		mvprintw(4 + 3 * choice, 5,  "_");
		mvprintw(5 + 3 * choice, 4, "/O\\");
		mvprintw(6 + 3 * choice, 4, "( )");
		attroff(COLOR_PAIR(PLAYER));
		
		attron(COLOR_PAIR(PLAT));
		mvprintw(2, consoleWidth/2 - 5, "AsciiJump");
		mvprintw(5, 10, "Play game");
		mvprintw(8, 10, "Set difficulty");
		mvprintw(11, 10, "Exit");
		attroff(COLOR_PAIR(PLAT));

		attron(COLOR_PAIR(WALL));
		mvprintw(consoleHeight - 1, 0, 
				 "Console: %dx%d", consoleHeight, consoleHeight);

		std::ifstream highscore("score");
		std::string line;
		getline(highscore, line);
		int score = atoi(line.c_str());
		highscore.close();

		mvprintw(consoleHeight - 1, consoleWidth - 22, "Highscore: %d", score);
		move(consoleHeight - 1, consoleWidth - 1);

		refresh();
		char c;
		c = getch();
		if ((c == 's' || c == 'B') && choice < 2) {
			choice ++;
		}
		if ((c == 'w' || c == 'A') && choice > 0) {
			choice --;
		}
		if (c == (char)10 || c == 'q') {
			if (choice == 2) {
				endwin();
				return 0;
			}
			if (choice == 1) {
				char d;
				mvprintw(8, 25, "e: Easy");
				mvprintw(9, 25, "m: Medium");
				mvprintw(10, 25, "h: Hard");
				move(consoleHeight - 1, consoleWidth - 1);
				refresh();
				d = getch();
				switch(d) {
					case 'e':
						difficulty = 20;
						break;
					case 'm':
						difficulty = 12;
						break;
					case 'h':
						difficulty = 8;
						break;
				}
			}
			if (choice == 0) {
				clear();
				game(consoleHeight, consoleWidth, difficulty);
			}
		}
		attroff(COLOR_PAIR(WALL));
	}
}	
