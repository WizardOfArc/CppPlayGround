#include <cmath>
#include <sstream>
#include "music.h"


using namespace Music;
using namespace std;

Note Note::from_freq(float frequency)
{
    Note note = Note();
    // put in the logic to calculate pitch class, cents and octave from frequency
    char pitch_class = 0; // frequency to pitch class
    float cents = 0.0; // frequency to cents
    int octave = 4; // frequency to octave
    return note;
}

string Note::name_from_pitch_class(char pitch_class)
{
    string pc_names[12] = {
        "C", "C#", "D", "Eb",
        "E", "F", "F#", "G",
        "G#", "A", "Bb", "B"
    };

    if(pitch_class < 0 || pitch_class > 11){
        return NULL;
    }

    return pc_names[pitch_class];
}

char pitch_class_from_name(std::string name)
{
    // can I use a switch on a string?
    return 'A';
}

double Note::to_frequency()
{
   return 440 * pow(2, this->m_octave - 4) * pow(2, ((double)this->m_pitch_class - 9)/12);
}

int Note::to_midi()
{
    return (this->m_octave + 1) * 12 + this->m_pitch_class;
}

string Note::to_json()
{
    string lbrace = "{";
    string rbrace = "}";
    string dquote = "\"";
    string colon = ":";
    string comma = ",";

    ostringstream json;
    json << lbrace;

    json << dquote << "note" << dquote;
    json << colon;
    json << dquote << Note::name_from_pitch_class(this->m_pitch_class) << dquote;
    json << comma;

    json << dquote << "octave" << dquote;
    json << colon;
    json << this->m_octave;
    json << comma;

    json << dquote << "cents" << dquote;
    json << colon;
    json << this->m_cents;
    json << comma;

    json << dquote << "frequency" << dquote;
    json << colon;
    json << this->to_frequency();
    json << comma;

    json << dquote << "midi" << dquote;
    json << colon;
    json << this->to_midi();

    json << rbrace;
    return json.str();
}