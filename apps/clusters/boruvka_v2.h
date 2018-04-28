
#include<vector>
#include<stdlib.h>
#include<iostream>

using namespace std;

//#define uintE int
//#define intE int
//#define intT int

typedef int uintE;
typedef int intE;
typedef int intT;

#define UINT_E_MAX 2000000000

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

#define EPS 0.00001
#define MAX_N 1000000

bool isin(vector<intE> v, intE n)
{
  for(int i = 0; i < v.size(); i++)
    if(v[i] == n) return true;
  return false;
}

vector<intE> g[MAX_N];
int cid[MAX_N];
bool visited[MAX_N];
vector<CNode*> clusters;

void bfs(intE v, intE c, CNode* t)
{
  if(visited[v]) return;
  visited[v] = 1;
  if(!clusters[cid[v]]->parent)
  {
    clusters[cid[v]]->parent = t;
    t->children.push_back(clusters[cid[v]]);
  }
  cid[v] = c;
  for(int i = 0; i < g[v].size(); i++) bfs(g[v][i], c, t);
}

CNode* boruvka(vector<wghEdge<intE> > &edge_list, int n)
{
  long long mst = 0;
  clusters = vector<CNode*>(n);

  for(int i = 0; i < n; i++)
  {
    CNode* t = new CNode(i);
    clusters[i] = t;
    cid[i] = i;
    g[i].clear();
  }
  cerr << "begin main boruvka loop" << endl;
  while(clusters.size() > 1)
  {
    cerr << "cluster size: " << clusters.size() << endl;
    int size = clusters.size();
    intE max_e[size];
    int max[size];
    for(int i = 0; i < size; i++) max[i] = 0;
    for(int i = 0; i < edge_list.size(); i++)
    {
      intE u = edge_list[i].u;
      intE v = edge_list[i].v;
      intE w = edge_list[i].w;
      if(cid[u] == cid[v]) continue;
      if(max[cid[u]] < w)
      {
        max[cid[u]] = w;
        max_e[cid[u]] = i;
      }
      if(max[cid[v]] < w)
      {
        max[cid[v]] = w;
        max_e[cid[v]] = i;
      }
    }
    for(int i = 0; i < size; i++)
    {
      if(!max[i]) continue;
      intE u = edge_list[max_e[i]].u;
      intE v = edge_list[max_e[i]].v;
      intE w = edge_list[max_e[i]].w;
      if(isin(g[u], v)) continue;
      g[u].push_back(v);
      g[v].push_back(u);
      mst += w; //why does this only count MST edges?
    }
    
    int count = 0;
    vector<CNode*> new_clusters;

    for(int i = 0; i < n; i++) visited[i] = 0;
    
    for(int i = 0; i < n; i++)
    {
      if(!visited[i])
      {
        CNode* t = new CNode();
    	new_clusters.push_back(t);
        bfs(i, count, t);        
        count++;
      }
    }
    if(clusters.size() == new_clusters.size())
    {
      CNode* root = new CNode();
      for(int i = 0; i < clusters.size(); i++)
      {
        clusters[i]->parent = root;
        root->children.push_back(clusters[i]);
        delete new_clusters[i];
      }
      return root;
    }
    clusters = new_clusters;
  }

  return clusters[0];
}

CNode* boruvka_adj(int** adj, int n)
{
  vector<wghEdge<intE> > edge_list;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(adj[i][j] > EPS)
        edge_list.push_back(wghEdge<intE>(i, j, adj[i][j]));
  return boruvka(edge_list, n);
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






