#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
using namespace std;
typedef map<int,unsigned int> CounterMap;
double MLOGA(vector<int> &perm, vector<vector<int> > &adj)
{
    double gaps = 0;
    unsigned adj_size = adj.size();
    //cout << adj_size << endl;
    for(unsigned i = 0; i < adj_size; i++)
    {
        int pi_u = perm[i];
        unsigned num_edges = adj[i].size();
        for(unsigned j = 0; j < num_edges; j++)
        {
            //cout << max(abs(perm[adj[i][j]] - pi_u), 1) << endl;
            gaps += log2(abs(perm[adj[i][j]] - pi_u));
        }
    }
    return gaps/2;
}

struct Node
{
    int gap;
    Node *left;
    Node *right;
    double freq;
    int numLeaves;
};

struct compare  
 {  
   bool operator()(const Node* l, const Node* r)  
   {  
       return l->freq > r->freq;  
   }  
 }; 

struct LogGapInfo
{
    double gaps;
    int len;
    CounterMap freqs;
    priority_queue<Node*, vector<Node*>, compare> q;
};

void MLOGGAPA(vector<int> &perm, vector<vector<int> > &adj, LogGapInfo *gapInfo)
{
    unsigned adj_size = adj.size();
    for(unsigned i = 0; i < adj_size; i++)
    {
        unsigned num_edges = adj[i].size();
        if(num_edges < 1)
        {
            continue;
        }
        vector<int> map_vertices(num_edges, 0);
        for(unsigned j = 0; j < num_edges; j++)
        {
            map_vertices[j] = perm[adj[i][j]];
        }
        sort(map_vertices.begin(), map_vertices.end());
        for(unsigned j = 0; j < num_edges - 1; j++)
        {
            int tmp_gap = map_vertices[j + 1] - map_vertices[j];
            double tmp = log2(tmp_gap);
            gapInfo->gaps += tmp;
            gapInfo->len += 1;
            CounterMap::iterator it(gapInfo->freqs.find(tmp_gap));
            if (it != gapInfo->freqs.end())
            {
                it -> second++;
            } 
            else
            {
                gapInfo->freqs[tmp_gap] = 1;
            }
        }
    }
}

double entropy(LogGapInfo &gapInfo)
{
    double ent = 0;
    double tmp = 0;
    for (const auto &p : gapInfo.freqs)
    {
        tmp = (double)p.second) / gapInfo.len;
        ent += tmp * (-log2(tmp));
    }
    return ent;
}

/*int numBits(LogGapInfo *gapInfo, Node *root)
{
    int bits = 0;
    unsigned num_leaves = gapInfo.leaves.size();
    for(unsigned i = 0; i < num_leaves; i++)
    {
        bits += gapInfo.freqs[gapInfo.leaves[i].gap] * gapInfo.leaves[i].depth;
    }
    return bits;
    
    
}*/

bool DFS(LogGapInfo *gapInfo, Node *node, int depth, int *bits)
{
    if(!node)
    {
        return false;
    }
    bool has_left = DFS(gapInfo, node->left, depth + 1, bits);
    bool has_right = DFS(gapInfo, node->right, depth + 1, bits);
    if(!has_left && !has_right)
    {
        *bits += gapInfo->freqs[node->gap] * depth;
    }
    return true;
}
/*
int main()
{
    int num_vertices = 4;
    int perm_ints[] = {1, 2, 0, 3};
    vector<int> perm(perm_ints, perm_ints + sizeof(perm_ints) / sizeof(int));
    vector<vector<int> > adj(num_vertices, vector<int>());
    int adj0[] = {1, 2};
    int adj1[] = {0, 3};
    int adj2[] = {2, 3};
    int adj3[] = {1, 3};
    adj[0] = vector<int>(adj0, adj0 + sizeof(adj0) / sizeof(int));
    adj[1] = vector<int>(adj1, adj1 + sizeof(adj1) / sizeof(int));
    adj[2] = vector<int>(adj2, adj2 + sizeof(adj2) / sizeof(int));
    adj[3] = vector<int>(adj3, adj3 + sizeof(adj3) / sizeof(int));
    MLOGA(perm, adj);
    cout << MLOGA(perm, adj) << endl;
    LogGapInfo gapInfo = {};
    MLOGGAPA(perm, adj, &gapInfo);
    cout << gapInfo.gaps << endl;
    
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
    cout << bits << endl;
    return 0;
}*/
