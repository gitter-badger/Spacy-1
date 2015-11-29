// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#include <gtest/gtest.h>

#include "setup.hh"
//#include "Spacy/Adapter/Kaskade/vector.hh"
#include "Spacy/Adapter/Kaskade/vectorSpace.hh"
#include "Spacy/vectorSpace.hh"

#include "Test/mockSetup.hh"


using namespace Kaskade;

TEST(Kaskade,VectorCreator_Create)
{
  KASKADE_SINGLE_SPACE_SETUP

  Spacy::Kaskade::VectorCreator<VariableSetDesc> creator(temperatureSpace);
  ASSERT_EQ( creator.impl().degreesOfFreedom() , temperatureSpace.degreesOfFreedom() );

  Spacy::VectorCreator spacyCreator(creator);
  ASSERT_EQ( spacyCreator.target<Spacy::Kaskade::VectorCreator<VariableSetDesc>>()->impl().degreesOfFreedom() , temperatureSpace.degreesOfFreedom() );
}


TEST(Kaskade,VectorCreator_CreateVector)
{
  KASKADE_SINGLE_SPACE_SETUP

  auto V = Spacy::Kaskade::makeHilbertSpace<VariableSetDesc>(temperatureSpace);

  auto v = V.zeroVector();

  ASSERT_EQ( norm(v) , 0. );

  auto& kv = *v.target< Spacy::Kaskade::Vector<VariableSetDesc> >();

  boost::fusion::at_c<0>(kv.impl().data)[0] = 2;
  ASSERT_EQ( norm(v) , 2. );
}



//TEST(Rn,AssignFromEigen_VectorXd)
//{
//  auto vec = testVector();

//  auto space = createMockBanachSpace();
//  Spacy::Rn::Vector spacy_v(0*vec,space);

//  ASSERT_EQ( spacy_v.impl()[0] , 0.);
//  ASSERT_EQ( spacy_v.impl()[1] , 0.);

//  spacy_v = vec;
//  ASSERT_EQ( spacy_v.impl()[0] , 1.);
//  ASSERT_EQ( spacy_v.impl()[1] , 2.);
//}

//TEST(Rn,AddVectors)
//{
//  auto vec = testVector();

//  auto space = createMockBanachSpace();
//  Spacy::Rn::Vector spacy_v(vec,space);

//  spacy_v += spacy_v;
//  ASSERT_EQ( spacy_v.impl()[0] , 2.);
//  ASSERT_EQ( spacy_v.impl()[1] , 4.);
//}

//TEST(Rn,SubtractVectors)
//{
//  auto vec = testVector();

//  auto space = createMockBanachSpace();
//  Spacy::Rn::Vector spacy_v(vec,space);

//  spacy_v -= spacy_v;
//  ASSERT_EQ( spacy_v.impl()[0] , 0.);
//  ASSERT_EQ( spacy_v.impl()[1] , 0.);
//}

//TEST(Rn,MultiplyVectorWithScalar)
//{
//  auto vec = testVector();

//  auto space = createMockBanachSpace();
//  Spacy::Rn::Vector spacy_v(vec,space);

//  spacy_v *= 3;
//  ASSERT_EQ( spacy_v.impl()[0] , 3.);
//  ASSERT_EQ( spacy_v.impl()[1] , 6.);
//}

//TEST(Rn,ApplyAsDual)
//{
//  auto vec = testVector();

//  auto space = createMockBanachSpace();
//  Spacy::Rn::Vector spacy_v(vec,space);

//  auto dualPairing = spacy_v(spacy_v);
//  ASSERT_EQ( dualPairing , 5.);
//}

//TEST(Rn,Negation)
//{
//  auto vec = testVector();

//  auto space = createMockBanachSpace();
//  Spacy::Rn::Vector spacy_v(vec,space);

//  auto spacy_w = -spacy_v;
//  ASSERT_EQ( spacy_w.impl()[0] , -1.);
//  ASSERT_EQ( spacy_w.impl()[1] , -2.);
//}

//TEST(Rn,Comparison)
//{
//  auto vec = testVector();
//  vec[1] = 0;

//  auto space = Spacy::Rn::makeHilbertSpace(testDim());
//  Spacy::Rn::Vector spacy_v(vec,space), spacy_w(vec,space);

//  ASSERT_TRUE( spacy_v == spacy_w );

//  space.setEps(1e-5);
//  spacy_w.impl()[0] = 1 - 5e-6;

//  ASSERT_TRUE( spacy_v == spacy_w );
//  spacy_w.impl()[0] = 1 - 1.1e-5;
//  ASSERT_FALSE( spacy_v == spacy_w );
//}
