/*#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>*/
#include "SudokuV2.h"

// Removes possible vaules from column peers
void removeFromColPeers(Cell (&sudoku)[9][9], int i, int j){
    //int value = sudoku[i][j].val;
	for (int row = 0; row < 9; row++){
        sudoku[row][j].poss.erase(std::remove((sudoku[row][j].poss.begin()), (sudoku[row][j].poss.end()), (sudoku[i][j].val)), sudoku[row][j].poss.end());
        // If there is only one possible value assign it and check its peers
        if (sudoku[row][j].poss.size()==1){
            sudoku[row][j].val = sudoku[row][j].poss[0];
            sudoku[row][j].poss.clear();
            removeAndUpdatePeers(sudoku, row, j);
        }
        //std::remove(sudoku[row][j].poss.begin(), sudoku[row][j].poss.end(), value); this does not remove the element completely!
        //std::erase(sudoku[row][j].poss,value); from c++ 20
		}
}

// Removes possible vaules from row peers
void removeFromRowPeers(Cell (&sudoku)[9][9], int i, int j){
	for (int col = 0; col < 9; col++){
        sudoku[i][col].poss.erase(std::remove((sudoku[i][col].poss.begin()), (sudoku[i][col].poss.end()), (sudoku[i][j].val)), sudoku[i][col].poss.end());
        // If there is only one possible value assign it and check its peers
        if (sudoku[i][col].poss.size()==1){
            sudoku[i][col].val = sudoku[i][col].poss[0];
            sudoku[i][col].poss.clear();
            removeAndUpdatePeers(sudoku, i, col);
        }
	}
}

// Removes possible vaules from box peers
void removeFromBoxPeers(Cell (&sudoku)[9][9], int i, int j){
    int boxstartrw = i - i %3;
    int boxstartcol = j - j %3;
	for (int row = 0; row < 3; row++){
        for (int col = 0; col <3; col++){
            sudoku[row+boxstartrw][col+boxstartcol].poss.erase(std::remove((sudoku[row+boxstartrw][col+boxstartcol].poss.begin()),(sudoku[row+boxstartrw][col+boxstartcol].poss.end()),(sudoku[i][j].val)),sudoku[row+boxstartrw][col+boxstartcol].poss.end());
            // If there is only one possible value assign it and check its peers
            if (sudoku[row+boxstartrw][col+boxstartcol].poss.size()==1){
                sudoku[row+boxstartrw][col+boxstartcol].val = sudoku[row+boxstartrw][col+boxstartcol].poss[0];
                sudoku[row+boxstartrw][col+boxstartcol].poss.clear();
                removeAndUpdatePeers(sudoku, row+boxstartrw, col+boxstartcol);
            }
        }		
	}	 
}

void removeAndUpdatePeers(Cell (&sudoku)[9][9], int i, int j){
    removeFromColPeers(sudoku, i, j); 
    removeFromRowPeers(sudoku, i, j); 
    removeFromBoxPeers(sudoku, i, j);
}

/*bool solveSudoku(Cell sudoku[9][9]){
    if 

    return true;
}*/




void printSudoku(Cell sudoku[9][9]){
    for (int i=0; i!=9; ++i){
        for (int j=0; j!=9; ++j){
            std::cout << sudoku[i][j].val << " ";
            }
            std::cout << std::endl;
    }
}

void printSudokuPossibility(Cell sudoku[9][9]){
    for (int i=0; i!=9; ++i){
        for (int j=0; j!=9; ++j){
            if (sudoku[i][j].poss.size()>0){
                std::cout << "{" ;
                for(int x=0; x<sudoku[i][j].poss.size(); x++){
                    std::cout << sudoku[i][j].poss.at(x);
                }
                std::cout << "}\t";

            }
            else {
                std::cout << sudoku[i][j].val << " \t";
            }
        }
        std::cout << std::endl;
    }
}

int main(){

    // Initialize grid with all possibilities and 0 values according to constructor in class
    Cell grid[9][9];
    
    
    // Enter file to solve here:
    std::string filename;
    std::cout << "Enter the name of your sudoku file:" << std::endl;
    std::cin >> filename;
    //std::ifstream sudokufile ("EasySudoku.txt");
    std::ifstream sudokufile (filename);

    // Read input file into array
    if (sudokufile.is_open()){

        // Fill sudoku array with elements from text file
        for(int i{}; i !=9; ++i){
            for(int j{}; j !=9; ++j){
              sudokufile >> grid[i][j].val;
              if (grid[i][j].val !=0){
                  grid[i][j].poss.clear();
              }  
            }
        }

        // Print the sudoku
        std::cout<< "This is the sudoku to solve:" << std::endl;
        printSudoku(grid);
        

        //Start solving
        for(int i{}; i !=9; ++i){
            for(int j{}; j !=9; ++j){
                if (grid[i][j].val !=0){
                    removeAndUpdatePeers(grid, i, j);   
                }
            }
        }

        std::cout<< "This is the solution:" << std::endl;
        printSudoku(grid);
        //Uncomment if you want to see possible solutions in grid
        /*std::cout<< "Here are all possible solutions:" << std::endl;
        printSudokuPossibility(grid);*/

    }
    else {std::cout << "Can't open the file" << std::endl;}

}

