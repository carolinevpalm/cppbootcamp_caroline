/* Implement an interface for shape, and derive circle, triangle, rectangle, square as children. Overload all three
comparison operators to compare the shapes based on their area -- if equal then their perimeter should be
considered. Only, and if only both area and perimeter are equal then the objects should be considered equal. */

#include <iostream>
#include "shapes.h"


int main(){

    Shape *circ1 = new Circle(5);
    Shape *circ2 = new Circle(100);
    Shape *tri1 = new Triangle(10,20);
    Shape *tri2 = new Triangle(2,5);
    Shape *rec1 = new Rectangle(3,4);
    Shape *rec2 = new Rectangle(30,60);
    Shape *squ1 = new Square(10);
    Shape *squ2 = new Square(100);


    Shape *shapes[8] = {circ1, circ2, tri1, tri2, rec1, rec2, squ1, squ2};
    std::string nameShapes[8] = {"circ1", "circ2", "tri1", "tri2", "rec1", "rec2", "squ1", "squ2"};

    for(size_t i=0; i<8; i++){
        std::cout << nameShapes[i] << ": \t";
        shapes[i] ->print();
    }

    for(size_t i=0; i<8; i++){
        for(size_t j=i+1; j<8; j++){
            if (*shapes[i] < *shapes[j]){
                std::cout << nameShapes[i] << " is smaller than " << nameShapes[j] << std::endl;                
            }
            else if (*shapes[i]>*shapes[j]){
                std::cout << nameShapes[i] << " is larger than " << nameShapes[j] << std::endl;
            }
            else if (*shapes[i]==*shapes[j]){
                std::cout << nameShapes[i] << " is equal to " << nameShapes[j] << std::endl;
            }
        }
    }

    
    return 0;   


}
