#include <curses.h>
#include "player.h"
#include "map.h"
#include "game.cpp"
#include <time.h>
#include <stdlib.h>

int main()
{
	//system("./set.sh");
	initscr();
	int consoleHeight, consoleWidth;
	getmaxyx(stdscr, consoleHeight, consoleWidth);
	printw("Console size: %dx%d", consoleHeight, consoleWidth);
	refresh();
	getch();

	game(consoleHeight, consoleWidth);
	refresh();
	getch();
	endwin();
	//system("./unset.sh");
	return 0;
}	
