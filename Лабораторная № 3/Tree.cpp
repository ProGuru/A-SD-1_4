#include <string.h>
#include <stdlib.h> // для random
#include <time.h>
#include <iostream>

using namespace std;



//Класс «узел дерева»
class Node 
{
  char d;	//тег узла
	Node * lft;	// левый сын
	//	Node  * mdl;	— средний сын (если нужно)
	Node * rgt;	// правый сын
public:
	Node(): lft(nullptr), rgt(nullptr) {} // конструктор узла
	~Node() // деструктор (уничтожает поддерево)
  { 
    if (lft) delete lft; 
	  if (rgt) delete rgt; 
  }
friend class Tree;	// дружественный класс «дерево»
};

// Класс «дерево в целом»
class Tree 
{	
  Node * root;	// указатель на корень дерева
  char num, maxnum;		//счётчик тегов и максимальный тег
  int maxrow, offset;		//максимальная глубина, смещение корня
  char ** SCREEN;	// память для выдачи на экран
  void clrscr();	// очистка рабочей памяти
  Node* MakeNode(int depth);	// создание поддерева
  void OutNodes(Node * v, int r, int c); // выдача поддерева
  Tree (const Tree &);	// фиктивный конструктор копии
  Tree (Tree &&);		//копия с переносом (С++11)
  Tree operator = (const Tree &) const = delete;	// присваивание
  Tree operator = (Tree &&) const = delete; // то же,  с переносом
public:
	Tree(char num, char maxnum, int maxrow);	
	~Tree();
	void MakeTree() // ввод — генерация дерева
	{ root = MakeNode(0); }	
	bool exist() { return root != nullptr; } // проверка «дерево не пусто»
	int DFS();	// обход дерева «в глубину»
	int BFS();	// обход «в ширину»
	void OutTree();	// выдача на экран
};

Tree ::	Tree(char nm, char mnm, int mxr): num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr), SCREEN(new char * [maxrow])
{	
  for(int i = 0; i < maxrow; i++) 
  SCREEN[ i ] = new char[ 80 ]; 
}

Tree :: ~Tree() 
{
  for(int i = 0; i < maxrow; i++) 
  delete []SCREEN[ i ];
	delete []SCREEN; 
  delete root; 
}

Node * Tree :: MakeNode(int depth)
{ 
  Node * v = nullptr;
  int Y = (depth < rand()%6+1) && (num <= 'z');
//Вариант: cout << "Node (" << num << ',' << depth << ")1/0: "; cin >> Y;
  if (Y) // создание узла, если Y = 1
  {	
	v = new Node;
	v->d = num++;	 // разметка в прямом порядке (= «в глубину»)
	v->lft = MakeNode(depth+1);
//	 v->d = num++;          //вариант — во внутреннем
	v->rgt = MakeNode(depth+1);
//	 v->d = num++;		// вариант — в обратном
  }
  return v;
}

void Tree :: OutTree()
{	
  clrscr();
	OutNodes(root, 1, offset);
	for (int i = 0; i < maxrow; i++)
	{ 
    SCREEN[ i ][ 79 ] = 0;
		cout << "\n" << SCREEN[ i ];
	}
	cout << "\n";  
}

void Tree :: clrscr()
{ 
  for(int i = 0; i < maxrow; i++)
	memset(SCREEN[i], '.', 80);
}


void Tree :: OutNodes(Node * v, int r, int c) 
{ 
  if (r && c && (c<80)) SCREEN[r-1][c-1] = v->d; // вывод метки
  if (r < maxrow) 
  {
	if (v->lft) OutNodes(v->lft, r + 1, c - (offset >> r)); //левый сын
	// if (v->mdl) OutNode(v->mdl, r + 1, c);	– средний сын (если нужно)
	if (v->rgt) OutNodes(v->rgt, r + 1, c + (offset >> r)); //правый сын
	}
}

template <class Item> class STACK
{ 
  Item *S; int t;
public:
	STACK(int maxt): S(new Item[ maxt ]), t(0) {}

	int empty() const 
  { return t == 0; }

	void push(Item item) 
  { S[t++] = item; }

	Item pop()
  { return ( t ? S[ --t ] : 0 ); }
};

template <class Item> class QUEUE
{	
  Item *Q; 
  int h, t, N;
public:
	QUEUE(int maxQ): h(0), t(0), N(maxQ), Q(new Item[maxQ + 1]) {}
	int empty() const 
  { return (h % N) == t; }

	void push(Item item) 
  { Q[ t++ ] = item; t %= N; }

	Item pop() 
  { h %= N; return Q[ h++ ]; }
};

int Tree :: DFS() 
{ 
  const int MaxS = 20; // максимальный размер стека
  int count = 0;
  STACK <Node *> S(MaxS); //создание стека указателей на узлы
  S.push(root); // STACK <- root
  int k = 0, f; // счётчик количества вершин и индикатор f
  while (!S.empty()) // Пока стек не пуст…
  {   
    f = 0;
    Node * v = S.pop(); // поднять узел из стека
    cout << v->d <<  '_'; count++; // выдать тег, счёт узлов

    if (v->rgt) S.push(v->rgt); // STACK <- (правый сын)
      else {k++; f++;}
    if (v->lft) S.push(v->lft); // STACK <- (левый сын)
      else {(f==0) ? k++ : k--;}
  }
  cout << endl << "Количество вершин, имеющих ровно одного потомка: " << k << endl;
  return count;
}

int Tree :: BFS()
{ 
  const int MaxQ = 20; //максимальный размер очереди
  int count = 0;	
  QUEUE < Node * > Q(MaxQ);  //создание очереди указателей на узлы
  Q.push(root); // QUEUE <- root поместить в очередь корень дерева 
  
  
  while (!Q.empty()) //пока очередь не пуста
  { 	
    Node * v = Q.pop();// взять из очереди,
    cout << v->d << '_'; count++; // выдать тег, счёт узлов 
    if (v->lft) Q.push(v->lft); // QUEUE <- (левый сын)
    if (v->rgt) Q.push(v->rgt); // QUEUE <- (правый сын)
  }
  return count;
}

int main()
{ 
  setlocale(LC_ALL, "Russian");
  srand(time(nullptr));

  int n = 0;
  Tree Tr('a', 'z', 8);
  
  Tr.MakeTree();
  if(Tr.exist()) 
  {
  Tr.OutTree();

	cout << "\n" << "Обход в глубину: ";
	n = Tr.DFS(); 
	cout << " Пройдено узлов = " << n;
  /*
	cout << "\n" << "Обход в ширину: ";
	n = Tr.BFS();
	cout << " Пройдено узлов = " << n;
  */
  }

  else cout << "Дерево пусто!";
  cout << "\n" << "=== Конец ===";   
  cin.get();
}