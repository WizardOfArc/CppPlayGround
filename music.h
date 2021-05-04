#ifndef _MUSIC_H
#define _MUSIC_H

namespace Music
{
    class Note
    {
    public:
        Note() {
            this->m_pitch_class = 0;
            this->m_octave = 4;
            this->m_cents = 0.0;
        }
        static Note from_freq(float frequency);
        static Note from_midi(int midi_note);
        static Note from_pitch_class_octave(char pitch_class, int octave);
        int to_midi();
        float to_frequency();
    private:
        char m_pitch_class;
        float m_cents;
        int m_octave;
    };
}

#endif