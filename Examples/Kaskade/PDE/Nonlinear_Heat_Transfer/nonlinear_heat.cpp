#include <iostream>

#include <dune/grid/config.h>
#include <dune/grid/uggrid.hh>

#define SPACY_ENABLE_LOGGING
#include <Spacy/zeroVectorCreator.hh>
#include <Spacy/Adapter/kaskade.hh>
#include <Spacy/Algorithm/Newton/newton.hh>
#include <Spacy/Util/cast.hh>
#include <Spacy/Util/log.hh>
#include <Spacy/inducedScalarProduct.hh>

#include <fem/gridmanager.hh>
#include <fem/lagrangespace.hh>
#include <fem/variables.hh>
#include <io/vtk.hh>
#include <utilities/gridGeneration.hh> //  createUnitSquare

#include "../fung_operator.hh"

#include <fung/fung.hh>
#include <fung/examples/nonlinear_heat.hh>

using namespace Kaskade;

int main()
{
    SET_LOG_PRINTER(Spacy::Log::StreamPrinter());

    constexpr int dim = 2;
    int refinements = 6;
    int order       = 1;

    using Grid = Dune::UGGrid<dim>;
    using H1Space = FEFunctionSpace<ContinuousLagrangeMapper<double,Grid::LeafGridView> >;
    using Spaces = boost::fusion::vector<H1Space const*>;
    using VariableDescriptions = boost::fusion::vector< Variable<SpaceIndex<0>,Components<1>,VariableId<0> > >;
    using VariableSetDesc = VariableSetDescription<Spaces,VariableDescriptions>;


    GridManager<Grid> gridManager( createUnitSquare<Grid>(1.,false) );
    gridManager.globalRefine(refinements);

    H1Space temperatureSpace(gridManager,gridManager.grid().leafGridView(),order);

    Spaces spaces(&temperatureSpace);
    VariableSetDesc variableSetDesc(spaces,{ "u" });


    double c = 1e-2, d = 1e2;
    Dune::FieldVector<double,1> u0{0};
    Dune::FieldMatrix<double,1,dim> du0{0};
    auto integrand = FunG::heatModel(c, d, u0, du0);
    auto F = FungOperator<decltype(integrand),VariableSetDesc>(integrand);


    // compute solution
    auto domain = Spacy::Kaskade::makeHilbertSpace<VariableSetDesc>( variableSetDesc );
    auto range = Spacy::Kaskade::makeHilbertSpace<VariableSetDesc>( variableSetDesc );
    connectAsPrimalDualPair(domain,range);

    Spacy::C1Operator A = Spacy::Kaskade::makeC1Operator( F , domain , range );
    domain.setScalarProduct( Spacy::InducedScalarProduct( A.linearization(zero(domain))) );

    auto p = Spacy::Newton::Parameter{};
    p.setVerbosity(true);
    p.setRelativeAccuracy(1e-12);

    auto x = covariantNewton(A,p);
    //  auto x = Spacy::contravariantNewton(f,p);
    //  auto x = Spacy::localNewton(f,p);

    //construct Galerkin representation
    writeVTK(Spacy::cast_ref< Spacy::Kaskade::Vector<VariableSetDesc> >(x), "temperature");
}
