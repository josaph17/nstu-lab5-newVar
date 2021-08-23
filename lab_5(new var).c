/*11. —ортировка Ухитра€Ф.»з массива путем однократного просмотра выбираетс€ последовательность элементов,
наход€щихс€ в пор€дке возрастани€, перенос€тс€ в выходной массив и замен€ютс€ во входном на У-1Ф. «атем
оставшиес€ элементы включаютс€ в полученную упор€доченную последовательность методом погружени€.*/
#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <malloc.h>

#define N 8  

void cleverSort(int *in, int* in2, int n);
void ShowArray(int in[], int n);
void recoverRisingSubSeq(int in[], int* in2, int indexes[], int n, int maxIndex);
void compareArrsAddMinus1(int* in, int in2[], int n);
void swap(int *a, int *b);
void immersionSort0(int in[], int left, int n);
void immersionSort(int out[], int in[], int sortedIndex, int n);

int main()
{
	setlocale(LC_ALL, "");

    //int Arr[N] = { 5,10,6,12,3,24,25,7,8 };
	//int Arr[N] = { 5,10,6,12,3,24,7,8};
    int Arr[N] = { 5,10,6,12,3,7,8,24 };
    int Arr2[N];

    cleverSort(Arr,Arr2, N);

	return 0;
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

    printf("Arr[]: \n");
    ShowArray(in, n);
    printf("counts[]: \n");
    ShowArray(counts, n);
    
    printf("\nCount of elements in max rising subSeq: %d\n", maximum+1);

    recoverRisingSubSeq(in, in2, counts, n, maximum); 

    compareArrsAddMinus1(in, in2, n);
    //-----------------------------
    printf("\nChanged Arr[]: \n");
    ShowArray(in, n);
    printf("After recoverRisingSubSeq Arr2[]: \n");
    ShowArray(in2, n);

    immersionSort(in2, in, maximum, n);
    printf("After immersionSort Arr2[]: \n");
    ShowArray(in2, n);
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

void recoverRisingSubSeq(int in[], int* in2, int indexes[], int n, int maxIndex)
{
    int j;
    int attn=0;
    int last_index;
    int last_out;

    for (j = n - 1; attn!=1; j--)
        if (indexes[j] == maxIndex)
        {
            last_index = indexes[j];
            in2[maxIndex] = in[j];
            last_out = in2[last_index];
            attn = 1;
        }

    for (j; j >= 0; j--)
        if ((indexes[j]+1 == last_index) && (in[j]< last_out))
        {
            last_index = indexes[j];
            in2[last_index] = in[j];
            last_out = in2[last_index];
        }
}

void compareArrsAddMinus1(int* in, int in2[], int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; j++)
            if (in[i] == in2[j])
                in[i] = -1;
}

void swap(int *a, int *b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
void immersionSort(int out[], int in[], int sortedIndex, int n)  
{
    int 	i, j, k, c;
    for (i = sortedIndex+1; i < n; ) /*по массиву in2 бежим*/
    {
        for (k = 0; k < n; k++) /*дл€ массива in, который содержит -1*/
        {
            if (in[k] != -1)
            {
                out[i] = in[k];
                i++;
            }        
        }
    }
    immersionSort0(out, sortedIndex + 1, n);
}

void immersionSort0(int in[], int left, int n)  /*¬ставка погружением, по bk35 текст в вопросах без ответов*/   //но у хирь€нова это обычна€ вставка
/*очередной элемент путем р€да обменов Упогружаетс€Ф до требуемой позиции в уже упор€доченную часть массива*/
{
    int 	i, j, k, c;
    for (i = left; i < n; i++)
    {
        for (k = i; k != 0; k--) /*к-- дл€ того чтобы дальше погружать в отсорт часть, пока не встанет на место*/
        {
            if (in[k] > in[k - 1]) /*если очередной элемент больше пред. отсорт. - выходим*/
                break;
            c = in[k];
            in[k] = in[k - 1];
            in[k - 1] = c;
        }
    }
}