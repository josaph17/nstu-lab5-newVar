/*11. —ортировка Ухитра€Ф.»з массива путем однократного просмотра выбираетс€ последовательность элементов,
наход€щихс€ в пор€дке возрастани€, перенос€тс€ в выходной массив и замен€ютс€ во входном на У-1Ф. «атем
оставшиес€ элементы включаютс€ в полученную упор€доченную последовательность методом погружени€.*/
#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <malloc.h>

#define N 8

void ShowArray(int A[], int n);
void cleverSort(int arr[], int n);
int createRecoverSeq(int *in, int indexes[], int n, int max);

int main()
{
	setlocale(LC_ALL, "");

	int Arr[N] = { 5, 10,6,12,3,24,7,8};

    cleverSort(Arr, N);

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

void cleverSort(int arr[], int n)
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

    printf("Arr[]: \n");
    ShowArray(arr, n);
    printf("counts[]: \n");
    ShowArray(counts, n);
    
    maximum++; /*count of elements in rising subSeq*/

    printf("\nCount of elements in max rising subSeq: %d\n", maximum);

    int seq = createRecoverSeq(arr, counts, n, maximum);

    printf("\nArray from createRecoverSeq: \n");
    ShowArray(seq, maximum);
    printf("Changed Arr[]: \n");
    ShowArray(arr, N);
}

int createRecoverSeq(int *in, int indexes[],  int n, int max)
{
    int *out = (int*)malloc(max * sizeof(int));

    if (NULL == out) /*check pointer, cause pointer can return malloc */
        return NULL; /*OS don't gave memory*/

    for (int i = 0; i < max; i++)
        out[i] = INT_MIN;

    int maxIndex = max - 1; /*value of max index  in indexes[]*/

    int p = 0;
    int last = INT_MIN;

    for (int j = 0; j < n-1; j++)
    {
        for (int r = j+1; r < n; r++) 
        {
            if (indexes[r] <= maxIndex)
            {
                if ((indexes[j] < indexes[r]) && (in[j] > last))
                {
                    out[p] = in[j];
                    in[j]= -1;
                    last = out[p];
                    p++;
                }
                else if ((indexes[j]== maxIndex) && (in[j] > last)) /*if index = maxIndex =3*/
                {
                    out[p] = in[j];
                    in[j] = -1;
                }
            }
        }
    }

    return out;
}