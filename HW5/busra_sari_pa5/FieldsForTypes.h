#ifndef FIELDSFORTYPES_H
#define FIELDSFORTYPES_H

#include "Field.h"
#include <vector>

class FieldsForTypes {
private:
    std::vector<std::vector<Field>> fields_for_types;

public:
    FieldsForTypes();
    FieldsForTypes(const std::vector<std::vector<Field>> &fields);

    std::vector<std::vector<Field>> &getFields();
    std::vector<Field> &operator[](size_t index);
    void setFields(const std::vector<std::vector<Field>> &fields);
    FieldsForTypes(size_t size);
};

#endif // FIELDSFORTYPES_H
