// This file was automatically generated by friendly type erasure.
// Please do not modify.

#pragma once

#include <memory>
#include <functional>
#include <ostream>
#include "Spacy/Util/table_util.hh"
#include "Detail/details_for_printer.hh"

namespace Spacy
{

    namespace Log
    {
        /// Interface for logger's printers.
        class Printer
        {
        public:
            Printer() noexcept;

            template < typename T, typename std::enable_if< PrinterDetail::PrinterConcept<
                                       Printer, typename std::decay< T >::type >::value >::type* = nullptr >
            Printer( T&& value )
                : functions_( {&type_erasure_table_detail::delete_impl< typename std::decay< T >::type >,
                               &PrinterDetail::execution_wrapper< Printer, typename std::decay< T >::type >::
                                   call_const_char_ptr_const_char_ptr_const_std_function_void_std_ostream_ref_ref} ),
                  type_id_( typeid( typename std::decay< T >::type ).hash_code() ),
                  impl_( new typename std::decay< T >::type( std::forward< T >( value ) ) )
            {
            }

            Printer( Printer&& other ) noexcept;

            ~Printer();

            template < typename T, typename std::enable_if< PrinterDetail::PrinterConcept<
                                       Printer, typename std::decay< T >::type >::value >::type* = nullptr >
            Printer& operator=( T&& value )
            {
                return *this = Printer( std::forward< T >( value ) );
            }

            Printer& operator=( Printer&& other ) noexcept;

            /**
             * @brief Checks if the type-erased interface holds an implementation.
             * @return true if an implementation is stored, else false
             */
            explicit operator bool() const noexcept;

            /**
            * @brief Log printable according to its level and name.
            * @param tag specifies the algorithm/function this log originates from
            * @param name name of the logged value
            * @param printable wraps writing of the logged value to some stream
            */
            void operator()( const char* tag, const char* name,
                             const std::function< void( std::ostream& ) >& printable );

            /**
            * @brief Conversion of the stored implementation to @code  T* @endcode.
            * @return pointer to the stored object if conversion was successful, else nullptr
            */
            template < class T >
            T* target() noexcept
            {
                return type_erasure_table_detail::dynamic_cast_impl< T >( type_id_, impl_ );
            }

            /**
            * @brief Conversion of the stored implementation to @code const T* @endcode.
            * @return pointer to the stored object if conversion was successful, else nullptr
            */
            template < class T >
            const T* target() const noexcept
            {
                return type_erasure_table_detail::dynamic_cast_impl< T >( type_id_, impl_ );
            }

        private:
            PrinterDetail::Functions< Printer > functions_;
            std::size_t type_id_;
            void* impl_ = nullptr;
        };
    }
}
