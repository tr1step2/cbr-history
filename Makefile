all: main.cpp
	g++ -std=c++11 main.cpp -lpugixml -lcurl -O4
debug: main.cpp
	g++ -std=c++11 main.cpp -lpugixml -lcurl -ggdb -g
