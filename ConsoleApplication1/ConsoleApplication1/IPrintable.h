#ifndef IPRINTABLE_H
#define IPRINTABLE_H

#include <string>

class IPrintable {
public:
    virtual void print() const = 0;
    virtual std::string toCSV() const = 0;
    virtual ~IPrintable() {}
};

#endif
