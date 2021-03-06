// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef SPACY_ADAPTER_GENERIC_WRITE_VTK_HH
#define SPACY_ADAPTER_GENERIC_WRITE_VTK_HH

#include <cassert>
#include <string>

#include "Spacy/Spaces/ProductSpace/vector.hh"
#include "Spacy/Util/cast.hh"

namespace Spacy
{
  namespace Generic
  {
    template <class Vec, class VTKWriter>
    void writeVTK(const ::Spacy::Vector &x, const std::string& fileName, VTKWriter vtkWriter)
    {
      if( is<Vec>(x) )
      {
        vtkWriter(cast_ref<Vec>(x),fileName);
        return;
      }

      if( is<ProductSpace::Vector>(x) )
      {
        const auto& x_ = cast_ref<ProductSpace::Vector>(x);

        for(auto i=0u; i<x_.numberOfVariables(); ++i)
          writeVTK<Vec>(x_.component(i), fileName+"_"+std::to_string(i),vtkWriter);

        return;
      }

      assert(false);
    }
  }
}

#endif // SPACY_ADAPTER_GENERIC_WRITE_VTK_HH
