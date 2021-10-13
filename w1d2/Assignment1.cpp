/* Modify your first assignment from yesterday to receive the dimensions of the arrays from the user. */

/* Write a program which takes a positive number from user, and then fill in a 3-dimensional array of size [8,9,11]
with random positive numbers smaller than the one user has provided – pretty print the array.*/

#include <iostream>

int main(){
    int a;
    size_t I;
    size_t J;
    size_t K;
    
    std::cout << "Enter dimension I of array[I][J][K]: " << std::endl;
    std::cin >> I;
    std::cout << "Enter dimension J of array[I][J][K]: " << std::endl;
    std::cin >> J;
    std::cout << "Enter dimension K of array[I][J][K]: " << std::endl;
    std::cin >> K;
    std::cout << "Enter a positive number (maximum value in array): " << std::endl;
    std::cin >> a;


    // Dynamically allocate memory for 3D Array
    int ***array = new int**[I];
    for (int i=0; i<I; i++){
        array[i] = new int*[J];
        for (int j=0; j<J; j++){
            array[i][j] = new int[K];
        }
    }

    // Assign random values to array
    for(int i = 0; i<I; i++){
        for(int j = 0; j<J; j++){
            for(int k = 0; k<K; k++){
                int randnr = rand() % a;
                array[i][j][k] = randnr;
                //std::cout << "[" << i << "]" << "[" << j << "]" << "[" << k << "] \t" << array[i][j][k] << std::endl; 
                
            }
        }
    }

    // Print the 3D array
    for (int i=0; i<I; i++){
        for (int j=0; j<J; j++){
            for (int k=0; k<K; k++) {
                std::cout << array[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Deallocate memory
    for (int i = 0; i < I; i++){
        for (int j = 0; j < J; j++){
            delete[] array[i][j];
        }
        delete[] array[i];
    }

    delete[] array;
 
    return 0; 

}

// https://www.techiedelight.com/dynamic-memory-allocation-in-c-for-2d-3d-array/
