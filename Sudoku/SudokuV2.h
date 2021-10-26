#ifndef SUDOKUV2_H_
#define SUDOKUV2_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>

/*typedef struct cell { //Gör om till Class?
    int val;
    std::vector<int> poss;

    //What functions should be included here?

}Cell;*/

class Cell {
    public:
        int val;
        std::vector<int> poss;
        Cell(){
            val = 0;
            poss.assign({1,2,3,4,5,6,7,8,9});
        }

}; //What functions should be included here?

void printSudoku(Cell sudoku[9][9]);
void printSudokuPossibility(Cell sudoku[9][9]);

bool removeAndUpdatePeers(Cell (&sudoku)[9][9], int i, int j);
bool removeFromColPeers(Cell (&sudoku)[9][9], int i, int j);
bool removeFromRowPeers(Cell (&sudoku)[9][9], int i, int j);
bool removeFromBoxPeers(Cell (&sudoku)[9][9], int i, int j);
bool assignValue(Cell (&sudoku)[9][9], int i, int j);
void checkUniqueRow(Cell (&sudoku)[9][9], int i, int j, int checkVal);
void checkUniqueCol(Cell (&sudoku)[9][9], int i, int j, int checkVal);
void checkUniqueBox(Cell (&sudoku)[9][9], int i, int j, int checkVal);
void checkUnique(Cell (&sudoku)[9][9]);
bool isSafe(Cell (&sudoku)[9][9], int row, int col, int num);
bool usedInBox(Cell (&sudoku)[9][9], int boxStartRow, int boxStartCol, int num);
bool usedInCol(Cell (&sudoku)[9][9], int col, int num);
bool usedInRow(Cell (&sudoku)[9][9], int row, int num);
bool guessSudoku(Cell (&sudoku)[9][9]);












#endif /*SUDOKUV2_H_ */