#include <iostream>
// машинное слово

using namespace std;

class SetWord 
{
private: // Закрытая часть класса — данные
    static int N, cnt; // мощность универсума и счётчик множеств. (все объекты класса Set будут использовать единственную копию этих переменных)
    int n; // мощность множества
    char S; // тег для множества
    //unsigned short int W; // машинное слово
    int W; // машинное слово
public: // Открытая часть — функции для работы с множеством

    SetWord& operator&= (const SetWord&);
    SetWord& operator|= (const SetWord&);
    SetWord operator| (const SetWord&) const; // объединение. двуместные операции в качестве аргумента (второго, потому что первый — это сам объект) имеют константную ссылку на объект типа Set
    SetWord operator& (const SetWord&) const; // пересечение. Функции не меняют объект, для которого вызываются, для контроля за этим в каждом из объявлений после списка параметров помещён спецификатор const.
    //Set operator~ () const; // дополнение до универсума (не применяется в задаче)
    SetWord& operator= (const SetWord&); // оператор присваивания
    SetWord& operator= (SetWord&&);

    void Show(); // вывод множества на экран
    void Show_Other(); // вывод множества на экран
    int power() {return n;} // получение мощности. Применяется в конце программы, где подсчитывается ср. арифмет. мощность всех множеств

    SetWord(char*); // конструктор множества
    SetWord(); // ещё конструктор — по умолчанию для результата вычисления Е
    SetWord(const SetWord &); // конструктор копии
    SetWord(SetWord &&);
    
    ~SetWord() {} // деструктор
};

int SetWord::N = 16; // Мощность универсума (вариант для шестнадцатиричной системя счисления)
int SetWord::cnt = 0; // Начальное значение счётчика множеств

int CompWord(char *a)
{
    unsigned short int wA = 0; // так как размер универсума не превосходит 16 символов, то для машинного слова будет достаточно типа переменной short int
    for (int i = 0; a[i]; ++i)
    {
        wA |= (1 << (a[i]<='9'?a[i]-'0':a[i]-'A'+10)); // |= это оператор присвоения битового "или", аналогичен a |= b ->  a = a | b. << - оператор побитового сдвига.
    }
    return wA;
}

void SetWord::Show_Other() // используется для вывода результата вычисления - Е, а также для подсчёта можности множества
{ 
    cout << '\n' << S << " = ["; // ПОЧЕМУ-ТО ТЕГ S НЕВЕРНО ВЫВОДИТ СВОЁ ЗНАЧЕНИЕ
    n = 0;
    
    for (int i = 0; i < N; i++)
    {
        if ((W >> i) & 1)
        {
            cout << (char)(i<=9?i+'0':i+'A'-10);
            n++;
        }
    }
    
    cout << "]";
}

void SetWord::Show() // используется для вывода результата вычисления - Е, а также для подсчёта можности множества
{ 
    cout << '\n' << "E" << " = ["; // ПОЧЕМУ-ТО ТЕГ S НЕВЕРНО ВЫВОДИТ СВОЁ ЗНАЧЕНИЕ
    n = 0;
    
    for (int i = 0; i < N; i++)
    {
        if ((W >> i) & 1)
        {
            cout << (char)(i<=9?i+'0':i+'A'-10);
            n++;
        }
    }
    
    cout << "]";
}

SetWord::SetWord(char *array): S('A' + cnt++), n(0), W(0) // генератор множества. S('A' + cnt++) - устанавливает тег в виде первой буквы латинского алфавита для первого объекта класса, для 2-го объекта класса S = B, для 3-го S = C
{
    W = CompWord(array);
    /*
	W = rand()%65536;
    (this)->Show_Other();
    */
}

SetWord::SetWord(): S('A' + cnt++), n(0), W(0) {} // конструктор по умолчанию, в котором все элементы множества = 0. Используется для выделения памяти под результат вычисления - Е

// описание методов для работы операторов
SetWord &SetWord::operator&= (const SetWord &B)
{ 
    SetWord C(*this);
    W = C.W & B.W;
    return *this; 
}

SetWord SetWord::operator& (const SetWord &B) const
{ 
    SetWord C(*this); // создаётся копия текущего объекта
    return (C &= B); 
}

SetWord &SetWord::operator|= (const SetWord &B)
{ 
    SetWord C(*this);
    W = C.W | B.W;
    return *this; 
    
}

SetWord SetWord::operator| (const SetWord &B) const
{
    SetWord C(*this);
    return (C |= B); 
}


SetWord::SetWord(const SetWord & B): S('A' + cnt++), n(B.n), W(0) // конструктор копирования. Можно было бы обойтись без него и предоставить это действие компилятору, если бы в классе не было указателя на дополнительную память. Копирование приведёт к тому, что указатели А в обоих объектах будут указывать на одну и ту же строку
{  
    W = B.W;
}

SetWord &SetWord::operator = (const SetWord& B) // перегрузка присваивания
{    
    if (this != &B)
    { 
        W = B.W;
        S = 'A' + cnt++; 
    }
    return *this; 
}


SetWord::SetWord(SetWord && B): S('A' + cnt++), n(B.n), W(B.W) {B.W = 0;} //Копирование с переносом. Используется, если источником данных является времнный объект


SetWord &SetWord::operator= (SetWord&& B) //Присваивание с переносом
{
    if (this != &B)
    {
    n = B.n; 
    W = B.W;  
    S = 'A' + cnt++; 
    //B.A = nullptr; 
    }
	return *this; 
}
