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
void reverseSeq(int *in, int n);
void compareArrs(int *in, int in2[], int n, int n2);
void VictorRecoverSeq(int* in, int indexes[], int n, int max);

int main()
{
	setlocale(LC_ALL, "");

    //int Arr[N] = { 5,10,6,12,3,24,25,7,8 };
	//int Arr[N] = { 5,10,6,12,3,24,7,8};
    int Arr[N] = { 5,10,6,12,3,7,8,24 };

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

    VictorRecoverSeq(arr, counts, n, maximum);

    printf("Changed Arr[]: \n");
    ShowArray(arr, N);
}

void reverseSeq(int *in, int n)
{
    int i, j, k;
    for (i = 0, j = n - 1; i < j; i++, j--)
    {
        k = in[i];
        in[i] = in[j]; 
        in[j] = k;
    }
}

void compareArrs(int* in, int in2[], int n, int n2)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n2; j++)
            if (in[i] == in2[j])
                in[i] = -1;
}

void VictorRecoverSeq(int* in, int indexes[], int n, int max)
{
    int* out = (int*)malloc(max * sizeof(int));

    if (NULL == out) /*check pointer, cause pointer can return malloc */
        return NULL; /*OS don't gave memory*/

    int j;
    int attn=0;
    int maxIndex = max - 1; /*value of max index  in indexes[]*/
    int last_index;
    int last_out;

    for (j = n - 1; attn!=1; j--)
        if (indexes[j] == maxIndex)
        {
            last_index = indexes[j];
            out[maxIndex] = in[j];
            last_out = out[last_index];
            attn = 1;
        }

    for (j; j >= 0; j--)
        if ((indexes[j]+1 == last_index) && (in[j]< last_out))
        {
            last_index = indexes[j];
            out[last_index] = in[j];
            last_out = out[last_index];
        }

    printf("\nRecover Sequence out[]: \n");
    ShowArray(out, max);
    compareArrs(in, out, n, max); 
}