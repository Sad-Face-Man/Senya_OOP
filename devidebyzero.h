#ifndef DEVIDEBYZERO_H
#define DEVIDEBYZERO_H

//#include <exception>
#include <QString>


class DevideByZero
{
private:
    QString windowName = "Ошибка деления на ноль.";
    QString errorName;
public:
    DevideByZero(QString);
    QString what() const throw();
};

#endif // DEVIDEBYZERO_H
