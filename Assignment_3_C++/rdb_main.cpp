#include "rdb.h"
using namespace std;

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
        cout << "7. To change the attribute name of the relation::"<<endl;
        cout << "8. To do the cartesian product of two relation" << endl;
        cout << "9. To do the projection in relation" << endl;
        cout << "10. To do the natural join of two relation" << endl;
        cout << "11. To do the operation on Relation table with DNF formula" << endl;
        cout <<"12. to exit press -1"<<endl;
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
            Attr_type.push_back(Attr_type[z-1]);
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
            Attr_type.push_back(Attr_type[z-1]);
        }
        else if(a==7){
            int z;
            cout<<"To change the attribute name of the schema choose the realtion::"<<endl;
            print_list(Rel_schema);
            cin>>z;
            int y;
            Relation * re = get_relation(Rel_list,z);
            cout<<"Choose the attribute which u want to change"<<endl;
            print_attribute(re);
            cin>>y;
            string s1 = re->attrnames[y-1];
            string s2;
            cout<<"Enter the new attribute name which should be in the place of ("<<s1<<")"<<endl;
            cin>>s2;
            Relation * output = difference(re,s1,s2);
            string str = get_schema(Rel_schema, z) + "-attribute_changed" ;
            Rel_list.push_back(output);
            Rel_schema.push_back(str);
           

        }
        else if (a == 8)
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
            vector<int>types;
            for(auto vec : Attr_type[z-1]){
                types.push_back(vec);
            }
            for(auto vec : Attr_type[y-1]){
                types.push_back(vec);
            }
            Attr_type.push_back(types);
            types.clear();
        }
        else if (a == 9)
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
        else if (a == 10)
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
        else if (a == 11)
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
                    cout << "Enter the operation (<(greater),>(less),!(not-equal),=(equal))" << endl;
                    cin >> o;
                    int v = Attr_type[z - 1][w - 1];
                    // cout<<v<<endl;
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
        }else if(a== -1){
            cout<<"The program is ended"<<endl;
            break;
        }
    }

    return 0;
}
