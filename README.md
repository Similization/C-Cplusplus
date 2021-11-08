Описание
Взаимодействие приложения с операционной системой (ОС) семейства UNIX. Многопоточное программирование с использованием потоков POSIX. Работа с разделяемой памятью. Линковщик и внешние библиотеки. Оптимизация работы с оперативной и кэш-памятью ЦП ЭВМ.

Домашнее задание №2: ИЗ №2
До 9 ноября, 18:00 (осталось 7 дней)Максимум 15 балловКритерии
К семинару №2 необходимо индивидуально решить ИЗ2 по программированию на С в соответствии с назначенным вариантом.

ИЗ2 посвящено приобретению навыков системной разработки на C и работы с внешними библиотеками. В качестве результата ИЗ2 ожидается:
* грамотное разбиение проекта на файлы;
* наличие двух реализаций – последовательной и параллельной, оформленных в виде статической и динамической библиотек соответственно, а также тестирующей программы, которая будет сравнивать на разных входных данных результаты обеих реализаций между собой;
* максимальная утилизация ресурсов процессора при параллельной обработке данных путём использования нескольких процессов или потоков;
* продуманные структуры данных в целях экономии оперативной памяти;
* реализация алгоритмов, эффективно взаимодействующих с кэш-памятью.

Вариант #21
В Вашем распоряжении результаты экспериментов, которые представляют собой массив из 100 млн вещественных чисел. Требуется построить модель линейной регрессии, которая бы объясняла эти данные, с помощью метода наименьших квадратов. Реализуйте последовательный алгоритм решения этой задачи, а затем распараллельте его с использованием нескольких потоков.

