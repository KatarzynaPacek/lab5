#include "Sample.h"
Sample::Sample(int label1 , vector<double> features1)
{
	label = label1;
	for(int i = 0; i < (int)features1.size() ; ++i )
	{
		features.push_back(features1[i]);
	}
}

int Sample::Get_label()
	{	
	return label;
	}

vector<double> Sample::Get_features()
	{
	return features;
	}

void Sample::Set_label(int newLabel)
{
	label=newLabel;
}

void Sample::Set_features(vector<double> newFeatures)
{
	features.clear();
	for(int i = 0; i < (int)newFeatures.size() ; ++i )
	{
		features.push_back(newFeatures[i]);
	}
}