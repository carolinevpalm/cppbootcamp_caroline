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

void removeAndUpdatePeers(Cell (&sudoku)[9][9], int i, int j);
void removeFromColPeers(Cell (&sudoku)[9][9], int i, int j);
void removeFromRowPeers(Cell (&sudoku)[9][9], int i, int j);
void removeFromBoxPeers(Cell (&sudoku)[9][9], int i, int j);
void assignValue(Cell (&sudoku)[9][9], int i, int j);
void checkUniqueRow(Cell (&sudoku)[9][9], int i, int j, int checkVal);
void checkUniqueCol(Cell (&sudoku)[9][9], int i, int j, int checkVal);
void checkUniqueBox(Cell (&sudoku)[9][9], int i, int j, int checkVal);
bool isSafe(Cell (&sudoku)[9][9], int row, int col, int num);
bool used_in_box(Cell (&sudoku)[9][9], int box_start_rpw, int box_start_col, int num);
bool used_in_col(Cell (&sudoku)[9][9], int col, int num);
bool used_in_row(Cell (&sudoku)[9][9], int row, int num);












#endif /*SUDOKUV2_H_ */