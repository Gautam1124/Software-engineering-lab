#include "rdb.h"
using namespace std;
void Print_Record(Record *R)
{
    vector<Attr *> vec = R->attrptr;
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i]->print_Attr();
        cout << " | ";
    }
    cout << endl;
}

void Print_Relation(Relation *R)
{
    // cout<<"check"<<endl;
    vector<string> vec = R->attrnames;
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " | ";
    }
    cout << endl;
    for (auto rec : R->recs)
    {
        Print_Record(rec);
    }
}

void remove_dub_attr(Relation *Re)
{
    vector<int> vec;
    for (int i = 0; i < Re->get_nattr(); i++)
    {
        for (int j = i + 1; j < Re->get_nattr(); j++)
        {
            if (Re->attrnames[i] == Re->attrnames[j])
            {
                vec.push_back(j);
            }
        }
    }
    for (auto it : vec)
    {
        Re->attrnames[it] = "123";
    }
    for (auto it = Re->attrnames.begin(); it != Re->attrnames.end();)
    {
        if (*it == "123")
        {
            it = Re->attrnames.erase(it);
        }
        else
        {
            it++;
        }
    }
    cout<<"we reached here now"<<endl;
    Attr *at = new IntegerAttr(-1);
    for (auto rec : Re->recs)
    {
        for (auto it : vec)
        {   rec->attrptr[it]->print_Attr();
            cout<<endl;
            rec->attrptr[it] = at;
        }
    }
    for (auto rec : Re->recs)
    {
        for (auto it = rec->attrptr.begin(); it != rec->attrptr.end();)
        {
            if (*it == at)
            {
                it = (rec->attrptr).erase(it);
            }
            else
            {
                it++;
            }
        }
    }
    cout<<"we reached here now"<<endl;
    Re->nattr = (Re->attrnames).size();
    Print_Relation(Re);
}

void remove_dub_rec(Relation *Re)
{
    auto it = Re->recs.begin();
    cout << Re->get_nattr() << endl;
    auto it1 = it;
    for (it; it != Re->recs.end(); it++)
    {
        it1 = it;
        if (it1 != Re->recs.end())
            it1++;
        for (it1; it1 != Re->recs.end();)
        {
            int flag = 0;
            // cout << "check1" << endl;
            for (int i = 0; i < Re->get_nattr(); i++)
            {
                // cout << "check2" << endl;
                if (*((*it)->get_attvec()[i]) != *((*it1)->get_attvec()[i]))
                {
                    //  cout << "check3" << endl;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                // Record * r = *it1;
                it1 = Re->recs.erase(it1);
                // delete r;
            }
            else
            {
                it1++;
            }
        }
    }
}

void print_attribute(Relation *R)
{
    int i = 1;
    for (auto it : R->attrnames)
    {
        cout << i << ". " << it << endl;
        i++;
    }
}

void print_list(list<string> rel_schema)
{
    int i = 1;
    for (auto str : rel_schema)
    {
        cout << i << ". " << str << endl;
        i++;
    }
}

Relation *get_relation(list<Relation *> Re_list, int z)
{
    if (z > Re_list.size())
    {
        cout << "Index eneterd is not correct" << endl;
        return NULL;
    }
    auto it = Re_list.begin();
    for (int i = 0; i < z - 1; i++)
    {
        it++;
    }
    return *it;
}

string get_schema(list<string> str, int z)
{
    int i = 1;
    for (auto s : str)
    {
        if (i == z)
        {
            return s;
        }
        i++;
    }
}
