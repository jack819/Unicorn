Sess : main.o math.o
	cc -o Sess main.o math.o -lGLEW -lGL -lglut

main.o : main.cpp math.h 
	cc -c main.cpp
	
math.o : math.cpp math.h
	cc -c math.cpp 

clean : 
	-rm Sess main.o math.o