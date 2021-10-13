/* At the very least the submission shall include:
• One executable receiving Sudoku Puzzle and outputting the result */

#include <iostream>
#include <fstream>

//This can be in a separate file? since outside main?
const int Blank = 0; //define a constant that is not allowed to change
const std::pair<int, int> GRID_FULL = std::make_pair(9,9);

// Returns a boolean which indicates whether any assigned entry in the specified row matches the given number. 
bool used_in_row(int sudoku[9][9], int row, int num){
	for (int col = 0; col < 9; col++)
		if (sudoku[row][col] == num)
		{
			return true;
		}
	return false;   
}

// Returns a boolean which indicates whether any assigned entry in the specified column matches the given number. 
bool used_in_col(int sudoku[9][9], int col, int num)
{
	for (int row = 0; row < 9; row++)
		if (sudoku[row][col] == num)
		{
			return true;
		}
	return false;  
}

// Returns a boolean which indicates whether any assigned entry within the specified 3x3 box matches the given number. 
bool used_in_box(int sudoku[9][9], int box_start_rpw, int box_start_col, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (sudoku[row + box_start_rpw][col + box_start_col] == num) 
			{
				return true;
			}
	return false;
}

// Returns a boolean which indicates whether it will be legal to assign num to the given row,col location.
bool is_safe(int sudoku[9][9], int row, int col, int num)
{
	// Check if 'num' is not already placed in current row, current column and current 3x3 box 
	return !used_in_row(sudoku, row, num) &&
		!used_in_col(sudoku, col, num) &&
		!used_in_box(sudoku, row - row % 3, col - col % 3, num);
}

// Searches the grid to find an entry that is still unassigned. If found, the reference parameters row, col will be set the location
// that is unassigned, and true is returned. If no unassigned entries remain, false is returned. 
std::pair<int, int> get_unassigned_location(int sudoku[9][9])
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (sudoku[row][col] == Blank)
			{
				return std::make_pair(row, col);
			}
	return GRID_FULL;
}

bool solve_sudoku(int sudoku[9][9]){
    // If sudoku grid ia already full return true --> it is solved
    if (GRID_FULL == get_unassigned_location(sudoku)){
        return true;
    }
    // Get location of unassigned
    std::pair<int, int> row_and_col = get_unassigned_location(sudoku);
    int row = row_and_col.first;
    int col = row_and_col.second;

    for (int num=1; num <=9; num++){
        // If placing the current number in the current unassigned location, go ahead
        if (is_safe(sudoku, row, col, num)){
            // Make tentative assignment
            sudoku[row][col] = num;

            // Do the same thing again recursively. If we go through all of the recursions, and in the end 
			// return true, then all of our number placements on the Soduko grid are valid and we have fully solved it
            if (solve_sudoku(sudoku)){
                return true;
            }

            // As we were not able to validly go through all of the recursions, we must have an invalid number
			// placement somewhere. Lets go back and try a different number for this particular unassigned location
            sudoku[row][col] = Blank;                
        }
    }

    // If we have gone through all possible numbers for the current unassigned location, then we probably assigned a bad number early. 
    // Lets backtrack and try a different number for the previous unassigned locations.
	return false; 
}

void printsudoku(int sudoku[9][9]){
    for (int i=0; i!=9; ++i){
        for (int j=0; j!=9; ++j){
            std::cout << sudoku[i][j] << " ";
            }
            std::cout << std::endl;
    }
}

        


int main(){
    int sudoku [9][9]{};

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
                sudokufile >> sudoku[i][j];
            }
        }

        // Print the sudoku
        std::cout<< "This is the sudoku to solve:" << std::endl;
        printsudoku(sudoku);


    
        // Solve the input sudoku
        if (true == solve_sudoku(sudoku)){

            // Print the sudoku solution
            std::cout<< "This is the solution to your sudoku:" << std::endl;
            printsudoku(sudoku);

        }
        else {std::cout << "There is no solution to your sudoku" << std::endl;}

    }

    else {std::cout << "Can't open the file" << std::endl;}

    
    return 0;
}