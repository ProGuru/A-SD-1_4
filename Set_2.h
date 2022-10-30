#include <iostream>
// массив битов

using namespace std;

class Set 
{
private: // Закрытая часть класса — данные
    static int N, cnt; // мощность универсума и счётчик множеств. (все объекты класса Set будут использовать единственную копию этих переменных)
    int n; // мощность множества
    char *A, S; // тег и память для множества. Т
public: // Открытая часть — функции для работы с множеством
    //Перегрузка оператора означает использование оператора для оперирования объектами классов. 
    Set& operator&= (const Set&);
    Set& operator|= (const Set&);
    Set operator| (const Set&) const; // объединение. двуместные операции в качестве аргумента (второго, потому что первый — это сам объект) имеют константную ссылку на объект типа Set
    Set operator& (const Set&) const; // пересечение. Функции не меняют объект, для которого вызываются, для контроля за этим в каждом из объявлений после списка параметров помещён спецификатор const.
    //Set operator~ () const; // дополнение до универсума (не применяется в задаче)
    Set& operator= (const Set&); // оператор присваивания
    Set& operator= (Set&&);

    void Show(); // вывод множества на экран
    void Show_Other(); // вывод множества на экран, (костыли)
    int power() {return n;} // получение мощности. Применяется в конце программы, где подсчитывается ср. арифмет. мощность всех множеств

    Set(char); // конструктор множества
    Set(); // ещё конструктор — по умолчанию для результата вычисления Е
    Set(const Set &); // конструктор копии
    Set(Set &&);
    
    ~Set() {delete [] A;} // деструктор
};

int Set::N = 16; // Мощность универсума (вариант для шестнадцатиричной системя счисления)
int Set::cnt = 0; // Начальное значение счётчика множеств

// описание методов для работы операторов
Set &Set::operator&= (const Set &B)
{ 
    Set C(*this);
    for (int i = 0; i < N; ++i) 
    {
        if ((C.A[i] == '1') && (B.A[i] == '1')) A[i] = '1';
        else A[i] = '0';
    }
    return *this; 
}

Set Set::operator& (const Set &B) const
{ 
    Set C(*this); // создаётся копия текущего объекта
    return (C &= B); 
}

Set &Set::operator|= (const Set &B)
{ 
    for (int i = 0; i < N; ++i) 
    {
        if ((A[i] == '1') || (B.A[i] == '1'))
        {
		A[i] = '1';
        }
        else A[i] = '0';
    }
    return *this; 
    
}

Set Set::operator| (const Set &B) const
{
    Set C(*this);
    return (C |= B); 
}

Set::Set(): n(0), S('E'), A(new char[N + 1]) // конструктор по умолчанию, в котором все элементы множества = 0. Используется для выделения памяти под результат вычисления - Е
{ 
    A[0] = 0;
}

void Set::Show_Other() // используется для вывода результата вычисления - Е, а также для подсчёта можности множества
{ 
    cout << '\n' << S << " = ["; // ПОЧЕМУ-ТО ТЕГ S НЕВЕРНО ВЫВОДИТ СВОЁ ЗНАЧЕНИЕ
    n = 0;
    for (int i = 0; i < N; i++)
    {
        if (A[i] == '1') 
        {
            cout << (char)(i<=9?i+'0':i+'A'-10);
            n++;
        }
    }
    cout << "]";
}

void Set::Show() // используется для вывода результата вычисления - Е, а также для подсчёта можности множества
{ 
    cout << '\n' << 'E' << " = ["; // ПОЧЕМУ-ТО ТЕГ S НЕВЕРНО ВЫВОДИТ СВОЁ ЗНАЧЕНИЕ
    n = 0;
    for (int i = 0; i < N; i++)
    {
        if (A[i] == '1') 
        {
            cout << (char)(i<=9?i+'0':i+'A'-10);
            n++;
        }
    }
    cout << "]";
}

Set::Set(char): S('A' + cnt++), n(0), A(new char[ N+1 ]) // генератор множества. S('A' + cnt++) - устанавливает тег в виде первой буквы латинского алфавита для первого объекта класса, для 2-го объекта класса S = B, для 3-го S = C
{
    for (int i = 0; i < N; i++)
	if (rand()%5>2) A[i] = '1'; else A[i] = '0';
    A[N] = 0;
    (this)->Show_Other();
}

Set::Set(const Set & B): S('A' + cnt++), n(B.n), A(new char[N+1]) // конструктор копирования. Можно было бы обойтись без него и предоставить это действие компилятору, если бы в классе не было указателя на дополнительную память. Копирование приведёт к тому, что указатели А в обоих объектах будут указывать на одну и ту же строку
{  
    char *dst(A), *src(B.A);	//Инициализация адресов/счётчиков
    while(*dst++ = *src++);	//Копирование символов до обнаружения 0
}

Set &Set::operator = (const Set& B) // перегрузка присваивания
{    
    if (this != &B)
    { 
        char *dst(A), *src(B.A);
        while(*dst++ = *src++); S = 'A' + cnt++; 
    }
    return *this; 
}

Set::Set(Set && B): S('A' + cnt++), n(B.n), A(B.A) //Копирование с переносом. Используется, если источником данных является времнный объект
{ 
    B.A = nullptr; 
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