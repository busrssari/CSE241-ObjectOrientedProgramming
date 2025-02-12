#ifndef FIELDPROPERTIES_H
#define FIELDPROPERTIES_H

#include <string>
#include <vector>

class FieldProperties {
private:
    std::string field_name;
    std::string field_type;
    std::string is_array_or_not;
    static int size;

public:
    FieldProperties();

    std::string getFieldName() const;
    void setFieldName(const std::string &name);

    std::string getFieldType() const;
    void setFieldType(const std::string &type);

    std::string getIsArray() const;
    void setIsArray(const std::string &isArray);

    static void incSize();
    static int getSize();

    bool isRecognizedField(const std::string &fieldName) const;
};

#endif // FIELDPROPERTIES_H
