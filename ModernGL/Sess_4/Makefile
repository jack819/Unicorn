Sess_4 : main.o Matrix4f.o GLProgram.o Camera.o
	cc -o Sess_4 main.o Matrix4f.o GLProgram.o Camera.o -lGLEW -lGL -lglut -lm -lstdc++

main.o : main.cpp   Matrix4f.h Vec3f.h GLProgram.h
	cc -c main.cpp 
	
Matrix4f.o : Matrix4f.cpp Matrix4f.h Vec3f.h
	cc -c Matrix4f.cpp 

GLProgram.o : GLProgram.cpp GLProgram.h
	cc -c GLProgram.cpp

Camera.o : Camera.cpp Camera.h
	cc -c Camera.cpp

clean : 
	-rm Sess_4 main.o Matrix4f.o GLProgram.o Camera.o