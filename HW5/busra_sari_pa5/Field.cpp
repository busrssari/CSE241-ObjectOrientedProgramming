#include "Field.h"

// Default constructor
Field::Field() {}

// Getter method for values
std::vector<std::string> Field::getValues() const {
    return values;
}

// Setter method for values
void Field::setValues(const std::vector<std::string> &_values) {
    values = _values;
}

// Method to add a value to the field
void Field::addValue(const std::string &value) {
    values.push_back(value);
}

// Method to search for a keyword within the field values
bool Field::search(const std::string &keyword) const {
    for (const auto &value : values) {
        if (value.find(keyword) != std::string::npos) {
            return true;
        }
    }
    return false;
}
