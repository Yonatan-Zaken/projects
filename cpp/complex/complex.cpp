/*********************************/
/*    Copmlex Number             */
/*	  Language: c++  		     */
/*    Author: Yonatan            */
/*    Reviewed By:               */
/*    Date:   13/3/20            */
/*********************************/
#include <cmath> // sqrt 

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

double Complex::GetIm() const
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
    c1.m_im = -m_im;
    return c1;
}
