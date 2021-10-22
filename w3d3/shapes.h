#ifndef SHAPES_H_
#define SHAPES_H_

#include <iostream>

class Shape {
    public:
    Shape() = default;
    Shape(const int &_p, const int &_a):Perimeter(_p), Area(_a){} //använd const för att den inte ska vara variabel, använd & för reference så att vi inte skapar en kopia varje gång (?)
    virtual ~Shape() = 0; //pure virtual function - destructor
    void print() {
        std::cout << "Perimeter: " << Perimeter << ",\t Area: " << Area << std::endl;
    }
    bool operator <(const Shape &s); // Operator overload
    bool operator >(const Shape &s);
    bool operator ==(const Shape &s);
    private:
    int Perimeter = 0;
    int Area = 0;
};

class Circle: public Shape {
    public:
    ~Circle() = default;
    Circle(const int &radius):Shape((2*3*radius),(3*radius*radius)){}
};

class Triangle: public Shape {
    public:
    ~Triangle() = default;
    Triangle(const int &height, const int &width):Shape((3*width),((height*width)/2)){} //antar liksidig triangel
};

class Rectangle: public Shape {
    public:
    ~Rectangle() = default;
    Rectangle(const int &height, const int &width):Shape(((2*height)+(2*width)),(height*width)){}
};

class Square: public Shape {
    public: 
    ~Square() = default;
    Square(const int width):Shape((4*width),(width*width)){}
};




#endif /* SHAPES_H_ */