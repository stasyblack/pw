/*Построить матрицу достижимости для графа.
На вход подаётся N - количество вершин графа.
После этого на вход подаются связи для каждой вершины. 0 означает отсутствие связей.
Рекомендуется считать связи и построить по ним таблицу связей.
С помощью алгоритма обхода в ширину или в глубину от каждой вершины построить матрицу достижимости для графа.
*/

#include <iostream>
#include <Windows.h>
#include <stack>
#include <fstream>

using namespace std;

int errorFileOpen(fstream& file);
int errorInputData(fstream& file);

int readData()
{
    char fname[40];
    int ndata,n;
    stack <int> myStack;
    cout << "Введите название файла: ";
    cin.getline(fname, 40);
   
    fstream file;//поток из файла
    file.open(fname, ios::in);//открытие файла
    if (errorFileOpen(file) == -1)
        return -1;
    file >> n; 
    int **mas = new int*[n];
    for (int i = 0; i < n; i++)
    {
        mas[i] = new int[n];
    }
    //while (!file.eof())//пока не конец файла
    for (int i = 0; i < n; i++)
    {
        
        //while (file.peek() != '\n')
        for (int j = 0; j < n; j++)
        {
            file >> mas[i][j];
            if (errorInputData(file) == -1)
            {
                file.close();
                return -1;
            }
        }
        //cout << "\nНовая сторка";
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mas[i][j]<<" ";
        }
        cout << endl;
    }
    file.close();//закрытие файла
    int* ver = new int[n];
    cout << endl;

    int** arr = new int* [n];
    for (int i = 0; i < n; i++)
        arr[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j]=0;

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
            ver[i] = 0;
        myStack.push(k);
        int node;
        while (!myStack.empty())
        {
            node = myStack.top();
            myStack.pop();
            if (ver[node] == 2)
                continue;
            ver[node] = 2;
            for (int j = n - 1; j >= 0; j--)
            {
                if ((mas[node][j] == 1) && (ver[j] != 2))
                {
                    myStack.push(j);
                    ver[j] = 1;
                }
            }
            //cout << node + 1<<" ";
            arr[k][node] = 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
        delete mas[i];
    delete[] mas;
    for (int i = 0; i < n; i++)
        delete arr[i];
    delete[] arr;
    return 0;
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