/**
 * File: life.cpp
 * --------------
 * Implements the Game of Life.
 */

#include <iostream>
#include <fstream>// for cout
using namespace std;

#include "console.h" // required of all files that contain the main function
#include "simpio.h"  // for getLine
#include "gevent.h" // for mouse event detection
#include "strlib.h"
#include "filelib.h"

#include "life-constants.h"  // for kMaxAge
#include "life-graphics.h"   // for class LifeDisplay

/**
 * Function: welcome
 * -----------------
 * Introduces the user to the Game of Life and its rules.
 */
static void welcome() {
    cout << "Welcome to the game of Life, a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells live and die by the following rules:" << endl << endl;
    cout << "\tA cell with 1 or fewer neighbors dies of loneliness" << endl;
    cout << "\tLocations with 2 neighbors remain stable" << endl;
    cout << "\tLocations with 3 neighbors will spontaneously create life" << endl;
    cout << "\tLocations with 4 or more neighbors die of overcrowding" << endl << endl;
    cout << "In the animation, new cells are dark and fade to gray as they age." << endl << endl;
    getLine("Hit [enter] to continue....   ");
}

/**
 * Function: main
 * --------------
 * Provides the entry point of the entire program.
 *
 *
 */
void getfile(ifstream &ifs){
    while (true)
    {
        string name =getLine("file name");
        if(!fileExists(name))
        {
            cout<<"wrong file"<<endl;
        }
        else{
            ifs.open(name);
            break;
        }
    }
}
Grid<char> creat_vector(ifstream &ifs)
{
    int a,b;
    ifs>>a;
    ifs>>b;
    Grid<char>cells(a,b);
    for (int i = 0; i < a; ++i)
    {
        for (int j = 0; j <b; ++j)
        {
            char world;
            ifs>>world;
            cells.set(i,j,world);
        }
    }
    return cells;
}
void count_neigh(Grid<char>&cells,bool s);
void print_vector(Grid<char>&cells)
{
    for (int i = 0; i < cells.numRows(); ++i)
    {
        for (int j = 0; j < cells.numCols(); ++j)
        {
            cout<<cells.get(i,j);
        }
        cout<<endl;
    }
}
bool warp()
{
    char s;
    while(true)
    {
        cout<<"Should the simulation wrap around the grid (y/n)?";
        cin>>s;
        s=toLowerCase(s);
        if(s=='y'||s=='n')
        {
            break;
        }
        cout<<"Invalid input. Please enter 'y' or 'n'.";
    }
    switch (s) {
    case 'y':
        return true;
    case 'n':
        return false;
    default :
        return false;
    }
}
bool select_warp(){
    return warp();
}
void menu(Grid<char>&cells,bool s);
 int main() {
    LifeDisplay display;
    display.setTitle("Game of Life");
    welcome();
    ifstream ifs;
    getfile(ifs);
    Grid<char>cells=creat_vector(ifs);
    print_vector(cells);
    bool s=select_warp();
    menu(cells,s);
    return 0;    
}


void count_neigh(Grid<char>&cells,bool s)
{
    Grid<char>next_cells(cells.numCols(),cells.numCols());
    if(s)
    {
        for (int i = 0; i < cells.numRows(); ++i)
        {
            for (int j = 0; j < cells.numCols(); ++j)
            {
                int cell_number=0;
                for (int k = -1; k <= 1; ++k)
                {
                    for (int l = -1; l <= 1; ++l)
                    {
                        if (k != 0 || l != 0) {
                            if( cells.inBounds(i+k,j+l)&&cells.get(i+k,j+l)=='X')
                            {
                                cell_number++;
                            }
                            else if (!cells.inBounds(i+k,j+l)&&
                                     cells.get((i+k+cells.numRows())%cells.numRows(),
                                               (j+l+cells.numCols())%cells.numCols())=='X')
                            {
                                cell_number++;
                            }
                        }

                    }
                }
                 //cout<<cell_number;
                switch (cell_number) {
                case 1:
                    next_cells.set(i,j,'-');
                    break;
                case 2:
                    next_cells.set(i,j,cells.get(i,j));
                    break;
                case 3:
                    next_cells.set(i,j,'X');
                    break;
                default:next_cells.set(i,j,'-');
                    break;
                }

            }    }}
    else
    {
        for (int i = 0; i < cells.numRows(); ++i)
        {
            for (int j = 0; j < cells.numCols(); ++j)
            {
                int cell_number=0;
                for (int k = -1; k <= 1; ++k)
                {
                    for (int l = -1; l <= 1; ++l)
                    {
                        if (k != 0 || l != 0) {
                            if( cells.inBounds(i+k,j+l)&&cells.get(i+k,j+l)=='X')
                            {
                                cell_number++;
                            }
                        }

                    }
                }
                cout<<cell_number;
                switch (cell_number) {
                case 1:
                    next_cells.set(i,j,'-');
                    break;
                case 2:
                    next_cells.set(i,j,cells.get(i,j));
                    break;
                case 3:
                    next_cells.set(i,j,'X');
                    break;
                default:next_cells.set(i,j,'-');
                    break;
                }
            }cout<<endl;
        }
    }
    print_vector(next_cells);
    cells=next_cells;
}
void menu(Grid<char>&cells,bool s)
{
    string input;
    FLAG:
    cout<<"a)nimate, t)ick, q)uit?";
    cin>>input;
    while(cin.peek()!='\n'||!cin)
    {
        cout<<"Invalid choice; please try again."<<endl;
        goto FLAG;
    }
    char select=input[0];
    switch (select) {
    case 't':
        count_neigh(cells,s);
        goto FLAG;
    case 'q':
        cout<<"Have a nice Life!"<<endl;
        break;
    default:
        cout<<"Invalid choice; please try again."<<endl;
        break;
    }
}
