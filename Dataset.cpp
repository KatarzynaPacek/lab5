#include "Dataset.h"


bool Dataset::push_back(Sample New_Sample)
{

	if(!Data.size())
		{
			Data.push_back(New_Sample);
			return true;
		}
	if(Data[(int)Data.size() - 1].Get_features().size()  == New_Sample.Get_features().size() )
		{
			Data.push_back(New_Sample);
			return true;
		}
	else
		return false;
	
}
