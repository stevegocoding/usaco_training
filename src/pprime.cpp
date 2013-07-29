/*
ID: stevego1
LANG: C++
PROG: pprime
*/

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

vector<int> palindromes;

int a = 0; 
int b = 0; 

void get_digits(string& digits, int n)
{
	/*
	int temp = n;
	int i = digits.size()-1;
	while (temp)
	{
		digits[i--] = '0' + temp % 10; 
		temp = temp / 10; 
	}

	return digits.size()-i-1;
	*/
	
	if (n / 10 == 0)
	{
		digits.push_back('0' + n%10);
		return;
	}
	get_digits(digits, n/10);
	digits.push_back('0' + n%10);
}

int get_number_value(string& digits)
{
	int val = 0; 
	int count = 0;
	for (int i = digits.length()-1; i >= 0; --i)
	{
		int temp = (int)pow(10, count++);
		int temp2 = digits[i] - '0'; 
		val += temp2 * temp; 
	}
	
	return val;
}

bool is_prime(int n)
{
	//if (n % 2 == 0)
	//	return false;
	
	for (int j = 2; j <= n/2; ++j)
		if (n % j == 0)
			return false;
	return true; 
}

void gen_palin_helper(string& digits)
{
	/*
	if (get_number_value(digits, start+2) > max_palin)
	{
		return; 
	}

	int n = digits.size() - start; 
	for (int i = start+2; i < n; ++i)
		digits[i-1] = digits[i];
	digits[start] = digit; 
	digits[digits.size()-1] = digit;
	
	for (int i = 1; i <= 9; ++i)
	{
		gen_palin_helper(digits, i, start-2, max_palin);

		int val = get_number_value(digits, start);
		if (is_prime(val) && palindromes[val] == 0)
			++palindromes[val]; 
	}
	*/

	int val = get_number_value(digits);
	
	if (val < a || val > b)
		return; 
	
	if (val % 2 == 0 || val % 3 == 0)
		return;
	
	if (digits[0] == '0')
		return; 

	if (digits.length() > 2 && digits.length() % 2 == 0)
		return; 

	if (is_prime(val) && palindromes[val] == 0)
		++palindromes[val]; 

	for (int i = 1; i <= 9; i+=2)
	{
		stringstream ss;
		ss << i;
		string new_digits = ss.str() + digits + ss.str();
		gen_palin_helper(new_digits); 
	}
}

bool is_palindrome(const string& s)
{
	int start = 0; 
	int end = s.length() - 1;
	while (start < end)
	{
		if (s[start++] != s[end--])
			return false;
	}
	return true; 
}

void solve(int a, int b)
{
	palindromes.resize(b); 

	for (int i = a; i <= b; ++i)
	{
		string digits;
		get_digits(digits, i);
		if (is_palindrome(digits))
			gen_palin_helper(digits);
	}
}


int main(int argc, char **argv)
{
	ifstream ifs("pprime.in"); 
	ofstream ofs("pprime.out");
	
	ifs >> a >> b;
	solve(a, b); 

	for (int i = 0; i < palindromes.size(); ++i)
	{
		if (palindromes[i] != 0)
		{
			ofs << i << endl; 
		}
	}

	return 0;
}