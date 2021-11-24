#pragma once
#include <string.h>
#include <iostream>
#include "Type.hpp"
using namespace std;
class Variable
{
public:
    string mName;
    Type type;
    long long INT;
    long double DOUBLE;
    string STRING;
    void debugPrint() const;
private:

};