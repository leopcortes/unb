all: teste_8_rainhas.cpp 8_rainhas.cpp 8_rainhas.hpp 8_rainhas.o
	g++ -std=c++11 -Wall 8_rainhas.o teste_8_rainhas.cpp -o teste_8_rainhas
	./teste_8_rainhas

compile: teste_8_rainhas.cpp 8_rainhas.cpp 8_rainhas.hpp 8_rainhas.o
	g++ -std=c++11 -Wall 8_rainhas.o teste_8_rainhas.cpp -o teste_8_rainhas
	
test: teste_8_rainhas	
	./teste_8_rainhas
	
cpplint: teste_8_rainhas.cpp 8_rainhas.cpp 8_rainhas.hpp
	cpplint 8_rainhas.cpp 8_rainhas.hpp teste_8_rainhas.cpp
	
gcov: teste_8_rainhas.cpp 8_rainhas.cpp 8_rainhas.hpp 
	g++ -std=c++11 -Wall -Wall -fprofile-arcs -ftest-coverage -c 8_rainhas.cpp
	g++ -std=c++11 -Wall -fprofile-arcs -ftest-coverage 8_rainhas.o teste_8_rainhas.cpp -o teste_8_rainhas
	./teste_8_rainhas
	gcov *.cpp	
	
debug: teste_8_rainhas.cpp 8_rainhas.cpp 8_rainhas.hpp 
	g++ -std=c++11 -Wall -Wall -g -c 8_rainhas.cpp
	g++ -std=c++11 -Wall -g 8_rainhas.o teste_8_rainhas.cpp -o teste_8_rainhas
	gdb teste_8_rainhas
	
cppcheck: teste_8_rainhas.cpp 8_rainhas.cpp 8_rainhas.hpp
	cppcheck --enable=warning . 

valgrind: teste_8_rainhas
	valgrind --leak-check=yes --log-file=valgrind.rpt ./teste_8_rainhas

8_rainhas.o: 8_rainhas.cpp 8_rainhas.hpp
	g++ -std=c++11 -Wall -Wall -c 8_rainhas.cpp
	
teste_8_rainhas: teste_8_rainhas.cpp 8_rainhas.cpp 8_rainhas.hpp 8_rainhas.o
	g++ -std=c++11 -Wall 8_rainhas.o teste_8_rainhas.cpp -o teste_8_rainhas

clean:
	rm -rf *.o *.exe *.gc* 