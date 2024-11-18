#include <istream>
#include <ostream>
#include <iostream>

using namespace std;

class Point{
    private:
        int x;
        int y;

    public:
        Point(){x=0; y=0;}
        Point(int x, int y): x(x), y(y){}
        Point operator+(const Point&);
        Point operator+=(const Point&);  
        Point operator-(const Point&);
        Point operator-=(const Point&);   
        friend ostream& operator <<(ostream &, const Point &);   
        friend istream& operator >>(istream &, Point &); 
};

Point Point::operator+(const Point& toAdd) {
    Point finalPoint(x + toAdd.x, y + toAdd.y);
    return finalPoint;
}

Point Point::operator+=(const Point& point) {
    x += point.x;
    y += point.y;
    return *this;
}
Point Point::operator-(const Point& toAdd) {
    Point finalPoint(x - toAdd.x, y - toAdd.y);
    return finalPoint;
}

Point Point::operator-=(const Point& point) {
    x -= point.x;
    y -= point.y;
    return *this;
}

ostream& operator <<(ostream &stream, const Point &point) {
    stream << "[" << point.x << ", " << point.y << "]" << endl;
    return stream;
}

istream& operator >>(istream & stream, Point &point) {
    cout << "Enter x and y coordinates." << endl;
    stream >> point.x >> point.y;
    return stream;  
}