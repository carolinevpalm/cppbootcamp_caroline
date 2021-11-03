#include "IncludeHeader/SudokuV2.h"

int nrGuesses;
int main(){

    //Start execution timer
    auto begin = std::chrono::high_resolution_clock::now();

    std::ifstream sudokufile ("InputSudokus/SudokuListSlack.txt");
    std::string sudokustring;
    int totalNrGuesses = 0;

    // Read input file into array
    if (sudokufile.is_open()){

        while(std::getline(sudokufile, sudokustring)){
            //std::cout << sudokustring << std::endl;
            
            auto beginPuzzle = std::chrono::high_resolution_clock::now();
            nrGuesses = 0;

            // Initialize grid with all possibilities and 0 values according to constructor in class
            Cell grid[9][9];
            //grid_t grid2;
            
            int i = 0;
            int j = 0;
            for (char c:sudokustring){
                if(c != '.'){ //skip if .
                    grid[i][j].val = c - '0'; //convert char to int
                    grid[i][j].poss.clear();
                }
                j++;
                if (j == 9){
                    i++;
                    j=0;
                }
            }

            // Print the sudoku
            std::cout<<"-----------------------------------------"<<std::endl;
            std::cout<< "This is the sudoku to solve:\n" << std::endl;
            printSudoku(grid);
            
            //Start solving, this could be done in the previous loop but since I want to print I splitted it
            for(int i{}; i !=9; ++i){
                for(int j{}; j !=9; ++j){
                    if (grid[i][j].val !=0){
                        removeAndUpdatePeers(grid, i, j);
                        //std::cout<< "\n ---------------" << std::endl;
                        //printSudokuPossibility(grid);   
                    }
                }
            }

            std::cout<< "\nHere are all possible solutions after constraint propagation:" << std::endl;
            printSudokuPossibility(grid);

            //Start guessing
            if (true == guessSudoku(grid)){

                // Print the sudoku solution
                std::cout<< "\nThis is the solution to your sudoku:\n" << std::endl;
                printSudoku(grid);

                std::cout << "\nNumber of guesses in search: "<< nrGuesses << std::endl;

                auto endPuzzle = std::chrono::high_resolution_clock::now();
                auto elapsedPuzzle = std::chrono::duration_cast<std::chrono::microseconds>(endPuzzle-beginPuzzle);
                std::cout<<"\nTime to solve puzzle: " << elapsedPuzzle.count() << " micro seconds" << std::endl;

                std::cout<<"-----------------------------------------\n"<<std::endl;
            }
            else {std::cout << "\nThere is no solution to your sudoku" << std::endl;}

            
            totalNrGuesses += nrGuesses;
            
        }

    }
    else {std::cout << "Can't open the file" << std::endl;}

    
    std::cout << "\n\nTotal number of guesses for all puzzles: "<< totalNrGuesses << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"\nTotal time of execution: " << elapsed.count() << " micro seconds\n\n" << std::endl;

    return 0;
}


