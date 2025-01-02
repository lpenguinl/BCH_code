# Код Боуза — Чоудхури — Хоквингема
В теории кодирования это широкий класс циклических кодов, применяемых для защиты информации от ошибок. Отличается возможностью построения кода с заранее определёнными корректирующими свойствами, а именно, минимальным кодовым расстоянием. Они позволяют исправлять любое фиксированное число ошибок над двухбуквенным алфавитом.
# Входные и выходные данные
Программа читает из файлов sentMatrix.txt и gottMatrix.txt размер матриц и сами матрицы, которые являются отправленным и полученным сообщением соответственно. 

В консоль выводится проверочная матрица H, и характеристики сообщения: расстояние Хэмминга, кодовое расстояние, максимальное количество обнаруживаемых и исправляемых ошибок.
Затем обрабатывается полученное сообщение и выводятся синдромы кода и таблица лидеров, соответствующих каждому синдрому.
Если это возможно, выводится сообщение с исправленными ошибками.
