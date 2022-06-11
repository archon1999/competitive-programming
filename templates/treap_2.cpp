template <typename T> struct treap {

private:
	struct node {
		T sum = 0, x = 0;
		int y, cnt = 1, rev = 0;
		node * l, * r;

		node( T x ) {
			this -> sum = x;
			this -> x = x;
			this -> y = rand() | ( 1 << ( rand() % 31 ) );
			this -> l = this -> r = nullptr;
		}

		~node( ) {
			if ( l )
				delete l;
			if ( r )
				delete r;
		}
	} * root = nullptr;

public:
	pair<node *, node *> split( node * Node, int k ) {
		if ( Node == nullptr )
			return { nullptr, nullptr };
		push( Node );
		if ( cnt ( Node ) <= k )
			return { Node, nullptr };
		if ( k == 0 )
			return { nullptr, Node };
		if ( cnt ( Node -> l ) < k ) {
			pair<node *, node *> res = split( Node -> r, k - cnt ( Node -> l ) - 1 );
			Node -> r = res.first;
			update( Node );
			return { Node, res.second };
		} else {
			pair<node *, node *> res = split( Node -> l, k );
			Node -> l = res.second;
			update( Node );
			return { res.first, Node };
		}
	}

	node * merge( node * First, node * Second ) {
		if ( First == nullptr )
			return Second;
		if ( Second == nullptr )
			return First;
		if ( First -> y <= Second -> y ) {
			push( First );
			First -> r = merge( First -> r, Second );
			update( First );
			return First;
		} else {
			push( Second );
			Second -> l = merge( First, Second -> l );
			update( Second );
			return Second;
		}
	}
	void insert( int pos, T x ){
		if ( pos > size() || pos < 0 ) return;
		pair< node *, node * > res = split( root, pos );
		node * new_node = new node( x );
		root = merge( merge( res.first, new_node ), res.second );
	}

	void erase( int pos ) {
		pair<node *, node *> res_1 = split( root, pos );
		pair<node *, node *> res_2 = split( res_1.second, 1 );
		root = merge( res_1.first, res_2.second );
	}

	node * erase( int l, int r ){
		pair < node *, node * > res_1 = split( root, l );
		pair < node *, node * > res_2 = split( res_1.second, r - l + 1 );
		root = merge( res_1.first, res_2.second );
		return res_2.first;
	}

	void reverse( int l, int r ){
		pair < node *, node * > res_1 = split( root, l );
		pair < node *, node * > res_2 = split( res_1.second, r - l + 1 );
		res_2.first -> rev ^= 1;
		merge( merge( res_1.first, res_2.first ), res_2.second );
	}

	T sum( int l, int r ){
		pair < node *, node * > res_1 = split( root, l );
		pair < node *, node * > res_2 = split( res_1.second, r - l + 1 );
		T res = res_2.first -> sum;
		merge( merge( res_1.first, res_2.first ), res_2.second );
		return res;
	}

	T& order ( node *root, int pos ){
		push( root );
		T *res = nullptr;
		if( cnt( root ) - cnt( root -> r ) == pos )
			res = &root -> x;
		else if( pos > cnt( root ) - cnt( root -> r ) )
			res = &order( root -> r, pos - ( cnt( root ) - cnt( root -> r ) ) );
		else
			res = &order( root -> l, pos);
		update( root );
		return *res;
	}

	inline void push( node * Node ){
		if( Node == nullptr || Node -> rev == 0 ) 
			return;
		
		swap( Node -> l, Node -> r );
		if( Node -> l != nullptr ) Node -> l -> rev ^= 1;
		if( Node -> r != nullptr ) Node -> r -> rev ^= 1;
		Node -> rev = 0;
	}

	inline void update( node * Node ) {
		if ( Node == nullptr )
			Node -> cnt = 0;
		else {
			Node -> sum = Node -> x;
			Node -> cnt = 1;
			if ( Node -> l != nullptr ){
				Node -> sum = Node -> sum + Node -> l -> sum;
				Node -> cnt += cnt( Node -> l );
			}
			if ( Node -> r != nullptr ){
				Node -> sum = Node -> sum + Node -> r -> sum;
				Node -> cnt += cnt( Node -> r );
			}
		}
	}

	node * find( node * Node, T x ) {
		if ( Node == nullptr )
			return nullptr;
	
		if ( Node -> x == x )
			return Node;
	
		if ( Node -> x < x )
			return find( Node -> r, x );
	
		return find( Node -> l, x );
	}

	void merge( node *other ){ root = merge( root, other ); }
	node * split( int k ){ return split( root, k ); }
	T& operator []( int pos ){ return order( root, pos + 1 ); }
	inline int size( ) { return root == nullptr ? 0 : root -> cnt; }
	inline bool empty( ) { return size() == 0; }
	inline void clear( ) { root = nullptr; }
	inline int cnt( node * Node ) { return Node == nullptr ? 0 : Node -> cnt; }
	int count( T x ) { return find( root, x ) != nullptr; }
	node * find( T x ) { return find( root, x ); }

};

