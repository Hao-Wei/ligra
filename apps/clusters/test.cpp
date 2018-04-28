#include<iostream>
#include "boruvka.h"

using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;
  int **adj;
  adj = new int* [n];
  for(int i = 0; i < n; i++)
  {
     adj[i] = new int [n];
     for(int j = 0; j < n; j++)
     {
         adj[i][j] = -UINT_E_MAX;
     }
  }
  for(int i = 0; i < m; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a-1][b-1] = -c;
    adj[b-1][a-1] = -c;
  }
  /*for(int i = 0; i < n; i++)
  {
     for(int j = 0; j < n; j++)
     {
         cout << adj[i][j] << " ";
     }
     cout << endl;
  }*/
  cout << boruvka_adj(adj, n) << endl;
}
