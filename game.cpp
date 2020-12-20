#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define WALL 1
#define PLAYER 2
#define PLAT 3
#define DEST 4

void gameOver(int consoleHeight, int consoleWidth) {
	erase();
	system("xset r rate");
	mvprintw(consoleHeight / 2, consoleWidth / 2 - 9, "GAME OVER");
	move(consoleHeight - 1, consoleWidth - 1);
	timeout(-1);
	getch();
}

void game(int consoleHeight, int consoleWidth, int diff)
{
	nodelay(stdscr, true);
	timeout(1);
	int mapHeight, mapWidth, mapHeightOffset, mapWidthOffset;
	mapHeightOffset = 3;
	mapWidthOffset = 10;
	mapHeight = consoleHeight - 2 * mapHeightOffset;
	mapWidth = consoleWidth - 2 * mapWidthOffset;

	start_color();
	use_default_colors();
	init_pair(PLAYER, COLOR_MAGENTA, -1);
	init_pair(WALL, COLOR_RED, -1);
	init_pair(PLAT, COLOR_GREEN, -1);
	init_pair(DEST, COLOR_YELLOW, -1);

	attron(COLOR_PAIR(WALL));
	for (int i = mapHeightOffset; i < mapHeight + mapHeightOffset; i++)	{
		mvprintw(i, mapWidthOffset - 2, "||");	
		mvprintw(i, mapWidth + mapWidthOffset + 2, "||");	
		mvprintw(consoleHeight - 1, consoleWidth - 1, "_");
	}
	attroff(COLOR_PAIR(WALL));

	srand(time(NULL));
	Player p(mapWidth/2, 0, mapWidthOffset, mapHeight + mapHeightOffset, 
			 mapWidthOffset + mapWidth, mapHeight);
	Map m(mapHeight, mapWidth, mapHeightOffset, mapWidthOffset, diff);
	int score;

	system("xset r rate 10 40");
	char c;
	while(1) {
		mvprintw(0, 0, "Score: ", score);
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
			p.jump(false);
			break;
		}

		if (m.colision(p.getX(), p.getY()) && p.falling())
			p.jump(true);

		if (p.upscroll()) {
			m.clear();
			m.upscroll();
		}

		if (!p.update())
			break;
		m.update();
		move(consoleHeight - 1, consoleWidth - 1);
		refresh();
		sleep(0.2);
	}
	gameOver(consoleHeight, consoleWidth);
}
