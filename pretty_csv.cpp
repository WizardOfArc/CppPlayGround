#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

string make_border(const vector<int> &padding_vector, char border_char){
    string result;
    result.append(1u, '+');
    for (int pad : padding_vector){
        result.append(pad, border_char);
        result.append(1u, '+');
    }
    return result;
}


string make_header_border(const vector<int> &padding_vector){
    return make_border(padding_vector, '=');
}

string make_regular_border(const vector<int> &padding_vector){
    return make_border(padding_vector, '-');
}


void print_file_line_by_line(string &filename){
   ifstream ifs;
   int line_num = 0;
   string line;
   ifs.open(filename);
   while( getline(ifs, line) ){
      cout << line_num << ": " << line << endl;
      line_num++;
   }
   ifs.close();
}


vector<int> get_max_col_widths(ifstream &ifs){
    vector<int> col_widths;
    ifs.seekg(0, ifs.beg);
    int line_num = 0;
    int col_count = 0;
    string line;
    while( getline(ifs, line) ){
        int curr_col_idx = 0;
        stringstream ss(line);
        string item;
        while( getline(ss, item, '\t') ){
            int col_width = item.length() + 2; // 2 for padding
            if (line_num == 0) {
                // we set up the vector with the first row
                col_widths.push_back(col_width);
                col_count++;
            } else {
                if(curr_col_idx >= col_widths.size()){
                    cout << "row" << line_num << "does not have same number of columns as header" << endl;
                    continue;
                }
                col_widths[curr_col_idx] = max(col_widths[curr_col_idx], col_width);
                curr_col_idx++;
            }
        }
        line_num++;
    }
    return col_widths;
}


string make_entry_with_padding(const string &entry, int padding){
    int spacing = padding - entry.length();
    int pre_pad = spacing / 2;
    int post_pad = spacing - pre_pad;
    string with_padding;
    with_padding.append(pre_pad, ' ');
    with_padding.append(entry);
    with_padding.append(post_pad, ' ');
    return with_padding;
}


void print_csv(ifstream &ifs, const vector<int> &col_ws){
    string header_border = make_header_border(col_ws);
    string regular_border = make_regular_border(col_ws);
    cout << header_border << endl;
    ifs.seekg(0, ifs.beg);
    int line_num = 0;
    string line;
    while( getline(ifs, line) ){
        if(line.empty()){
            continue;
        }
        int curr_col_idx = 0;
        stringstream ss(line);
        string item;
        cout << "|";
        while(getline(ss, item, '\t')){
           // per col part
           cout << make_entry_with_padding(item, col_ws[curr_col_idx]) << "|";
           curr_col_idx++;
        }
        cout << endl;
        if (line_num == 0){
            cout << header_border << endl;
        } else if(curr_col_idx){
            cout << regular_border << endl;
        }

        line_num++;
    }
}

int main(int argc, char** argv){

    // string fname = "pretty_csv.cpp";
    // print_file_line_by_line(fname);
    if (argc != 2){
        cout << "Please provide a csv file path.\n";
        return 1;
    }
    ifstream csvfs;
    string csv = string(argv[1]);
    size_t extension_pos;
    extension_pos = csv.length() - 4; // where .csv should be
    size_t found = csv.find(".tsv", extension_pos);
    if(found == string::npos){
        cout << "Please provide a csv file path.\n";
        return 1;
    }
    csvfs.open(csv);
    vector<int> col_ws = get_max_col_widths(csvfs);
    csvfs.close();
    csvfs.open(csv);
    print_csv(csvfs, col_ws);
    csvfs.close();
    return 0;
}


