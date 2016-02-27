all:
	mkdir -p bin
	g++ src/main.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -o bin/sudoko-grab
	cp src/img/sudoku.jpg bin/
