namespace number {

    static const int MOD = 9_E + 7;
    random_device rd; mt19937 mt( rd( ) );
    uniform_int_distribution<long long> dist( 0, 18_E );
 
    inline int norm( int a ) { while( a < 0 ) a += MOD; while( a >= MOD ) a -= MOD; return a; }
    inline int add( int a, int b ) { return norm( a + b ); }
    inline int sub( int a, int b ) { return norm( a - b ); }
    inline int mul( int a, int b, int mod = MOD ) { return ( 1ll * a * b ) % mod; }
 
    int mul_mod( int a, int b, const int &mod = MOD ) { int s = 0; while( b ) { if( b & 1 ) s = ( s + a ) % mod; a = ( a + a ) % mod; b >>= 1; } return s; }
    int pow_mod( int a, int n, const int &mod = MOD ) { int p = 1; while( n ) { if( n & 1 ) p = mul( p, a, mod ); a = mul( a, a, mod ); n >>= 1; } return p; }
    int _pow_mod( int a, int n, const int &mod = MOD ) { int p = 1; while( n ) { if( n & 1 ) p = mul_mod( p, a, mod ); a = mul_mod( a, a, mod ); n >>= 1; } return p; }
 
    inline int inv( int a ) { return pow_mod( a, MOD - 2 ); }
    inline int div_mod( int a, int b ) { return mul( a, inv( b ) ); }
    
    inline int gcd( int a, int b ){ while( b ){ a %= b; swap( a, b ); } return a; }
    inline int lcm( int a, int b ){ return a * ( b / gcd( a, b ) ); }

    template<typename T> T sqr( T x ) { return x * x; };
    
    int sqrt_n( long long n ){
        int x = sqrt( ( long double ) n );
        while( 1ll * x * x < n ) x++;
        while( 1ll * x * x > n ) x--;
        return x;
    }

    bool miller_rabin( long long m ) {
        int s = 0, d = m - 1;
        while( d % 2 == 0 ) s++, d /= 2;
        int a = 1 + dist( mt ) % ( m - 1 );
        int x = _pow_mod( a, d, m );
        if( x == 1 ) return true;
        for( int r = 0; r < s; r++ ) { if( x == m - 1 ) return true; x = mul_mod( x, x, m ); }
        return false;
    }
 
    bool is_prime( long long n ) {
        if( n <= 4 ) return ( n == 2 || n == 3 ); 
        if( n % 2 == 0 || n % 3 == 0 ) return false;
        for( long long i = 5; i * i <= n; i += 6 ) 
            if( n % i == 0 || n % ( i + 2 ) == 0 )
                return 0; 
        return 1;
    }
    
    long long pollard_rho( long long n, int it = 50000 ) {
        long long b0 = dist( mt ) % n, b1 = b0, g;
        b1 = mul_mod( b1, b1, n );
        if( ++b1 == n ) b1 = 0;
        g = gcd( abs( b1 - b0 ), n );
        for( int count = 0; count < it && ( g == 1 || g == n ); count++ ) {
            b0 = mul_mod( b0, b0, n );
            if( ++b0 == n ) b0 = 0;
            b1 = mul_mod( b1, b1, n ); ++b1;
            b1 = mul_mod( b1, b1, n );
            if( ++b1 == n ) b1 = 0;
            g = gcd( abs( b1 - b0 ), n );
        }
        return g;
    }
 
    int gcdex( int a, int b, int & x, int & y ) {
        if( a == 0 ) { x = 0; y = 1; return b; }
        int x1, y1, d = gcdex( b % a, a, x1, y1 );
        x = y1 - ( b / a ) * x1; y = x1;
        return d;
    }

    vector<int> sieve( int n ){
        vector<int> p( n + 1, 0 );
        p[0] = p[1] = 1;
        for( int i = 2; i <= n; i++ ){
            if( !p[i] ){
                p[i] = i;
                if( 1ll * i * i <= n ){
                    for( int j = i * i; j <= n; j += i ){
                        p[j] = i;
                    }
                }
            }
        }
        return p;
    }

    vector<int> primes_list( int n ){
        vector<int> primes, sieve( n + 1, 0 );
        for( int i = 2; i <= n; i++ ){
            if( !sieve[i] ){
                primes.push_back( i );
                if( 1ll * i * i <= n ){
                    for( int j = i * i; j <= n; j += i ){
                        sieve[j] = 1;
                    }
                }
            }
        }
        return primes;
    }

    vector<int> divs_list( long long n ){
        vector<int> divs;
        for( int i = 1; 1ll * i * i <= n; i++ ){
            if( n % i == 0 ){
                divs.push_back( i );
                if( i * i != n ) {
                    divs.push_back( n / i );
                }
            }
        }
        sort( divs.begin(), divs.end() );
        return divs;
    }
    
    int divs_count( long long n ){
        int cnt = 0;
        for( int i = 1; 1ll * i * i <= n; i++ ){
            if( n % i == 0 ){
                cnt += 2;
                cnt -= ( i * i == n );
            }
        }
        return cnt;
    }

}