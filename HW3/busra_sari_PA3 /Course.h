#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include "Student.h"
using namespace std;

class Student; // Forward declaration

class Course
{
private:
    string name;
    string code;
    Student **students;
    int studentCount;
    int maxStudentCount;

public:
    Course(const string &name, const string &code);
    void addStudent(Student *student);
    void deleteStudent(Student *student);
    bool isUniqueStudent(Student *student);
    string getName() const;
    string getCode() const;
    Student **getStudents() const;
    int getStudentCount() const;
    void setName(const string &name);
    void setCode(const string &code);
    void setStudentCount(const int &count);
    ~Course();
};

#endif // COURSE_H
