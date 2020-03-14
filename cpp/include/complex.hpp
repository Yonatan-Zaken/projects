/*********************************/
/*    Copmlex Number             */
/*	  Language: c++  		     */
/*    Author: Yonatan            */
/*    Reviewed By:               */
/*    Date:   13/3/20            */
/*********************************/

#ifndef ILRD_RD8081__HPP
#define ILRD_RD8081__HPP

#include <iosfwd> // ostream

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
    double GetIm() const;
    void SetReal(double re);
    void SetImag(double im);
    double Abs() const;
    Complex Conj() const;
    
private:
    double m_re;
    double m_im;
}; // class Complex
} // namespace ilrd 

ilrd::Complex operator+(const ilrd::Complex&, const ilrd::Complex&);  
ilrd::Complex operator+=(const ilrd::Complex&, const ilrd::Complex&);
ilrd::Complex operator-(const ilrd::Complex&, const ilrd::Complex&);  
ilrd::Complex operator*(const ilrd::Complex&, const ilrd::Complex&);  
ilrd::Complex operator/(const ilrd::Complex&, const ilrd::Complex&);  
bool operator==(const ilrd::Complex&, const ilrd::Complex&);  
bool operator!=(const ilrd::Complex&, const ilrd::Complex&);  
bool operator>(const ilrd::Complex&, const ilrd::Complex&);  
bool operator<(const ilrd::Complex&, const ilrd::Complex&);  
std::ostream& operator<<(std::ostream&, const ilrd::Complex&);

//add functuanality for >>
//??? std::istream& operator>>(std::istream&, ilrd::Complex&);

#endif
