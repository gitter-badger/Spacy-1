// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#include "vector.hh"

#include "vectorSpace.hh"

#include "Spacy/Util/cast.hh"
#include "Spacy/Util/Exceptions/callOfUndefinedFunctionException.hh"
#include "Spacy/Util/Exceptions/invalidArgumentException.hh"

#include "Spacy/Spaces/RealSpace/real.hh"
#include "Spacy/vectorSpace.hh"

#include <utility>

namespace Spacy
{
  namespace FEniCS
  {
    Vector::Vector(const VectorSpace& space)
      : VectorBase(space),
        v_( creator<VectorCreator>(space).get() )
    {}

    Vector& Vector::operator=(const dolfin::Function& v)
    {
      v_ = v;
      return *this;
    }

//    Vector& Vector::axpy(double a, const Vector& y)
//    {
//      get().vector()->axpy(a,*castTo<Vector>(y).get().vector());
//      return *this;
//    }

    dolfin::GenericVector& Vector::get()
    {
      return *v_.vector();
    }

    const dolfin::GenericVector& Vector::get() const
    {
      return *v_.vector();
    }

    Real Vector::operator()(const Vector& y) const
    {
      return get().inner( y.get() );
    }
  }
}
