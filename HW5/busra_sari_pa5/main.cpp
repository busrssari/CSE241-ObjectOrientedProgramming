#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "FieldProperties.h"
#include "Field.h"
#include "FieldsForTypes.h"

using namespace std;

// Function declarations
vector<vector<Field>> parseLine(const string &line, const vector<FieldProperties> &fieldProperties);
vector<FieldProperties> parseFirstLine(const string &templateStr);
void swap(vector<Field> &a, vector<Field> &b);
void isDuplicateEntry(const string &line, const vector<string> &lines);
void checkMissingField(const string &line, size_t expectedFields);
void validateCommandFormat(const std::string &commandType, const std::string &command);
void validatesearchCommand(const string &commandType, const string &keyword, const string &fieldName, vector<FieldProperties> &fieldProperties);
void validateSortCommand(const string &commandType, const string &fieldName, vector<FieldProperties> &fieldProperties);
void searchForKeyword(const string &keyword, const string &fieldName, const vector<FieldProperties> &fieldProperties, FieldsForTypes &fieldsForTypes, const vector<string> &lines);
void sortForKeyword(const string &fieldName, const vector<FieldProperties> &fieldProperties, FieldsForTypes &fieldsForTypes, const vector<string> &lines);


int main() {
    // Open the data file
    ifstream dataFile("data.txt");
    if (!dataFile.is_open()) {
        cerr << "Failed to open the file!" << endl;
        return 1;
    }

    // Read the first line of the data file to extract field properties
    string firstLine;
    getline(dataFile, firstLine);

    vector<FieldProperties> fieldProperties = parseFirstLine(firstLine);

    // Output the field names
    for (size_t i = 0; i < fieldProperties.size(); ++i) {
        cout << fieldProperties[i].getFieldName();
        if (i < fieldProperties.size() - 1) {
            cout << "|";
        } else {
            cout << endl;
        }
    }

    string line;
    int numOfLine = 0;
    vector<string> lines;
    int numOfField = FieldProperties::getSize();
    FieldsForTypes fieldsForTypes(numOfField);

    // Parse each line of the data file
    while (getline(dataFile, line)) {
        try {
            // Check for duplicate entries and missing fields
            isDuplicateEntry(line, lines);
            checkMissingField(line, numOfField);

            lines.push_back(line);
            numOfLine++;

            // Parse the line and store the fields
            FieldsForTypes parsedLine = parseLine(line, fieldProperties);

            for (int i = 0; i < numOfField; i++) {
                for (const auto &field : parsedLine[i]) {
                    fieldsForTypes[i].push_back(field);
                }
            }
        } catch (const exception &ex) {
            cout << line << endl;
            cerr << ex.what() << endl;
            continue;
        }
    }

    dataFile.close();

    cout << numOfLine << " unique entries" << endl;

    // Open the commands file
    ifstream commandsFile("commands.txt");
    if (!commandsFile.is_open()) {
        cerr << "Failed to open commands.txt!" << endl;
        return 1;
    }

    string commandLine;
    // Process each command from the commands file
    while (getline(commandsFile, commandLine)) {
        try {
            istringstream iss(commandLine);
            string commandType;
            iss >> commandType;
            validateCommandFormat(commandType, commandLine);

            if (commandType == "search") {
                string keyword, fieldName;

                // Extract keyword and field name from the command line
                size_t pos1 = commandLine.find('"');
                size_t pos2 = commandLine.find('"', pos1 + 1);
                if (pos1 != string::npos && pos2 != string::npos) {
                    keyword = commandLine.substr(pos1 + 1, pos2 - pos1 - 1);
                }
                size_t pos3 = commandLine.find('"', pos2 + 1);
                size_t pos4 = commandLine.find('"', pos3 + 1);
               
                if (pos3 != string::npos && pos4 != string::npos) {
                    fieldName = commandLine.substr(pos3 + 1, pos4 - pos3 - 1);
                }
                // Validate the search command and execute it
                validatesearchCommand(commandType, keyword, fieldName, fieldProperties);
                cout << commandLine << endl;
                searchForKeyword(keyword, fieldName, fieldProperties, fieldsForTypes, lines);
            }
            if (commandType == "sort") {
                string fieldName;
                // Extract the field name from the command line
                size_t pos1 = commandLine.find('"');
                size_t pos2 = commandLine.find('"', pos1 + 1);
                if (pos1 != string::npos && pos2 != string::npos) {
                    fieldName = commandLine.substr(pos1 + 1, pos2 - pos1 - 1);
                }
                // Validate the sort command and execute it
                validateSortCommand(commandType, fieldName, fieldProperties);
                cout << commandLine << endl;
                sortForKeyword(fieldName, fieldProperties, fieldsForTypes, lines);
            }
        } catch (const exception &ex) {
            cout << commandLine << endl;
            cerr << ex.what() << endl;
        }
    }

    commandsFile.close();
    return 0;
}



