
template<typename T> struct dsu {
    
    vector<int> p, _size;

    dsu( int n ){
        p.resize( n + 1 );
        _size.resize( n + 1 );
        for( int i = 0; i <= n; i++ ) {
            p[i] = i;
            _size[i] = 1;
        }
    }

    T get( T v ){
        return v == p[v] ? v : p[v] = get( p[v] );
    }

    bool join( T a, T b ){
        a = get( a );
        b = get( b );
        if( a != b ){
            if( _size[a] > _size[b] ) swap( a, b );
            _size[b] += _size[a];
            p[a] = b;
            return true;
        }
        return false;
    }

    int size( int v ){
        return _size[get( v )];
    }
    
};