#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "music.h"

using namespace std;
using namespace Music;

vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main () {
   vector<string> q_params = split(getenv("QUERY_STRING"), '&');

   string query_type;
   string query_value;
   string json;
   Note note;
   bool valid = false;

   if(q_params.size() == 1){
      vector<string> kvpair = split(q_params[0], '=');
      query_type = kvpair[0];
      query_value = kvpair[1];
      if(query_type == "midi"){
          int midi = std::stoi(query_value);
          note = Note::from_midi(midi);
          valid = true;
      } else if(query_type == "frequency"){
          double frequency = std::stod(query_value);
          note = Note::from_freq(frequency);
          valid = true;
      } else if(query_type == "note"){
          // expecting NAME_OCTAVE
          vector<string> note_parts = split(query_value, '_');
          int octave = std::stoi(note_parts[1]);
          string name = note_parts[0];
          char pc = Note::pitch_class_from_name(name);
          note = Note::from_pitch_class_octave(pc, octave);
          valid = true;
      }
   }
   if (valid){
     json = note.to_json();
   } else {
     json = "{}";
   }

   std::cout << "Content-type:application/json\r\n\r\n";
   std::cout << json;
   return 0;
}
