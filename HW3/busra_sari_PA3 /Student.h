
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include "Course.h"
using namespace std;

class Course; // Forward declaration

class Student
{
private:
    string name;
    string ID;
    Course **courses;
    int courseCount;
    int maxCourseCount;

public:
    Student(const string &name, const string &ID);
    void addCourse(Course *course);
    void deleteCourse(Course *course);
    string getName() const;
    string getID() const;
    Course **getCourses() const;
    int getCourseCount() const;
    bool coursesTaken(const Course *course) const;
    void setName(const string &name);
    void setID(const string &ID);
    void setCourseCount(const int &count);
    ~Student();
};

#endif // STUDENT_H
