/*
CSCI203
Student Name: Tessa Marelic
Subject: CSCI203
Student ID: 4954130
Email: tlm789

This file contains all the methods to create/destroy/fill a matrix 
as well as a branch and bound algorithm to calculate the optimised shortest path
 and a greedy algorithm to calculate non-optimissed shortest path which
 is used as the upper bound for the branch and bound algorithm

Author:
Sources:
followed algorithms provided in the lecture notes and tutorial instructions

*/


#include<string>
#include<iostream>
#include<fstream>
#include"Matrix.h"
#include<cmath>
#include<ctime>
#include<fstream>
#include<cstring>
#include<cctype>
#include<locale>
#include <algorithm>

using namespace std;

//constructor
Matrix::Matrix(){
mat = NULL;
notVisited = NULL;
dist = NULL;
visited=NULL;
finalPath = NULL;

row = 0;
col = 0;



}


//copy constructor

Matrix::Matrix(const Matrix &m){

row = m.row;
col = m.col;

mat = new double*[row];

for(int i =0; i<row; i++){
	for(int j = 0; j<col; j++){
		mat[i][j] = m.mat[i][j];
	}

}

}

//dynamic memory is created for matrices and arrays via this constructor

Matrix::Matrix(int r, int c){

this->row = r;
this->col = c;

mat = new double*[row];


for(int i = 0; i < row; i++){
	mat[i] = new double[col];

}

notVisited = new int[row];
dist = new double[row];
cities = new string[row+1];
visited = new int[row];
finalPath = new int[row];
lowerCheck= new bool[row];
checkRow = new bool[row];

totalNodes=0;
beginUpperBound = 0;


}


//destructor
Matrix::~Matrix(){

	if(mat != NULL){
		for(int i = 0; i<row; ++i){
			
		delete [] mat[i];
		}
	delete [] mat;
	}

	mat = NULL;


	if(notVisited != NULL)
		delete [] notVisited;

	if(dist != NULL)
		delete [] dist;

	if(cities != NULL)
		delete [] cities;

	if(visited != NULL)
		delete [] visited;

	if(finalPath != NULL)
		delete [] finalPath;

if(lowerCheck != NULL)
		delete [] lowerCheck;
	

if(checkRow != NULL)
		delete [] checkRow;
}



void Matrix::setValues(int r,int c){
row = r;
col = c;

}

//method to fill matrix with values from a text file
void Matrix::fillMatrix(ifstream& file){

	double weight;
	for(int i =0; i < this->row; i++){
		for(int j = 0; j<this->col; j++){
			file >> weight;

			//if (weight == 0)
				//weight = INFINITY;//nodes are not connected

			this->mat[i][j] = weight;
			
			}
		
	}

/*for(int i = 0; i<this->row; i++){

	for (int j=0; j<this->row; j++){
		cout << mat[i][j] << ' ';
	}
cout << endl;
}*/




	
}

//fill the cities array with the city names supplied via text file
void Matrix::fillCities(ifstream& file){

std::string city;

for(int i = 0; i < this->row; i++){
	getline(file,city,'\n');	
	city.erase(city.find_last_not_of( ' ' ) );

	this->cities[i] = city;
}


}

