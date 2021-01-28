#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define N 10
/*
���ڳ�ʼ���������飬ͨ�����ڶ�����ȴ���1��������Ȼ�ź����������Ρ�

��Ȼ�ϲ�������һ�ζ����������ɨ�裬�������ҳ�������Щ�ź����������Ρ�

Ȼ�����ڵ��ź����������������ϲ������ɸ�����ź����������Ρ������ϲ������ź����������Σ�ֱ�������������ź���
*/
int subarr[N] = {0};

void getLengthOfOrderedSubarray(int *arr, int len){
    int s = 1;//���������и���
    int tmp = 0;//����subarr
    for(int i = 0; i < len - 1; ++i){
        if(arr[i] > arr[i + 1]){//����һ������������
            ++subarr[tmp++];
            ++s;
        }
        else{
            ++subarr[tmp];
        }
        //�������һ��Ԫ�أ������򣺵�ǰtmpλ+1�����򣺺���Ѵ���tmp����ǰtmpλ+1
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
