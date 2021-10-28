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