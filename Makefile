driver.x: driver.o bet.o
	g++ -std=c++11 -o driver.x driver.o bet.o

driver.o: driver.cpp bet.h
	g++ -c -std=c++11 driver.cpp

bet.o: bet.cpp bet.h
	g++ -c -std=c++11 bet.cpp

clean:
	rm -f driver.x *.o
