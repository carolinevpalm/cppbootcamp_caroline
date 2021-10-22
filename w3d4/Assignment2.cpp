// Write a function which can encode the information in the given figure:
// • Speed/20
// • Distance/150
// Sensitivity: C2-Restricted
// 1 0 1 1 1 0 1 0 0 1 0 1 1 0 1 1
// speed(4), front(3), rear(3), right(3), left (3)

#include<iostream>
#include<bitset>

uint16_t fourBit(uint16_t a){
    return a > 15 ? 15 : a;
}

uint16_t threeBit(uint16_t a){
    return a > 7 ? 7 : a;
}


void function(uint16_t speed, uint16_t front, uint16_t rear, uint16_t right, uint16_t left){
    //std::bitset<16>speedMask("1111000000000000");
    //std::bitset<16>frontMask("0000111000000000");
    //std::bitset<16>rearMask("0000000111000000");
    //std::bitset<16>rightMask("0000000000111000");    
    //std::bitset<16>leftMask("0000000000000111");
    
    //Divide input and handle max values based in number of bits for each
    speed/=20;
    //speed = speed>15 ? 15 : speed;
    front/=150;
    //front = front > 7 ? 7 : front;
    rear/=150;
    //rear = rear > 7 ? 7 : rear;
    right/=150;
    //right = right > 7 ? 7 : right;
    left/=150;
    //left = left > 7 ? 7 : left;
    
    
    std::bitset<16> speedbits(fourBit(speed)<<12);
    std::bitset<16> frontbits(threeBit(front)<<9);
    std::bitset<16> rearbits(threeBit(rear)<<6);
    std::bitset<16> rightbits(threeBit(right)<<3);
    std::bitset<16> leftbits(threeBit(left));

    std::cout << speedbits<<std::endl;
    std::cout << frontbits<<std::endl;
    std::cout << rearbits<<std::endl;
    std::cout << rightbits<<std::endl;
    std::cout << leftbits<<std::endl;
    
    std::cout << std::bitset<16> (speedbits|frontbits|rearbits|rightbits|leftbits)<<std::endl;

} 

int main(){
    uint16_t speed = 220;
    uint16_t front = 800;
    uint16_t rear = 400;
    uint16_t right = 150;
    uint16_t left = 1500;
    //std::bitset<16> speedbits((speed/20)<<12);
    //std::cout<<speedbits<<std::endl;

    function(speed,front,rear,right,left);

    return 0;    


}