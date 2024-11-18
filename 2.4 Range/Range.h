#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Range;

template <class T>
ostream& operator<<(ostream &, Range<T> &);

template <class T>
class Range {
    public:
        Range(T start, T end) : start(start), end(end), step(1){};
        Range(T start, T end, T step) : start(start), end(end), step(step){};
        friend ostream& operator<< <>(ostream &, Range<T> &);

        int length() {
            return ((end-start)/step)+1;
        }

        T sum() {
            T summation = 0;
            for (int i = 0; i < length(); i++) {
                T currVal = (start + (step*i));
                values.push_back(currVal);
                summation += currVal;
            }
            return summation;
        }

        T average() {
            return sum()/length();
        }

        T min() {
            if (step > 0) {
                return values.front();
            } else {
                return values.back();
            }
        }

        T max() {
            if (step > 0) {
                return values.back();
            } else {
                return values.front();
            }
        }

    private:
        T start;
        T end;
        T step;
        vector<T> values;
};

template <class T>
ostream& operator<< (ostream & out, Range<T> &r) {
    for (T val : r.values) {
        out << val;
    }
    return out;
}