#include <cstdlib>
#include "LargeIntegers.h"
#include <iostream>
#include <limits.h>
#include <string>
#include <cstring>


/*
 * Constructor.
 * initialize the number to 0.
 */
InfInt::InfInt() {
    mySign = positive;
    myDigits.resize(1, '0');
    digitsNum = 1;
}




/*
 * Constructor.
 * get number in string and separate the digits
 * and add to vector .
 */
InfInt::InfInt(const string &s) {
    myDigits.resize(s.size(), '0');//initialize the vector to the desirable size.
    digitsNum = 0;
    int limit = 0; //variable to determine the index of the first digit
    if (s.size() == 0) { //initialize to zero if the string is empty
        myDigits.resize(1);
        mySign = positive;
        addSigDigit(0);
        return;
    }
    if (s[0] == '-') { //identifying the negatives by -
        mySign = negative;
        limit = 1; // the sign - is not a digit so we don't counting it;
    } else //positive numbers
        mySign = positive;
    if (s[0] == '+') //dealing with positive number with + in start
        limit = 1;
    for (int k = s.size() - 1; k >= limit; k--) {
        if (!isdigit(s[k])) //identify the non-digits
            throw "bad input";
        addSigDigit(s[k] - '0'); //adding the digits from the right digit to left
    }
    normalize(); //get rid of redundant zeroes
}

/*
 * Constructor.
 * get long number and convert it to  InfInt;
 * we dealing with numbers as positive numbers
 * ans save the sign in appropriate variable.
 */
InfInt::InfInt(long n) {

    myDigits.resize(1, '0'); //initialize the vector
    digitsNum = 0;
    if (n < 0) { // negative number
        mySign = negative;
        n = n * -1; //dealing as positive number
    } else { //positive number
        mySign = positive;
    }
    addSigDigit(n % 10); //get rightest digit
    n = n / 10;// get rid of rightest digit
    while (n != 0) { //get the digits of the number
        addSigDigit(n % 10);
        n = n / 10;
    }
}

/*
 * this constructor get a char* string .
 * implementing this constructor available
 * us to declare the InfInt as
 * InfInt x="....."
 */
InfInt::InfInt(const char* c){
    string s="";
    for(int i=0;c[i]!='\0';i++){
        s=s+c[i];
    }
    myDigits.resize(s.size(), '0');//initialize the vector to the desirable size.
    digitsNum = 0;
    int limit = 0; //variable to determine the index of the first digit
    if (s.size() == 0) { //initialize to zero if the string is empty
        myDigits.resize(1);
        mySign = positive;
        addSigDigit(0);
        return;
    }
    if (s[0] == '-') { //identifying the negatives by -
        mySign = negative;
        limit = 1; // the sign - is not a digit so we don't counting it;
    } else //positive numbers
        mySign = positive;
    if (s[0] == '+') //dealing with positive number with + in start
        limit = 1;
    for (int k = s.size() - 1; k >= limit; k--) {
        if (!isdigit(s[k])) //identify the non-digits
            throw "bad input";
        addSigDigit(s[k] - '0'); //adding the digits from the right digit to left
    }
    normalize(); //get rid of redundant zeroes

}


/*
 * return the number of the digits that our infint cosist of.
 */
int InfInt::numDigits() const {
    return digitsNum;
}


/*
 * this function get rid of redundant zeroes
 * that appear in the left of the first
 * digit distinct from zero
 */
void InfInt::normalize() {
    int i;
    for (i = numDigits() - 1; i >= 0; i--) { //find redundant zeroes and deal with
        if (getDigit(i) != 0)
            break;
        digitsNum--; //is redundant
    }
    if (i < 0) { //all zeroes
        digitsNum = 1;
        mySign = positive;
    }
}

/*
 * return the kth digit of out infint number.
 * the 0th digit is the rightest one of the digit.
 */
int InfInt::getDigit(int k) const {
    if (k >= 0 && k < numDigits()) { //relevant index
        return myDigits[k] - '0';
    }
    return 0;
}

