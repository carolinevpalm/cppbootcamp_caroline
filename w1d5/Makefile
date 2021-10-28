# Write a make file which generates a shared object from the Shape Assignment. Then write another application
# which uses the share object and creates shapes.

CXX = g++
NAME = shapes.out
main: main.cpp libshapes.so
	@echo -- Building $(NAME) using libshapes.so as a shared library
	@echo -- run "export LD_LIBRARY_PATH=."
	$(CXX) main.cpp -L. -lshapes -o $(NAME)

normal: main.cpp shapes.cpp
	$(CXX) main.cpp shapes.cpp -o shapesnormal.out


libshapes.so: shapes.cpp
	@echo -- Building shared library $@
	$(CXX) --shared -fPIC shapes.cpp -o libshapes.so

#libload:
#	export LD_LIBRARY_PATH=.

clean:
	@echo -- Cleaning up folder
	rm -rf *.o *.so *.a *.out

