#include "devidebyzero.h"

DevideByZero::DevideByZero(QString err)
{
    errorName = err;
}

QString DevideByZero::what() const throw()
{
    return errorName;
}
