#ifndef ALGORITHM_REALNUMBERS_REALSOLVER_HH
#define ALGORITHM_REALNUMBERS_REALSOLVER_HH

#include "Interface/abstractLinearSolver.hh"

namespace Algorithm
{
  class C0Operator;

  class RealSolver : public Interface::AbstractLinearSolver
  {
  public:
    RealSolver(double value);

    std::unique_ptr<Interface::AbstractFunctionSpaceElement> operator()(const Interface::AbstractFunctionSpaceElement& y) const final override;

  private:
    double value_;
  };
}

#endif // ALGORITHM_REALNUMBERS_REALSOLVER_HH
