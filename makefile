all: main.cpp ProdCon.cpp Barbers.cpp
	g++ -g -Wall -pthread -D PRODCON -D BARBERS -o simulation main.cpp ProdCon.cpp Barbers.cpp

prodcon: main.cpp ProdCon.cpp
	g++ -g -Wall -pthread -D PRODCON -o simulation main.cpp ProdCon.cpp

barbers: main.cpp Barbers.cpp
	g++ -g -Wall -pthread -D BARBERS -o simulation main.cpp Barbers.cpp
	
clean:
	rm simulation