/*Написать программу для работы с контейнером map.
Программа получает на вход строку которая состоит из строк, разделенных пробелом. 
Необходимо подсчитать количество раз которое встречается каждое из строк в входной строке.
*/

#include <iostream>
#include <map>
#include <Windows.h>
#include <fstream>

using namespace std;

int errorFileOpen(fstream& file);
int errorInputData(fstream& file);
void showMap(map <string, int> data);

int readData()
{
    char fname[40];
    string ndata;
    map <string, int> data;
    map <string, int> ::iterator it;
    cout << "Введите название файла: ";
    cin.getline(fname, 40);
    fstream file;//поток из файла
    file.open(fname, ios::in);//открытие файла
    if (errorFileOpen(file) == -1)
        return -1;
    while (!file.eof())//пока не конец файла
    {
        file >> ndata;
        if (errorInputData(file) == -1)
        {
            file.close();
            return -1;
        }
        it = data.find(ndata);
        if (it == data.end())//если ключа с таким значением нет
        {
            data.insert(make_pair(ndata, 1));
        }
        else
        {
            it->second++;
        }
        //cout << ndata<<endl;
    }
    file.close();//закрытие файла
    showMap(data);
    return 0;
}


void showMap(map <string, int> data)
{
    map <string, int> ::iterator it = data.begin();
    for (int i = 0; it != data.end(); it++, i++)
    {
        cout << "Строка: " << it->first << " встречается " << it->second << " раз" << endl;
    }

}

int errorFileOpen(fstream& file)
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
int errorInputData(fstream& file)
{
    if (file.fail())
    {
        cout << "\nОшибка данных в файле";
        return -1;
    }
    return 0;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    if (readData() == -1)
        return -1;
}

