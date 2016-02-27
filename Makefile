all:
	mkdir -p bin
	g++ -std=c++11 src/main.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lm -o bin/sudoko-grab
	cp src/img/sudoku.jpg bin/
