/**
 * File: maze-generator.cpp
 * ------------------------
 * Presents an adaptation of Kruskal's algorithm to generate mazes.
 */

#include <iostream>
using namespace std;
#include "maze-graphics.h"
#include "maze-types.h"
#include "console.h"
#include "simpio.h"
#include <vector.h>

static int getMazeDimension(string prompt,
                            int minDimension = 7, int maxDimension = 50) {
    while (true) {
        int response = getInteger(prompt);
        if (response == 0) return response;
        if (response >= minDimension && response <= maxDimension) return response;
        cout << "Please enter a number between "
             << minDimension << " and "
             << maxDimension << ", inclusive." << endl;
    }
}

set<wall>create_wall(vector<vector<cell>>cells,int dimension)
{
    set<wall>walls;
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension-1; j++)
        {
            wall wall;
            wall.one = cells[i][j];
            wall.two = cells[i][j+1];
            walls.insert(wall);
        }
    }
    for (int i = 0; i < dimension-1; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            wall wall;
            wall.one = cells[i][j];
            wall.two = cells[i+1][j];
            walls.insert(wall);
        }
    }
    return walls;
}

vector<vector<cell>>create_cell(int dimension)
 {
    vector<vector<cell>>cells;
    for (int i = 0; i < dimension; i++)
    {
        vector<cell>temp;
        for (int j = 0; j < dimension; j++)
        {
            cell cells;
            cells.col = i ;
            cells.row = j ;
            temp.push_back(cells);
        }
        cells.push_back(temp);
    }
    return cells;
 }

void remove_walls(vector<wall>walls)
{
    set<int>had_remove_wall;
    random_shuffle(walls.begin(),walls.end());

}

int main() {
    while (true) {
        int dimension = getMazeDimension("What should the dimension of your maze be [0 to exit]? ");
        if (dimension == 0) break;
        MazeGeneratorView window;
        window.setDimension(dimension);
        vector<vector<cell>>cells = create_cell(dimension);
        set<wall>walls = create_wall(cells,dimension);
        window.addAllWalls(walls);
        cout << "This is where I'd animate the construction of a maze of dimension " << dimension << "." << endl;
        system("pause");
    }

    return 0;
}
