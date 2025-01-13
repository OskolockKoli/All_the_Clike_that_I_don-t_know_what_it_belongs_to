#include <iostream>

using namespace std;

int f(int a, int b) {
    if (a < 0) {
        a = 0;
    }
    else {
        a = b;
    }
    return a;
}

int main()
{
    setlocale(0, "Rus");
    int n, m, i ,j, C;
    cout << "Введите колво строчек: ";
    cin >> n;
    cout << "Введите колво столбиков: ";
    cin >> m;
    cout << "Введите C: ";
    cin >> C;
    int** A = new int* [n];
    for (i = 0; i < n; i++) {
        A[i] = new int[m];
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cout << f(A[i][j], C);
        }
        cout << endl;
    }

    return 0;
}