#include <iostream>
#include <vector>
#include <list>
#include <stack>


using namespace std;
const int MaxV = 26;

char Ch(int c) 
    { return c+'a'; }

class GR {
   int num, n, m;
   vector <list<int>> LIST; // матрица для списка смежности
   vector <int> NEW, X; // NEW вектор пройденных вершин, X - порядок векторов
   void GAM(int); // функция GAM является подфункцией GAM_test
public:
   GR(int); //Эта функция определяется аналогично примеру 4.1.
   void GAM_test(); // функция нахождения Гамильонова пути
   ~GR() = default;
};

void GR::GAM (int k)
{
  if(k == n) //Найдено решение, выводим. n - кол-во вершин
  {  
    cout << "<";
    for (auto x : X) cout << Ch(x) << ' '; // в вектор Х записывается путь. x - порядок символа в англ. алфавите
    cout << ">\n"; cin.get();
  }
  else
    { 
        for (auto u : LIST[ X[ k-1 ] ]) //Перебираем множество Ak, X[ k-1 ] - обращаемся к строке матрицы с позицией текущей вершины
        { 
            if (NEW[ u ]) //Очередная вершина свободна?
            { 
                NEW[ u ] = false; //Объявляем вершину занятой
                X.push_back(u); // и добавляем её в решение
                GAM(k+1); //Продолжаем расширять вектор
                X.pop_back(); //Убираем проверенную вершину… Это нужно чтобы освободить текущую память в стеке, перед тем как алгоритм станет искать новые пути. Если этого не сделать, при нахождении новых путей будут сначала печататься старые
                NEW[ u ] = true; // и объявляем её снова свободной, чтобы можно было обнаружить новые пути
            }
        }
    }
}

void GR::GAM_test(){
  NEW.resize(n, 1); // вектор из 1 (пускай и логических)
  NEW[0] = false; // первый элемент - ложь

  cout << "\nГамильтонов путь:\n";
  X.push_back(0); // вектор, добавление 0 в конец
  GAM(1);
  cin.get();
}

GR :: GR(int MaxV) : num(0), n(0), m(0) // описание конструктора. Задание графа
{ 
  int G[ MaxV ][ MaxV ]; // метрица смежности
  string s; // переменная для ввода строки букв - т. е. меток смежных вершин

	for(int i = 0; i < MaxV; ++i) // заполнение матрицы смежности нулями
    for(int j = 0; j < MaxV; ++j) 
    G[ i ][ j ] = 0;

 	cout << "\n Введите мн-ва смежности (строки букв a до z)\n";

  do{ // заполнение матрицы смежности
	  cout << "v[" << Ch(n) << "]="; // Ch(n) - вывод символа на экран
    cin >> s; // ввод смежных вершин

    for (auto i : s) // цикл foreach. переменной i автоматически приписывается тип char 
      if (isalpha( i )) // проверка, является ли символ буквой
      {
      int j = (tolower( i ) - 'a'); // получение порядкового номера латинской буквы
      G[ n ][ j ] = G[ j ][ n ] = 1; // матрица смежности делается симметричной
      }

	  ++n;
  } while(isalpha(s[0]) && n < MaxV);

  // ФОРМИРОВАНИЕ СПАСКА СМЕЖНОСТИ

  n = m = 0; // n - количество вершин, m - количество рёбер
  LIST.resize(MaxV); // под массив выделяется MaxV элементов

  for (int i=0; i<MaxV; ++i)
  {
    int f = 0;
    cout << '\n' << Ch(i) << ": "; // вывод каждой буквы из алфавита на экран

	  for (int j = 0; j < MaxV; ++j) // из матрицы смежности формируется список смежности
      if(G[ i ][ j ]) // если элемент существует
	    { 
        ++f; // подсчёт количества связей для одного узла
	      LIST[ i ].push_back(j); // заполнение массива
	      cout << Ch( j ) << ' '; // вывод на экран смежной вершины
	    }
      else cout << "- ";

	  m += f; // подчсёт количества рёбер

	  if (f) ++n; // количество вершин
	  else break;
  }
  cout << "\n|V|=" << n <<  " |E|=" << m/2; // |V| - мощность множества вершин (количество вершин), |E| - мощность множества (количество связей)
}

int main()
{ 
    GR G(MaxV);
    setlocale(LC_ALL, "Russian");
    cout << "\nGAM test ====================== (C)lgn, 16.10.03;24.02.20";
    //Тестирование функции GAM
    G.GAM_test();
} 