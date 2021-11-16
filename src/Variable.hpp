using namespace std;
#include <string.h>
#include "Type.hpp"
typedef union Value
{
    int INT;
    string STRING;
    double DOUBLE;
} variableValue;
class Variable
{
public:
    Type type;
    variableValue value;

private:
};