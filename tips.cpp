#include <iostream>
#include <string>
#include <vector>

#include "ctml.hpp"
#include "tsv_tools.hpp"

CTML::Node close_me()
{
    CTML::Node closeme("div", "close");
    closeme.SetAttribute("class", "close-me");
    return closeme;
}

std::vector<CTML::Node> tip_item(std::vector<std::string> entry, int index)
{
    std::vector<CTML::Node> item_pair;
    CTML::Node tip_header("div", "Tip " + std::to_string(index + 1) + ": " + entry[0]);
    tip_header.SetAttribute("class", "section-header");
    item_pair.push_back(tip_header);
    CTML::Node tip_content("div");
    tip_content.SetAttribute("class", "section-content");
    tip_content.AppendText(entry[1]);
    tip_content.AppendChild(close_me());
    item_pair.push_back(tip_content);
    return item_pair;
}

CTML::Node section_container(std::vector<std::vector<std::string> > data)
{
    CTML::Node sections("div");
    sections.SetAttribute("class", "sections");
    for (int i = 0; i < data.size(); i++)
    {
        std::vector<CTML::Node> item_pair = tip_item(data[i], i);
        sections.AppendChild(item_pair[0]);
        sections.AppendChild(item_pair[1]);
    }
    return sections;
}

int main()
{
    std::string tips_tsv_file("TSVs/tips.tsv");
    std::vector<std::vector<std::string> > data = AZITSV::parse_tsv_file(tips_tsv_file);
    CTML::Node container = section_container(data);
    CTML::ToStringOptions options(
        CTML::StringFormatting::SINGLE_LINE,
        true,
        0,
        false);
    std::cout << container.ToString(options) << std::endl;
    return 0;
}
