#include <string.h>
#include <stdlib.h> // для random
#include <ctime> // time.h для C, ctime для С++
#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>

#include "Set_1.h" // массив символов
#include "Set_2.h" // массив битов
#include "Set_3.h" // машинное слово
#include "Set_4.h" // список

using namespace std;

const long q0 = 100000; // количество повторений цикла времени
char Un[] = {"0123456789ABCDEF"}; // множество - универсум
int N = strlen(Uni); // N - мощность универсума

// функция ввода элементов массива

char* inputArray(char X) {
    char *newArray = new char[N];
    cout << "Введите элементы множества "<< X << ", завершающим символом будет символ '*'" << endl;
    int i = 0; // индексы массива
    while (i < (N - 1))
    {
        cout << i + 1 << ": ";
        cin >> newArray[i++];

        if (newArray[i - 1] == '*') break;

        if (!(((int)newArray[i - 1] >= 48) && ((int)newArray[i - 1] <= 57)) && !(((int)newArray[i - 1] >= 65) && ((int)newArray[i - 1] <= 70))) {
            cout << "Извините, введёный символ не соответствует набору символов для 16-ричной системы счисления. Всего Вам доброго!" << endl;
            break;
        }
    }
    newArray[i - 1] = 0; // символ окончания последовательности введёных элементов массива

    return newArray;
}

// функция вывода элементов массива на экран

void printArray(char *array, char teg) {
    cout << '\n' << teg << " = [";
    for (int i = 0; i < strlen(array); i++)
    {
         cout << array[i];
    }
    cout << "]"; 
}

// Удаляем дубликаты в массиве:

void deleteDublicate(char *array) {
    int n = strlen(array);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (array[i] == array[j]) { 
                for (int k = j; k < n; k++) {
                    array[k] = array[k + 1]; 
                }
                n--;
                j--;
            } 
        }
    }
}

// Сортировка массива по возрастанию: Пузырьковая сортировка (Bubble sort)

void sortArray(char *array) {
    int n = strlen(array);
    int tmp = 0;
    for(int i = 0; i < n; i++) {
        for(int j = (n - 1); j >= (i + 1); j--){
            if (array[j] < array[j - 1]) {
                tmp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = tmp;
            }
        }
    }
}

// Алгоритм ввода слуайных значений в массив

char* makeRandonArray() {
    char *array = new char[N];
    int n = 0; // индекс массива
    int p = 5, q = 2; // переменные для управления вероятностю появления нуля
    for (int i = 0; i < N; i++) 
	    if (rand()%p>q) array[ n++ ] = Un[i]; // в результате геренеции множества образуется массив символов, а также ведётся подсчёт мощности множества
    array[n] = 0;
    return array;
}

