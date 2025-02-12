#include "System.h"
using namespace std;

// Constructor initializes the System object with arrays for courses and students
System::System() : courses(new Course *[10]), students(new Student *[10]), numCourses(0), numStudents(0), maxCourses(10), maxStudents(10) {}

// Function to parse input for creating a new student
bool System::parseforStudent(string &name, string &ID)
{
    string line;
    cin.ignore();
    getline(cin, line);

    size_t lastSpaceIndex = line.find_last_of(' ');
    if (lastSpaceIndex != string::npos)
    {
        string firstPart = line.substr(0, lastSpaceIndex);
        string secondPart = line.substr(lastSpaceIndex + 1);

        // Check if the first part of input is a valid name
        if (!isName(firstPart))
        {
            return false;
        }

        // Check if the second part of input is a valid ID
        if (!isNumeric(secondPart))
        {
            return false;
        }
        name = firstPart;
        ID = secondPart;

        return true;
    }
    else
    {
        return false;
    }
}

// Function to parse input for creating a new course
bool System::parseforCourse(string &name, string &code)
{
    string line;
    cin.ignore();
    getline(cin, line);

    size_t firstSpaceIndex = line.find_first_of(' ');
    if (firstSpaceIndex != string::npos)
    {
        string firstPart = line.substr(0, firstSpaceIndex);
        string secondPart = line.substr(firstSpaceIndex + 1);

        // Check if the second part of input is a valid name
        if (!isName(secondPart))
        {
            return false;
        }
        name = secondPart;
        code = firstPart;

        return true;
    }
    else
    {
        return false;
    }
}

// Function to check if a string contains only alphabetic characters and spaces (for names)
bool System::isName(const string &str)
{
    for (char c : str)
    {
        if (!isalpha(c) && c != ' ')
        {
            return false;
        }
    }
    return true;
}

