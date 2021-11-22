/*Реализовать шаблонный контейнер двунаправленного самосортирующегося списка.
Контейнер хранить шаблонные данные и количество обращений к каждым данным. 
После каждого обращения на чтение список сортируется чтобы самые часто запрашиваемые данные были в начале списка.*/

#include <iostream>
#include <Windows.h> 
#include <fstream>
#include <list>
#include <iterator>
#include <string>

using namespace std;

template <typename S>
struct Cache
{
    S info;
    //char info;
    int count = 1;
};

template <class S>
class CasheList
{
public:
    CasheList()
    {

    }
    ~CasheList()
    {

    }
    list <Cache <S>> myList;
    //list <Cache> myList;
    int errorFileOpen(fstream& file);
    int errorInputData(fstream& file);
    int readData();
    void AddData(char ndata);
    void showList();
};


template <typename S>
void CasheList<S>::AddData(char ndata)
{
    Cache <char> data;
    bool flag = true;
    data.info = ndata;
    auto it1 = myList.begin();
    if (myList.empty())
    {
        myList.push_back(data);
    }
    else
    {
        for (auto it = myList.begin(); it != myList.end(); it++)
        {
            if (it->info == ndata)
            {
                it->count = it->count + 1;
                flag = false;
                for (it1 = myList.begin(); it1 != it; it1++)
                {
                    if (it1->count<it->count)
                    {
                        swap(*it, *it1);
                    }
                }
                
            }
        }
        if (flag)
        {
            myList.push_back(data);
        }
    }

}

template <typename S>
int CasheList<S>::readData()
{
    char fname[40];
    char ndata;
    
    cout << "Введите название файла: ";
    cin.getline(fname, 40);
    fstream file;//поток из файла
    file.open(fname, ios::in);//открытие файла
    if (errorFileOpen(file) == -1)
        return -1;
    while (!file.eof())//пока не конец файла
    {
        file >> ndata;
        if (file.eof())
        {
            break;
        }
        if (errorInputData(file) == -1)
        {
            file.close();
            return -1;
        }
        AddData(ndata);
    }
    file.close();//закрытие файла
    return 0;
}

template <typename S>
int  CasheList<S>::errorFileOpen(fstream& file)
{
    if (!file)//проверка на правильность открытия файла
    {
        cout << "\nОшибка открытия файла исходных данных";
        return -1;
    }
    else
        return 0;
}

//проверка на пустой файл
template <typename S>
int  CasheList<S>::errorInputData(fstream& file)
{
    if (file.fail())
    {
        cout << "\nОшибка данных в файле";
        return -1;
    }
    return 0;
}

template <typename S>
void CasheList<S>::showList()
{
    for (auto it = myList.begin(); it != myList.end(); it++)
    {
        cout << it->info << "  " << it->count << endl;
    }
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    CasheList <Cache <char>> cas;
    if (cas.readData() == -1)
        return -1;
    cas.showList();
}
