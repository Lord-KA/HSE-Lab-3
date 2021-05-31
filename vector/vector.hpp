#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <utility>
#include <cassert>
#include <type_traits>
#include <algorithm>


template< typename T, class Allocator = std::allocator<T> >
class vector {
private:
    using value_type        = T;
    using allocator_type    = Allocator;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;

public:
    //====================================
    //  Member functions
    
    constexpr vector() noexcept(noexcept(Allocator()));
    
    constexpr explicit vector( const Allocator& alloc ) noexcept;

    constexpr explicit vector( size_type count,
                               const T& value = T(),
                               const Allocator& alloc = Allocator() );
    
    constexpr explicit vector( size_type count,
                               const Allocator& alloc = Allocator() );

    template< class InputIt >
    constexpr explicit vector( InputIt first, InputIt last,              
                               const Allocator& alloc = Allocator() ) -> vector<typename std::iterator_traits<InputIt>::value_type>; 

    constexpr vector( const vector& other );

    constexpr vector( const vector& other, const Allocator& alloc );
    
    constexpr vector( vector&& other );

    constexpr vector( vector&& other, const Allocator& alloc ); 

    constexpr vector( std::initializer_list<T> init,                //TODO
                      const Allocator& alloc = Allocator() );

    constexpr ~vector() { allocator_.deallocate(data_, capacity_); }

    
    constexpr vector& operator=( const vector& other );

    constexpr vector& operator=( vector&& other ) noexcept ;

    constexpr vector& operator=( std::initializer_list<T> ilist );  //TODO
    

    constexpr void assign( size_type count, const T& value );
    
    template< class InputIt >
    constexpr void assign( InputIt first, InputIt last );

    constexpr void assign( std::initializer_list<T> ilist );        //TODO


    constexpr allocator_type get_allocator() const noexcept { return allocator_; }

    //====================================
    //  Element access

    constexpr T& at( size_type pos );
    
    constexpr const T& at( size_type pos ) const;


    constexpr T& operator[]( size_type pos );
    
    constexpr const T& operator[]( size_type pos ) const;


    constexpr T& front()             { assert(size_); return data_[0]; }
    
    constexpr const T& front() const { assert(size_); return data_[0]; }

    constexpr T& back()              { assert(size_); return data_[size_ - 1]; }
    
    constexpr const T& back()  const { assert(size_); return data_[size_ - 1]; }
    
    //====================================
    //  Iterators
    
    struct iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        iterator( size_t id = 0, vector* this_ = nullptr ) : id_(id), this_(this_) {}
        iterator( const iterator& other) = default;

        bool operator==( const iterator &other ) const { return id_ == other.id_; }
        bool operator!=( const iterator &other ) const { return id_ != other.id_; }

        bool operator< ( const iterator &other ) const { return id_ <  other.id_; }
        bool operator> ( const iterator &other ) const { return id_ >  other.id_; }
        bool operator<=( const iterator &other ) const { return id_ <= other.id_; }
        bool operator>=( const iterator &other ) const { return id_ >= other.id_; }

        T& operator*() { assert(id_ < this_->size()); return this_->data_[id_]; }               
        const T& operator*() const { assert(id_ < this_->size()); return this_->data_[id_]; }

        T& operator[]( long long int n ) { assert(id_ + n < this_->size()); return this_->data_[id_ + n]; }
        const T& operator[]( long long int n ) const { assert(id_ + n < this_->size());return this_->data_[id_ + n]; }


        iterator operator++() {
            ++id_;
            return *this;
        }

        iterator operator++(int) {
            iterator result(*this);
            ++id_;
            return result;
        }

        iterator operator--() {
            --id_;
            return *this;
        }

        iterator operator--(int) {
            iterator result(*this);
            --id_;
            return result;
        }

        iterator operator+(long long int n) const {
            iterator result(*this);
            result.id_ += n;
            return result;
        }

        long long operator-(const iterator& other) const {
            return id_ - other.id_;
        }

        iterator operator-(long long int n) const { 
            iterator result(*this);
            result.id_ -= n;
            return result;
        }

        iterator operator+=(long long int n){
            id_ += n;
            return (*this);
        }

