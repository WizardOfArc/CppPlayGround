#include <iostream>
#include <fstream>
#include <string>

#include "ctml.hpp"

CTML::Node make_wee_entry(int number)
{
    CTML::Node entry("div", "Number(" + std::to_string(number + 1) + ")");
    entry.SetAttribute("class", "wee-entry");
    entry.SetAttribute("id", "entry-" + std::to_string(number));
    return entry;
}

int main()
{
    CTML::Document doc;
    doc.AppendNodeToHead(CTML::Node("title", "Made From Cpp"));
    CTML::Node css_link("link");
    css_link.SetAttribute("rel", "stylesheet");
    css_link.SetAttribute("type", "type/css");
    css_link.SetAttribute("href", "CSS/index.css");
    doc.AppendNodeToHead(css_link);
    doc.AppendNodeToBody(CTML::Node("h1", "Is this the Future?"));
    CTML::Node all_container("div");
    all_container.SetAttribute("id", "all-container");
    for (int i = 0; i < 20; i++)
    {
        all_container.AppendChild(make_wee_entry(i));
    }
    doc.AppendNodeToBody(all_container);
    std::cout << "Content-type:text/html\r\n\r\n";
    std::cout << doc.ToString() << std::endl;
    // is this ^ enough for rendering html as a reponse to a GET?

    // for writing out to a file
    // std::ofstream out_file;
    // out_file.open("html_test.html");
    // out_file << doc.ToString();
    // out_file.close();
}
