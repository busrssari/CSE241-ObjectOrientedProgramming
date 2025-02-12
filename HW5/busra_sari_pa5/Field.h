#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <vector>

class Field {
private:
    std::vector<std::string> values;

public:
    Field();

    std::vector<std::string> getValues() const;
    void setValues(const std::vector<std::string> &_values);
    void addValue(const std::string &value);
    bool search(const std::string &keyword) const;
};

#endif // FIELD_H
