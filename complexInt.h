#pragma once

#include <iostream>
#include <sstream>
#include <string.h>
using namespace std;




class Complex         
{
private:
    double re, im;      

public:

    Complex(){
    };

    Complex(double r)
    {
        this->re = r;
        this->im = 0;
    }

    Complex(double r, double i)
    {
        this->re = r;
        this->im = i;
    }

    Complex(const Complex& c)  
    {
        this->re = c.re;
        this->im = c.im;
    }

    ~Complex()
    {
    }

    //функции

    // Модуль комплексного числа
    double abs()
    {
        return sqrt(re * re + im * im);
    }

    // оператор присваивания
    Complex& operator = (Complex& c)
    {
        this->re = c.re;
        this->im = c.im;

        return (*this);
    }

    // оператор +=
    Complex& operator += (Complex& c)
    {
        this->re += c.re;
        this->im += c.im;
        return *this;
    }

    bool operator < (Complex c) 
    {
        if (re < c.re) {
            return true;
        }
        else if (re == c.re && im < c.im) {
            return true;
        }
        return false;
    }

    bool operator > (Complex c)
    {
        if (this->re > c.re) {
            return true;
        }else if (this->re == c.re && this->im > c.im) {
            return true;
        }
        return false;

    }

    bool operator == (Complex c)
    {
        if (this->re == c.re && this->im == c.im) {
            return true;
        }
        return false;

    }


    string getString() {

        ostringstream s1,s2;
        s1 << this->re;
        s2 << this->im;
        string str;

        if (re == 0 && im != 0) {
            str = s2.str() + "i";
        }
        else if (im == 0 && re != 0) {
            str = s1.str();
        }
        else if (im == 0 && re == 0) {
            str = "0";
        }
        else if (im == 1) {
            str = s1.str() + "+i";
        }
        else {
            str = s1.str() + "+" + s2.str() + "i";
        }

        
        return str;
    }
};

