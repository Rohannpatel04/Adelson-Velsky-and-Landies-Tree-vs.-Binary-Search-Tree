g++ -g -O0 TreeDriver.cpp -o treetest
valgrind --leak-check=yes ./treetest
./treetest 
