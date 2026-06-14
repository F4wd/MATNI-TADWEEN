#include <iostream>
#include "Paragraph.h"
using namespace std;


Paragraph::Paragraph() 
{

}
Paragraph::Paragraph(const char* text) 
{
    if (text) {
        const char* start = text;
        const char* current = text;

        while (*current != '\0') {
            if (*current == '\n') {
                int len = current - start;
                char* lineText = new char[len + 1];
                for (int i = 0; i < len; i++) {
                    lineText[i] = start[i];
                }
                lineText[len] = '\0';
                addLine(lineText);
                delete[] lineText;
                start = current + 1;
            }
            current++;
        }

        if (current > start) {
            int len = current - start;
            char* lineText = new char[len + 1];
            for (int i = 0; i < len; i++) {
                lineText[i] = start[i];
            }
            lineText[len] = '\0';
            addLine(lineText);
            delete[] lineText;
        }
    }
}
Paragraph::Paragraph(const Paragraph& other) : lines(other.lines) 
{

}
Paragraph::~Paragraph() 
{

}
Paragraph& Paragraph::operator=(const Paragraph& other) 
{
    if (this != &other) 
    {
        lines = other.lines;
    }
    return *this;
}
int Paragraph::getLineCount() const
{
    return lines.size();
}
Line& Paragraph::getLine(int index)
{
    if (index >= 0 && index < lines.size()) 
    {
        return lines[index];
    }
    return lines[0];
}
const Line& Paragraph::getLine(int index) const 
{
    if (index >= 0 && index < lines.size()) 
    {
        return lines[index];
    }
    return lines[0];
}
void Paragraph::addLine(const Line& line)
{
    lines.push_back(line);
}
void Paragraph::addLine(const char* text)
{
    Line newLine(text);
    lines.push_back(newLine);
}
void Paragraph::insertLine(int index, const Line& line)
{
    if (index < 0 || index > lines.size())
    {
        return;
    }
    lines.insert(lines.begin() + index, line);
}
void Paragraph::insertLine(int index, const char* text) 
{
    Line newLine(text);
    insertLine(index, newLine);
}
void Paragraph::deleteLine(int index) 
{
    if (index < 0 || index >= lines.size())
    {
        return;
    }
    lines.erase(lines.begin() + index);
}
void Paragraph::clear() 
{
    lines.clear();
}
void Paragraph::display() const
{
    for (auto i = 0; i < lines.size(); i++) 
    {
        lines[i].display();
        cout << endl;
    }
}
