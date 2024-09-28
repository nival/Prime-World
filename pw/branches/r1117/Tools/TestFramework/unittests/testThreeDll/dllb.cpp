#include "dll.h"
#include "dllb.h"

std::string getStrB()
{
    std::string c = getStr();
    std::string b("B!");

    return c+b;
}