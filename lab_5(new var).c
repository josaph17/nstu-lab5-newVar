/*11. —ортировка Ухитра€Ф.»з массива путем однократного просмотра выбираетс€ последовательность элементов,
наход€щихс€ в пор€дке возрастани€, перенос€тс€ в выходной массив и замен€ютс€ во входном на У-1Ф. «атем
оставшиес€ элементы включаютс€ в полученную упор€доченную последовательность методом погружени€.*/
#include <stdio.h>
#include <malloc.h>

#define N 8  

void ShowArray(int in[], int n);
void cleverSort(int *in, int* in2, int n);
void RecoverSubSeqAddMinus1(int in[], int* in2, int indexes[], int n, int maxIndex);
void TransferDigits(int out[], int in[], int sortedIndex, int n);
void immersionSort(int in[], int left, int n);

int main()
{
    //int Arr[N] = { 5,10,6,12,3,24,25,7 };
    //int Arr[N] = { 0,0,0,0,0,0,0 }; // 1. All digits is equal
	//int Arr[N] = { 1,2,3,4,5,6,7,8};          //2. Rising Arr
    /*int Arr[N] = { 7,6,5,4,3,2,1,0 };*/  //3. Decreasing Arr
    //int Arr[N] = { 5,10,6,12,3,7,8,24 };
    int Arr[N] = { 24,3,6,12,3,7,8,24 }; /*2 pairs of identical numbers*/
    int Arr2[N];

    cleverSort(Arr,Arr2, N);

    printf("\nChanged Arr[]: \n");
    ShowArray(Arr, N);
    printf("After cleverSort Arr2[]: \n");
    ShowArray(Arr2, N);
	return 0;
}

void ShowArray(int in[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", in[i]);
    }
    printf("\n");
}

void cleverSort(int* in, int* in2, int n)
{
    int counts[N];
    for (int i = 0; i < n; ++i)
        counts[i] = 0;

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) { 
            if (in[j] > in[i]) {
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
    //printf("\nCount of elements in max rising subSeq: %d\n", maximum+1);
    printf("counts[]: \n");
    ShowArray(counts, n);
    
    RecoverSubSeqAddMinus1(in, in2, counts, n, maximum);
    printf("\nAfter RecoverSubSeqAddMinus1 Arr2[]: \n");
    ShowArray(in2, n);
  
    TransferDigits(in2, in, maximum, n);
}

void RecoverSubSeqAddMinus1(int in[], int* in2, int indexes[], int n, int maxIndex)
{
    int j;
    int attn=0;
    int last_index;
    int last_out;

    for (j = n - 1; attn!=1; j--)
        if (indexes[j] == maxIndex) /*choose first indexes[j] == maxIndex*/
        {
            last_index = indexes[j];
            in2[maxIndex] = in[j];
            last_out = in2[last_index];
            in[j] = -1; /*change in[]*/
            attn = 1;
        }

    for (j; j >= 0; j--)
        if ((indexes[j]+1 == last_index) && (in[j]< last_out))
        {
            last_index = indexes[j];
            in2[last_index] = in[j];
            in[j] = -1;
            last_out = in2[last_index];
        }
}

void TransferDigits(int out[], int in[], int sortedIndex, int n)  
{
    int 	i, j, k, c;
    for (i = sortedIndex+1; i < n; )
    {
        for (k = 0; k < n; k++)
        {
            if (in[k] != -1)
            {
                out[i] = in[k];
                i++;
            }        
        }
    }
    immersionSort(out, sortedIndex + 1, n);
}

void immersionSort(int in[], int left, int n)  
{
    int 	i, j, k, c;
    for (i = left; i < n; i++)
    {
        for (k = i; k != 0; k--) /*к - to do next immersion in sorted piece,
                                 while he don't take his place*/
        {
            if (in[k] > in[k - 1]) /*if regular item bigger than previous sorted*/
                break;
            c = in[k];
            in[k] = in[k - 1];
            in[k - 1] = c;
        }
    }
}