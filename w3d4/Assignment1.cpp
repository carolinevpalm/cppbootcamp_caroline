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

    for(int i = 11; i<16; i++){
        if ((bits&maskSeatbelt)[i]){
            std::cout << "Seatbelt " << i-10 << " is used."<<std::endl;
        }
        else {std::cout << "Seatbelt " << i-10 << " is unused."<<std::endl;}
    }

    for(int i = 7; i<11; i++){
        if ((bits&maskWindows)[i]){
            std::cout << "Window " << i-6 << " is open."<<std::endl;
        }
        else {std::cout << "Window " << i-6 << " is closed."<<std::endl;}
    }

    for(int i = 3; i<7; i++){
        if ((bits&maskDoors)[i]){
            std::cout << "Door " << i-2 << " is open."<<std::endl;
        }
        else {std::cout << "Door " << i-2 << " is closed."<<std::endl;}
    }

    for(int i = 0; i<3; i++){
        if ((bits&maskLights)[i]){
            std::cout << "Light " << i+1 << " is on."<<std::endl;
        }
        else {std::cout << "Light " << i+1 << " is off."<<std::endl;}
    }

   




    return 0;
}
