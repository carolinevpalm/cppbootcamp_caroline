// We want to generate 1024 random integers, then given a new random number; find two integers which are the
// closest to the given number (smaller, and bigger) with less than twelve lookups.
// Create a sorted container and populate it, then pick a random integer and look for the boundaries 
// – implement your own logarithmic search if you are in the mood for it

#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>


int main(){
    std::srand(time(nullptr));
    std::multiset <int> randNr;
    for(int i = 0; i<1024; i++){
        randNr.insert(rand());
    }

    int compareNr = rand();
    std::cout << "Compare number is: " << compareNr << std::endl;
    
    auto uppr = randNr.upper_bound(compareNr); //upper bound searches 10 times (binary search)
    int upprVal = *uppr;
    auto lowr = --uppr;
    int lowrVal = *lowr;


    std::cout << "The number before is: " << lowrVal << "\nThe number after is: " << upprVal << std::endl;




    return 0;
}