/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::casual unit test

#include <libs/icl/test/disable_test_warnings.hpp>

#include <string>
#include <vector>
#include <boost/mpl/list.hpp>
#include "../unit_test_unwarned.hpp"
#include <boost/test/test_case_template.hpp>


// interval instance types
#include "../test_type_lists.hpp"
#include "../test_value_maker.hpp"

#include <boost/type_traits/is_same.hpp>

#include <boost/icl/gregorian.hpp>
#include <boost/icl/ptime.hpp>

#define BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS
#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace boost::icl;


BOOST_AUTO_TEST_CASE(casual)
{
    //typedef int T;
    //typedef int U;
    //typedef interval_map<T,U, total_absorber> IntervalMapT;
    //typedef interval_set<T>                   IntervalSetT;
    //typedef IntervalMapT::interval_type       IntervalT;

    /*
    int i;
    int j = int();
    chrono::duration<int> cd1 = chrono::duration<int>();
    chrono::duration<int> cd2(0);
    chrono::duration<int> dur1(0);
    chrono::duration<int> dur2, dur3, dur4;
    dur2 = dur3 = dur4 = dur1;
    int itg1(0);
    int itg2, itg3, itg4;
    itg2 = itg3 = itg4 = itg1;

    cout << "uninitialized       i = " << i << endl;
    cout << "default constructed j = " << j << endl;
    cout << (cd1==cd2 ? "eq" : "!eq") << endl;
    cout << "chrono::duration cd1()  = " << cd1 << endl;
    cout << "chrono::duration cd2(0) = " << cd2 << endl;
    */

    BOOST_CHECK_EQUAL(true, true);
}

