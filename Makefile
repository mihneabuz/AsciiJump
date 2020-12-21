EXE = asciijump

build: 
	g++ game.cpp -o $(EXE) -lncursesw -Wall -Wextra

run: build
	./$(EXE)

clean:
	rm $(EXE)
