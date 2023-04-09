#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <string>
#include <iterator>

class Attr{
public:
    virtual void print_Attr() const = 0;
    virtual bool operator>=(const Attr &right) const = 0;
    virtual bool operator==(const Attr &right) const = 0;
    virtual bool operator!=(const Attr &right) const = 0;
    virtual bool operator>(const Attr &right) const = 0;
    virtual bool operator<=(const Attr &right) const = 0;
    virtual bool operator<(const Attr &right) const = 0;
};

// IntegerAttr class declaration
class IntegerAttr : public Attr {
public:
    int value;
    IntegerAttr(int val) : value(val){};
    void print_Attr() const override;
    bool operator>=(const Attr &right) const override;
    bool operator==(const Attr &right) const override;
    bool operator!=(const Attr &right) const override;
    bool operator>(const Attr &right) const override;
    bool operator<=(const Attr &right) const override;
    bool operator<(const Attr &right) const override;
};


class FloatAttr : public Attr {
public:
    float value;
    FloatAttr(float val) : value(val){};
    void print_Attr() const override;
    bool operator>=(const Attr &right) const override;
    bool operator==(const Attr &right) const override;
    bool operator!=(const Attr &right) const override;
    bool operator>(const Attr &right) const override;
    bool operator<=(const Attr &right) const override;
    bool operator<(const Attr &right) const override;
};

class StringAttr : public Attr {
public:
    std::string value;
    StringAttr(std::string val) : value(val){};
    void print_Attr() const override;
    bool operator>=(const Attr &right) const override;
    bool operator==(const Attr &right) const override;
    bool operator!=(const Attr &right) const override;
    bool operator>(const Attr &right) const override;
    bool operator<=(const Attr &right) const override;
    bool operator<(const Attr &right) const override;
};

class Record{
    public:
    std::vector<Attr*> attrptr;
    void addattr(Attr*);
    std::vector<Attr*> get_attvec();
    ~Record(){
        int n = attrptr.size();
        for(int i=0;i<n;i++){
            delete attrptr[i];
        }
    }
};

class Relation
{

public:
    int nattr, nrecs;
    std::vector<std::string> attrnames;
    std::vector<int> attrinds;
    std::list<Record *> recs;

    Relation() : nattr(0), nrecs(0) {}

    Relation(std::vector<std::string> &attrname) : attrnames(attrname), nrecs(0)
    {
        nattr = attrnames.size();
        for (int i = 0; i < nattr; i++)
        { 
            attrinds.push_back(i);
        }
    }

    int& get_nattr();
    int get_nrecs();
    std::vector<std::string>& get_attnvec();
    void addrecs(Record* rec);
    void removerecs(Record* rec);
    int get_attr_index(std::string attrname);
};

void Print_Relation(Relation *);
void Print_Record(Record *);
void remove_dub_attr(Relation *);
void remove_dub_rec(Relation *);

Relation *unionop(Relation *R1, Relation *R2);
Relation *difference(Relation *R1, Relation *R2);
Relation *difference(Relation *R1, std::string s1,std::string s2);
Relation *cartesianproduct(Relation *R1, Relation *R2);
Relation *projection(Relation *R, std::list<std::string> projattrs);

struct DNFformula
{
    std::list<std::list<std::tuple<std::string, char, Attr *>>> ops;
};
Relation *Union(Relation *R1, DNFformula *f);
Relation *naturaljoin(Relation *Re1, Relation *Re2, std::list<std::string> joinattr);
void print_attribute(Relation *R);
void print_list(std::list<std::string> rel_schema);
Relation *get_relation(std::list<Relation *> Re_list, int z);
std::string get_schema(std::list<std::string> str, int z);




