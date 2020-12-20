#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define WALL 1
#define PLAYER 2
#define PLAT 3
#define DEST 4

void gameOver(int consoleHeight, int consoleWidth, int score) {
	erase();
	system("xset r rate");
	mvprintw(consoleHeight / 2 - 1, consoleWidth / 2 - 9, "GAME OVER");
	mvprintw(consoleHeight / 2 + 1, consoleWidth / 2 - 10, "Score: %d", score);
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
			 /*mapWidthOffset +*/ mapWidth, mapHeight);
	Map m(mapHeight, mapWidth, mapHeightOffset, mapWidthOffset, diff);
	int score = 0;
	int scoremult = 10000 / (consoleHeight + 10) / diff;

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
		case 'd':
			p.moveRight();
			break;
		case 'w':
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
