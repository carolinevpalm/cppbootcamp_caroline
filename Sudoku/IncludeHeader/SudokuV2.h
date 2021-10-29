#ifndef SUDOKUV2_H_
#define SUDOKUV2_H_

#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <chrono>

class Cell {
    public:
        int val;
        std::vector<int> poss;
        Cell(){
            val = 0;
            poss.assign({1,2,3,4,5,6,7,8,9});
        }

}; //What functions should be included here?

/*class Grid : public Cell {
    public:
        //const size_t rows;
        //const size_t cols;
        std::array<std::array<Cell,9>,9> grid;
        Grid(){
            grid =  
        } 
};*/

using grid_t = std::array<std::array<Cell,9>,9>;


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

extern int nrGuesses;












#endif /*SUDOKUV2_H_ */