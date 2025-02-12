#include "FieldsForTypes.h"

// Default constructor
FieldsForTypes::FieldsForTypes() {}

// Constructor with initialization
FieldsForTypes::FieldsForTypes(const std::vector<std::vector<Field>> &fields) : fields_for_types(fields) {}

// Getter for the fields vector
std::vector<std::vector<Field>> &FieldsForTypes::getFields() {
    return fields_for_types;
}

// Overloaded operator for accessing fields by index
std::vector<Field> &FieldsForTypes::operator[](size_t index) {
    return fields_for_types[index];
}

// Setter for the fields vector
void FieldsForTypes::setFields(const std::vector<std::vector<Field>> &fields) {
    fields_for_types = fields;
}

// Constructor with size initialization
FieldsForTypes::FieldsForTypes(size_t size) : fields_for_types(size) {}
