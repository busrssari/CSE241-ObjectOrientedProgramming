#include "Student.h"

using namespace std;

// Constructor to initialize Student object with name and ID
Student::Student(const ::string &name, const string &ID) : name(name), ID(ID), courses(new Course *[10]), courseCount(0), maxCourseCount(10) {}

// Function to add a course to the student's list of courses
void Student::addCourse(Course *course)
{
    // If the course is null, return
    if (course == nullptr)
    {
        return;
    }

    // If the number of courses exceeds the maximum capacity, double the capacity
    if (courseCount >= maxCourseCount)
    {
        maxCourseCount *= 2;
        Course **tempCourses = new Course *[maxCourseCount];

        // Copy existing courses to temporary array
        for (int i = 0; i < courseCount; ++i)
        {
            tempCourses[i] = courses[i];
        }

        // Delete old courses array and assign temporary array to courses
        delete[] courses;
        courses = tempCourses;
    }

    // Add the new course to the student's list of courses
    courses[courseCount] = course;
    courseCount++;
}

// Function to delete a course from the student's list of courses
void Student::deleteCourse(Course *course)
{
    // If the course is null, return
    if (course == nullptr)
    {
        return;
    }

    int tempIndex = 0;
    bool courseFound = false;

    // Loop through the courses in the student's list
    for (int i = 0; i < courseCount; i++)
    {
        // If the course is found, mark as found and skip it
        if (courses[i] == course)
        {
            courseFound = true;
            continue;
        }
        else
        {
            // If the course is not found, copy it to the temporary array
            courses[tempIndex] = courses[i];
            tempIndex++;
        }
    }

    // If the course is not found in the student's list, return
    if (!courseFound)
    {
        return;
    }

    // Decrement the number of courses
    courseCount--;

    // If the number of courses falls below half of the maximum capacity, halve the capacity
    if (courseCount < maxCourseCount / 2)
    {
        maxCourseCount /= 2;
        Course **tempCourses = new Course *[maxCourseCount];

        // Copy existing courses to temporary array
        for (int i = 0; i < courseCount; i++)
        {
            tempCourses[i] = courses[i];
        }

        // Delete old courses array and assign temporary array to courses
        delete[] courses;
        courses = tempCourses;
    }
}

// Getter function to retrieve student's name
string Student::getName() const
{
    return name;
}

// Getter function to retrieve student's ID
string Student::getID() const
{
    return ID;
}

// Getter function to retrieve array of courses enrolled by the student
Course **Student::getCourses() const
{
    return courses;
}

// Getter function to retrieve number of courses enrolled by the student
int Student::getCourseCount() const
{
    return courseCount;
}

// Setter function to set student's name
void Student::setName(const string &name)
{
    this->name = name;
}

// Setter function to set student's ID
void Student::setID(const string &ID)
{
    this->ID = ID;
}

// Setter function to set number of courses enrolled by the student
void Student::setCourseCount(const int &count)
{
    courseCount = count;
}

// Function to check if the student has taken a specific course
bool Student::coursesTaken(const Course *course) const
{
    // Loop through the courses in the student's list
    for (int i = 0; i < courseCount; ++i)
    {
        // If the course is found in the student's list, return true
        if (courses[i] == course)
        {
            return true;
        }
    }
    // If the course is not found in the student's list, return false
    return false;
}

// Destructor to deallocate memory allocated for courses array
Student::~Student()
{
    delete[] courses;
}
