
struct node {
    int next[K], go[K];
    vector<int> leaf;
    int from, link;
    int number;
    char symbol;
    int len;
    node( int from = 0, char symbol = 0 ) : from( from ), symbol( symbol ) {
        link = -1;
        fill(next, next + K, -1);
        fill(go, go + K, -1);
    }
};
 
vector<node> trie;
 
void add_string( string s, int x ) {
    if( trie.empty() ){       
        trie.push_back( node( 0, 'a' ) );
        trie[0].len = 0;
    }
    int v = 0;
    for( int i = 0; i < s.size(); i++ ) {
        int c = s[i] - 'a';
        if( trie[v].next[c] == -1 ) {
            trie.push_back( node( v, s[i] ) );
            trie[v].next[c] = trie.size() - 1;
        }
        v = trie[v].next[c];
        trie[v].len = trie[trie[v].from].len + 1;
    }
    trie[v].leaf.push_back( x );
}
 
int get_link ( int v );
 
int go( int v, char  c) {
    c -= 'a';
    if( trie[v].go[c] != -1 )
        return trie[v].go[c];
    if( trie[v].next[c] != -1 ) {
        return trie[v].go[c] = trie[v].next[c];
    }
    if( v == 0 )
        return trie[v].go[c] = 0;
    return trie[v].go[c] = go( get_link( v ), c + 'a' );
}
 
int get_link(int v) {
    if( trie[v].link != -1 )
        return trie[v].link;
    if( v == 0 || trie[v].from == 0 )
        return 0;
    return trie[v].link = go( get_link( trie[v].from ), trie[v].symbol );
}
