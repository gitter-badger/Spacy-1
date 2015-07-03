#include "linearSolver.hh"

#include "Interface/abstractLinearSolver.hh"
#include "c1Operator.hh"
#include "functionSpaceElement.hh"
#include "linearOperator.hh"

namespace Algorithm
{
  LinearSolver::LinearSolver(const LinearOperator& A)
    : Mixin::SharedImpl<AbstractLinearSolver>( A.getSolver().sharedImpl() )
  {}

  LinearSolver::LinearSolver(std::shared_ptr<AbstractLinearSolver> impl)
    : Mixin::SharedImpl<AbstractLinearSolver>(impl)
  {}

  FunctionSpaceElement LinearSolver::operator ()(const FunctionSpaceElement& x) const
  {
    return FunctionSpaceElement( impl()(x.impl()) );
  }
}

