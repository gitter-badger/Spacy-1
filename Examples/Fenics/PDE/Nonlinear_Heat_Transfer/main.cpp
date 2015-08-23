#include <dolfin.h>
#include "NonlinearPoisson.h"

#include "Adapter/fenics.hh"
#include "Algorithm/Newton/newton.hh"
#include "inducedScalarProduct.hh"

using namespace dolfin;

// Source term (right-hand side)
class Source : public Expression
{
  void eval(Array<double>& values, const Array<double>& x) const
  {
    double dx = x[0] - 0.5;
    double dy = x[1] - 0.5;
    values[0] = 1;//10*exp(-(dx*dx + dy*dy) / 0.02);
  }
};

// Sub domain for Dirichlet boundary condition
class DirichletBoundary : public SubDomain
{
  bool inside(const Array<double>& x, bool on_boundary) const
  {
    return x[0] < DOLFIN_EPS or x[0] > 1.0 - DOLFIN_EPS or x[1] < DOLFIN_EPS or x[1] > 1. - DOLFIN_EPS;
  }
};

int main()
{
  // Create mesh and function space
  int n = 256;
  UnitSquareMesh mesh(n,n);
  NonlinearPoisson::FunctionSpace V(mesh);
  std::cout << "degrees of freedom: " << V.dim() << std::endl;

  // Define boundary condition
  Constant u0(0.0);
  DirichletBoundary boundary;
  DirichletBC bc(V, u0, boundary);
  std::vector<const DirichletBC*> bcs { &bc };

   // Define variational forms
  NonlinearPoisson::BilinearForm a(V, V);
  NonlinearPoisson::LinearForm L(V);

  Constant c(1e-2), d(1e2);
  Source f;
  Function u(V);
  L.f = f;
  L.c = c;
  L.d = d;
  a.c = c;
  a.d = d;
  
  
  // Compute solution
  using namespace Algorithm;

  auto domain = Fenics::makeHilbertSpace(V);
  auto range = Fenics::makeHilbertSpace(V);
  connectPrimalDual(domain,range);
  
  auto A = Fenics::makeOperator( L , a , bcs , domain , range );
  domain.setScalarProduct( InducedScalarProduct( A.linearization(domain.element()) ) );
//  range.setScalarProduct( inducedScalarProduct( A.linearization(domain.element()) ) );

  auto p = Algorithm::Newton::Parameter{};
  p.setVerbosity(true);
  p.setRelativeAccuracy(1e-12);

  auto sol = Algorithm::covariantNewton(A,p);
//  auto sol = Algorithm::contravariantNewton(A,p);
//  auto sol = Algorithm::localNewton(A,p);
  Fenics::copy(sol,u);

  // Save solution in VTK format
  File file("poisson.pvd");
  file << u;

  // Plot solution
  plot(u);
  interactive();

  return 0;
}