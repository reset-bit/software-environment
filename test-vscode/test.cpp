#include <iostream>
using namespace std;
#define N 10
int w[N][N], c[N][N]; 
int bestx[N];
int x[N];//临时存放第i个零件的供应商
int cw = 0, cc = 0, bestw = 10000;
int n, m, cost;//部件数,供应商数,限定价格
void Backtrack(int t)
{
    if (t > n)
    {
        bestw = cw; //当前最小重量
        for (int j = 1; j <= n; j++){
            bestx[j] = x[j];
        }
    }
    else
    {
        for (int j = 1; j <= m; j++)
        {
            if (cc + c[t][j] <= cost && cw + w[t][j] < bestw)
            {
                x[t] = j;
                cc += c[t][j];
                cw += w[t][j];
                Backtrack(t + 1);
                cc -= c[t][j];
                cw -= w[t][j];
            }
        }
    }
}

int main()
{
    cout << "Please input the number of parts, the number of suppliers, and the maximum total price:" << endl;
    cin >> n >> m >> cost;
    cout << "Please enter the weight of each component purchased from each supplier in turn:" << endl;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> w[i][j];
        }
    }
    cout << "Please enter the purchase price of each component from each supplier in turn:" << endl;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> c[i][j];
        }
    }
        
    Backtrack(1);

    cout << "Minimum machine weight:" << bestw << endl;
    cout << "The sources of each component are as follows: ";
    for (int i = 1; i <= n; i++){
        cout << bestx[i] << ' ';
    }
    cout << endl;
    return 0;
}