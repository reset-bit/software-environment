#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>

double f(double x) {
    return 1 / (1 + x * x);
}

double intergrate_cpu(double a, double b, int precision) {
    double sum = 0;
    double dx = (double)1 / precision;//单个矩形宽
    int i;
    //面积法求积分
    for (i = 0; i < precision; i++) {
        sum += f(a + dx) * dx;
        a += dx;
    }
    return sum;
}

double intergrate_openmp(double a, double b, int precision) {
    double dx = (double)1 / precision;//单个矩形宽
    double sum = 0;
    int thread_num = 4, i;
    //设置线程数为4，面积法求积分
#pragma omp parallel sections reduction(+:sum) private(i) num_threads(thread_num)
    {
#pragma omp section
        {
            for (i = omp_get_thread_num(); i < precision; i += thread_num)//全部线程跑过一遍应完成thread_num个任务
            {
                sum += f(a + i * dx) * dx;
            }
        }
#pragma omp section
        {
            for (i = omp_get_thread_num(); i < precision; i += thread_num)
            {
                sum += f(a + i * dx) * dx;
            }
        }
#pragma omp section
        {
            for (i = omp_get_thread_num(); i < precision; i += thread_num)
            {
                sum += f(a + i * dx) * dx;
            }
        }
#pragma omp section
        {
            for (i = omp_get_thread_num(); i < precision; i += thread_num)
            {
                sum += f(a + i * dx) * dx;
            }
        }
    }
    return sum;
}

int main() {
    double a = 0, b = 1;//积分上下限
    int precision = 1000000000;//积分精度
    int i;
    
    //CPU串行程序求积分
    clock_t t1 = clock();
    printf("CPU:pi = %lf\n", 4 * intergrate_cpu(a, b, precision));
    clock_t t2 = clock();
    printf("CPU run time = %f s\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

    //OpenMP并行程序求积分
    t1 = clock();
    printf("OpenMP : pi = %lf\n", 4 * intergrate_openmp(a, b, precision));
    t2 = clock();
    printf("OpenMP run time = %f s\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

    return 0;
}

//double montecarlo_cpu(int precision) {
//	int count = 0;
//	for (int i = 0; i < precision; ++i) {
//		double x = rand() / (double)RAND_MAX;//保证在(0,1)
//		double y = rand() / (double)RAND_MAX;
//		if (x * x + y * y < 1) {//统计落在圆内的点个数
//			++count;
//		}
//	}
//	double pi = 4 * (double)count / precision;
//	return pi;
//}
//
//double motecarlo_openmp(int precision) {
//	int count = 0;
//	int thread_num = 4;
//	double x, y;
//
//	//设置线程数为4
//#pragma omg parallel sections num_threads(thread_num) for private(x, y) reduction(+:count)
//	{
//#pragma omg section
//		{
//			for (int i = 0; i < precision; i += thread_num) {//全部线程跑过一遍应完成thread_num个任务
//				x = (double)rand() / (double)RAND_MAX;//保证在(0,1)
//				y = (double)rand() / (double)RAND_MAX;
//				if (x * x + y * y < 1) {//统计落在圆内的点个数
//					++count;
//				}
//			}
//		}
//#pragma omg section
//		{
//			for (int i = 0; i < precision; i += thread_num) {
//				x = (double)rand() / (double)RAND_MAX;
//				y = (double)rand() / (double)RAND_MAX;
//				if (x * x + y * y < 1) {
//					++count;
//				}
//			}
//		}
//#pragma omg section
//		{
//			for (int i = 0; i < precision; i += thread_num) {
//				x = (double)rand() / (double)RAND_MAX;
//				y = (double)rand() / (double)RAND_MAX;
//				if (x * x + y * y < 1) {
//					++count;
//				}
//			}
//		}
//#pragma omg section
//		{
//			for (int i = 0; i < precision; i += thread_num) {
//				x = (double)rand() / (double)RAND_MAX;
//				y = (double)rand() / (double)RAND_MAX;
//				if (x * x + y * y < 1) {
//					++count;
//				}
//			}
//		}		
//	}
//	double pi = 4 * (double)count / precision;
//	return pi;
//}
//
//int main() {
//	int precision = 1000000000;//计算精度
//
//	//CPU串行程序montecarlo算法求pi
//	clock_t t1 = clock();
//	printf("CPU pi = %lf\n", montecarlo_cpu(precision));
//	clock_t t2 = clock();
//	printf("CPU run time : %f s\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
//
//	//OpenMP并行程序montecarlo算法求pi
//	t1 = clock();
//	printf("OpenMP pi = %lf\n", motecarlo_openmp(precision));
//	t2 = clock();
//	printf("OpenMP run time : %f s\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
//
//	return 0;
//}