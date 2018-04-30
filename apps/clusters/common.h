#ifndef CLUSTERING_COMMON
#define CLUSTERING_COMMON

#include<iostream>
#include<vector>
#include<stdlib.h>
#include <iomanip> 

using namespace std;

//#define uintE int
//#define intE int
//#define intT int

typedef int uintE;
typedef int intE;
typedef int intT;

#define UINT_E_MAX 2000000000
#define INT_MIN -2000000000

struct CNode
{
  uintE id;
  CNode* parent;
  vector<CNode*> children;

  CNode(intT node_id) : id(node_id), parent(NULL), children(vector<CNode*>()){}
  CNode() : id(UINT_E_MAX), parent(NULL), children(vector<CNode*>()) {}
};

template <class intT>
struct wghEdge {
  intT u;
  intT v;
  intT w;
  wghEdge(intT f, intT s, intT t) : u(f), v(s), w(t) {}
};

struct Comp{
  bool operator() (wghEdge<intE> a, wghEdge<intE> b) {return a.w > b.w;}
};

#define EPS 0.00001
#define MAX_N 1000000

class UnionFind {
  private:
    int id[MAX_N];
  public:
    UnionFind(int n) {
      for(int i = 0; i < n; i++) id[i] = i;
    }

    int find(int i) {
      while(id[i] != i) 
      {
        id[i] = id[id[i]];
        i = id[i];
      }
    }

    void join(int i, int j) {
      j = find(j);
      id[j] = i;
    }
};

bool isin(vector<intE> v, intE n)
{
  for(int i = 0; i < v.size(); i++)
    if(v[i] == n) return true;
  return false;
}

void inorder_traversal(CNode* n, vector<int> &perm)
{
  if(n->children.empty())
    perm.push_back(n->id);
  else
  {
    for(int i = 0; i < n->children.size(); i++)
      inorder_traversal(n->children[i], perm);
  }
}

void print_tree(CNode* n, int indent=0)
{
  if(n) {
    cout << setw(indent) << ' ';
    if(n->id == UINT_E_MAX)
      cout << "X" << endl;
    else
      cout << n->id << endl;
    for(int i = 0; i < n->children.size(); i++)
      print_tree(n->children[i], indent+4);      
  }
}

void adj_to_edge_list(int** adj, vector<wghEdge<intE> > &edge_list, int n)
{
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(adj[i][j] > 0)
        edge_list.push_back(wghEdge<intE>(i, j, adj[i][j]));
}

void edge_list_to_adj_list(vector<wghEdge<intE> > &edge_list, vector<vector<int> > &adj_list, int n)
{
  adj_list = vector<vector<int> >(n);
  for(int i = 0; i < edge_list.size(); i++)
  {
    int u = edge_list[i].u;
    int v = edge_list[i].v;
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
  }
}

void flip_perm(vector<int> &perm)
{
  vector<int> cc;
  for(int i = 0; i < perm.size(); i++) cc.push_back(perm[i]);
  for(int i = 0; i < perm.size(); i++) perm[cc[i]] = i;
}

#endif