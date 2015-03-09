#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename TYPE, int LENGTH> class DinamicArray
{
    TYPE *Array; // Тип массива
public:
    int Len = LENGTH; // Длина массива
    DinamicArray(); //+  Создание массива
    void Append(TYPE *NewElement); //+  Дозапись элемента *NewElement в конец
    void WriteByIndex(int Index ,TYPE *NewElement); //+  Запись элемента (со смещением) *NewElement в позицию Index
    void ReWriteByIndex(int Index ,TYPE *NewElement); //+  Доапись элемента *NewElement в позицию Index
    TYPE *GetByIndex(int Index); //+ Считывание элемента с позиции *GetByIndex
};

int main()
{
    cout << "JIuc   \n";

    DinamicArray <int, 5> o1; // Создание объекта-массива o1 на 5 элементов типа int

    // Цикл на полное заполнение массива
    for (int i = 0; i < o1.Len; i++)
        o1.ReWriteByIndex(i, &i);

    // Цикл на вываод всего массива
    for (int i = 0; i < o1.Len; i++)
        cout << *o1.GetByIndex(i) << ' ';

    int a=5;
    o1.WriteByIndex(3, &a); // Запись переменной a в элемент с индексом 3
    o1.Append(&a); // Дозапись переменной a в конец массива
    cout << '\n';

    //  Цикл на вывод измененного массива
    for (int i = 0; i < o1.Len; i++)
        cout << *o1.GetByIndex(i) << ' ';

    cout << '\n' << o1.Len; // проверка длины массива

}



//+  Создание массива
template <typename TYPE, int LENGTH> DinamicArray<TYPE, LENGTH> :: DinamicArray()
{
    Array = (TYPE*) malloc(LENGTH * sizeof(*Array));
    cout << "Massiv sozdan...  \n";
}

//+  Дозапись элемента *NewElement в конец
template <typename TYPE, int LENGTH> void DinamicArray<TYPE, LENGTH> :: Append(TYPE *NewElement)
{
    Len++;
    Array = (TYPE*) realloc(Array, Len * sizeof(*Array));
    Array[Len-1] = *NewElement;
}

//+  Запись элемента (со смещением) *NewElement в позицию Index
template <typename TYPE, int LENGTH> void DinamicArray<TYPE, LENGTH> :: WriteByIndex(int Index, TYPE *NewElement)
{
    Len++;
    Array = (TYPE*) realloc(Array, Len * sizeof(*Array));
    for (int i = Len - 1; i>Index ; i--)
        Array[i] = Array[i-1];
    Array[Index] = *NewElement;
}

//+  Перезапись элемента *NewElement в позицию Index
template <typename TYPE, int LENGTH> void DinamicArray<TYPE, LENGTH> :: ReWriteByIndex(int Index, TYPE *NewElement)
{
    Array[Index] = *NewElement;
}

//+ Считывание элемента с позиции *GetByIndex
template <typename TYPE, int LENGTH> TYPE* DinamicArray<TYPE, LENGTH> :: GetByIndex(int Index)
{
    return &Array[Index];
}
