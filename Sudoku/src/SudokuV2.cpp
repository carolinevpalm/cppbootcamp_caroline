#include "../IncludeHeader/SudokuV2.h"

// Assigns value. First checks if assignment is ok. 
bool assignValue(Cell (&sudoku)[9][9], int i, int j, int value){
    bool ret = false;
    //int value = sudoku[i][j].poss[0];
    if(isSafe(sudoku, i, j, value)){
        ret = true;
        sudoku[i][j].val = value;
        sudoku[i][j].poss.clear();
        if(!removeAndUpdatePeers(sudoku, i, j)){
            //return false;
            ret = false;
        }
    }
    return ret;
}
    
// Removes possible vaules from column peers
bool removeFromColPeers(Cell (&sudoku)[9][9], int i, int j){
    bool ret = true;
	for (int row = 0; row < 9; row++){
        auto &cell = sudoku[row][j];
        cell.poss.erase(std::remove((cell.poss.begin()), (cell.poss.end()), (sudoku[i][j].val)), cell.poss.end());
        // Check that the last possible solution is not removed before value has been assigned
        if (cell.poss.empty() && cell.val == 0){
            ret = false;
        }
        // If there is only one possible value assign it and check its peers (recursive)
        else if (cell.poss.size()==1){
            int value = cell.poss[0];
            if(!assignValue(sudoku, row, j, value)){
                ret = false;
            }
        }     
	}
    return ret;
}

// Removes possible vaules from row peers
bool removeFromRowPeers(Cell (&sudoku)[9][9], int i, int j){
    bool ret = true;
	for (int col = 0; col < 9; col++){
        auto &cell = sudoku[i][col];
        cell.poss.erase(std::remove((cell.poss.begin()), (cell.poss.end()), (sudoku[i][j].val)), cell.poss.end());
        // Check that the last possible solution is not removed before value has been assigned
        if (cell.poss.empty() && cell.val == 0){
            ret = false;
        }
        // If there is only one possible value assign it and check its peers (recursive)
        else if (cell.poss.size()==1){
            int value = cell.poss[0];
            if(!assignValue(sudoku, i, col, value)){
                ret = false;
            }
        }     
	}
    return ret;
}

// Removes possible vaules from box peers
bool removeFromBoxPeers(Cell (&sudoku)[9][9], int i, int j){
    bool ret = true;
    const int boxstartrw = i - i %3;
    const int boxstartcol = j - j %3;
	for (int row = 0; row < 3; row++){
        for (int col = 0; col <3; col++){
            auto &cell = sudoku[row+boxstartrw][col+boxstartcol];
            cell.poss.erase(std::remove((cell.poss.begin()),(cell.poss.end()),(sudoku[i][j].val)),cell.poss.end());
            // Check that the last possible solution is not removed before value has been assigned
            if (cell.poss.empty() && cell.val == 0){
                ret = false;
            }
            // If there is only one possible value assign it and check its peers (recursive)
            else if (cell.poss.size()==1){
                int value = cell.poss[0];
                if(!assignValue(sudoku, row+boxstartrw, col+boxstartcol,value)){
                    ret = false;
                }
            }            
        }		
	}
    return ret;	 
}

bool removeAndUpdatePeers(Cell (&sudoku)[9][9], int i, int j){
    if (!removeFromColPeers(sudoku, i, j) || !removeFromRowPeers(sudoku, i, j) || !removeFromBoxPeers(sudoku, i, j)){
        return false;
    }
    else{return true;}
}

void checkUniqueRow(Cell (&sudoku)[9][9], int i, int j, int checkVal){
    // Count if the value being checked is in the possible soulitions for any other cell in the row, 
    // if not --> assign the value and update its peers.
    int checkValCountRow = 0;
    for (int col = 0; col < 9; col++){
        auto &cell = sudoku[i][col];
        if(std::find(cell.poss.begin(), cell.poss.end(), checkVal) != cell.poss.end()){
            checkValCountRow++;
        }     
    }
    if (checkValCountRow == 1){
            assignValue(sudoku, i, j, checkVal);
            //sudoku[i][j].val = checkVal;
            //sudoku[i][j].poss.clear();
            //removeAndUpdatePeers(sudoku, i, j);
    }
}

void checkUniqueCol(Cell (&sudoku)[9][9], int i, int j, int checkVal){
    // Count if the value being checked is in the possible soulitions for any other cell in the column, 
    // if not --> assign the value and update its peers.
    int checkValCountCol = 0;
    for (int row = 0; row < 9; row++){
        auto &cell = sudoku[row][j];
        if(std::find(cell.poss.begin(), cell.poss.end(), checkVal) != cell.poss.end()){
            checkValCountCol++;
        }
    }
    if (checkValCountCol == 1){
        assignValue(sudoku, i, j, checkVal);
        //sudoku[i][j].val = checkVal;
        //sudoku[i][j].poss.clear();
        //removeAndUpdatePeers(sudoku, i, j);
    }
}

void checkUniqueBox(Cell (&sudoku)[9][9], int i, int j, int checkVal){
    // Count if the value being checked is in the possible soulitions for any other cell in the box, 
    // if not --> assign the value and update its peers.
    const int boxstartrw = i - i %3;
    const int boxstartcol = j - j %3;
    int checkValCountBox = 0;
    for (int row = 0; row < 3; row++){
        for (int col = 0; col <3; col++){
            auto &cell = sudoku[row+boxstartrw][col+boxstartcol];
            if(std::find(cell.poss.begin(), cell.poss.end(), checkVal) != cell.poss.end()){
                checkValCountBox++;
            }
        }
    }
    if (checkValCountBox == 1){
        assignValue(sudoku, i, j, checkVal);
        //sudoku[i][j].val = checkVal;
        //sudoku[i][j].poss.clear();
        //removeAndUpdatePeers(sudoku, i, j);
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
//const bool GridFull = true;
bool checkGridFull(Cell (&sudoku)[9][9]){
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (sudoku[row][col].val == 0){
				return false;
			}
	return true;
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

//int nrGuesses;
bool guessSudoku(Cell (&sudoku)[9][9]){
    // If sudoku grid ia already full return true --> it is solved
    if (checkGridFull(sudoku)){
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
        
        //if (isSafe(sudoku, row, col, num)){ //Behövs detta eftersom man bara tar posbible och uppdaterar alla peers?

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
            //Above not needed do using std::array
            //Cell backup[9][9]; 
            //backup[9][9] = sudoku[9][9];

            //sudoku[row][col].val = num;
            //sudoku[row][col].poss.clear();
            //if(removeAndUpdatePeers(sudoku, row, col)){ // If a NOK assignment has been done go back and try a different guess otherwise continue
            if(assignValue(sudoku, row, col, num)){
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
            //sudoku[9][9] = backup[9][9];
        //}               
    }
    // If we have gone through all possible numbers for the current unassigned location, then we probably assigned a bad number early. 
    // Lets backtrack and try a different number for the previous unassigned locations.
	return false; 
}