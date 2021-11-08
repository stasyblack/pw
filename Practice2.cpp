// Practice2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h> 
#include <string.h>
#include <malloc.h>
using namespace std;

const int maxData = 100;
const int minData = -100;

template <typename T>

int TInt(T);//функция для преобразования типа данных T в int
template<>
int TInt<int>(int p)
{
    return p;
}


template <class T>
class Arr
{
private:
    T* a;
    int size;
public:

    Arr(T sizemas)
    {
        size = sizemas;
        a = (int*)malloc(size * sizeof(int));//выделение памяти
        if (!a)
        {
            throw bad_alloc();
        }
    }

    Arr(Arr& obj)
    {
        a = new T[obj.size];
        if (!a)
        {
            throw bad_alloc();
        }
        size = obj.size;
        for (int i = 0; i < obj.size; i++)
        {
            a[i] = obj.a[i];
        }
    }
    ~Arr()
    {
        free(a);
    }
    void print();
    int create();
    int testData(int c);
    int testInput();
    int addElement(int n);
    void addMas(Arr& d);
    void subMas(Arr& d);
    Arr& operator =(Arr& massiv)
    {
        if (sizeof(a) >= sizeof(massiv.a))
        {
            for (int i = 0; i < size; i++)
            {
                a[i] = massiv.a[i];
            }
        }
        else
            throw bad_alloc("Выход за границы массива");
    }
    friend std::ostream& operator<<(std::ostream& out, Arr <T>& massiv) 
    {
        out << "Перегрузка оператора вывода"<<endl;
        for (int i = 0; i < massiv.size; i++)
        {
            out << massiv.a[i] << " ";
        }
        return out;
    }
    double distance(Arr& obj)
    {
        if (typeid(obj.a[0]) != typeid(int) or typeid(a[0]) != typeid(int))
        {
            throw logic_error("неверный тип данных");
        }
        double dist = 0;
        for (int i = 0; i < size; i++)
        {
            dist = (a[i] - obj.a[i]) * (a[i] - obj.a[i]) + dist;
        }
        return sqrt(dist);
    }
};

template <typename T>
int Arr <T>::create()
{
    cout << "Введите " << size << " элементов массива: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "a[" << i << "] = ";
        cin >> a[i];
            if ((testData(a[i]) == -1) ||(testInput() == -1))
            {
                //cout << "Элемент a[" << i << "] = " << a[i] << " выходить за диапазон значений" << endl;
                cout << "Oшибка ввода: выход за границы диапазона" << endl;
                throw invalid_argument("неверное значение аргумента");
            }
    }
    return 0;
}


template <typename T>
int Arr<T>::addElement(int n)
{
        if ((testData(n) == -1)||(testInput()==-1))
        {
            cout << "Элемент a[" << size << "] выходит за диапазон значений" << endl;
            throw invalid_argument("выход за границы диапазона");
        }
    size++;
    a = (int*)realloc(a, size * sizeof(int)); //выделение памяти под новый элемент массив
    a[size - 1] = n;
    return size;
}

template <typename T>
void Arr<T>::addMas(Arr& d)
{
    cout << "Сложение массивов" << endl;
    for (int i = 0; i < size; i++)
    {
        a[i] = a[i] + d.a[i];
        cout << a[i] << " ";
    }
    cout << endl;
}

template <typename T>
void Arr<T>::subMas(Arr& d)
{
    cout << "Вычитание массивов" << endl;
    for (int i = 0; i < size; i++)
    {
        a[i] = 4 * a[i] - d.a[i];
        cout << a[i] << " ";
    }
    cout << endl;
}

template <typename T>
int Arr<T>::testData(int c)
{
    if ((c > maxData) || (c < minData))
    {
        return -1;
    }
    return 0;
}

template <typename T>
int Arr<T>::testInput()
{
    if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
    {
        cin.clear(); // то возвращаем cin в 'обычный' режим работы
        cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
        return -1;
    }
    return 0;
}

template <typename T>
void Arr<T>::print()
{
    for (int i = 0; i < size; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int sizemas;
    int n;
    cout << "Введите размер массива: ";
    cin >> sizemas;
    try
    {
        if (sizemas < 0)
        {
            throw out_of_range("размер массива не может быть меньше 0");
        }
    }
    catch (out_of_range exception)
    {
        cout << "Исключение " << exception.what() << endl;
        exit(-1);
    }
    Arr <int> mas(sizemas);
    try 
    {
        mas.create();
    }
    catch (invalid_argument exception)
    {
        cout << "Исключение " << exception.what() << endl;
        exit(-1);
    }
    mas.print();
    cout << "Введите новый элемент: ";
    cin >> n;
    try
    {
        sizemas = mas.addElement(n);
    }
    catch (invalid_argument exception)
    {
        cout << "Исключение " << exception.what() << endl;
        exit(-1);
    }
    cout << "Массив с добавленным элементом" << endl;
    mas.print();
    cout << endl;
    try
    {
        Arr <int> newMas = mas;//объявление объекта newMas и копирование в него данных из mas
    }
    catch (bad_alloc exception)
    {
        cout << "Исключение " << exception.what() << endl;
        exit(-1);
    }
    Arr <int> newMas = mas;
    cout << "Скопированный массив" << endl;
    newMas.print();
    mas.addMas(newMas);
    mas.subMas(newMas);
    cout << newMas;//перегрузка <<=
    double d;
    try
    {
        d = mas.distance(newMas);
    }
    catch (logic_error exception)
    {
        cout << "Исключение " << exception.what() << endl;
        exit(-1);
    }
    d = mas.distance(newMas);
    cout << "\nРасстояние между массивами: " << d;
    return 0;
}

