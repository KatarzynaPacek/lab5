#pragma once
#include <vector>

using namespace std;

/*
- Stwórz klasę `Sample`, zawierającą:
    - zmienną całkowitą `label`,
    - wektor liczb zmiennoprzecinkowych `features`,
- w konstruktorze klasy `Sample` przyjmuj oba te parametry,
- stwórz też dla nich *gettery*.
*/


class Sample {
	
protected:
	int label;
	vector<double> features;


public:
	Sample(int label , vector<double> features);
	int Get_label();
	vector<double> Get_features();
	void Set_label(int newLabel);
	void Set_features(vector<double> newFeatures);

};

