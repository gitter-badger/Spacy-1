#ifndef SPACY_FUNCTION_SPACES_KASKADE_VECTOR_SPACE_ELEMENT_HH
#define SPACY_FUNCTION_SPACES_KASKADE_VECTOR_SPACE_ELEMENT_HH

#include "Spacy/Spaces/RealSpace/real.hh"
#include "Spacy/Util/Base/addArithmeticOperators.hh"
#include "Spacy/Util/Base/vectorBase.hh"
#include "Spacy/Util/cast.hh"

#include "util.hh"

namespace Spacy
{  
  /// \cond
  class VectorSpace;
  /// \endcond

  namespace Kaskade
  {
    /// \cond
    template <class> class VectorCreator;
    /// \endcond

    /**
     * @ingroup KaskadeGroup
     * @brief Coefficient vector implementation for %Kaskade 7 (single space).
     * @tparam Description %Kaskade::VariableSetDescription
     */
    template <class Description>
    class Vector :
        public VectorBase ,
        public AddArithmeticOperators< Vector<Description> >
    {
      using VectorImpl = typename Description::template CoefficientVectorRepresentation<>::type;
      using Variable = std::decay_t<std::remove_pointer_t<typename boost::fusion::result_of::value_at_c<typename Description::Variables,0>::type> >;
      using Space = std::decay_t<std::remove_pointer_t<typename boost::fusion::result_of::value_at_c<typename Description::Spaces,Variable::spaceIndex>::type> >;

    public:
      /**
       * @brief Construct vector \f$x\f$ from underlying vector space.
       * @param space underlying vector space
       */
      Vector(const VectorSpace& space)
        : VectorBase(space),
          spaces_(&cast_ref< VectorCreator<Description> >(space.creator()).impl()),
          v_( Description::template CoefficientVectorRepresentation<>::init( spaces_ ))
      {}

      /// Assign from coefficient vector of %Kaskade 7.
      Vector& operator=(const typename Description::template CoefficientVectorRepresentation<>::type& v)
      {
        v_ = v;
        return *this;
      }

      /// Access coefficient vector.
      VectorImpl& impl()
      {
        return v_;
      }

      /// Access coefficient vector.
      const VectorImpl& impl() const
      {
        return v_;
      }


      /**
       * @brief Apply as dual element.
       * @param y primal vector
       * @return \f$x(y)\f$
       */
      Real operator()(const Vector& y) const
      {
        return impl() * y.impl();
      }

      //      Vector& axpy(double a, const AbstractVector& y)
      //      {
      //        v_.axpy(a,castTo< Vector<Description> >(y).v_);
      //        return *this;
      //      }

    private:
      typename Description::Spaces spaces_;
      VectorImpl v_;
    };
  }
}

#endif // SPACY_FUNCTION_SPACES_KASKADE_VECTOR_SPACE_ELEMENT_HH
