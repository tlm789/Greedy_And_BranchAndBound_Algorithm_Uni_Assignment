
/*

CSCI203
Student Name: Tessa Marelic
Subject: CSCI203
Student ID: 4954130
Email: tlm789
This is the header file for setQ.cpp, it contains
all prototypes concerned with the creation and
manipulation of a queue

*/
#include<iostream>

#ifndef _CLASSQUEUE_
#define _CLASSQUEUE_



struct Qmembers{
	int colIndex;
	int rowIndex;
	double edge;

};

struct PossTrees{
	int colInd;
	int rowInd;
	double upperBound;
	double lowerBound;

};


class setQ{
	
	

	private:
	
	int QSIZE;
	int POSSTREESIZE;
	int start;
	int startTree;
	int next;
	int nextTree;
	int counter;
	int possCounter;


	public:


	
	Qmembers *queue;
	//PossTrees *possTreesQ;
	PossTrees *bbq;
	setQ();
	~setQ();
	void allocateMemory(int);
	void allocateMemoryPossTrees(int);
	void enqueue(Qmembers);
	void enqueueNV(PossTrees);
	Qmembers dequeue();
	PossTrees dequeueNV();
	bool isEmpty();
	int getCounter();
	Qmembers front();
	void display();
	int getQSIZE();
	void setQSIZE(int);
	void enqueuePT(PossTrees);
	int getPosCounter();
	
	

};

#endif
