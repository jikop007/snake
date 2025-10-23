all:
	g++ src/main.cpp src/Game.cpp src/Snake.cpp src/Apple.cpp -Iinclude -std=c++17 -Wall -o snake.exe

run: all
	./snake.exe

clean:
	-del snake.exe 2>nul || rm -f snake.exe
