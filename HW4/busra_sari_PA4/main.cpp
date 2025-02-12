// main.cpp
#include "war.h"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));
    War war;

    do
    {
        war.SimulateOneStep();
    } while (!war.isItFinish());

    war.whoWon();

    return 0;
}
