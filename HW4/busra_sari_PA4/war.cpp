// war.cpp
#include "war.h"
#include "robot.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

// Static member initialization
int War::numofDead = 0;

// Constructor
War::War()
{
    // Initialize the grid with nullptrs
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = nullptr;
        }
    }
    // Create the initial grid of robots
    createGrid();
}

// Destructor
War::~War()
{
    // Delete dynamically allocated robots
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] != nullptr)
                delete (grid[i][j]);
        }
    }
}

// Move a robot from one cell to another
void War::move(int x, int y, int nx, int ny)
{
    grid[nx][ny] = grid[x][y];
    grid[x][y] = nullptr;
    grid[nx][ny]->setMoved(true);
}

// Perform a fight between two robots
void War::fight(int x, int y, int nx, int ny)
{
    Robot **attacker = &grid[x][y];
    Robot **victim = &grid[nx][ny];

    int hitNum = 0;
    int flag = 0;

    while (true)
    {
        hitNum = (*attacker)->getDamage();
        (*victim)->setHitpointsBeforeHit((*victim)->getHitpoints());
        (*victim)->setHitpoints((*victim)->getHitpoints() - hitNum);
        hit_message(*attacker, *victim, hitNum);

        if ((*victim)->isItDead())
        {
            numofDead++;
            *victim = nullptr;
            (*attacker)->setMoved(true);
            flag = 1;
        }

        if ((*attacker)->isItDead())
        {
            numofDead++;
            *attacker = nullptr;
            flag = 1;
        }

        if (flag == 1)
        {
            break;
        }

        if ((*attacker)->getStrength() == 3 && (*victim)->getStrength() != 3) // Eğer attacker'ın gücü 3 ise
        {
            hitNum = (*attacker)->getDamage(); // Saldırıyı tekrarla
            (*victim)->setHitpointsBeforeHit((*victim)->getHitpoints());
            (*victim)->setHitpoints((*victim)->getHitpoints() - hitNum);
            hit_message(*attacker, *victim, hitNum);

            if ((*victim)->isItDead()) // İkinci saldırı sonrasında hedef öldü mü?
            {
                numofDead++;
                *victim = nullptr;
                (*attacker)->setMoved(true);
            }
        }

        swap(*attacker, *victim);
    }
    std::cout << std::endl;
}

// Swap two robot pointers
void War::swap(Robot *&a, Robot *&b) const
{
    Robot *temp = a;
    a = b;
    b = temp;
}

// Print hit message during a fight
void War::hit_message(Robot *attacker, Robot *victim, int hitNum) const
{
    std::cout << attacker->getName() << "(";
    if (attacker->getStrength() == 10)
        std::cout << "10";
    else
        std::cout << attacker->getHitpoints();

    std::cout << ")"
              << " hits " << victim->getName() << "(" << victim->getHitpointsBeforeHit() << ")"
              << " with " << hitNum << std::endl;

    if (victim->isItDead())
    {
        std::cout << "The new hitpoints of " << victim->getName() << " is 0" << std::endl;
        std::cout << victim->getName() << " is dead" << std::endl;
    }
    else
    {
        std::cout << "The new hitpoints of " << victim->getName() << " is " << victim->getHitpoints() << std::endl;
    }

    if (attacker->isItDead())
    {
        std::cout << "The new hitpoints of " << attacker->getName() << " is 0" << std::endl;
        std::cout << attacker->getName() << " is dead" << std::endl;
    }
}

// Randomly choose a direction for a robot to move
void War::choose_direction(int row, int col, int &newRow, int &newCol) const
{
    do
    {
        int direction = rand() % 4;

        switch (direction)
        {
        case 0:
            if (row != 0)
            {
                newRow = row - 1;
                return;
            }
            break;
        case 1:
            if (row != 9)
            {
                newRow = row + 1;
                return;
            }
            break;
        case 2:
            if (col != 9)
            {
                newCol = col + 1;
                return;
            }
            break;
        case 3:
            if (col != 0)
            {
                newCol = col - 1;
                return;
            }
            break;
        }
    } while (true);
}

// Create the initial grid of robots
void War::createGrid()
{
    int x, y;
    for (int i = 0; i < INITIAL_COUNT_OF_EACH_ROBOT_TYPE; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            chooseNullCell(x, y);
            switch (j)
            {
            case 0:
                grid[x][y] = new RoboCop();
                break;
            case 1:
                grid[x][y] = new Bulldozer();
                break;
            case 2:
                grid[x][y] = new Roomba();
                break;
            case 3:
                grid[x][y] = new Kamikaze();
                break;
            case 4:
                grid[x][y] = new OptimusPrime();
                break;
            default:
                break;
            }
        }
    }
}

// Choose a random empty cell in the grid
void War::chooseNullCell(int &x, int &y) const
{
    do
    {
        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;
    } while (grid[x][y] != nullptr);
}

// Choose a random cell with a robot in the grid
void War::chooseRobot(int &x, int &y) const
{
    do
    {
        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;
    } while (grid[x][y] == nullptr);
}

// Display the grid
void War::Display()
{
    std::cout << std::endl;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] == nullptr)
            {
                std::cout << ". ";
            }
            else if (grid[i][j]->getStrength() == 100)
            {
                std::cout << "O ";
            }
            else if (grid[i][j]->getStrength() == 30)
            {
                std::cout << "R ";
            }
            else if (grid[i][j]->getStrength() == 3)
            {
                std::cout << "r ";
            }
            else if (grid[i][j]->getStrength() == 50)
            {
                std::cout << "B ";
            }
            else if (grid[i][j]->getStrength() == 10)
            {
                std::cout << "K ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Simulate one step of the war
void War::SimulateOneStep()
{
    // Reset moved flags of all robots
    resetMovedFlags();
    int x, y, nx, ny;
    // Choose a random robot
    chooseRobot(x, y);
    nx = x;
    ny = y;
    // Choose a random direction for the robot to move
    choose_direction(x, y, nx, ny);

    // Move the robot until it encounters another robot or reaches the grid boundary
    while (grid[nx][ny] == nullptr)
    {
        move(x, y, nx, ny);
        x = nx;
        y = ny;
        choose_direction(x, y, nx, ny);
    }
    // Fight between the two encountered robots
    fight(x, y, nx, ny);
}

// Reset moved flags of all robots
void War::resetMovedFlags()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] != nullptr)
                grid[i][j]->setMoved(false);
        }
    }
}

// Check if the war is finished
bool War::isItFinish()
{
    return numofDead == 24; // 24 robots in total
}

// Display the winner(s) of the war
void War::whoWon()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] != nullptr)
            {
                std::cout << grid[i][j]->getName() << " win" << std::endl
                          << std::endl;
            }
        }
    }
}
