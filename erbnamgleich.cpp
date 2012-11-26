#include <iostream>
using namespace std;

class Basis {
 public:
    int f(void)   const { cout << "Basis::f(void)"   << endl; return 1; }
    int f(double) const { cout << "Basis::f(double)" << endl; return 1; }
    void g(void)        { cout << "Basis::g(void)"   << endl;           }
};

class Sub1 : public Basis {
 public:
    //.... Überschreiben von g() --> beide f() aus Basis verfügbar
    int g(char) const { cout << "Sub1::g(char)" << endl; return 1; }
};

class Sub2 : public Basis {
 public:
    //.... Überschreiben von f(void) --> kein f() aus Basis mehr verfügbar
    int f(void) const { cout << "Sub2::f(void)" << endl; return 2; }
};

class Sub3 : public Basis {
 public:
    //.... Überschreiben von f(void) (anderer Rückgabetyp)
    //     --> kein f() aus Basis mehr verfügbar
    void f(void) const { cout << "Sub3::f(void)" << endl; }
};

class Sub4 : public Basis {
 public:
    //.... Neudefinition von f() (anderer Parametertyp
    //     --> kein f() aus Basis mehr verfügbar
    int f(char) const { cout << "Sub4::f(char)" << endl; return 4; }
};

int main(void) {
  Sub1 s1; Sub2 s2; Sub3 s3; Sub4 s4;
   int x = s1.f(); //... Basis::f(void)
   s1.f(3.14);     //... Basis::f(double)
   s1.Basis::g();  //... Basis::g(void)
   x = s1.g(’a’);  //... Sub1::g(char)
   cout << "--------------------------" << endl;
   x = s2.f();            //... Sub2::f(void)
   x = s2.Basis::f();     //... Basis::f(void)
   x = s2.Basis::f(3.14); //... Basis::f(double)
   // x = s2.f(3.14); // nicht mögl., da Basis::f(double) nicht verfügbar
   s2.g();                //... Basis::g(void)
   cout << "--------------------------" << endl;
   s3.f();                //... Sub3::f(void)
   x = s3.Basis::f();     //... Basis::f(void)
   x = s3.Basis::f(3.14); //... Basis::f(double)
   // x = s3.f();     // nicht mögl., da Basis::f() (mit Rückgabe) nicht verfügbar
   // x = s3.f(3.14); // nicht mögl., da Basis::f(double) nicht verfügbar
   s3.g();                //... Basis::g(void)
   cout << "--------------------------" << endl;
   x = s4.f(’a’);         //... Sub4::f(char)
   x = s4.Basis::f();     //... Basis::f(void)
   x = s4.Basis::f(3.14); //... Basis::f(double)
   // x = s4.f();     // nicht möglich, da Basis::f() nicht verfügbar
   // x = s4.f(3.14); // falsch, da Basis::f(double) nicht verfügbar
   s4.g();                //... Basis::g(void)
}

