// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef SPACY_UTIL_MIXIN_EPS_HH
#define SPACY_UTIL_MIXIN_EPS_HH

#include "mixinConnection.hh"

namespace Spacy
{
  namespace Mixin
  {
    /// %Mixin class for maximal attainable accuracy \f$\varepsilon\f$.
    class Eps : public MixinConnection<Eps>
    {
    public:
      /**
       * @param eps maximal attainable accuracy \f$\varepsilon\f$
       */
      explicit Eps(double eps = 1e-15) noexcept;

      void setEps(double eps);

      /// Access \f$\varepsilon\f$.
      double eps() const noexcept;

      ///Access \f$\sqrt\varepsilon\f$.
      double sqrtEps() const noexcept;

      /// Access \f$\varepsilon^{1/3}\f$.
      double cbrtEps() const noexcept;

      /// update function for observer pattern.
      void update(Eps* changedSubject);

    private:
      double eps_;
    };
  }
}

#endif // SPACY_UTIL_MIXIN_EPS_HH
