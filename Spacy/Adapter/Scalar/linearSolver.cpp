#include "linearSolver.hh"

#include <Spacy/vector.hh>
#include <Spacy/Spaces/RealSpace/real.hh>
#include <Spacy/Util/cast.hh>

namespace Spacy
{
  namespace Scalar
  {
    LinearSolver::LinearSolver(double y)
      : y_(y)
    {}

    ::Spacy::Vector LinearSolver::operator()(const ::Spacy::Vector& x) const
    {
      return cast_ref<Real>(x) / y_;
    }
  }
}
