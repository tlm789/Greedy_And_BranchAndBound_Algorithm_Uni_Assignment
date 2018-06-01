/*
CSCI203
Student Name: Tessa Marelic
Subject: CSCI203
Student ID: 4954130
Email: tlm789

Author:
Sources:
followed algorithms provided in the lecture notes and tutorial instructions

*/



#include <functional>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

#ifndef _NODE_
#define _NODE_







class node{

private:
		
		double lowerBound;
		double upperBound;
		int node1;
		
	public:
		node();
		vector<int> paths;
		
		double getLower();
		void setLower(double);
		double getUpper();
		void setUpper(double);

};
#endif
