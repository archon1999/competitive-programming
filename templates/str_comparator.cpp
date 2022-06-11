struct num {
    static const int MA = 1e9 + 7, MB = 1e9 + 9;

    int a, b;

    num() { }
    num( int x ) : a( x ), b( x ) { }
    num( int a, int b ) : a( a ), b( b ) { }

    num operator + ( const num &x ) const { return num( ( a + x.a ) % MA, ( b + x.b ) % MB ); }
    num operator - ( const num &x ) const { return num( ( a + MA - x.a ) % MA, ( b + MB - x.b ) % MB ); }
    num operator * ( int x ) const { return num( ( ( int64_t ) a * x ) % MA, ( ( int64_t ) b * x ) % MB ); }
    num operator * ( const num &x ) const { return num( ( ( int64_t ) a * x.a ) % MA, ( ( int64_t ) b * x.b ) % MB ); }
    bool operator == ( const num &x ) const { return a == x.a && b == x.b; }

    explicit operator int64_t () const { return ( int64_t ) a * MB + b + 1; } // > 0
};

template <class hash_t> 
struct str_comparator {
    static const int P;
    static vector<hash_t> deg;

    int n;
    const char *s;
    hash_t *h;

    str_comparator( int n, const char *s ) : n( n ), s( s ) {
        h = new hash_t[n + 1];
        h[0] = 0;
        for( int i = 0; i < n; i++ ){
            h[i + 1] = h[i] * P + s[i];
        }
        deg.reserve( n);
        while ( deg.size() <= n )
        deg.push_back( *deg.rbegin() * P );      
    }

    hash_t substr( int i, int len ) const { return h[i + len] - h[i] * deg[len]; }

    int lcp( int i, int j ) {
        int L = 0, R = n - max( i, j );
        while ( L < R ) {
        int M = ( L + R + 1 ) / 2;
        if ( substr( i, M ) == substr( j, M ) )
            L = M;
        else
            R = M - 1;
        }
        return L;
    }

    int cmp( int a, int b ) {
        int len = n - max( a, b ), l = lcp( a, b );
        return l < len ? ( int ) s[a + l] - s[b + l] : b - a;
    }

    bool operator() ( int i, int j ) { return cmp( i, j ) < 0; }
};

template <class hash_t> vector <hash_t> str_comparator<hash_t>::deg( 1, hash_t( 1 ) );
template <class hash_t> const int str_comparator<hash_t>::P = max( 239, rand() );