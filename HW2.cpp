#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std; 

struct wordItem
{
string word;
int count;
};

void getStopWords(char *ignoreWordFileName, vector<string> &_vecIgnoreWords);
int storeUniqueWords(vector<string> &_vecIgnoreWords, string filename, wordItem *&Unique);
bool checkStopWord(vector<string> &_vecIgnoreWords, string word1);
int getTotalNumberNonStopWords(wordItem list[], int length);
bool isStopWord(string word, vector<string> &_vecIgnoreWords);
void arraySort(wordItem list[], int length);
void printTopN(wordItem wordItemList[], int topN);
int UniqueNonStopWords(wordItem list[], int length);
const int STOPWORD_LIST_SIZE = 50;
const int INITIAL_ARRAY_SIZE = 100;



int main(int argc, char * argv[]){


	vector<string> _vecIgnoreWords(STOPWORD_LIST_SIZE);
	wordItem * Unique = new wordItem[INITIAL_ARRAY_SIZE];
	getStopWords(argv[3], _vecIgnoreWords);
	for (int i = 0; i < _vecIgnoreWords.size(); i++){
		cout << _vecIgnoreWords[i] << endl;
	}
	int doubleCounter = storeUniqueWords(_vecIgnoreWords, argv[2], Unique); 
	int length = INITIAL_ARRAY_SIZE << doubleCounter;
	arraySort(Unique, length);
	for(int g = 0; g < length; g++){
		cout << Unique[g].word  << '\t' << Unique[g].count << endl;
	}
	int total = getTotalNumberNonStopWords(Unique, length);
	int topN = stoi(argv[1]);
	cout << "TopN is: " << stoi(argv[1]) << endl;
	printTopN(Unique, topN);
	int onlyOnce = UniqueNonStopWords(Unique, length);
	cout << "#" << endl;
	cout << "Array Doubled:" << doubleCounter << endl;
	cout << "#" << endl;
	cout << "Unique non-stop words: " << onlyOnce << endl;
	cout << "#" << endl;
	cout << "Total non-stop words:" << total << endl;









}

void getStopWords(char *ignoreWordFileName, vector<string> &_vecIgnoreWords){

	ifstream myFile;
	string line;
	string stopWord;
	myFile.open(ignoreWordFileName);
	if (myFile.fail()){
		cout << "File not opened successfully" << endl;
	}
	else{
	    int i = 0;
		while(myFile >> line){
			istringstream ss(line);
			while (ss >> stopWord){
				_vecIgnoreWords[i] = stopWord;
				i++;
				}

		}

	}
	myFile.close();
}

bool checkStopWord(vector<string> &_vecIgnoreWords, string word1){
	bool test = false;
	for (int i = 0; i < _vecIgnoreWords.size(); i++){
		if (_vecIgnoreWords[i] == word1){
			test = true;
		}
	}

	return test;

}


int storeUniqueWords(vector<string> &_vecIgnoreWords, string filename, wordItem *&Unique){
	int doubleCount = 0;
	int j = 0;
	string newWord;
	string tempLine;
	int arraySize = INITIAL_ARRAY_SIZE;
	ifstream hungerGames;
	hungerGames.open(filename);
	if (hungerGames.fail()){
		cout << "Could not open file" << endl;
		return -1;
	}
	else{
		cout << "Made it to the else" << endl;
		while(hungerGames >> tempLine){
			istringstream ss(tempLine);
			while(ss >> newWord){
				//Gets a word
				bool test = false;
				//Checks to see if the word is a stop word
				test = isStopWord(newWord, _vecIgnoreWords);
				//If it is, then we move on
				if (test == true){
					continue;
				}
				//If not then we check a few things
				if (test == false){
					//First, check to see if the word is already in our array somewhere.
					bool AlreadyIn = false;
					for(int i = 0; i < arraySize; i++){
						if(Unique[i].word == newWord){
							Unique[i].count = Unique[i].count + 1;
							AlreadyIn = true;
							break;
						}
					}
					if(AlreadyIn == false){
						Unique[j].word = newWord;
						Unique[j].count = 1;
						j++;
					}

					if(j == arraySize - 1){
						for (int f = 0; f < arraySize; f++){
							cout << Unique[f].word << '\t' << f << endl;
						}
						arraySize *= 2;
						cout << "array size: " << arraySize << endl;

						wordItem * temp = new wordItem[arraySize];
						for (int k = 0; k < (arraySize / 2); k++){
							temp[k] = Unique[k];

						}
						doubleCount++;
						delete [] Unique;

						Unique = temp;


					}


					}

		

			}

		}

	}

	hungerGames.close();
	return doubleCount;
}

bool isStopWord(string word, vector<string> &_vecIgnoreWords){
	bool test = false;
	for (int i = 0; i < 50; i++){

		if (word == _vecIgnoreWords[i]){
			test = true;
		}

	}

return test;

}


int getTotalNumberNonStopWords(wordItem list[], int length){
	int total = 0;
	for (int i = 0; i < length; i++){
		total = total + list[i].count;
	}
	return total;

}

void arraySort(wordItem list[], int length){

	//Bubble Sort Algorithm
	int i = 0;
	while (i<length){

		for(int j=length; j>0; j--){

			if(list[j-1].count < list[j].count){

				wordItem x = list[j];

				list[j] = list[j-1];

				list[j-1] = x;

			}

		}
    i++;
	}

}

void printTopN(wordItem wordItemList[], int topN){
	for (int i = 0; i < topN; i++){

		cout << wordItemList[i].count  << " - " << wordItemList[i].word << endl;

	}


}


int UniqueNonStopWords(wordItem list[], int length){
	int counter = 0;
	for (int i = 0; i < length; i++){
		if(list[i].count > 0){
			counter++;
		}

	}

	return counter;
}

















/*int getUniqueWords(char *filename, vector<string> &vecIgnoreWords){
	string fullLine;
	int arraySize = INITIAL_ARRAY_SIZE;
	ifstream wordsFile;
	wordsFile.open(filename);
	int doubleCount = 0;
	string stopWord;
	string uniqueWord;
	if (wordsFile.fail()){
		cout << "File not opened successfully" << endl;
	}
	else{

		int i = 0;
		bool test = false;
		wordItem *UniqueArray = new wordItem[INITIAL_ARRAY_SIZE];
		while(getline(wordsFile, fullLine)){
			istringstream ss2(fullLine);
			while(ss2 >> uniqueWord){
				test = false; 
				for(int k = 0; k < i; k++){
					if (vecIgnoreWords[k] == uniqueWord){
						test = true;
						break;
					}
					else if (UniqueArray[k].word == uniqueWord){
						UniqueArray[k].count++;
					}
				}
				if (test == false){

					if(i == arraySize - 1){
						wordItem *_UniqueArray = new wordItem[2*arraySize];
						for (int j = 0; j < arraySize; j++){
							_UniqueArray[j] = UniqueArray[j];

						}
						arraySize = 2 * arraySize;
						doubleCount++;
					delete [] UniqueArray;
					_UniqueArray[i].word = uniqueWord;
					_UniqueArray[i].count = 1;
					i++;
					}
					else{


						UniqueArray[i] = uniqueWord;
						i++;


					}
				}
			}


		}





	}

	wordsFile.close();
	return doubleCount;

}*/