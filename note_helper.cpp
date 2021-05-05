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

   cout << "Content-type:application/json\r\n\r\n";
   cout << "{";
   for(int i=0; i < q_params.size(); i++){
      if(i >0){
        cout << ",";
      }
      vector<string> kvpair = split(q_params[i], '=');
      cout << "\"" << kvpair[0] << "\":" << "\"" << kvpair[1] << "\"";
   }
   cout << "}";
   return 0;
}
