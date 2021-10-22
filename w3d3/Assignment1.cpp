// Write a function template which receives two of any shapes from last week’s assignment, compares them, and
//prints out the result.

#include <iostream>
#include "shapes.h"

// Shape is smaller either if the area is smaller OR if the area is equal and the perimiter is smaller
// What is the difference between using this and s.?
bool Shape::operator<(const Shape &s){
    bool returnVal = false;
    if ((this->Area < s.Area) || ((this->Area == s.Area)&&(this->Perimeter < s.Perimeter))){
        returnVal = true;
    }
    return returnVal;
}

//Shape is larger either if the area is larger OR if the area is equal and the perimiter is larger
bool Shape::operator>(const Shape &s){
    bool returnVal = false;
    if ((this->Area > s.Area) || ((this->Area == s.Area)&&(this->Perimeter > s.Perimeter))){
        returnVal = true;
    }
    return returnVal;
}

//Shape is equal if both area and perimeter is equal
bool Shape::operator==(const Shape &s){
    bool returnVal = false;
    if ((this->Area == s.Area) && (this->Perimeter == s.Perimeter)){
        returnVal = true;
    }
    return returnVal;
}


Shape::~Shape(){} 




template <class T1, class T2>
void shapeCompare (T1 &a, T2 &b){
    if (a < b){
        std::cout << "Shape a is smaller than shape b" << std::endl;
    }
    else if (a > b){
        std::cout << "Shape a is larger than shape b" << std::endl;
    }
    else if (a == b){
        std::cout << "Shape a is equal to shape b" << std::endl;

    }
}

int main(){
    Circle c1(5);
    Rectangle r1(3, 4);
    shapeCompare<>(c1, r1);

    return 0;
}