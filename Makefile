all: compile execute


compile:
	g++ main.cpp  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

execute:
	./a.out