#include "SudokuV2.h"

// Assigns value when there is only one possibility left. First checks if assignment is ok. 
bool assignValue(Cell (&sudoku)[9][9], int i, int j){
    int value = sudoku[i][j].poss[0];
    if(isSafe(sudoku, i, j, value)){
        sudoku[i][j].val = sudoku[i][j].poss[0];
        sudoku[i][j].poss.clear();
        if(!removeAndUpdatePeers(sudoku, i, j)){
            return false;
        }
    return true;
    }
    else{return false;}
}
    
// Removes possible vaules from column peers
bool removeFromColPeers(Cell (&sudoku)[9][9], int i, int j){
	for (int row = 0; row < 9; row++){
        sudoku[row][j].poss.erase(std::remove((sudoku[row][j].poss.begin()), (sudoku[row][j].poss.end()), (sudoku[i][j].val)), sudoku[row][j].poss.end());
        // Check that the last possible solution is not removed before value has been assigned
        if (sudoku[row][j].poss.empty() && sudoku[row][j].val == 0){
            return false;
        }
        // If there is only one possible value assign it and check its peers (recursive)
        if (sudoku[row][j].poss.size()==1){
            if(!assignValue(sudoku, row, j)){
                return false;
            }
        }     
	}
    return true;
}

// Removes possible vaules from row peers
bool removeFromRowPeers(Cell (&sudoku)[9][9], int i, int j){
	for (int col = 0; col < 9; col++){
        sudoku[i][col].poss.erase(std::remove((sudoku[i][col].poss.begin()), (sudoku[i][col].poss.end()), (sudoku[i][j].val)), sudoku[i][col].poss.end());
        // Check that the last possible solution is not removed before value has been assigned
        if (sudoku[i][col].poss.empty() && sudoku[i][col].val == 0){
            return false;
        }
        // If there is only one possible value assign it and check its peers (recursive)
        if (sudoku[i][col].poss.size()==1){
            if(!assignValue(sudoku, i, col)){
                return false;
            }
        }     
	}
    return true;
}

// Removes possible vaules from box peers
bool removeFromBoxPeers(Cell (&sudoku)[9][9], int i, int j){
    int boxstartrw = i - i %3;
    int boxstartcol = j - j %3;
	for (int row = 0; row < 3; row++){
        for (int col = 0; col <3; col++){
            sudoku[row+boxstartrw][col+boxstartcol].poss.erase(std::remove((sudoku[row+boxstartrw][col+boxstartcol].poss.begin()),(sudoku[row+boxstartrw][col+boxstartcol].poss.end()),(sudoku[i][j].val)),sudoku[row+boxstartrw][col+boxstartcol].poss.end());
            // Check that the last possible solution is not removed before value has been assigned
            if (sudoku[row+boxstartrw][col+boxstartcol].poss.empty() && sudoku[row+boxstartrw][col+boxstartcol].val == 0){
                return false;
            }
            // If there is only one possible value assign it and check its peers (recursive)
            if (sudoku[row+boxstartrw][col+boxstartcol].poss.size()==1){
                if(!assignValue(sudoku, row+boxstartrw, col+boxstartcol)){
                    return false;
                }
            }            
        }		
	}
    return true;	 
}

bool removeAndUpdatePeers(Cell (&sudoku)[9][9], int i, int j){
    if (!removeFromColPeers(sudoku, i, j) || !removeFromRowPeers(sudoku, i, j) || !removeFromBoxPeers(sudoku, i, j)){
        return false;
    }
    else{return true;
    /*return removeFromColPeers(sudoku, i, j) && 
    removeFromRowPeers(sudoku, i, j) && 
    removeFromBoxPeers(sudoku, i, j);*/
    }
}

void checkUniqueRow(Cell (&sudoku)[9][9], int i, int j, int checkVal){
    // Count if the value being checked is in the possible soulitions for any other cell in the row, 
    // if not --> assign the value and update its peers.
    int checkValCountRow = 0;
    for (int col = 0; col < 9; col++){
        if(std::find(sudoku[i][col].poss.begin(), sudoku[i][col].poss.end(), checkVal) != sudoku[i][col].poss.end()){
            checkValCountRow++;
        }     
    }
    if (checkValCountRow == 1){
            sudoku[i][j].val = checkVal;
            sudoku[i][j].poss.clear();
            removeAndUpdatePeers(sudoku, i, j);
    }
}

void checkUniqueCol(Cell (&sudoku)[9][9], int i, int j, int checkVal){
    // Count if the value being checked is in the possible soulitions for any other cell in the column, 
    // if not --> assign the value and update its peers.
    int checkValCountCol = 0;
    for (int row = 0; row < 9; row++){
        if(std::find(sudoku[row][j].poss.begin(), sudoku[row][j].poss.end(), checkVal) != sudoku[row][j].poss.end()){
            checkValCountCol++;
        }
    }
    if (checkValCountCol == 1){
        sudoku[i][j].val = checkVal;
        sudoku[i][j].poss.clear();
        removeAndUpdatePeers(sudoku, i, j);
    }
}

