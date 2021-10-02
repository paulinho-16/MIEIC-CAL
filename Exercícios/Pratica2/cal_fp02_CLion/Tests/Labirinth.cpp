/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}

bool Labirinth::findGoalRecursive(int x, int y) {
    // Check if this position is worth visiting (limits checking could
    // be omitted because the labyrinth is surrounded by walls)
    if (x < 0 || y < 0 || x >= 10 || y >= 10 || labirinth[x][y] == 0 || visited[x][y])
        return false;
    // Mark as visited
    visited[x][y] = true;
    // Check if the exit was reached
    if (labirinth[x][y] == 2) {
        cout << " Reached the goal!" << endl;
        return true;
    }
    // Try all the adjacent cells
    return findGoalRecursive(x-1,y) || findGoalRecursive(x+1,y) || findGoalRecursive(x,y-1) || findGoalRecursive(x,y+1);
}

bool Labirinth::findGoal(int x, int y)
{
    printLabirinth();
    initializeVisited();
    return findGoalRecursive(x,y);
}


