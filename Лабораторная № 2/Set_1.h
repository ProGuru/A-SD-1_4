#include <iostream>
// массив символов

using namespace std;

char Un1[] = {"0123456789ABCDEF"}; // множество - универсум

class SetLetter 
{
private: // Закрытая часть класса — данные
    static int N, cnt; // мощность универсума и счётчик множеств. (все объекты класса Set будут использовать единственную копию этих переменных)
    int n; // мощность множества
    char *A, S; // тег и память для множества. Т
public: // Открытая часть — функции для работы с множеством
    //Перегрузка оператора означает использование оператора для оперирования объектами классов. 
    SetLetter& operator&= (const SetLetter&);
    SetLetter& operator|= (const SetLetter&);
    SetLetter operator| (const SetLetter&) const; // объединение. двуместные операции в качестве аргумента (второго, потому что первый — это сам объект) имеют константную ссылку на объект типа Set
    SetLetter operator& (const SetLetter&) const; // пересечение. Функции не меняют объект, для которого вызываются, для контроля за этим в каждом из объявлений после списка параметров помещён спецификатор const.
    //Set operator~ () const; // дополнение до универсума
    SetLetter& operator= (const SetLetter&); // оператор присваивания
    SetLetter& operator= (SetLetter&&);

    void Show(); // вывод множества на экран
    int power() {return n;} // получение мощности. Применяется в конце программы, где подсчитывается ср. арифмет. мощность всех множеств

    SetLetter(char*); // конструктор множества
    SetLetter(); // ещё конструктор — по умолчанию для результата вычисления Е
    SetLetter(const SetLetter &); // конструктор копии
    SetLetter(SetLetter &&);
    
    ~SetLetter() {delete [] A;} // деструктор
};

int SetLetter::N = 16; // Мощность универсума (вариант для шестнадцатиричной системя счисления)
int SetLetter::cnt = 0; // Начальное значение счётчика множеств

// описание методов для работы операторов
SetLetter &SetLetter::operator&= (const SetLetter &B)
{ 
    SetLetter C(*this); // создаётся копия текущего объекта
    n = 0;
    for (int i = 0; i < C.n; ++i) 
    {
	    for (int j = 0; j < B.n; j++)
		if (C.A[ i ] == B.A[ j ]) A[ n++ ] = C.A[ i ];
    }
    A[n] = 0; // ограничитель строки
    return *this; 
}

SetLetter SetLetter::operator& (const SetLetter &B) const
{ 
    SetLetter C(*this); // создаётся копия текущего объекта
    return (C &= B); 
}

SetLetter &SetLetter::operator|= (const SetLetter &B)
{ 
    for(int i = 0; i < B.n; ++i) 
    {
	bool f = true;
	for (int j = 0; j < n; ++j)
	    if (B.A[ i ] == A[ j ]) f = false;
	if (f) A[n++] = B.A[ i ];
    }
    A[n] = 0;
    return *this;
}

SetLetter SetLetter::operator| (const SetLetter &B) const
{
    SetLetter C(*this);
    return (C |= B); 
}
/*
Set Set::operator~ () const
{ 
    Set C;
    for (char c = 'A'; c <= 'Z'; ++c) // Цикл по универсуму
    { 
	bool f = true;
	for (int j = 0; j < n; ++j)
		if (c == A[j]) 
        { 
            f = false; break; 
        } 
	if (f) C.A[C.n++] = c;
    }
    C.A[C.n] = 0; // изменил "->" на "."
    return C;
}
*/
SetLetter::SetLetter(): n(0), S('A' + cnt++), A(new char[N + 1]) // конструктор по умолчанию, в котором все элементы множества = 0. Используется для выделения памяти под результат вычисления - Е
{ 
    A[N + 1] = 0;
}

void SetLetter::Show() // используется для вывода результата вычисления - Е
{ 
    cout << '\n' << 'E' << " = [" << A << "]"; // ПОЧЕМУ-ТО ТЕГ S НЕВЕРНО ВЫВОДИТ СВОЁ ЗНАЧЕНИЕ
}

SetLetter::SetLetter(char *array): S('A' + cnt++), n(strlen(array)), A(array) // генератор множества. S('A' + cnt++) - устанавливает тег в виде первой буквы латинского алфавита для первого объекта класса, для 2-го объекта класса S = B, для 3-го S = C
{
    n = strlen(array) ;
}

SetLetter::SetLetter(const SetLetter & B): S('A' + cnt++), n(B.n), A(new char[N+1]) // конструктор копирования. Можно было бы обойтись без него и предоставить это действие компилятору, если бы в классе не было указателя на дополнительную память. Копирование приведёт к тому, что указатели А в обоих объектах будут указывать на одну и ту же строку
{  
    char *dst(A), *src(B.A);	//Инициализация адресов/счётчиков
    while(*dst++ = *src++);	//Копирование символов до обнаружения 0
}

SetLetter &SetLetter::operator = (const SetLetter& B) // перегрузка присваивания
{    
    if (this != &B)
    { 
        char *dst(A), *src(B.A); n = B.n; 
        while(*dst++ = *src++); S = 'A' + cnt++; 
    }
    return *this; 
}

SetLetter::SetLetter(SetLetter && B): S('A' + cnt++), n(B.n), A(B.A) //Копирование с переносом. Используется, если источником данных является времнный объект
{ 
    B.A = nullptr; 
}

SetLetter &SetLetter::operator= (SetLetter&& B) //Присваивание с переносом
{
    if (this != &B)
    {
        n = B.n; 
        A = B.A;  
        S = 'A' + cnt++; 
        B.A = nullptr; 
    }
	return *this; 
}