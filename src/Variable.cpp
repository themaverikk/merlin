#include "Variable.hpp"
#include <iostream>
void Variable::debugPrint() const {
    cout << "variable name: " << mName << endl;
    cout<<"variable Type: " <<  type.mName <<endl;
    if(type.mName=="INT") cout << "variable value: " << INT <<endl;
    if(type.mName=="DOUBLE") cout << "variable value: " << DOUBLE <<endl;
    if(type.mName=="STRING") cout << "variable value: " << STRING <<endl;

}