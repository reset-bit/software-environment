#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
using namespace std;

__global__ void MatMul_gpu(int n, int *a, int *b, int *c) {
	int i = blockIdx.x * blockDim.x + threadIdx.x;//x方向值
	int j = blockIdx.y * blockDim.y + threadIdx.y;//y方向值

	if (i < n && j < n) {
		int temp = 0;
		for (int k = 0; k < n; ++k) {
			temp += *(a + i * n + k) * *(b + k * n + j);
		}
		*(c + i * n + j) = temp;
	}
}

void MatMul_cpu(int n, int* a, int* b, int* c) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			*(c + i * n + j) = 0;
			for (int k = 0; k < n; ++k) {
				*(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
			}
		}
	}
}

int main() {
	int const N = 5000;
	int* a, * b, * c;
	int* p_a, * p_b, * p_c;
	//分配CPU端显存
	a = (int*)malloc(sizeof(int) * N * N);
	b = (int*)malloc(sizeof(int) * N * N);
	c = (int*)malloc(sizeof(int) * N * N);
	//分配GPU端显存
	cudaMalloc((void**)&p_a, sizeof(int) * N * N);
	cudaMalloc((void**)&p_b, sizeof(int) * N * N);
	cudaMalloc((void**)&p_c, sizeof(int) * N * N);
	//初始化矩阵
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			*(a + i * N + j) = (int)(rand() % 10 + 1);
			*(b + i * N + j) = (int)(rand() % 10 + 1);
			*(c + i * N + j) = 0;
		}
	}
	//打印待乘矩阵
	//cout << "A:" << endl;
	//for (int i = 0; i < N; ++i) {
	//	for (int j = 0; j < N; ++j) {
	//		cout << *(a + i * N + j) << "  ";
	//	}
	//	cout << endl;
	//}
	//cout << "B:" << endl;
	//for (int i = 0; i < N; ++i) {
	//	for (int j = 0; j < N; ++j) {
	//		cout << *(b + i * N + j) << "  ";
	//	}
	//	cout << endl;
	//}
	//拷贝显存
	cudaMemcpy(p_a, a, sizeof(int) * N * N, cudaMemcpyHostToDevice);
	cudaMemcpy(p_b, b, sizeof(int) * N * N, cudaMemcpyHostToDevice);
	//分配gpu线程块及线程网络组织形式
	dim3 dimGrid(ceil(N / 4.0), ceil(N / 4.0), 1);
	dim3 dimBlock(4, 4, 1);

	//利用event事件在流的执行中添加标记点，打印gpu执行时间
	//cudaEvent_t start1, stop1;
	//cudaEventCreate(&start1);
	//cudaEventCreate(&stop1);
	//cudaEventRecord(start1, 0);
	//MatMul_gpu <<<dimGrid, dimBlock>>> (N, p_a, p_b, p_c);//核函数调用
	//cudaEventRecord(stop1, 0);
	//cudaEventSynchronize(stop1);
	//float time1;
	//cudaEventElapsedTime(&time1, start1, stop1);
	//cout << "gpu time = " << time1 << endl;
	//拷贝计算结果
	//cudaMemcpy(c, p_c, sizeof(int) * N * N, cudaMemcpyDeviceToHost);

	//打印cpu执行时间
	cudaEvent_t start2, stop2;
	cudaEventCreate(&start2);
	cudaEventCreate(&stop2);
	cudaEventRecord(start2, 0);
	MatMul_cpu(N, a, b, c);//函数调用
	cudaEventRecord(stop2, 0);
	cudaEventSynchronize(stop2);
	float time2;
	cudaEventElapsedTime(&time2, start2, stop2);
	cout << "cpu time = " << time2 << endl;

	//打印计算结果
	//cout << "A*B:" << endl;
	//for (int i = 0; i < N; ++i) {
	//	for (int j = 0; j < N; ++j) {
	//		cout << *(c + i * N + j) << "  ";
	//	}
	//	cout << endl;
	//}
	//清理内存
	free(a);
	free(b);
	free(c);
	cudaFree(p_a);
	cudaFree(p_b);
	cudaFree(p_c);
	return 0;
}