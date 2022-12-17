#include <iostream>
#include <cstring> // для работы с strlen
// список символов

using namespace std;

// Структура списка
char Uni[] = {"0123456789ABCDEF"}; // множество - универсум

struct List
{
    char data; // элемент множества
    List *next; // указатель на следующий элемент
    List(char e, List * n = nullptr): data(e), next(n) {} // конструктор структуры. *** При инициализации указатель на следующий элемент = 0? ***
    void clearAllChar(List*);
    ~List() {

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

void List::clearAllChar(List *list) {
    List* current = list;
    while (list) 
    {
        current = current->next;
        delete list;
        list = current;
    }
}

//----------------------------------------------------------------------------------------------------------------------------

void clearing(List *list) { // метод очищения списка от элементов
    List* current = list;
    while (list) 
    {
        current = current->next;
        delete list;
        list = current;
    }
}

class SetList 
{
private: // Закрытая часть класса — данные
    static int N, cnt; // мощность универсума и счётчик множеств (нужен для тега S). (все объекты класса Set будут использовать единственную копию этих переменных)
    int n; // мощность множества
    char S; // тег и память для множества. Т
    List *A; // вместо char *A теперь будет переменная типа List
public: // Открытая часть — функции для работы с множеством
    //Перегрузка оператора означает использование оператора для оперирования объектами классов. 
    SetList& operator&= (const SetList&);
    SetList& operator|= (const SetList&);
    SetList operator| (const SetList&) const; // объединение. двуместные операции в качестве аргумента (второго, потому что первый — это сам объект) имеют константную ссылку на объект типа Set
    SetList operator& (const SetList&) const; // пересечение. Функции не меняют объект, для которого вызываются, для контроля за этим в каждом из объявлений после списка параметров помещён спецификатор const.
    //Set operator~ () const; // дополнение до универсума
    SetList& operator= (const SetList&); // оператор присваивания
    SetList& operator= (SetList&&);

    void Show(); // вывод множества на экран
    int power() {
        return n;
    } // получение мощности. Применяется в конце программы, где подсчитывается ср. арифмет. мощность всех множеств

    SetList(char*); // конструктор множества
    SetList(); // ещё конструктор — по умолчанию для результата вычисления Е
    SetList(const SetList &); // конструктор копии
    SetList(SetList &&);
    
    ~SetList()  // деструктор проходит по списку и удаляет каждый элемент
    {
        //delete A; // вызывается деструктор для объекта A (в конструкторе определён как ~List())
    } 
};

int SetList::N = 16; // Мощность универсума (вариант для шестнадцатиричной системя счисления)
int SetList::cnt = 0; // Начальное значение счётчика множеств. Для тега

// описание методов для работы операторов
SetList &SetList::operator&= (const SetList &B)
{ 
    SetList C(*this); // создаётся копия текущего объекта

    List *a  = new List(0);

    clearing(A);
    A = a;
    
    for (List *p = C.A; p; p = p->next) 
    {
	    for (List *q = B.A; q; q = q->next) 
        {
            if (p->data == q->data) {
                List *newList = new List(0); // выделение памяти под новый элемент

                a->data = p->data;
                a->next = newList;
                a = newList;
                a->next = nullptr;
            }
        }
    }

    return *this; 
}

SetList SetList::operator& (const SetList &B) const
{ 
    SetList C(*this); // создаётся копия текущего объекта
    return (C &= B); 
}

SetList &SetList::operator|= (const SetList &B)
{ 
    for (List *q = B.A; q; q = q->next)
    {
        bool f = true;
        List *w;

        for (List *a = A; a; a = a->next) { // проходимся по списку A и смотрим, есть ли в нём похожий символ или нет
            if (q->data == a->data) {
                f = false;
                break;
            }
        }
             
        if (f) {
            List *newList = new List(q->data); // выделение памяти под новый элемент, добавляем в него символ, которога нет в А

            List *w = A; // при каждой итерации указатель ставим в начало

            for (w; w; w = w->next) { // ищем указатель на конец списка А
                if (w->next == nullptr) {
                    break;
                }
            }
            w->next = newList; // добавляем в конец списка А элемент, который есть в В, но нет в А
        }
        
    }
    return *this;
}

SetList SetList::operator| (const SetList &B) const
{
    SetList C(*this);
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
SetList::SetList(): n(0), S('A' + cnt++), A(new List(0)) // конструктор по умолчанию, в котором все элементы множества = 0. Используется для выделения памяти под результат вычисления - Е
{ 
    //List *head = new List(0); // выделение памяти под обнулённый указатель на начало списка
}

void SetList::Show() // используется для вывода результата вычисления - Е
{ 
    cout << '\n' << 'E' << " = [";
    
    for (List *p = A; p; p = p->next)
    {
        cout << p->data;
    }
    
    cout << "]"; 
}

SetList::SetList(char* array): n(strlen(array)), S('A' + cnt++), A(new List(0)) // генератор множества. S('A' + cnt++) - устанавливает тег в виде первой буквы латинского алфавита для первого объекта класса, для 2-го объекта класса S = B, для 3-го S = C
{
    /*
    int nRand = rand()%10 + 1; // здесь максимальное количество элементов множества = 10
    char Massiv[nRand + 1];
    
    for (int i = 0; i < nRand; i++) // N - мощность универсума
    {
        int unitRand = rand()%strlen(Uni);
        Massiv[ n++ ] = Uni[unitRand]; 
    }
    Massiv[n] = 0;
    */
    
    //cout << '\n' << S << " = [" << Massiv << "]"; // вывод символов в прямой последовательности

    A = New_List(array); // записываем в список массив элементов
}

SetList::SetList(const SetList & B): S('A' + cnt++), n(B.n), A(new List(0)) // конструктор копирования. Можно было бы обойтись без него и предоставить это действие компилятору, если бы в классе не было указателя на дополнительную память. Копирование приведёт к тому, что указатели А в обоих объектах будут указывать на одну и ту же строку
{ 
    List *q = B.A;
    A->data = q->data;

    List *startPtr = new List(q->data);
    A = startPtr;

    while (q)
    {
        if (q->next == nullptr) break;
        q = q->next;

        List *newList = new List(q->data);
        startPtr->next = newList;
        startPtr = newList;
    }
}

SetList &SetList::operator = (const SetList& B) // перегрузка присваивания
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

SetList::SetList(SetList && B): S('A' + cnt++), n(B.n), A(B.A) //Копирование с переносом. Используется, если источником данных является времнный объект
{ 
    B.A = nullptr; 
}

SetList &SetList::operator= (SetList&& B) //Присваивание с переносом
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