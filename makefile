all: ProdCon.cpp
	g++ -g -Wall -pthread -o simulation ProdCon.cpp

clean:
	rm simulation