CXX = g++
CXXWARNINGS = -Wall -Werror -Wextra
INCLUDES = -I include/ -I external/include
LIBS = -lpthread
CXXSTANDARD = -std=c++11
CXXFLAGS = $(CXXSTANDARD) $(CXXWARNINGS)

project : project.o src/tempTrender.o src/parse_csv.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) project.o src/tempTrender.o src/parse_csv.o -o project $(LIBS)

project.o : project.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c project.cpp -o project.o

src/tempTrender.o : src/tempTrender.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c src/tempTrender.cpp -o src/tempTrender.o

src/parse_csv.o : src/parse_csv.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c src/parse_csv.cpp -o src/parse_csv.o
