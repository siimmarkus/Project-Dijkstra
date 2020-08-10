#####################################################
# You may need to change the parameters under here. #
#####################################################

# Step 1: Choose a compiler. By default, use clang++

# If you use clang++, make sure the following line does not start with a comment (#)
#CXX=clang++
# If you use g++, uncomment the following line
CXX=g++

# Set default compiler parameters
# -Wall 	shows all warnings when compiling, always use this!
# -std=c++11 	enables the C++11 standard mode
CXXFLAGS = -Wall -std=c++11

# Step 2: If you use clang++ under Mac OS X, remove these comments
#CXXFLAGS += -stdlib=libc++
#LFLAGS += -stdlib=libc++

# Step 3: Run 'make' in the same directory as this file


############################
# Settings for the library #
############################


# Compiler flag -Idir specifies, that there are includes in the 'dir' directory
LIB_CXXFLAGS = $(CXXFLAGS) -Iinclude

# List of objects for the library
LIBOBJS = obj/Graaf.o obj/Node.o obj/Edge.o
OBJ = obj/Main.o

# Name of the library
LIBRARY = lib/libgraphtheory.a

################################
# Settings for the testing app #
################################

# Compiler flags for the testing app
APP_CXXFLAGS = $(CXXFLAGS) -Iinclude

# Linker flags (order the compiler to link with our library)
LFLAGS += -Llib -lgraphtheory

# Declare the name of our program (in Windows, the compiler adds .exe)
PROGRAM = bin/program.exe



$(PROGRAM): $(OBJ) $(LIBRARY)
	$(CXX) $(OBJ) $(LFLAGS) -o $(PROGRAM)


# Create the library by using 'ar'
$(LIBRARY) : $(LIBOBJS)
	ar cr $(LIBRARY) $(LIBOBJS)

# Compile each source file of the librar
obj/Graaf.o: src/Graaf.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/Graaf.cpp -o obj/Graaf.o

obj/Node.o: src/Node.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/Node.cpp -o obj/Node.o

obj/Edge.o: src/Edge.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/Edge.cpp -o obj/Edge.o

obj/Main.o: src/Main.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/Main.cpp -o obj/Main.o

# Rule for linking the test app with our library
# $(TESTAPP): $(TESTOBJS) $(LIBRARY)
# 	$(CXX) $(TESTOBJS) -o $(TESTAPP) $(LFLAGS) 

# Compile each source file of the library
# obj/geometrytest.o: tests/geometrytest.cpp
	# $(CXX) $(APP_CXXFLAGS) -c tests/geometrytest.cpp -o obj/geometrytest.o 

# This is the first target. It will be built when you run 'make' or 'make build'
build: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f $(LIBOBJS)
	rm -f $(OBJ)
	rm -f $(LIBRARY)
	rm -f $(PROGRAM)
