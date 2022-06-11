
const int LOGN = 20;

int n, m;
int timer;
vector<int> edges[MAXN];
int up[MAXN][LOGN];
int tin[MAXN];
int tout[MAXN];
int h[MAXN];
int cnt[MAXN];

void dfs( int v, int p, int h = 1 ){
    up[v][0] = p;
    tin[v] = ++timer;
    ::h[v] = h;
    cnt[v] = 1;
    for( int u: edges[v] ){
        if( u != p ){
            dfs( u, v, h + 1 );
            cnt[v] += cnt[u];
        }
    }
    tout[v] = ++timer;
}
 
void preprocess(){
    for( int i = 1; i < LOGN; i++ ){
        for( int j = 1; j <= n; j++ ){
            up[j][i] = up[up[j][i - 1]][i - 1];
        }
    }
}
 
bool upper( int u, int v ){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
 
int lca( int u, int v ){
    if( upper( u, v ) ) return u;
    if( upper( v, u ) ) return v;
    for( int i = LOGN - 1; i >= 0; i-- ){
        if( !upper( up[u][i], v ) ){
            u = up[u][i];
        }
    }
    return up[u][0];
}
 
int get_parent( int u, int k ){
    for( int i = 0; i < LOGN; i++ ){
        if( ( 1 << i ) & k ){
            u = up[u][i];
        }
    }
    return u;
}
 
int dist( int u, int v ){
    int l = lca( u, v );
    return h[u] - h[l] + h[v] - h[l];
}