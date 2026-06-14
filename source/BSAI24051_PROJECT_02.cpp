
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Line.h"
#include "Paragraph.h"

using namespace std;

void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

bool COMPARE_TEXT(const char* str1, const char* str2)
{
    for (int i = 0; str1[i] != '\0'; i++)
    {
        if (str1[i] != str2[i])
            return false;
    }
    return true;
}

enum Mode
{
    NORMAL,
    INSERT
};

int main()
{
    Paragraph paragraph;
    paragraph.addLine("Welcome to the Simple Text Editor!");
    paragraph.addLine("Press 'i' to enter Insert Mode.");
    paragraph.addLine("Press 'ESC' to enter Normal Mode.");
    paragraph.addLine("In Normal Mode, use 'j' and 'k' to move between lines.");
    paragraph.addLine("In Normal Mode, use 'h' and 'l' to move within a line.");

    Mode currentMode = NORMAL;
    int cr = 0, cc = 0;
    bool chalrha = true;
    Line clipboard;
    system("cls");

    gotoRowCol(0, 0);
    cout << "Mode: NORMAL" << endl;
    cout << "Commands: i=Insert, ESC=Normal,0 for first index of line, j/k=Down/Up, h/l=left/right" << endl;
    cout << "          dd=Delete line, x=Delete char, yy=Copy line, p=Paste" << endl;
    gotoRowCol(3, 0);
    paragraph.display();
    int displaycr = 3;

    while (chalrha)
    {
        if (paragraph.getLineCount() == 0)
        {
            paragraph.addLine("");
        }

        Line& currentLine = paragraph.getLine(cr);
        if (cc > currentLine.getLength())
        {
            cc = currentLine.getLength();
        }

        gotoRowCol(displaycr, 0);
        for (int i = 0; i < 20; i++)
        {
            gotoRowCol(displaycr + i, 0);
            for (int j = 0; j < 80; j++)
            {
                cout << " ";
            }
        }

        gotoRowCol(displaycr, 0);
        for (int i = 0; i < paragraph.getLineCount(); i++)
        {
            gotoRowCol(displaycr + i, 0);
            const Line& line = paragraph.getLine(i);
            if (i == cr)
            {
                for (int j = 0; j < line.getLength(); j++)
                {
                    if (j == cc && currentMode == NORMAL)
                    {
                        color(112);
                        cout << line.getCharAt(j);
                        color(4);
                    }
                    else
                    {
                        cout << line.getCharAt(j);
                    }
                }
                if (cc == line.getLength() && currentMode == NORMAL)
                {
                    color(112);
                    cout << ' ';
                    color(7);
                }
            }
            else
            {
                for (int j = 0; j < line.getLength(); j++)
                {
                    cout << line.getCharAt(j);
                }
            }
        }

        gotoRowCol(displaycr + cr, cc);
        int key = _getch();

        if (currentMode == NORMAL)
        {
            switch (key)
            {
            case 'i':
                currentMode = INSERT;
                gotoRowCol(0, 0);
                cout << "Mode: INSERT ";
                break;
            case 'h':
                if (cc > 0)
                    cc--;
                break;
            case 'l':
                if (cc < currentLine.getLength())
                    cc++;
                break;
            case 'j':
                if (cr < paragraph.getLineCount() - 1)
                {
                    cr++;
                    Line& newLine = paragraph.getLine(cr);
                    if (cc > newLine.getLength())
                    {
                        cc = newLine.getLength();
                    }
                }
                break;
            case 'k':
                if (cr > 0)
                {
                    cr--;
                    Line& newLine = paragraph.getLine(cr);
                    if (cc > newLine.getLength())
                    {
                        cc = newLine.getLength();
                    }
                }
                break;
            case '0':
                cc = 0;
                break;
            case '$':
                cc = currentLine.getLength();
                break;
            case 'x':
                if (cc < currentLine.getLength())
                {
                    currentLine.deleteChar(cc);
                }
                break;
            case 'd':
                if (_getch() == 'd') {
                    if (paragraph.getLineCount() > 1) {
                        paragraph.deleteLine(cr);
                        if (cr >= paragraph.getLineCount()) cr = paragraph.getLineCount() - 1;
                        cc = 0;
                    }
                    else {
                        currentLine.clear();
                        cc = 0;
                    }
                }
                break;
            case 'y':
                if (_getch() == 'y') clipboard = currentLine;
                break;
            case 'p':
                paragraph.insertLine(cr + 1, clipboard);
                cr++;
                break;
            case 'P':
                paragraph.insertLine(cr, clipboard);
                break;
            case 'q':
                if (_getch() == 'q')
                    chalrha = false;
                break;
            }
        }
        else if (currentMode == INSERT)
        {
            switch (key)
            {
            case 27:
                currentMode = NORMAL;
                gotoRowCol(0, 0);
                cout << "Mode: NORMAL ";
                if (cc > 0 && cc == currentLine.getLength()) cc--;
                break;
            case 13: {
                Line newLine;
                for (int i = cc; i < currentLine.getLength(); i++)
                {
                    newLine.insertChar(newLine.getLength(), currentLine.getCharAt(i));
                }
                while (cc < currentLine.getLength())
                {
                    currentLine.deleteChar(cc);
                }
                paragraph.insertLine(cr + 1, newLine);
                cr++;
                cc = 0;
            }
                   break;
            case 8:
                if (cc > 0)
                {
                    currentLine.deleteChar(cc - 1);
                    cc--;
                }
                break;
            default:
                if (key >= 32 && key <= 126)
                {
                    currentLine.insertChar(cc, key);
                    cc++;
                }
                break;
            }
        }
    }
    system("cls");
    cout << "Thank you for using Simple Text Editor!" << endl;
    return 0;
}