/*
 * the function get an index and value , and change
 * the kth digit with a given value.
 */
void InfInt::changeDigit(int k, int value) {
    if (k >= 0 && k < numDigits())
        myDigits[k] = char('0' + value);
    else
        throw "change digit failed , irrelevant index.";
}

/*
 * value added to InfInt as most significant digit
 * Note: 0th digit is least significant digit
 */
void InfInt::addSigDigit(int value) {
    if (digitsNum >= myDigits.size()) { //resize the vector to accept the new value
        myDigits.resize(myDigits.size() * 2);
    }
    myDigits[digitsNum] = char('0' + value);
    digitsNum++;
}

/*
 * return true if the number is negative , false if positive or 0.
 */
bool InfInt::IsNegative() const {
    return mySign == negative;
}

/*
 * return the number as string.
 */
string InfInt::toString() const {
    string s = "";
    if (IsNegative())
        s = '-';
    for (int j = numDigits() - 1; j >= 0; j--) { //add digit by digit to string
        s += char('0' + getDigit(j));
    }
    return s;
}

/*
 * this function get a binary string , and convert
 * it to InfInt,
 */
InfInt FromBinaryToInfInt(string binary) {
    InfInt result("0");
    InfInt x("1"); //used to be powers of 2
    if (binary[0] == '0') { //MSB=0 -> positive number
        for (int i = binary.length() - 1; i >= 0; i--) { //binary[0]*2^0+binary[1]*2^1 ...
            result += (x * (binary[i] - '0'));
            x *= 2; //get next power of two
        }
    } else if (binary[0] == '1') { //MSB=1 -> negative number
        long firstOne = -1; //initialize , used to locate first significant 1.
        for (int i = 0; i < binary.length(); i++) { //get the index of the first significant 1
            if (binary[i] == '0') {
                firstOne = i - 1; //the index is one before.
                break;
            }
        }
        if (firstOne == -1) //there is no 0's
            result = InfInt(-1);
            /*
             * we evaluate after we find the first significant 1.
             * this well be a negative number(appropriate power of 2).
             *
             */
        else {
            for (int i = binary.length() - 1; i > firstOne; i--) {
                result += (x * (binary[i] - '0'));
                x *= 2;
            }
            result -= (x * (binary[firstOne] - '0')); //minus the value
        }
    }
    return result;
}

/*
 * convert our number to binary represintaion
 * according to Two'Complement.
 */
string InfInt::toBinary() const {
    string str = toString(); //get the string of the number
    InfInt tempInfInt(str);
    string binaryRep;  //binary representation string
    if (tempInfInt == 0) //0 is the binary representation of 0
        return "0";
    while (tempInfInt != 0) {
        if (tempInfInt % 2 == 0) { //LSB IS 0
            binaryRep = "0" + binaryRep;
        } else { //LSB IS 1
            binaryRep = "1" + binaryRep;
        }
        tempInfInt = tempInfInt / 2; //to allow to get the next bit
    }
    binaryRep = "0" + binaryRep; //initialize as positive binary string
    if (IsNegative()) {
        int n = binaryRep.length();
        int i;
        for (i = n - 1; i >= 0; i--)
            if (binaryRep[i] == '1')
                break;
        if (i == -1) //negative number , get 1 in MSB
            return '1' + binaryRep;

        for (int k = i - 1; k >= 0; k--) {
            if (binaryRep[k] == '1')
                binaryRep[k] = '0';
            else
                binaryRep[k] = '1';
        }
    }

    return binaryRep;
}


/*
 * print the number by cout.
 */
ostream &operator<<(ostream &o, const InfInt &n) {
    string s = n.toString();
    o << s;
    return o;
}

/*
 * scan the number from the user : cin.
 */
istream &operator>>(istream &i, InfInt &n) {
    string s;
    cout << "Put an integer number" << endl;
    i >> s;
    n = InfInt(s);
    return i;
}

/*
 * casting infint to int.
 * if infint>max_int >> return max_int.
 * if infint<min_int >>return min_int.
 * if min_int<infint<max_int >> return infint as int.
 */