//find shortest path using Dijkstar algorithm from lecture notes modified to create a Hamiltonian Circuit 
void Matrix::Greedy(){

int setIndex = 0;
int count = 0;
int v = 0;
double minEdge = 100000;
set.allocateMemory(row);
int j = 1;
int visitedIndex = 0;
double minTree = 0;

//fill notVisited array with nearest neighbours to v1 	
for(int i = 1; i<row; i++){

	notVisited[0] =-1;//this is the first node visited = node 1 so set to -1 to mark it as visited
	
	notVisited[i] = i;
	
	
}

	for(int i = 1; i<row-1; i++){
		dist[i] = mat[0][i];
		visited[i]=1;
		
		}
		

	while (count < row-1){

		minEdge = INFINITY;
		for(int i = 1; i<row; i++){

			if(dist[i]>0){
				if(minEdge >= dist[i]){
					minEdge = dist[i];
					v=i;
				}
			}
		}
		


//find index of minimum

	
		minTree+= minEdge;
		qmembers.colIndex=setIndex;
		qmembers.rowIndex=v;
		qmembers.edge=minEdge;
		set.enqueue(qmembers);
		setIndex=v;

		notVisited[v]=-1;//set to -1 because it's now been visited

		for(int w=0; w<row; w++){//copy next nodes values except for the ones already visited

			int b = notVisited[w];

			if(b>0)
				dist[w] =mat[v][b];

			else
				dist[w]=-1;
			/*if(b!=-1){
				if(dist[b] > dist[v] + mat[v][b]){
				dist[b] = dist[v] + mat[v][b];
				
				}
				visited[b]=v;
			}*/
		}
		
	count++;
	
	}	
//go back home once all nodes have been visited and set to -1 in the notVisisted array
qmembers.colIndex = setIndex;//this is the last node visited before going back to the start
int firstNode = set.queue[0].colIndex;
qmembers.rowIndex = firstNode;
int e = mat[firstNode][setIndex];
minTree+= e;
qmembers.edge = e;
set.enqueue(qmembers);

cout << "1. Greedy Algorithm:" << endl;
cout << endl;
cout << "Number of cities:" << ' ' << row << endl;
cout << endl;
cout << "Tour:" << endl;
cout << endl;
for(int g=0; g<row; g++){

	cout << set.queue[g].colIndex+1 << ' ';

}

cout << endl;

DisplayCities();
cout << endl;
cout << "Total Cost is:" << ' ' << minTree << endl;
upperBound = minTree;
beginUpperBound = minTree;//set upper bound to be used in branch and bound
}

void Matrix::DisplayCities(){
cout.clear();
cout << endl;
for(int i=0; i < this->row+1; i++){

int index = set.queue[i].colIndex;
	cout << this->cities[index] << "->" << ' ';
	
}
cout << endl;
}

//method to calculate least cost path using branch and bound algorithm with priority queue to store lower bound
void Matrix::BranchBound(){

int countExpansions = 0;//variable to count how many partial solution expansions
double currentBest = upperBound;//initialise current best solution with upper bound from greedy algorithm
double l = 0;
findLowerBound();

double lBound = 0;

//initialise queue with first partial paths

	for(int j=1; j<row; j++){
		node n;
		
		n.paths.push_back(0);
		n.paths.push_back(j);
		l = calculateLowerBound(n.paths);
		n.setLower(l);
		
		q.push(n);
		
	}

//pop top to start the while loop
node y = q.top();
q.pop();


	//they are being stored by lowest lower bound value to expand the best estimated solution first
	while(q.size()!=0){

		if(y.getLower() < upperBound)
		{
	
			//check if its a full solution

			//int pathSize = (int)y.paths.size();
			if(y.paths.size()==row-1){
			
			for(int i= 0; i< row; i++)
			{
				if(find(y.paths.begin(), y.paths.end(), i)== y.paths.end())
				{
					y.paths.push_back(i);
				}
			}
			y.paths.push_back(0);
			

			double upper = calculateUpperBound(y.paths);// find the real cost of the solution, greedy algorithm not used here because we have the actual path
				//cout << "upperbound values" << ' ' << upper << endl;		
			y.setUpper(upper);
			
			//cout<<"------------------------"<< upper<< upperBound<< endl;
			if(upper < upperBound){
				
				//cout<< "complete path<------------------"<<endl;
				fPath = y.paths;
				upperBound = upper;//update global upperbound with new lower value so the tree is pruned of solutions with lowerbounds higher than the current best
			}
				
				
			}else
				expand(y.paths);
				countExpansions++;//to count amount of expansions take place
		}
	

		
		y = q.top();//pop next solution
		q.pop();

		
	}
cout << endl;
cout<< "2. Branch and bound algorithm (Best first using a priority queue and breadth-first node expansion:"<< endl;
cout << endl;
cout << "Number of cities" << ' ' << row << endl;
cout << endl;
cout << "upper bound is: " << ' ' << beginUpperBound << endl;
cout << "lower bound is: " << ' ' << lowerBound << endl;
cout << endl;
cout << "Optimal tour:" << endl;
cout << endl;
for(int i = 0; i<fPath.size()-1; i++){
cout << fPath[i]+1 << " ";
}
cout << endl;
cout << endl;
for(int i=0; i<fPath.size(); i++){
	int index = fPath[i];
	cout << cities[index] << ' ' << "->" << ' ';
}
cout << endl;
cout << endl;
cout << "Total cost: " << ' ' << upperBound << endl;

cout << "total nodes generated" << ' ' << totalNodes << endl;


}



