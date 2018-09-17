# Makefile for project.cpp
# Ryker McIntyre
# December 2017

CMP = g++
MAIN = project.cpp
CLASS = gfx.o
EXEC = graph

$(EXEC): $(MAIN) $(CLASS)
	$(CMP) -std=c++11 $(MAIN) $(CLASS) -lX11 -o $(EXEC)

clean:
	rm $(EXEC)

