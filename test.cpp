#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <string.h>
#include "player.h"
#include "map.h"

void game(int consoleHeight, int consoleWidth)
{
	nodelay(stdscr, true);
	timeout(1);
	int mapHeight, mapWidth, mapHeightOffset, mapWidthOffset;
	mapHeightOffset = 3;
	mapWidthOffset = 10;
	mapHeight = consoleHeight - 2 * mapHeightOffset;
	mapWidth = consoleWidth - 2 * mapWidthOffset;

	for (int i = mapHeightOffset; i < mapHeight + mapHeightOffset; i++)	{
		mvprintw(i, mapWidthOffset - 2, "||");	
		mvprintw(i, mapWidth + mapWidthOffset + 2, "||");	
		mvprintw(consoleHeight - 1, consoleWidth - 1, "_");
	}


	Player p(mapWidth/2 + mapWidthOffset, 0, mapWidthOffset, 
			 mapHeight + mapHeightOffset, mapWidthOffset + mapWidth);
	Map m(mapHeight, mapWidth, mapHeightOffset, mapWidthOffset);

	char c;
	while(1) {
		mvprintw(0, 0, "%f %f", p.getX(), p.getY());
		move(consoleHeight - 1, consoleWidth - 1);
		c = getch();
		switch(c) {
		case 'a':
			p.moveLeft();
			break;
		case 'd':
			p.moveRight();
			break;
		case 'w':
			p.jump();
			break;
		case 's':
			return;
		}
		p.update();
		move(consoleHeight - 1, consoleWidth - 1);
		refresh();
		sleep(0.2);
	}


}

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
