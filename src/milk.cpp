/*
ID: stevego1
LANG: C++
PROG: milk
*/

#include <fstream> 
#include <algorithm>
#include <vector>

using namespace std;

struct milk_farmer
{
	milk_farmer(int _price, int _product) 
		: price(_price)
		, product(_product) 
	{}
	int price, product; 
};
bool farmer_comp(const milk_farmer& f1, const milk_farmer& f2) { return f1.price < f2.price; }

int main(int argc, char **argv)
{
	int demands = 0; 
	int num_farmers = 0; 
	vector<milk_farmer> farmers;
	ifstream ifs("milk.in");
	ofstream ofs("milk.out"); 
	ifs >> demands >> num_farmers; 
	for (int i = 0; i < num_farmers; ++i)
	{
		int price = 0; 
		int product = 0; 
		ifs >> price >> product;
		farmers.push_back(milk_farmer(price, product)); 
	}
	sort(farmers.begin(), farmers.end(), farmer_comp); 
	
	int cost = 0;
	int amount = 0; 
	int i = 0; 
	while (demands != 0 && i < farmers.size())
	{
		amount = (demands > farmers[i].product) ? farmers[i].product : demands;
		cost += farmers[i].price * amount; 
		demands -= amount; 
		i++; 
	}
	ofs << cost << endl;  
	
	return 0; 
}