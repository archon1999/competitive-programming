#include<bits/stdc++.h>

using namespace std;

template < typename T >
struct bst {
private:
	struct node {
		node * l, * r;
		T key;
	};
	int cnt = 0;
	node * root;
public:
	bst( T value ) {
		root = new node;
		root->key = value;
		root->l = root->r = NULL;
	}

	bst( ) {
		root = NULL;
	};

	void push( T value ) {
		push( value, root );
	}

	void push( T value, node *& Node ) {
		if ( Node == NULL ) {
			cnt++;
			Node = new node;
			Node->key = value;
			Node->l = Node->r = NULL;
		} else {
			if ( value > Node->key )
				push( value, Node->r );
			if ( value < Node->key )
				push( value, Node->l );
		}
	}

	bool find( T value ) {
		return find( value, root );
	}

	bool find( T value, node * Node ) {
		if ( Node == NULL )
			return 0;
		if ( Node->key == value )
			return 1;
		if ( value > Node->key )
			return find( value, Node->r );
		if ( value < Node->key )
			return find( value, Node->l );
	}

	int size( ) {
		return cnt;
	}

	void print( ) {
		print( root );
	}

	void print( node * Node ) {
		if ( Node != NULL ) {
			print( Node->l );
			cout << Node->key << " ";
			print( Node->r );
		}
	}
};

int main( ) {

	int n;
	cin >> n;
	vector<int> vc( n );

	bst<int> tree;
	
	for ( int i = 0; i < n; i++ ) scanf( "%d", &vc[i] );
	
	random_shuffle( vc.begin(), vc.end() );
	
	for ( int i = 0; i < n; i++ ) tree.push( vc[i] );
	
	tree.print( );
}