// Function to check if a string contains only numeric characters (for IDs)
bool System::isNumeric(const string &str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

// Function to find the index of a student in the students array by name and ID
int System::selectStudent(const string &name, const string &ID)
{
    for (int i = 0; i < numStudents; ++i)
    {
        if (students[i]->getName() == name && students[i]->getID() == ID)
        {
            return i;
        }
    }
    return -1;
}

// Function to find the index of a course in the courses array by name and code
int System::selectCourse(const string &name, const string &code)
{
    for (int i = 0; i < numCourses; ++i)
    {
        if (courses[i]->getName() == name && courses[i]->getCode() == code)
        {
            return i;
        }
    }
    return -1;
}

// Function to delete a student from the system
void System::deleteStudentFromSystem(int index)
{
    if (index < numStudents)
    {
        // Delete the student from all courses
        for (int i = 0; i < numCourses; ++i)
        {
            courses[i]->deleteStudent(students[index]);
        }
        // Delete the student object
        delete students[index];
        // Shift the remaining students to fill the gap
        for (int i = index; i < numStudents - 1; ++i)
        {
            students[i] = students[i + 1];
        }
        students[numStudents - 1] = nullptr;

        --numStudents;
    }
}

// Function to delete a course from the system
void System::deleteCourseFromSystem(int index)
{
    if (index < numCourses)
    {
        // Delete the course from all students
        for (int i = 0; i < numStudents; ++i)
        {
            students[i]->deleteCourse(courses[index]);
        }

        // Delete the course object
        delete courses[index];
        // Shift the remaining courses to fill the gap
        for (int i = index; i < numCourses - 1; ++i)
        {
            courses[i] = courses[i + 1];
        }
        courses[numCourses - 1] = nullptr;
        --numCourses;
    }
}

// Function to add a new student to the system
void System::addNewStudent(const string &name, const string &ID)
{

    Student *newStudent = new Student(name, ID);
    // Check if the new student is unique
    if (isUniqueNewStudent(newStudent))
    {
        // If maximum capacity reached, double the capacity
        if (numStudents >= maxStudents)
        {
            maxStudents *= 2;
            Student **tempStudents = new Student *[maxStudents];
            // Copy existing students to the new array
            for (int i = 0; i < numStudents; ++i)
            {
                tempStudents[i] = students[i];
            }
            // Delete the old array and assign the new array
            delete[] students;
            students = tempStudents;
        }
        // Add the new student to the array
        students[numStudents++] = newStudent;
    }
}

// Function to add a new course to the system
void System::addNewCourse(const string &name, const string &code)
{
    Course *newCourse = new Course(name, code);
    // Check if the new course is unique
    if (isUniqueNewCourse(newCourse))
    {
        // If maximum capacity reached, double the capacity
        if (numCourses >= maxCourses)
        {
            maxCourses *= 2;
            Course **tempCourses = new Course *[maxCourses];
            // Copy existing courses to the new array
            for (int i = 0; i < numCourses; ++i)
            {
                tempCourses[i] = courses[i];
            }
            // Delete the old array and assign the new array
            delete[] courses;
            courses = tempCourses;
        }
        // Add the new course to the array
        courses[numCourses++] = newCourse;
    }
}

// Function to add a selected student to a course
int System::addSelectedStudentToCourse(int studentIndex)
{
    if (studentIndex >= numStudents)
    {
        return -1;
    }

    Student *selectedStudent = students[studentIndex];
    if (selectedStudent == nullptr)
    {
        return -1;
    }
    int count = 0;

    Course **coursesNotTaken = new Course *[numCourses];

    // Find the courses not taken by the selected student
    for (int i = 0; i < numCourses; ++i)
    {
        if (!(selectedStudent->coursesTaken(courses[i])))
        {
            coursesNotTaken[count] = courses[i];
            count++;
        }
    }
    cout << "0 up" << endl;
    for (int i = 0; i < count; ++i)
    {
        cout << i + 1 << " " << coursesNotTaken[i]->getCode() << " " << coursesNotTaken[i]->getName() << endl;
    }

    string courseIndex;
    cin >> courseIndex;

    // Validate user input
    if (!isNumeric(courseIndex))
    {
        return -1;
    }
    int index = stoi(courseIndex);

    if (index == 0)
    {
        return 0;
    }

    index--;
    if (index < 0 || index >= count)
    {
        return -1;
    }

    Course *selectedCourse = coursesNotTaken[index];
    if (selectedCourse == nullptr)
    {
        return -1;
    }

    // Add the selected student to the selected course
    selectedStudent->addCourse(selectedCourse);
    selectedCourse->addStudent(selectedStudent);
    return -1;
}

// Function to drop a selected student from a course
int System::dropSelectedStudentFromCourse(int studentIndex)
{
    if (studentIndex >= numStudents)
    {
        return -1;
    }

    Student *selectedStudent = students[studentIndex];
    if (selectedStudent == nullptr)
    {
        return -1;
    }

    cout << "0 up" << endl;
    // Display the courses registered by the selected student
    for (int i = 0; i < selectedStudent->getCourseCount(); ++i)
    {
        Course *course = selectedStudent->getCourses()[i];
        cout << i + 1 << " " << course->getCode() << " " << course->getName() << endl;
    }

    string courseIndex;
    cin >> courseIndex;
    if (!isNumeric(courseIndex))
    {
        return -1;
    }
    int index = stoi(courseIndex);
    if (index == 0)
    {
        return 0;
    }
    index--;

    if (index < 0 || index >= selectedStudent->getCourseCount())
    {
        return -1;
    }

    Course *selectedCourse = selectedStudent->getCourses()[index];
    if (selectedCourse == nullptr)
    {
        return -1;
    }

    // Drop the selected student from the selected course
    selectedStudent->deleteCourse(selectedCourse);
    selectedCourse->deleteStudent(selectedStudent);

    return -1;
}

// Function to check if a new student is unique
bool System::isUniqueNewStudent(Student *newStudent)
{
    for (int i = 0; i < numStudents; i++)
    {
        if (newStudent->getName() == students[i]->getName() && newStudent->getID() == students[i]->getID())
        {
            return false;
        }
    }
    return true;
}

// Function to check if a new course is unique
bool System::isUniqueNewCourse(Course *newCourse)
{
    for (int i = 0; i < numCourses; i++)
    {
        if (newCourse->getName() == courses[i]->getName() && newCourse->getCode() == courses[i]->getCode())
        {
            return false;
        }
    }
    return true;
}

// Function to list students registered to a particular course
void System::listStudentsRegisteredToCourse(int courseIndex) const
{
    if (courseIndex >= numCourses)
    {
        return;
    }

    Course *selectedCourse = courses[courseIndex];
    if (selectedCourse == nullptr)
    {
        return;
    }

    Student **students = selectedCourse->getStudents();
    int studentCount = selectedCourse->getStudentCount();
    if (studentCount == 0)
    {
        return;
    }

    // Display the list of students registered to the course
    for (int i = 0; i < studentCount; ++i)
    {
        cout << students[i]->getName() << " " << students[i]->getID() << endl;
    }
}

// Function to list all students in the system
void System::listAllStudents()
{
    if (numStudents == 0)
    {
        return;
    }
    // Display the list of all students
    for (int i = 0; i < numStudents; ++i)
    {
        cout << students[i]->getName() << " " << students[i]->getID() << endl;
    }
}

// Function to list all courses in the system
void System::listAllCourses()
{
    if (numCourses == 0)
    {
        return;
    }
    // Display the list of all courses
    for (int i = 0; i < numCourses; ++i)
    {
        cout << courses[i]->getName() << " " << courses[i]->getCode() << endl;
    }
}

// Destructor to free memory allocated for students and courses
System::~System()
{

    for (int i = 0; i < numStudents; ++i)
    {
        delete students[i];
    }

    delete[] students;

    for (int i = 0; i < numCourses; ++i)
    {
        delete courses[i];
    }

    delete[] courses;
}

// Function to print the main menu options
void System::printMainMenu()
{
    cout << "Main Menu" << endl;
    cout << "0 exit" << endl;
    cout << "1 student" << endl;
    cout << "2 course" << endl;
    cout << "3 list_all_students" << endl;
    cout << "4 list_all_courses" << endl;
    cout << ">> ";
}

// Function to print the student menu options
void System::printStudentMenu()
{
    cout << "0 up" << endl;
    cout << "1 add_student" << endl;
    cout << "2 select_student" << endl;
    cout << ">> ";
}

// Function to print the course menu options
void System::printCourseMenu()
{
    cout << "0 up" << endl;
    cout << "1 add_course" << endl;
    cout << "2 select_course" << endl;
    cout << ">> ";
}

// Function to print the select student menu options
void System::printSelectStudentMenu()
{
    cout << "0 up" << endl;
    cout << "1 delete_student" << endl;
    cout << "2 add_selected_student_to_a_course" << endl;
    cout << "3 drop_selected_student_from_a_course" << endl;
    cout << ">> ";
}

// Function to print the select course menu options
void System::printSelectCourseMenu()
{
    cout << "0 up" << endl;
    cout << "1 delete_course (after delete, print course menu)" << endl;
    cout << "2 list_students_registered_to_the_selected_course" << endl;
    cout << ">> ";
}

// Function to handle the course menu options
void System::selectCourseMenu(int index)
{
    int choice = -1;
    printSelectCourseMenu();

    // Loop to repeatedly prompt the user for course menu options
    while (choice != 0)
    {
        // Check for invalid input
        if (!(cin >> choice) || choice < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            cout << ">>";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            deleteCourseFromSystem(index);
            return;
        }
        case 2:
            listStudentsRegisteredToCourse(index);
            break;
        case 0:
            return;
        default:
            break;
        }
        printSelectCourseMenu();
    }
}

