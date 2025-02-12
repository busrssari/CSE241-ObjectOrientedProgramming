#ifndef SYSTEM_H
#define SYSTEM_H

#include "Student.h"
#include "Course.h"
#include <iostream>
#include <string>
#include <cctype>

class System
{
private:
    Course **courses;
    Student **students;
    int numCourses;
    int numStudents;
    int maxCourses;
    int maxStudents;

public:
    System();
    void addNewStudent(const string &name, const string &ID);
    void addNewCourse(const string &name, const string &code);
    bool isUniqueNewCourse(Course *course);
    bool isUniqueNewStudent(Student *student);
    void deleteStudentFromSystem(int index);
    void deleteCourseFromSystem(int index);
    int selectStudent(const string &name, const string &ID);
    int selectCourse(const string &name, const string &code);
    int addSelectedStudentToCourse(int index);
    int dropSelectedStudentFromCourse(int index);
    void listStudentsRegisteredToCourse(int index) const;
    void listAllStudents();
    void listAllCourses();
    bool parseforStudent(string &name, string &ID);
    bool parseforCourse(string &name, string &code);
    bool isName(const string &str);
    bool isNumeric(const string &str);
    ~System();
    void printMainMenu();
    void printStudentMenu();
    void printCourseMenu();
    void printSelectStudentMenu();
    void printSelectCourseMenu();
    void selectCourseMenu(int index);
    void selectStudentMenu(int index);
    void studentMenu();
    void courseMenu();
    void mainMenu();
};

#endif // System_H