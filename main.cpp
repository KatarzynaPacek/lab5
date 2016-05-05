#include "Sample.h"
#include "Dataset.h"
#include "Prediction.h"

#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <algorithm>
/*
- Jako argumenty wiersza poleceń programu, przekaż nazwę pliku oraz liczbę całkowitą `k`,
- dla celów testowych, w repozytorium znajduje się plik `wine.csv`,
- wczytaj plik `wine.csv` do wektora obiektów typu `Sample` tak, aby pierwsza jego kolumna określała `label`, a pozostałe znalazły się w wektorze `features`,
- stwórz dwa obiekty klasy `Dataset`. Pierwszy nazwij `train`, drugi `test`,
- do `train` wprowadź losowe 20% wczytanych z pliku obiektów, a do `test`, resztę,
- zaimplementuj funkcję `knn()`, zwracającą wektor obiektów klasy `Prediction` przyjmującą jako argumenty dwa obiekty typu `Dataset` (`train` i `test`) i zmienną całkowitą `k`:
    - utwórz w niej wektor `predictions`:
    - do utworzonego wektora wprowadź kopie wszystkich obiektów (mają typ `Sample`) znajdujących się w `test`, uzupełniając dla nich wartość `prediction`, według następującego schematu:

>   Dla każdego obiektu ze zbioru testowego znajdź `k` obiektów ze zbioru uczącego, którego cechy (`features`) znajdują się w najmniejszej od niego [odległości](https://pl.wikipedia.org/wiki/Odległość). Za `prediction` uznaj `label`, który powtarza się najczęściej wśród znalezionych.
>   

- Wyświetl użytkownikowi informacje o zbiorze (nazwa pliku, liczba próbek, liczba cech) oraz jakość klasyfikacji (`accuracy()`).
*/

using namespace std;

vector <Prediction *> knn(Dataset *train, Dataset *test, int k);
double distance(Sample * a, Sample * b);


int main(int argc, char const *argv[])
{
	int a = 0;
	int k = atoi(argv[2]);
	string filename = argv[1];
	fstream file;
	vector<Sample> vector_wine;
	Dataset * train = new Dataset;
	Dataset * test = new Dataset;


	srand( time( NULL ) );



	file.open("wine.csv" , ios::in);
	if( file.is_open() == true )
	{	
		cout << "Uzyskano dostep do pliku" << endl;
		
		while(!file.eof())
		{
			string row;

    		getline(file , row);
    		if(file.eof()) break;
    		char* row1 = (char*)row.c_str();
    		char* number;
    		number = strtok(row1 , ",\n");
    		int label=atoi(number);
    		vector<double> features;
    		while(number != NULL)
    		{
    			number = strtok(NULL , ",\n");
    			if(number)
    			{
    				features.push_back(atof(number));
    			}
    		}
    		//cout<<"size: "<<features.size()<<endl;
    		Sample newSample(label,features);
			vector_wine.push_back(newSample);
    		//cout << row << endl;

    	}


    	
	}

   
   	else cout << "Dostep do pliku zostal zabroniony" << endl;
	file.close();

	cout << (int)vector_wine.size() << endl;

	a = ((int)vector_wine.size() * 0.2);
	//cout << " a = " <<  a << endl;

	for(int i =0 ; i < a ; ++i ) // przydzielenie 20% obiektów do train
	{
		int random_number = (rand() % (int)vector_wine.size());
		train -> push_back(vector_wine[random_number]);

		//cout << (int)vector_wine.size() << " ";
 		//cout << random_number << endl;

		vector_wine.erase(vector_wine.begin()+random_number);
	}

	//cout << (int)vector_wine.size() << endl;

	for(int i = 0; i < (int)vector_wine.size(); ++i) /// przydzielenie pozostalych 80% obiektow
	{
		test -> push_back(vector_wine[i]);
	}
	vector<Prediction*> predictions=knn(train,test,k);
	cout<<endl<<"-------------------------"<<endl;
	cout<<"|  Uruchomiono dla pliku: "<< filename<<endl;
	cout<<"|  Liczba probek:         "<< k<<endl;
	cout<<"|  Liczba cech:           "<< test->Data[0].Get_features().size()<<endl;
	cout<<"|  Jakość klasyfikacji:   "<< Prediction::accuracy(predictions)<<endl;
	cout<<"-------------------------"<<endl;
}


