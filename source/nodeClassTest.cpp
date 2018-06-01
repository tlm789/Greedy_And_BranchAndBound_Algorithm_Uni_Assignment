

using namespace std;

#include<string>
#include<vector>
#include"nodeClassTest.h"


using namespace std;


nodeClassTest::nodeClassTest(){

lowerBound=0;
node =0;

}


double nodeClassTest::getLower(){
	return lowerBound;
}

void nodeClassTest::setLower(double l){
 lowerBound = l;
}
