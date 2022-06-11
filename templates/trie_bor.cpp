struct trie {

    static const int MAXN = 200020;

    map<int, int> edges[MAXN], cnt[MAXN];
    int terminate[MAXN];
    int size;

    trie() : size( 0 ){ }

    int insert( const string &s, int v = 0 ){
        for( int i = 0; i < s.size(); i++ ){
            int c = s[i];
            cnt[v][c]++;
            if( !edges[v][c] ) edges[v][c] = ++size;
            v = edges[v][c];
        }
        terminate[v]++;
        return v;
    }

    int erase( const string &s, int v = 0 ){
        if( find( s ) == -1 ) return -1;
        for( int i = 0; i < s.size(); i++ ){
            int c = s[i];
            cnt[v][c]--;
            v = edges[v][c];
        }
        terminate[v]--; 
        return v;
    }

    int find( const string &s, int v = 0 ){
        for( int i = 0; i < s.size(); i++ ){
            int c = s[i];
            if( !edges[v].count( c ) ) return -1;
            v = edges[v][c];
        }
        if( terminate[v] ) return v;
        return -1;
    }

    int get_different_strings( int v = 0 ){
        int ans = ( terminate[v] > 0 );
        for( auto [c, u]: edges[v] ){
            ans += get_different_strings( u );
        }
        return ans;
    }

    string find_kth( int k ){
        assert( k <= size );
        string ans;
        int v = 0;
        while( !edges[v].empty() && k ){
            if( k <= terminate[v] ) break;
            k -= terminate[v];
            for( auto [c, u]: edges[v] ){
                if( k > cnt[v][c] ){
                    k -= cnt[v][c];
                } else {
                    ans += c + 'a';
                    v = u;
                    break;
                }
            }
        }
        return ans;
    }
    
};