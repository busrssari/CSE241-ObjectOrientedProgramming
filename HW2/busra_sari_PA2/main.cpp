#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SparseVector.h" // Include the header file for SparseVector class
#include "SparseMatrix.h"

using namespace std;

// Sort the data vector of SparseVector by index
void SparseVector::sortDataByIndex()
{
    // Bubble sort based on index
    for (size_t i = 0; i < data.size() - 1; ++i)
    {
        for (size_t j = 0; j < data.size() - i - 1; ++j)
        {
            if (data[j].getIndex() > data[j + 1].getIndex())
            {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

// Overloaded addition operator for SparseVector class
SparseVector SparseVector::operator+(const SparseVector &other) const
{
    SparseVector newVec;

    // Add elements from the first vector
    for (const auto &inner1 : data)
    {
        innerVector inner;
        double newValue = inner1.getValue();
        inner.setter(inner1.getIndex(), newValue);
        newVec.data.push_back(inner);
    }

    // Add elements from the second vector
    for (const auto &inner2 : other.data)
    {
        bool found = false;
        for (auto &inner1 : newVec.data)
        {
            if (inner1.getIndex() == inner2.getIndex())
            {
                double newValue = inner1.getValue() + inner2.getValue();
                if (newValue != 0.0)
                {
                    inner1.setter(inner1.getIndex(), newValue);
                }
                found = true;
                break;
            }
        }
        if (!found)
        {
            innerVector inner;
            inner.setter(inner2.getIndex(), inner2.getValue());
            newVec.data.push_back(inner);
        }
    }

    // Sort the new vector based on index
    newVec.sortDataByIndex();
    return newVec;
}

// Overloaded subtraction operator for SparseVector class
SparseVector SparseVector::operator-(const SparseVector &other) const
{
    SparseVector newVec;

    // Subtract elements from the first vector
    for (const auto &inner1 : data)
    {
        innerVector inner;
        double newValue = inner1.getValue();
        inner.setter(inner1.getIndex(), newValue);
        newVec.data.push_back(inner);
    }

    // Subtract elements from the second vector
    for (const auto &inner2 : other.data)
    {
        bool found = false;
        for (auto &inner1 : newVec.data)
        {
            if (inner1.getIndex() == inner2.getIndex())
            {
                double newValue = inner1.getValue() - inner2.getValue();
                if (newValue != 0.0)
                {
                    inner1.setter(inner1.getIndex(), newValue);
                }
                found = true;
                break;
            }
        }
        if (!found)
        {
            innerVector inner;
            inner.setter(inner2.getIndex(), -inner2.getValue()); // Subtracting with negative value
            newVec.data.push_back(inner);
        }
    }

    newVec.sortDataByIndex(); // Sort the new vector based on index
    return newVec;
}

// Implement the unary negation operator for SparseVector class
SparseVector SparseVector::operator-() const
{
    SparseVector newVec;

    // Negate all elements
    for (const auto &inner : data)
    {
        innerVector negatedInner;
        double newValue = inner.getValue() * (-1);
        negatedInner.setter(inner.getIndex(), newValue);
        newVec.data.push_back(negatedInner);
    }

    return newVec;
}

SparseVector SparseVector::operator=(const SparseVector &other) // Assignment operator overload for SparseVector class

{
    data.clear(); // Clear existing data

    for (const auto &inner : other.data) // Copy data from the other vector

    {
        data.push_back(inner);
    }

    return *this;
}

int check_errors(ifstream *f) // Function to check errors in file operations

{
    int stop = 0;
    if (f->eof())
    {
        stop = 0;
    }
    if (f->fail())
    {
        stop = 1;
    }
    if (f->bad())
    {
        stop = 1;
    }
    return stop;
}

SparseVector::SparseVector(const string &name)
{
    int index = 0;
    double value;
    char ch;

    innerVector inner;

    ifstream file(name); // Open the file
    if (file.is_open())
    {
        while (!file.eof())
        {
            file >> index >> ch >> value; // Read index, separator, and value from file

            if (check_errors(&file))
            {
                break;
            }
            if (value != 0.0)
            {
                inner.setter(index, value); // Set index and value for the inner class
                data.push_back(inner);      // Add inner class to the data vector
            }
        }
    }
}

ostream &operator<<(ostream &cout, const SparseVector &vec) // Overloaded output operator implementation for SparseVector class

{
    for (int i = 0; i < vec.gettheData().size(); i++)
    {
        cout << vec.gettheData()[i].getIndex() << ":" << vec.gettheData()[i].getValue() << " ";
    }
    return cout;
}

double dot_product(const SparseVector &vector1, const SparseVector &vector2) // Function to calculate dot product between two SparseVectors

{
    double dotProduct = 0.0;

    for (const auto &inner1 : vector1.gettheData()) // Multiply corresponding values and accumulate

    {
        int index1 = inner1.getIndex();
        double value1 = inner1.getValue();

        for (const auto &inner2 : vector2.gettheData())
        {
            int index2 = inner2.getIndex();
            double value2 = inner2.getValue();

            if (index1 == index2)
            {
                dotProduct += value1 * value2;
                break;
            }
        }
    }

    return dotProduct;
}

void innerMatrix::sortCols()
{
    vector<int> sortedCols; // Create temporary vectors to store sorted columns and values

    vector<double> sortedValues;

    for (size_t i = 0; i < cols.size(); ++i) // Copy columns and values to temporary vectors

    {
        sortedCols.push_back(cols[i]);
        sortedValues.push_back(values[i]);
    }

    for (size_t i = 0; i < sortedCols.size(); ++i) // Sort columns and corresponding values in ascending order
    {
        for (size_t j = i + 1; j < sortedCols.size(); ++j)
        {
            if (sortedCols[i] > sortedCols[j])
            {
                swap(sortedCols[i], sortedCols[j]); // Swap columns and values if necessary to maintain sorted order

                swap(sortedValues[i], sortedValues[j]);
            }
        }
    }

    cols.clear(); // Clear current columns and values vectors

    values.clear();

    for (size_t i = 0; i < sortedCols.size(); ++i) // Copy sorted columns and values back to original vectors

    {
        cols.push_back(sortedCols[i]);
        values.push_back(sortedValues[i]);
    }
}

// Overloaded addition operator for SparseMatrix objects
SparseMatrix SparseMatrix::operator+(const SparseMatrix &matrix2)
{
    SparseMatrix result;
    result.filename = filename;

    for (const auto &inner1 : data) // Copy data from the first matrix to the result matrix

    {
        result.data.push_back(inner1);
    }

    for (const auto &inner2 : matrix2.data) // Iterate over the data of the second matrix

    {
        bool found = false;
        for (auto &inner_result : result.data) // Search for matching rows in the result matrix

        {
            if (inner_result.getRow() == inner2.getRow())
            {
                for (size_t i = 0; i < inner2.getCols().size(); ++i) // Iterate over columns of the second matrix

                {
                    int col2 = inner2.getCol(i);
                    double value2 = inner2.getValue(i);
                    bool col_found = false;
                    for (size_t j = 0; j < inner_result.getCols().size(); ++j) // Search for matching columns in the row of the result matrix

                    {
                        if (inner_result.getCol(j) == col2)
                        {
                            double newValue = inner_result.getValue(j) + value2; // Add values if columns match

                            if (newValue != 0)
                            {
                                inner_result.setValue(j, newValue);
                            }
                            else
                            {
                                inner_result.removeValue(j); // If the result is zero, remove the entry

                                inner_result.removeCol(j);
                            }
                            col_found = true;
                            break;
                        }
                    }

                    if (!col_found) // If the column is not found, add it to the result matrix

                    {
                        inner_result.setCol(col2);
                        inner_result.pushValue(value2);
                    }
                }
                found = true;
                break;
            }
        }

        if (!found) // If the row is not found, add it to the result matrix
        {
            innerMatrix new_inner;
            new_inner.setRow(inner2.getRow());
            for (size_t i = 0; i < inner2.getCols().size(); ++i)
            {
                new_inner.setCol(inner2.getCol(i));
                new_inner.pushValue(inner2.getValue(i));
            }
            result.data.push_back(new_inner);
        }
    }

    for (auto &inner_result : result.data) // Sort the columns of each row in the result matrix
    {
        inner_result.sortCols();
    }

    return result;
}

// Overloaded subtraction operator for SparseMatrix objects
SparseMatrix SparseMatrix::operator-(const SparseMatrix &matrix2)
{
    SparseMatrix result;
    result.filename = filename;

    for (const auto &inner1 : data) // Copy data from the first matrix to the result matrix

    {
        result.data.push_back(inner1);
    }

    for (const auto &inner2 : matrix2.data) // Iterate over the data of the second matrix

    {
        bool found = false;
        for (auto &inner_result : result.data) // Search for matching rows in the result matrix

        {
            if (inner_result.getRow() == inner2.getRow())
            {
                for (size_t i = 0; i < inner2.getCols().size(); ++i) // Iterate over columns of the second matrix

                {
                    int col2 = inner2.getCol(i);
                    double value2 = inner2.getValue(i);
                    bool col_found = false;
                    for (size_t j = 0; j < inner_result.getCols().size(); ++j) // Search for matching columns in the row of the result matrix

                    {
                        if (inner_result.getCol(j) == col2)
                        {
                            double newValue = inner_result.getValue(j) - value2; // Subtract values if columns match

                            if (newValue != 0)
                            {
                                inner_result.setValue(j, newValue);
                            }
                            else
                            {
                                inner_result.removeValue(j); // If the result is zero, remove the entry

                                inner_result.removeCol(j);
                            }
                            col_found = true;
                            break;
                        }
                    }

                    // If the column is not found, add its negation to the result matrix
                    if (!col_found)
                    {
                        inner_result.setCol(col2);
                        inner_result.pushValue(-value2);
                    }
                }
                found = true;
                break;
            }
        }

        if (!found) // If the row is not found, add its negation to the result matrix
        {
            innerMatrix new_inner;
            new_inner.setRow(inner2.getRow());
            for (size_t i = 0; i < inner2.getCols().size(); ++i)
            {
                new_inner.setCol(inner2.getCol(i));
                new_inner.pushValue(-inner2.getValue(i));
            }
            result.data.push_back(new_inner);
        }
    }

    for (auto &inner_result : result.data) // Sort the columns of each row in the result matrix
    {
        inner_result.sortCols();
    }

    return result;
}

// Overloaded multiplication operator for SparseMatrix objects
SparseMatrix SparseMatrix::operator*(const SparseMatrix &matrix2)
{
    SparseMatrix result;

    int row1 = data.empty() ? 0 : data.back().getRow() + 1; // Determine dimensions of the matrices

    int col1 = 0;
    for (const auto &inner : data)
    {
        if (!inner.getCols().empty())
        {
            col1 = std::max(col1, inner.getCols().back() + 1);
        }
    }

    int row2 = matrix2.data.empty() ? 0 : matrix2.data.back().getRow() + 1;
    int col2 = 0;
    for (const auto &inner : matrix2.data)
    {
        if (!inner.getCols().empty())
        {
            col2 = std::max(col2, inner.getCols().back() + 1);
        }
    }
    if (col1 != row2)
    {
        std::cerr << "Error: The number of columns in the first matrix does not match the number of rows in the second matrix. Matrix multiplication cannot be performed." << std::endl;
    }

    int newRow = std::max(row1, row2); // Determine dimensions of the result matrix

    int newCol = std::max(col1, col2);

    for (int i = 0; i < newRow; ++i) // Perform matrix multiplication

    {
        innerMatrix inner;
        int index = 0;
        for (int j = 0; j < newCol; ++j)
        {
            double sum = 0;

            for (int k = 0; k < col1; ++k) // Perform dot product for each element
            {
                double value1 = getValueforSM(i, k);
                double value2 = matrix2.getValueforSM(k, j);
                sum += value1 * value2;
            }

            if (sum != 0) // Store non-zero elements in the result matrix
            {
                result.setValueforSM(i, j, sum);
            }
        }
    }

    return result;
}

// Overloaded unary negation operator for SparseMatrix objects
SparseMatrix SparseMatrix::operator-()
{
    double value;
    SparseMatrix newMatrix;
    newMatrix.setFilename();

    for (int i = 0; i < data.size(); i++) // Iterate over each row of the matrix

    {
        innerMatrix inner;

        for (int j = 0; j < data[i].getCols().size(); j++) // Iterate over each column of the current row
        {

            value = data[i].getValue(j) * (-1); // Negate the value and add it to the new matrix
            inner.setCol(data[i].getCol(j));
            inner.pushValue(value);
        }

        inner.setRow(data[i].getRow()); // Set the row index and add the modified row to the new matrix
        newMatrix.data.push_back(inner);
    }
    return newMatrix;
}

// Assignment operator for SparseMatrix objects
SparseMatrix &SparseMatrix::operator=(const SparseMatrix &other)
{

    data.clear(); // Clear current data

    for (int i = 0; i < other.data.size(); i++) // Copy data from the other matrix
    {
        data.push_back(other.data[i]);
    }
    return *this;
}

// Returns the transpose of the current matrix
SparseMatrix SparseMatrix::transpose() const
{
    SparseMatrix transposedMatrix;

    for (const auto &inner : data) // Iterate over each innerMatrix object in the data vector
    {

        for (size_t i = 0; i < inner.getCols().size(); ++i) // Iterate over each non-zero value in the inner matrix
        {

            int row = inner.getCol(i); // Swap row and column indices, and push the value to the transposed matrix
            int col = inner.getRow();
            double value = inner.getValue(i);

            innerMatrix transposedInner;
            transposedInner.setRow(row);
            transposedInner.setCol(col);
            transposedInner.pushValue(value);

            transposedMatrix.data.push_back(transposedInner);
        }
    }
    transposedMatrix.sortRows(); // Sort rows of the transposed matrix
    return transposedMatrix;
}

// Function to sort rows of the SparseMatrix object based on row indices
void SparseMatrix::sortRows()
{
    for (size_t i = 0; i < data.size() - 1; ++i)
    {
        for (size_t j = 0; j < data.size() - i - 1; ++j)
        {
            if (data[j].getRow() > data[j + 1].getRow()) // Compare row indices and swap if necessary
            {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

// Constructor for SparseMatrix objects with file input
SparseMatrix::SparseMatrix(const string &name)
{
    string line;
    size_t spacePos, colonPos;

    ifstream file(name); // Open the file for reading
    if (file.is_open())
    {

        while (1) // Read lines from the file until the end
        {
            innerMatrix inner;

            string row_index;
            int colCount = 0;

            std::getline(file, line);

            if (check_errors(&file)) // Check for errors while reading
            {
                break;
            }

            spacePos = line.find(' '); // Parse row index from the line
            row_index = line.substr(0, spacePos);
            line.erase(0, spacePos + 1);
            inner.setRow(stoi(row_index));

            while (!line.empty()) // Parse columns and values from the line
            {
                string col;
                string value;
                colonPos = line.find(':');
                col = line.substr(0, colonPos);
                line.erase(0, colonPos + 1);

                spacePos = line.find(' ');
                if (spacePos == std::string::npos)
                {
                    value = line;
                    line.clear();
                }
                else
                {
                    value = line.substr(0, spacePos);
                    line.erase(0, spacePos + 1);
                }

                if (stod(value) != 0) // Add non-zero elements to the inner matrix
                {
                    inner.setCol(stoi(col));
                    inner.pushValue(stod(value));
                }
            }

            if (!inner.getCols().empty()) // Add non-empty inner matrices to the data vector
            {
                data.push_back(inner);
            }
        }
    }
}

// Function to set value in the SparseMatrix at given row and column indices
void SparseMatrix::setValueforSM(int row, int col, double value)
{

    for (auto &inner : data) // Iterate over each innerMatrix object in the data vector
    {

        if (inner.getRow() == row) // Find the row matching the given index
        {

            for (size_t i = 0; i < inner.getCols().size(); ++i) // Iterate over each non-zero value in the row
            {

                if (inner.getCol(i) == col) // Update the value if column index matches
                {
                    inner.setValue(i, value);
                    return;
                }
            }
        }
    }

    innerMatrix new_inner; // If no match found, create a new innerMatrix object and add it to the data vector
    new_inner.setRow(row);
    new_inner.setCol(col);
    new_inner.pushValue(value);
    data.push_back(new_inner);
}

double SparseMatrix::getValueforSM(int row, int col) const // Function to get value from the SparseMatrix at given row and column indices
{

    for (const auto &inner : data) // Iterate over each innerMatrix object in the data vector
    {

        if (inner.getRow() == row) // Find the row matching the given index
        {

            for (size_t i = 0; i < inner.getCols().size(); ++i) // Iterate over each non-zero value in the row
            {

                if (inner.getCol(i) == col) // Return the value if column index matches
                {
                    return inner.getValue(i);
                }
            }
        }
    }

    return 0.0; // Return zero if no match found
}

// Overloaded stream insertion operator for SparseMatrix objects
ostream &operator<<(ostream &cout, const SparseMatrix &matrix)
{
    for (const auto &inner : matrix.data)
    {
        cout << inner.getRow() << " ";
        for (size_t i = 0; i < inner.getCols().size(); ++i)
        {
            cout << inner.getCol(i) << ":" << inner.getValue(i) << " ";
        }
        cout << endl;
    }
    return cout;
}

int main()
{
    SparseVector vector1("vector.txt"); // Test SparseVector constructors
    SparseVector vector2("vector2.txt");

    cout << "vector1:" << endl // Test SparseVector output operator <<
         << vector1 << endl
         << endl;
    cout << "vector2:" << endl
         << vector2 << endl
         << endl;

    SparseVector vector3 = -vector2; // Test unary negation operator -
    cout << "vector3 = -vector2:" << endl
         << vector3 << endl
         << endl;

    SparseVector vector4 = vector1 + vector2; // Test SparseVector addition operator +
    cout << "vector4 = vector1 + vector2:" << endl
         << vector4 << endl
         << endl;

    SparseVector vector5 = vector1 - vector2; // Test SparseVector subtraction operator -
    cout << "vector5 = vector1 - vector2:" << endl
         << vector5 << endl
         << endl;

    cout << "Dot product of vector1 and vector2: " << dot_product(vector1, vector2) << endl // Test dot_product function
         << endl;

    SparseMatrix matrix1("matrix.txt"); // Test SparseMatrix constructor
    SparseMatrix matrix2("matrix2.txt");

    cout << "matrix1:" << endl // Test SparseMatrix output operator <<
         << matrix1 << endl
         << endl;
    cout << "matrix2:" << endl
         << matrix2 << endl
         << endl;

    SparseMatrix matrix3 = matrix1 + matrix2; // Test SparseMatrix addition operator +
    cout << "matrix3 = matrix1 * matrix2:" << endl
         << matrix3 << endl
         << endl;

    SparseMatrix matrix4 = matrix1 - matrix2; // Test SparseMatrix subtraction operator -
    cout << "matrix4 = matrix1 - matrix2:" << endl
         << matrix4 << endl
         << endl;
         
    SparseMatrix matrix5 = matrix1 * matrix2; // Test SparseMatrix multiplication operator *
    cout << "matrix5 = matrix1 * matrix2:" << endl
         << matrix5 << endl
         << endl;

    SparseMatrix matrix6 = -matrix1; // Test SparseMatrix negation operator -
    cout << "matrix6 = -matrix1:" << endl
         << matrix6 << endl
         << endl;

    SparseMatrix matrix7 = matrix2.transpose(); // Test SparseMatrix transpose function
    cout << "matrix7 = Transpose of matrix2:" << endl
         << matrix7 << endl
         << endl;

    SparseMatrix matrix8; // Test SparseMatrix assignment operator =
    matrix8 = matrix1;
    cout << "matrix8 = matrix1:" << endl
         << matrix8 << endl
         << endl;

    return 0;
}
