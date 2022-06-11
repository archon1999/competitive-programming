namespace bitwise {
	inline void set( int &x, int i ){ x |= ( 1 << i ); }
	inline void reset( int &x, int i ){ x ^= ( 1 << i ); }
	inline bool check( int x, int i ){ return ( ( 1 << i ) & x ); }
	inline bool is_pow( int x ){ return x && !( x & ( x - 1 ) ); }
	inline short count( int x ){ return __builtin_popcount( x ); }
	inline int sub( int a, int b ){ return a & ( ~b ); }
	inline int low_bit( int x ){ return x - x & ( x - 1 ); }
	inline int high_bit( int x ){ x |= x >> 1; x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16; return x - ( x >> 1 );  }
}