InfInt::operator int() const {
    int result = 0;
    if (*this > INT_MAX) return INT_MAX;
    if (*this < INT_MIN) return INT_MIN;
    for (int k = numDigits() - 1; k >= 0; k--) { //get digit by digit

        result = result * 10 + getDigit(k);
    }
    if (IsNegative())
        result *= -1;
    return result;
}

/*
 * relational and comparison operators overloading.
 * define "<" how it will be executing , and use it
 * to define the rest of the  functions.
 *
 */
bool InfInt::operator<(const InfInt &n) const {
    if (IsNegative() != n.IsNegative()) //if signs aren’t equal, this < n only if this is negative
        return IsNegative();
    if (numDigits() != n.numDigits()) { //if the digits aren’t the same must check the digits and sign
        return (numDigits() < n.numDigits() && (!IsNegative())) ||
               (numDigits() > n.numDigits() && IsNegative());
    }

    for (int k = numDigits() - 1; k >= 0; k--) { //they have the same num of digits
        if (getDigit(k) < n.getDigit(k))  //comparing by digits in this and n
            return (!IsNegative());
        if (getDigit(k) > n.getDigit(k))
            return IsNegative();
    }
    return false; //they are equeal

}

bool InfInt::operator<(int n) const {
    InfInt bigN(n);
    return *this < bigN;

}

bool InfInt::operator>(const InfInt &n) const {
    return n < *this;
}

bool InfInt::operator>(int n) const {
    InfInt bigN(n);
    return *this > bigN;
}

bool InfInt::operator==(const InfInt &n) const {
    if (*this < n || *this > n)
        return false;
    return true;
}

bool InfInt::operator==(int n) const {
    InfInt x;
    x = InfInt(n);
    return *this == x;

};

bool InfInt::operator!=(const InfInt &n) const {
    return !(*this == n);
}

bool InfInt::operator!=(int n) const {
    InfInt x(n);
    return *this != x;

}

bool InfInt::operator>=(const InfInt &n) const {
    if (*this > n || *this == n)
        return true;
    return false;
}

bool InfInt::operator<=(const InfInt &n) const {
    if (*this < n || *this == n)
        return true;
    return false;
}



/*
 * -= operator overloading ,using long substraction method.
 */
InfInt &InfInt::operator-=(const InfInt &n) {
    int diff;
    int borrow = 0; //initialize
    int len = numDigits();
    if (this == &n) { //x-x=0
        *this = InfInt();
        return *this;
    }
    if (IsNegative() != n.IsNegative()) { //signs opposite? then this - (-n) = this + n
        *this += (n * -1);
        return *this;
    }
    /* signs are the same, check which number is larger
     and switch to get larger number "on top" if necessary
     since sign can change when subtracting
     */
    if (!IsNegative() && (*this) < n || IsNegative() && (*this) > n) {
        *this = n - *this;
        if (!IsNegative()) mySign = negative;
        else
            mySign = positive; // toggle sign
        return *this;
    }
    // same sign and larger number on top
    for (int k = 0; k < len; k++) {
        diff = getDigit(k) - n.getDigit(k) - borrow;
        borrow = 0;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        changeDigit(k, diff);
    }
    normalize(); //get rid of redundant zeroes in left
    return *this;
}

/*
 * += operator overloading ,using long addition method.
 */
InfInt &InfInt::operator+=(const InfInt &n) {
    int sum;
    int carry = 0;
    int len = numDigits();

    if (n == 0) //x+0=x
        return *this;
    if (this == &n) { //x+x=2x
        *this *= 2;
        return *this;
    }
    if (!IsNegative() != !(n.IsNegative())) { //signs not the same, subtract
        *this -= (n * -1);
        return *this;
    }
    if (len < n.numDigits()) //process both numbers until one is exhausted
        len = n.numDigits();
    for (int k = 0; k < len; k++) { //long addition method.
        sum = getDigit(k) + n.getDigit(k) + carry;
        carry = sum / 10; //10=base.
        sum = sum % 10; //10=base
        if (k < digitsNum) {
            changeDigit(k, sum);
        } else {
            addSigDigit(sum);
        }
    }
    if (carry != 0) //add as first digit from left{
        addSigDigit(carry);
    return *this;
}

