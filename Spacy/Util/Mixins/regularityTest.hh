#pragma once

#include "mixinConnection.hh"

namespace Spacy
{
  namespace Mixin
  {
    /// %Mixin class for maximal number of steps/iterations.
    class RegularityTest : public MixinConnection<RegularityTest>
    {
    public:
      /**
       * @brief Constructor.
       * @param lowerBound lower bound for regularity test
       */
      explicit RegularityTest(double lowerBound = 1e-12) noexcept;

      /// Set lower bound of regularity test for termination criteria.
      void setLowerBound(double lowerBound);

      double getLowerBound() const noexcept;

      /**
       * @brief Apply regularity test.
       * @param nu damping factor
       * @return \f$nu > lowerBound_\f$
       */
      bool regularityTestPassed(double nu) const noexcept;

      /**
       * @brief Apply regularity test.
       * @param nu damping factor
       * @return \f$nu <= lowerBound_\f$
       */
      bool regularityTestFailed(double nu) const noexcept;

      /// update function for observer pattern.
      void update(RegularityTest* changedSubject);

    private:
      double lowerBound_;
    };
  }
}
