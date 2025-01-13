/*
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Функция для симплекс метода
void simplex(int n, int m, vector<double>& b, vector<vector<double>>& A) {
    // Инициализация начальной базы
    bool isBasis[n];
    for (int i = 0; i < n; ++i) {
        if (b[i] > 0) {
            isBasis[i] = true;
        }
        else {
            isBasis[i] = false;
        }
    }

    while (!isBasisSolution()) {
        int pivotRow = findPivotRow();
        int pivotCol = findPivotColumn(pivotRow);
        swapRows(pivotRow, pivotCol);
        updateTableau();
    }
}

bool isBasisSolution() {
    for (int i = 0; i < n; ++i) {
        if (!isBasis[i]) return false;
    }
    return true;
}

int findPivotRow() {
    double minRatio = INFINITY;
    int pivotRow = -1;
    for (int row = 0; row < m; ++row) {
        if (!isBasis[row]) {
            double ratio = abs(A[row][m]) / A[row][n];
            if (ratio < minRatio) {
                minRatio = ratio;
                pivotRow = row;
            }
        }
    }
    return pivotRow;
}

int findPivotColumn(int pivotRow) {
    double maxCoef = -INFINITY;
    int pivotCol = -1;
    for (int col = 0; col < n; ++col) {
        if (isBasis[col]) {
            double coef = abs(A[pivotRow][col]);
            if (coef > maxCoef) {
                maxCoef = coef;
                pivotCol = col;
            }
        }
    }
    return pivotCol;
}

void swapRows(int row1, int row2) {
    for (int col = 0; col <= n; ++col) {
        double temp = A[row1][col];
        A[row1][col] = A[row2][col];
        A[row2][col] = temp;
    }
}

void updateTableau() {
    for (int row = 0; row < m; ++row) {
        if (!isBasis[row]) {
            double multiplier = A[row][n] / A[row][m];
            for (int col = 0; col <= n; ++col) {
                A[row][col] -= A[m][col] * multiplier;
            }
        }
    }
}

int main() {
    int n = 3; // Количество переменных
    int m = 2; // Количество ограничений

    vector<double> b(n + 1, 0);
    b[0] = 1; // Целевая функция

    vector<vector<double>> A(m + 1, vector<double>(n + 1));
    A[0][0] = 27;
    A[0][1] = 28;
    A[0][2] = 30;
    A[0][3] = -26;

    A[1][0] = 1;
    A[1][1] = 1;
    A[1][2] = 1;
    A[1][3] = 0;

    simplex(n, m, b, A);

    cout << "Ответ: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << "x_" << i + 1 << ": " << b[i + 1] << endl;
    }
    return 0;
}
*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Функции для расчета потенциалов
void CalculateRowPotentials(const vector<int>& supply, map<char, double>& row_potentials);
void CalculateColPotentials(const vector<int>& demand, const map<char, double>& row_potentials, map<char, double>& col_potentials);
bool IsOptimalPlan(const map<char, double>& row_potentials, const map<char, double>& col_potentials);

// Основная функция для решения задачи
void SolveTransportationProblem(const vector<int>& supply, const vector<int>& demand, int cost[]) {
    // Создание списка возможных поставок
    map<pair<char, char>, int> assignments;

    while (!IsOptimalPlan(assignments)) {
        // Инициализация потенциалов
        map<char, double> row_potentials;
        map<char, double> col_potentials;
        CalculateRowPotentials(supply, row_potentials);
        CalculateColPotentials(demand, row_potentials, col_potentials);

        pair<char, char> nextAssignment;
        bool foundNextAssignment = false;
        double minimumDiff = numeric_limits<double>::max();

        for (auto& [from, to] : assignments) {
            double diff = fabs((row_potentials[to] + col_potentials[from]) * cost[from][to]);
            if (diff < minimumDiff && !foundNextAssignment) {
                minimumDiff = diff;
                nextAssignment = make_pair(from, to);
                foundNextAssignment = true;
            }
        }

        if (foundNextAssignment) {
            assignments.insert({ nextAssignment, 1 });
        }
    }

    cout << "Оптимальный план:" << endl;
    for (auto& [from, to] : assignments) {
        cout << from << " -> " << to << ", ";
    }
    cout << endl;
}

// Функция для расчета потенциала по строкам
void CalculateRowPotentials(const vector<int>& supply, map<char, double>& row_potentials) {
    for (int i = 0; i < supply.size(); ++i) {
        double potential = accumulate(supply.begin(), supply.end(), 0.0) / supply[i];
        row_potentials[supply[i]] = potential;
    }
}

// Функция для расчета потенциала по столбцам
void CalculateColPotentials(const vector<int>& demand, const map<char, double>& row_potentials, map<char, double>& col_potentials) {
    for (int i = 0; i < demand.size(); ++i) {
        double potential = accumulate(demand.begin(), demand.end(), 0.0) / demand[i];
        col_potentials[demand[i]] = potential;
    }
}

// Проверка оптимальности плана
bool IsOptimalPlan(const map<char, double>& row_potentials, const map<char, double>& col_potentials) {
    for (int i = 0; i < row_potentials.size(); ++i) {
        if (fabs((row_potentials[i] + col_potentials[i]) * cost[i]) != fabs(supply[i])) {
            return false;
        }
    }

    for (int i = 0; i < col_potentials.size(); ++i) {
        if (fabs((row_potentials[i] + col_potentials[i]) * cost[i]) != fabs(demand[i])) {
            return false;
        }
    }

    return true;
}

int main() {
    // Данные из задачи
    int cost[][7] = {
        {  4,   3,   5,   6,   2,   1,   8 },
        {  2,   1,   8,   3,   7,   6,   4 },
        {  7,   3,   9,  10,   8,   4,   7 },
        {  3,   4,   1,   5,   1,   5,  10 },
        {  6,   7,   2,   3,   4,   8,   5 },
        {  5,   9,   4,   6,   7,   2,   3 }
    };

    int supply[] = { 100, 120, 80, 100, 110, 150 };
    int demand[] = { 100, 150, 50, 100, 110, 150, 180 };

    SolveTransportationProblem(supply, demand, cost);

    return 0;
}
