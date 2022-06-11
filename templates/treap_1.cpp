template <typename T> struct treap {

private:
    struct node {
		T x;
		int y, cnt = 1, rev;
		node *l, *r;
		node( T x ){
			this -> x = x;
			this -> y =  rand() | ( 1 << ( rand() % 31 ) );;
			this -> l = this -> r = nullptr;
		}

		~node ( ) {
			if ( l )
				delete l;
			if ( r )
				delete r;
		}
    } * root = nullptr;

public:
    pair<node *, node *> split ( node *Node, T x ){
	    if ( Node == nullptr )
		    return { nullptr, nullptr };
	    
		push ( Node );
	    if ( Node -> x <= x ){
		    pair < node *, node * > res = split ( Node -> r, x );
		    Node -> r = res.first;
		    upd ( Node );
		    return { Node, res.second };
	    } else {
		    pair < node *, node * > res = split ( Node -> l, x );
		    Node -> l = res.second;
		    upd ( Node );
		    return { res.first, Node };
	    }
    }

    node * merge( node * First, node * Second ){
	    if ( First == nullptr )
		    return Second;
	
	    if ( Second == nullptr )
		    return First;
	
	    push ( First );
	    push ( Second );
	    if ( First -> y <= Second -> y ){
		    First -> r = merge ( First -> r, Second );
		    upd ( First );
		    return First;
	    } else {
		    Second -> l = merge ( First, Second -> l );
		    upd ( Second );
		    return Second;
	    }
    }

    node * find ( node * Node, T x ){
	    if ( Node == nullptr )
		    return nullptr;
	    if ( Node -> x == x )
		    return Node;
	    if ( Node -> x < x )
		    return find ( Node -> r, x );
	    return find ( Node -> l, x );
    }

    node * insert( node * Node, T x ){
	    if ( count( x ) ) return root;
	    pair < node *, node * > res = split ( root, x );
	    node * new_node = new node ( x );
	    return merge ( merge ( res.first, new_node ), res.second ) ;
    }

    void reverse ( node * Node, int l, int r ){
            pair < node *, node * > res_1 = split ( Node, l - 1 );
            pair < node *, node * > res_2 = split ( res_1.second, r );
    	    res_2.first -> rev ^= 1;
    	    merge ( merge ( res_1.first, res_2.first ), res_2.second );
    }

	node * erase ( node * Node, T x ){
	    if ( !count ( x ) ) return root;
	    pair < node *, node * > res_1 = split ( root, x - 1 );
	    pair < node *, node * > res_2 = split ( res_1.second, x );
	    return merge ( res_1.first, res_2.second );
    }

    int kth_elem( node * Node, int k ){
	    if ( Node == nullptr )
		    return 0;
 
	    if ( k == cnt ( Node -> l ) ) return Node -> x;
 
	    if ( k > cnt ( Node -> l ) )
		    return kth_elem ( Node -> r, k - cnt ( Node -> l ) - 1 );
	    else
		    return kth_elem ( Node -> l, k );
    }

    int order( node * Node, int x, int k = 1 ){
	    if( Node == nullptr )
		    return k - 1;
	    if( Node -> x == x )
		    return k + cnt ( Node -> l );
	    if( x > Node -> x )
		    return order ( Node -> r, x, k + cnt ( Node -> l ) + 1 );
	    else
		    return order ( Node -> l, x, k );
    }
    
	inline void upd ( node * Node ){
	    if ( Node == nullptr )
		    Node -> cnt = 0;
	    else
		    Node -> cnt = cnt ( Node -> l ) + cnt ( Node -> r ) + 1;
    }
    
	void push ( node * Node ){
    	if ( Node == nullptr || !Node -> rev ) 
			return;
    	
		swap ( Node -> l, Node -> r );
    	if ( Node -> l != nullptr )
    	    Node -> l -> rev ^= 1;
	    
		if ( Node -> r != nullptr )
		    Node -> r -> rev ^= 1;
	    
		Node -> rev = 0;
    }

	int cnt ( node * Node ) { return Node != nullptr ? Node -> cnt : 0 };
	node * split( int x ){ return split( root, x ); }
	void merge( node *other ) { root = merge( root, other ); }
	void reverse ( int l, int r ){ reverse ( root, l, r ); }
	int order ( int x ) { return order ( root, x - 1 ); }
    int kth_elem ( int k ) { return kth_elem ( root, k - 1 ); }
    int max () { return kth_elem ( root -> cnt - 1 ); }
    int min () { return kth_elem ( 0 ); }
    node * insert ( T x ) { return root = insert ( root, x ); }
    node * find ( T x ) { return find ( root, x ); }
    node * erase ( T x ) { return root = erase ( root, x ); }
    int count ( T x ) { return find ( root, x ) != nullptr; }
};
 