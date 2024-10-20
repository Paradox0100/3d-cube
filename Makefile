build:
	g++ src/*.cpp -o program -lSDL2
run:
	./program
clean:
	rm -f program