        iterator operator-=(long long int n){
            id_ -= n;
            return (*this);
        }




    private:
        size_t id_;
        const vector* this_;
    };
    
    constexpr iterator begin() noexcept { return iterator(0, this); }

    constexpr iterator end()   noexcept { return iterator(this->size(), this); }


    //====================================
    //  Capacity

    [[nodiscard]] constexpr bool empty() const noexcept { return begin() == end(); } 

    constexpr size_type size() const noexcept { return size_; }

    constexpr size_type max_size() const noexcept { return allocator_.max_size(); }

    constexpr void reserve( size_type new_cap );

    constexpr size_type capacity() const noexcept { return capacity_; }

    constexpr void shrink_to_fit();


    //====================================
    //  Modifiers

    constexpr void clear() noexcept { if (data_) allocator_.deallocate(data_, capacity_); size_ = 0; capacity_ = 0; }

    constexpr iterator insert( const iterator pos, const T& value ); //TODO all insert(), emplace() and erase()

    constexpr iterator insert( const iterator pos, T&& value );

    constexpr iterator insert( const iterator pos, size_type count, const T& value );

    template<class InputIt>
    constexpr iterator insert( const iterator pos, InputIt first, InputIt last );

    constexpr iterator insert( const iterator pos, std::initializer_list<T> ilist);

    template<class... Args>
    constexpr iterator emplace( const iterator pos, Args&&... args );

    constexpr iterator erase( const iterator pos );

    constexpr iterator erase( const iterator first, const iterator last );

    constexpr void push_back( const T& value );

    constexpr void push_back( T&& value );

    template<class... Args>
    constexpr T* emplace_back( Args&&... args);

    constexpr void pop_back() noexcept { assert(size_); --size_; };

    constexpr void resize( size_type count );

    constexpr void resize( size_type count, const T& value = T() );

    constexpr void swap( vector& other ) noexcept { std::swap(data_, other.data_); std::swap(capacity_, other.capacity_); std::swap(size_, other.size_); }


private:
    Allocator allocator_;
    T* data_;
    size_type capacity_;
    size_type size_;

#ifndef NDEBUG
public:
    void dump(std::ostream& out) {
        out << "capacity = " << capacity_ << "\n";
        out << "size     = " << size_ << "\n";
        for (auto elem : *this)
            out << "{ " << elem << " } ";
        out << '\n';
    }


#endif
};




template< typename T, class Allocator >
constexpr vector<T, Allocator>::vector() noexcept(noexcept(Allocator())) : data_(nullptr), capacity_(0), size_(0) {}


template< typename T, class Allocator >
constexpr vector<T, Allocator>::vector( const Allocator& alloc ) noexcept : allocator_(alloc), data_(nullptr), capacity_(0), size_(0) {}


template< typename T, class Allocator >
constexpr vector<T, Allocator>::vector( size_type count, const T& value, const Allocator& alloc) : allocator_(alloc), data_(nullptr), capacity_(count), size_(count) {
    data_ = allocator_.allocate(capacity_);
    if (!data_)
        throw std::runtime_error("Failed to allocate memory");
    std::fill(data_, data_ + capacity_, value);
}


template< typename T, class Allocator >
constexpr vector<T, Allocator>::vector( size_type count, const Allocator& alloc ) : allocator_(alloc), data_(nullptr), capacity_(count), size_(count) {
    data_ = allocator_.allocate(capacity_);
    if (!data_)
        throw std::runtime_error("Failed to allocate memory");
}


template< typename T, class Allocator >                  
template< class InputIt >
constexpr explicit vector<T, Allocator>::vector( InputIt first, InputIt last,
                               const Allocator& alloc ) -> vector<typename std::iterator_traits<InputIt>::value_type> : allocator_(alloc), data_(nullptr), capacity_(0), size_(0) {

    for (; first != last; ++first){
        if (size_ == capacity_){
            if (!data_){
                capacity_ = 2;
                data_ = allocator_.allocate(capacity_);
                if (!data_)
                    throw std::runtime_error("Failed to allocate memory");
            }
            else {
                size_t new_cap = capacity_ * 2;
                T* tmp = allocator_.allocate(new_cap);
                if (!tmp)
                    throw std::runtime_error("Failed to allocate memory");
                std::copy(data_, data_ + capacity_, tmp);           //TODO think if it is more effitient (sometimes?) to make element-wise move
                allocator_.deallocate(data_, capacity_);
                data_ = tmp;
                capacity_ = new_cap;
            }
        }
        data_[size_] = (*(first));
        ++size_;
    }
}


