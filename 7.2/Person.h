#include <iostream>
#include <string>
using namespace std;

class Person;

bool operator>(const int& i, const Person &g);
bool operator<(const int& i, const Person &g);
bool operator>=(const int& i, const Person &g);
bool operator<=(const int& i, const Person &g);
bool operator!=(const int& i, const Person &g);

class Person {
public:
  Person(string name, int amount) : name(name), amount(amount) {}
  bool operator >(const Person &g);
  bool operator <(const Person& g);
  bool operator <(const int &g);
  bool operator <=(const Person& g);
  bool operator >=(const Person& g);
  bool operator !=(const Person& g);
  int getAmount() const;
  friend bool operator>(const int& i, const Person &g);
  friend bool operator<(const int& i, const Person &g);
  friend bool operator<=(const int& i, const Person &g);
  friend bool operator>=(const int& i, const Person &g);
  friend bool operator!=(const int& i, const Person &g);
  friend ostream& operator <<(ostream &out, const Person &g);
  bool operator ==(const Person& person);
private:
  string name;
  int amount;
};


bool operator>(const int& i, const Person &g) {
    return i > g.amount;
}

bool operator<(const int& i, const Person &g) {
    return i < g.amount;
}

bool operator>=(const int& i, const Person &g) {
    return i >= g.amount;
}

bool operator<=(const int& i, const Person &g) {
    return i <= g.amount;
}

bool operator!=(const int& i, const Person &g) {
    return i != g.amount;
}

bool Person::operator >(const Person &g) {
  return amount > g.amount;
}


bool Person::operator <(const Person &g) {
  return amount < g.amount;
}


bool Person::operator <(const int &g) {
  return amount < g;
}

bool Person::operator >=(const Person &g) {
  return amount >= g.amount;
}

bool Person::operator <=(const Person &g) {
  return amount <= g.amount;
}

bool Person::operator !=(const Person &g) {
  return amount != g.amount;
}


int Person::getAmount() const {
  return amount;
}
ostream& operator <<(ostream &out, const Person &g) {
  out << g.name << ": " << g.amount;
  return out;
}

bool Person:: operator==(const Person& person) {
    return amount==person.getAmount();
}
