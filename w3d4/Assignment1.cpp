// Implement a function that can read the information shown in the figure
// 1 0 1 1 1 0 1 0 0 1 0 1 1 0 1 1
// seatbelts (5), windows (4), doors (4), lights (3)

#include<iostream>
#include<bitset>


int main(){
    
    std::bitset<16> bits("1011101001011011");
    std::bitset<16> maskSeatbelt("1111100000000000");
    std::bitset<16> maskWindows("0000011110000000");
    std::bitset<16> maskDoors("0000000001111000");
    std::bitset<16> maskLights("0000000000000111");

    std::cout << (bits&maskSeatbelt).count() << " seatbelts are used" << std::endl;
    std::cout << (bits&maskWindows).count() << " windows are open" << std::endl;
    std::cout << (bits&maskDoors).count() << " doors are open" << std::endl;
    std::cout << (bits&maskLights).count() << " lights are on" << std::endl;




    return 0;
}
