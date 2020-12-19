typedef struct Coord {
	float x;
	float y;
} coord;

class Player {
public:
	coord poz;
	coord next;
	coord poffset;
	float vel;
	float step;
	int margin;
	int cooldown;

	Player(int x, int y, int offx, int offy, int mx) {
		poz.x = x;
		poz.y = y;
		next.x = x;
		next.y = y;
		poffset.x = offx;
		poffset.y = offy;
		margin = mx;
		step = (mx - offx) / 50;
		cooldown = 0;
		vel = 0;
	}

	float getX() {
		return poz.x;
	}

	float getY() {
		return poz.y;
	}

	void moveLeft() {
		if (poz.x > poffset.x + 1)
			next.x -= step;
	}

	void moveRight() {
		if (poz.x < margin)
			next.x += step;
	}

	void jump(bool c) {
		if (c)
			vel = 0.06;
		else if (!cooldown) {
			vel = 0.06;
			cooldown = 100;
		}
	}

	bool falling() {
		return vel < 0;
	}

	float getTrueX(){
		return poz.x - poffset.x;
	}

    float getTrueY(){
		return poz.y + 1;
	}

	void update() {
		if (cooldown)
			cooldown --;
		mvprintw(0, 25, "cooldown: %d", cooldown);
		next.y += vel;
		vel = vel - 0.0001;
		if (next.y <= 0) {
			next.y = 0;
			vel = 0;
		}
		if ((int)poz.x != (int)next.x || (int)poz.y != (int)next.y) {
			mvprintw(poffset.y - poz.y - 2, poz.x,      " ");
			mvprintw(poffset.y - poz.y - 1, poz.x - 1, "   ");
			mvprintw(poffset.y - poz.y, poz.x - 1,     "   ");
			poz.x = next.x;
			poz.y = next.y;
			mvprintw(poffset.y - poz.y - 2, poz.x,      "_");
			mvprintw(poffset.y - poz.y - 1, poz.x - 1, "/O\\");
			mvprintw(poffset.y - poz.y, poz.x - 1,     "( )");
		}
	}

};
