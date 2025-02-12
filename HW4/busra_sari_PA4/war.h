// war.h

#ifndef WAR_H
#define WAR_H

class Robot;

class War
{
private:
    static const int GRID_SIZE = 10;
    static const int INITIAL_COUNT_OF_EACH_ROBOT_TYPE = 5;

    Robot *grid[GRID_SIZE][GRID_SIZE];
    static int numofDead;

public:
    War();
    ~War();

    void createGrid();
    void choose_direction(int row, int col, int &newRow, int &newCol) const;
    void SimulateOneStep();
    void move(int x, int y, int nx, int ny);
    void fight(int x, int y, int nx, int ny);
    void hit_message(Robot *attacker, Robot *victim, int hitNum) const;
    void Display();
    void chooseNullCell(int &x, int &y) const;
    void chooseRobot(int &x, int &y) const;
    bool isItFinish();
    void resetMovedFlags();
    void swap(Robot *&a, Robot *&b) const;
    void whoWon();
};

#endif // WAR_H
