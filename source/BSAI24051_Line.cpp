#include <iostream>
#include "Line.h"

int stringLength(const char* text) {
    int _size = 0;
    while (text[_size] != '\0')
    {
        _size++;
    }
    return _size;
}

void stringCopy(char* dest, const char* src, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        dest[i] = src[i];
    }
    dest[size] = '\0';
}

Line::Line() : text(nullptr), length(0), capacity(0) {
    capacity = 10;
    text = new char[capacity];
    text[0] = '\0';
}

Line::Line(const char* str) : text(nullptr), length(0), capacity(0) {
    if (str) {
        length = stringLength(str);
        capacity = length + 10;
        text = new char[capacity];
        stringCopy(text, str, length);
    }
    else {
        capacity = 10;
        text = new char[capacity];
        text[0] = '\0';
    }
}

Line::Line(const Line& other) : text(nullptr), length(other.length), capacity(other.capacity) {
    text = new char[capacity];
    stringCopy(text, other.text, length);
}

Line::~Line() {
    delete[] text;
}

Line& Line::operator=(const Line& other) {
    if (this != &other) {
        delete[] text;
        length = other.length;
        capacity = other.capacity;
        text = new char[capacity];
        stringCopy(text, other.text, length);
    }
    return *this;
}

int Line::getLength() const {
    return length;
}

const char* Line::getText() const {
    return text;
}

char Line::getCharAt(int index) const {
    if (index >= 0 && index < length) {
        return text[index];
    }
    return '\0';
}

void Line::insertChar(int index, char c) {
    if (index < 0 || index > length) {
        return;
    }

    if (length + 1 >= capacity) {
        capacity *= 2;
        char* newText = new char[capacity];
        stringCopy(newText, text, length);
        delete[] text;
        text = newText;
    }

    for (int i = length; i > index; i--) {
        text[i] = text[i - 1];
    }
    text[index] = c;
    length++;
    text[length] = '\0';
}

void Line::deleteChar(int index)
{
    if (index < 0 || index >= length) 
    {
        return;
    }

    for (int i = index; i < length - 1; i++) 
    {
        text[i] = text[i + 1];
    }
    length--;
    text[length] = '\0';
}

void Line::appendChar(char c)
 {
    insertChar(length, c);
}

void Line::appendText(const char* str) {
    if (!str) return;

    int strLen = stringLength(str);
    if (length + strLen >= capacity) {
        capacity = length + strLen + 10;
        char* newText = new char[capacity];
        stringCopy(newText, text, length);
        delete[] text;
        text = newText;
    }

    for (int i = 0; i < strLen; i++) {
        text[length + i] = str[i];
    }

    length += strLen;
    text[length] = '\0';
}

void Line::clear() {
    length = 0;
    text[0] = '\0';
}

void Line::display() const {
    std::cout << text;
}