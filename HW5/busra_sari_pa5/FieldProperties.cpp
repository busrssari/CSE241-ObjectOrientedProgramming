#include "FieldProperties.h"

// Initialize static member variable
int FieldProperties::size = 0;

// Default constructor
FieldProperties::FieldProperties() {}

// Getter and setter methods for field name
std::string FieldProperties::getFieldName() const {
    return field_name;
}

void FieldProperties::setFieldName(const std::string &name) {
    field_name = name;
}

// Getter and setter methods for field type
std::string FieldProperties::getFieldType() const {
    return field_type;
}

void FieldProperties::setFieldType(const std::string &type) {
    field_type = type;
}

// Getter and setter methods for isArray flag
std::string FieldProperties::getIsArray() const {
    return is_array_or_not;
}

void FieldProperties::setIsArray(const std::string &isArray) {
    is_array_or_not = isArray;
}

// Method to increment the size
void FieldProperties::incSize() {
    size++;
}

// Static method to get the size
int FieldProperties::getSize() {
    return size;
}

// Method to check if a field name is recognized
bool FieldProperties::isRecognizedField(const std::string &fieldName) const {
    return fieldName == getFieldName();
}
