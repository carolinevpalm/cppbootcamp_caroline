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
    //return false;
    //int value = sudoku[i][j].val;
	for (int row = 0; row < 9; row++){
        sudoku[row][j].poss.erase(std::remove((sudoku[row][j].poss.begin()), (sudoku[row][j].poss.end()), (sudoku[i][j].val)), sudoku[row][j].poss.end());
        // If there is only one possible value assign it and check its peers (recursive)
        if (sudoku[row][j].poss.empty() && sudoku[row][j].val == 0){
            return false;
            //return true;
        }
        
        if (sudoku[row][j].poss.size()==1){
            if(!assignValue(sudoku, row, j)){
                return false;
            }
            
            //sudoku[row][j].val = sudoku[row][j].poss[0];
            //sudoku[row][j].poss.clear();
            //removeAndUpdatePeers(sudoku, row, j);
        }
        //std::remove(sudoku[row][j].poss.begin(), sudoku[row][j].poss.end(), value); this does not remove the element completely!
        //std::erase(sudoku[row][j].poss,value); from c++ 20
       
	}
    return true;

}

// Removes possible vaules from row peers
bool removeFromRowPeers(Cell (&sudoku)[9][9], int i, int j){
    //return false;
	for (int col = 0; col < 9; col++){
        sudoku[i][col].poss.erase(std::remove((sudoku[i][col].poss.begin()), (sudoku[i][col].poss.end()), (sudoku[i][j].val)), sudoku[i][col].poss.end());
        // If there is only one possible value assign it and check its peers (recursive)
        if (sudoku[i][col].poss.empty() && sudoku[i][col].val == 0){
            return false;
            //return true;
        }
        
        if (sudoku[i][col].poss.size()==1){
            if(!assignValue(sudoku, i, col)){
                return false;
            }
            //if (isSafe(sudoku, i, col, sudoku[i][col].val)){
                //sudoku[i][col].val = sudoku[i][col].poss[0];
                //sudoku[i][col].poss.clear();
                //removeAndUpdatePeers(sudoku, i, col);
                //return true;
            //}
            //else{return false;}
        }
       

	}
    return true;
}

// Removes possible vaules from box peers
bool removeFromBoxPeers(Cell (&sudoku)[9][9], int i, int j){
    //return false;
    int boxstartrw = i - i %3;
    int boxstartcol = j - j %3;
	for (int row = 0; row < 3; row++){
        for (int col = 0; col <3; col++){
            sudoku[row+boxstartrw][col+boxstartcol].poss.erase(std::remove((sudoku[row+boxstartrw][col+boxstartcol].poss.begin()),(sudoku[row+boxstartrw][col+boxstartcol].poss.end()),(sudoku[i][j].val)),sudoku[row+boxstartrw][col+boxstartcol].poss.end());
            // If there is only one possible value assign it and check its peers (recursive)
            if (sudoku[row+boxstartrw][col+boxstartcol].poss.empty() && sudoku[row+boxstartrw][col+boxstartcol].val == 0){
                return false;
                //return true;
            }
            
            if (sudoku[row+boxstartrw][col+boxstartcol].poss.size()==1){
                if(!assignValue(sudoku, row+boxstartrw, col+boxstartcol)){
                    return false;
                }
                //sudoku[row+boxstartrw][col+boxstartcol].val = sudoku[row+boxstartrw][col+boxstartcol].poss[0];
                //sudoku[row+boxstartrw][col+boxstartcol].poss.clear();
                //removeAndUpdatePeers(sudoku, row+boxstartrw, col+boxstartcol);
            }
            
        }		
	}
    return true;	 
}

