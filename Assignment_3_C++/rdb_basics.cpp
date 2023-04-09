#include "rdb.h"
#include <typeinfo>
using namespace std;

void Record::addattr(Attr *attr)
{
    attrptr.push_back(attr);
}
vector<Attr *> Record::get_attvec()
{
    return attrptr;
}

int &Relation::get_nattr()
{
    return nattr;
}
int Relation::get_nrecs()
{
    return nattr;
}
vector<string> &Relation::get_attnvec()
{
    return attrnames;
}
void Relation::addrecs(Record *rec)
{
    recs.push_back(rec);
    nrecs++;
}
void Relation::removerecs(Record *rec)
{
    recs.remove(const_cast<Record *>(rec));
}
int Relation::get_attr_index(string attrname)
{
    int index = -1;
    for (int i = 0; i < nattr; i++)
    {
        if (attrname == attrnames[i])
        {
            index = i;
            break;
        }
    }
    return index;
}
Relation *unionop(Relation *R1, Relation *R2)
{
    if (R1->get_nattr() != R2->get_nattr())
    {
        cout << "Relation must have same no. of attribtes" << endl;
        return NULL;
    }
    else
    {
        for (int i = 0; i < R1->get_nattr(); i++)
        {

            if (R1->get_attnvec()[i] != R2->get_attnvec()[i])
            {
                cout << "Relation must have same no. of attribtes" << endl;
                return NULL;
            }
        }
        Relation *result = new Relation(R1->get_attnvec());
        for (auto r : R1->recs)
        {
            result->addrecs(r);
        }
        for (auto r : R2->recs)
        {

            result->addrecs(r);
        }
        remove_dub_rec(result);
        return result;
    }
}

Relation *difference(Relation *R1, Relation *R2)
{
    if (R1->get_nattr() != R2->get_nattr())
    {
        cout << "Relation must have same no. of attribtes" << endl;
        return NULL;
    }
    else
    {
        for (int i = 0; i < R1->get_nattr(); i++)
        {
            if (R1->get_attnvec()[i] != R2->get_attnvec()[i])
            {
                cout << "Relation must have same type of attribtes" << endl;
                return NULL;
            }
        }
        Relation *result = new Relation(R1->get_attnvec());
        int flag = 0;
        int n = R1->get_nattr();
        for (auto r1 : R1->recs)
        {
            flag = 1;
            for (auto r2 : R2->recs)
            {
                for (int i = 0; i < n; i++)
                {
                    if (typeid(*(r1->attrptr[i])) == typeid(IntegerAttr))
                    {
                        if(dynamic_cast<IntegerAttr*>(r1->attrptr[i])->value== dynamic_cast<IntegerAttr*>(r2->attrptr[i])->value){
                            flag=0;
                        }else{
                            flag=1;
                            break;
                        }
                    }
                    else if (typeid(*(r1->attrptr[i])) == typeid(StringAttr))
                    {
                        if(dynamic_cast<StringAttr*>(r1->attrptr[i])->value== dynamic_cast<StringAttr*>(r2->attrptr[i])->value){
                            flag=0;
                        }else{
                            flag=1;
                            break;
                        }
                    }
                    else if (typeid(*(r1->attrptr[i])) == typeid(FloatAttr))
                    {
                        if(dynamic_cast<FloatAttr*>(r1->attrptr[i])->value== dynamic_cast<FloatAttr*>(r2->attrptr[i])->value){
                            flag=0;
                        }else{
                            flag=1;
                            break;
                        }
                    }
                }
                if(flag==0){
                    break;
                }
            }
            if (flag == 1)
            {
                result->addrecs(r1);
            }
        }
        return result;
    }
}
Relation* difference(Relation * Re,string s1,string s2){
    Relation * re = new Relation(Re->attrnames);
    for(int i=0;i<re->nattr;i++){
        if(re->attrnames[i]==s1){
            re->attrnames[i]=s2;
        }
    }
    for(auto it:Re->recs){
        re->addrecs(it);
    }
    return re;
}
Relation *cartesianproduct(Relation *R1, Relation *R2)
{
    Relation *result = new Relation();
    for (auto aname : R1->get_attnvec())
    {
        result->get_attnvec().push_back(aname);
    }
    for (auto aname : R2->get_attnvec())
    {
        result->get_attnvec().push_back(aname);
    }
    result->get_nattr() = result->get_attnvec().size();
    for (auto r1 : R1->recs)
    {
        for (auto r2 : R2->recs)
        {
            Record *re = new Record;
            for (auto a : r1->get_attvec())
            {
                re->addattr(a);
            }
            for (auto a : r2->get_attvec())
            {
                re->addattr(a);
            }
            result->addrecs(re);
        }
    }
    // remove_dub_attr(result);
    return result;
}

Relation *projection(Relation *R, list<string> projattrs)
{
    // cout<<endl;
    vector<string> vec;
    vector<int> veci;
    for (auto str : projattrs)
    {
        vec.push_back(str);
        for (int i = 0; i < R->get_nattr(); i++)
        {
            // cout<<str;
            // cout<<R->attrnames[i]<<" ";
            if (str == R->get_attnvec()[i])
            {
                // cout<<"check";
                veci.push_back(i);
                break;
            }
        }
    }

    Relation *result = new Relation();
    for (int i = 0; i < vec.size(); i++)
    {
        result->get_attnvec().push_back(vec[i]);
    }
    result->get_nattr() = vec.size();
    // cout<<vec.size();
    for (auto rec : R->recs)
    {
        Record *re = new Record();
        // cout<<veci.size();
        for (auto i : veci)
        {
            // cout<<i<<endl;
            // rec->attrptr[i]->print_Attr();
            re->addattr(rec->get_attvec()[i]);
        }
        //    Print_Record(re);
        result->addrecs(re);
    }
    return result;
}

Relation *Union(Relation *R1, DNFformula *f)
{
    Relation *result = new Relation(R1->get_attnvec());
    result->get_nattr() = R1->get_nattr();
    for (auto op1 : f->ops)
    {
        Relation *temp = new Relation(R1->get_attnvec());
        temp->recs = R1->recs;
        for (auto conjen : op1)
        {
            string attrname = get<0>(conjen);
            char op = get<1>(conjen);
            Attr *val = get<2>(conjen);
            // cout << "check1" << attrname << endl;
            int index = temp->get_attr_index(attrname);
            // cout << "check2" << index << endl;
            if (index == -1)
            {
                cout << "Attribute name entered is wrong crash" << endl;
                return NULL;
            }
            for (auto it = temp->recs.begin(); it != temp->recs.end();)
            {
                Record *r = *it;
                Attr *recval = r->get_attvec()[index];
                bool match = false;
                switch (op)
                {
                case '=':
                    match = (*val == *recval);
                    break;

                case '!':
                    match = (*val != *recval);
                    break;

                case '<':
                    match = (*val < *recval);
                    // recval->print_Attr();
                    // cout<<endl;
                    // val->print_Attr();
                    break;

                case '>':
                    match = (*val > *recval);
                    // recval->print_Attr();
                    // cout<<endl;
                    // val->print_Attr();
                    break;

                default:
                    cout << "Invalid symbol output program crashed" << endl;
                    return NULL;
                    break;
                }
                if (!match)
                {
                    it = temp->recs.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
        result = unionop(result, temp);
    }
    return result;
}
