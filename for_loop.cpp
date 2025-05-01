#include <iostream>
using namespace std;

int main(){
    for (int i = 0; i <= 10; i = i + 2) {
        cout << i << "\n";
    }
    return 0;

    //for-each loop same as for loop with list
    int myNumbers[5] = {10, 20, 30, 40, 50};
    for (int i : myNumbers) {
    cout << i << "\n";
    }
}