#include <iostream>
// массив битов

using namespace std;

class SetBits 
{
private: // Закрытая часть класса — данные
    static int N, cnt; // мощность универсума и счётчик множеств. (все объекты класса Set будут использовать единственную копию этих переменных)
    int n; // мощность множества
    char *A, S; // тег и память для множества. Т
public: // Открытая часть — функции для работы с множеством
    //Перегрузка оператора означает использование оператора для оперирования объектами классов. 
    SetBits& operator&= (const SetBits&);
    SetBits& operator|= (const SetBits&);
    SetBits operator| (const SetBits&) const; // объединение. двуместные операции в качестве аргумента (второго, потому что первый — это сам объект) имеют константную ссылку на объект типа Set
    SetBits operator& (const SetBits&) const; // пересечение. Функции не меняют объект, для которого вызываются, для контроля за этим в каждом из объявлений после списка параметров помещён спецификатор const.
    //Set operator~ () const; // дополнение до универсума (не применяется в задаче)
    SetBits& operator= (const SetBits&); // оператор присваивания
    SetBits& operator= (SetBits&&);

    void Show(); // вывод множества на экран
    void Show_Other(); // вывод множества на экран, (костыли)
    int power() {
        n = 16;
        return n;
    } // получение мощности. Применяется в конце программы, где подсчитывается ср. арифмет. мощность всех множеств

    SetBits(char*); // конструктор множества
    SetBits(); // ещё конструктор — по умолчанию для результата вычисления Е
    SetBits(const SetBits &); // конструктор копии
    SetBits(SetBits &&);
    
    ~SetBits() {} // деструктор
};

int SetBits::N = 16; // Мощность универсума (вариант для шестнадцатиричной системя счисления)
int SetBits::cnt = 0; // Начальное значение счётчика множеств

void makeBitArray(char *array, char *bA) // в функцию передается указатель на первый элемент массива a[]. Запись BitArray(char a[]) будет аналогичной
{
    for (int i = 0; i < strlen(array); ++i)
    {
        cout << array[i];
        bA[array[i]<='9'?array[i]-'0':array[i]-'A'+10] = 1; // устанавливаем в 1 биты, соответствующие каждому символу из А. Запись a[i]<='9'?a[i]-'0':a[i]-'A'+10 является тернарной функцией
    }
}

// описание методов для работы операторов
SetBits &SetBits::operator&= (const SetBits &B)
{ 
    //Show_Other();

    SetBits C(*this);
    for (int i = 0; i < N; ++i) 
    {
        if ((C.A[i] == '1') && (B.A[i] == '1')) A[i] = '1';
        else A[i] = '0';
    }
    return *this; 
}

SetBits SetBits::operator& (const SetBits &B) const
{ 
    SetBits C(*this); // создаётся копия текущего объекта
    return (C &= B); 
}

SetBits &SetBits::operator|= (const SetBits &B)
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

SetBits SetBits::operator| (const SetBits &B) const
{
    SetBits C(*this);
    return (C |= B); 
}

SetBits::SetBits(): n(0), S('E'), A(new char[N + 1]) // конструктор по умолчанию, в котором все элементы множества = 0. Используется для выделения памяти под результат вычисления - Е
{ 
    A[0] = 0;
}

void SetBits::Show_Other() // используется для вывода результата вычисления - Е, а также для подсчёта можности множества
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

void SetBits::Show() // используется для вывода результата вычисления - Е, а также для подсчёта можности множества
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

SetBits::SetBits(char *array): S('A' + cnt++), n(0), A(new char[ N+1 ]) // генератор множества. S('A' + cnt++) - устанавливает тег в виде первой буквы латинского алфавита для первого объекта класса, для 2-го объекта класса S = B, для 3-го S = C
{
    for (int i = 0; i < strlen(A); i++)
    {
        A[i] = '0';
    }
    
    for (int i = 0; i < strlen(array); ++i)
    {
        A[array[i]<='9'?array[i]-'0':array[i]-'A'+10] = '1'; // устанавливаем в 1 биты, соответствующие каждому символу из А. Запись a[i]<='9'?a[i]-'0':a[i]-'A'+10 является тернарной функцией
    }
}

SetBits::SetBits(const SetBits & B): S('A' + cnt++), n(B.n), A(new char[N+1]) // конструктор копирования. Можно было бы обойтись без него и предоставить это действие компилятору, если бы в классе не было указателя на дополнительную память. Копирование приведёт к тому, что указатели А в обоих объектах будут указывать на одну и ту же строку
{  
    for (int i = 0; i < N; i++)
    {
        A[i] = B.A[i];
    }
    A[N] = 0;
}

SetBits &SetBits::operator = (const SetBits& B) // перегрузка присваивания
{    
    if (this != &B)
    { 
        char *dst(A), *src(B.A);
        while(*dst++ = *src++); S = 'A' + cnt++; 
    }
    return *this; 
}

SetBits::SetBits(SetBits && B): S('A' + cnt++), n(B.n), A(B.A) //Копирование с переносом. Используется, если источником данных является времнный объект
{ 
    B.A = nullptr; 
}

SetBits &SetBits::operator= (SetBits&& B) //Присваивание с переносом
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