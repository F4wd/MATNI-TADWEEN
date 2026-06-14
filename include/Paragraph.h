#ifndef PARAGRAPH_H
#define PARAGRAPH_H
#include <vector>
#include "Line.h"

class Paragraph {
private:
    std::vector<Line> lines;

public:
    Paragraph();
    Paragraph(const char* text);
    Paragraph(const Paragraph& other);
    ~Paragraph();
    Paragraph& operator=(const Paragraph& other);
    int getLineCount() const;
    Line& getLine(int index);
    const Line& getLine(int index) const;
    void addLine(const Line& line);
    void addLine(const char* text);
    void insertLine(int index, const Line& line);
    void insertLine(int index, const char* text);
    void deleteLine(int index);
    void clear();
    void display() const;
};

#endif