#include "triangularStateConstraintPreconditioner.hh"

#include "FunctionSpaces/ProductSpace/productSpaceElement.hh"
#include "Adapter/Fenics/hilbertSpace.hh"
#include <utility>
#include <iostream>
namespace Algorithm
{
  TriangularStateConstraintPreconditioner::TriangularStateConstraintPreconditioner(std::shared_ptr<Interface::AbstractLinearSolver> stateSolver,
                                                                                   std::shared_ptr<Interface::AbstractLinearSolver> controlSolver,
                                                                                   std::shared_ptr<Interface::AbstractLinearSolver> adjointSolver,
                                                                                   std::unique_ptr<AbstractOperator>&& B,
                                                                                   std::unique_ptr<AbstractOperator>&& BT,
                                                                                   std::shared_ptr<Interface::AbstractBanachSpace> domain,
                                                                                   std::shared_ptr<Interface::AbstractBanachSpace> range)
    : AbstractOperator(domain,range),
      stateSolver_(stateSolver), controlSolver_(controlSolver), adjointSolver_(adjointSolver),
      B_(std::move(B)), BT_(std::move(BT))
  {}

  std::unique_ptr<Interface::AbstractFunctionSpaceElement> TriangularStateConstraintPreconditioner::operator()(const Interface::AbstractFunctionSpaceElement& x) const
  {
    auto x_ = clone( toProductSpaceElement(x) );
    auto y = clone(x);
    auto& y_ = toProductSpaceElement(*y);

    y_.variable(adjointIndex()) = *(*adjointSolver_)( x_->variable(stateIndex()) );
    x_->variable(controlIndex()) -= *(*BT_)( y_.variable(adjointIndex()) );

    y_.variable(controlIndex()) = *(*controlSolver_)( x_->variable(controlIndex()) );

    x_->variable(adjointIndex()) -= *(*B_)( y_.variable(controlIndex()) );

    y_.variable(stateIndex()) = *(*stateSolver_)( x_->variable(adjointIndex()) );

    return y;
  }

  TriangularStateConstraintPreconditioner* TriangularStateConstraintPreconditioner::cloneImpl() const
  {
    return new TriangularStateConstraintPreconditioner( stateSolver_ , controlSolver_ , adjointSolver_ , clone(B_) , clone(B_) , sharedDomain() , sharedRange() );
  }
}
