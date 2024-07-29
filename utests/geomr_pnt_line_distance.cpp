// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      geomr_pnt_line_distance.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2024-07-22
 @brief     Unit tests for MR_cell_cplx.@EOL
 @std       C++23
 @copyright 
  @parblock
  Copyright (c) 2024, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software
     without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
  @endparblock
*/
/*******************************************************************************************************************************************************.H.E.**/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

#include "MR_cell_cplx.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(geomr_pnt_line_distance) {

  mjr::MRccT5 aPoly;

  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, { 0.0,  0.0, 0.0}, false) ==  0.00000000000,    boost::test_tools::tolerance(0.001) );  // On vertex
  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, { 1.0,  0.0, 0.0}, false) ==  0.00000000000,    boost::test_tools::tolerance(0.001) );  // On vertex
  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, { 0.5,  0.0, 0.0}, false) ==  0.00000000000,    boost::test_tools::tolerance(0.001) );  // On Center

                                                                                      
  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, { 0.0,  0.0, 1.0}, false) ==  1.00000000000,    boost::test_tools::tolerance(0.001) );  // One unit above vertex
  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, { 1.0,  0.0, 1.0}, false) ==  1.00000000000,    boost::test_tools::tolerance(0.001) );  // One unit above vertex
  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, { 0.5,  0.0, 1.0}, false) ==  1.00000000000,    boost::test_tools::tolerance(0.001) );  // One unit above center


  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, {-1.0,  0.0, 1.0}, false) ==  1.00000000000,    boost::test_tools::tolerance(0.001) );  // One unit above and left of segment   LINE MODE
  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, { 2.0,  0.0, 1.0}, false) ==  1.00000000000,    boost::test_tools::tolerance(0.001) );  // One unit above and right of segment  LINE MODE

  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, {-1.0,  0.0, 1.0},  true) ==  1.41421356237,    boost::test_tools::tolerance(0.001) );  // One unit above and left of segment   SEGMENT MODE
  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, { 2.0,  0.0, 1.0},  true) ==  1.41421356237,    boost::test_tools::tolerance(0.001) );  // One unit above and right of segment  SEGMENT MODE



  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, {-1.0,  0.0, 0.0}, false) ==  0.00000000000,    boost::test_tools::tolerance(0.001) );  // One unit left of segment colinear    LINE MODE
  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, { 2.0,  0.0, 0.0}, false) ==  0.00000000000,    boost::test_tools::tolerance(0.001) );  // One unit right of segment colinear   LINE MODE

  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, {-1.0,  0.0, 0.0},  true) ==  1.00000000000,    boost::test_tools::tolerance(0.001) );  // One unit left of segment colinear    SEGMENT MODE
  BOOST_TEST_CHECK(aPoly.geomr_pnt_line_distance({0.0, 0.0, 0.0}, {1.0,  0.0, 0.0}, { 2.0,  0.0, 0.0},  true) ==  1.00000000000,    boost::test_tools::tolerance(0.001) );  // One unit right of segment colinear   SEGMENT MODE

}

