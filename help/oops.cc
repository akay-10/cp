#include <bits/stdc++.h>

using namespace std;

class Person {
    double *h, *w;
    int *a;

public:
    Person() {
        h = new double(0.0);
        w = new double(0.0);
        a = new int(0);
    }
    Person(double height, double weight, int age) {
        h = new double(height);
        w = new double(weight);
        a = new int(age);
    }
    Person(const Person &P) {
        *h = *P.h;
        *w = *P.w;
        *a = *P.a;
    }
    double getHeight() { return *h; }
    double getWeight() { return *w; }
    int getAge() { return *a; }

    bool operator<(const Person &B) {
        if (*h != *B.h)
            return *h < *B.h;
        else if (*w != *B.w)
            return *w < *B.w && *h == *B.h;
        else
            return *a < *B.a && *w == *B.w && *h == *B.h;
    }
    friend ostream &operator<<(ostream &output, const Person &P) {
        output << *P.h << " " << *P.w << " " << *P.a;
        return output;
    }
    ~Person() { delete h, a, w; }
};

int main() {
    Person p(4.5, 6.4, 1), q;
    q = p;
    cout << p;
    cout << (p < q);
    cout << q;
}
class circle {
    int x, y, r;

public:
    circle(int a, int b, int c) {
        x = a;
        b = y;
        r = c;
    }
    int getx() { return x; }
    int gety() { return y; }
};
void find_guess(int p, int q, circle c) {
    cout << c.getx() - p << " " << c.gety() - q;
}
int main() {
    circle q(8, 9, 5);
    find_guess(4, 5, q);
}

template <typename T>
class Xvector {
    int SIZE;
    T *vector;

public:
    Xvector(int size) {
        SIZE = size;
        vector = new T[SIZE];
    }

    int size() { return SIZE; }

    // getting value at index
    T operator[](int index) const { return *(vector + index); }

    // setting value  at index
    T &operator[](int index) { return vector[index]; }
};

int main() {
    // creating objects
    Xvector<int> v1(5);
    Xvector<float> v2(5);
    int index, key;
    cin >> index >> key;
    try {
        // checking for out of bound using SIZE
        if (index >= v1.size()) {
            throw -1;  // -1 is the error_id when thrown from here catched at
                       // the catch block below
        }
        // if throw not executed means compiler is here therfore values assigned
        // if throw is executed then these lines will be skipped
        v1[index] = key;
        v2[index] = key * 0.1;

        // just for checking that values are alloted
        cout << v1[index] << " " << v2[index] << endl;
    } catch (int error_id) {
        // if throw is executed means compiler skiped the setting values to
        // array lines and compiler is now here
        cout << "Out of Bound Exception " << error_id << endl;
    }
    return 0;
}

class person {
    int *h;

public:
    person() { h = new int(0); }
    person(person &p) { *h = *p.h; }
    void setvalue(int x) { *h = x; }
    void disp() { cout << *h; }
};

int main() {
    person ob1;
    ob1.setvalue(5);
    person ob2 = ob1;
    ob2.disp();
}
class co {
    int x, y;

public:
    co &getx() {
        x = 3;
        return *this;
    }
    co &gety() {
        y = 5;
        return *this;
    }
    void display() { cout << x << " " << y; }
};

int main() {
    co c;
    c.getx().gety().display();
    return 0;
}
class x {
protected:
    double d;

public:
    x() { d = 5.0; }
    double getd() { return d; }
};
double operator-(double temp, x cc) { return temp - cc.getd(); }
double operator-(x cc, double temp) { return cc.getd() - temp; }

int main() {
    x cc;
    double a = 2.2;
    cout << cc - a;
    cout << a - cc;
    return 0;
}

class Point {
protected:
    int x, y;

public:
    virtual void find_length();
    int getx() { return x; }
    int gety() { return y; }
};

class Line : public Point {
public:
    void find_length(Point &A, Point &B) {
        double d = sqrt((A.getx() - B.getx()) * (A.getx() - B.getx()) +
                        (A.gety() - B.gety()) * (A.gety() - B.gety()));
        cout << d << endl;
    }
};

class Triangle : public Line {
public:
    void find_length(Point &A, Point &B, Point &C) {
        Line::find_length(A, B);
        Line::find_length(B, C);
        Line::find_length(C, A);
    }
};
class Student {
private:
    int stud_id;
    int stud_marks;

public:
    Student(){};
    Student(int id, int marks) {
        try {
            if (id > 60 || id < 0) throw(0);
            if (marks < 0 || marks > 500) throw(1);
        } catch (int a) {
            std::cout << "Exception handler";
        }
        stud_id = id;
        stud_marks = marks;
    };
};
int main() { Student S(-1, 30); }