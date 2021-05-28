#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cassert>



template< typename T, class Allocator = std::allocator<T> >
class vector {
private:
    using value_type        = T;
    using allocator_type    = Allocator;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    //using iterator          = 


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
    constexpr vector( InputIt first, InputIt last,
                               const Allocator& alloc = Allocator() );

    constexpr vector( const vector& other,
                      const Allocator& alloc = Allocator() );
    
    constexpr vector( vector&& other,
                      const Allocator& alloc = Allocator() );

    constexpr vector( std::initializer_list<T> init,
                      const Allocator& alloc = Allocator() );

    constexpr ~vector();

    
    constexpr vector& operator=( const vector& other );

    constexpr vector& operator=( vector&& other ) ;             //TODO add noexcept

    constexpr vector& operator=( std::initializer_list<T> ilist );
    

    constexpr void assign( size_type count, const T& value );
    
    template< class InputIt >
    constexpr void assign( InputIt first, InputIt last );

    constexpr void assign( std::initializer_list<T> ilist );


    constexpr allocator_type get_allocator() const noexcept;

    //====================================
    //  Element access

    constexpr T& at( size_type pos );
    
    constexpr const T& at( size_type pos ) const;


    constexpr T& operator[]( size_type pos );
    
    constexpr const T& operator[]( size_type pos ) const;


    constexpr T& front();
    
    constexpr const T& front() const;

    constexpr T& back();
    
    constexpr const T& back() const;
    
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

        T& operator*() { assert(id_ < this_->size()); return this_->data[id_]; }               
        const T& operator*() const { assert(id_ < this_->size()); return this_->data[id_]; }

        T& operator[]( long long int n ) { assert(id_ + n < this_->size()); return this_->data[id_ + n]; }
        const T& operator[]( long long int n ) const { assert(id_ + n < this_->size());return this_->data[id_ + n]; }


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

    [[nodiscard]] constexpr bool empty() const noexcept { return begin() == end(); } //TODO check how constexpr is sutable here

    constexpr size_type size() const noexcept { return size_; }

    constexpr size_type max_size() const noexcept { return std::numeric_limits<difference_type>::max(); }

    constexpr void reserve( size_type new_cap );

    constexpr size_type capacity() const noexcept { return capacity_; }

    constexpr void shrink_to_fit();


    //====================================
    //  Modifiers

    constexpr void clear() noexcept { if (data) delete[] data; size_ = 0; capacity_ = 0; };

    constexpr iterator insert( const iterator pos, const T& value );

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

    constexpr void resize( size_type count, const T& value );

    constexpr void swap( vector& other ) noexcept { std::swap(data, other.data); std::swap(capacity_, other.capacity_); std::swap(size_, other.size_); }


private:
    T* data;
    size_type capacity_;
    size_type size_;

};



#endif
