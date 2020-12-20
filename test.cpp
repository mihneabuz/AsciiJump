#include <curses.h>
#include "player.h"
#include "map.h"
#include "game.cpp"
#include <time.h>
#include <stdlib.h>

int main()
{
	initscr();
	int consoleHeight, consoleWidth;
	getmaxyx(stdscr, consoleHeight, consoleWidth);
	game(consoleHeight, consoleWidth, 30);
	refresh();
	getch();
	endwin();
	return 0;
}	