/*
 *multiplication infint with int using long multiplication.
 */
InfInt &InfInt::operator*=(int n) {
    int carry = 0;
    int product; //product of num and one digit+carry.
    int len = numDigits();
    if (0 == n) { //x*0=0
        *this = InfInt(); //initialize as zero.
        return *this;
    }
    if (10 < n || n < 0) { // handle pre-condition failure . 10 is the base.
        *this *= InfInt(n);
        return *this;
    }
    if (1 == n) { //x*1=x;
        return *this;
    }
    //long multiplication method
    for (int k = 0; k < len; k++) { //once fo each digit
        product = n * getDigit(k) + carry;
        carry = product / 10;
        changeDigit(k, product % 10);
    }
    while (carry != 0) { //carry all digits.
        addSigDigit(carry % 10);
        carry /= 10;
    }
    return *this;
}

/*
 * multiplication operator over loading,
 * using standard "grade school method for multiplying.
 */
InfInt &InfInt::operator*=(const InfInt &n) {
    if (IsNegative() != n.IsNegative()) //opposite signs => -
        mySign = negative;
    else  //same signs => +
        mySign = positive;
    InfInt self(*this);
    InfInt sum; //to accumulate sum
    int len = n.numDigits();
    for (int k = 0; k < len; k++) {
        sum += self * n.getDigit(k); //kth digit * self
        self *= 10; //add a zero
    }
    *this = sum;
    return *this;
}

/*
 * additiom operator overloading , using += operator.
 */
InfInt InfInt::operator+(const InfInt &n) const {

    InfInt result(*this);
    result += n;
    return result;

}

/*
 * substraction operator over loading . using -= operator.
 */
InfInt InfInt::operator-(const InfInt &n) const {
    InfInt result(*this);
    result -= n;
    return result;
}

/*
 * multiplication operator overloading , using *= operator.
 */
InfInt InfInt::operator*(int n) const {
    InfInt result(*this);
    result *= n;
    return result;
}

/*
 * multiplication operator overloading , using *= operator.
 */
InfInt InfInt::operator*(const InfInt &n) const {
    InfInt result(*this);
    result *= n;
    return result;
}

/*
 * division operator overloading , getting infint param.
 * using "/" functiion with int parameter.
 */
InfInt InfInt::operator/(const InfInt &n) const {
    if (n == 0) //divide by zero
        throw "can not divide by zero";
    InfInt dividend(*this);
    InfInt tempDivisor(n);
    InfInt quotient; //result
    dividend.mySign = positive;
    tempDivisor.mySign = positive;
    string power2 = "1";
    for (int i = 0; i < digitsNum; i++) {
        power2 = power2 + "0";
    };
    InfInt x(power2); //x is a power of 2 which appropriate to out number digits.


    while (dividend >= tempDivisor) { // our number >= the divisor number.
        /*
         * this loop used to speed the runtime
         */
        while (dividend >= tempDivisor * x) {
            dividend -= (tempDivisor * x);
            quotient += x;
        }
        x = x / 10; //get rid of one digit

    }

    if (IsNegative() != n.IsNegative()) { //oppositie signs=> -
        quotient.mySign = negative;
        quotient.normalize(); //get rid of redundant zeroes from left
    }
    return quotient; //return the result
}

/*
 * division operator overloading , getting int ass parameter.
 * using long division method
 */
