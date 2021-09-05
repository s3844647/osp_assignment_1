all: ProdCon.cpp Barbers.cpp
	g++ -g -Wall -pthread -o simulation ProdCon.cpp Barbers.cpp

clean:
	rm simulation