void Matrix::expand(vector<int> v){
setLowerCheck();


//bool array to stop visiting already visited nodes
	for(int i = 0; i<v.size(); i++){
		int p = v[i];
		lowerCheck[p] = 1;
		
	
	}

	int pathSize = (int)v.size() + 1;
	

	for(int j = 0; j<row; j++){

		if(!lowerCheck[j]){
			node n;
			n.paths=v;
			n.paths.push_back(j);
			double low = calculateLowerBound(n.paths);
			n.setLower(low);
			q.push(n);
			totalNodes++;	
		}
		
	}

}

double Matrix::calculateLowerBound(vector<int> v){


setCheckRow();//set all bools to 0
setLowerCheck();//set all bools to 0
double lower = 0;
double init = 0;
//double temp = 0;
double home = 0;

//set lowerCheck bools so skip rows already visited
for(int i = 0; i<v.size(); i++){
	int p = v[i];
	lowerCheck[p] = 1;
	
}

//set checkRow bools so skip size-1 cols because can visit another city from last one
for(int i = 0; i<v.size()-1; i++){
	int q = v[i];
	checkRow[q] = 1;
	
}

//calculate initial connection cost of the contents already in the vector of visited nodes
for(int i = 0; i< v.size()-1; i++){
int co = v[i];
int ro = v[i+1];
init+=mat[co][ro];
}



double minHome = INFINITY;

for(int j=0; j<row; j++){

double minEdge = INFINITY;

	//cross out cols = to vector indexes except last one as can visit another city from last one
	if(!lowerCheck[j]){
		for(int i = 0; i < row; i++){
		

			if(!checkRow[i] && mat[i][j] >0 && mat[i][j] < minEdge){
				minEdge = mat[i][j];

			}	
		}

		if(minEdge != INFINITY){
			lower+=minEdge;
		}
	}


}

//find least cost to get home from last node
for(int i = 0; i < row; i++){
		
	if(!lowerCheck[i] && mat[0][i] >0 && mat[0][i] < minHome){
		minHome = mat[0][i];
	}	
}


lower+=init;

if(minHome != INFINITY)
	lower+=minHome;

return lower;
}

double Matrix::calculateUpperBound(vector<int> v){

double upper = 0;

for(int i = 0; i< v.size()-1; i++){
int co = v[i];
int ro = v[i+1];
upper+=mat[co][ro];
}
int index = v[v.size()-1];
double home = mat[0][index];

upper+=home;

return upper;
}


//method to set notVisited array to false
void Matrix::setLowerCheck(){

for(int i = 0; i<row; i++){
	lowerCheck[i] = 0;
}
}

void Matrix::setCheckRow(){

for(int i = 0; i< row; i++){
checkRow[i]=0;
}

}





void Matrix::findLowerBound(){


for(int i=0;i<row; i++){
	double minEdge = INFINITY;
	double temp = 0;
	for(int j=0;j<row; j++){
	temp = mat[i][j];
	if(temp < minEdge && temp != 0)
		minEdge=temp;
	}

lowerBound+=minEdge;

}

}

void Matrix::setUnvisited(){

//create initial not visited list
for(int i = 1; i<row; i++){

	notVisited[0] =-1;//this is the first node visited = node 1 so set to -1 to mark it as visited
	
	notVisited[i] = i;

	//cout << notVisited[i] << ',';
	
}
}






