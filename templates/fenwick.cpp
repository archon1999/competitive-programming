
struct fenwick{

	vector<int> fw;

	fenwick() { }

	fenwick( int n ){
		fw.resize( n + 1, 0 );
	}

	void init( int n ){
		fw.clear();
		fw.resize( n + 1, 0 );
	} 

	void update( int pos, int x ){
		for( int i = pos; i < fw.size(); i |= i + 1 ){
			fw[i] += x;
		}
	}

	int get( int r ){
		int s = 0;
		for( int i = r; i >= 0; ( i &= i + 1 )-- ){
			s += fw[i];
		}
		return s;
	}

	int get( int l, int r ){
		return get( r ) - get( l - 1 );
	}

};