template< typename T, class Allocator >
constexpr vector<T, Allocator>::vector( const vector& other ) : allocator_(other.allocator_), data_(nullptr), capacity_(other.capacity_), size_(other.size_) {
    data_ = allocator_.allocate(capacity_);
    if (!data_)
        throw std::runtime_error("Failed to allocate memory");
    std::copy(other.begin(), other.end(), data_);
}


template< typename T, class Allocator >
constexpr vector<T, Allocator>::vector( const vector& other, const Allocator& alloc ) : allocator_(alloc), capacity_(other.capacity_), size_(other.size_) {
    data_ = allocator_.allocate(capacity_);
    if (!data_)
        throw std::runtime_error("Failed to allocate memory");
    std::copy(other.begin(), other.end(), data_);
}


template< typename T, class Allocator >
constexpr vector<T, Allocator>::vector( vector&& other ) : allocator_(other.allocator_), data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}


template< typename T, class Allocator >
constexpr vector<T, Allocator>::vector( vector&& other, const Allocator& alloc ) : allocator_(alloc), data_(nullptr), capacity_(other.capacity_), size_(other.size_) {
    if (alloc != other.allocator_){                         //TODO check if this it the right way of element-wise move
        data_ = allocator_.allocate(capacity_);
        if (!data_)
            throw std::runtime_error("Failed to allocate memory");

        if (std::is_move_assignable<T>::value)
            for (size_t i = 0; i < size_; ++i)
                data_[i] = std::move(other.data_[i]);
        else
            std::copy(other.begin(), other.end(), data_);
    }
    else {
        data_ = other.data_;
        other.size_ = 0;
        other.capacity_ = 0;
    }
}


template< typename T, class Allocator >
constexpr vector<T, Allocator>& vector<T, Allocator>::operator=( const vector& other ) {
    size_ = other.size_;
    if (data_)
        allocator_.deallocate(data_, capacity_);
    capacity_ = other.capacity_;
    data_ = allocator_.allocate(capacity_);
    if (!data_)
        throw std::runtime_error("Failed to allocate memory");
    std::copy(other.begin(), other.end(), data_);
    return *this;
}


template< typename T, class Allocator >
constexpr vector<T, Allocator>& vector<T, Allocator>::operator=( vector&& other ) noexcept {
    allocator_= other.allocator_;
    capacity_ = std::exchange(other.capacity_, 0);
    size_ = std::exchange(other.size_, 0);
    data_ = std::exchange(other.data_, nullptr);
    return *this;
}


template< typename T, class Allocator >
constexpr void vector<T, Allocator>::assign( size_type count, const T& value) {
    if (capacity_ < count){
        allocator_.deallocate(data_, capacity_);
        capacity_ = count;
        data_ = allocator_.allocate(capacity_);
        if (!data_)
            throw std::runtime_error("Failed to allocate memory");
    }
    size_ = count;
    std::fill(data_, data_ + size_, value);
}


template< typename T, class Allocator >
template< class InputIt >
constexpr void vector<T, Allocator>::assign( InputIt first, InputIt last) {
    size_ = 0;
    for (; first != last; ++first){
        if (size_ == capacity_){
            if (!data_){
                capacity_ = 2;
                data_ = allocator_.allocate(capacity_);
                if (!data_)
                    throw std::runtime_error("Failed to allocate memory");
            }
            else {
                size_t new_cap = capacity_ * 2;
                T* tmp = allocator_.allocate(new_cap);
                if (!tmp)
                    throw std::runtime_error("Failed to allocate memory");
                std::copy(data_, data_ + capacity_, tmp);           //TODO think if it is more effitient (sometimes?) to make element-wise move
                allocator_.deallocate(data_, capacity_);
                data_ = tmp;
                capacity_ = new_cap;
            }
        }
        data_[size_] = *first;
        ++size_;
    }
}


