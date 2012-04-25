/*
ID: stevego1
LANG: C++
PROG: ride
TASK: ride
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

using namespace std;

string comet_name;
string group_name;

int comet_number = 1;
int group_number = 1;

int char_to_number(char ch)
{
    return ch - 64;
}

void get_input(istream& is)
{
    is >> comet_name;
    is >> group_name;
}

int name_to_number(string& name_str)
{
    if (name_str.empty())
        return -1;

    int number = 1;
    string::iterator it;
    for (it = name_str.begin(); it != name_str.end(); ++it)
    {
        number *= char_to_number(*it);
    }

    return number;
}

int main(int argc, char **argv)
{
    ifstream ifs("ride.in");
    ofstream ofs("ride.out");

    get_input(ifs);

    int comet_num = name_to_number(comet_name);
    int group_num = name_to_number(group_name);

    if ((comet_num % 47) == (group_num % 47))
        ofs << "GO" << endl;
    else
        ofs << "STAY" << endl;

    return 0;
}