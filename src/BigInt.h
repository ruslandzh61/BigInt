#ifndef BIGINT_H
#define BIGINT_H

#include <list>
#include <string>

class BigInt
{
    friend std::ostream& operator<<(std::ostream& sout, const BigInt& a);
    friend std::istream& operator>>(std::istream& sinp, BigInt& a);
    
    
	friend BigInt operator+(const BigInt& a, const BigInt& b);
    friend BigInt operator-(const BigInt& a, const BigInt& b);
    friend BigInt operator*(const BigInt& a, const BigInt& b);
    friend BigInt operator*(const BigInt& a, int n);
    friend BigInt operator*(int n, const BigInt& b);
    friend BigInt operator/(const BigInt& a, const BigInt& b);
    friend BigInt operator/(const BigInt& a, int n);
    friend BigInt operator%(const BigInt& a, const BigInt& b);
    friend BigInt operator%(const BigInt& a, int n);
    
    friend BigInt operator+(const BigInt& a);
    friend BigInt operator-(const BigInt& a);
    
    friend bool operator<(const BigInt& a, const BigInt& b);
    friend bool operator>=(const BigInt& a, const BigInt& b);
    friend bool operator>(const BigInt& a, const BigInt& b);
    friend bool operator<=(const BigInt& a, const BigInt& b);
    friend bool operator==(const BigInt& a, const BigInt& b);
    friend bool operator!=(const BigInt& a, const BigInt& b);
    
    
	public:
    
    const BigInt& operator+=(const BigInt& b);
    const BigInt& operator-=(const BigInt& b);
    const BigInt& operator*=(const BigInt& b);
    const BigInt& operator*=(int n);
    const BigInt& operator/=(const BigInt& b);
    const BigInt& operator/=(int n);
    const BigInt& operator%=(const BigInt& b);
    const BigInt& operator%=(int n);
    
    BigInt& operator=(const BigInt& b);
    
    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);
    
	BigInt();
    BigInt(int n);
    BigInt(const BigInt& other);
	BigInt(const std::string& str);
	std::string toStr() const;
    BigInt abs() const;
    bool static haveSameSigns(const BigInt& a, const BigInt& b);
    
	private:
    bool checkIfDigit(char ch);
    void construct(const std::string& str);
	std::list<int> digits;
	bool isNegative;
};

std::ostream& operator<<(std::ostream& sout, const BigInt& a);
std::istream& operator>>(std::istream& sinp, BigInt& a);

BigInt operator+(const BigInt& a, const BigInt& b);
BigInt operator-(const BigInt& a, const BigInt& b);
BigInt operator*(const BigInt& a, const BigInt& b);
BigInt operator*(const BigInt& a, int n);
BigInt operator*(int n, const BigInt& b);
BigInt operator/(const BigInt& a, const BigInt& b);
BigInt operator/(const BigInt& a, int n);
BigInt operator%(const BigInt& a, const BigInt& b);
BigInt operator%(const BigInt& a, int n);

BigInt operator+(const BigInt& a);
BigInt operator-(const BigInt& a);

bool operator<(const BigInt& a, const BigInt& b);
bool operator>=(const BigInt& a, const BigInt& b);
bool operator>(const BigInt& a, const BigInt& b);
bool operator<=(const BigInt& a, const BigInt& b);
bool operator==(const BigInt& a, const BigInt& b);
bool operator!=(const BigInt& a, const BigInt& b);

#endif