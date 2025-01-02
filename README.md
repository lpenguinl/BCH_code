# Код Боуза — Чоудхури — Хоквингема
В теории кодирования это широкий класс циклических кодов, применяемых для защиты информации от ошибок. Отличается возможностью построения кода с заранее определёнными корректирующими свойствами, а именно, минимальным кодовым расстоянием. Они позволяют исправлять любое фиксированное число ошибок над двухбуквенным алфавитом.
# Входные и выходные данные
Программа читает из файлов sentMatrix.txt и gottMatrix.txt размер матриц и сами матрицы, которые являются отправленным и полученным сообщением соответственно. 

В консоль выводится проверочная матрица H, и характеристики сообщения: расстояние Хэмминга, кодовое расстояние, максимальное количество обнаруживаемых и исправляемых ошибок.
Затем обрабатывается полученное сообщение и выводятся синдромы кода и таблица лидеров, соответствующих каждому синдрому.
Если это возможно, выводится сообщение с исправленными ошибками.

# Описание методов 
1. **vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B)** - Возвращает матрицу, которая является результатом умножения матрицы A на матрицу B;
2. **vector<vector<int>> transpose(const vector<vector<int>>& matrix)** - Возвращает транспонированную матрицу matrix;
3. **void swapRows(vector<vector<int>>& matrix, int row1, int row2)** - меняет строки row1 и row2 местами в матрице matrix;
4. **vector<vector<int>> toCanonicalForm(const vector<vector<int>>& originalMatrix)** - приводит матрицу originalMatrix к каноническому виду (приведенно-ступенчатой форме);
<p align="center">
<img width="150" alt="image" src="https://github.com/user-attachments/assets/474e72da-bb5f-4dec-9253-9beddb7becbb" />
</p>

   Матрица G состоит из единичной матрицы порядка k и G* – проверочной части порождающей матрицы размером k(n–k).
   n - количество столбцов, k - количество строк.

5. **vector<vector<int>> findH(const vector<vector<int>>& G)** - Нахождение проверочной матрицы H;

<p align="center">
<img width="150" alt="image" src="https://github.com/user-attachments/assets/d6dd2652-1817-440e-a70d-e4d4be3fd89e" />
</p>

   Связь между проверочной матрицей H и порождающей матрицей G. Знак T обозначает транспонирование, а 0 – нулевая матрица порядка k.
   Проверочная матрица H имеет размеры r*n.

   Если порождающая матрица задана в каноническом виде, то проверочная матрица может быть найдена путем транспонирования подматрицы G и добавления справа единичной матрицы порядка r = n - k:
<p align="center">
<img width="242" alt="image" src="https://github.com/user-attachments/assets/b00f9a5a-bb29-4d09-8742-70648e29b813" />
</p>

6. **int findMinWt(const vector<vector<int>>& G)** - нахождение веса Хэмминга матрицы G;
   Весом Хэмминга вектора c называется количество его ненулевых разрядов. Например, wt(1001011) = 4, wt(0000000) = 0.
   
7. **int hammingDistanceVec(const vector<int>& A, const vector<int>& B)** - Нахождение расстояния Хэмминга для матриц A и B;

   Расстоянием Хэмминга d(c1,c2) между двумя векторами c1 и c2 Иназывается вес их разности d(c1,c2) = wt(c1–c2). Например, d(1001, 1011) = wt(0010).
   Видно, что расстояние Хэмминга равно количеству попарно несовпадающих разрядов векторов.
    
9. **int calculateAllHammingDistances(const vector<vector<int>>& matrix)** - Нахождение минимального расстояния Хэмминга между строками матрицы matrix;
   
10. **int codeDistance(const vector<vector<int>>& matrix)** - Нвхождение кодового расстояния для матрицы matrix;

    Для нахождения кодового расстояния необходимо найти минимальный вес строк G и минимальное расстояние Хэмминга между всеми строками G. Тогда кодовое расстояние равно минимальному из этих значений.
   
11. **int maxDetectableErrors(const vector<vector<int>>& matrix)** - Вычисление максимального количества обнаруживаемых ошибок;

   Число обнаруживаемых ошибок связано с кодовым расстоянием данной формулой:
   <p align="center">
<img width="150" alt="image" src="https://github.com/user-attachments/assets/8e0e455a-eeb7-4f45-8ffc-83cb984e2c82" />
</p>

11. **int correctableErrors(const vector<vector<int>>& matrix)** - Вычисление максимального количества исправляемых ошибок;
   
      Число исправляемых ошибок связано с кодовым расстоянием данной формулой:
<p align="center">
<img width="150" alt="image" src="https://github.com/user-attachments/assets/3bd90ede-b233-4732-bd01-04b1f206a617" />
</p>

12. **vector<int> codeSyndrome(const vector<int>& word, const vector<vector<int>>& H)** - Нахождение синдромов кода;

   Для обнаружения и исправления ошибок используется синдромный метод декодирования.
   Синдром - Результат умножения принятого кодового слова на транспонированную матрицу H. Если синдром равен нулю, то ошибок нет.
   
13. **map<vector<int>, vector<int>> findSyndromeLeaders(const vector<vector<int>>& H)** - нахождение лидера для каждого синдрома;

   Класс смежности - множество искаженных кодовых слов, имеющих один и тот же синдром.
   Лидер синдрома - это кодовое слово, имеющее наименьший вес Хэмминга среди всех элементов этого класса. 
   Выбор лидера синдрома позволяет допределить, какая ошибка наиболее вероятно произошла во время передачи.
   
14. **void multiplyRow(vector<int>& row, int scalar)** - Умножение строки на скаляр по модулю 2;
    
15. **vector<int> vectorAddMod2(const vector<int>& A, const vector<int>& B)** - Сложение матриц по модулю 2;
    
16. **vector<vector<int>> fixErrors(vector<vector<int>>& GGot, const vector<vector<int>>& H)** - Исправление ошибок в переданном сообщение GGot;

    Если количество исправляемых ошибок равно 0, то ничего не исправляется.
    Иначе каждый синдром кода складывается с соответствующим ему лидером (нулевому синдрому соответсвует нулевой лидер, поэтому такое сложение не изменит матрицу).
    
17. **void print(const vector<vector<int>>& G)** - Вывод матрицы в консоль;
    
18. **vector<vector<int>> readMatrixFromFile(const string& filename)** - Чтение матрицы из файла.

# Алгоритм исправления ошибок 
   1. Чтение из файла порождающей матрицы G и полученного сообщения GGot
   2. Приведение порождающей матрицы G к каноничному виду
   3. Нахождение проверочной матрицы H
   4. Вычисление расстояния Хэмминга
   5. Вычисление кодового расстояния
   6. Вычисление максимального количества обнаруживаемых ошибок
   7. Вычисление максимального количества исправляемых ошибок
   8. Нахождение синдромов
   9. Нахождение лидеров для каждого синдрома 
   10. Исправление ошибок, если это возможно


