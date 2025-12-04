bin/testTableEntry: src/testTableEntry.cpp src/TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry src/testTableEntry.cpp

clean:
	rm -rf *.o *.gch bin