void checkUniqueBox(Cell (&sudoku)[9][9], int i, int j, int checkVal){
    // Count if the value being checked is in the possible soulitions for any other cell in the box, 
    // if not --> assign the value and update its peers.
    int boxstartrw = i - i %3;
    int boxstartcol = j - j %3;
    int checkValCountBox = 0;
    for (int row = 0; row < 3; row++){
        for (int col = 0; col <3; col++){
            if(std::find(sudoku[row+boxstartrw][col+boxstartcol].poss.begin(), sudoku[row+boxstartrw][col+boxstartcol].poss.end(), checkVal) != sudoku[row+boxstartrw][col+boxstartcol].poss.end()){
                checkValCountBox++;
            }
        }
    }
    if (checkValCountBox == 1){
        sudoku[i][j].val = checkVal;
        sudoku[i][j].poss.clear();
        removeAndUpdatePeers(sudoku, i, j);
    }
}

void checkUnique(Cell (&sudoku)[9][9]){
    for(int i{}; i !=9; ++i){
        for(int j{}; j !=9; ++j){
            if (sudoku[i][j].val ==0){
                for(int x=0; x<sudoku[i][j].poss.size(); x++){
                    int checkVal = sudoku[i][j].poss.at(x);
                    checkUniqueRow(sudoku, i, j, checkVal);
                }
            }
        }
    }

    for(int i{}; i !=9; ++i){
        for(int j{}; j !=9; ++j){
            if (sudoku[i][j].val ==0){
                for(int x=0; x<sudoku[i][j].poss.size(); x++){
                    int checkVal = sudoku[i][j].poss.at(x);
                    checkUniqueCol(sudoku, i, j, checkVal);
                }
            }
        }
    }

    for(int i{}; i !=9; ++i){
        for(int j{}; j !=9; ++j){
            if (sudoku[i][j].val ==0){
                for(int x=0; x<sudoku[i][j].poss.size(); x++){
                    int checkVal = sudoku[i][j].poss.at(x);
                    checkUniqueBox(sudoku, i, j, checkVal);
                }
            }
        }
    }
}

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

// Returns a boolean which indicates whether any assigned entry in the specified row matches the given number. 
bool usedInRow(Cell (&sudoku)[9][9], int row, int num){
	for (int col = 0; col < 9; col++)
		if (sudoku[row][col].val == num)
		{
			return true;
		}
	return false;   
}

// Returns a boolean which indicates whether any assigned entry in the specified column matches the given number. 
bool usedInCol(Cell (&sudoku)[9][9], int col, int num){
	for (int row = 0; row < 9; row++)
		if (sudoku[row][col].val == num){
			return true;
		}
	return false;  
}

// Returns a boolean which indicates whether any assigned entry within the specified 3x3 box matches the given number. 
bool usedInBox(Cell (&sudoku)[9][9], int boxStartRow, int boxStartCol, int num){
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (sudoku[row + boxStartRow][col + boxStartCol].val == num){
				return true;
			}
	return false;
}

// Returns a boolean which indicates whether it will be legal to assign num to the given row,col location.
bool isSafe(Cell (&sudoku)[9][9], int row, int col, int num){
	// Check if 'num' is not already placed in current row, current column and current 3x3 box 
	return !usedInRow(sudoku, row, num) &&
		!usedInCol(sudoku, col, num) &&
		!usedInBox(sudoku, row - row % 3, col - col % 3, num);
}

// Searches the grid to find an entry that is still unassigned. If found return false, otherwise return GridFull (true). 
const bool GridFull = true;
bool checkGridFull(Cell (&sudoku)[9][9]){
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (sudoku[row][col].val == 0){
				return false;
			}
	return GridFull;
}

// Searches grid for index with minimum possible solutions
std::pair<int, int> getMinPossible(Cell (&sudoku)[9][9]){
    int min =10; //Start at 10 since maxiumum is 9 possibilities
    int rowmin = 0;
    int colmin = 0;
	for (int row = 0; row < 9; row++){
		for (int col = 0; col < 9; col++){
            //If possible solutions is less than previous but more than 0 --> save index in array
			if ((sudoku[row][col].poss.size() < min) && (sudoku[row][col].poss.size()>0)){ 
                min = sudoku[row][col].poss.size();
				rowmin = row;
                colmin = col;
			}
        }
    }
    return std::make_pair(rowmin, colmin);
}

