// This file was automatically generated by friendly type erasure.
// Please do not modify.

#pragma once

#include <memory>
#include <functional>
#include <Spacy/Util/table_util.hh>
#include <Spacy/linearOperator.hh>
#include <Spacy/vector.hh>
#include <Spacy/vectorSpace.hh>

namespace Spacy
{
    namespace C1OperatorDetail
    {
        template < class Interface, class Buffer >
        struct Functions
        {
            using clone_function = void ( * )( void*, std::shared_ptr< void >& );
            using clone_into_function = void ( * )( void*, Buffer&, std::shared_ptr< void >& );
            using call_const_Vector_ref_function = Vector ( * )( const Interface&, void*, const Vector& x );
            using d1_function = Vector ( * )( const Interface&, void*, const Vector& x, const Vector& dx );
            using linearization_function = LinearOperator ( * )( const Interface&, void*, const Vector& x );
            using domain_function = const VectorSpace& (*)( const Interface&, void* );
            using range_function = const VectorSpace& (*)( const Interface&, void* );

            clone_function clone;
            clone_into_function clone_into;
            call_const_Vector_ref_function call_const_Vector_ref;
            d1_function d1;
            linearization_function linearization;
            domain_function domain;
            range_function range;
        };

        template < class Interface, class Impl >
        struct execution_wrapper
        {
            static Vector call_const_Vector_ref( const Interface& interface, void* impl, const Vector& x )
            {
                return static_cast< const Impl* >( impl )->operator()( x );
            }

            static Vector d1( const Interface& interface, void* impl, const Vector& x, const Vector& dx )
            {
                return static_cast< const Impl* >( impl )->d1( x, dx );
            }

            static LinearOperator linearization( const Interface& interface, void* impl, const Vector& x )
            {
                return static_cast< const Impl* >( impl )->linearization( x );
            }

            static const VectorSpace& domain( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->domain();
            }

            static const VectorSpace& range( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->range();
            }
        };

        template < class Interface, class Impl >
        struct execution_wrapper< Interface, std::reference_wrapper< Impl > >
        {
            static Vector call_const_Vector_ref( const Interface& interface, void* impl, const Vector& x )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator()( x );
            }

            static Vector d1( const Interface& interface, void* impl, const Vector& x, const Vector& dx )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().d1( x, dx );
            }

            static LinearOperator linearization( const Interface& interface, void* impl, const Vector& x )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().linearization( x );
            }

            static const VectorSpace& domain( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().domain();
            }

            static const VectorSpace& range( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().range();
            }
        };

        template < class T >
        using TryMemFn_call_const_Vector_ref = decltype( std::declval< T >().operator()( std::declval< Vector >() ) );
        template < class T, class = void >
        struct HasMemFn_call_const_Vector_ref : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_call_const_Vector_ref<
            T, type_erasure_table_detail::voider< TryMemFn_call_const_Vector_ref< T > > > : std::true_type
        {
        };
        template < class T >
        using TryMemFn_d1 = decltype( std::declval< T >().d1( std::declval< Vector >(), std::declval< Vector >() ) );
        template < class T, class = void >
        struct HasMemFn_d1 : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_d1< T, type_erasure_table_detail::voider< TryMemFn_d1< T > > > : std::true_type
        {
        };
        template < class T >
        using TryMemFn_linearization = decltype( std::declval< T >().linearization( std::declval< Vector >() ) );
        template < class T, class = void >
        struct HasMemFn_linearization : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_linearization< T, type_erasure_table_detail::voider< TryMemFn_linearization< T > > >
            : std::true_type
        {
        };
        template < class T >
        using TryMemFn_domain = decltype( std::declval< T >().domain() );
        template < class T, class = void >
        struct HasMemFn_domain : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_domain< T, type_erasure_table_detail::voider< TryMemFn_domain< T > > > : std::true_type
        {
        };
        template < class T >
        using TryMemFn_range = decltype( std::declval< T >().range() );
        template < class T, class = void >
        struct HasMemFn_range : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_range< T, type_erasure_table_detail::voider< TryMemFn_range< T > > > : std::true_type
        {
        };

        template < class T >
        using C1OperatorConceptImpl = std::integral_constant<
            bool, HasMemFn_call_const_Vector_ref< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                      HasMemFn_d1< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                      HasMemFn_linearization< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                      HasMemFn_domain< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                      HasMemFn_range< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value >;

        template < class Impl, class T, bool = std::is_same< Impl, T >::value >
        struct C1OperatorConcept : std::false_type
        {
        };
        template < class Impl, class T >
        struct C1OperatorConcept< Impl, T, false > : C1OperatorConceptImpl< T >
        {
        };
    }
}
