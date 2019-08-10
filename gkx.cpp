#include "GKX.h"
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>

using namespace std;

info* info::newyzel()
{
    info* a;
    a = new info;
    wcout << L"Введите название платежа: ";
    getline(cin, a->title);
    if ((a->title).size() == 0)
    {
        wcout << L"Название платежа не может быть пустым." << endl;
        delete a;
        return this;
    }
    else if (this->search(a->title) != NULL)
    {
        wcout << L"Платёж с данным названием уже существует." << endl;
        delete a;
        return this;
    }
    wcout << L"Введите день оплаты платежа: ";
    cin >> a->day;
    wcout << L"Введите месяц оплаты платежа: ";
    cin >> a->month;
    wcout << L"Введите год оплаты платежа: ";
    cin >> a->year;
    getline(cin, a->status);
    while (cin.fail())
    {
        wcout << L"\nЗдесь требовалось ввести число.\nПопробуйте ввести дату выплаты снова:";
        cin.clear();
        string h;
        getline(cin, h);
        cin >> a->day;
        cin >> a->month;
        cin >> a->year;
    }
    a->prev = this;
    a->next = NULL;
    if (this != NULL)next = a;
    return a;
}

info* info::search(const string & b)
{
    info* a;
    for (a = this; a != NULL; a = a->prev)
        if (a->title == b)break;
    return a;

}

ostream & operator<<(ostream & out, const info & a)
{
    wcout << L"Название платежа:";
    out << a.title << endl;
    wcout << L"День выплаты: ";
    out << a.day << endl;
    wcout << L"Меяц выплаты: ";
    out << a.month << endl;
    wcout << L"Год выплаты: ";
    out << a.year << endl;
    wcout << L"Статус выплаты: ";
    out << a.status << endl;

    return out;
}

info* info::deleteyzel()
{
    string a;
    info* b;
    wcout << L"Введите название платежа который вы хотите удалить:";
    getline(cin, a);
    if (a.size() == 0)
    {
        wcout << L"Название платежа не может быть пустое." << endl;
        return this;
    }
    else if ((b = this->search(a)) == NULL)
    {
        wcout << L"Платежа с данным названием не существует" << endl;
        return this;
    }
    else
    {
        if (b->next != NULL)(b->next)->prev = b->prev;
        if (b->prev != NULL)(b->prev)->next = b->next;
        if (b != this)
        {
            delete b;
            wcout << L"Платёж успешно удален." << endl;
            return this;
        }
        else if (b->next == NULL && b->prev == NULL)
        {
            delete b;
            wcout << L"Платёж успешно удален." << endl;
            return NULL;
        }
        else
        {
            info* c = b->prev;
            delete b;
            wcout << L"Платёж успешно удален." << endl;
            return c;
        }
    }
}

void info::out()
{
    string a;
    info* b;
    wcout << L"Введите название платежа:";
    getline(cin, a);
    if ((b = this->search(a)) == NULL)
        wcout << L"Платежа с данным названием не существует" << endl;
    else cout << *b << endl;
}

void info::redakt()
{
    string a;
    info* b;
    wcout << L"Введите название платежа который вы хотите отредактировать:";
    getline(cin, a);
    if (a.size() == 0)
        wcout << L"Название платежа не может быть пустым." << endl;
    else if ((b = this->search(a)) == NULL)
        wcout << L"Платёж с данным названием не существует." << endl;
    else
    {
        int v;
        do {
           wcout << L"Выберете ,что нужно отредактировать:" << endl << \
                L"[1]Редатировать название." << endl << \
                L"[2]Редактировать день." << endl << \
                L"[3]Редактировать месяц." << endl << \
                L"[4]Редактировать год." << endl << \
                L"[5]Редактировать статус выплаты." << endl << \
                L"[0]Выход из режима редактирования." << endl;
            cin >> v;
            while (cin.fail())
            {
                wcout << L"\nЗдесь требовалось ввести число.\nПопробуйте снова:";
                cin.clear();
                string h;
                getline(cin, h);
                cin >> v;
            }
            cin.get();
            switch (v) {
            case 0:
                cout << endl;
                break;
            case 1:
                wcout << L"Введите новое название платежа :";
                getline(cin, b->title);
                break;
            case 2:
                wcout << L"Введите новый день выплаты: ";
                cin >> b->day;
                break;
            case 3:
                wcout << L"Введите новый месяц выплаты: ";
                cin >> b->month;
                break;
            case 4:
                wcout << L"Введите новый год выплаты: ";
                cin >> b->year;
                break;
            case 5:
                wcout << L"Введите новый статус платежа: ";
                getline(cin, b->status);
                break;
            default:
                wcout << L"Команды под даннм номером нет в списке.Выберите команду из списка." << endl;
                break;
            }
        } while (v != 0);
    }
}

int info::zapic(const string & namefile)
{
    ofstream zap;
    zap.open(namefile, ios_base::out | ios_base::binary);
    if (!zap.is_open())
    {
        wcout << L"Не удалось открыть файл для записи." << endl;
        return 1;
    }
    info* help = this;
    while (1)
    {
        zapichelp(zap, help->title);
        zap.write((char*)& day, sizeof(int));
        zap.write((char*)& month, sizeof(int));
        zap.write((char*)& year, sizeof(int));
        zapichelp(zap, help->status);
        if (help->prev != NULL)
        {
            help = help->prev;
            delete (help->next);
        }
        else
        {
            delete help;
            break;
        }
    }
    zap.close();
    wcout << L"Запись прошла уcпешно." << endl;
    return 0;
}

void info::zapichelp(ofstream & a, string & b)
{
    int k = b.size() + 1;
    b += '\n';
    a.write((char*)& k, sizeof(int));
    a.write((char*)(b.c_str()), k * sizeof(char));
}

info* info::read(const string & namefile)
{
    ifstream in;
    info* help = this;
    in.open(namefile, ios_base::in | ios_base::binary);
    if (!in.is_open())
    {
        wcout << L"Не удалось открыть файл для чтения." << endl;
        return NULL;
    }
    while (1)
    {
        info* a;
        a = new info;
        readhelp(in, a->title);
        if (in.eof())
        {
            delete a;
            break;
        }
        in.read((char*) & (a->day), sizeof(int));
        in.read((char*) & (a->month), sizeof(int));
        in.read((char*) & (a->year), sizeof(int));
        readhelp(in, a->status);
        a->prev = NULL;
        a->next = help;
        if (help != NULL)help->prev = a;
        help = a;
    }
    while (help->next != NULL)help = help->next;
    cout << "Файл успешно загружен и прочитан." << endl;
    in.close();
    return help;
}

void info::readhelp(ifstream & a, string & b)
{
    char buffer[50];
    int k;
    a.read((char*)& k, sizeof(int));
    a.read((char*)& buffer, k * sizeof(char));
    strcpy_s(buffer + k - 1, 50, "\0");
    b = buffer;
}

void info::outall()
{
    info* help = this;
    while ((help->prev) != NULL)help = help->prev;
    for (help; help != NULL; help = help->next)
        cout << *help << endl;
}
