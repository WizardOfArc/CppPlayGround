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

std::vector<std::vector<std::string> > parse_link_list(std::string link_list_string)
{
    std::vector<std::vector<std::string> > link_list;
    std::vector<std::string> entries = AZITSV::split(link_list_string, '|');
    for (int i = 0; i < entries.size(); i++)
    {
        std::vector<std::string> row = AZITSV::split(entries[i], '\\');
        link_list.push_back(row);
    }
    return link_list;
}

std::vector<CTML::Node> band_item(std::vector<std::string> entry)
{
    std::vector<CTML::Node> item_pair;
    CTML::Node band_name("div", entry[0]);
    band_name.SetAttribute("class", "section-header");
    item_pair.push_back(band_name);

    CTML::Node band_content("div");
    band_content.SetAttribute("class", "section-content");

    CTML::Node band_logo("img");
    band_logo.SetAttribute("src", entry[1]);
    band_logo.SetAttribute("height", "100");
    band_logo.UseClosingTag(false);
    band_content.AppendChild(band_logo);

    CTML::Node band_blurb("div");
    band_blurb.AppendText(entry[3]);
    band_content.AppendChild(band_blurb);

    CTML::Node band_pic("img");
    band_pic.SetAttribute("src", entry[2]);
    band_pic.SetAttribute("height", "100");
    band_pic.UseClosingTag(false);
    band_content.AppendChild(band_pic);

    band_content.AppendChild(CTML::Node("h3", "Links"));
    std::vector<std::vector<std::string> > link_list = parse_link_list(entry[4]);
    for (int i = 0; i < link_list.size(); i++)
    {
        std::vector<std::string> row = link_list[i];
        CTML::Node link_row("div");
        link_row.SetAttribute("class", "external-site");
        CTML::Node link_anchor("a");
        link_anchor.SetAttribute("href", row[1]);
        link_anchor.SetAttribute("target", "_blank");
        CTML::Node icon_div("div");
        icon_div.SetAttribute("class", "ext-site-icon " + row[0] + "-icon");
        link_anchor.AppendChild(icon_div);
        link_anchor.AppendText(row[0]);
        link_row.AppendChild(link_anchor);
        band_content.AppendChild(link_row);
    }
    band_content.AppendChild(close_me());
    item_pair.push_back(band_content);
    return item_pair;
}

CTML::Node section_container(std::vector<std::vector<std::string> > data)
{
    CTML::Node sections("div");
    sections.SetAttribute("class", "sections");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].size() < 5)
        {
            continue;
        }
        std::vector<CTML::Node> item_pair = band_item(data[i]);
        sections.AppendChild(item_pair[0]);
        sections.AppendChild(item_pair[1]);
    }
    return sections;
}

int main()
{
    std::string bands_tsv_file("TSVs/bands.tsv");
    std::vector<std::vector<std::string> > data = AZITSV::parse_tsv_file(bands_tsv_file);
    CTML::Node container = section_container(data);
    CTML::ToStringOptions options(
        CTML::StringFormatting::SINGLE_LINE,
        true,
        0,
        false);
    std::cout << "Content-type:text/html\r\n\r\n";
    std::cout << container.ToString(options) << std::endl;
    return 0;
}
