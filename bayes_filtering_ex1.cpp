// monte carlo localization algorithm estimates the posterior distribution of the robot's
// position and orientation based on sensors. --> this uses the recursive bayes filter.

// given P(POS) = prob robot being in actual position, and
//  P(DOOR|POS) = prob of robot seeing the door given it's in the actual position, and
// P(DOOR|!POS) = prob of the robot seeing the door given it's not i the actual position,
// compute P(POS|DOOR) given bayesian logic

#include <iostream>
using namespace std;

int main() 
{
	//Given P(POS), P(DOOR|POS) and P(DOOR|¬POS)
	double a = 0.0002 ; //P(POS) = 0.002
	double b = 0.6    ; //P(DOOR|POS) = 0.6
	double c = 0.05   ; //P(DOOR|¬POS) = 0.05
	
	//TODO: Compute P(¬POS) and P(POS|DOOR)
	double d = (1 - a);                         //P(¬POS)
	double e = (b * a) / ((b * a) + (c * d));   //P(POS|DOOR)
	
	//Print Result
	cout << "P(POS|DOOR)= " <<    e    << endl;
	
	return 0;
}
