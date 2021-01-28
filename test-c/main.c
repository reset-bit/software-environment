#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define N 10
/*
对于初始给定的数组，通常存在多个长度大于1，且已自然排好序的子数组段。

自然合并排序用一次对数组的线性扫描，就足以找出所有这些排好序的子数组段。

然后将相邻的排好序的子数组段两两合并，构成更大的排好序的子数组段。继续合并相邻排好序的子数组段，直至整个数组已排好序
*/
int subarr[N] = {0};

void getLengthOfOrderedSubarray(int *arr, int len){
    int s = 1;//有序子数列个数
    int tmp = 0;//处理subarr
    for(int i = 0; i < len - 1; ++i){
        if(arr[i] > arr[i + 1]){//结束一个有序子数列
            ++subarr[tmp++];
            ++s;
        }
        else{
            ++subarr[tmp];
        }
        //处理最后一个元素，仍有序：当前tmp位+1；无序：后加已处理tmp，当前tmp位+1
        if(i == len - 2){
            ++subarr[tmp];
        }
    }
//    for(int i = 0; i < s; ++i){
//        if(i == s - 1){
//            printf("%d\n", subarr[i]);
//        }
//        printf("%d ", subarr[i]);
//    }
}

void merge(int *arr, int len1, int len2){

    int tmp = 0, tmp1 = 0, tmp2 = 0;
    while(tmp1 < len1 && tmp2 < len2){
        if(a1[tmp1] < a2[tmp2]){
            arr[tmp++] = a1[tmp1++];
        }
        else{
            arr[tmp++] = a2[tmp2++];
        }
    }
    while(tmp1 < len1){
        arr[tmp++] = a1[tmp1++];
    }
    while(tmp2 < len2){
        arr[tmp++] = a2[tmp2++];
    }
}

void mergeSort(int *arr, int left, int right){
    getLengthOfOrderedSubarray(arr, right - left + 1);

    for(int i = 0; subarr[i + 1] != 0; ++i){
        merge(arr, subarr[i], subarr[i + 1]);
    }

}

int main(){
    int len = 0;
    printf("please enter the length of array:\n");
    scanf("%d", &len);
    printf("please enter the array:\n");
    int *array = (int *)malloc((len + 1) * sizeof(int));
    if(!array){
        exit(OVERFLOW);
    }
    for(int i = 0; i < len; ++i){
        scanf("%d", array + i);
    }

    if(len > 0){
        mergeSort(array, 0, len - 1);

        printf("the sorted array is:\n");
        for(int i = 0; i < len; ++i){
            if(i == 0){
                printf("%d", array[i]);
            }
            else{
                printf(" %d", array[i]);
            }
        }
    }
    return 0;
}
