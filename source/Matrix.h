/*
CSCI203
Student Name: Tessa Marelic
Subject: CSCI203
Student ID: 4954130
Email: tlm789

Author:
Sources:


*/


#include"setQ.h"
#include"node.h"

#include<iostream>
#include<fstream>
#include<cmath>
#include<ctime>
#include<vector>
#include<string>
#include <functional>
#include <queue>


using namespace std;

#ifndef _MATRIX_
#define _MATRIX_

/*struct Vertices{

	int c;
	int r;
	
};

struct considered{
	int co;
	int ro;
	double weight;
};

*/

struct LessThanByLowerBound
{
	bool operator()(node& lhs, node& rhs)
	{
		return lhs.getLower() > rhs.getLower();
	}

};

class Matrix{

	private:
		int row;
		int col;
		double **mat;
		int *notVisited;
		double *dist;
		int *visited;
		int *finalPath;
		std::string *cities;
		setQ set;
		priority_queue<node,std::vector<node>,LessThanByLowerBound> q;
		bool *lowerCheck;
		bool *checkRow;
		vector<int> fPath;
		
		Qmembers qmembers;
		PossTrees trees;
		double upperBound;
		double beginUpperBound;
		double lowerBound;
		int totalNodes;

		
		//Vertices *vertices;
		
		//Edges *edges;
		
		
		
		
		

	public:
		Matrix();
		Matrix(int,int);
		~Matrix();
		Matrix(const Matrix&);
		void setRow(int);
		void setCol(int);
		int getRow();
		int getCol();
		void setValues(int,int);
		void fillMatrix(ifstream&);
		void fillCities(ifstream&);
		void Greedy();
		void DisplayCities();
		void BranchBound();
		void findLowerBound();
		void setUnvisited();
		double calculateLowerBound(vector<int>);
		double calculateUpperBound(vector<int>);
		void setLowerCheck();
		void setCheckRow();
		void expand(vector<int>);
		

		//void displayEdges();
		//void displayVeticeEdge();
		
		


};

#endif
