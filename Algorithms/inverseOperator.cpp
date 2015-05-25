#include "inverseOperator.hh"

#include "Interface/abstractLinearSolver.hh"
#include "functionSpaceElement.hh"

#include <utility>

namespace Algorithm
{
  InverseOperator::InverseOperator(std::unique_ptr<AbstractLinearSolver>&& impl)
    : impl_(std::move(impl))
  {}

  FunctionSpaceElement InverseOperator::operator()(const FunctionSpaceElement& x, const FunctionSpaceElement& y) const
  {
    return (*impl_)(x,y);
  }

  FunctionSpaceElement InverseOperator::operator()(const FunctionSpaceElement& y) const
  {
    return (*impl_)(y);
  }
}