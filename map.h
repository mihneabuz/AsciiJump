#define PLAT 3
#define DEST 4

typedef struct Platform {
	bool exists;
	int type;
	int poz;
	int size;
} platform;

class Map {
public:
	int height;
	int width;
	int heightOffset;
	int widthOffset;
	int platform_chance;
	int platform_chance_inc;
	int platform_chance_dec;
	int max_platform_size;
	int min_platform_size;
	platform* map;
	float advance;

	Map(int h, int w, int hoff, int woff, int chance) {
		height = h;
		width = w;
		heightOffset = hoff;
		widthOffset = woff;
		min_platform_size = width / 12 + 1;
		max_platform_size = width / 8;
		platform_chance = chance;
		platform_chance_inc = chance / 5;
		platform_chance_dec = chance;
		advance = 0;
		map = new platform[height];
		map[height - 1].exists = false;
		map[height - 2].exists = false;
		map[height - 3].exists = false;
		for (int i = 0; i < height - 3; i++) {
			map[i] = generateLine();
		}
	}

	platform generateLine() {
		platform aux;
		int x = rand() % 100;
		if (x < platform_chance) {
			platform_chance -= platform_chance_dec;
			aux.exists = true;
			aux.type = rand() % 3 == 2 ? 1 : 0;
 			aux.poz = rand() % (width - max_platform_size + 1);
			aux.size = rand() % (max_platform_size - min_platform_size + 1)
					   + min_platform_size;
		}
		else
		{
			platform_chance += platform_chance_inc;
			aux.exists = false;
			aux.poz = 0;
			aux.size = 0;
		}
		return aux;	
	}

	bool colision(int x, int y) {
		y++;
		if (map[height - y].poz <= x && 
			map[height - y].poz + map[height - y].size >= x) {
			if (map[height - y].type) {
				map[height - y].exists = false;
				for (int i = 0; i < map[height - y].size; i++)
					mvprintw(heightOffset + height - y, 
							 widthOffset + map[height - y].poz + i, " ");
			}
			return true;
		}
		return false;
	}

	void update() {
		for (int i = 0; i < height; i ++)
			if (map[i].exists)
			{
				if (map[i].type)
					attron(COLOR_PAIR(DEST));
				else
					attron(COLOR_PAIR(PLAT));
				for (int j = 0; j < map[i].size; j ++)
					mvprintw(heightOffset + i, widthOffset + map[i].poz + j, "~");
				if (map[i].type)
					attroff(COLOR_PAIR(DEST));
				else
					attroff(COLOR_PAIR(PLAT));
			}
	}

	void clear() {
		for (int i = 0; i < height; i ++)
			if (map[i].exists)
			{
				for (int j = 0; j < map[i].size; j ++)
					mvprintw(heightOffset + i, widthOffset + map[i].poz + j, " ");
			}
	}

	void upscroll() {
		advance += 0.7;
		if (advance > 1) {
			advance --;
			for (int i = height - 1; i > 0; i--) {
				map[i] = map[i - 1];
			}
			map[0] = generateLine();
		}
	}


};
