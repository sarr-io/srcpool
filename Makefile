all:
	g++ -Isrc/include -Ieditor -Lsrc/lib -o instance/srcpool main.cpp editor/renderer.cpp editor/plugins/*.cpp src/include/glad/glad.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image