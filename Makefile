build:
	g++ test.cpp -o main -lncursesw

run: build
	./main

clean:
	rm main

test: build
	./main
