/*
 * shapes.cpp: A simple C++ program using virtual functions
 *             and object constructors
 */

#include <stdio.h>                           // use only C I/O

class Shape {
    Shape *next;
protected:                                   // count of shapes created
    static int next_idx;
    int idx;
    friend void print(Shape&, const char*);  // allow access to idx...
public:
    virtual void print(void)
    {   printf("Shape #%d\n", idx);
    }
};

int Shape::next_idx;

class Circle : public Shape {
    int xc, yc, rad;
public:
    virtual void print(void);
    Circle(int, int, int);
    /*
     * A copy constructor of the form Circle(const Circle &);
     * will be generated... when it is (later) needed.
     */
};

Circle::Circle(int x, int y, int r)
{   Circle &c = *this;           // not needed - see Rectangle::Rectangle()
    c.xc = x;
    c.yc  = y;
    c.rad = r;
    c.idx = ++next_idx;
}

void Circle::print(void)
{
    printf("Circle #%d centre (%d,%d), radius %d\n", idx, xc, yc, rad);
}

class Rectangle : public Shape {
    int xl, yb, xr, yt;
public:
    virtual void print(void);
    Rectangle(int, int, int, int);
};

Rectangle::Rectangle(int x, int y, int xs, int ys)
{    xl = x;
     yb = y;
     xr = x + xs;
     yt = y + ys;
     idx = ++next_idx;
    /*
     * A copy constructor of the form Rectangle(const Rectangle &);
     * will be generated... when it is (later) needed.
     */
}

void Rectangle::print(void)
{
    printf("Rectangle #%d from (%d,%d) to (%d,%d)\n", idx, xl, yb, xr, yt);
}

/*
 * This function can be called on <any> shape. In turn it calls the virtual
 * function print(), which will be Circle::print() if the shape is a Circle,
 * Rectangle::print() if it is a rectangle.
 */
void print(Shape &s, const char *comment)
{   printf("Shape #%d: %s\n", s.idx, comment);
    s.print();
}

/*
 * These static objects are constructed using the user-defined constructors.
 */
static Rectangle sr(0, 0, 20, 10);
static Circle sc(5, 5, 10);

int main(void)
{
/*
 * These objects are constructed using both a user-defined constructor and
 * a generated copy constructor.
 */
    Rectangle r = Rectangle(0,0, 20, 10);
    Circle c = Circle(5, 5, 10);

    printf("local shapes... NB created after static shapes...\n");
    print(r, "should be a Rectangle...");
    print(c, "should be a Circle...");

    printf("\nstatic shapes...\n");
    print(sr, "should be a Rectangle...");
    print(sc, "should be a Circle...");

    return 0;
}

