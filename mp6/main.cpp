#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;

int main()
{
    // Write your own main here
    SquareMaze myMaze;
    myMaze.makeMaze(40, 40);
    PNG* mazePng = myMaze.drawCreativeMaze();
    mazePng->writeToFile("creative.png");
    delete mazePng;
    cout << "Add your own tests here! Modify main.cpp" << endl;
    return 0;
}
