/*11. —ортировка Ухитра€Ф.»з массива путем однократного просмотра выбираетс€ последовательность элементов,
наход€щихс€ в пор€дке возрастани€, перенос€тс€ в выходной массив и замен€ютс€ во входном на У-1Ф. «атем
оставшиес€ элементы включаютс€ в полученную упор€доченную последовательность методом погружени€.*/
#include <stdio.h>
#include <locale.h>
#include <limits.h>
#define N 8

void ShowArray(int A[], int n);
void habrLength(int arr[], int n);
void recoverSeq(int in[], int indexes[], int n, int max);
int main()
{
	setlocale(LC_ALL, "");
	int Arr[N] = { 5, 10,6,12,3,24,7,8};
	printf("First array Arr: \n");
	ShowArray(Arr, N);
    habrLength(Arr, N);
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

void habrLength(int arr[], int n)
{
    int counts[N];
    for (int i = 0; i < n; ++i)
        counts[i] = 0;

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) { 
            if (arr[j] > arr[i]) {
                if (counts[j] <= counts[i]) { /*if index of sequence >= i*/
                    counts[j] = counts[i] + 1; /*index of element of growing subSequence, which finished on this element*/
                }
            }
        }
    }
   
    int maximum = 0;

    for (int i = 0; i < n; ++i)
    {
        if (maximum < counts[i])
            maximum = counts[i];
    }

    printf("\n¬еличина максимального индекса: %d\n", maximum);	 //max length: %d

    recoverSeq(arr, counts, n, maximum);
}

void recoverSeq(int in[], int indexes[],  int n, int max)
{
    int out[N];

    for (int i = 0; i < n; ++i)
        out[i] = INT_MIN;

    int p=0;
    int last = INT_MIN;

    printf("\nin[] : \n");
    ShowArray(in, n);
    printf("indexes[] : \n");
    ShowArray(indexes, n);

    for (int j = 0; j < n-1; j++)
    {
        for (int r = j+1; r < n; r++) 
        {
            if (indexes[r] <= max)
            {
                if ((indexes[j] < indexes[r]) && (in[j] > last))
                {
                    out[p] = in[j];
                    last = out[p];
                    p++;
                }
                else if ((in[j] > last)) /*if index = last*/
                {
                    out[p] = in[j];
                }
            }
        }
            
    }

    printf("\nRecover Sequence out[]: \n");
    ShowArray(out, N);
}