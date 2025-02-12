#include "Course.h"

using namespace std;

// Constructor to initialize Course object with name and code
Course::Course(const string &name, const string &code)
    : name(name), code(code), students(new Student *[10]), studentCount(0), maxStudentCount(10) {}

// Function to check if a student is unique in the course
bool Course::isUniqueStudent(Student *student)
{
    // Loop through the students in the course
    for (int i = 0; i < studentCount; i++)
    {
        // If the student is found in the course, return false
        if (student == students[i])
        {
            return false;
        }
    }
    // If the student is not found, return true
    return true;
}

// Function to add a student to the course
void Course::addStudent(Student *student)
{
    // If the student is not unique or null, return
    if (!isUniqueStudent(student) || student == nullptr)
    {
        return;
    }

    // If student count exceeds maximum capacity, double the capacity
    if (studentCount >= maxStudentCount)
    {
        maxStudentCount *= 2;
        // Create a temporary array with doubled capacity
        Student **tempStudents = new Student *[maxStudentCount];

        // Copy existing students to temporary array
        for (int i = 0; i < studentCount; i++)
        {
            tempStudents[i] = students[i];
        }

        // Add new student to temporary array
        tempStudents[studentCount] = student;

        // Delete old students array and assign temporary array to students
        delete[] students;
        students = tempStudents;
        studentCount++;
    }
    else
    {
        // If capacity allows, directly add student to the course
        students[studentCount] = student;
        studentCount++;
    }
}

// Function to delete a student from the course
void Course::deleteStudent(Student *student)
{
    // If student is null, return
    if (student == nullptr)
    {
        return;
    }

    int tempIndex = 0;
    bool studentFound = false;

    // Loop through the students in the course
    for (int i = 0; i < studentCount; i++)
    {
        // If the student is found, mark as found and skip it
        if (students[i] == student)
        {
            studentFound = true;
            continue;
        }
        else
        {
            // If student is not found, copy it to temporary array
            students[tempIndex] = students[i];
            tempIndex++;
        }
    }

    // If student is not found in the course, return
    if (!studentFound)
    {
        return;
    }

    // Decrement student count
    studentCount--;

    // If student count falls below half of maximum capacity, halve the capacity
    if (studentCount < maxStudentCount / 2)
    {
        maxStudentCount /= 2;
        // Create a temporary array with halved capacity
        Student **tempStudents = new Student *[maxStudentCount];

        // Copy existing students to temporary array
        for (int i = 0; i < studentCount; i++)
        {
            tempStudents[i] = students[i];
        }

        // Delete old students array and assign temporary array to students
        delete[] students;
        students = tempStudents;
    }
}

// Getter function to retrieve course name
string Course::getName() const
{
    return name;
}

// Getter function to retrieve course code
string Course::getCode() const
{
    return code;
}

// Getter function to retrieve array of students enrolled in the course
Student **Course::getStudents() const
{
    return students;
}

// Getter function to retrieve number of students enrolled in the course
int Course::getStudentCount() const
{
    return studentCount;
}

// Setter function to set course name
void Course::setName(const string &name)
{
    this->name = name;
}

// Setter function to set course code
void Course::setCode(const string &code)
{
    this->code = code;
}

// Setter function to set number of students enrolled in the course
void Course::setStudentCount(const int &count)
{
    studentCount = count;
}

// Destructor to deallocate memory allocated for students array
Course::~Course()
{
    delete[] students;
}