// Function to parse a single line of data based on the given field properties
vector<vector<Field>> parseLine(const string &line, const vector<FieldProperties> &fieldProperties)
{
    // Initialize an object to store fields for different types
    FieldsForTypes fieldsObj(fieldProperties.size());
    istringstream iss(line);
    string token;
    size_t index = 0;

    // Parse the line based on the delimiter '|'
    while (getline(iss, token, '|'))
    {
        // Check if the index is within the range of field properties
        if (index >= fieldProperties.size())
        {
            cerr << "Error: Template line index out of range." << endl;
            break;
        }
        // Get the field properties for the current index
        FieldProperties field = fieldProperties[index];
        Field aField;
        istringstream fieldStream(token);
        string value;

        // Determine if the field is a single or multi-value field and parse accordingly
        if (field.getIsArray() == "single")
        {
            getline(fieldStream, value, '|');
            aField.addValue(value);
        }
        else if (field.getIsArray() == "multi")
        {
            while (getline(fieldStream, value, ':'))
            {
                aField.addValue(value);
            }
        }

        // Store the parsed field in the appropriate index of the fields object
        fieldsObj.getFields()[index].push_back(aField);
        index++;
    }

    return fieldsObj.getFields();
}

// Function to parse the first line of the data file to extract field properties
vector<FieldProperties> parseFirstLine(const string &templateStr)
{
    vector<FieldProperties> fields;
    istringstream iss(templateStr);
    string token;
    while (getline(iss, token, '|'))
    {
        FieldProperties field;
        istringstream fieldStream(token);
        string name, type, isArray;
        getline(fieldStream, name, ':');
        getline(fieldStream, type, ':');
        getline(fieldStream, isArray, ':');
        field.setFieldName(name);
        field.setFieldType(type);
        field.setIsArray(isArray);
        field.incSize();
        fields.push_back(field);
    }
    return fields;
}

// Function to swap two field vectors
void swap(vector<Field> &a, vector<Field> &b)
{
    vector<Field> temp = a;
    a = b;
    b = temp;
}

// Function to check if a line is a duplicate entry
void isDuplicateEntry(const string &line, const vector<string> &lines)
{
    for (const auto &entry : lines)
    {
        if (line == entry)
        {
            throw runtime_error("Exception: duplicate entry");
        }
    }
}

// Function to check if all fields are present in a line
void checkMissingField(const string &line, size_t expectedFields)
{
    stringstream ss(line);
    string token;
    size_t actualFields = 0;
    while (getline(ss, token, '|'))
    {
        actualFields++;
    }
    if (actualFields != expectedFields)
    {
        throw runtime_error("Exception: missing field");
    }
}

// Function to validate the format of a command
void validateCommandFormat(const std::string &commandType, const std::string &command)
{
    istringstream iss(command);
    vector<string> tokens;
    string token;

    // Split the command into tokens
    while (iss >> token)
    {
        tokens.push_back(token);
    }

    // Check the command type and its format
    if (commandType == "search")
    {
        // "search" command should have 4 tokens: search "keyword" in "field_name"
        if (tokens.size() != 4)
        {
            throw runtime_error("Exception: command is wrong");
        }
        if (tokens[2] != "in")
        {
            throw runtime_error("Exception: command is wrong");
        }

        // Check if keywords and field names are enclosed in double quotes
        if (tokens[1].front() != '"' || tokens[1].back() != '"' || tokens[3].front() != '"' || tokens[3].back() != '"')
        {
            throw runtime_error("Exception: command is wrong");
        }
    }
    else if (commandType == "sort")
    {
        // "sort" command should have 2 tokens: sort "field_name"
        if (tokens.size() != 2)
        {
            throw runtime_error("Exception: command is wrong");
        }
        if (tokens[1].front() != '"' || tokens[1].back() != '"')
        {
            throw runtime_error("Exception: command is wrong");
        }
    }
    else
    {
        throw runtime_error("Exception: command is wrong");
    }
}

