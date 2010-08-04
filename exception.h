#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class Exception
{
public:
    Exception(QString message): _message(message) {}
    inline QString message() { return _message; }

private:
    QString _message;
};

#endif // EXCEPTION_H