InfInt InfInt::operator/(int divisor) const {
    bool neg = false;
    int tempDivisor = divisor;
    if (divisor == 0) //divided by zero case
        throw ("can't divided by zero!");
    string number = this->toString(); //getting the number as string
    string tempNum = "";
    if (divisor < 0) { //treat all as positive number and keep the sign in boolean var.
        tempDivisor = divisor * -1; //from neg to positive.
        if (number[0] != '-') //our number is pos,divisor is neg => result is neg.
            neg = true;
        else if (number[0] == '-') //our number is neg ,divisor is neg =>result is pos.
            neg = false;
    }
    if (number[0] == '-') { //out number is neg
        if (divisor > 0) { //the divisor pos
            neg = true;
        }
        for (int i = 1; i < number.length(); i++) { //get the number without -
            tempNum += number[i];
        }
        number = tempNum;
    }

    divisor = tempDivisor; //updated divisor => without - and after determine the result sign

    string ans;
    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    int temp = number[idx] - '0'; //most left digit
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');
    // Repeatedly divide divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (number.size() > idx) {
        ans += (temp / divisor) + '0';  // Store result in answer i.e. temp / divisor
        temp = (temp % divisor) * 10 + number[++idx] - '0'; // // Take next digit of number
    }
    if (ans.length() == 0)     // If divisor is greater than number
        return InfInt("0");
    if (neg) //add - sign
        ans = '-' + ans;

    InfInt x(ans);
    return x;
}

/*
 * modulo operator overloading,infint paarameter.
 * x%y=x-(x/y)*y
 */
InfInt InfInt::operator%(const InfInt &n) const {
    return *this - (*this / n) * n;
}

/*
 * modulo operator overloading , int parameter.
 * x%y=x-(x/y)*y
 */
InfInt InfInt::operator%(int n) const {
    return *this - (*this / n) * n;
}

/*
 * Prefix ++ operator.
 * increment the number by 1 and return it.
 */
InfInt InfInt::operator++() {
    *this += 1;
    return *this;
}

/*
 * postfix ++ operator.
 * return the number then increment the number by 1.
 */
InfInt InfInt::operator++(int) {
    InfInt n(1);
    *this += 1;
    return *this - n;
}

/*
 * Prefix -- operator.
 * decrement the number by 1 and return it.
 */
const InfInt InfInt::operator--() {

    *this -= 1;
    return *this;
}

/*
 * postfix -- operator.
 * return the number then decrement the number by 1.
 */
const InfInt InfInt::operator--(int) {
    InfInt x(1);
    *this -= 1;
    return *this + x;

}

/*
 * AND operator overloading.
 * coverting the two numbers to two binary string
 * matching the min string to the max string,
 * execute AND between two digits in same index.
 */
InfInt InfInt::operator&(const InfInt &n) {
    string s1 = this->toBinary(); //get out number as binary string.
    string s2 = n.toBinary(); //get (n) number as binary string.
    string max, min;
    string result = "";

    /*
     *determine the max an min binary representation
     */
    if (s1.length() >= s2.length()) {
        max = s1;
        min = s2;
    } else {
        max = s2;
        min = s1;
    }
    int diff = max.length() - min.length(); //the difference between the two representations.
    if (min[0] == '0') { //positive number.
        for (int i = 0; i < diff; i++) { //we complete the min to max length by adding zeroes in left.
            min = '0' + min;
        }

    } else { //negative number
        for (int i = 0; i < diff; i++) { //we complete the min to max length by adding ones in left.
            min = '1' + min;
        }
    }
    /*
     * we execute & between every two digits in the same index in the two strings.
     */
    for (int i = 0; i < max.length(); i++) {
        if (((max[i] - '0') & (min[i] - '0')) == 0) {
            result = result + "0";
        } else {
            result = result + "1";
        }
    }
    return FromBinaryToInfInt(result); //convert result' binary string to infint and return it.
}

/*
 * &= operator overloading , using & operator we define .
 */
InfInt &InfInt::operator&=(const InfInt &n) {
    *this = *this & n;
    return *this;
}

/*
 * OR operator overloading.
 * coverting the two numbers to two binary string
 * matching the min string to the max string,
 * execute OR between two digits in same index.
 */
