// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef MOCK_VECTOR_HH
#define MOCK_VECTOR_HH

#include <string>

namespace Spacy
{
  class Real;
  class Vector;
  class VectorSpace;
}

namespace Mock
{
  class Vector
  {
  public:
    static constexpr int testValue = 3;

    Vector() = default;

    Vector(const Spacy::VectorSpace& space);

    Vector& operator+=(const Vector& y );

    Vector& operator-=(const Vector& y);

    Vector& operator*=(double a);

    Vector operator-() const;

    bool operator==(const Vector y) const;

    Spacy::Real operator()(const Vector& y) const;

    const Spacy::VectorSpace& space() const;

    void toFile(const std::string&) const;

    private:
    friend const double& value(const Vector& v) { return v.value_; }
    friend double& value(Vector& v) { return v.value_; }
    double value_ = testValue;
    const Spacy::VectorSpace* space_ = nullptr;
  };
}

#endif
