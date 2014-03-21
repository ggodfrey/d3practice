#include <vector>
#include "FunctionRegistry.h"

FunctionRegistry::FunctionRegistry()
{
    printf("FunctionRegistry construct\n");
}

FunctionRegistry::~FunctionRegistry()
{

}

void FunctionRegistry::updateFunctions()
{
    for(unsigned int j = 0; j < instances.size(); j++)
    {
        //in the format of f(object)
        (functions.at(j))(instances.at(j));
    }
}

void FunctionRegistry::addFunctions(functionName funk, instType funkObj)
{
    instances.push_back(funkObj);
    functions.push_back(funk);
}
