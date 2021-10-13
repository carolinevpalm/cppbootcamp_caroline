/* Write a program which takes a positive number from user, and then fill in a 3-dimensional array of size [8,9,11]
with random positive numbers smaller than the one user has provided – pretty print the array.*/

#include <iostream>

int main(){
    unsigned int a;
    unsigned int array[8][9][11];
    std::cout << "Enter a positive number: " << std::endl;
    std::cin >> a;

    for(unsigned int i = 0; i<8; i++){
        for(unsigned int j = 0; j<9; j++){
            for(unsigned int k = 0; k<11; k++){
                unsigned int randnr = rand() % a;
                array[i][j][k] = randnr;
                std::cout << "[" << i << "]" << "[" << j << "]" << "[" << k << "] \t" << array[i][j][k] << std::endl; 
                
            }
        }
    }

}