// funkcję `knn()`, zwracającą wektor obiektów klasy `Prediction` przyjmującą jako argumenty dwa obiekty typu `Dataset` (`train` i `test`) i zmienną całkowitą `k`:
  //  - utwórz w niej wektor `predictions`:
    //- do utworzonego wektora wprowadź kopie wszystkich obiektów (mają typ `Sample`) znajdujących się w `test`, uzupełniając dla nich wartość `prediction`, według następującego schematu:

vector <Prediction *> knn(Dataset *train, Dataset *test, int k)
{
	vector <Prediction *> predictions;

	for(int i = 0 ; i < (int)(test -> Data.size()) ; ++i)
	{
		predictions.push_back(new Prediction(*reinterpret_cast<Prediction *>(&(test->Data[i]))));
	}
	
	for(int i = 0 ; i < (int)(test -> Data.size()) ; ++i)
	{
		
		vector<Sample> looking;
		double bigest_distance = 0;
		int index = 0;
		//bigest_distance = distance(predictions[i] , &(looking[i])
		for(int j = 0 ; j < k ; ++j) // przypisywanie pierwszym trzem obiektom pierwszych trzech obiektow z train
		{
			looking.push_back(train -> Data[j]);
			if(bigest_distance < distance(predictions[j] , &(looking[j])))
			{
				bigest_distance = distance(predictions[j] , &(looking[j]));
				index = j;
			}


		}
		for(int l = k; l < (int)(train -> Data.size()); ++l)
		{
			if(bigest_distance > distance(predictions[l] , &(train->Data[l])))
			{
				looking[index] = train->Data[l];
				bigest_distance=0;
				for(int m = 0 ; m < k ; ++m) 
				{
					if(bigest_distance < distance(predictions[m] , &(looking[m])))
					{
						bigest_distance = distance(predictions[m] , &(looking[m]));
						index = m;
					}
				}
			}
		}

		vector<int> labels;
		for(int j = 0 ; j < k ; ++j)
		{
			labels.push_back(looking[j].Get_label());
		}
		
		sort(labels.begin(),labels.end(),[](const int& a, const int& b)->bool
		{
			return a<b;
		});

		int maxLabel=labels[0];
		int lastLabel=labels[0];
		int counter=1;
		int maxCounter=1;
		for(int j=1;j<k;++j)
		{
			if(labels[j]!=lastLabel)
			{
				if(maxCounter<counter)
				{
					maxCounter=counter;
					maxLabel=lastLabel;
				}
				counter=1;
				lastLabel=labels[j];
			}
			else
			{
				counter++;
			}
		}

		predictions[i]->prediction = maxLabel;
	}
	return predictions;
}

	double distance(Sample * b1, Sample * b2)
	{
		double distance;
		double sum = 0;
		vector<double> one(b1->Get_features());
		vector<double> second(b2->Get_features());

		int a;
		a = (int)one.size();
		if((int)one.size() > (int)second.size())
			a = (int)second.size();


		for(int i = 0 ; i < a ; ++i)
		{
			sum += pow((one[i] - second[i]) , 2);
		}

		return distance = sqrt(sum);




	}


	//czyli prediction jest to label ktory powtarza sie najczesciej wsrod znalezionych
	//dla kazdego obiektu w wektorze predictions 
	// zdnajdz k czyli 3 obiekty ze zbioru train 
	//ktorego cechy features znajduja sie od niego w najmnijeszej odleglosci





	//for(int i = 0; i < test.size() ; ++i) // petla w ktorej wypelniamy predictions obiektami z test
	

