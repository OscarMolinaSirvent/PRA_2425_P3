bin/testTableEntry: src/testTableEntry.cpp src/TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry src/testTableEntry.cpp

bin/testHashTable: src/testHashTable.cpp src/TableEntry.h src/HashTable.h src/Dict.h
	mkdir -p bin
	g++ -o bin/testHashTable src/testHashTable.cpp

bin/testBSTree: src2/testBSTree.cpp
	mkdir -p bin
	g++ -o bin/testBSTree src2/testBSTree.cpp

bin/testBSTreeDict: src2/testBSTreeDict.cpp
	mkdir -p bin
	g++ -o bin/testBSTreeDict src2/testBSTreeDict.cpp
clean:
	rm -rf *.o *.gch bin
