// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#include "vectorSpace.hh"

#include "Spacy/vector.hh"
#include "Spacy/vectorSpace.hh"
#include "l2Product.hh"
#include "vector.hh"
#include "Spacy/Spaces/ProductSpace/vectorSpace.hh"
#include "Spacy/Spaces/RealSpace/real.hh"

namespace Spacy
{
  namespace FEniCS
  {
    VectorCreator::VectorCreator(const dolfin::FunctionSpace& space)
      : Mixin::Get<dolfin::FunctionSpace>(space)
    {}

    VectorCreator::VectorCreator(const dolfin::FunctionSpace& space, const std::unordered_map<std::size_t, std::size_t>& dofmap)
      : Mixin::Get<dolfin::FunctionSpace>(space),
        dofmap_(dofmap),
        inverseDofmap_(dofmap_.size())
    {
      auto mend = end(dofmap_);
      for( auto m = begin(dofmap_) ; m!=mend ; ++m )
        inverseDofmap_[m->first] = m->second;
    }

    std::size_t VectorCreator::dofmap(std::size_t i) const
    {
      if( dofmap_.empty() ) return i;
      auto j = dofmap_.find(i);
      if( j == end(dofmap_) ) throw std::runtime_error("dofmap");
      return j->second;
    }

    std::size_t VectorCreator::inverseDofmap(std::size_t i) const
    {
      if(inverseDofmap_.empty()) return i;
      return inverseDofmap_[i];
    }


    ::Spacy::Vector VectorCreator::operator()(const VectorSpace* space) const
    {
      return Vector{*space};
    }

    unsigned VectorCreator::size() const
    {
      return get().dim();
    }

    VectorSpace makeHilbertSpace(const dolfin::FunctionSpace& space)
    {
      return ::Spacy::makeHilbertSpace( VectorCreator{space} , l2Product{} );
    }

    VectorSpace makeHilbertSpace(const dolfin::FunctionSpace& space, const std::unordered_map<std::size_t,std::size_t>& dofmap)
    {
      return ::Spacy::makeHilbertSpace( VectorCreator{space,dofmap} , l2Product{} );
    }

    VectorSpace makeHilbertSpace(const dolfin::FunctionSpace& space, const std::vector<unsigned>& primalIds, const std::vector<unsigned>& dualIds)
    {
      unsigned maxPrimalId = primalIds.empty() ? 0 : *std::max_element(begin(primalIds),end(primalIds));
      unsigned maxDualId   = dualIds.empty()   ? 0 : *std::max_element(begin(dualIds),end(dualIds));
      std::vector<std::shared_ptr< VectorSpace > > spaces( 1 + std::max( maxPrimalId , maxDualId ) );
      for(std::size_t i : primalIds)
      {
        std::unordered_map<std::size_t,std::size_t> dofmap;
        auto subSpace = space[i]->collapse(dofmap);
        spaces[i] =  std::make_shared< VectorSpace >( makeHilbertSpace( *subSpace,dofmap) );
      }
      for(std::size_t i : dualIds)
      {
        std::unordered_map<std::size_t,std::size_t> dofmap;
        auto subSpace = space[i]->collapse(dofmap);
        spaces[i] =  std::make_shared< VectorSpace >( makeHilbertSpace( *subSpace,dofmap ) );
      }

      return ProductSpace::makeHilbertSpace( spaces , primalIds , dualIds );
    }
  }
}
