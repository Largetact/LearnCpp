#include <iostream>
using namespace std;
int main(){
    int myNum = 79;               // Integer (whole number without decimals)
    double myFloatNum = 3.14;    // Floating point number (with decimals)
    char myLetter = 'K';         // Character
    string myText = "Khawpun";     // String (text)
    bool myBoolean = false;       // Boolean (true or false)
    int age = 19;
    int sum = myNum + age;
    const int e = 2.71828;
    float f1 = 35e3;
    double d1 = 12E4;

    cout << myNum << endl;
    cout << myFloatNum << endl;
    cout << myLetter << endl;
    cout << myText << endl;
    cout << myBoolean << endl;
    cout << "I am" << age << "year old.";
}