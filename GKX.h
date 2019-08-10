#ifndef INFO_H
#define INFO_H
#include<iostream>
#include<string>

using namespace std;

class info
{
private:
    string title;
    int price;
    int day, month, year;
    string status;

    info* search(const string& b);
    void zapichelp(ofstream& a, string& b);
    void readhelp(ifstream& a, string& b);
    friend ostream& operator<<(ostream& out, const info& a);
    info* next;
    info* prev;

public:
    info* newyzel();
    info* deleteyzel();
    void out();
    void redakt();
    void outall();
    int zapic(const string& namefile);
    info* read(const string& namefile);
};
#endif
