#include "BigInt.h"
#include <sstream>
#include <stdexcept>

using namespace std;

BigInt::BigInt()
:isNegative(false)
{
	digits.push_back(0);
}

BigInt::BigInt(int n)
{
    ostringstream sout;
    sout << n;
    std::string n_str = sout.str();
    construct(n_str);
}

BigInt::BigInt(const BigInt& other)
{
    this->isNegative = other.isNegative;
    this->digits = other.digits;
}

BigInt::BigInt(const string& str)
{
	construct(str);
}

bool BigInt::checkIfDigit(char ch)
{
    return (0 <= ch - '0') && (ch - '0' <= 9); 
}

void BigInt::construct(const std::string& str)
{
    isNegative = false;
	istringstream sinp(str);
	char ch;
	sinp >> ch;
	int countOfDigits = 0;
	if(ch == '-' || ch == '+')
	{
		isNegative = ch == '-';
	}
	else
	{
        if (!checkIfDigit(ch))
            throw std::invalid_argument("invalid string representation");
		countOfDigits++;
		digits.push_back(ch - '0');
	}
	while(sinp >> ch)
	{
        if (!checkIfDigit(ch))
            throw std::invalid_argument("invalid string representation");
		digits.push_back(ch - '0');
		countOfDigits++;
	}
	if(countOfDigits == 1 && digits.front() == 0)
		isNegative = false;
}

string BigInt::toStr() const
{
	ostringstream sout;
	if(isNegative)
		sout << "-";
	for (auto it = digits.begin(); it != digits.end(); ++it)
	{
		sout << *it;
	}
	
	return sout.str();
}

bool BigInt::haveSameSigns(const BigInt& a, const BigInt& b)
{
    return (a.isNegative && b.isNegative) || (!a.isNegative && !b.isNegative);
}

BigInt BigInt::abs() const
{
    BigInt res = *this;
    res.isNegative = false;
    return res;
}


std::ostream& operator<<(std::ostream& sout, const BigInt& a)
{
    sout << a.toStr();
	return sout;
}

std::istream& operator>>(std::istream& sinp, BigInt& a)
{
    a.isNegative = false;
    a.digits.clear();
    
	std::string s;
	sinp >> s;
	int countOfDigits = 0;
	if(s[0] == '-' || s[0]    == '+')
	{
		a.isNegative = s[0] == '-';
	}
	else
	{
		countOfDigits++;
		a.digits.push_back(s[0] - '0');
	}
    int i = 1;
	while(i != s.length())
	{
		a.digits.push_back(s[i] - '0');
		countOfDigits++;
        i++;
	}
	if(countOfDigits == 1 && a.digits.front() == 0) //if digit equals zero
		a.isNegative = false;
    return sinp;
}

BigInt& BigInt::operator=(const BigInt& b) //instead BigInt t(a.toStr());
{
    this->isNegative = b.isNegative;
    this->digits = b.digits;
    return *this;
}



BigInt operator+(const BigInt& a, const BigInt& b)
{
    return BigInt(a) += b;
}

BigInt operator-(const BigInt& a, const BigInt& b)
{
    return BigInt(a) -= b;
}

BigInt operator*(const BigInt& a, const BigInt& b)
{
    return BigInt(a) *= b;
}

BigInt operator*(const BigInt& a, int n)
{
    BigInt r = a;
    r *= n;
    return r;
}

BigInt operator*(int n, const BigInt& b)
{
    BigInt r = b;
    r *= n;
    return r;
}

BigInt operator/(const BigInt& a, const BigInt& b)
{
    return BigInt(a) /= b;
}

BigInt operator/(const BigInt& a, int n)
{
    BigInt r = a;
    r /= n;
    return r;
}

BigInt operator%(const BigInt& a, int n)
{
    BigInt r = a;
    r %= n;
    return r;
}



BigInt operator+(const BigInt& a)
{
    BigInt r(a);
    return r;
}

BigInt operator-(const BigInt& a)
{
    BigInt r(a);
    r.isNegative = !r.isNegative;
    return r;
}



BigInt& BigInt::operator++() //prefix
{
   *this += 1;
   return *this;
}

BigInt BigInt::operator++(int) //postfix
{
    BigInt tmp = *this;
    operator++();
    return tmp;
}

