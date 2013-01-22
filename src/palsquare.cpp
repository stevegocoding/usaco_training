/*
ID: stevego1
LANG: C++
PROG: palsquare
*/

#include <string> 
#include <fstream>

using namespace std;

char NUMBER[20] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
					'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

bool is_palindrome(const string& s)
{
	int low = 0; 
	int high = (int)s.length()-1; 
	while (low < high)
	{
		if (s[low++] != s[high--])
			return false;
	}
	return true; 
}

string convert(int val, int base)
{
	string num; 
	while(val)
	{
		num.insert(num.begin(), NUMBER[val % base]); 
		val /= base; 
	}
	return num; 
}

int main(int argc, char **argv)
{
	ifstream ifs("palsquare.in");
	ofstream ofs("palsquare.out"); 

	int base = 0; 
	ifs >> base;
	string num, square; 
	for (int i = 1; i <= 300; ++i) 
	{
		num = convert(i, base); 
		square = convert(i*i, base);
		if (is_palindrome(square))
			ofs << num << " " << square << endl; 
	}

	return 0; 
}