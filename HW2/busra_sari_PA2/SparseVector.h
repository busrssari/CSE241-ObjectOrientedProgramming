#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class innerVector
{
private:
    int index;
    double value;

public:
    inline void setter(int _index, double _value) {index = _index;  value = _value;};
    inline double getValue() const {return value; };
   inline int getIndex() const {return index;};

}; 

class SparseVector
{
private:
    string filename;
    vector<innerVector> data;

public:
    inline void setFilename(const string &name = "-") {filename=name;};
    inline SparseVector() {setFilename();};
    SparseVector operator=(const SparseVector &other);
    SparseVector operator+(const SparseVector &other) const;
    SparseVector operator-(const SparseVector &other) const;
    SparseVector operator-() const;
    void sortDataByIndex();
    SparseVector(const string &name);
    inline const string &getFilename()  {return filename;};
    inline vector<innerVector> gettheData() const {return data;};
    friend ostream &operator<<(std::ostream &cout, const SparseVector &vec);
};

#endif // SPARSEVECTOR_H
