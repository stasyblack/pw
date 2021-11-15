/*Написать программу для работы с контейнером vector.
Программа получает на вход количество элементов для двух векторов, разделенные пробелом. 
Вектора заполняются случайными элементами от -100 до 100 в соответствии с заданным размером. 
Необходимо вывести содержимое векторов, найти среднее арифметическое элементов каждого из  векторов и пересекающиеся элементы.*/


#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;
const int vmin = -100;
const int vmax = 200;

vector <int> inputVector(vector <int> vec)
{
    int n = vec.size();
    for (int i = 0; i < n; i++)
    {
        vec.at(i) = vmin + rand() % vmax; 
    }
    return vec;
}

void showVector(vector <int> vec)
{
    int n = vec.size();
    for (int i = 0; i < n; i++)
    {
        cout << vec.at(i) << " ";
    }
    cout << endl;
}

double averageVector(vector <int> vec)//нахождение среднего арифметического вектора
{
    int n = vec.size();
    double sr_sum = 0;
    for (int i = 0; i < n; i++)
    {
        sr_sum = sr_sum + vec.at(i);
    }
    sr_sum = sr_sum / n;
    return sr_sum;
}

void compareVector(vector <int> vec1, vector <int> vec2)//поиск общих элементов
{
    int n1 = vec1.size();
    int n2 = vec2.size();
    vector <int> vec;
    for (int i=0;i<n1;i++)
        for (int j = 0; j < n2; j++)
        {
            if (vec1[i] == vec2[j])
            {
                vec.push_back(vec1[i]);
            }
        }
    if (vec.empty())
    {
        cout << "Общих элементов нет";
    }
    else
    {
        cout << "Общие элементы: ";
        showVector(vec);
    }
}

int testInput(int n)
{
    if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
    {
        cin.clear(); // то возвращаем cin в 'обычный' режим работы
        cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
        cout << "Ошибка: могу быть введены только цифры." << endl;
        return -1;
    }
    if (n <= 0)
    {
        cout << "Ошибка: размерностью вектора может быть только положительное число";
        return -1;
    }
    return 0;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n1, n2;
    cout << "Введите количество элементов в первом векторе: ";
    cin >> n1;
    if (testInput(n1) == -1)
        return -1;
    cout << "Введите количество элементов во втором векторе: ";
    cin >> n2;
    if (testInput(n2) == -1)
        return -1;
    vector <int> vector1(n1);
    vector <int> vector2(n2);
    vector1=inputVector(vector1);
    vector2=inputVector(vector2);
    showVector(vector1);
    showVector(vector2);
    cout << "Среднее арифметическое первого вектора: " << averageVector(vector1) << endl;
    cout << "Среднее арифметическое второго вектора: " << averageVector(vector2) << endl;
    compareVector(vector1, vector2);
}
