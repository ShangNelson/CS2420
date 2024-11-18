#include <istream>
#include <ostream>
#include <iostream>

using namespace std;

template <class Type>
class Point;

template <class Type>
istream& operator >>(istream &, Point<Type> &);

template <class Type>
ostream& operator <<(ostream &, const Point<Type> &);  

template <class Type>
class Point{
    private:
        Type x;
        Type y;

    public:
        Point(){x=0; y=0;}
        Point(Type x, Type y): x(x), y(y){}
        Point operator+(const Point<Type>&);
        Point operator+=(const Point<Type>&);  
        Point operator-(const Point<Type>&);
        Point operator-=(const Point<Type>&);   
        friend ostream& operator << <>(ostream &, const Point<Type> &);   
        friend istream& operator >> <>(istream &, Point<Type> &); 
};

template <class Type>
Point<Type> Point<Type>::operator+(const Point& toAdd) {
    Point finalPoint(x + toAdd.x, y + toAdd.y);
    return finalPoint;
}

template <class Type>
Point<Type> Point<Type>::operator+=(const Point& point) {
    x += point.x;
    y += point.y;
    return *this;
}
template <class Type>
Point<Type> Point<Type>::operator-(const Point& toAdd) {
    Point finalPoint(x - toAdd.x, y - toAdd.y);
    return finalPoint;
}

template <class Type>
Point<Type> Point<Type>::operator-=(const Point<Type> &point) {
    x -= point.x;
    y -= point.y;
    return *this;
}

template <class Type>
ostream& operator <<(ostream &stream, const Point<Type> &point) {
    stream << "[" << point.x << ", " << point.y << "]" << endl;
    return stream;
}

template <class Type>
istream& operator >>(istream & stream, Point<Type> &point) {
    cout << "Enter x and y coordinates." << endl;
    stream >> point.x >> point.y;
    return stream;  
}