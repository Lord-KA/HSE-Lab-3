#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

template< typename T, class Allocator = std::allocator<T> >
class vector {
private:
    using value_type        = T;
    using allocator_type    = Allocator;
    using size_type         = std::size_t;
    using iterator          = 

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
    
    constexpr iterator begin() noexcept;
                                                                //TODO add iterators;
    constexpr iterator end()   noexcept;


    //====================================
    //  Capacity

    [[nodiscard]] constexpr bool empty() const noexcept; // { return begin() == end(); } //TODO check how constexpr is sutable here

    constexpr size_type size() const noexcept { return std::distance(begin(), end()); }


};



#endif
