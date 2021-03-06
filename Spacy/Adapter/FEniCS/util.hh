// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef SPACY_ADAPTER_FENICS_UTIL_HH
#define SPACY_ADAPTER_FENICS_UTIL_HH

/// \cond
namespace dolfin
{
  class Form;
  class GenericVector;
  class Function;
}
/// \endcond

namespace Spacy
{
  /// @cond
  class Vector;
  /// @endcond

  namespace FEniCS
  {
    /**
     * @ingroup FenicsGroup
     * @brief Copy coefficients of F to G.
     *
     * Whatever the copy-constructor for dolfin forms does it does not copy. So if
     * you want to copy these do the following.
     * Create A new form from the function spaces stored in G. Then copy the coefficients with
     * this function.
     */
    void copyCoefficients(const dolfin::Form& F, dolfin::Form& G);

    /**
     * @ingroup FenicsGroup
     * @brief Copy from \ref VectorAnchor "::Spacy::Vector" to dolfin::GenericVector.
     *
     * Does consider product space structures.
     * @see ProductSpace
     */
    void copy(const ::Spacy::Vector& x, dolfin::GenericVector& y);

    /**
     * @ingroup FenicsGroup
     * @brief Copy from \ref VectorAnchor "::Spacy::Vector" to dolfin::Function.
     *
     * Does consider product space structures.
     * @see ProductSpace
     */
    void copy(const ::Spacy::Vector& x, dolfin::Function& y);

    /**
     * @ingroup FenicsGroup
     * @brief Copy from dolfin::GenericVector to \ref VectorAnchor "::Spacy::Vector".
     *
     * Does consider product space structures.
     * @see ProductSpaceGroup
     */
    void copy(const dolfin::GenericVector& y, ::Spacy::Vector& x);

    /**
     * @brief Copy from dolfin::Function to \ref VectorAnchor "::Spacy::Vector".
     *
     * Does consider product space structures.
     * @see ProductSpaceGroup
     */
    void copy(const dolfin::Function& y, ::Spacy::Vector& x);
  }
}

#endif // SPACY_ADAPTER_FENICS_UTIL_HH

