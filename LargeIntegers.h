/*
 this class define a new type of integer  numbers , called InfInt
 which is support the ability to deal with big integers.
 using the arithmetic and logical operators.
 we getting the big number as string (or long if the number
 is small) and store his digits in vector as chars
 i.e. a number like 1234 is stored as the vector {4,3,2,1}.
 we implement arithmetic operators by using the vector.
 in addition , we define the logical operators by convert
 this number to binary representation and work with bits.

 */
#ifndef FIVE_InfInt_H
#define FIVE_InfInt_H
#include <iostream>
#include <vector>


using namespace std;
enum Sign {
    positive, negative
};

class InfInt {
public:
    InfInt();
    InfInt(long n);
    InfInt(const char *c);
    InfInt(const string &s);
    string toString() const;
    string toBinary() const;
    bool IsNegative() const;
    int numDigits() const;
    int getDigit(int k) const;

    operator int() const;
    bool operator==(const InfInt &n) const;
    bool operator==(int n) const;
    bool operator<(const InfInt &n) const;
    bool operator<(int n) const;
    bool operator!=(const InfInt &n) const;
    bool operator!=(int n) const ;
    bool operator>(const InfInt &n) const;
    bool operator>(int n) const;
    bool operator>=(const InfInt &n) const;
    bool operator<=(const InfInt &n) const;


    InfInt operator+(const InfInt &n) const;
    InfInt operator-(const InfInt &n) const;
    InfInt operator*(const InfInt &n) const;
    InfInt operator*(int n) const;
    InfInt operator/(const InfInt &n) const;
    InfInt operator/(int n) const;
    InfInt operator%(const InfInt &n) const;
    InfInt operator%(int n) const;
    InfInt &operator+=(const InfInt &n);
    InfInt &operator-=(const InfInt &n);
    InfInt &operator*=(const InfInt &n);
    InfInt &operator*=(int n);
    InfInt operator++();
    InfInt operator++(int);
    const InfInt operator--();
    const InfInt operator--(int);

    InfInt operator&(const InfInt &n);
    InfInt operator^(const InfInt &n);
    InfInt operator|(const InfInt &n);
    InfInt &operator&=(const InfInt &n);
    InfInt operator>>(int n) const;
    InfInt operator<<(int n) const;
    InfInt &operator>>=(int n);


    friend ostream &operator<<(ostream &o, const InfInt &n);
    friend istream &operator>>(istream &i, InfInt &n);

private:
    Sign mySign;
    vector<char> myDigits;
    int digitsNum;
    void addSigDigit(int value);
    void changeDigit(int k, int value);
    void normalize();
};

InfInt FromBinaryToInfInt(string binary);


#endif