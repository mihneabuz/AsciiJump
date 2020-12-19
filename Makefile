build:
	g++ test.cpp -o main -lncurses

run: build
	./main

clean:
	rm main

test: build
	./run.sh
