# Код Боуза — Чоудхури — Хоквингема
В теории кодирования это широкий класс циклических кодов, применяемых для защиты информации от ошибок. Отличается возможностью построения кода с заранее определёнными корректирующими свойствами, а именно, минимальным кодовым расстоянием. Они позволяют исправлять любое фиксированное число ошибок над двухбуквенным алфавитом.
# Входные и выходные данные
Программа читает из файлов sentMatrix.txt и gottMatrix.txt размер матриц и сами матрицы, которые являются отправленным и полученным сообщением соответственно. 

В консоль выводится проверочная матрица H, и характеристики сообщения: расстояние Хэмминга, кодовое расстояние, максимальное количество обнаруживаемых и исправляемых ошибок.
Затем обрабатывается полученное сообщение и выводятся синдромы кода и таблица лидеров, соответствующих каждому синдрому.
Если это возможно, выводится сообщение с исправленными ошибками.

# Описание методов 
1. vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) - Возвращает матрицу, которая является результатом умножения матрицы A на матрицу B;
2. vector<vector<int>> transpose(const vector<vector<int>>& matrix) - Возвращает транспонированную матрицу matrix;
3. void swapRows(vector<vector<int>>& matrix, int row1, int row2) - меняет строки row1 и row2 местами в матрице matrix;
4. vector<vector<int>> toCanonicalForm(const vector<vector<int>>& originalMatrix) - приводит матрицу originalMatrix к каноническому виду (приведенно-ступенчатой форме);

   ![image](https://github.com/user-attachments/assets/3eeafe54-a2d7-4201-b58b-aa47b3c818a0)
   Матрица G состоит из единичной матрицы порядка k и G* – проверочной части порождающей матрицы размером k*(n–k).

7. vector<vector<int>> findH(const vector<vector<int>>& G)
8. int findMinWt(const vector<vector<int>>& G)
9. int hammingDistance(int a, int b)
10. int hammingDistanceVec(const vector<int>& A, const vector<int>& B)
11. int calculateAllHammingDistances(const vector<vector<int>>& matrix)
12. int codeDistance(const vector<vector<int>>& matrix)
13. int maxDetectableErrors(const vector<vector<int>>& matrix)
14. int correctableErrors(const vector<vector<int>>& matrix)
15. vector<int> codeSyndrome(const vector<int>& word, const vector<vector<int>>& H)
16. void addRows(vector<int>& dest, const vector<int>& src)
17. map<vector<int>, vector<int>> findSyndromeLeaders(const vector<vector<int>>& H)
18. vector<int> vectorAddMod2(const vector<int>& A, const vector<int>& B)
19. vector<vector<int>> fixErrors(vector<vector<int>>& GNew, const vector<vector<int>>& H)
20. void print(const vector<vector<int>>& G)
21. vector<vector<int>> readMatrixFromFile(const string& filename)
