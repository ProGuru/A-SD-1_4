#include <iostream>
#include <vector>
#include <list>
#include <stack>


using namespace std;
const int MaxV = 26;

char Ch(int c) 
{ return c+'a'; }


void swap_arr(int a[][MaxV], int i, int j, int N) // меняем строки местами
{
    
    for (auto col = 0; col < N; col++) // проходимся по всем элементам столбца
    {
    int s = a[i][col];
    a[i][col] = a[j][col];
    a[j][col] = s;
    }

    for (auto row = 0; row < N; row++) // проходимся по всем элементам столбца
    {
    int s = a[row][i];
    a[row][i] = a[row][j];
    a[row][j] = s;
    }
    
}

bool permutation(int a[][MaxV], int N, int k, int b[][MaxV], bool &z) // алгоритм Нарайаны
{
    int x = 0;

    if (k == N)
    {
        x = 0;
        for (int i = 0; i < N; ++i)
        { 
            for(int j = 0; j < N; ++j)
            if (a[i][j] == b[i][j])
            {
                x++;
            }
        }
        if (x == N * N) z = 1;
    }

    else
    {
        for (int y = k; y < N; y++)
        {
            swap_arr(a, k, y, N);
            permutation(a, N, k + 1, b, z);
            swap_arr(a, k, y, N);
        }
    }
    if (z)
    {
        return 1;
    }
    else return 0;
}


class GR 
{
   int n;
   
public:
    int N = 0; // количество вершин, для которых было хоть что-то введено
    int G[ MaxV ][ MaxV ]; // метрица смежности
   GR(int); //Эта функция определяется аналогично примеру 4.1.

   ~GR() = default;
};


GR :: GR(int MaxV) : n(0) // описание конструктора. Задание графа
{ 
    
    
    string s; // переменная для ввода строки букв - т. е. меток смежных вершин

	for(int i = 0; i < MaxV; ++i) // заполнение матрицы смежности нулями
    for(int j = 0; j < MaxV; ++j) 
    G[ i ][ j ] = 0;

 	cout << "\n Введите мн-ва смежности (строки букв a до z)\n";

  do{ // заполнение матрицы смежности
	  cout << "v[" << Ch(n) << "]="; // Ch(n) - вывод символа на экран
    cin >> s; // ввод смежных вершин
    N++; // помечаем, что для текущец вершины были введены смежные

    for (auto i : s) // цикл foreach. переменной i автоматически приписывается тип char 
      if (isalpha( i )) // проверка, является ли символ буквой
      {
      int j = (tolower( i ) - 'a'); // получение порядкового номера латинской буквы
      G[ n ][ j ] = G[ j ][ n ] = 1; // матрица смежности делается симметричной
      }

	  ++n;
  } while(isalpha(s[0]) && n < MaxV);

    // вывод на экран матрицы смежности
    cout << "\nМатрица смежности";
    cout << "\n     a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z";
    cout << "\n-----------------------------------------------------------------------------------";

    for (auto i = 0; i < (N-1); ++i) // вывод на экран таблицы смежности
    { 
    cout << "\n "<< Ch(i) << " |";
    for(auto j = 0; j < (N-1); ++j)
        cout << " " << G[ i ][ j ] << " ";
    }

}

int main()
{ 
    cout << "Поиск изоморфного неориентированного графа\n";
    cout << "Граф № 1 \n";
    GR Grath_1(MaxV); // объявляем 1-й граф
    cout << endl << "\nГраф № 2";
    GR Grath_2(MaxV); // объявляем 2-й граф
    setlocale(LC_ALL, "Russian");

    bool z  = false; // для оформления логической функции в permutation, иначе не получается из-за рекурсии
    if (Grath_1.N != Grath_2.N)
    {
        cout << "\nКоличество вершин у обоих графов не совпадает! \n";
    }
    else
    {
        if (permutation(Grath_1.G, Grath_1.N - 1, 0, Grath_2.G, z))
        cout << "\nГрафы являются изоморфными! \n";
        else {cout << "\nГрафы не прошли проверку на изоморфизм. \n";} 
    }

} 