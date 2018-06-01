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
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<cstring>

#include"Matrix.h"


using namespace std;


int main(int argc, char* argv[]){

int r;
int c;
ifstream fin;
char matrixFile[40];
char citiesFile[40];

strcpy(matrixFile,argv[1]);
fin.open(matrixFile, ios::in);

strcpy(citiesFile,argv[2]);


//fin.open("Australia_roads.txt", ios::in);
//fin.open("Australia_flights.txt", ios::in);

if(!fin){
	cout << "cannot open matrix file" << endl;
} 

//read dimensions of matrix
fin >> r;

c=r;

//create new r x c matrix
Matrix m(r,c);

//fill matrix with adjacency matrix values from text file

m.fillMatrix(fin);

fin.close();

fin.open(citiesFile, ios::in);
//fin.open("Australia_cities.txt", ios::in);
//fin.open("cityFile.txt", ios::in);

if(!fin){
	cout << "cannot open cities file" << endl;
} 


//fill cities array
m.fillCities(fin);
fin.close();

time_t begin = time(0);
m.Greedy();
time_t end = time(0);
double time1 = difftime(end,begin)*1000;
//cout << "time of greedy is:" << ' ' << time1 << endl;

time_t start = time(0);
m.BranchBound();
time_t finish = time(0);
double time2=difftime(start,finish)*1000;
//cout << "time of b&b is:" << ' ' << time2 << endl;

return 0;

}