bool removeAndUpdatePeers(Cell (&sudoku)[9][9], int i, int j){ //returns true if all peer removals are true BEHÖVER LOGIKEN VARA OMVÄND?
    if (!removeFromColPeers(sudoku, i, j) || !removeFromRowPeers(sudoku, i, j) || !removeFromBoxPeers(sudoku, i, j)){
        return false;
    }
    else{
    return removeFromColPeers(sudoku, i, j) && 
    removeFromRowPeers(sudoku, i, j) && 
    removeFromBoxPeers(sudoku, i, j);
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
bool usedInCol(Cell (&sudoku)[9][9], int col, int num)
{
	for (int row = 0; row < 9; row++)
		if (sudoku[row][col].val == num){
			return true;
		}
	return false;  
}

// Returns a boolean which indicates whether any assigned entry within the specified 3x3 box matches the given number. 
bool usedInBox(Cell (&sudoku)[9][9], int box_start_rpw, int box_start_col, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (sudoku[row + box_start_rpw][col + box_start_col].val == num){
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


bool guessSudoku(Cell (&sudoku)[9][9]){
    // If sudoku grid ia already full return true --> it is solved
    if (GridFull == checkGridFull(sudoku)){
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
        
            // Create backup and make tentative assignment
            Cell backup[9][9]{};
            for(int i{}; i !=9; ++i){
                for(int j{}; j !=9; ++j){
                    backup[i][j] = sudoku[i][j];
                }
            }

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
    std::string filename;
    std::cout << "Enter the name of your sudoku file:" << std::endl;
    std::cin >> filename;
    //std::ifstream sudokufile ("EasySudoku.txt");
    std::ifstream sudokufile (filename);

    //Start execution timer
    auto begin = std::chrono::high_resolution_clock::now();

    // Read input file into array
    if (sudokufile.is_open()){

        // Initialize grid with all possibilities and 0 values according to constructor in class
        Cell grid[9][9];

        // Fill sudoku array with elements from text file
        // Currently empty cells needs to be indicated with blank space and 0 (do find and replace in input file)
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
        
        //Start solving, this could be done in the previous loop but since I want to print I splitted it
        for(int i{}; i !=9; ++i){
            for(int j{}; j !=9; ++j){
                if (grid[i][j].val !=0){
                    removeAndUpdatePeers(grid, i, j);   
                }
            }
        }

        std::cout<< "\nHere are all possible solutions after rule (1) of constraint propagation:" << std::endl;
        printSudokuPossibility(grid);

        //The following should be done in a nicer way :) Perhaps everytime we assign a value? Flytta till slutet av removeAndUpdatePeers

        for(int i{}; i !=9; ++i){
            for(int j{}; j !=9; ++j){
                if (grid[i][j].val ==0){
                    for(int x=0; x<grid[i][j].poss.size(); x++){
                        int checkVal = grid[i][j].poss.at(x);
                        checkUniqueRow(grid, i, j, checkVal);
                    }
                }
            }
        }

        for(int i{}; i !=9; ++i){
            for(int j{}; j !=9; ++j){
                if (grid[i][j].val ==0){
                    for(int x=0; x<grid[i][j].poss.size(); x++){
                        int checkVal = grid[i][j].poss.at(x);
                        checkUniqueCol(grid, i, j, checkVal);
                    }
                }
            }
        }

        for(int i{}; i !=9; ++i){
            for(int j{}; j !=9; ++j){
                if (grid[i][j].val ==0){
                    for(int x=0; x<grid[i][j].poss.size(); x++){
                        int checkVal = grid[i][j].poss.at(x);
                        checkUniqueBox(grid, i, j, checkVal);
                    }
                }
            }
        }

        std::cout<< "\nHere are all possible solutions after rule (1) and (2) of constraint propagation:" << std::endl;
        printSudokuPossibility(grid);

        //Start brute forcing
        if (true == guessSudoku(grid)){

        // Print the sudoku solution
        std::cout<< "\nThis is the solution to your sudoku:" << std::endl;
        printSudoku(grid);

        }
        else {std::cout << "\nThere is no solution to your sudoku" << std::endl;}

    }
    else {std::cout << "Can't open the file" << std::endl;}

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Time of execution: " << elapsed.count() << " micro seconds" << std::endl;

}

