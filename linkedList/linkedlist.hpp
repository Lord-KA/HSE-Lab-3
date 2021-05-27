#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <vector>
#include <iostream>
#include <cassert>


template<class T, class U = T>
T exchange(T& obj, U&& new_value)
{
    T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}

//==================================
// Object pool

template<typename Data>
class ObjPool{
public:
    
    ObjPool(const ObjPool &other)
    {
        capacity = other.capacity;
        last_free = other.last_free;
        data = new Node[capacity];
        std::copy(other.data, other.data + other.capacity, data);
    }

    ObjPool(ObjPool &&other)
    {
        capacity = exchange(other.capacity, 0);
        last_free = exchange(other.last_free, -1);
        data = exchange(other.data, nullptr);
    }

    ObjPool& operator=(const ObjPool &other)
    {
        capacity = other.capacity;
        last_free = other.last_free;
        if (data)
            delete[] data;
        data = new Node[capacity];
        std::copy(other.data, other.data + other.capacity, data);
        return (*this);
    }

    ObjPool& operator=(ObjPool &&other)
    {
        capacity = exchange(other.capacity, 0);
        last_free = exchange(other.last_free, -1);
        if (data)
            delete[] data;
        data = exchange(other.data, nullptr);
        return (*this);
    }
    

    ObjPool(size_t capacity=1) : capacity(capacity) 
    {
        data = new Node [capacity];
        for (size_t i=0; i<capacity - 1; ++i)
            data[i].next = i + 1;
        data[capacity - 1].next = -1;
        
        last_free = 0;
    }
    ~ObjPool()
    {
        delete [] data;
    }
    
    size_t alloc()
    {
        refit();
        size_t result = last_free;
        last_free = data[last_free].next;
        return result;
    }
    
    Data *get(size_t id) const
    {
        assert(id != -1);
        assert(id < capacity);
        return &data[id].val;
    }
    
    void free(size_t id) 
    {
        data[id].next = last_free;
        last_free = id;
    }
    
    void print(std::ostream& out)
    {
        for (size_t id = last_free; id != -1; id = data[id].next)
        {
            out << "(" << id << ") -> ";
        }
        out << '\n';                
    }
    
    
private:
    struct Node{
        size_t next;
        Data val;
    };
    
    Node *data;
    size_t capacity;
    size_t last_free;
    
    void refit()
    {
        if (last_free != -1)
            return;
        Node *nbuf = new Node[capacity * 2];
        std::copy(data, data + capacity, nbuf);
        assert(data);
        delete [] data;
        data = nbuf;
        capacity *= 2;
        for (size_t i = capacity / 2; i < capacity - 1; ++i)
            data[i].next = i + 1;
        data[capacity - 1].next = -1;
        last_free = capacity / 2;
    }
};

//==================================
// LinkedList

template<typename T>
class linkedList {
public:
    struct Node{
        size_t next_;
        T val_;
    };

private:
    size_t head_;
    size_t size_;
    ObjPool<Node> pool;

public:
    
    linkedList() : head_(-1), size_(0) {}
    linkedList( const linkedList &other ) : head_(other.head_), size_(other.size_), pool(other.pool) {}
    linkedList( linkedList &&other ) : head_(other.head_), size_(other.size_) { pool = std::move(other.pool); }

    void insert( const T &val ) { insert(0, val); };
    void insert( size_t n, const T &val );

    T eject( size_t n = 0 );

    void dump(std::ostream &out) const;        //DEBUG

    T erase( size_t n );
    T get  ( size_t n );
};

template<typename T>
void linkedList<T>::insert(size_t n, const T &val) {
    assert(n <= size_);
    ++size_;
    if (n == 0){
        size_t id = pool.alloc();
        pool.get(id)->next_ = head_;
        pool.get(id)->val_ = val;
        head_ = id;
        return;
    }
    size_t id = head_;
    for (size_t i = 0; i < n - 1; ++i)
        id = pool.get(id)->next_;

    size_t new_id = pool.alloc();
    Node *v = pool.get(id), *new_ = pool.get(new_id);
    new_->next_ = v->next_;
    new_->val_ = val;
    v->next_ = new_id;
}

template<typename T>
T linkedList<T>::eject(size_t n) {
    assert(n < size_);
    --size_;
    if (n == 0){
        Node *v = pool.get(head_);
        head_ = v->next_;
        return v->val_;
    }
    size_t id = head_;
    for (size_t i = 0; i < n - 1; ++i)
        id = pool.get(id)->next_;
    Node *v = pool.get(id);
    size_t result_id = v->next_;
    v->next_ = pool.get(result_id)->next_;
    return pool.get(result_id)->val_;
}

template<typename T>
void linkedList<T>::dump(std::ostream &out) const {
    out << "head = " << head_ << '\n';
    out << "size = " << size_ << '\n';
    size_t id = head_;
    for (size_t i = 0; i < size_; ++i){
        out << "( " << pool.get(id)->val_ << " )";
        if (i != size_ - 1)
            out << ", ";
        else
            out << '\n';
        id = pool.get(id)->next_;
    }
}

#endif
