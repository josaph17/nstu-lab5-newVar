/*11. —ортировка Ухитра€Ф.»з массива путем однократного просмотра выбираетс€ последовательность элементов,
наход€щихс€ в пор€дке возрастани€, перенос€тс€ в выходной массив и замен€ютс€ во входном на У-1Ф. «атем
оставшиес€ элементы включаютс€ в полученную упор€доченную последовательность методом погружени€.*/
#include <stdio.h>
#include <locale.h>
#define N 8

void ShowArray(int A[], int n);
int habrLength(int numbers[], int n);
int main()
{
	setlocale(LC_ALL, "");
	int Arr[N] = { 5, 10,6,12,3,24,7,8};
	printf("First array Arr: \n");
	ShowArray(Arr, N);
    int length = habrLength(Arr, N);
    printf("ƒлина максимально длинной послед-и: %d\n", length);	 //max length: %d
	return 0;
}

void ShowArray(int A[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}

int habrLength(int numbers[], int n) 
{
    int indexes[N];
    for (int i = 0; i < n; ++i)
        indexes[i] = 0;

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) {
            if (numbers[j] > numbers[i]) {
                if (indexes[j] <= indexes[i]) {
                    indexes[j] = indexes[i] + 1;
                }
            }
        }
    }
    ShowArray(indexes, N);

    int maximum = 0;

    for (int i = 0; i < n; ++i)
    {
        if (maximum < indexes[i])
            maximum = indexes[i];
    }

    return maximum+1;
}