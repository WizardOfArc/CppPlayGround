#include <iostream>
#include "music.h"

using namespace std;
using namespace Music;

int main(){
    cout << "hi\n";
    cout << "Test making a note Middle C and returning Midi note\n";

    Note middle_C = Note();
    cout << "Did it pass? " << (middle_C.to_midi() == (int)60) << endl;
    return 0;
}