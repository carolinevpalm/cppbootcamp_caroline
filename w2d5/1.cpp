#include <iostream>

const size_t SIZE = 10;

int function() {
    return std::rand();
}
// MUST FILL THE ARRAY FRON THE LAST INDEX
int *fillArray() {
    //int a[SIZE]; 
    //--> this array is only in the stack, we need to NEW to create it in the dynamic memory to be able to return and access outside function
    int *a = new int[SIZE];
    size_t i = SIZE;// YOU ARE NOT SUPPOSE TO CHANGE THIS    
    /*for (; i > 0; --i) {
        a[i] = function();        
    }*/
    //--> a[0] is never assigned
    for (; i > 0; --i) {
        a[i-1] = function();        
    }
    return a;    
}
void printArray(int a[SIZE]) {        
    for (size_t i = 0; i < SIZE; i++) {
        //std::cout << *a+i << std::endl;
        //--> this only dereference the first element and then adds +i
        // *(a+1) would also work
        std::cout << a[i] << std::endl;
        
    } 
    delete[] a; //delete pointer from fillArray since we are done with it now   
}
void printBool (bool _b) {
    /*if (_b = true) {
        std::cout << "VALUE is TRUE" << std::endl;        
    } else if (_b = false)    {
        std::cout << "VALUE is FALSE" << std::endl;        
    }  */  
    //--> _b is assigned to true not compared
    
    if (_b == true) {
        std::cout << "VALUE is TRUE" << std::endl;        
    } else if (_b == false)    {
        std::cout << "VALUE is FALSE" << std::endl;        
    }    
}
// YOU ARE NOT ALLOWED TO CHANGE THE RETURN TYPE
//void resizeForMe(char *a, size_t _newSize) { 
    // --> needs to have reference to pointer
void resizeForMe(char *&a, size_t _newSize) {
    delete[] a;
    a = new char[_newSize];
}


int main() {
    printArray(fillArray());
    printBool(false);
    char *a = new char[SIZE];        
    for (size_t i = 0; i<SIZE; i++){
        i%2 ? a[i] = 'A' : a[i] = 'D'; //this is an if/else statement in one line
        // if devisable with two --> return is 0 --> print D, otherwise print A
    }
    a[SIZE-1] = 0x00; // add nullterminator to array   
    std::cout << "String a is: " << a << std::endl;
    //resizeForMe(a,100); --> wrong size compared to for loop
    resizeForMe(a,1000);
    for (size_t i = 0; i<1000; i++) i%2 ? a[i] = 'B' : a[i] = 'C';
    a[1000-1] = 0x00; // add nullterminator to array
    std::cout << "String a is: " << a << std::endl;
    delete[] a; //delete a that was newed in resize function
    
    return 0;
}