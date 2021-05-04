#include <iostream>
#include "music.h"

using namespace std;
using namespace Music;

int main(){
    cout << "hi\n";
    cout << "Test making a note Middle C and returning Midi note\n";

    Note middle_C;
    cout << "Did it pass? " << (middle_C.to_midi() == (int)60) << endl;

    cout << "To json: " << middle_C.to_json() << endl;
    return 0;
}