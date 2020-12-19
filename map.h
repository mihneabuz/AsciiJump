#include <stdlib.h>
typedef struct Platform {
	bool exists;
	int poz;
	int size;
} platform;

class Map {
public:
	int height;
	int width;
	int heightOffset;
	int widthOffset;
	int size;
	int platform_chance = 30;
	int max_platform_size = 7;
	int min_platform_size = 4;
	char platform_char = (char)126;
	platform* map;

	Map(int h, int w, int hoff, int woff) {
		height = h;
		width = w;
		heightOffset = hoff;
		widthOffset = woff;
		size = 1.5 * height;
		map = new platform[size];
		for (int i = 0; i < size; i++) {
			map[i] = generateLine();
		}
	}

	platform generateLine() {
		platform aux;
		int x = rand() % 100;
		if (x < platform_chance) {
			aux.exists = true;
 			aux.poz = rand() % (width - max_platform_size + 1);
			aux.size = rand() % (max_platform_size - min_platform_size + 1)
					   + min_platform_size;
		}
		else
		{
			aux.exists = false;
			aux.poz = 0;
			aux.size = 0;
		}
		return aux;	
	}

	bool colision(int x, int y) {
		if (map[height - y].poz < x && 
			map[height - y].poz + map[height - y].size > x)
			return true;
		return false;
	}
	void update() {
		for (int i = 0; i < height; i ++)
			if (map[i].exists)
			{
				for (int j = 0; j < map[i].size; j ++)
					mvprintw(heightOffset + i, widthOffset + map[i].poz + j, "~");
			}
	}


};
