all: Launcher.cpp ProdCon.cpp Barbers.cpp
	g++ -g -Wall -o simulation Launcher.cpp ProdCon.cpp

clean:
	rm simulation