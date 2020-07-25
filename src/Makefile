
cpproot=fit-thermo-H2O-R32
ext=cpp
cppfile=$(cpproot).$(ext)
objfile=$(cpproot).o functions-thermo-H2O-R32.o
exefile=$(cpproot).x

CXX=g++


lnk: cmp 
	$(CXX)   $(objfile)  -o $(exefile)
cmp:
	$(CXX) -c functions-thermo-H2O-R32.cpp
	$(CXX) -c $(cppfile) 

run:
	./$(exefile)
cln:
	rm -f $(objfile)  $(exefile)

all: cln cmp lnk run

 
