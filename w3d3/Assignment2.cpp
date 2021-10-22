// Generate random numbers between 0-33, ten thousand times, then print how many duplicates of each number
//you have generated -- print in ascending order.
// Hint: results should be stored in ascending order in your container.

#include <iostream>
#include <map>

int main(){

    const int maxVal = 33;
    std::map<int, int> duplicates; //För att sortera med värde istället kan man använda multimap som tillåter duplicate keys --> key blir number of occurance

    for(int i = 0; i < 10000; i++){
        int randnr = rand() % (maxVal+1);
        //int startVal = 1;
        duplicates[randnr]++;
    
    }

    for (auto &e: duplicates) {
        std::cout << e.first << "\t" << e.second << std::endl;
    }

    return 0;

}