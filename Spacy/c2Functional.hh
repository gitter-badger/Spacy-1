// This file was automatically generated by friendly type erasure.
// Please do not modify.

#pragma once

#include <array>
#include "Spacy/Util/table_util.hh"
#include <Spacy/Spaces/RealSpace/real.hh>
#include <Spacy/linearOperator.hh>
#include <Spacy/vector.hh>
#include <Spacy/vectorSpace.hh>
#include "Detail/details_for_c2Functional.hh"

namespace Spacy
{
    /// Type-erased twice differentiable functional \f$f:\ X \to \mathbb{R} \f$.
    class C2Functional
    {
    public:
        C2Functional() noexcept;

        template < typename T, typename std::enable_if< C2FunctionalDetail::C2FunctionalConcept<
                                   C2Functional, typename std::decay< T >::type >::value >::type* = nullptr >
        C2Functional( T&& value )
            : functions_(
                  {&type_erasure_table_detail::clone_into_shared_ptr< typename std::decay< T >::type >,
                   &type_erasure_table_detail::clone_into_buffer< typename std::decay< T >::type, Buffer >,
                   &C2FunctionalDetail::execution_wrapper< C2Functional,
                                                           typename std::decay< T >::type >::call_const_Vector_ref,
                   &C2FunctionalDetail::execution_wrapper< C2Functional, typename std::decay< T >::type >::d1,
                   &C2FunctionalDetail::execution_wrapper< C2Functional, typename std::decay< T >::type >::d2,
                   &C2FunctionalDetail::execution_wrapper< C2Functional, typename std::decay< T >::type >::hessian,
                   &C2FunctionalDetail::execution_wrapper< C2Functional, typename std::decay< T >::type >::domain} ),
              type_id_( typeid( typename std::decay< T >::type ).hash_code() ), impl_( nullptr )
        {
            if ( sizeof( typename std::decay< T >::type ) <= sizeof( Buffer ) )
            {
                new ( &buffer_ ) typename std::decay< T >::type( std::forward< T >( value ) );
                impl_ = std::shared_ptr< typename std::decay< T >::type >(
                    std::shared_ptr< typename std::decay< T >::type >(),
                    static_cast< typename std::decay< T >::type* >( static_cast< void* >( &buffer_ ) ) );
            }
            else
                impl_ = std::make_shared< typename std::decay< T >::type >( std::forward< T >( value ) );
        }

        C2Functional( const C2Functional& other );

        C2Functional( C2Functional&& other ) noexcept;

        template < typename T, typename std::enable_if< C2FunctionalDetail::C2FunctionalConcept<
                                   C2Functional, typename std::decay< T >::type >::value >::type* = nullptr >
        C2Functional& operator=( T&& value )
        {
            return *this = C2Functional( std::forward< T >( value ) );
        }

        C2Functional& operator=( const C2Functional& other );

        C2Functional& operator=( C2Functional&& other ) noexcept;

        /**
         * @brief Checks if the type-erased interface holds an implementation.
         * @return true if an implementation is stored, else false
         */
        explicit operator bool() const noexcept;

        /// Apply functional.
        Real operator()( const Vector& x ) const;

        /// Compute derivative as function space element in \f$X^*\f$, where \f$x\in X\f$.
        Vector d1( const Vector& x ) const;

        /// Compute second derivative as function space element in \f$X^*\f$, where \f$x,dx\in X\f$.
        Vector d2( const Vector& x, const Vector& dx ) const;

        /// Access hessian as linear operator \f$ X \rightarrow X^* \f$.
        LinearOperator hessian( const Vector& x ) const;

        /// Access domain space \f$X\f$.
        const VectorSpace& domain() const;

        /**
        * @brief Conversion of the stored implementation to @code  T* @endcode.
        * @return pointer to the stored object if conversion was successful, else nullptr
        */
        template < class T >
        T* target() noexcept
        {
            return type_erasure_table_detail::dynamic_cast_impl< T >( type_id_, read() );
        }

        /**
        * @brief Conversion of the stored implementation to @code const T* @endcode.
        * @return pointer to the stored object if conversion was successful, else nullptr
        */
        template < class T >
        const T* target() const noexcept
        {
            return type_erasure_table_detail::dynamic_cast_impl< T >( type_id_, read() );
        }

    private:
        using Buffer = std::array< char, 64 >;

        void* read() const noexcept;

        void* write();

        C2FunctionalDetail::Functions< C2Functional, Buffer > functions_;
        std::size_t type_id_;
        std::shared_ptr< void > impl_ = nullptr;
        Buffer buffer_;
    };

    /**
    * @brief For a functional \f$ f: X\to \mathbb{R} \f$, compute \f$f'\f$ at \f$x\in X\f$ as dual element \f$ f'(x) \in
    * X^* \f$.
    *
    * Equivalent to calling f.d1(x).
    *
    * @param f twice differentiable functional
    * @param x point of linearization
    * @return \f$f'(x)\f$, i.e. f.d1(x).
    * @see C2Functional
    */
    Vector d1( const C2Functional& f, const Vector& x );

    /**
    * @brief For a functional \f$ f: X\to \mathbb{R} \f$, compute \f$f''\f$ at \f$x\in X\f$ as linear operator \f$
    * f''(x): X \to X^* \f$.
    *
    * Equivalent to calling f.hessian(x).
    *
    * @param f twice differentiable functional
    * @param x point of linearization
    * @return \f$f''(x)\f$, i.e. f.hessian(x).
    * @see C2Functional
    */
    LinearOperator d2( const C2Functional& f, const Vector& x );
}
