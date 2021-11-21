#pragma once

#include <string>
#include <vector>
using namespace std;

enum BUILTIN_TYPE
{
    VOID,
    INT8,
    UINT8,
    INT32,
    INT,
    UINT32,
    DOUBLE,
    STRUCT,
    UNKNOWN,
    STRING,
};

class Type
{
public:
    Type(const string &name = "", enum BUILTIN_TYPE type = UNKNOWN)
        : mName(name), mType(type) {}

    string mName;
    enum BUILTIN_TYPE mType;
    vector<Type> mFields; // for STRUCT only.
};
