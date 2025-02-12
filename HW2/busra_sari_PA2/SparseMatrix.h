#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class innerMatrix
{
private:
    int row;
    vector<int> cols;
    vector<double> values;

public:
    inline void setRow(int _row) { row = _row; };
    inline void setCol(int col) { cols.push_back(col); };
    inline void pushValue(double value) { values.push_back(value); };
    inline void setValue(int index, double value) { values[index] = value; };
    inline int getRow() const { return row; };
    inline int getCol(int index) const { return cols[index]; };
    inline vector<int> getCols() const { return cols; };
    inline vector<double> getValues() const { return values; };
    inline double getValue(int index) const { return values[index]; };
    inline void removeValue(size_t index) { values.erase(values.begin() + index); };
    inline void removeCol(size_t index) {  cols.erase(cols.begin() + index);};
    void sortCols();
};

class SparseMatrix
{
private:
    string filename;
    vector<innerMatrix> data;

public:
    inline void setFilename(const string &name = "-") {  filename = name;};
    inline SparseMatrix() {setFilename(); };
      inline const string &getFilename() {return filename;};
    SparseMatrix(const string &name);
    SparseMatrix operator+(const SparseMatrix &matrix2);
    SparseMatrix operator-(const SparseMatrix &matrix2);
    SparseMatrix operator*(const SparseMatrix &matrix2);
    SparseMatrix operator-();
    SparseMatrix &operator=(const SparseMatrix &other);
    SparseMatrix transpose() const;
    void sortRows();
    vector<innerMatrix> gettheData() const {return data; };
    void setValueforSM(int row, int col, double value);
    double getValueforSM(int row, int col) const;
    friend ostream &operator<<(std::ostream &cout, const SparseMatrix &vec);
};

#endif // SPARSEMATRIX_H
