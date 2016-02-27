all:
	g++ src/main.cpp -lopencv_core -lopencv_flann -lopencv_highgui -o bin/sudoko-grab
