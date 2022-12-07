#include <iostream>
#include <cstring> // для работы с strlen
// массив символов

using namespace std;

// Структура списка
char Uni[] = {"0123456789ABCDEF"}; // множество - универсум

struct List
{
    char data; // элемент множества
    List *next; // указатель на следующий элемент
    List(char e, List * n = nullptr): data(e), next(n) {} // конструктор структуры. *** При инициализации указатель на следующий элемент = 0? ***
    void clear(List*);
    ~List() {
        // clear();
    } // деструктор структуры. В теле освобождение памяти выделенного на указатель
};

List *New_List(char X[]) // функция заполнения списка
{
    List *temp; // буфер
    List *LX = new List(0); // выделение памяти под обнулённый указатель на начало списка
    for (int i = 0; i < strlen(X); i++)
    {
        if (i == 0) // при первои итерации данные будут записаны в поле первой записи
        {
            LX->data = X[i];
            temp = LX; // в temp запишем указатель на данную запись
        }
        else
        {
            List *p = new List(X[i]); // выделение памяти под новый элемент
            temp->next = p; // в предыдущую запись в поле указателя на следующий элемент запишем эту запись
            temp = p;
        }
    }
    return LX; // возвращаем указатель на начало списка
}

void List::clear(List *list) {
    List* current = list;
    while (list) 
    {
        current = current->next;
        delete list;
        list = current;
    }
}

//----------------------------------------------------------------------------------------------------------------------------

class Set 
{
private: // Закрытая часть класса — данные
    static int N, cnt; // мощность универсума и счётчик множеств. (все объекты класса Set будут использовать единственную копию этих переменных)
    int n; // мощность множества
    char S; // тег и память для множества. Т
    List *A; // вместо char *A теперь будет переменная типа List
public: // Открытая часть — функции для работы с множеством
    //Перегрузка оператора означает использование оператора для оперирования объектами классов. 
    Set& operator&= (const Set&);
    Set& operator|= (const Set&);
    Set operator| (const Set&) const; // объединение. двуместные операции в качестве аргумента (второго, потому что первый — это сам объект) имеют константную ссылку на объект типа Set
    Set operator& (const Set&) const; // пересечение. Функции не меняют объект, для которого вызываются, для контроля за этим в каждом из объявлений после списка параметров помещён спецификатор const.
    //Set operator~ () const; // дополнение до универсума
    Set& operator= (const Set&); // оператор присваивания
    Set& operator= (Set&&);

    void Show(); // вывод множества на экран
    int power() {return n;} // получение мощности. Применяется в конце программы, где подсчитывается ср. арифмет. мощность всех множеств

    Set(char); // конструктор множества
    Set(); // ещё конструктор — по умолчанию для результата вычисления Е
    Set(const Set &); // конструктор копии
    Set(Set &&);
    
    ~Set()  // деструктор проходит по списку и удаляет каждый элемент
    {
        delete A; // вызывается деструктор для объекта A (в конструкторе определён как ~List())
    } 
};

int Set::N = 16; // Мощность универсума (вариант для шестнадцатиричной системя счисления)
int Set::cnt = 0; // Начальное значение счётчика множеств. Для тега

// описание методов для работы операторов
Set &Set::operator&= (const Set &B)
{ 
    Set C(*this); // создаётся копия текущего объекта

    /*
    n = 0;
    for (int i = 0; i < C.n; ++i) 
    {
	    for (int j = 0; j < B.n; j++)
		if (C.A[ i ] == B.A[ j ]) A[ n++ ] = C.A[ i ];
    }
    A[n] = 0; // ограничитель строки
    */

    List *a  = new List(0);
    for (List *p = C.A; p; p = p->next) 
    {
	    for (List *q = B.A; q; q = q->next) 
        {
            if (p->data == q->data) {
                a->data = p->data;
                List *newList = new List(0); // выделение памяти под новый элемент
                
                a->next = newList;
                a = newList;
                a->next = nullptr;
            }
        }
    }
    
    A = a;
    // a->next = nullptr; // пробный вариант окончания списка

    return *this; 
}

Set Set::operator& (const Set &B) const
{ 
    Set C(*this); // создаётся копия текущего объекта
    return (C &= B); 
}

Set &Set::operator|= (const Set &B)
{ 
    for (List *q = B.A; q; q = q->next)
    {
        bool f = true;
        List *w;

        for (List *a = A; a; a = a->next) {
            if (q->data == a->data) {
                f = false;
                break;
            }
        }
             
        if (f) {
            List *newList = new List(q->data); // выделение памяти под новый элемент

            List *w = A;

            for (w; w; w = w->next) {
                if (w->next == nullptr) {
                    break;
                }
            }
            w->next = newList;
        }
        
    }
    return *this;
}

Set Set::operator| (const Set &B) const
{
    Set C(*this);
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
Set::Set(): n(0), S('A' + cnt++), A(new List(0)) // конструктор по умолчанию, в котором все элементы множества = 0. Используется для выделения памяти под результат вычисления - Е
{ 
    //List *head = new List(0); // выделение памяти под обнулённый указатель на начало списка
}

void Set::Show() // используется для вывода результата вычисления - Е
{ 
    cout << '\n' << 'E' << " = [";
    
    for (List *p = A; p; p = p->next)
    {
        cout << p->data << endl;
    }
    
    cout << "]"; 
}

Set::Set(char): S('A' + cnt++), n(0), A(new List(0)) // генератор множества. S('A' + cnt++) - устанавливает тег в виде первой буквы латинского алфавита для первого объекта класса, для 2-го объекта класса S = B, для 3-го S = C
{
    int nRand = rand()%10 + 1; // здесь максимальное количество элементов множества = 10
    char Massiv[nRand + 1];
    
    for (int i = 0; i < nRand; i++) // N - мощность универсума
    {
        int unitRand = rand()%strlen(Uni);
        Massiv[ n++ ] = Uni[unitRand]; 
    }
     
	 
    Massiv[n] = 0;
    cout << '\n' << S << " = [" << Massiv << "]"; // вывод символов в прямой последовательности

    A = New_List(Massiv); // записываем в список массив элементов
}

Set::Set(const Set & B): S('A' + cnt++), n(B.n), A(new List(0)) // конструктор копирования. Можно было бы обойтись без него и предоставить это действие компилятору, если бы в классе не было указателя на дополнительную память. Копирование приведёт к тому, что указатели А в обоих объектах будут указывать на одну и ту же строку
{ 
    for (List *p = A; p; p = p->next)
    {
        for (List *q = B.A; q; q = q->next)
        {
            A->data = B.A->data;
        }
    }
}

Set &Set::operator = (const Set& B) // перегрузка присваивания
{    
    if (this != &B)
    { 
        for (List *p = A; p; p = p->next)
        {
            for (List *q = B.A; q; q = q->next)
            {
                A->data = B.A->data;
            }
        }
        n = B.n; 
        S = 'A' + cnt++; 
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