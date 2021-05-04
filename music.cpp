#include "music.h"

using namespace Music;

Note Note::from_freq(float frequency)
{
    Note note = Note();
    // put in the logic to calculate pitch class, cents and octave from frequency
    char pitch_class = 0; // frequency to pitch class
    float cents = 0.0; // frequency to cents
    int octave = 4; // frequency to octave
    return note;
}

int Note::to_midi()
{
    return (this->m_octave + 1) * 12 + this->m_pitch_class;
}