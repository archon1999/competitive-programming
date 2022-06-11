template<typename First, typename Second, typename Third> struct triple{ 
    First first; 
    Second second; 
    Third third; 
    
    friend bool operator < ( const triple<First, Second, Third> &t1, const triple<First, Second, Third> &t2 ) {
        if( t1.first != t2.first ) return t1.first < t2.first;
        if( t1.second != t2.second ) return t1.second < t2.second;
        return t1.third < t2.third;
    }
    
    friend bool operator == ( const triple<First, Second, Third> &t1, const triple<First, Second, Third> &t2 ) { return t1.first == t2.first && t1.second == t2.second && t1.third == t2.third; }
    friend ostream& operator << ( ostream &os, const triple<First, Second, Third> &t ) { return os << t.first << " " << t.second << " " << t.third;  }
    friend istream& operator >> ( istream &is, triple<First, Second, Third> &t ) { return is >> t.first >> t.second >> t.third; }
    friend string to_string( const triple<First, Second, Third> &t ){ return "{" + to_string( t.first ) + ", " + to_string( t.second ) + ", " + to_string( t.third ) + "}"; }
};
