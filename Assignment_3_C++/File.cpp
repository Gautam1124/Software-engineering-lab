#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <string>
#include <iterator>
using namespace std;
// BAse Class
class Attr
{
public:
    virtual void print_Attr() const
    {
        cout << "NOthin :>";
    }
    virtual bool operator==(const Attr &right) const
    {
        return *this == right;
    }
    virtual bool operator!=(const Attr &right) const
    {
        return !(*this == right);
    }
    virtual bool operator>=(const Attr &right) const
    {
        throw invalid_argument("Less than operator not defined for this attribute type.");
    }
    virtual bool operator>(const Attr &right) const
    {
        throw invalid_argument("Less than operator not defined for this attribute type.");
    }
    virtual bool operator<=(const Attr &right) const
    {
        throw invalid_argument("Less than operator not defined for this attribute type.");
    }
    virtual bool operator<(const Attr &right) const
    {
        throw invalid_argument("Less than operator not defined for this attribute type.");
    }
    virtual ~Attr() {}
};
class IntegerAttr : public Attr
{
    int value;

public:
    IntegerAttr(int val) : value(val){};
    void print_Attr() const override
    {
        cout << value;
    }
    bool operator>=(const Attr &right) const override
    {
        return value >= dynamic_cast<const IntegerAttr &>(right).value;
    }
    bool operator==(const Attr &right) const override
    {
        return value == dynamic_cast<const IntegerAttr &>(right).value;
    }
    bool operator!=(const Attr &right) const override
    {
        return value != dynamic_cast<const IntegerAttr &>(right).value;
    }
    bool operator>(const Attr &right) const override
    {
        return value > dynamic_cast<const IntegerAttr &>(right).value;
    }
    bool operator<=(const Attr &right) const override
    {
        return value <= dynamic_cast<const IntegerAttr &>(right).value;
    }
    bool operator<(const Attr &right) const override
    {
        return value < dynamic_cast<const IntegerAttr &>(right).value;
    }
};
class FloatAttr : public Attr
{
    float value;

public:
    FloatAttr(float val) : value(val){};
    void print_Attr() const override
    {
        cout << value;
    }
    bool operator>=(const Attr &right) const override
    {
        return value >= dynamic_cast<const FloatAttr &>(right).value;
    }
    bool operator==(const Attr &right) const override
    {
        return value == dynamic_cast<const FloatAttr &>(right).value;
    }
    bool operator!=(const Attr &right) const override
    {
        return value != dynamic_cast<const FloatAttr &>(right).value;
    }
    bool operator>(const Attr &right) const override
    {
        return value > dynamic_cast<const FloatAttr &>(right).value;
    }
    bool operator<=(const Attr &right) const override
    {
        return value <= dynamic_cast<const FloatAttr &>(right).value;
    }
    bool operator<(const Attr &right) const override
    {
        return value < dynamic_cast<const FloatAttr &>(right).value;
    }
};
class StringAttr : public Attr
{
    string value;

public:
    void print_Attr() const override
    {
        cout << value;
    }
    StringAttr(string val) : value(val){};
    bool operator==(const Attr &right) const override
    {
        return value == dynamic_cast<const StringAttr &>(right).value;
    }
    bool operator!=(const Attr &right) const override
    {
        return value != dynamic_cast<const StringAttr &>(right).value;
    }
    bool operator>=(const Attr &right) const override
    {
        return value >= dynamic_cast<const StringAttr &>(right).value;
    }
    bool operator>(const Attr &right) const override
    {
        return value > dynamic_cast<const StringAttr &>(right).value;
    }
    bool operator<=(const Attr &right) const override
    {
        return value <= dynamic_cast<const StringAttr &>(right).value;
    }
    bool operator<(const Attr &right) const override
    {
        return value < dynamic_cast<const StringAttr &>(right).value;
    }
};

class Record
{
    vector<Attr *> attrptr;

public:
    void addattr(Attr *attr)
    {
        attrptr.push_back(attr);
    }
    vector<Attr *> get_attvec()
    {
        return attrptr;
    }
    ~Record()
    {
        int n = attrptr.size();
        for (int i = 0; i < n; i++)
            delete attrptr[i];
    }
};

