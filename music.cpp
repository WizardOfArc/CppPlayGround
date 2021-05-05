#include <cmath>
#include <map>
#include <sstream>
#include "music.h"


using namespace Music;
using namespace std;

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
    int whole_number_part = (int)power_of_two;
    double fraction_part = power_of_two - whole_number_part;
    int octave = whole_number_part + 4;
    double semitones = (fraction_part * 12) + 9;
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
    string pc_names[12] = {
        "C", "C#", "D", "Eb",
        "E", "F", "F#", "G",
        "G#", "A", "Bb", "B"
    };
    if (pitch_class > 11){
        pitch_class = pitch_class % 12;
    }

    return pc_names[pitch_class];
}

char Note::pitch_class_from_name(std::string name)
{
    if(!pc_map_initialized){
        pc_map["C"] = (char)0;
        pc_map["C#"] = (char)1;
        pc_map["Db"] = (char)1;
        pc_map["D"] = (char)2;
        pc_map["D#"] = (char)3;
        pc_map["Eb"] = (char)3;
        pc_map["E"] = (char)4;
        pc_map["F"] = (char)5;
        pc_map["F#"] = (char)6;
        pc_map["Gb"] = (char)6;
        pc_map["G"] = (char)7;
        pc_map["G#"] = (char)8;
        pc_map["Ab"] = (char)8;
        pc_map["A"] = (char)9;
        pc_map["Bb"] = (char)10;
        pc_map["B"] = (char)11;
        pc_map_initialized = true;
    }

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