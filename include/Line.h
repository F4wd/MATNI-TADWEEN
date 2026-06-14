#ifndef LINE_H
#define LINE_H
class Line
{
private:
    char* text;
    int length;
    int capacity;

public:
    Line();
    Line(const char* str);
    Line(const Line& other);
    ~Line();
    Line& operator=(const Line& other);
    int getLength() const;
    const char* getText() const;
    char getCharAt(int index) const;
    void insertChar(int index, char c);
    void deleteChar(int index);
    void appendChar(char c);
    void appendText(const char* str);
    void clear();
    void display() const;
};

#endif 