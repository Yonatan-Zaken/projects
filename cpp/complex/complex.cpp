/*********************************/
/*    Copmlex Number             */
/*	  Language: c++  		     */
/*    Author: Yonatan            */
/*    Reviewed By:               */
/*    Date:   13/3/20            */
/*********************************/
#include <cmath> // sqrt 
#include <cassert> // assert
#include <iostream> // <<

#include "complex.hpp"

using namespace ilrd;
/************************************ Ctors ***********************************/

Complex::Complex(double re, double im): m_re(re), m_im(im)
{
}

/***************************** Member Functions *******************************/

double Complex::GetReal() const
{
    return m_re;
}

double Complex::GetImag() const
{
    return m_im;
}

void Complex::SetReal(double re)
{
    m_re = re;
}

void Complex::SetImag(double im)
{
    m_im = im;
}

double Complex::Abs() const
{
    return sqrt((m_re * m_re) + (m_im * m_im));    
}

Complex Complex::Conj() const
{
    Complex c1(m_re);
    c1.m_im = (m_im == 0) ? 0 : -m_im;
    
    return c1;
}

/**************************** Operator Functions ******************************/

const Complex operator+(const Complex& c1, const Complex& c2)
{
    double re = c1.GetReal() + c2.GetReal();
    double im = c1.GetImag() + c2.GetImag();
    
    Complex sum(re,im);
    
    return sum;
}

const Complex operator-(const Complex& c1, const Complex&c2)
{
    double re = c1.GetReal() - c2.GetReal();
    double im = c1.GetImag() - c2.GetImag();
    
    Complex sub(re,im);
    
    return sub;
}

const Complex operator*(const Complex& c1, const Complex& c2)
{
    double re = (c1.GetReal() * c2.GetReal()) - (c1.GetImag() * c2.GetImag());
    double im = (c1.GetReal() * c2.GetImag()) + (c1.GetImag() * c2.GetReal());
    
    Complex mult(re,im);
    
    return mult;
}

const Complex operator/(const Complex& c1, const Complex& c2)
{
    assert((0 != c2.GetReal()) || (0 != c2.GetImag()));
    
    Complex conj = c2.Conj();
    Complex mult = c2 * conj;
    double abs = mult.GetReal();
    
    Complex div = (c1 * conj);
    div.SetReal(div.GetReal() / abs);
    div.SetImag(div.GetImag() / abs);
    
    return div;
}

bool operator==(const Complex& c1, const Complex& c2)
{
    return ((c1.GetReal() == c2.GetReal()) && (c1.GetImag() == c2.GetImag()));
}

bool operator!=(const Complex& c1, const Complex& c2)
{
    return (!(c1 == c2));
}

bool operator>(const Complex& c1, const Complex& c2)
{
    return (c1.Abs() > c2.Abs());
}

bool operator<(const Complex& c1, const Complex& c2)
{
    return (!(c1 > c2));
}

/************************** Operator Member Functions *************************/

Complex& Complex::operator+=(const Complex& c)
{
    *this = *this + c;
    return *this;    
}

Complex& Complex::operator-=(const Complex& c)
{
    *this = *this - c;
    return *this;    
}

Complex& Complex::operator*=(const Complex& c)
{
    *this = *this * c;
    return *this;    
}

Complex& Complex::operator/=(const Complex& c)
{
    *this = *this / c;
    return *this;    
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
    os << "(" << c.GetReal() << "," << c.GetImag() << "i)";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c)
{
    double re = 0; 
    is >> re; 
    double im = 0;
    is >> im;
    
    c.SetReal(re);
    c.SetImag(im);

    return is; 
}
