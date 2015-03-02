#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename TYPE, int LENGTH> class DinamicArray
{
    TYPE *Array; // ��� �������
public:
    int Len = LENGTH; // ����� �������
    DinamicArray(); //+  �������� �������
    void Append(TYPE *NewElement); //+  �������� �������� *NewElement � �����
    void WriteByIndex(int Index ,TYPE *NewElement); //+  ������ �������� (�� ���������) *NewElement � ������� Index
    void ReWriteByIndex(int Index ,TYPE *NewElement); //+  ������� �������� *NewElement � ������� Index
    TYPE *GetByIndex(int Index); //+ ���������� �������� � ������� *GetByIndex
};

int main()
{
    cout << "JIuc   \n";

    DinamicArray <int, 5> o1; // �������� �������-������� o1 �� 5 ��������� ���� int

    // ���� �� ������ ���������� �������
    for (int i = 0; i < o1.Len; i++)
        o1.ReWriteByIndex(i, &i);

    // ���� �� ������ ����� �������
    for (int i = 0; i < o1.Len; i++)
        cout << *o1.GetByIndex(i) << ' ';

    int a=5;
    o1.WriteByIndex(3, &a); // ������ ���������� a � ������� � �������� 3
    o1.Append(&a); // �������� ���������� a � ����� �������
    cout << '\n';

    //  ���� �� ����� ����������� �������
    for (int i = 0; i < o1.Len; i++)
        cout << *o1.GetByIndex(i) << ' ';

    cout << '\n' << o1.Len; // �������� ����� �������

}



//+  �������� �������
template <typename TYPE, int LENGTH> DinamicArray<TYPE, LENGTH> :: DinamicArray()
{
    Array = (TYPE*) malloc(LENGTH * sizeof(*Array));
    cout << "Massiv sozdan...  \n";
}

//+  �������� �������� *NewElement � �����
template <typename TYPE, int LENGTH> void DinamicArray<TYPE, LENGTH> :: Append(TYPE *NewElement)
{
    Len++;
    Array = (TYPE*) realloc(Array, Len * sizeof(*Array));
    Array[Len-1] = *NewElement;
}

//+  ������ �������� (�� ���������) *NewElement � ������� Index
template <typename TYPE, int LENGTH> void DinamicArray<TYPE, LENGTH> :: WriteByIndex(int Index, TYPE *NewElement)
{
    Len++;
    Array = (TYPE*) realloc(Array, Len * sizeof(*Array));
    for (int i = Len - 1; i>Index ; i--)
        Array[i] = Array[i-1];
    Array[Index] = *NewElement;
}

//+  ���������� �������� *NewElement � ������� Index
template <typename TYPE, int LENGTH> void DinamicArray<TYPE, LENGTH> :: ReWriteByIndex(int Index, TYPE *NewElement)
{
    Array[Index] = *NewElement;
}

//+ ���������� �������� � ������� *GetByIndex
template <typename TYPE, int LENGTH> TYPE* DinamicArray<TYPE, LENGTH> :: GetByIndex(int Index)
{
    return &Array[Index];
}
