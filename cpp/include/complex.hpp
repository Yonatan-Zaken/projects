/*********************************/
/*    Copmlex Number             */
/*	  Language: c++  		     */
/*    Author: Yonatan            */
/*    Reviewed By:               */
/*    Date:   13/3/20            */
/*********************************/
#ifndef ILRD_RD8081__HPP
#define ILRD_RD8081__HPP

#include <iosfwd> // i/ostream

namespace ilrd
{

class Complex
{
public:	
    Complex(double re = 0, double im = 0); // converting ctor 	
    // using compiler generated cctor
    // using compiler generated dtor
    // using compiler generated assignment operator
    
    double GetReal() const;
    double GetImag() const;
    void SetReal(double re);
    void SetImag(double im);
    double Abs() const;
    Complex Conj() const;
    
    Complex& operator+=(const Complex&);
    Complex& operator-=(const Complex&);
    Complex& operator*=(const Complex&);
    Complex& operator/=(const Complex&);
    
private:
    double m_re;
    double m_im;
}; // class Complex
} // namespace ilrd 

const ilrd::Complex operator+(const ilrd::Complex&, const ilrd::Complex&);  
const ilrd::Complex operator-(const ilrd::Complex&, const ilrd::Complex&);  
const ilrd::Complex operator*(const ilrd::Complex&, const ilrd::Complex&);  
const ilrd::Complex operator/(const ilrd::Complex&, const ilrd::Complex&);  
bool operator==(const ilrd::Complex&, const ilrd::Complex&);  
bool operator!=(const ilrd::Complex&, const ilrd::Complex&);  
bool operator>(const ilrd::Complex&, const ilrd::Complex&);  
bool operator<(const ilrd::Complex&, const ilrd::Complex&);  
std::ostream& operator<<(std::ostream&, const ilrd::Complex&);
std::istream& operator>>(std::istream&, ilrd::Complex&);

#endif