int main()
{ 
    srand(time(nullptr));

    int inputMenu = 0;
    while ((inputMenu != 1) && (inputMenu != 2))
    {
        cout << "Ввод элементов массива будет вручную (1), или в случайном порядке (2)?" << endl;
        cin >> inputMenu;
    }

    char *A, *B, *C, *D;

    if (inputMenu == 1) {
        cout << "Множество А: " << endl;
        A = inputArray('A');
        deleteDublicate(A);
        sortArray(A);
        printArray(A, 'A');

        cout << "Множество B: " << endl;
        B = inputArray('B');
        deleteDublicate(B);
        sortArray(B);
        printArray(B, 'B');

        cout << "Множество C: " << endl;
        C = inputArray('C');
        deleteDublicate(C);
        sortArray(C);
        printArray(C, 'C');

        cout << "Множество D: " << endl;
        D = inputArray('D');
        deleteDublicate(D);
        sortArray(D);
        printArray(D, 'D');
    } else {
        A = makeRandonArray(); // формируется массив символов без повторений
        sortArray(A); 
        printArray(A, 'A');

        B = makeRandonArray(); // формируется массив символов без повторений
        sortArray(B); 
        printArray(B, 'B');

        C = makeRandonArray(); // формируется массив символов без повторений
        sortArray(C); 
        printArray(C, 'C');

        D = makeRandonArray(); // формируется массив символов без повторений
        sortArray(D); 
        printArray(D, 'D');
    }
    
    // создаём множества разных типов данных:
    SetLetter arrayLetter_A(A), arrayLetter_B(B), arrayLetter_C(C), arrayLetter_D(D), arrayLetter_E; // программа передаёт параметр в виде символа констуктору Set(char) (конструктор множества)
    SetBits arrayBits_A(A), arrayBits_B(B), arrayBits_C(C), arrayBits_D(D), arrayBits_E;
    SetWord word_A(A), word_B(B), word_C(C), word_D(D), word_E;
    SetList list_A(A), list_B(B), list_C(C), list_D(D), list_E;


    //  Массив элементов:
    clock_t  begin = clock();
    
    for(long q = 0; q < q0; q++)
    {
        //arrayLetter_E = (arrayLetter_A | arrayLetter_B);
        arrayLetter_E = (arrayLetter_A & arrayLetter_B & arrayLetter_C) | arrayLetter_D;
    }
    
    clock_t end = clock() - begin;

    cout << endl << endl <<  "Результат вычиления тип данных: МАССИВ ЭЛЕМЕНТОВ: ";
    arrayLetter_E.Show(); // вывод результата вычисления
    
    cout << " Middle power = " << (arrayLetter_A.power() + arrayLetter_B.power() + arrayLetter_C.power() + arrayLetter_D.power() + arrayLetter_E.power())/5 << " Time=" << (float)(end) / CLOCKS_PER_SEC << " c / " << q0 << endl;
    


    //  Массив битов:
    clock_t  begin1 = clock();
    
    for(long q = 0; q < q0; q++)
    {
        //arrayBits_E = (arrayBits_A | arrayBits_B);
        arrayBits_E = (arrayBits_A & arrayBits_B & arrayBits_C) | arrayBits_D;
    }
    
    clock_t end1 = clock() - begin1;

    cout << endl << "Результат вычиления тип данных: МАССИВ БИТОВ: ";
    arrayBits_E.Show(); // вывод результата вычисления
    
    cout << " Middle power = " << (arrayBits_A.power() + arrayBits_B.power() + arrayBits_C.power() + arrayBits_D.power() + arrayBits_E.power())/5 << " Time=" << (float)(end1) / CLOCKS_PER_SEC << " c / " << q0 << endl;
    


    //  Слово:
    clock_t  begin2 = clock();
    
    for(long q = 0; q < q0; q++)
    {
        //word_E = (word_A | word_B);
        word_E = (word_A & word_B & word_C) | word_D;
    }
    
    clock_t end2 = clock() - begin2;

    cout << endl << "Результат вычиления тип данных: СЛОВО: ";
    word_E.Show(); // вывод результата вычисления
    
    cout << " Middle power = " << (word_A.power() + word_B.power() + word_C.power() + word_D.power() + word_E.power())/5 << " Time=" << (float)(end2) / CLOCKS_PER_SEC << " c / " << q0 << endl;
    


    //  Список:
    clock_t  begin3 = clock();
    
    for(long q = 0; q < q0; q++)
    {
        //list_E = (list_A | list_B);
        list_E = (list_A & list_B & list_C) | list_D;
    }
    
    clock_t end3 = clock() - begin3;

    cout << endl << "Результат вычиления тип данных: СПИСОК: ";
    list_E.Show(); // вывод результата вычисления
    
    cout << " Middle power = " << (list_A.power() + list_B.power() + list_C.power() + list_D.power() + list_E.power())/5 << " Time=" << (float)(end3) / CLOCKS_PER_SEC << " c / " << q0 << endl;
    
    cin.get();
    getch();
    return 0;
}