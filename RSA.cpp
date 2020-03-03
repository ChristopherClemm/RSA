#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;


int totient(int n)
{
	  int tot = 1;
	  int p = 0;
	  int q = 0;
	  bool hit = false;
	    for (int i = 2; i < sqrt(n); i++)
	    {
	    	if(hit == false)
	    	{
				for(int j = i; j < n; j++)
				{



					if (i * j == n)
					{
						p = i;
						q = j;
						hit = true;
						break;

					}
				}
	    	}

	    }
	    cout << "p = " << p;
	    cout << ", q = " << q << ", \"decrypted.txt\"";

	    return (p-1)*(q-1);
}

int calcD(int e, int totN)
{
	int result = totN + 1;
	int little = e;
	int count = 1;
	while( little != result)
	{
		if (little < result)
		{
			little += e;
			count++;

		}
		else if(little > result)
		{
			result = result + totN;

		}
	}
	return count;


}

bool etext(int n,int e, string filename)
{
	ifstream inFile;
	string tempString;
	vector <int> letters;
	vector<int> eLetters;

	inFile.open(filename);

	 while (getline(inFile, tempString))
		{
		}
	 inFile.close();
	 for(int i = 0; i < tempString.length(); i++)
	 {
		 int num = 0;

		 if(tempString.at(i) == ' ')
		 {
			 num = 28;
		 }
		 else
		 {
			 char tempChar = tempString.at(i);
			 num = tempChar - 63;
		 }

		 letters.push_back(num);

	 }

	 for(int i = 0; i < letters.size(); i ++)
	 {
		 int E = e;
		 int N = n;
		 int curN =  letters.at(i);
		 int currentNumber = curN;
		 int product = 1;
		 while(E > 1)
		 {
			 if(E % 2 == 0)
			 {
				 currentNumber = currentNumber * currentNumber;
				 E = E/2;
				 currentNumber = currentNumber % n;

			 }
			 else
			 {
				 E = E - 1;
				 product = product * currentNumber;

			 }
		 }
		 int solved = ((product * currentNumber) % n);

		 eLetters.push_back(solved);
	 }
	 ofstream outFile;
	 outFile.open("incrypted.txt");
	 for(int i = 0; i < eLetters.size() -1 ; i++)
	 {
		 outFile << eLetters.at(i) << " ";
	 }
	 outFile << eLetters.at(eLetters.size()-1);
	 outFile.close();




}

bool dtext(int n,int d,string filename, int e)
{
	ifstream inFile;
	int tempn;
	vector <int> numbers;
	vector<int> dNumbers;

	inFile.open(filename);

	 while (inFile >> tempn)
	    {
		 	 numbers.push_back(tempn);
	    }

	 inFile.close();


	 for(int i = 0; i < numbers.size() ; i++)
	 {

		 int D = d;
		 int N = n;
		 int curN =  numbers.at(i);
		 long long currentNumber = curN;
		 long long product = 1;
		 while(D > 1)
		 {
			 if(D % 2 == 0)
			 {
				 currentNumber = currentNumber * currentNumber;
				 D = D/2;
				 currentNumber = currentNumber % n;
			 }
			 else
			 {
				 D = D - 1;
				 product = product * currentNumber;

			 }
		 }
		 int solved = ((product * currentNumber) % n);

		 dNumbers.push_back(solved);

	 }
	 vector<char>dLetters;

	 for(int i = 0; i < dNumbers.size(); i++)
	 {
		 char temp;
		 if (dNumbers.at(i) == 28)
		 {
			  temp = ' ';
		 }
		 else
		 {
			 temp = 'A';
			 if(dNumbers.at(i) < '[' )
			 {
				 int temp2 = dNumbers.at(i) - 2;
				 temp = temp + temp2;
			 }
			 else
			 {
				 temp = 'A';
			 }
		 }

		 dLetters.push_back(temp);
	 }


	 ofstream outFile;
	 outFile.open("decrypted.txt");

	 for(int i = 0; i < dLetters.size()  ; i++)
	 {

		 outFile << dLetters.at(i);
	 }

	return true;

}


int main(int argc, char** argv)
{
		bool error = false;
		string input;
		int e = 0;
		int n = 0;

		e = atoi(argv[1]);
		n = atoi(argv[2]);

		char decision;
		decision = argv[3][0];

		string filename;
		filename = argv[4];

		bool encrypt;
		if( decision == 'e')
		{
			encrypt = true;
		}
		else if (decision == 'd')
		{
			encrypt = false;
		}
		else
		{
			cout << "proper use of 'd' or 'e' not used try again." << endl;
			error = true;
		}

		if (encrypt == true)
		{
			bool finsih = etext(n,e, filename);
			cout << "\"incrypted.txt\"";
		}
		else
		{
			int totN = totient(n);
			int d = calcD(e, totN);
			bool finish = dtext(n,d, filename, e);
		}


	return 0;
}
