#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>


double get_rand_range(int min, int max) {
    return rand() * 1.0 / RAND_MAX * (max - min) + min;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int N, min, max, temp, ost;
    double sum = 0, num, r = 0; // r - итоговая сумма элементов массива, которую в конце нужно будет вычесть
    double* mas;

    printf("Введите количество чисел, которые вы хотите сгенерировать:\n");
    scanf_s("%d", &N);

    printf("Введите диапазон значений, начиная с минимального:\n");
    scanf_s("%d %d", &min, &max);
    printf("\n");

    if (min > max) { // Проверка введённых значений
        temp = max;
        max = min;
        min = temp;
    }

    mas = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        mas[i] = get_rand_range(min, max); // Генерируем рандомное число в заданном диапазоне

        printf("%lf | ", mas[i]);

        num = ((mas[i] - (int)mas[i]) * pow(10, 7)); // Отделяем дробную часть числа, для дальнейшей работы над ней
        ost = (int)num; 
        if (ost % 10 >= 5) ost = (ost / 10) + 1; // Округление для точности дробной части числа
        else ost /= 10;

        if ((ost == 0) && (mas[0] != 0)) { // В частном случае, если остаток равен 0, выполняем ещё одно условие
            r += mas[0];  
            mas[0] = 0; // Зануляем для того, чтобы вычитание происходило только один раз
        }
        else {
            while (ost % 10 == 0) ost /= 10; // Убираем лишние нули дробной части
            printf("%d\n", ost); // В консоли справа от '|' Выводится дробная часть числа для наглядности
            if ((ost < N) && (mas[ost] != 0)) { 
                r += mas[ost]; // В переменную r заносим элементы массива, чтобы в конце вычесть всю необходимую разность
                mas[ost] = 0; // Зануляем для того, чтобы вычитание происходило только один раз
            }
        }

    }
    for (int i = 0; i < N; i++) sum += mas[i]; // Считаем сумму элементов массива и вычитаем получившееся число
    sum -= r;
    printf("Итоговая сумма = %g\n", sum);
    free(mas);
    system("pause");
    return 0;
}