class Relation
{
    int nattr, nrecs;
    vector<string> attrnames;

public:
    vector<int> attrinds;
    list<Record *> recs;

    Relation() {}
    Relation(vector<string> &attrname) : attrnames(attrname), nrecs(0)
    {
        nattr = attrnames.size();
        for (int i = 0; i < nattr; i++)
        { // cout<<attrnames[i]<<" ";
            attrinds.push_back(i);
        }
    }
    int &get_nattr()
    {
        return nattr;
    }
    int get_nrecs()
    {
        return nattr;
    }
    vector<string>& get_attnvec(){
        return attrnames;
    }
    void addrecs(Record *rec)
    {
        recs.push_back(rec);
        nrecs++;
    }
    void removerecs(Record *rec)
    {
        recs.remove(const_cast<Record *>(rec));
    }
    int get_attr_index(string attrname)
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
};

void Print_Relation(Relation *R);
void Print_Record(Record *R);
void remove_dub_attr(Relation *Re)
{
    vector<int> vec;
    for (int i = 0; i < Re->get_nattr(); i++)
    {
        for (int j = i + 1; j < Re->get_nattr(); j++)
        {
            if (Re->get_attnvec()[i] == Re->get_attnvec()[j])
            {
                vec.push_back(j);
            }
        }
    }
    for (auto it : vec)
    {
        Re->get_attnvec()[it] = "123";
    }
    for (auto it = Re->get_attnvec().begin(); it != Re->get_attnvec().end();)
    {
        if (*it == "123")
        {
            it = Re->get_attnvec().erase(it);
        }
        else
        {
            it++;
        }
    }
    IntegerAttr *at = new IntegerAttr(-1);
    for (auto rec : Re->recs)
    {
        int i = 0;
        for (auto it : vec)
        {
            rec->get_attvec()[it] = at;
        }
    }
    for (auto rec : Re->recs)
    {
        for (auto it = rec->get_attvec().begin(); it != rec->get_attvec().end();)
        {
            if (*it == at)
            {
                it = rec->get_attvec().erase(it);
            }
            else
            {
                it++;
            }
        }
    }
    Re->get_nattr() = Re->get_attnvec().size();
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
bool check_same_record(Record *R1, Record *R2)
{
    if (R1->get_attvec().size() != R2->get_attvec().size())
        return false;
    for (int i = 0; i < R1->get_attvec().size(); i++)
    {
        if (*(R1->get_attvec()[i]) != *(R2->get_attvec()[i]))
        {
            return false;
        }
    }
    return true;
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
        for (auto r1 : R1->recs)
        {
            flag = 1;
            for (auto r2 : R2->recs)
            {
                if (r1 == r2)
                {
                    flag = 0;
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
struct DNFformula
{
    list<list<tuple<string, char, Attr *>>> ops;
};

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
    remove_dub_attr(result);
    return result;
}

void Print_Record(Record *R)
{
    vector<Attr *> vec = R->get_attvec();
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
    vector<string> vec = R->get_attnvec();
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
void print_attribute(Relation *R)
{
    int i = 1;
    for (auto it : R->get_attnvec())
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

int main()
{
    // vector<string> attnames  {"name","id","age","gender"};
    // // for(int i=0;i<attnames.size();i++){
    // //     cout<<attnames[i];
    // // }
    // StringAttr strname("john");
    // IntegerAttr id(123);
    // IntegerAttr age(23);
    // StringAttr gen("male");

    // Record R;
    // R.addattr(&strname);
    // R.addattr(&id);
    // R.addattr(&age);
    // R.addattr(&gen);
    // // Print_Record(&R);

    // Relation Re(attnames);
    // // cout<<"check";
    // Re.addrecs(&R);
    // Print_Relation(&Re);
    // cout<<endl;

    // StringAttr strname1("johny");
    // IntegerAttr id1(1234);
    // IntegerAttr age1(231);
    // StringAttr gen1("male");
    // Relation Re1(attnames);
    // Record R1;
    // R1.addattr(&strname1);
    // R1.addattr(&id1);
    // R1.addattr(&age1);
    // R1.addattr(&gen1);
    // Re1.addrecs(&R1);
    // Print_Relation(&Re1);
    // Relation *ptr;
    // ptr = unionop(&Re,&Re1);
    // Print_Relation(ptr);
    // cout<<endl;
    // // ptr = difference(ptr,&Re);
    // // Print_Relation(ptr);

    // vector<string> vec {"company_name","salary"};
    // StringAttr sr("Google");
    // IntegerAttr sa(12000);
    // Record R3;
    // R3.addattr(&sr);
    // R3.addattr(&sa);
    // Relation Re2(vec);
    // Re2.addrecs(&R3);
    // Print_Relation(&Re2);
    // cout<<endl;
    // ptr = cartesianproduct(ptr,&Re2);
    // Print_Relation(ptr);
    // list<string> li;
    // li.push_back("name");
    // li.push_back("id");
    // li.push_back("company_name");
    // ptr = projection(ptr,li);
    // // cout<<ptr->nattr<<endl;
    // // cout<<endl;
    // Print_Relation(ptr);
    list<Relation *> Rel_list;
    list<string> Rel_schema;
    vector<vector<int>> Attr_type;
    int t;
    cout << "For doing the relational algebra operation on scheama if u want to store all the attribute in the form of string press1 or if u want to store them in their respective attribute press 0:" << endl;
    cin >> t;
    while (1)
    {
        int a;
        cout << "1. To create an empty table" << endl;
        cout << "2. To delete the existing table" << endl;
        cout << "3. To add a record to a table" << endl;
        cout << "4. To print the Table" << endl;
        cout << "5. To do the union of two tables" << endl;
        cout << "6. To do the Difference of two relation::" << endl;
        cout << "7. To do the cartesian product of two relation" << endl;
        cout << "8. To do the projection in relation" << endl;
        cout << "9. To do the natural join of two relation" << endl;
        cout << "10. To do the operation on Relation table with DNF formula" << endl;
        cin >> a;
        if (a == 1)
        {
            string str;
            vector<string> att;
            vector<int> attt;
            int n;
            cout << "Enter the Schema name for this table" << endl;
            cin >> str;
            Rel_schema.push_back(str);
            cout << "Enter the no. of attribute names in the table" << endl;
            cin >> n;
            vector<int> dt;
            cout << "Enter the Attribute names in the table" << endl;
            int ele;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter the " << i + 1 << " Attribute name" << endl;
                cin >> str;
                if (t == 0)
                {
                    cout << "choose the data type of the attribute: " << str << endl;
                    cout << "1.Integer  "
                         << " 2.Float  "
                         << " 3.String" << endl;
                    cin >> ele;
                    dt.push_back(ele);
                }
                att.push_back(str);
            }
            Attr_type.push_back(dt);
            Relation *rela = new Relation(att);
            Rel_list.push_back(rela);
        }
        else if (a == 2)
        {
            if (Rel_list.size() == 0)
            {
                cout << "Currently there is no table in the List Sorry :(" << endl;
                continue;
            }
            int z;
            cout << "For deleting Table choose which Table u want to delete" << endl;
            print_list(Rel_schema);
            cin >> z;
            auto it1 = Rel_list.begin();
            auto it2 = Rel_schema.begin();
            auto it3 = Attr_type.begin();
            it3 = it3 + (z - 1);
            while (z > 1)
            {
                it1++;
                it2++;
                z--;
            }
            it1 = Rel_list.erase(it1);
            it2 = Rel_schema.erase(it2);
            it3 = Attr_type.erase(it3);
            cout << Attr_type.size();
            cout << "The list is deleted :)" << endl
                 << endl;
        }
        else if (a == 3)
        {
            int z;
            cout << "For entering the record choose the schema" << endl;
            print_list(Rel_schema);
            cin >> z;
            Relation *re = get_relation(Rel_list, z);
            if (t == 1)
            {
                vector<string> &att = re->get_attnvec();
                int n = re->get_nattr();
                Record *rec = new Record();
                string in;
                for (int i = 0; i < n; i++)
                {
                    cout << "Enter the attribute value for :: " << att[i] << endl;
                    cin >> in;
                    StringAttr *satr = new StringAttr(in);
                    rec->addattr(satr);
                }
                re->addrecs(rec);
            }
            else if (t == 0)
            {
                vector<int> at = Attr_type[z - 1];
                vector<string> &att = re->get_attnvec();
                int n = re->get_nattr();
                Record *rec = new Record();
                int ele;
                float ele1;
                string ele2;
                for (int i = 0; i < n; i++)
                {
                    cout << "Enter the attribute value for ::  (" << att[i];
                    if (at[i] == 1)
                    {
                        cout << ") of INTEGER data type" << endl;
                        cin >> ele;
                        IntegerAttr *iattr = new IntegerAttr(ele);
                        rec->addattr(iattr);
                    }
                    else if (at[i] == 2)
                    {
                        cout << ") of FLOAT data type" << endl;
                        cin >> ele1;
                        FloatAttr *fattr = new FloatAttr(ele1);
                        rec->addattr(fattr);
                    }
                    else if (at[i] == 3)
                    {
                        cout << ") of STRING type::" << endl;
                        cin >> ele2;
                        StringAttr *sattr = new StringAttr(ele2);
                        rec->addattr(sattr);
                    }
                }
                re->addrecs(rec);
            }
        }
        else if (a == 4)
        {
            if (Rel_list.size() == 0)
            {
                cout << "Relation list is empty (No table found)=> :(" << endl;
                continue;
            }
            int z;
            cout << "For printing choose the schema to print" << endl;
            print_list(Rel_schema);
            cin >> z;
            Relation *re = get_relation(Rel_list, z);
            Print_Relation(re);
        }
        else if (a == 5)
        {
            int z, y;
            cout << "For doing union chooose two schema ::" << endl;
            print_list(Rel_schema);
            cin >> z >> y;
            // cout<<str;
            Relation *re1 = get_relation(Rel_list, z);
            Relation *re2 = get_relation(Rel_list, y);
            Relation *output = unionop(re1, re2);
            Rel_list.push_back(output);
            string str = get_schema(Rel_schema, z) + "-union-" + get_schema(Rel_schema, y);
            Rel_schema.push_back(str);
        }
        else if (a == 6)
        {
            int z, y;
            cout << "For doing Difference choose two schema" << endl;
            print_list(Rel_schema);
            cin >> z >> y;
            Relation *re1 = get_relation(Rel_list, z);
            Relation *re2 = get_relation(Rel_list, y);
            Relation *output = difference(re1, re2);
            string str = get_schema(Rel_schema, z) + "-difference-" + get_schema(Rel_schema, y);
            Rel_list.push_back(output);
            Rel_schema.push_back(str);
        }
        else if (a == 7)
        {
            int z, y;
            cout << "For cartesian product choose two schema" << endl;
            print_list(Rel_schema);
            cin >> z >> y;
            Relation *re1 = get_relation(Rel_list, z);
            Relation *re2 = get_relation(Rel_list, y);
            Relation *output = cartesianproduct(re1, re2);
            string str = get_schema(Rel_schema, z) + "-Cartesian.Product-" + get_schema(Rel_schema, y);
            Rel_list.push_back(output);
            Rel_schema.push_back(str);
        }
        else if (a == 8)
        {
            int z;
            cout << "For doing Projection choose the schema::" << endl;
            print_list(Rel_schema);
            cin >> z;
            Relation *re = get_relation(Rel_list, z);
            int y;

            cout << "To choose the attribute first enter the no. of attribbute u want to pass for projections" << endl;
            print_attribute(re);
            cin >> y;
            cout << "Now Enter" << y << " index(sorted order) corresponding to the atribute u want in projeattr list" << endl;
            vector<int> index;
            int ele;
            for (int i = 0; i < y; i++)
            {
                cin >> ele;
                index.push_back(ele);
            }
            list<string> st;
            for (auto el : index)
            {
                st.push_back(re->get_attnvec()[el - 1]);
            }
            Relation *output = projection(re, st);
            Rel_list.push_back(output);
            string str = get_schema(Rel_schema, z) + "-Projection";
            Rel_schema.push_back(str);
        }
        else if (a == 9)
        {
            int z, x;
            cout << "Enter the index of two relation u want to choose for the doing naturalJoin" << endl;
            print_list(Rel_schema);
            cin >> z >> x;
            Relation *re1 = get_relation(Rel_list, z);
            Relation *re2 = get_relation(Rel_list, x);
            int y;
            cout << "For doing natural join Enter the no. of attribute which are common in both of the relation" << endl;
            cout << "Attributes of 1st relation is::" << endl;
            print_attribute(re1);
            cout << endl
                 << endl;
            cout << "Attribute of 2nd relation is::" << endl;
            print_attribute(re2);
            cout << endl;
            cout << "Enter the no. of attribute which are common::" << endl;
            cin >> y;
            cout << "Now Enter" << y << " index(sorted order) corresponding to the common atribute u want in joinattr list with respect to the first relation" << endl;
            vector<int> index;
            int ele;
            for (int i = 0; i < y; i++)
            {
                cin >> ele;
                index.push_back(ele);
            }
            list<string> st;
            for (auto el : index)
            {
                st.push_back(re1->get_attnvec()[el - 1]);
            }
            Relation *output = naturaljoin(re1, re2, st);
            Rel_list.push_back(output);
            string str = get_schema(Rel_schema, z) + "-natural.Join-" + get_schema(Rel_schema, x);
            Rel_schema.push_back(str);
        }
        else if (a == 10)
        {
            int z;
            cout << "Enter the index of relation u want to choose for the doing DNFformula" << endl;
            print_list(Rel_schema);
            cin >> z;
            Relation *re = get_relation(Rel_list, z);
            cout << "DNF formula is of form <list<list<tuple<string,char,Attr*>>> it is of a list of list form where the outer list contains the list which will be conjuctive while all the list within the list will be disjunctitive with each other :)" << endl;
            cout << "Enter the no. of list u want to enter which are disjunctive to the Relation" << endl;
            int y;
            cin >> y;
            DNFformula f;
            for (int i = 0; i < y; i++)
            {
                cout << "Enter the no. of tuple u want to be inside the (" << i + 1 << ") list for the conjunctive operation" << endl;
                int x;
                cin >> x;
                list<tuple<string, char, Attr *>> op;
                for (int j = 0; j < x; j++)
                {
                    int w;
                    cout << "Choose the attribute to include in the tuple" << endl;
                    print_attribute(re);
                    cin >> w;
                    string str = re->get_attnvec()[w - 1];
                    char o;
                    cout << "Enter the operation (<,>,!,=)" << endl;
                    cin >> o;
                    int v = Attr_type[z - 1][w - 1];
                    if (v == 1)
                    {
                        int ele;
                        cout << "Enter the attribute value for " << re->get_attnvec()[w - 1] << " of INTEGER type" << endl;
                        cin >> ele;
                        IntegerAttr *at = new IntegerAttr(ele);
                        op.push_back({str, o, at});
                    }
                    else if (v == 2)
                    {
                        float ele;
                        cout << "Enter the attribute value for " << re->get_attnvec()[w - 1] << " of FLOAT type" << endl;
                        cin >> ele;
                        FloatAttr *at = new FloatAttr(ele);
                        op.push_back({str, o, at});
                    }
                    else if (v == 3)
                    {
                        string ele;
                        cout << "Enter the attribute value for " << re->get_attnvec()[w - 1] << " of FLOAT type" << endl;
                        cin >> ele;
                        StringAttr *at = new StringAttr(ele);
                        op.push_back({str, o, at});
                    }
                }
                f.ops.push_back(op);
                op.clear();
            }

            Relation *result = Union(re, &f);
            Rel_list.push_back(result);
            string s = get_schema(Rel_schema,z) + "-DNFoperation";
            Rel_schema.push_back(s);

            // DNFformula f;
            // list<tuple<string, char, Attr *>> op1 = {{"id", '<', new IntegerAttr(2)}, {"salary", '>', new FloatAttr(120)}};
            // f.ops.push_back(op1);
            // Relation *re1 = get_relation(Rel_list, 1);
            // Relation *ne = Union(re1, &f);
            // Print_Relation(ne);
        }
    }

    return 0;
}