template< typename T, class Allocator >
constexpr T& vector<T, Allocator>::at( size_type pos ) {
    if (pos >= size())
        throw std::out_of_range("Position given to at() is invalid");
    return data_[pos];
}


template< typename T, class Allocator >
constexpr const T& vector<T, Allocator>::at( size_type pos ) const {
    if (pos >= size())
        throw std::out_of_range("Position given to at() is invalid");
    return data_[pos];
}


template< typename T, class Allocator >
constexpr T& vector<T, Allocator>::operator[]( size_type pos ) {
    assert(pos < size());
    return data_[pos];
}


template< typename T, class Allocator >
constexpr const T& vector<T, Allocator>::operator[]( size_type pos ) const {
    assert(pos < size());
    return data_[pos];
}


template< typename T, class Allocator >
constexpr void vector<T, Allocator>::reserve( size_type new_cap ) {
    if (new_cap > capacity_){
        T* tmp = allocator_.allocate(new_cap);
        if (!tmp)
            throw std::runtime_error("Failed to allocate memory");
    
        if (data_){
            std::copy(data_, data_ + size_, tmp);
            allocator_.deallocate(data_, capacity_);
        }
        data_ = tmp;
        capacity_ = new_cap;
    }
}


template< typename T, class Allocator >
constexpr void vector<T, Allocator>::shrink_to_fit() {
    if (size_ != capacity_){
        T* tmp = allocator_.allocate(size_);
        if (!tmp)
            throw std::runtime_error("Failed to allocate memory");

        std::copy(data_, data_ + size_, tmp);
        allocator_.deallocate(data_, capacity_);
        data_ = tmp;
        capacity_ = size_;
    }
}


template< typename T, class Allocator >             //TODO
constexpr typename vector<T, Allocator>::iterator vector<T, Allocator>::insert( const vector<T, Allocator>::iterator pos, const T& value ) {
    
}


template< typename T, class Allocator >
constexpr void vector<T, Allocator>::push_back( const T& value ) {
    if (size_ == capacity_ || !capacity_){
        if (!capacity_)
            capacity_ = 1;
        reserve(capacity_ * 2);
    }
   
    data_[size_] = value;
    ++size_;
}


template< typename T, class Allocator >
constexpr void vector<T, Allocator>::push_back( T&& value ) {
    if (size_ == capacity_ || !capacity_){
        if (!capacity_)
            capacity_ = 1;
        reserve(capacity_ * 2);
    }

    data_[size_] = std::move(value);
    ++size_;
} 


template< typename T, class Allocator >
template<class... Args>
constexpr T* vector<T, Allocator>::emplace_back( Args&&... args) {
    if (size_ == capacity_ || !capacity_){
        if (!capacity_)
            capacity_ = 1;
        reserve(capacity_ * 2);
    }

    allocator_.construct(data_ + size_, args...);
    ++size_;
}


template< typename T, class Allocator >
constexpr void vector<T, Allocator>::resize( size_type count ) {
    if (count == size_)
        return;
    T* tmp = allocator_.allocate(count);
    if (!tmp)
        throw std::runtime_error("Failed to allocate memory");
 
    if (count < size_)
        std::copy(data_, data_ + count, tmp);

    if (count > size_){
        std::copy(data_, data_ + size_, tmp);
    }

    allocator_.deallocate(data_, capacity_);
    data_ = tmp;
    capacity_ = count;
}


template< typename T, class Allocator >
constexpr void vector<T, Allocator>::resize( size_type count, const T& value ) {
    if (count == size_)
        return;
    T* tmp = allocator_.allocate(count);
    if (!tmp)
        throw std::runtime_error("Failed to allocate memory");
 
    if (count < size_)
        std::copy(data_, data_ + count, tmp);

    if (count > size_){
        std::copy(data_, data_ + size_, tmp);
        std::fill(tmp + size_, tmp + count, value);
    }

    allocator_.deallocate(data_, capacity_);
    data_ = tmp;
    capacity_ = count;
}



#endif
