#include <iostream>
using namespace std;

extern bool font[][5][3];
unsigned char_to_index(char);

int main() {
    char ch;
    cin >> ch;
    unsigned ci = char_to_index(ch);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            cout << (font[ci][i][j] ? 'X' : ' ');
        }
        cout << endl;
    }
}
