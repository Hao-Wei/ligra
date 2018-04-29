
#include "common.h"
#include "kruskal.h"
#include "kruskal2.h"
#include "boruvka.h"
#include "boruvka2.h"
#include "boruvka3.h"

int main()
{
  cerr << "BEGIN" << endl;
  int n, m;
  cin >> n >> m;
  int **adj;
  adj = new int* [n];
  for(int i = 0; i < n; i++)
  {
     adj[i] = new int [n];
     for(int j = 0; j < n; j++)
     {
         adj[i][j] = INT_MIN;
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
  Boruvka* bv = new Boruvka(n);
  CNode* root = bv->run(adj);
  print_tree(root);

  Boruvka2* bv2 = new Boruvka2(n);
  root = bv2->run(adj);
  print_tree(root);

  Boruvka3* bv3 = new Boruvka3(n);
  root = bv3->run(adj);
  print_tree(root);

  Kruskal* ks = new Kruskal(n);
  root = ks->run(adj);
  print_tree(root);

  Kruskal2* ks2 = new Kruskal2(n);
  root = ks2->run(adj);
  print_tree(root);
}