BigInt& BigInt::operator--() //perfix
{
   //BigInt b(1);
   *this -= 1;
   return *this;
}

BigInt BigInt::operator--(int) //postfix
{
    BigInt tmp = *this;
    operator--();
    return tmp;
}



const BigInt& BigInt::operator+=(const BigInt& b) //no const for a, since it changes value of a
{
    if (BigInt::haveSameSigns(*this, b)) // check if numbers are of the same sign
    {
        BigInt r;
        r.digits.pop_front();
        r.isNegative = isNegative;
        
        auto itA = digits.rbegin();
        auto itB = b.digits.rbegin();
        
        int carry = 0;
        while (itA != digits.rend() || itB != b.digits.rend())
        {
            int d = carry;
            if (itA != digits.rend())
            {
                d += *itA;
                ++itA;
            }
            if (itB != b.digits.rend())
            {
                d += *itB;
                ++itB;
            }
            r.digits.push_front(d%10);
            carry = d / 10;
            
        }
        if (carry != 0)
            r.digits.push_front(carry);
        *this = r;
        return *this;
    }
    if (isNegative) 
    {
        isNegative = false;
        *this -= b;
        isNegative = !isNegative;
        return *this;
    }
    BigInt t = b;
    t.isNegative = false;
    *this -= t;
    return *this;
}

const BigInt& BigInt::operator-=(const BigInt& b)
{
    if (BigInt::haveSameSigns(*this, b))
    {
        if (this->abs() > b.abs()) // 4111 - 3999; (-4111) - (-3999)
        {
            BigInt r;
            r.digits.pop_front();
            r.isNegative = isNegative;
            
            auto itA = digits.rbegin();
            auto itB = b.digits.rbegin();
            
            int carry = 0;
            while (itA != digits.rend() || itB != b.digits.rend())
            {
                int d = carry;
                carry = 0;
                if (itA != digits.rend())
                {
                    d += *itA;
                    ++itA;
                }
                if (itB != b.digits.rend())
                {
                    d -= *itB;
                    ++itB;
                }
                if (d < 0)
                {
                    carry--;
                    d += 10;
                }
                r.digits.push_front(d);
            }
            //get rid of zeros in the beginning if there are zeros; 
            while(r.digits.front() == 0)
            {
                r.digits.pop_front();
            }
            *this = r;
            return *this;
        }
        else if (this->abs() == b.abs()) // r = 0
        {
            BigInt r;
            *this  = r;
            return *this;
        }
        /*abs(a) < abs(b): 3999 - 4111; -3999 - (-4111)
        we have a method that calculates subtraction of one number from another with the same sign, 
		so we change sign of final result:a - b = -(b - a)*/
        BigInt t(*this);
        *this = -(b - t); 
        return *this; // 3999 - 4111 = - (4111 - 3999(case described above)); -3999 - (-4111) = -(-4111 - (-3999))
    }
    // a and b have opposite signs
    // we have a method that calculates sum of numbers with the same sign, so we change 
    if (isNegative) // a is negative, b - positive
    {
        isNegative = false;
        *this += b;
        isNegative = true;
        return *this;
    }
    // b is negative
    BigInt t(b);
    t.isNegative = false;
    *this += t;
    return *this;
}

const BigInt& BigInt::operator*=(const BigInt& b)
{
    BigInt r;
    if (toStr() == "0" || b.toStr() == "0")
    {
        *this = r;
        return *this;
    }
    r.isNegative = !(BigInt::haveSameSigns(*this, b));
    r.digits.pop_front();
    
    auto itA = digits.rbegin();
    BigInt copy = b;
    while(itA != digits.rend())
    {
        r += *itA * copy;
        copy.digits.push_back(0);
        ++itA;
    }
    
    
    *this = r;
    return *this;
}

const BigInt& BigInt::operator*=(int n)
{
    if (n == 0)
    {
        *this = 0;
        return *this;
    }
    if (n < 0)
    {
        n = -n;
        this->isNegative = !this->isNegative;
    }
    if (n == 1)
        return *this;
    
    auto itA = digits.rbegin();
    int carry = 0;
    long long tmp;
    while(itA != digits.rend())
    {
        tmp = n * *itA + carry;
        carry = tmp / 10;
        *itA = tmp%10;
        ++itA;
    }
    while (carry != 0)
    {
        digits.push_front(carry % 10);
        carry /= 10;
    }
    return *this;
}