InfInt InfInt::operator|(const InfInt &n) {
    string s1 = this->toBinary(); //getting binary representation of the first num.
    string s2 = n.toBinary(); //getting binary representation of the 2nd num.
    string max, min;
    string result = "";

    //determine the max and min representation between them.
    if (s1.length() >= s2.length()) {
        max = s1;
        min = s2;
    } else {
        max = s2;
        min = s1;
    }
    int diff = max.length() - min.length(); //the differenece between the two strings.
    if (min[0] == '0') { //positive num
        for (int i = 0; i < diff; i++) { //we complete the min to max length by adding zeroes in left.
            min = '0' + min;
        }

    } else { //negative num
        for (int i = 0; i < diff; i++) { //we complete the min to max length by adding ones in left.
            min = '1' + min;
        }
    }
    for (int i = 0; i < max.length(); i++) { //execute OR between two digits in the same index.
        if (((max[i] - '0') | (min[i] - '0')) == 0) {
            result = result + "0";
        } else {
            result = result + "1";
        }
    }
    return FromBinaryToInfInt(result); //convert the binary result to infint and return it.
}

/*
 * XOR operator overloading.
 * coverting the two numbers to two binary string
 * matching the min string to the max string,
 * execute OR between two digits in same index.
 */
InfInt InfInt::operator^(const InfInt &n) {
    string s1 = this->toBinary(); //get the binary representation of the first num.
    string s2 = n.toBinary(); //get the binary representation of the second num.
    string max, min;
    string result = "";

    //determine the min and max representations between the two strings.
    if (s1.length() >= s2.length()) {
        max = s1;
        min = s2;
    } else {
        max = s2;
        min = s1;
    }
    int diff = max.length() - min.length(); //the difference between the two representations.
    if (min[0] == '0') { //positive numbers.
        for (int i = 0; i < diff; i++) { //complete the min string to the max by adding zeroes in left.
            min = '0' + min;
        }

    } else { //negative numbers.
        for (int i = 0; i < diff; i++) { //complete the min string to the max by adding zeroes in left.
            min = '1' + min;
        }
    }
    for (int i = 0; i < max.length(); i++) { //execute XOR between two digits in the same index.
        if (((max[i] - '0') ^ (min[i] - '0')) == 0) {
            result = result + "0";
        } else {
            result = result + "1";
        }
    }
    return FromBinaryToInfInt(result); //convert the binary result to infint.
}

/*
 * right shift operator overloading , get parameter >0.
 * if the number is positive , we add, in binary representation , zeroes
 * in left for each one  right  shifting , and add ones if the number is negative.
 */
InfInt InfInt::operator>>(int n) const {
    if (n == 0) //>>0 not ghange the number.
        return *this;
    if (n < 0)
        throw ("shifting must be with positive value");

    string binary = this->toBinary(); //get the number as binary representation.
    string shifting;
    for (int i = 0; i < binary.length(); i++) {
        if (IsNegative()) //we add ones in left for each one right shifting.
            shifting = '1' + shifting;
        else //we add zeroes in left for each one left shifting.
            shifting = '0' + shifting;
    }
    if (n < binary.length()) { //change the bits that still in the representation.
        for (int i = shifting.length() - 1, counter = n; i > n; i--, counter++) {
            shifting[i] = binary[binary.length() - 1 - counter];
        }
    }
    return FromBinaryToInfInt(shifting); //convert the binary representation to infint and return it.

}

/*
 * left shifting operator overloading.
 * for each bit shifting to left , we add zero from right.
 */
InfInt InfInt::operator<<(int n) const {
    if (n == 0) //<<0 not change the num.
        return *this;
    if (n < 0) //we define shifting for param >=0
        throw ("shifting must be with positive value");

    string binary = this->toBinary(); //get binary representation
    string shifting = binary; //result

    for (int i = 0; i < n; i++) { //add zeroes from right for each one bit shifting.
        shifting += '0';
    }
    return FromBinaryToInfInt(shifting); //convert the result to infint and return it.

}

/*
 * >>= operator overloading , using >> that defined above.
 */
InfInt &InfInt::operator>>=(int n) {
    *this =*this >> n;
    return *this;
}
