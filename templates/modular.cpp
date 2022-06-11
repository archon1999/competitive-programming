template<typename T> struct modular {
 
	static const T mod = ( int ) 1e9 + 7;
 
	T x = 0;
	modular(){}
	modular( int x ){ this -> x = norm( x ); }
 
	T norm( int a ) { if( a > mod ) a %= mod; if( a < 0 ) a = ( a % mod + mod ); return a; }
	modular norm( modular m ){ return m.x = norm( m.x ); }
 
	modular operator - () { return modular( -x ); }
	modular operator ++ () { return modular( ++x ); }
 
	modular & operator += ( const modular &m ){ this -> x = norm( this -> x + m.x ); return *this; }
	modular & operator -= ( const modular &m ){ this -> x = norm( this -> x - m.x ); return *this; }
	modular & operator *= ( const modular &m ){ this -> x = ( 1ll * m.x % mod * this -> x ) % mod; return *this; }
	modular & operator /= ( const modular &m ){ return *this *= inv( m ); }
 
	modular & operator += ( const int &x ){ this -> x = norm( this -> x + x ); return *this; }
	modular & operator -= ( const int &x ){ this -> x = norm( this -> x - x ); return *this; }
	modular & operator *= ( const int &x ){ this -> x = ( 1ll * x % mod * this -> x ) % mod; return *this; }
	modular & operator /= ( const int &x ){ return *this *= inv( modular( x ) ); }
 
	friend bool operator < ( modular &a, modular &b ) { return a.x < b.x; }
	friend bool operator == ( modular &a, modular &b ) { return a.x == b.x; }
	friend bool operator != ( modular &a, modular &b ) { return a.x != b.x; }
 
	friend modular operator + ( modular a, modular b ){ return a += b; }
	friend modular operator - ( modular a, modular b ){ return a -= b; }
	friend modular operator * ( modular a, modular b ){ return a *= b; }
	friend modular operator / ( modular a, modular b ){ return a /= b; }
 
	friend modular inv( modular m ){ return pow( m, mod - 2 ); }
	friend modular pow( modular m, long long n ){ modular res( 1 ); while( n ){ if( n & 1 ) res *= m; m *= m; n >>= 1; } return res; }
	friend modular mul( modular m, long long n ){ modular res; while( n ){ if( n & 1 ) res += m; m += m; n >>= 1; } return res; }
 
	friend ostream & operator << ( ostream &os, modular m ){ return os << m.x; }
	friend istream & operator >> ( istream &is, modular m ){ return is >> m.x; }
 
};
