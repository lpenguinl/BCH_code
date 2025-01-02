#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <iomanip>
#include <numeric>
#include <fstream>
#include <sstream>

using namespace std;

// Умножение матриц
vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rows1 = A.size();
    int cols1 = A[0].size();
    int cols2 = B[0].size();

    vector<vector<int>> result(rows1, vector<int>(cols2, 0));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += (A[i][k] * B[k][j]);
            }
        }
    }
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            result[i][j] %= 2;
        }
    }

    return result;
}
// Вычисление транспонированной матрицы
vector<vector<int>> transpose(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> transposed(cols, vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

// Функция для обмена строк
void swapRows(vector<vector<int>>& matrix, int row1, int row2) {
    swap(matrix[row1], matrix[row2]);
}

// перевод в каноничную форму
vector<vector<int>> toCanonicalForm(const vector<vector<int>>& originalMatrix) {
    vector<vector<int>> matrix = originalMatrix;
    int numRows = matrix.size();

    if (numRows == 0) {
        return {};
    }

    int numCols = matrix[0].size();
    int lead = 0; // Текущая ведущая позиция

    for (int row = 0; row < numRows; ++row) {
        if (lead >= numCols) break;

        // Находим ведущий элемент
        int pivotRow = row;
        while (pivotRow < numRows && matrix[pivotRow][lead] == 0) {
            pivotRow++;
        }
        if (pivotRow == numRows) {
            lead++;
            row--;
            continue;
        }

        // Переставляем строки
        if (pivotRow != row) {
            swapRows(matrix, row, pivotRow);
        }

        // Делим текущую строку на ведущий элемент
        double pivot = matrix[row][lead];
        if (pivot != 1.0) {
            for (int col = 0; col < numCols; col++) {
                matrix[row][col] /= pivot;
            }
        }

        // Обнуляем остальные элементы столбца
        for (int i = 0; i < numRows; ++i) {
            if (i != row) {
                double factor = matrix[i][lead];
                for (int j = 0; j < numCols; j++) {
                    matrix[i][j] -= factor * matrix[row][j];
                }
            }
        }
        lead++;
    }

    //Заменяем -1 на 1 
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == -1) {
                matrix[i][j] = 1;
            }
        }
    }

    return matrix;
}
// Нахождение проверочной матрицы H
vector<vector<int>> findH(const vector<vector<int>>& G) {
    int k = G.size();
    int n = G[0].size();
    int r = n - k; 

    vector<vector<int>> H;
    vector<int> row(n, 0);

    for (int j = 0; j < r; ++j) {
        H.push_back(row);
    }
    vector<vector<int>> GTransposed = transpose(G);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < k; j++) {
            H[i][j] = GTransposed[i+ k][j];
        }
    }
    for (int j = 0; j < r; j++) {

        H[j][k + j] = 1;
    }

    return H;
}
// Вес Хэмминга
int hammingWeight(const vector<int>& a) {
    int weight = 0;

    for (int val : a) {
        if (val)
            weight++;
    }

    return weight;
}
//Вес кода
int findMinWt(const vector<vector<int>>& G) {
    int rows = G.size();
    int cols = G[0].size();
    int minCounter = G[0].size() + 1;

    for (int i = 0; i < rows; ++i) {
        int counter = 0;
        for (int j = 0; j < cols; ++j) {
            if (G[i][j] != 0) {
                counter++;
            }
        }
        minCounter = min(counter, minCounter);
        
    }

    return minCounter;
}

//расстояние Хэминга
int hammingDistance(int a, int b) {
    int xorResult = a ^ b;
    int distance = 0;

    while (xorResult > 0) {
        distance += xorResult & 1;
        xorResult >>= 1;
    }

    return distance;
}

//Расстояние Хэмминга для векторов одинаковой длины
int hammingDistanceVec(const vector<int>& A, const vector<int>& B) {
    int distance = 0;

    for (size_t i = 0; i < A.size(); ++i) {
        if (A[i] != B[i]) {
            distance++;
        }
    }

    return distance;
}
// Расстояние Хэмминга для кода
int calculateAllHammingDistances(const vector<vector<int>>& matrix) {
    int numRows = matrix.size();
    int cols = matrix[0].size();
    int minHamming = matrix[0].size() + 1;

    for (int i = 0; i < numRows; ++i) {
        for (int j = i + 1; j < numRows; ++j) {
            minHamming = min(hammingDistanceVec(matrix[i], matrix[j]), minHamming);
        }
    }

    return minHamming;
}
// кодовое расстояние
int codeDistance(const vector<vector<int>>& matrix) {
    int Weight = findMinWt(matrix);
    int hamming = calculateAllHammingDistances(matrix);

    return min(Weight, hamming);
}

// максимальное количество обнаруживаемых ошибок
int maxDetectableErrors(const vector<vector<int>>& matrix) {
    int distance = codeDistance(matrix);

    if (distance <= 1) {
        return 0;
    }

    return distance - 1;
}
// максимальное количество исправляемых ошибок
int correctableErrors(const vector<vector<int>>& matrix) {
    int distance = codeDistance(matrix);

    if (((distance - 1) / 2) < 0) {
        return 0;
    }

    return ((distance - 1) / 2);
}

// Синдром - Результат умножения принятого кодового слова на проверочную матрицу H^T.
vector<int> codeSyndrome(const vector<int>& word, const vector<vector<int>>& H) {
    vector<vector<int>> word_matrix;

    word_matrix.push_back(word);
    vector<vector<int>> syndrome_matrix = matrixMultiply(word_matrix, transpose(H));

    return syndrome_matrix[0];
}

