#  Infinity Integer class - C++ 

***

InfInt is a class for an integer number , positive or negative Which is not limited in his size <br>
with operators overloading for : +, -, *, /, %, ^, &, |, ~, <, >, <=, >=, ==, +=, >>=, &= , << , >> , ++ , -- <br>


## Usage example :

```c++
int main() {
    InfInt i = "1234123561269128075127893561293785612897356120893189627305";
    InfInt j = "-235182305981623978569187236509123758039467349056546";
    InfInt k = "2025129382315023402340012391284141824912120312304129429";
    cout << "i: " << i << endl << "j: " << j << endl;

    cout <<i<<endl;
    cout << j <<endl;
    cout << i+j <<endl;
    cout << i*j <<endl;
    cout << i<<10 <<endl;
    cout << (i==j) << endl;
    cout << (k%2) << endl;
    j--;
    i++;
    cout << i <<endl;
    cout << j << endl;

    return 0;
}
```
<br>
output : 

```
i: 1234123561269128075127893561293785612897356120893189627305
j: -235182305981623978569187236509123758039467349056546
1234123561269128075127893561293785612897356120893189627305
-235182305981623978569187236509123758039467349056546
1234123326086822093503914992106549103773598081425840570759
-290244025005527546307766786587830305625266003947932045519305019486599788645363355107612618146052665110588530
123412356126912807512789356129378561289735612089318962730510
0
1
1234123561269128075127893561293785612897356120893189627306
-235182305981623978569187236509123758039467349056547
```