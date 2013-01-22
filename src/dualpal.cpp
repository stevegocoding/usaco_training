/*
ID: stevego1
LANG: C++
PROG: dualpal
*/

#include <string> 
#include <fstream>

using namespace std;

char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

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
		num.insert(num.begin(), '0' + val % base /*NUMBER[val % base]*/); 
		val /= base; 
	}
	return num; 
}

int main(int argc, char **argv)
{
	ifstream ifs("dualpal.in"); 
	ofstream ofs("dualpal.out"); 
	int n = 0;
	int s = 0; 
	ifs >> n; 
	ifs >> s; 

	int num = s + 1;
	int c = 0; 
	string num_str;
	while (n > 0) 
	{
		c = 0;  
		for (int b = 2; b <= 10; ++b)
		{
			num_str = convert(num, b); 
			if (is_palindrome(num_str))
			{
				c++; 
			}
		}
		if (c >= 2)
		{
			n--; 
			ofs << num_str << endl;
		}
		num++; 
	}
	return 0; 
}