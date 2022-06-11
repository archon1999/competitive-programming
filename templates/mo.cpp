
struct mo {

    typedef int64_t answer_type;

    struct query {
        int l, r, i;
        int64_t ord;
        answer_type ans = 0;
        
        query(){ }
        query( int l, int r, int i ) : l( l ), r( r ), i( i ) { ord = gilbert_order( l, r, 21, 0 ); }
        query( const query& other ) : query( other.l, other.r, other.i ){}

        friend bool operator < ( const query &a, const query &b ) {
            return a.ord < b.ord;
        }
        
        friend string to_string( const query& q ){
            return "{" + to_string( q.l ) + ", " + to_string( q.r ) + ", " + to_string( q.i ) + "}";
        }
    };

    vector<query> queries;
    int _size = 0;
    
    mo( int n ) { queries.resize( n ); }
    mo() {}

    struct solver {
        int32_t l = 1, r = 0;

        static const int MAXN = 20001;
    
        answer_type ans = 0;

        inline void add_left(){
            l--;
            //**//
        }

        inline void add_right(){
            r++;
            //**//

        }

        inline void remove_left(){   
            //**//
            l++;
        }

        inline void remove_right(){
            //**//
            r--;
        }

        inline answer_type get_ans(){
            return ans;
        }

    };

    void solve(){
        sort();
        solver solution;
        for( int i = 0; i < _size; i++ ){
            auto &q = queries[i];
            while( solution.r < q.r ){
                solution.add_right();
            }

            while( solution.r > q.r ){
                solution.remove_right();
            }

            while( solution.l < q.l ){
                solution.remove_left();
            }

            while( solution.l > q.l ){
                solution.add_left();
            }

            q.ans = solution.get_ans();
        }
    }

    void insert( int l, int r, int i ){
        if( _size < queries.size() ){
            queries[_size] = query( l, r, i );
        } else {
            queries.push_back( query( l, r, i ) );
        }
        _size++;
    }

    query& get( size_t i ){
        assert( i < _size );
        return queries[i];
    }

    vector<answer_type> get_answers(){
        vector<answer_type> answers( _size );
        for( int i = 0; i < _size; i++ ){
            answers[queries[i].i] = queries[i].ans;
        }
        return answers;
    }

    void sort(){
        std::sort( queries.begin(), queries.begin() + _size ); 
    }

    int size(){
        return _size;
    }

    inline static int64_t gilbert_order( int x, int y, int pow, int rotate ) {
        if ( pow == 0 ) {
            return 0;
        }
        int hpow = 1 << ( pow - 1 );
        int seg = ( x < hpow ) ? (
            ( y < hpow ) ? 0 : 3
        ) : (
            ( y < hpow ) ? 1 : 2
        );
        seg = ( seg + rotate ) & 3;
        const int rotate_delta[4] = { 3, 0, 0, 1 };
        int nx = x & ( x ^ hpow ), ny = y & ( y ^ hpow );
        int nrot = ( rotate + rotate_delta[seg] ) & 3;
        int64_t sub_square_size = int64_t(1) << ( 2 * pow - 2 );
        int64_t ans = seg * sub_square_size;
        int64_t add = gilbert_order( nx, ny, pow - 1, nrot );
        ans += ( seg == 1 || seg == 2 ) ? add : ( sub_square_size - add - 1 );
        return ans;
    }

};