int nrGuesses = 0;
bool guessSudoku(Cell (&sudoku)[9][9]){
    // If sudoku grid ia already full return true --> it is solved
    if (GridFull == checkGridFull(sudoku)){
        std::cout << "\nNumber of guesses in search: "<< nrGuesses << std::endl;
        return true;
    }
    
    //Get location with minumum possible solution
    std::pair<int,int> rowAndCol = getMinPossible(sudoku);
    int row =rowAndCol.first;
    int col = rowAndCol.second;

    for (int x = 0; x < sudoku[row][col].poss.size(); x++){
        // If placing the current number in the current unassigned location, go ahead
        int num = sudoku[row][col].poss.at(x);
        
        if (isSafe(sudoku, row, col, num)){ //Behövs detta eftersom man bara tar posbible och uppdaterar alla peers?

            nrGuesses++; // Increase counter for number of guesses every time a new safe guess is made
            //std::cout << "\nNumber of guesses: "<< nrGuesses << std::endl;
            //std::cout << "Guess number: "<< num << " at [" << row << "][" << col << "]" << std::endl;
        
            // Create backup and make tentative assignment
            Cell backup[9][9]{};
            for(int i{}; i !=9; ++i){
                for(int j{}; j !=9; ++j){
                    backup[i][j] = sudoku[i][j];
                }
            }
            //Above not needed do 
            //Cell backup [9][9]{};
            //backup = sudoku;

            sudoku[row][col].val = num;
            sudoku[row][col].poss.clear();
            if(removeAndUpdatePeers(sudoku, row, col)){ // If a NOK assignment has been done go back and try a different guess otherwise continue

                //std::cout << "------------------------" << std::endl;
                //printSudokuPossibility(sudoku);
                
                // Do the same thing again recursively. If we go through all of the recursions, and in the end 
                // return true, then all of our number placements on the Soduko grid are valid and we have fully solved it
                if (guessSudoku(sudoku)){
                    return true;
                }
            }
            // As we were not able to validly go through all of the recursions, we must have an invalid number
			// placement somewhere. Lets go back and try a different number for this particular unassigned location
            
            for(int i{}; i !=9; ++i){
                for(int j{}; j !=9; ++j){
                    sudoku[i][j] = backup[i][j];
                }
            }
        }               
    }
    // If we have gone through all possible numbers for the current unassigned location, then we probably assigned a bad number early. 
    // Lets backtrack and try a different number for the previous unassigned locations.
	return false; 
}


int main(){
        
    // Enter file to solve here:
    /*std::string filename;
    std::cout << "Enter the name of your sudoku file:" << std::endl;
    std::cin >> filename;
    std::ifstream sudokufile (filename);*/

    // Fill sudoku array with elements from text file (alternative input format)
        /*for(int i{}; i !=9; ++i){
            for(int j{}; j !=9; ++j){
                sudokufile >> grid[i][j].val;
                if (grid[i][j].val !=0){
                    grid[i][j].poss.clear();
                }  
            }
        }*/


    //Start execution timer
    auto begin = std::chrono::high_resolution_clock::now();

    std::ifstream sudokufile ("SudokuListSlack.txt");
    std::string sudokustring;

    // Read input file into array
    if (sudokufile.is_open()){

        while(std::getline(sudokufile, sudokustring)){
            //std::cout << sudokustring << std::endl;
            
            auto beginPuzzle = std::chrono::high_resolution_clock::now();
            nrGuesses = 0;

            // Initialize grid with all possibilities and 0 values according to constructor in class
            Cell grid[9][9];
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
                    }
                }
            }

            //std::cout<< "\nHere are all possible solutions after rule (1) of constraint propagation:" << std::endl;
            //printSudokuPossibility(grid);

            //The following should be done in a nicer way :) Perhaps everytime we assign a value? Flytta till slutet av removeAndUpdatePeers
            checkUnique(grid);

            //std::cout<< "\nHere are all possible solutions after rule (1) and (2) of constraint propagation:" << std::endl;
            //printSudokuPossibility(grid);

            //Start brute forcing
            if (true == guessSudoku(grid)){

            // Print the sudoku solution
            std::cout<< "\nThis is the solution to your sudoku:\n" << std::endl;
            printSudoku(grid);

            auto endPuzzle = std::chrono::high_resolution_clock::now();
            auto elapsedPuzzle = std::chrono::duration_cast<std::chrono::microseconds>(endPuzzle-beginPuzzle);
            std::cout<<"\nTime to solve puzzle: " << elapsedPuzzle.count() << " micro seconds" << std::endl;

            std::cout<<"-----------------------------------------\n"<<std::endl;

            

            }
            else {std::cout << "\nThere is no solution to your sudoku" << std::endl;}

        }

    }
    else {std::cout << "Can't open the file" << std::endl;}

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"\n\nTotal time of execution: " << elapsed.count() << " micro seconds\n\n" << std::endl;

    return 0;
}

//TODO: move location of constraint propagation (2) so it is included in guessing. 

