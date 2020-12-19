class Player {
public:
	float x_poz;
	float y_poz;
	float x_next;
	float y_next;
	float vel;
	int margin;
	int offset_y;
	int offset_x;
	int cooldown;

	Player(int x, int y, int offx, int offy, int m) {
		x_poz = x;
		y_poz = y;
		x_next = x;
		y_next = y;
		offset_y = offy;
		offset_x = offx;
		margin = m;
		cooldown = 0;
		vel = 0;
	}

	float getX() {
		return x_poz;
	}

	float getY() {
		return y_poz;
	}

	void moveLeft() {
		if (x_poz > offset_x + 2)
			x_next -= 0.6;
	}

	void moveRight() {
		if (x_poz < margin)
			x_next += 0.6;
	}

	void jump() {
		if (!cooldown)
			vel = 0.06;
		cooldown = 100;
	}

	void update() {
		if (cooldown)
			cooldown --;
		mvprintw(0, 25, "cooldown: %d", cooldown);
		y_next += vel;
		vel = vel - 0.0001;
		if (y_next <= 0) {
			y_next = 0;
			vel = 0;
		}
		if ((int)x_poz != (int)x_next || (int)y_poz != (int)y_next) {
			mvprintw(offset_y - y_poz - 2, x_poz,      " ");
			mvprintw(offset_y - y_poz - 1, x_poz - 1, "   ");
			mvprintw(offset_y - y_poz, x_poz - 1,     "   ");
			x_poz = x_next;
			y_poz = y_next;
			mvprintw(offset_y - y_poz - 2, x_poz,      "_");
			mvprintw(offset_y - y_poz - 1, x_poz - 1, "/O\\");
			mvprintw(offset_y - y_poz, x_poz - 1,     "( )");
		}
	}

};