const BigInt& BigInt::operator/=(const BigInt& b)
{
    if (b.toStr() == "0")
        throw std::invalid_argument("division by zero");
    BigInt r;
    if (toStr() == "0" || this->abs() < b.abs())
    {
        *this = r;
        return *this;
    }
    if (*this == b)
    {
        BigInt res(1);
        *this = res;
        return *this;
    }
    r.isNegative = !(BigInt::haveSameSigns(*this, b));
    r.digits.pop_front();
    
    auto itA = digits.begin();

    BigInt remainder("0");
    BigInt dividend("1");
    while(itA != digits.end())
    {
        dividend = remainder * 10 + *itA;
        BigInt copy = dividend;
        *itA = 0;
        while(copy >= b)
        {
            copy -= b;
            ++*itA;
        }
        remainder = dividend - *itA * b;
        ++itA;
    }
    while(digits.front() == 0)
    {
        digits.pop_front();
    }
    
    return *this;
}

const BigInt& BigInt::operator/=(int n)
{
    if (n == 0)
        throw std::invalid_argument("division by zero");
    BigInt r;
    if (n < 0)
    {
        n = -n;
        this->isNegative = !this->isNegative;
    }
    if (toStr() == "0" || this->abs() < n)
    {
        *this = r;
        return *this;
    }
    if (n == 1)
        return *this;
    
    auto itA = digits.begin();
    int remainder = 0;
    int dividend;
    while(itA != digits.end())
    {
        dividend = remainder * 10 + *itA;
        *itA = dividend / n;
        remainder = dividend % n;
        ++itA;
    }
    while(digits.front() == 0)
    {
        digits.pop_front();
    }
    return *this;
}

const BigInt& BigInt::operator%=(const BigInt& b)
{
    if (b == 0)
        throw std::invalid_argument("division by zero");
    BigInt r;
    if (toStr() == "0" || this->abs() < b.abs())
    {
        return *this;
    }
    if (*this == b)
    {
        *this = r;
        return *this;
    }
    auto itA = digits.begin();

    BigInt remainder("0");
    BigInt dividend("1");
    while(itA != digits.end())
    {
        dividend = remainder * 10 + *itA;
        BigInt copy = dividend;
        *itA = 0;
        while(copy >= b)
        {
            copy -= b;
            ++*itA;
        }
        remainder = dividend - *itA * b;
        ++itA;
    }
    
    *this = remainder;
    return *this;
}

const BigInt& BigInt::operator%=(int n)
{

    if (n == 0)
        throw std::invalid_argument("division by zero");
    BigInt r;
    if (n < 0)
    {
        n = -n;
        this->isNegative = !this->isNegative;
    }
    if (toStr() == "0" || this->abs() < n)
    {
        return *this;
    }
    if (n == 1)
    {
        *this = r;
        return *this;
    }
    auto itA = digits.begin();
    int remainder = 0;
    int dividend;
    while(itA != digits.end())
    {

        dividend = remainder * 10 + *itA;
        remainder = dividend % n;
        ++itA;
    }
    *this = remainder;
    return *this;
}


bool operator==(const BigInt& a, const BigInt& b)
{
    return operator>=(a, b) && operator<=(a,b);
}

bool operator!=(const BigInt& a, const BigInt& b)
{
    return !operator==(a, b);
}

bool operator<(const BigInt& a, const BigInt& b)
{
    if (!BigInt::haveSameSigns(a, b))
        return a.isNegative && !b.isNegative;
    if (a.digits.size() != b.digits.size())
        return b.digits.size() > a.digits.size();
	
    auto itA = a.digits.begin();
    auto itB = b.digits.begin();
    while(itA != a.digits.end())
    {
        if (*itA != *itB)
            return *itA < *itB;
        ++itA;
        ++itB;
    }
    return false;
}

bool operator>=(const BigInt& a, const BigInt& b)
{
    return !operator<(a, b);
}

bool operator>(const BigInt& a, const BigInt& b)
{
    return operator<(b, a);
}

bool operator<=(const BigInt& a, const BigInt& b)
{
    return !operator>(a, b);
}


