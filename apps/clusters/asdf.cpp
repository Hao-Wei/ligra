
#include "common.h"
#include "kruskal.h"
#include "kruskal2.h"
#include "boruvka.h"
#include "boruvka2.h"
#include "boruvka3.h"
#include "getGaps.C"

int compute_gaps(LogGapInfo &gapInfo)
{
    
  //init leaves
  for (const auto &p : gapInfo.freqs)
  {
      Node *tmp_node = new Node{p.first, 0, 0, ((double)p.second) / gapInfo.len, 1};
      gapInfo.q.push(tmp_node);
  }
  
  //build tree
  int numLeaves = 0;
  int numGaps = gapInfo.freqs.size();
  Node *root;
  if(numGaps < 2)
  {
      Node *n1;
      n1 = gapInfo.q.top();
      gapInfo.q.pop();
      root = new Node{-1, n1, NULL, n1->freq, n1->numLeaves};
  }
  else
  {
      while(numLeaves < numGaps)
      {
          Node *n1;
          n1 = gapInfo.q.top();
          gapInfo.q.pop();
          Node *n2;
          n2 = gapInfo.q.top();
          gapInfo.q.pop();
          numLeaves = n1->numLeaves + n2->numLeaves;
          root = new Node{-1, n1, n2, n1->freq + n2->freq, numLeaves};
          gapInfo.q.push(root);
      }
  }
  int bits = 0;
  DFS(&gapInfo, root, 0, &bits);
  return bits;
}

void print_metrics(int num_edges, vector<int>& perm, vector<int>& iden, vector<vector<int> >& adj_list)
{
  LogGapInfo gapInfoIdent = {};
  LogGapInfo gapInfoNorm = {};
  double ans = 0;
  int bitsIdent = 0;
  int bitsNorm = 0;
  ans = MLOGA(iden, adj_list);
  cout << "MLOGA: " << 2.0*ans/num_edges << endl;
  ans = MLOGA(perm, adj_list);
  cout << "MLOGA: " << 2.0*ans/num_edges << endl;

  MLOGGAPA(iden, adj_list, &gapInfoIdent);
  cout << "MLOGGAPA: " << 2.0*gapInfoIdent.gaps/num_edges << endl;
  MLOGGAPA(perm, adj_list, &gapInfoNorm);
  cout << "MLOGGAPA: " << 2.0*gapInfoNorm.gaps/num_edges << endl;

  bitsIdent = compute_gaps(gapInfoIdent);
  cout << "Huff: " << 2.0*bitsIdent/num_edges << endl;
  bitsNorm = compute_gaps(gapInfoNorm);
  cout << "Huff: " << 2.0*bitsNorm/num_edges << endl;

  double entropyIden = entropy(gapInfoIdent);
  cout << "Entropy: " << entropyIden << endl;
  double entropyNorm = entropy(gapInfoNorm);
  cout << "Entropy: " << entropyNorm << endl;
  

  /*ans = MLOGA(iden, adj_list);
  cout << "NUM BITS: " << ans/edge_list.size() << endl;
  ans = MLOGA(perm, adj_list);
  cout << "NUM BITS: " << ans/edge_list.size() << endl;*/
}

int main()
{
  cerr << "BEGIN" << endl;
  string s;
  cin >> s;
  int n, m;
  cin >> n >> m;
  
  int offset[n+1];
  for(int i = 0; i < n; i++) cin >> offset[i];
  offset[n] = m;
  int edges[m];
  for(int i= 0; i < m; i++) cin >> edges[i];
  



  int **adj;
  adj = new int* [n];
  for(int i = 0; i < n; i++)
  {
     adj[i] = new int [n];
     for(int j = 0; j < n; j++)
     {
         adj[i][j] = 0;
     }
  }
  for(int u = 0; u < n; u++)
  {
    for(int j = offset[u]; j < offset[u+1]; j++)
    {
        int v = edges[j];
        if(u == v) continue;
        adj[u][v]++;
        for(int k = offset[v]; k < offset[v+1]; k++)
        {
            int w = edges[k];
            if(u == w) continue;
            adj[u][w]++;
        }  
    }
  }
  for(int i = 0; i < n; i++)
    for(int j = i+1; j < n; j++)
    {
        adj[i][j] += adj[j][i];
        adj[j][i] = adj[i][j];
    }
  /*for(int i = 0; i < n; i++)
  {
     for(int j = 0; j < n; j++)
     {
         cout << adj[i][j] << " ";
     }
     cout << endl;
  }*/
  vector<int> iden;
  for(int i = 0; i < n; i++) iden.push_back(i);
  vector<wghEdge<intE> > edge_list;
  vector<vector<int> > adj_list;
  vector<int> perm;

  for(int u = 0; u < n; u++)
  {
    for(int j = offset[u]; j < offset[u+1]; j++)
    {
      int v = edges[j];
      edge_list.push_back((wghEdge<int>){u, v, 0});
    }
  }
  cout << "SIZE OF GRAPH: " << edge_list.size() << endl;
  edge_list_to_adj_list(edge_list, adj_list, n);

  double ans = 0;


  Boruvka* bv = new Boruvka(n);
  CNode* root = bv->run(adj);
  inorder_traversal(root, perm);
  flip_perm(perm);
  //for(int i = 0;i < perm.size(); i++) cout << perm[i] << " ";
 //cout << endl;

  cout << "Boruvka" << endl;
  print_metrics(edge_list.size(), perm, iden, adj_list);
  perm.clear();
  //print_tree(root);

  Boruvka2* bv2 = new Boruvka2(n);
  root = bv2->run(adj);
  inorder_traversal(root, perm);
  flip_perm(perm);
  //for(int i = 0;i < perm.size(); i++) cout << perm[i] << " ";
  //cout << endl;
  cout << "Boruvka2" << endl;
  print_metrics(edge_list.size(), perm, iden, adj_list);
  perm.clear();
  //print_tree(root);

  Boruvka3* bv3 = new Boruvka3(n);
  root = bv3->run(adj);
  inorder_traversal(root, perm);
  flip_perm(perm);
  //for(int i = 0;i < perm.size(); i++) cout << perm[i] << " ";
  //cout << endl;
  cout << "Boruvka3" << endl;
  print_metrics(edge_list.size(), perm, iden, adj_list);
  perm.clear();
  //print_tree(root);

  Kruskal* ks = new Kruskal(n);
  root = ks->run(adj);
  inorder_traversal(root, perm);
  flip_perm(perm);
  //for(int i = 0;i < perm.size(); i++) cout << perm[i] << " ";
  //cout << endl;
  cout << "Kruskal" << endl;
  print_metrics(edge_list.size(), perm, iden, adj_list);
  perm.clear();
  //print_tree(root);

  Kruskal2* ks2 = new Kruskal2(n);
  root = ks2->run(adj);
  inorder_traversal(root, perm);
  flip_perm(perm);
  //for(int i = 0;i < perm.size(); i++) cout << perm[i] << " ";
  //cout << endl;
  cout << "Kruskal2" << endl;
  print_metrics(edge_list.size(), perm, iden, adj_list);
  perm.clear();
  //print_tree(root);
}
