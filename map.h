class Map {
	int height;
	int width;
	int heightOffset;
	int widthOffset;
	char** map;

public:
	Map(int h, int w, int hoff, int woff) {
		height = h;
		width = w;
		heightOffset = hoff;
		widthOffset = woff;
		map = new char*[height];
		for (int i = 0; i < height; i++)
			map[i] = new char[width];
	}

	void update() {

	}


};
