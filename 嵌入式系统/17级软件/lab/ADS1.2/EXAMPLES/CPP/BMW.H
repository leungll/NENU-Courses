/*
 * bmw.h: This example illustrates virtual base classes with virtual functions.
 * It is modelled after Stroustup's BMW (Borders, Menu, Window) example from
 * section 10.10c of the A.R.M. (p233-235).
 */

#ifndef bmw_h
#define bmw_h

class W {
  public:
    virtual void f(void) = 0;
    virtual void g(void) = 0;
    virtual void h(void) = 0;
    virtual void k(void);
};

class MW : public virtual W {
  public:
    virtual void g(void);
};

class BW : public virtual W {
  public:
    virtual void f(void);
};

class BMW: public BW, public MW, public virtual W {
  public:
    virtual void h(void);
};

#endif

