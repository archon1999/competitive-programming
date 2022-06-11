#include <iostream>
#include <assert.h>

using namespace std;

template<typename T> struct list {

private:
    struct node {
        T value;
        node * next, * prev;
        node(T elem){
            value = elem;
            next = prev = nullptr;
        }
        ~node(){
            if(next) delete next;
            if(prev) delete prev;
        }
    };
    node * first = nullptr;
    node * last = nullptr;

public:
    size_t sz = 0;
    size_t size(){
        return sz;
    }

    void push_back(T elem){
        sz++;
        if(first == nullptr){
            first = new node(elem);
        } else {
            if(last == nullptr){
                last = new node(elem);  
                first -> next = last;
                last -> prev = first;       
            } else {
                node * new_node = new node(elem);
                new_node -> prev = last;
                last -> next = new_node;
                last = last -> next;
            }
        }
    }

    void push_front(T elem){
        sz++;
        if(first == nullptr){
            first = new node(elem);
        } else {
            node * new_node = new node(elem);
            if(last == nullptr){
                last = first;
                last -> prev = new_node;
                first = new_node;
                first -> next = last;
            } else {
                first -> prev = new_node;
                new_node -> next = first;
                first = new_node;
            }
        }
    }

    node * nth_node(int n, node * first){
        if( n == 1 ) {
            return first;
        }
        return nth_node(n - 1, first -> next);
    }

    void erase(int n){
        assert(sz >= n);
        sz--;
        node * temp = nth_node(n, first);
        if(temp -> next != nullptr){
            if(temp -> prev != nullptr){
                temp -> prev -> next = temp -> next;
                temp -> next -> prev = temp -> prev;
            } else {
                temp -> next -> prev = nullptr;      
            }
            temp = temp -> next;
        } else {
            temp = nullptr;
        }   
    }
    void pop_back(){
        assert(first != nullptr);
        sz--;
        if(last != nullptr){
            if(last -> prev != nullptr){
                last = last -> prev;
            } else {
                delete last;
            }
        } else {
            delete first;
        }
    }

    void pop_front(){
        assert(first != nullptr);
        sz--;
        if(last != nullptr){
            if(last -> next != nullptr){
                first = last;
                last = last -> next;
            } else {
                first = last;
                delete last;
            }
        } else {
            delete first;
        }
    }

    void print(){
        while(first != nullptr){
            cout << first -> value << " ";
            first = first -> next;
        }
    }

};

int main(){

    list<int> ls;
    
    int n;
    cin >> n;
    
    for( int i = 0; i < n; i++ ){
        int val;
        cin >> val;
        ls.push_back(val);
    }

    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(i % 3 == 0) {
            ls.erase(i - cnt);
            cnt++;
        }
    }
    ls.print();
    
}