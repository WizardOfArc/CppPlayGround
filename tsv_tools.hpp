#ifndef AZI_TSV_HPP_
#define AZI_TSV_HPP_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace AZITSV
{
    std::vector<std::string> split(const std::string &s, char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    std::vector<std::vector<std::string> > parse_tsv_file(const std::string &filename)
    {
        std::vector<std::vector<std::string> > records;
        // read file line by line
        std::ifstream ifs;
        std::string line;
        ifs.open(filename);
        while (getline(ifs, line))
        {
            std::vector<std::string> line_parts;
            line_parts = split(line, '\t');
            records.push_back(line_parts);
        }
        ifs.close();
        return records;
    }
}
#endif