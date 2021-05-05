#ifndef _MUSIC_H
#define _MUSIC_H
#include <map>
#include <string>

namespace Music
{

    static bool pc_map_initialized;
    static std::map<std::string, char> pc_map;
    static const std::string PC_NAMES[12] = {
        "C", "C#", "D", "Eb",
        "E", "F", "F#", "G",
        "G#", "A", "Bb", "B"
    };

    class Note
    {
    public:
        Note() {
            this->m_pitch_class = 0;
            this->m_octave = 4;
            this->m_cents = 0.0;
        }
        Note(char pc, float cents, int oct);
        static Note from_freq(double frequency);
        static Note from_midi(int midi_note);
        static Note from_pitch_class_octave(char pitch_class, int octave);
        static std::string name_from_pitch_class(char pitch_class);
        static char pitch_class_from_name(std::string name);
        static void normalize(char &pc, float &cents, int &oct);

        char get_pitch_class();
        int get_octave();
        float get_cents();
        int to_midi();
        double to_frequency();
        std::string to_json();

    private:
        char m_pitch_class;
        float m_cents;
        int m_octave;
    };
}

#endif