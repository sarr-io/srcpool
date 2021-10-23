all:
	g++ -Isrc/include -Ieditor -Lsrc/lib -o instance/window window.cpp editor/plugins/*.cpp src/include/glad/glad.c -lmingw32 -lSDL2main -lSDL2 -mwindows