// Умножение строки на скаляр (mod 2)
void multiplyRow(vector<int>& row, int scalar) {
    for (int& elem : row) {
        elem = (elem * scalar) % 2;
    }
}
//Функция сложения строк по модулю 2
void addRows(vector<int>& dest, const vector<int>& src) {
    for (size_t i = 0; i < dest.size(); ++i) {
        dest[i] = (dest[i] + src[i]) % 2;
    }
}

// Функция для нахождения лидеров синдромов
map<vector<int>, vector<int>> findSyndromeLeaders(const vector<vector<int>>& H) {
    int n;
    if (H.size() > 0) {
        n = H[0].size();
    }
    else {
        n = 0;
    }
    map<vector<int>, vector<int>> syndrome_leaders;

    for (int i = 0; i < (1 << n); ++i) {
        vector<int> error(n);
        for (int j = 0; j < n; ++j) {
            error[n - j - 1] = (i >> j) & 1;
        }
        vector<int> syndrome = codeSyndrome(error, H);

        if (syndrome_leaders.find(syndrome) == syndrome_leaders.end()) {
            syndrome_leaders[syndrome] = error;
        }
        else {
            if (hammingWeight(error) < hammingWeight(syndrome_leaders[syndrome]))
                syndrome_leaders[syndrome] = error;
        }
    }

    return syndrome_leaders;
}
// Возвращает значение сложения векторов по модулю 2
vector<int> vectorAddMod2(const vector<int>& A, const vector<int>& B) {
    if (A.size() != B.size()) {
        cerr << "Error: Vectors must have the same size for addition." << endl;
        return {};
    }
    vector<int> result(A.size());
    for (size_t i = 0; i < A.size(); ++i) {
        result[i] = (A[i] + B[i]) % 2;
    }

    return result;
}
// Исправление ошибок
vector<vector<int>> fixErrors(vector<vector<int>>& GNew, const vector<vector<int>>& H) {
    if (correctableErrors(GNew) < 1) {
        cout << "Errors cannot be corrected";
        return GNew;
    }

    vector<vector<int>> syndromeMatrix;

    for (int i = 0; i < GNew.size(); i++) {
        vector<int> syndrome = codeSyndrome(GNew[i], H);
        syndromeMatrix.push_back(syndrome);
    }
    map<vector<int>, vector<int>> leaders = findSyndromeLeaders(H);

    for (size_t i = 0; i < GNew.size(); ++i) {
        for (const auto& syndrome_leader : leaders) {
            if (syndromeMatrix[i] == syndrome_leader.first) {
                GNew[i] = vectorAddMod2(GNew[i], syndrome_leader.second);
                break;
            }
        }
    }

    return GNew;
}
//Вывод матрицы
void print(const vector<vector<int>>& G) {
    for (const auto& row : G) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}
// Функция для чтения матрицы из файла
vector<vector<int>> readMatrixFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << filename << endl;
        return {}; // Возвращаем пустую матрицу, если не удалось открыть файл
    }

    int numRows, numCols;
    if (!(file >> numRows >> numCols)) {
        std::cerr << "Error: Could not read dimensions from file." << endl;
        file.close();
        return {};
    }

    vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols));
    std::string line;
    std::getline(file, line); // Читаем пустую строку после измерений

    for (int i = 0; i < numRows; ++i) {
        if (!getline(file, line)) {
            std::cerr << "Error: Could not read line " << i + 1 << " from the file." << std::endl;
            file.close();
            return {};
        }
        std::istringstream iss(line);
        for (int j = 0; j < numCols; ++j) {
            if (!(iss >> matrix[i][j])) {
                std::cerr << "Error: Could not read matrix value at row " << i + 1 << " column " << j + 1 << std::endl;
                file.close();
                return {};
            }
        }
    }
    file.close();
    return matrix;
}


int main() {

    // Исходное сообщение
    string filename = "sentMatrix.txt"; 
    vector<vector<int>> G = readMatrixFromFile(filename);

    // Полученное сообщение
    filename = "gotMatrix.txt"; 
    vector<vector<int>> GGot = readMatrixFromFile(filename);

    // Приведение отправленного сообщения к каноничному виду
    vector<vector<int>> GNew = toCanonicalForm(G);

    // Вычисляем проверочную матрицу H
    vector<vector<int>> H = findH(GNew);

    // Выводим матрицу H
    cout << "Matrix H:" << endl;
    print(H);
    cout << endl;

    cout << "Hamming Distance: " << calculateAllHammingDistances(G) << endl;
    cout << "Code Distance: " << codeDistance(G) << endl;
    cout << "The maximum number of errors to be detected: " << maxDetectableErrors(G) << endl;
    cout << "The maximum number of errors to be corrected: " << correctableErrors(G) << endl;
    cout << endl;

    vector<vector<int>> syndromeMatrix;
    for (int i = 0; i < GGot.size(); i++) {
        vector<int> syndrome = codeSyndrome(GGot[i], H);
        syndromeMatrix.push_back(syndrome);
    }

    // Выводим синдромы кода
    cout << "Code syndrome: " << endl;
    print(syndromeMatrix); 
    cout << endl;

    map<vector<int>, vector<int>> leaders = findSyndromeLeaders(H);

    // Выводим лидеры синдромов
    cout << "Syndrome leaders:" << endl;
    for (const auto& pair : leaders) {
        cout << "Syndrome: ";
        for (int val : pair.first) {
            cout << val << " ";
        }
        cout << ", Leader: ";
        for (int val : pair.second) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Если количество исправляемых ошибок больше 0, то исправляем их и выводим полученную матрицу, которая будет совпадать с G
    if (correctableErrors(G) > 0) {
        vector<vector<int>> fixed = fixErrors(GGot, H);

        cout << "Corrected code:" << endl;
        print(fixed);
    }
    else {
        cout << "Errors cannot be fixed";
    }
    
    return 0;
}
