#include "rdb.h"
using namespace std;

//Defination of Base class Attr
void Attr::print_Attr() const
{
    cout << "NOthin :>";
}
bool Attr::operator==(const Attr &right) const
{
    return *this == right;
}
bool Attr::operator!=(const Attr &right) const
{
    return !(*this == right);
}
bool Attr::operator>=(const Attr &right) const
{
    throw invalid_argument("Less than operator not defined for this attribute type.");
}
bool Attr::operator>(const Attr &right) const
{
    throw invalid_argument("Less than operator not defined for this attribute type.");
}
bool Attr::operator<=(const Attr &right) const
{
    throw invalid_argument("Less than operator not defined for this attribute type.");
}
bool Attr::operator<(const Attr &right) const
{
    throw invalid_argument("Less than operator not defined for this attribute type.");
}
//Defination of IntegerAttr
void IntegerAttr::print_Attr() const 
{
    cout << value;
}
bool IntegerAttr::operator>=(const Attr &right) const 
{
    return value >= dynamic_cast<const IntegerAttr &>(right).value;
}
bool IntegerAttr::operator==(const Attr &right) const 
{
    return value == dynamic_cast<const IntegerAttr &>(right).value;
}
bool IntegerAttr::operator!=(const Attr &right) const 
{
    return value != dynamic_cast<const IntegerAttr &>(right).value;
}
bool IntegerAttr::operator>(const Attr &right) const 
{
    return value > dynamic_cast<const IntegerAttr &>(right).value;
}
bool IntegerAttr::operator<=(const Attr &right) const 
{
    return value <= dynamic_cast<const IntegerAttr &>(right).value;
}
bool IntegerAttr::operator<(const Attr &right) const 
{
    return value < dynamic_cast<const IntegerAttr &>(right).value;
}
//Defination of FloatAttr
void FloatAttr::print_Attr() const 
{
    cout << value;
}
bool FloatAttr::operator>=(const Attr &right) const 
{
    return value >= dynamic_cast<const FloatAttr &>(right).value;
}
bool FloatAttr::operator==(const Attr &right) const 
{
    return value == dynamic_cast<const FloatAttr &>(right).value;
}
bool FloatAttr::operator!=(const Attr &right) const 
{
    return value != dynamic_cast<const FloatAttr &>(right).value;
}
bool FloatAttr::operator>(const Attr &right) const 
{
    return value > dynamic_cast<const FloatAttr &>(right).value;
}
bool FloatAttr::operator<=(const Attr &right) const 
{
    return value <= dynamic_cast<const FloatAttr &>(right).value;
}
bool FloatAttr::operator<(const Attr &right) const 
{
    return value < dynamic_cast<const FloatAttr &>(right).value;
}
//Defination of StringAttr 

void StringAttr::print_Attr() const 
{
    cout << value;
}
bool StringAttr::operator==(const Attr &right) const 
{
    return value == dynamic_cast<const StringAttr &>(right).value;
}
bool StringAttr::operator!=(const Attr &right) const 
{
    return value != dynamic_cast<const StringAttr &>(right).value;
}
bool StringAttr::operator>=(const Attr &right) const 
{
    return value >= dynamic_cast<const StringAttr &>(right).value;
}
bool StringAttr::operator>(const Attr &right) const 
{
    return value > dynamic_cast<const StringAttr &>(right).value;
}
bool StringAttr::operator<=(const Attr &right) const 
{
    return value <= dynamic_cast<const StringAttr &>(right).value;
}
bool StringAttr::operator<(const Attr &right) const 
{
    return value < dynamic_cast<const StringAttr &>(right).value;
}
