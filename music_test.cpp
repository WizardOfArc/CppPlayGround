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

    cout << "\n<====================================================>\n";
    cout << "Validating PC names and mapping:\n";
    cout << "<====================================================>\n";
    for (char pc = (char)0; pc < 12; pc += (char)1){
        string name = Note::name_from_pitch_class(pc);
        cout << "Does " << (int)pc << "(" << name << ") equal " << (int)Note::pitch_class_from_name(name) << "?\n";
    }

    cout << "\n<====================================================>\n";
    cout << "Notes from chromatic scale:\n";
    cout << "<====================================================>\n";
    for(int octave = -2; octave < 8; octave++){
        for(char pc = (char)0; pc < 12; pc += (char)1){
            Note pc_note = Note::from_pitch_class_octave(pc, octave);
            cout << Note::name_from_pitch_class(pc) << "_" << octave << " is: " << pc_note.to_json() << endl;
        }
    }

    cout << "\n<====================================================>\n";
    cout << "Notes from midi:\n";
    cout << "<====================================================>\n";
    for(int i = 0; i < 128; i++){
        Note note = Note::from_midi(i);
        cout << "Midi note " << i << " is: " << note.to_json() << endl;
    }

    cout << "\n<====================================================>\n";
    cout << "Notes from frequencies:\n";
    cout << "<====================================================>\n";
    for(int i = 1; i < 880; i++){
        Note note = Note::from_freq(i);
        cout << i << " Hz is: " << note.to_json() << endl;
    }
    return 0;
}