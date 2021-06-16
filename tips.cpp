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

CTML::Node css()
{
    CTML::Node css_link("link");
    css_link.SetAttribute("rel", "stylesheet");
    css_link.SetAttribute("type", "type/css");
    css_link.SetAttribute("href", "../html/Tips/CSS/index.css");
    return css_link;
}

CTML::Node js()
{
    CTML::Node js_script("script");
    js_script.SetAttribute("src", "../html/Tips/JS/index.js");
    return js_script;
}

CTML::Node homelink()
{
    CTML::Node home_link_anchor("a");
    home_link_anchor.SetAttribute("href", "../html/index.html");
    CTML::Node home_link_div("div");
    home_link_div.SetAttribute("class", "home-link");
    home_link_anchor.AppendChild(home_link_div);
    return home_link_anchor;
}

CTML::Node display_title(const std::string title)
{
    CTML::Node tips_title("div", title);
    tips_title.SetAttribute("class", "title-text");
    return tips_title;
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
    CTML::Document doc;
    doc.AppendNodeToHead(CTML::Node("title", "Tips"));
    doc.AppendNodeToHead(css());

    doc.AppendNodeToBody(display_title("Musical Tips"));
    doc.AppendNodeToBody(section_container(data));
    doc.AppendNodeToBody(homelink());
    doc.AppendNodeToBody(js());

    std::cout << "Content-type:text/html\r\n\r\n";
    // StringFormatting::SINGLE_LINE
    // bool trailingNewLine=false,
    // uint32_t indentLevel=0,
    // bool escapeContent=true)
    CTML::ToStringOptions options(
        CTML::StringFormatting::SINGLE_LINE,
        true,
        0,
        false);
    std::cout << doc.ToString(options) << std::endl;
    return 0;
}