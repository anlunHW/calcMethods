all:
	g++ -o parallel -fopenmp -DN=2000 -DM=2000 main.cpp
	g++ -o matrixCreate -DN=2000 -DM=2000 matrixCreate.cpp
	./matrixCreate
	#cat 1.matrix | ./parallel

nonParallel:
	g++ -o nonParallel -DN=2000 -DM=2000 main.cpp
	#g++ -o matrixCreate -DN=10000 -DM=10000 matrixCreate.cpp
	#./matrixCreate
	#cat 1.matrix | ./nonParallel

runSmall:
	g++ -o test -fopenmp -DN=4 -DM=4 main.cpp
	g++ -o matrixCreate -DN=4 -DM=4 matrixCreate.cpp
	./matrixCreate
	cat 1.matrix | ./test

article:
	xelatex -shell-escape main.tex
