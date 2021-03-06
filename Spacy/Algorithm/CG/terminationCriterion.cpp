// This file was automatically generated by friendly type erasure.
// Please do not modify.

#include "terminationCriterion.hh"

namespace Spacy
{
    namespace CG
    {
        TerminationCriterion::TerminationCriterion() noexcept : impl_( nullptr )
        {
        }

        TerminationCriterion::TerminationCriterion( const TerminationCriterion& other )
            : functions_( other.functions_ ), type_id_( other.type_id_ ),
              impl_( other.impl_ ? other.functions_.clone( other.impl_ ) : nullptr )
        {
        }

        TerminationCriterion::TerminationCriterion( TerminationCriterion&& other ) noexcept
            : functions_( other.functions_ ),
              type_id_( other.type_id_ ),
              impl_( other.impl_ )
        {
            other.impl_ = nullptr;
        }

        TerminationCriterion::~TerminationCriterion()
        {
            if ( impl_ )
                functions_.del( impl_ );
        }

        TerminationCriterion& TerminationCriterion::operator=( const TerminationCriterion& other )
        {
            functions_ = other.functions_;
            type_id_ = other.type_id_;
            impl_ = other.impl_ ? other.functions_.clone( other.impl_ ) : nullptr;
            return *this;
        }

        TerminationCriterion& TerminationCriterion::operator=( TerminationCriterion&& other ) noexcept
        {
            type_id_ = other.type_id_;
            functions_ = other.functions_;
            impl_ = other.impl_;
            other.impl_ = nullptr;
            return *this;
        }

        TerminationCriterion::operator bool() const noexcept
        {
            return impl_ != nullptr;
        }

        bool TerminationCriterion::operator()() const
        {
            assert( impl_ );
            return functions_.call( *this, impl_ );
        }

        void TerminationCriterion::clear()
        {
            assert( impl_ );
            functions_.clear( *this, impl_ );
        }

        void TerminationCriterion::update( double alpha, double qAq, double qPq, double rPINVr )
        {
            assert( impl_ );
            functions_.update( *this, impl_, std::move( alpha ), std::move( qAq ), std::move( qPq ),
                               std::move( rPINVr ) );
        }

        bool TerminationCriterion::vanishingStep() const
        {
            assert( impl_ );
            return functions_.vanishingStep( *this, impl_ );
        }

        bool TerminationCriterion::minimalDecreaseAchieved() const
        {
            assert( impl_ );
            return functions_.minimalDecreaseAchieved( *this, impl_ );
        }

        void TerminationCriterion::setEps( double eps )
        {
            assert( impl_ );
            functions_.setEps( *this, impl_, std::move( eps ) );
        }

        void TerminationCriterion::setAbsoluteAccuracy( double accuracy )
        {
            assert( impl_ );
            functions_.setAbsoluteAccuracy( *this, impl_, std::move( accuracy ) );
        }

        void TerminationCriterion::setMinimalAccuracy( double accuracy )
        {
            assert( impl_ );
            functions_.setMinimalAccuracy( *this, impl_, std::move( accuracy ) );
        }

        void TerminationCriterion::setRelativeAccuracy( double accuracy )
        {
            assert( impl_ );
            functions_.setRelativeAccuracy( *this, impl_, std::move( accuracy ) );
        }
    }
}
