#include <iostream>
using namespace std;

int main(){
    string brainrot = "Bombombini gusini";
    string meme = "tung tung tung sahur";
    string plus = brainrot + meme;
    string space = meme + " " + brainrot;
    string apppend = brainrot.append(meme);
    cout << "The length of the txt string is: " << meme.length();//same as 'len' in python
    // you can use 'length' or 'size'

    cout << meme[0];
    cout << meme.at(0);
    brainrot[0] = 'b';

    //getline() to real a line of text
    string fullName;
    cout << "Type your full name: ";
    getline (cin, fullName);
    cout << "Your name is: " << fullName;
    //output
    // Type your full name: John Doe
    // Your name is: John Doe
}


