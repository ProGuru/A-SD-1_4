#include <string.h>
#include <stdlib.h> // для random
#include <time.h>
#include <bits/stdc++.h>
#include <iostream>

#include "Set_1.h" // массив символов
//#include "Set_2.h" // массив битов
//#include "Set_3.h" // машинное слово

using namespace std;

const long q0 = 100000; // количество повторений цикла времени

int main()
{ 
    srand(time(nullptr));
    Set A('A'), B('B'), C('C'), D('D'), E; // программа передаёт параметр в виде символа констуктору Set(char) (конструктор множества)
    clock_t  begin = clock();
    for(long q = 0; q < q0; q++)
    {
        E = (A & B & C) | D;
    }
    clock_t  end = clock() - begin;
    E.Show();
    cout << " Middle power = " << (A.power() + B.power() + C.power() + D.power() + E.power())/5 << " Time=" << (float)(end) / CLOCKS_PER_SEC << " c / " << q0 << endl;
    cin.get();
    return 0;
}