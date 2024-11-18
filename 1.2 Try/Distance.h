#include <iostream>
using namespace std;


class Distance {
  private:
     int feet;             
     int inches;         
     void adjustDist();


  public:
     //Default Constructor
     Distance() ;  
     //Overloaded Constructor                 
     Distance(int f, int i = 0);
     //Overloaded Addition Operator    
     Distance operator+(const Distance&);
     //Overloaded Minus Operator    
     Distance operator-(const Distance&);
     //Insertion Operator
     friend ostream &operator<<( ostream &output, const Distance &D );
     //Extraction Operator
     friend istream &operator>>( istream  &input, Distance &D );
};


Distance::Distance() {
    feet = 0;
    inches = 0;
}
Distance::Distance(int f, int i) {
   feet = f;
   inches = i;
   adjustDist();
}
void Distance::adjustDist(){
 if(inches > 12){
   int addFeet = inches / 12;
   feet += addFeet;
   inches %= 12;
 }
}
Distance Distance::operator+(const Distance& d){
   Distance dist;
   dist.inches = inches + d.inches;
   dist.feet = feet + d.feet;
   adjustDist();
   return dist;
}

Distance Distance::operator-(const Distance& d){
   Distance dist;
   dist.inches = inches - d.inches;
   dist.feet = feet - d.feet;
   adjustDist();
   return dist;
}

ostream &operator<<( ostream &out, const Distance &d ) {
   out << "Feet: " << d.feet << " Inches : " << d.inches;
   return out;           
}


istream &operator>>( istream  &input, Distance &d ) {
   input >> d.feet >> d.inches;
   return input;           
}