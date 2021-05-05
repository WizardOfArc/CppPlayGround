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

    Note another_note = Note((char)3, 0, 4);
    cout << "Another note: " << another_note.to_json() << endl;

    Note yet_another_note = Note::from_freq(440);
    cout << "Yet another note: " << yet_another_note.to_json() << endl;

    Note fourth_note = Note::from_freq(128);
    cout << "120 hz is: " << fourth_note.to_json() << endl;

    Note fifth_note = Note::from_freq(660);
    cout << "660 hz is: " << fifth_note.to_json() << endl;

    for(int i = 1; i < 440; i++){
        Note note = Note::from_freq(i);
        cout << i << " Hz is: " << note.to_json() << endl;
    }
    return 0;
}