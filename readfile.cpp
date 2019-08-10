#include <iostream>
#include <fstream>

using namespace std;

void readfile (){
    setlocale(0,"rus");
    ifstream file;
    file.open("text.txt");

    if (!file.is_open())
        cout << "Ошибка открытия файла!";


    file.close();
}
