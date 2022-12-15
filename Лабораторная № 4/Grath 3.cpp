#include <time.h>
#include <iostream>

using namespace std;
const int N=10;	//Количество вершин

int a[ N ][ N ], i, j, maxv = 0, k, st, ans[ N ], i1, num, K[ N+1 ], U[ N ];

void G(int k) 	//Перебор с возвратом
{  
    int i, i0;
	if(k == 1) i0 = 0; else i0 = K[ k-2 ] + 1;

	for( i = i0; i < N; i++)
	if (U[ i ]) 
    {
		K[ k-1 ] = i; 
        j = 0;
		while ((j < k) && a[ K[ j ] ][ i ]) j++;

		if (j+1 == k) //Найдена клика...
        { 	
			if (k > maxv) //больше предыдущей, зафиксировать решение
            {
			maxv = k;

			for (auto i1 = 0; i1 < k; ++i1)
			ans[ i1 ] = K[ i1 ] + 1;
			}

            if (k == maxv) //... и выдать
            { 
                cout << '\n' << " max=" << maxv << " : ";
                for(auto i1 = 0; i1 < maxv; ++i1)
                cout << (K[i1] + 1) << " ";
                cin.get( );
            }

            U[ i ] = 0; //Вершина (i) теперь занята
            G(k+1); // Попробовать расширить решение
            U[ i ] = 1; //Возврат: (i) снова свободна
		}
	}
}

int main()
{  
    setlocale(LC_ALL, "Russian");
	srand(time(nullptr));
    //Генерация матрицы смежности неорграфа
	for(auto i = 0; i < N; ++i)
	{  
        U[ i ] = 1;
		for (auto j = i; j < N; ++j) 
			if(j == i) a[ i ][ j ] = 0; else a[ i ][ j ] = a[ j ][ i ] = rand() % 15 > 2; // очень вероятное событие; заполняем матрицу симметрично, главная диагонать = 0
	}

	if (N<21) //Вывод на экран, если помещается
    { 
        cout << "\nМатрица смежности";
        cout << "\n      1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 0";
        cout << "\n-----------------------------------------------------------------";

        for (auto i = 0; i < N; ++i) // вывод на экран таблицы смежности
        { 
        cout << "\n "<< i+1 << " |";
        for(auto j = 0; j < N; ++j)
            cout << " " << a[ i ][ j ] << " ";
        }
	}

	//Эмпирический алгоритм — полиномиальной сложности
	for (auto i = 0; i < N; ++i)
	{  
        K[0] = i;
		for(auto st = i + 1; st < N; ++st)
		if(a[ i ][ st ])
		{ 
            k = 1;
			for(auto j = st; j < N; ++j)
			{	
                num = 1;
				while((a[ K[ num-1 ] ][ j ]) && (num <= k)) ++num;
				if ((num - 1) == k)
				{ ++k; K[ k-1 ] = j; }
			}

			if (k > maxv) //Зафиксировать решение
			{ 
                maxv = k;
				for(auto i1 = 0; i1 < k; ++i1) ans[ i1 ] = K[ i1 ] + 1;
			}

			if (k == maxv) //... и выдать 
            {
				cout << "\n max=" << maxv << " : ";
				for (auto i1 = 0; i1 < maxv; ++i1)
					cout << (K[i1] + 1) << " ";
				cin.get();
			}
		}
	}

	cout << "\n Клика мощностью " << maxv <<" из вершин: ";
	for(auto i = 0; i < maxv; ++i)
		cout << ans[i] << " ";
	cout << "\n Контроль перебором";
	maxv = 0;
	G(1);
	cout << "\nИТОГ: мощность " << maxv <<", вершины: ";
	for(auto i = 0; i < maxv; ++i)
		cout << ans[i] << " ";
	cout << endl;
	cin.get();
}