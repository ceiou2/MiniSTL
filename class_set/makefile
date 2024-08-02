all:testRB_Tree testSet

testRB_Tree:testRB_Tree.cpp RB_Tree.h
	g++ -o testRB_Tree testRB_Tree.cpp -g
testSet:testSet.cpp RB_Tree.h
	g++ -o testSet testSet.cpp -g -lgtest -lpthread

clear:
	rm testRB_Tree testSet
