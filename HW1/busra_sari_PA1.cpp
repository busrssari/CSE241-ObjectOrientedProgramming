/*
  The code is a Mastermind game implementation in C++.
  To compile the program, use: g++ -std=c++11 busra_sari_PA1.cpp
  After compiling, run the program using ./a.out
  When prompted, type either "mastermind -r 6" or "mastermind -u 12345a"
*/

#include <iostream>
#include <ctime>

using namespace std;

// Function to calculate the length of a character array
int length(char newInput[])
{
    int size = 0;
    if (newInput[0] == '0')
    {
        return 0;
    }
    while (newInput[size] != '\0')
    {
        size++;
    }
    return size;
}

// Function to check if a digit is present in the secret array
bool find(char secret[], char digit)
{
    int index = 0;
    while (secret[index] != '\0')
    {
        if (secret[index] == digit)
        {
            return true;
        }
        index++;
    }
    return false;
}

// Function to create a secret code
void createSecret(char (&secret)[15], int length)
{
    char list[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e'};
    int i = 0, index;
    char digit;

    srand(time(0));
    for (i = 0; i < length; i++)
    {
        index = rand() % 15;
        digit = list[index];

        // Check for leading zero
        if (i == 0 && index == 0)
        {
            i--;
        }
        // Check for duplicate digits
        else if (find(secret, digit) == 1)
        {
            i--;
        }
        else
        {
            secret[i] = list[index];
        }
    }
    secret[i] = '\0';
}

// Function to compare the user input with the secret code
bool compare(char secret[], char newInput[])
{
    int first = 0, second = 0;
    int size = length(secret);

    // Counting correct digits in correct position (first)
    for (int i = 0; i < size; i++)
    {
        if (newInput[i] == secret[i])
        {
            first++;
        }
    }

    // If all digits are in the correct position, game is won
    if (first == size)
    {
        return true;
    }
    // If not, count correct digits in wrong position (second)
    else
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (newInput[i] == secret[j] && i != j)
                {
                    second++;
                }
            }
        }
        cout << first << " " << second << endl;
        return false;
    }
}

// Function to check if the secret number is found or if the maximum attempts are reached
bool isSecretNum(char secret[], char newInput[], int iter)
{
    if (compare(secret, newInput) == 1)
    {
        cout << "found " << iter << endl;
        return true;
    }
    else if (iter == 100)
    {
        cout << "failed " << endl;
        return true;
    }
    return false;
}

// Function to check if the length of the input matches the length of the secret code
bool E1(char secret[], char newInput[])
{
    if (length(newInput) != length(secret))
    {
        cout << "E1" << endl;
        return 1;
    }
    return 0;
}

// Function to check if the input contains valid characters
bool E2(char newInput[])
{
    char list[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e'};
    int count = 0, size;
    size = length(newInput);

    // Counting characters that are valid
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (newInput[i] == list[j])
            {
                count++;
                break;
            }
        }
    }

    // If the count is not equal to the size, invalid characters are present
    if (count != size)
    {
        cout << "E2" << endl;
        return true;
    }

    return false;
}

// Function to convert a character array to an integer
int toInt_fromChar(char thirdInput[])
{
    int num = 1, total = 0;
    int size = length(thirdInput);

    for (int i = 0; i < size; i++)
    {
        num = thirdInput[i] - '0';
        for (int j = i; j < size - 1; j++)
        {
            num *= 10;
        }
        total += num;
    }

    return total;
}

// Function to check if the input size for option -r is valid
bool isValidSizeR(char thirdInput[])
{
    if (thirdInput[0] == '-')
    {
        cout << "E0" << endl;
        return false;
    }
    int size = toInt_fromChar(thirdInput);

    // Checking if the size is within the valid range
    if (size <= 0 || size > 15)
    {
        cout << "E0" << endl;
        return false;
    }
    return true;
}

// Function to check if the input size is valid
bool isValidSize(char newInput[])
{
    int size = length(newInput);
    if (size <= 0 || size > 15)
    {
        cout << "E0" << endl;
        return false;
    }
    return true;
}

// Function to check if the input contains unique digits
bool isUnique(char newInput[])
{
    int size = length(newInput);

    // Checking for duplicate digits
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (newInput[i] == newInput[j] && i != j)
            {
                cout << "E0" << endl;
                return false;
            }
        }
    }
    return true;
}

// Function to check if the parameters passed to the program are correct
bool wrongParameters(char str[], char option[])
{
    char _str[] = {'m', 'a', 's', 't', 'e', 'r', 'm', 'i', 'n', 'd'};

    // Checking for correct length and characters in the parameters
    if (length(option) != 2 || length(str) != 10)
    {
        cout << "E0" << endl;
        return true;
    }

    for (int i = 0; i < 10; i++)
    {
        if (str[i] != _str[i])
        {
            cout << "E0" << endl;
            return true;
        }
    }

    // Checking for valid option format
    if (option[0] != '-' || (option[1] != 'u' && option[1] != 'r'))
    {
        cout << "E0" << endl;
        return true;
    }

    return false;
}

// Function to run the mastermind game
void mastermind(char secret[])
{
    char newInput[20];
    int iter = 0;

    do
    {
        cin >> newInput;

        if (!isValidSize(newInput))
        {
            return;
        }

        if (!isUnique(newInput))
        {
            return;
        }

        if (E1(secret, newInput))
        {
            return;
        }

        if (E2(newInput))
        {
            return;
        }

        iter++;

    } while (isSecretNum(secret, newInput, iter) == 0);
}

int main(int argc, char *argv[])
{
    char str[20];
    char option[20];
    char thirdInput[20];
    cin >> str >> option >> thirdInput;

    if (!wrongParameters(str, option))
    {
        if (option[1] == 'r')
        {
            char secret[15];

            if (isValidSizeR(thirdInput))
            {
                int size = toInt_fromChar(thirdInput);
                createSecret(secret, size);
                mastermind(secret);
            }
        }

        if (option[1] == 'u')
        {
            if (isValidSize(thirdInput))
            {
                if (!E2(thirdInput))
                {
                    if (isUnique(thirdInput))
                    {
                        mastermind(thirdInput);
                    }
                }
            }
        }
    }
    return 0;
}
