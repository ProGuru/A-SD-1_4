#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

//#include "Set.h"

using namespace std;

class Set 
{
private: // Закрытая часть класса — данные
    static int N, cnt; // мощность универсума и счётчик множеств. (все объекты класса Set будут использовать единственную копию этих переменных)
    int n; // мощность множества
    char S, *A; // тег и память для множества
public: // Открытая часть — функции для работы с множеством
    //Перегрузка оператора означает использование оператора для оперирования объектами классов. 
    Set& operator&= (const Set&);
    Set& operator|= (const Set&);
    Set operator| (const Set&) const; // объединение. двуместные операции в качестве аргумента (второго, потому что первый — это сам объект) имеют константную ссылку на объект типа Set
    Set operator& (const Set&) const; // пересечение. Функции не меняют объект, для которого вызываются, для контроля за этим в каждом из объявлений после списка параметров помещён спецификатор const.
    Set operator~ () const; // дополнение до универсума
    Set& operator= (const Set&); // оператор присваивания
    Set& operator= (Set&&);

    void Show(); // вывод множества на экран
    int power() {return n;} // получение мощности 
    //void Out() {cout << "Здесь должен быть вывод множества, алгоритм брать из лабы 1";}

    Set(char); // конструктор множества
    Set(); // ещё конструктор — по умолчанию
    Set(const Set &); // конструктор копии
    Set (Set &&);

    ~Set() {delete [] A;} // деструктор
};

int Set::N = 16; // Мощность универсума (пример для латинских букв)
int Set::cnt = 0; // Начальное значение счётчика  множеств
const long q0 = 1; // количество повторений цикла времени

Set &Set::operator&= (const Set &B)
{ 
    Set C(*this);
    n = 0;
    for (int i = 0; i < C.n; ++i) 
    {
	    for (int j = 0; j < B.n; j++)
		if (C.A[ i ] == B.A[ j ]) A[ n++ ] = C.A[ i ];
    }
    A[n] = 0; // ограничитель строки
    return *this; 
}

Set Set::operator& (const Set &B) const
{ 
    Set C(*this);
    return (C &= B); 
}

Set &Set::operator|= (const Set &B)
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

Set Set::operator| (const Set &B) const
{
    Set C(*this);
    return (C |= B); 
}

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

void Set::Show() 
{ 
    cout << "\n" << 'E' << " = [" << A << "]"; 
}

Set::Set(): n(0), S ('A' + cnt++), A(new char[N + 1])   
{ 
    A[0] = 0; 
}

Set::Set(char): S('A' + cnt++), n(0), A(new char[ N+1 ])
{
    for (int i = 0; i < N; i++)
	if (rand()%5>3) A[ n++ ] = i + 'A';
    A[n] = 0;
    cout << '\n' << S << " = [" << A << "]";
}

Set::Set(const Set & B): S('A' + cnt++), n(B.n), A(new char[N+1])
{  
    char *dst(A), *src(B.A);	//Инициализация адресов/счётчиков
    while(*dst++ = *src++);	//Копирование символов до обнаружения 0
}

Set &Set::operator = (const Set& B)
{    
    if (this != &B)
    { 
        char *dst(A), *src(B.A); n = B.n; 
        while(*dst++ = *src++); S = 'A' + cnt++; 
    }
    return *this; 
}

Set::Set(Set && B): S('A' + cnt++), n(B.n), A(B.A)
{ 
    B.A = nullptr; //Копирование с переносом
}

Set &Set::operator= (Set&& B) //Присваивание с переносом
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

int main()
{ 
    srand(time(nullptr));
    Set A('A'), B('B'), C('C'), D('D'), E;
    clock_t  begin = clock();
    for(long q = 0; q < q0; q++)
    {
        E = (A | B); 
    }
    clock_t  end = clock();
    E.Show();
    cout << " Middle power = " << (A.power() + B.power() + C.power() + D.power() + E.power())/5 << " Time=" << end - begin << " / " << q0 << endl;
    cin.get();
    return 0;
}