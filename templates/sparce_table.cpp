template<typename F> struct sparce_table{

    static const int MAXN = 100'000;
    
    int table[20][MAXN], LOG_2[MAXN];

    F f;
    sparce_table(){ f = F(); };

    bool is_pow( int n ){
        return ( n & ( n - 1 ) ) == 0;
    }

    void build( int a[], int n ){
        for( int i = 1; i <= n; i++ ) table[0][i] = a[i];
        for( int i = 2; i < MAXN; i++ ) LOG_2[i] = LOG_2[i - 1] + is_pow( i );
        for( int i = 1; i <= LOG_2[n]; i++ )
            for( int j = 1; j <= n; j++ )
                table[i][j] = f( table[i - 1][j], table[i - 1][j + ( 1 << ( i - 1 ) )] );
    }

    int get( int l, int r ){
        if( l > r ) swap( l, r );
        int pw = LOG_2[r - l + 1];
        return f( table[pw][l], table[pw][r - ( 1 << pw ) + 1]);
    }

};

struct table_min {
    int operator()( const int &a, const int &b ){
        return a < b ? a : b;
    }    
};

struct table_max {
    int operator()( const int &a, const int &b ){
        return a > b ? a : b;
    }    
};

struct table_gcd {
    int operator()( const int &a, const int &b ){
        return __gcd( a, b );
    }    
};