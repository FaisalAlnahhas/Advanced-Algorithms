//
//  lab2.c
//  
//
//  Created by Faisal Alnahhas on 3/24/18.
//

#include <stdio.h>

// Basic Definitions

/////////Dr. Weems's code, downloaded from http://ranger.uta.edu/~weems/NOTES5311/ff.c ////////////////////////

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_NODES 3000
#define oo 1000000000
#define True 1
#define False 0

// Declarations

int n;  // number of nodes
int e;  // number of edges
int capacity[MAX_NODES][MAX_NODES]; // capacity matrix
int flow[MAX_NODES][MAX_NODES];     // flow matrix
int color[MAX_NODES]; // needed for breadth-first search
int pred[MAX_NODES];  // array to store augmenting path
//int increment = oo;

int min (int x, int y) {
    return x<y ? x : y;  // returns minimum of x and y
}

// A Queue for Breadth-First Search

int head,tail;
int q[MAX_NODES+2];

void enqueue (int x) {
    q[tail] = x;
    tail++;
    color[x] = GRAY;
}

int dequeue () {
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}

// Breadth-First Search for an augmenting path

int bfs (int start, int target) {
    int u,v;
    for (u=0; u<n; u++) {
        color[u] = WHITE;
    }
    head = tail = 0;
    enqueue(start);
    pred[start] = -1;
    while (head!=tail) {
        u = dequeue();
        // Search all adjacent white nodes v. If the capacity
        // from u to v in the residual network is positive,
        // enqueue v.
        for (v=0; v<n; v++) {
            if (color[v]==WHITE && capacity[u][v]-flow[u][v]>0) {
                enqueue(v);
                pred[v] = u;
            }
        }
    }
    // If the color of the target node is black now,
    // it means that we reached it.
    return color[target]==BLACK;
}

// Ford-Fulkerson Algorithm

int max_flow (int source, int sink) {
    int i,j,u;
    // Initialize empty flow.
    int max_flow = 0;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            flow[i][j] = 0;
        }
    }
    //int increment = oo;
    // While there exists an augmenting path,
    // increment the flow along this path.
    while (bfs(source,sink)) {
        //printf("source: %d, sink: %d\n", source, sink);
        // Determine the amount by which we can increment the flow.
        int increment = oo;
        for (u=sink; pred[u]!=(-1); u=pred[u]) {
            increment = min(increment,capacity[pred[u]][u]-flow[pred[u]][u]);
            //printf("inc: %d\n", increment);
        }
        // Now increment the flow.
        for (u=sink; pred[u]!=(-1); u=pred[u]) {
            flow[pred[u]][u] += increment;
            flow[u][pred[u]] -= increment;  // Reverse in residual
            //printf("inc 2: %d\n", increment);
        }
        // Path trace
       /* for (u=sink; pred[u]!=(-1); u=pred[u]) {
            printf("%d<-",u);
        }
        printf("%d adds %d incremental flow\n",source,increment);*/
        max_flow += increment;
       // if (source == sink) return max_flow;
    }
    // No augmenting path anymore. We are done.
    return max_flow;
}

// Reading the input file and the main program

//////////////////END OF DR. Weem's code/////////////////////////////////////////////////
struct Graph
{
    int u, v, edge_capacity;
};


FILE *file_manage(char *f) {
    int a,b,c,i,j;
    
    FILE* fo = fopen(f,"r");
    struct Graph G;
    
    if(fo == NULL)
    {
        printf("File not found.\n");
        return fo;
    }
    
    else
    {
        // read number of nodes and edges
        fscanf(fo,"%d %d",&n,&e);
        //printf("%d nodes, and %d edges.\n", n, e);
        // initialize empty capacity matrix
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                capacity[i][j] = 0;
            }
        }
        // read edge capacities
        for (i=0; i<e; i++) {
            fscanf(fo,"%d %d %d",&a,&b,&c);
            G.u = a;
            G.v = b;
            G.edge_capacity = c;
            //printf("a:%d   b:%d   c:%d\n", a, b, c);
            //printf("G.u:%d   G.v:%d   G.cap:%d\n", G.u, G.v, G.edge_capacity);
            capacity[G.u][G.v] += G.edge_capacity; // Could have parallel edges
            capacity[G.v][G.u] += G.edge_capacity; // residual flow
            //printf("capacity[][] = %d\n", capacity[G.u][G.v]);
        }
    }
    fclose(fo);
    return fo;
}

void cut_tree()
{
    int s, i, t, zero, j;
    int p[n];
    int fl[n];
    
    for(zero=0; zero<n; zero++)
    {
        p[zero] = 0;
        fl[zero] = 0;
    }
    
    for(s = 1; s<n; s++)
    {
        t = p[s];
        fl[s] = max_flow(s, t);
        for (i = 0; i < n; i++)
            if(i!=s && color[i] == BLACK && p[i] == t) p[i] = s;
        
        if(color[p[t]] == BLACK)
        {
            p[s] = p[t];
            p[t] = s;
            fl[s] = fl[t];
            fl[t] = max_flow(s, t);
        }
    }
    
    for(j = 1; j < n; j++)
        printf("%d %d %d\n", j, p[j], fl[j]);
}

int main (int argc, char *argv[]) {
    
    if (argc != 2) printf("Please choose one input file only.\n");
    //some parts of this code in main is also Dr. Weems's
    int i,j;
    file_manage(argv[1]);
    
    //printf("total flow is %d\n",max_flow(0,n-1));
    //printf("flows along edges:\n");
    /*for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            if (flow[i][j]>0)
                printf("%d->%d has %d\n",i,j,flow[i][j]); */
    cut_tree();
    return 0;
}
