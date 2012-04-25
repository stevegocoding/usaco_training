/*
ID: stevego1
LANG: C++
PROG: gift1
*/

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

struct person;
person *find_person_by_idx(unsigned int idx);

struct person
{
    string name;
    list<int> friends_list;
    unsigned int num_friends;

    int money;
    int money_each_gift;
    int money_left;

    person()
        : num_friends(0)
        , money(0)
        , money_each_gift(0)
        , money_left(0)
    {
    }

    void add_friend(int friend_index)
    {
        friends_list.push_back(friend_index);

        money_each_gift = money / num_friends;
        money_left = money % num_friends;
    }

    void receive_gift(int gift_money)
    {
        money += gift_money;
    }

    void give_gift()
    {
        list<int>::iterator it;
        for (it = friends_list.begin(); it != friends_list.end(); ++it)
        {
            person *rcvr = find_person_by_idx(*it);
            rcvr->receive_gift(money_each_gift);
            money -= money_each_gift;
        }
    }

    void print_money(ostream& os)
    {
        os << name << " " << money << endl;
    }
};

typedef vector<person*> person_vector;
person_vector g_group;

typedef vector<string> person_names_vector;
person_names_vector g_names;

person *find_person_by_idx(unsigned int idx)
{
    string name = g_names[idx]; 
    person_vector::iterator it; 
    for (it = g_group.begin(); it != g_group.end(); ++it)
    {
        if ((*it)->name.compare(name) == 0)
        {
            return *it; 
        }
    }
    return NULL;
}

int find_idx_by_name(const string& name)
{
    person_names_vector::iterator it;
    for (it = g_names.begin(); it != g_names.end(); ++it)
    {
        if ((*it).compare(name) == 0)
            return it - g_names.begin();
    }
    return -1;
}

void release()
{
    person_vector::iterator it;
    for (it = g_group.begin(); it < g_group.end(); ++it)
    {
        delete *it;
    }
}

void get_input(istream& is)
{
    int num_people = 0;
    is >> num_people;
    g_names.reserve(num_people);

    for (int i = 0; i < num_people; ++i)
    {
        string name;
        is >> name;
        g_names.push_back(name);
    }

    int person_idx = 0;
    for (; person_idx < num_people; ++person_idx)
    {
        person *p = new person();

        string name;
        int initial_money = 0;
        int num_friends = 0;
        is >> name >> initial_money >> num_friends;

        p->name = name;
        p->num_friends = num_friends;
        p->money = initial_money;

        for (int j = 0; j < num_friends; ++j)
        {
            string fn;
            is >> fn;
            int fi = find_idx_by_name(fn);
            p->add_friend(fi);
        }
        
        g_group.push_back(p);
    }   
}

int main(int argc, char **argv)
{
    ifstream ifs("gift1.in");
    ofstream ofs("gift1.out");

    get_input(ifs);

    person_vector::iterator it = g_group.begin();
    for (; it != g_group.end(); ++it)
        (*it)->give_gift();

    for (it = g_group.begin(); it != g_group.end(); ++it)
    {
        (*it)->print_money(ofs);
    }
    
    release(); 
}
