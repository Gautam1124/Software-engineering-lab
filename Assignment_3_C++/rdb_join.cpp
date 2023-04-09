#include "rdb.h"
using namespace std;

Relation *naturaljoin(Relation *Re1, Relation *Re2, list<string> joinattr)
{
    Relation *result = cartesianproduct(Re1, Re2);
    Print_Relation(result);
    vector<int> vec1;
    vector<int> vec2;
    for (auto str : joinattr)
    {
        cout << "Check1::" << str << endl;
        int flag = 0, i = 0;
        for (auto att1 : result->get_attnvec())
        {
            cout << "check2::" << att1 << endl;
            if (flag == 0 && str == att1)
            {
                vec1.push_back(i);
                flag = 1;
                cout << "Check3::" << i << endl;
            }
            else if (str == att1)
            {
                vec2.push_back(i);
                cout << "Check4::" << i << endl;
            }
            i++;
        }
    }
    for (auto it = result->recs.begin(); it != result->recs.end();)
    {
        int flag = 1;
        for (int i = 0; i < vec1.size(); i++)
        {
            if (*((*it)->get_attvec()[vec1[i]]) != *((*it)->get_attvec()[vec2[i]]))
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
        {
            it = result->recs.erase(it);
        }
        else
        {
            it++;
        }
    }
    cout<<"Hello that muchn is completed whats next"<<endl;
    remove_dub_attr(result);
    return result;
}