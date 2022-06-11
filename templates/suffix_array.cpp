vector<int> suffix_array( const char *s ) {
    int n = strlen( s ) + 1;
    vector<pair<pair<int, int>, int> > p( n );
    vector<int> c( n );
 
    int k = 0;
    for ( int h = 0; c[p[n - 1].second] + 1 < n; h = max( 2 * h, 1 ), k++ ) {
        for( int i = 0; i < n; i++ ) p[i] = { { h == 0 ? s[i] : c[i], c[( i + h ) % n] }, i };
        stable_sort( p.begin(), p.end() );
        for ( int i = 1; i < n; i++ )
            c[p[i].second] = c[p[i - 1].second] + ( p[i].first != p[i - 1].first );
    }

    vector<int> r( n );
    for( int i = 0; i < n; i++ ) r[i] = p[i].second;
 
    return r;
}


int compare ( int i, int j, int l, int k ) {
 	pair<int,int> a = { c[k][i], c[k][i + l - ( 1 << k )] };
	pair<int,int> b = { c[k][j], c[k][j + l - ( 1 << k )] };
	return a == b ? 0 : a < b ? -1 : 1;
}
