#include <cmath>
#include <map>
#include <sstream>
#include "music.h"


using namespace Music;
using namespace std;

std::string Note::PC_NAMES[12] = {
    "C", "C#", "D", "Eb",
    "E", "F", "F#", "G",
    "G#", "A", "Bb", "B",
    };

std::map<std::string, char> Note::pc_map = {
    {std::string("C"), (char)0},
    {std::string("c"), (char)0},
    {std::string("C#"), (char)1},
    {std::string("cis"), (char)1},
    {std::string("Db"), (char)1},
    {std::string("des"), (char)1},
    {std::string("D"), (char)2},
    {std::string("d"), (char)2},
    {std::string("D#"), (char)3},
    {std::string("dis"), (char)3},
    {std::string("Eb"), (char)3},
    {std::string("ees"), (char)3},
    {std::string("E"), (char)4},
    {std::string("e"), (char)4},
    {std::string("F"), (char)5},
    {std::string("f"), (char)5},
    {std::string("F#"), (char)6},
    {std::string("fis"), (char)6},
    {std::string("Gb"), (char)6},
    {std::string("ges"), (char)6},
    {std::string("G"), (char)7},
    {std::string("g"), (char)7},
    {std::string("G#"), (char)8},
    {std::string("gis"), (char)8},
    {std::string("Ab"), (char)8},
    {std::string("aes"), (char)8},
    {std::string("A"), (char)9},
    {std::string("a"), (char)9},
    {std::string("Bb"), (char)10},
    {std::string("bes"), (char)10},
    {std::string("B"), (char)11},
    {std::string("b"), (char)11},
};

void Note::normalize(char &pc, float &cents, int &oct){
    if(cents > -50 && cents < 50){
        return;
    }
    if(cents <= -50){
        cents = -(100 + cents);
        if(pc == 0){
            pc = (char)11;
            oct = oct - 1;
            return;
        }
        pc = pc - (char)1;
        return;
    }
    if(cents >= 50){
        // adjust up
        cents = cents - 100;
        if(pc == 11){
            pc = (char)0;
            oct = oct + 1;
            return;
        }
        pc = pc + (char)1;
        return;
    }
}

Note Note::from_freq(double frequency)
{
    double power_of_two = log2(frequency/440);
    int whole_number_part;
    if(power_of_two > 0){
        whole_number_part = (int)(power_of_two + 0.5);
    } else {
        whole_number_part = (int)(power_of_two - 0.5);
    }
    double fraction_part = power_of_two - whole_number_part;
    int octave = whole_number_part + 4;
    double semitones = (fraction_part * 12) + 9;
    if (semitones >= 12){
        semitones -= 12;
        octave += 1;
    }
    int pc = (int)semitones;
    double cents = (semitones - pc)*100;
    if(pc < 0){
        pc = pc+12;
    }
    char pitch_class = (char)pc;
    float float_cents = (float)cents;
    Note::normalize(pitch_class, float_cents, octave);
    Note note = Note(pitch_class, float_cents, octave);
    // put in the logic to calculate pitch class, cents and octave from frequency
    return note;
}

Note Note::from_midi(int midi_note){
    int pc = midi_note % 12;
    int octave_semitones = (midi_note - pc) - 1;
    int octave = octave_semitones / 12;
    return Note::from_pitch_class_octave((char)pc, octave);
}

Note::Note(char pc, float cents, int oct){
    this->m_pitch_class = pc;
    this->m_cents = cents;
    this->m_octave = oct;
}

Note Note::from_pitch_class_octave(char pc, int oct){
    return Note(pc, 0.0, oct);
}

string Note::name_from_pitch_class(char pitch_class)
{
    if (pitch_class > 11){
        pitch_class = pitch_class % 12;
    }
    return PC_NAMES[pitch_class];
}

char Note::pitch_class_from_name(std::string name)
{
    return pc_map[name];
}

double Note::to_frequency()
{
   int normalized_octave = this->m_octave - 4;
   double full_pitch_class = (double)this->m_cents/100 + (double)this->m_pitch_class;
   double normalized_pitch_class = full_pitch_class - 9;
   double fraction_part = normalized_pitch_class / 12;
   return 440 * pow(2, normalized_octave + fraction_part);
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