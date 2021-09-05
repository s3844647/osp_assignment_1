all: main.cpp ProdCon.cpp
	g++ -g -Wall -pthread -D PRODCON -o simulation main.cpp ProdCon.cpp

clean:
	rm simulation