#pragma once

#include <Spacy/vectorSpace.hh>

namespace Spacy
{
  namespace RealSpace
  {
    /**
     * @ingroup RealGroup
     * @brief Construct space of real numbers.
     * @return ::Spacy::makeHilbertSpace() "::Spacy::makeHilbertSpace( [](const Spacy* space){ return Vector{*space}; } , ScalarProduct{} )"
     */
    VectorSpace makeHilbertSpace(bool defaultIndex = false);
  }

  /**
   * @brief Construct space of real numbers.
   * @return ::RealSpace::makeHilbertSpace()
   */
  VectorSpace makeRealSpace(bool defaultIndex = false);

  namespace Space
  {
    /**
     * @brief Global space of real numbers with space index 0.
     *
     * This space is used by class Real if the underlying space is left unspecified.
     */
    static VectorSpace R = RealSpace::makeHilbertSpace(true);
  }
}