// Function to validate the "search" command
void validatesearchCommand(const string &commandType, const string &keyword, const string &fieldName, vector<FieldProperties> &fieldProperties)
{

    bool recognized = false;
    for (const auto &field : fieldProperties)
    {
        if (field.isRecognizedField(fieldName))
        {
            recognized = true;
            break;
        }
    }
    if (!recognized)
    {
        throw runtime_error("Exception: command is wrong");
    }
}

// Function to validate the "sort" command
void validateSortCommand(const string &commandType, const string &fieldName, vector<FieldProperties> &fieldProperties)
{
    bool recognized = false;
    for (const auto &field : fieldProperties)
    {
        if (field.isRecognizedField(fieldName))
        {
            recognized = true;
            break;
        }
    }
    if (!recognized)
    {
        throw runtime_error("Exception: command is wrong");
    }
}

// Function to perform keyword-based search on fields
void searchForKeyword(const string &keyword, const string &fieldName, const vector<FieldProperties> &fieldProperties, FieldsForTypes &fieldsForTypes, const vector<string> &lines)
{
    int typeIndex = -1;
    for (size_t i = 0; i < fieldProperties.size(); ++i)
    {
        if (fieldProperties[i].getFieldName() == fieldName)
        {
            typeIndex = i;
            break;
        }
    }

    if (typeIndex == -1)
    {
        cerr << "Exception: field name not found" << endl;
        return;
    }
    else
    {
        // Use the search function of the Field class
        for (size_t i = 0; i < fieldsForTypes.getFields()[typeIndex].size(); ++i)
        {
            if (fieldsForTypes.getFields()[typeIndex][i].search(keyword))
            {
                int lineIndex = i;

                for (size_t j = 0; j < fieldProperties.size(); j++)
                {
                    const auto &values = fieldsForTypes.getFields()[j][lineIndex].getValues();
                    for (size_t k = 0; k < values.size(); ++k)
                   
                    {
                        cout << values[k];
                        if (k != values.size() - 1)
                        {
                            cout << ":";
                        }
                    }
                    if (j != fieldProperties.size() - 1)
                    {
                        cout << "|";
                    }
                }
                cout << endl;
            }
        }
    }
}

// Function to sort fields based on a specified field name
void sortForKeyword(const string &fieldName, const vector<FieldProperties> &fieldProperties, FieldsForTypes &fieldsForTypes, const vector<string> &lines)
{
    int typeIndex = -1;
    for (size_t i = 0; i < fieldProperties.size(); ++i)
    {
        if (fieldProperties[i].getFieldName() == fieldName)
        {
            typeIndex = i;
            break;
        }
    }

    if (typeIndex == -1)
    {
        cerr << "Exception: field name not found" << endl;
        return;
    }

    // Bubble sort for simplicity
    bool swapped;
    do
    {
        swapped = false;
        for (size_t i = 0; i < fieldsForTypes.getFields()[typeIndex].size() - 1; ++i)
        {
            if (fieldsForTypes.getFields()[typeIndex][i].getValues()[0] > fieldsForTypes.getFields()[typeIndex][i + 1].getValues()[0])
            {
                swap(fieldsForTypes.getFields()[typeIndex][i], fieldsForTypes.getFields()[typeIndex][i + 1]);
                swapped = true;
            }
        }
    } while (swapped);

    // Print sorted fieldsForTypes
    stringstream ss;
    for (size_t i = 0; i < fieldsForTypes.getFields()[0].size(); ++i) // For each line
    {
        for (size_t j = 0; j < fieldsForTypes.getFields().size(); ++j) // For each field
        {
            const auto &values = fieldsForTypes.getFields()[j][i].getValues();
            for (size_t k = 0; k < values.size(); ++k)
            {
                ss << values[k];
                if (k < values.size() - 1)
                    ss << ":"; // Add ":" after each element except the last one
            }
            if (j < fieldsForTypes.getFields().size() - 1)
                ss << "|"; // Add "|" after the last field
        }
        ss << endl; // Move to the next line after finishing a line
    }

    cout << ss.str(); // Print the results
}