/*
ID: stevego1
LANG: C++
PROG: calfflac
*/

#include <fstream>
#include <string>
#include <vector> 
#include <ctype.h>

using namespace std; 

int main(int argc, char **argv)
{
	ifstream ifs("calfflac.in"); 
	ofstream ofs("calfflac.out"); 

	string original; 
	string str; 
	int origin_len = 0;
	int str_len = 0; 
	vector<int> str_pos; 

	char ch; 
	while (ifs.get(ch))
	{
		original.push_back(ch); 
		if (isalpha(ch))
		{
			str.push_back(toupper(ch));
			str_pos.push_back(origin_len);
			str_len++; 
		}
		origin_len++; 
	}

	int max_len = 0; 
	int palin_start = 0; 
	for (int i = 0; i < str_len; ++i)
	{
		int len = 0; 
		while ((i-len) >= 0 && (i+len) < str_len && str[i-len] == str[i+len])
			len++;
		if (len > max_len)
		{
			max_len = len;
			palin_start = i; 
		}
	}

	// for even numbers chars in the string 
	int even_max_len = 0; 
	int even_palin_start = 0; 
	for (int i = 0; i < str_len; ++i)
	{
		int len = 0; 
		while ((i-len) >= 0 && (i+len+1) < str_len && str[i-len] == str[i+len+1])
			len++;
		if (len > even_max_len)
		{
			even_max_len = len;
			even_palin_start = i; 
		}
	}

	if ((2 * max_len -1) > (2 * even_max_len))
	{
		ofs << 2 * max_len - 1 << endl;
		for (int i = str_pos[palin_start - max_len + 1]; i <= str_pos[palin_start + max_len - 1]; ++i)
			ofs << original[i];
	}
	else 
	{
		ofs << 2 * even_max_len << endl; 
		for (int i = str_pos[even_palin_start - even_max_len + 1]; i <= str_pos[even_palin_start + even_max_len]; ++i)
			ofs << original[i];
	}
	
	ofs << endl; 
	
	return 0;
}