#include "Prediction.h"


double Prediction::accuracy(vector<Prediction*> Arg)
{
	double a = 0;

	for(int i =0 ; i < (int)Arg.size() ; ++i)
	{
		if(Arg[i]->label == Arg[i]->prediction)
			a++;
	}

	return (a/(double)Arg.size());
}