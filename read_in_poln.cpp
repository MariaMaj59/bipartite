#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	ofstream in("input.txt");

	int n;
	cout << "Введите размерность матрицы: ";
	cin >> n;

	in << n << "\n";

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				in << 0 << ' ';
			else
				in << 1 << ' ';
		}
		in << "\n";
	}
	

	in.close();
	return 0;
}
