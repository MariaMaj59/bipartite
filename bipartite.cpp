#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

bool prov_bipartite(int n, char *color, int **graph, int v, int c, string &Oddloop) { //Выводит false, если граф двудольный, иначе true
	color[v] = c;
	Oddloop = Oddloop + to_string(v + 1) + ' ';	//Записываем в строку проверяемую вершину
	for (int i = 0; (i < n); i++) 
		if ((graph[v][i] == 1) && (v != i))     //Проверяем только смежные вершины
			if (color[i] == 0)                  //Если это непроверенная вершина
				prov_bipartite(n, color, graph, i, (c == 1 ? 2 : 1), Oddloop);   //Раскрашиваем смежную вершину в другой цвет
			else if (color[i] == c)             //Если понадобился 3ий цвет - граф не является двудольным
				return 0;
	return 1;   //Если граф можно раскрасить 2мя цветами -> он двудольный
}

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream in("input.txt");     //чтение из файла
	ofstream out("output.txt");   //открываю файл для перезаписи
	int n;					//Количество вершин графа
	bool bipartite = 1;		//Двудольность графа
	string Oddloop("");     //Цикл в графе

	if (!in.is_open())                          // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else {
		in >> n; //Первое число в файле - количество вершин

		int **graph = new int*[n];       //Массив с матрицей смежности графа
		char *color = new char[n];       //Цвета вершин: 0 - вершина ещё не покрашена; 1, 2 - различные цвета.
		for (int i = 0; i < n; i++) {
			graph[i] = new int[n];
			color[i] = 0;
		}

		for (int i = 0; i < n; i++)			//Заполнение матрицы из файла
			for (int j = 0; j < n; j++)
				in >> graph[i][j];

		double start_time = clock();		//ПРОВЕРКА ВРЕМЕНИ РАБОТЫ АЛГОРИТМА - НАЧАЛЬНОЕ ВРЕМЯ

		bipartite = prov_bipartite(n, color, graph, 0, 1, Oddloop); //Проверяем двудольность, раскрашиваем граф, находим нечетный цикл

		double end_time = clock();			//ПРОВЕРКА ВРЕМЕНИ РАБОТЫ АЛГОРИТМА - КОНЕЧНОЕ ВРЕМЯ


		if (bipartite)                      //Если граф двудольный
		{
			for (int i = 1; i <= n; i++)    //Записываем в первую строку все вершины одного цвета
				if (color[i - 1] == 1)
					out << i << " ";
			out << endl;
			for (int i = 1; i <= n; i++)    //Записываем во вторую строку все вершины другого цвета
				if (color[i - 1] == 2)
					out << i << " ";
		}
		else									//Если граф не двудольный
			out << "NOT BIPARTITE\n" << Oddloop;//Сообщаем об этом и выводим цикл нечетной длины

		double search_time = end_time - start_time;
		cout << "\nВремя выполнения алгоритма в миллисекундах: " << search_time << endl;

		delete[] graph;
		delete[] color;
	}

	in.close();
	out.close();
	return 0;
}