// Function to handle the select student menu options
void System::selectStudentMenu(int index)
{
    int choice = -1;
    printSelectStudentMenu();

    // Loop to repeatedly prompt the user for select student menu options
    while (choice != 0)
    {
        // Check for invalid input
        if (!(cin >> choice) || choice < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">>";
            choice = -1;
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            deleteStudentFromSystem(index);
            return;
        }
        case 2:
            choice = addSelectedStudentToCourse(index);
            break;
        case 3:
            choice = dropSelectedStudentFromCourse(index);
        case 0:
            return;
        default:
            break;
        }
        printSelectStudentMenu();
    }
}

// Function to handle student-related actions and user input
void System::studentMenu()
{
    int choice = -1, index;
    printStudentMenu();

    while (choice != 0)
    {
        if (!(cin >> choice) || choice < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">>";
            choice = -1;
            continue;
        }
        if (choice != 0)
        {
            string name, ID;
            // Parse user input for student name and ID
            if (parseforStudent(name, ID))
            {
                index = -1;
                switch (choice)
                {
                case 1:
                    addNewStudent(name, ID);
                    break;
                case 2:
                    // Select a student and display the select student menu
                    index = selectStudent(name, ID);
                    if (index != -1)
                    {
                        selectStudentMenu(index);
                    }
                    break;
                default:
                    break;
                }
            }
            printStudentMenu();
        }
    }
}

// Function to handle course-related actions and user input
void System::courseMenu()
{
    int choice = -1, index;
    printCourseMenu();

    while (choice != 0)
    {
        if (!(cin >> choice) || choice < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            cout << ">>";
            continue;
        }

        if (choice != 0)
        {
            string name, code;
            // Parse user input for course name and code
            if (parseforCourse(name, code))
            {
                index = -1;
                switch (choice)
                {
                case 1:
                    addNewCourse(name, code);
                    break;
                case 2:
                    // Select a course and display the select course menu
                    index = selectCourse(name, code);
                    if (index != -1)
                    {
                        selectCourseMenu(index);
                    }
                    break;
                default:
                    break;
                }
            }
            printCourseMenu();
        }
    }
}

// Function to handle the main menu of the system and user input for main actions
void System::mainMenu()
{
    int choice = -1;
    printMainMenu();
    while (choice != 0)
    {
        if (!(cin >> choice) || choice < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">>";
            choice = -1;
            continue;
        }

        switch (choice)
        {
        case 1:
            studentMenu();
            break;
        case 2:
            courseMenu();
            break;
        case 3:
            listAllStudents();
            break;
        case 4:
            listAllCourses();
            break;
        case 0:
            return;
        default:
            break;
        }
        printMainMenu();
    }
}