// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry               
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2013.
// 
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution 
//    may be used to endorse or promote products derived from this software 
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS. 
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING 
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// --------------------------------------------------------------------------
// $Maintainer: Clemens Groepl $
// $Authors: $
// --------------------------------------------------------------------------

#include <OpenMS/CONCEPT/ClassTest.h>
#include <OpenMS/test_config.h>

///////////////////////////
#include <OpenMS/CONCEPT/UniqueIdGenerator.h>
#include <ctime>
#include <boost/accumulators/statistics/covariance.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
///////////////////////////

using namespace OpenMS;
using namespace std;

START_TEST(UniqueIdGenerator, "$Id$")

unsigned nofIdsToGenerate = 100000;
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

START_SECTION((UniqueIdGenerator()))
{
  // singleton has private ctor
  NOT_TESTABLE;
}
END_SECTION

START_SECTION((~UniqueIdGenerator()))
{
  // singleton has private dtor
  NOT_TESTABLE;
}
END_SECTION

START_SECTION((static UInt64 getUniqueId()))
{
  STATUS("OpenMS::UniqueIdGenerator::getUniqueId(): " << OpenMS::UniqueIdGenerator::getUniqueId());
  /* test for collisions, test will be different for every test execution */
  OpenMS::UniqueIdGenerator::setSeed(std::time(0));
  std::vector<OpenMS::UInt64> ids;
  ids.reserve(nofIdsToGenerate);
  for (unsigned i=0; i<nofIdsToGenerate; ++i)
  {
    ids.push_back(OpenMS::UniqueIdGenerator::getUniqueId());
  }
  std::sort(ids.begin(), ids.end());
  BOOST_AUTO(iter, ids.begin()+1);
  for(; iter!=ids.end(); ++iter)
  {
    if(*iter == *(iter-1))
    {
      TEST_NOT_EQUAL(*iter, *(iter-1));
    }
  }
  TEST_NOT_EQUAL(*iter, *(iter-1));
}
END_SECTION

START_SECTION((static void setSeed(UInt seed)))
{
  UInt one_moment_in_time = 546666321;
//  OpenMS::DateTime one_moment_in_time;
//  one_moment_in_time.set(5,4,6666,3,2,1);
//  OpenMS::UniqueIdGenerator::setSeed(one_moment_in_time);

  /* check if the generator changed */
  UInt64 large_int = 0;
  std::vector<UInt64> unique_ids;
  large_int = 4039984684862977299;
  unique_ids.push_back(large_int);
  large_int = 11561668883169444769;
  unique_ids.push_back(large_int);
  large_int = 8153960635892418594;
  unique_ids.push_back(large_int);
  large_int = 12940485248168291983;
  unique_ids.push_back(large_int);
  large_int = 11522917731873626020;
  unique_ids.push_back(large_int);
  large_int = 4387255872055054320;
  unique_ids.push_back(large_int);

  OpenMS::UniqueIdGenerator::setSeed(one_moment_in_time);
  for (int i=0; i<unique_ids.size(); ++i)
  {
    OpenMS::UInt64 uid = OpenMS::UniqueIdGenerator::getUniqueId();
    TEST_EQUAL(uid,unique_ids[i]);
  }
  /* check if the same sequence is generated form the same seed */
  std::vector<OpenMS::UInt64> ids;
  ids.reserve(nofIdsToGenerate);
  OpenMS::UniqueIdGenerator::setSeed(one_moment_in_time);
  for (unsigned i=0; i<nofIdsToGenerate; ++i)
  {
    ids.push_back(OpenMS::UniqueIdGenerator::getUniqueId());
  }
  std::vector<OpenMS::UInt64> ids2;
  ids2.reserve(nofIdsToGenerate);
  OpenMS::UniqueIdGenerator::setSeed(one_moment_in_time);
  for (unsigned i=0; i<nofIdsToGenerate; ++i)
  {
    ids2.push_back(OpenMS::UniqueIdGenerator::getUniqueId());
  }

  for ( unsigned i = 0; i < nofIdsToGenerate; ++i )
  {
    if(ids[i] != ids2[i])
    {
      TEST_EQUAL(ids[i],  ids2[i]);
    }
  }
}
END_SECTION

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
