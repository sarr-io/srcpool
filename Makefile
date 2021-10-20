all:
	g++ -Isrc/include -Lsrc/lib -o instance/window window.cpp -lmingw32 -lSDL2main -lSDL2 -mwindows