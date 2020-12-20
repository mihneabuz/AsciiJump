#define PLAYER 2

typedef struct Coord {
	float x;
	float y;
} coord;

class Player {
public:
	coord poz;
	coord next;
	coord poffset;
	coord margin;
	float vel;
	float step;
	int cooldown;
	int jumps;
	bool started;

	Player(int x, int y, int offx, int offy, int mx, int my) {
		poz.x = x;
		poz.y = y;
		next.x = x;
		next.y = y + 1;
		poffset.x = offx;
		poffset.y = offy;
		margin.x = mx;
		margin.y = my;
		step = (mx - offx) / 60;
		vel = 0;
		cooldown = 0;
		jumps = 4;
		started = 0;
	}

	float getX() {
		return poz.x;
	}

	float getY() {
		return poz.y;
	}

	void moveLeft() {
		if (poz.x > 1)
			next.x -= step;
	}

	void moveRight() {
		if (poz.x < margin.x)
			next.x += step;
	}

	void jump(bool no_check) {
		if (no_check)
			vel = 0.06;
		else if (!cooldown && jumps) {
			vel = 0.06;
			cooldown = 100;
			jumps--;
			started = true;
		}
	}

	bool falling() {
		return vel < 0;
	}

	int upscroll() {
		if (next.y > margin.y / 2) {
			next.y -= 0.7;
			return 1;
		}
		return 0;
	}

	int update() {
		attron(COLOR_PAIR(PLAYER));
		if (cooldown)
			cooldown --;
		mvprintw(0, margin.x + poffset.x - 17, "Jump remaining: %d", jumps);
		next.y += vel;
		if (started) {
			vel = vel - 0.00008;
			if (next.y <= 0)
				return 0;
		}

		if ((int)poz.x != (int)next.x || (int)poz.y != (int)next.y) {
			mvprintw(poffset.y - poz.y - 2, poz.x + poffset.x,      " ");
			mvprintw(poffset.y - poz.y - 1, poz.x + poffset.x- 1,  "   ");
			mvprintw(poffset.y - poz.y, poz.x + poffset.x- 1,      "   ");
			poz.x = next.x;
			poz.y = next.y;
			mvprintw(poffset.y - poz.y - 2, poz.x + poffset.x,      "_");
			mvprintw(poffset.y - poz.y - 1, poz.x + poffset.x- 1,  "/O\\");
			mvprintw(poffset.y - poz.y, poz.x + poffset.x- 1,      "( )");
		}
		attroff(COLOR_PAIR(PLAYER));
		return 1;
	}
};
