all: lray clean

lray: main.o jsoncpp.o
	g++ -o lray main.o jsoncpp.o

main.o: main.cpp
	g++ -c main.cpp

jsoncpp.o: jsoncpp.cpp
	g++ -c jsoncpp.cpp

clean:
	-rm *.o

.phony: all clean