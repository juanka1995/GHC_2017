bin/main: obj/main.o obj/controlador.o
	g++ -Wall -std=c++11 -O3 -o bin/main obj/main.o obj/controlador.o

obj/main.o: src/main.cpp include/Controlador.h
	g++ -I include/ -Wall -c -std=c++11 -O3 -o obj/main.o src/main.cpp

obj/controlador.o: src/Controlador.cpp include/Controlador.h
	g++ -I include/ -Wall -c -std=c++11 -O3 -o obj/controlador.o src/Controlador.cpp

clean:
	rm -f bin/main obj/*.o doc/*.out
