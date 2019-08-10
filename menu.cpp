#include "menu.h"
#include<iostream>
#include "GKX.h"

using namespace std;

menu::menu()
{

}

void menu::start()
{
    setlocale(LC_ALL, "");
    const string filename{ "text.txt" };
    info* st = NULL;
    int v;
    wcout << L"Вас приветствует программа управления платежами." << endl;
    st = st->read(filename);
    do
    {
        wcout << L"Пожалуйста,выберите команду из списка." << endl;
        wcout << L"[1]Добавить платёж." << endl;
        wcout << L"[2]Удалить платёж." << endl;
        wcout << L"[3]Вывести все платежи." << endl;
        wcout << L"[4]Вывести информацию по определенному платежу." << endl;
        wcout << L"[5]Открыть меню редактирования." << endl;
        wcout << L"[0]Выход." << endl;
        cin >> v;
        while (cin.fail())
        {
            wcout << "\nЗдесь требовалось ввести число.\nПопробуйте снова:";
            cin.clear();
            string h;
            getline(cin, h);
            cin >> v;
        }
        cin.get();
        switch (v) {
        case 0:
            st->zapic(filename);
            wcout << L"До свидания." << endl;
            break;
        case 1:
            st = st->newyzel();
            cout << endl;
            break;
        case 2:
            if (st == NULL)
            {
                wcout << L"Еще нет ни одного платежа" << endl;
                break;
            }
            st = st->deleteyzel();
            cout << endl;
            break;
        case 3:
            if (st == NULL)
            {
                wcout << L"Еще нет ни одного платежа" << endl;
                break;
            }
            st->outall();
            break;
        case 4:
            if (st == NULL)
            {
                wcout << L"Еще нет ни одного платежа" << endl;
                break;
            }
            st->out();
            break;
        case 5:
            if (st == NULL)
            {
                wcout << L"Еще нет ни одного платежа" << endl;
                break;
            }
            st->redakt();
            break;
        default:
            wcout << L"Команды под данным номером нет в списке. Попробуйте снова." << endl;
            break;
        }

    } while (v != 0);
}
