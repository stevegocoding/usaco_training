/*
ID: stevego1
LANG: C++
PROG: namenum
*/

#include <string> 
#include <vector> 
#include <fstream> 
#include <algorithm>

using namespace std;

char keymap[8][3] = {
					{'A', 'B', 'C'}, 
					{'D', 'E', 'F'}, 
					{'G', 'H', 'I'}, 
					{'J', 'K', 'L'}, 
					{'M', 'N', 'O'},
					{'P', 'R', 'S'}, 
					{'T', 'U', 'V'}, 
					{'W', 'X', 'Y'}}; 

int main(int argc, char **argv)
{
	vector<string> dict; 
	string number; 
	ifstream ifs("namenum.in"); 
	ifstream dictifs("dict.txt");
	ifs >> number; 
	while (!dictifs.eof())
	{
		string w; 
		getline(dictifs, w); 
		dict.push_back(w); 
	}

	int dig = 0; 
	vector<int> matched_digs(dict.size()); 
	fill(matched_digs.begin(), matched_digs.end(), 0); 
	vector<string> results;
	int start = 0; 
	while (dig < number.length())
	{
		//  start = keymap[number[dig]-'0'-2][i] - dict[0][dig] 
		for (int w = start; w < dict.size(); ++w)
		{
			if (matched_digs[w] == -1)
				continue; 
			bool matched = false;
			for (int i = 0; i < 3; ++i)
			{
				char ch = keymap[number[dig]-'0'-2][i];
				char ch2 = dict[w][matched_digs[w]]; 
				matched = matched || (ch == ch2);
			}
			if (matched)
				matched_digs[w]++;
			else 
				matched_digs[w] = -1; 
			if (matched_digs[w] == dict[w].length() && dig == number.length()-1)
			{
				results.push_back(dict[w]); 
			}
		}
		dig++; 
	}
	
	ofstream ofs("namenum.out"); 
	if (results.size() == 0)
		ofs << "NONE" << endl;
	else
	{		
		for (int i = 0; i < results.size(); ++i)
			ofs << results[i] << endl; 
	}

	ofs.close(); 
	
	return 0; 
}