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
#include"node.h"

using namespace std;

node::node(){

lowerBound=0;
upperBound=0;
node1=0;

}

		
		
double node::getLower(){
return lowerBound;

}


void node::setLower(double l){
lowerBound = l;
}

double node::getUpper(){
return upperBound;
}

void node::setUpper(double u){
upperBound = u;
}
