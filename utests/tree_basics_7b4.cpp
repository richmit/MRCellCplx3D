// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      tree_basics_7b4.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2024-07-14
 @brief     Unit tests for MR_rect_tree.@EOL
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

#include "MR_rect_tree.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tree_basics_7b4) {

  mjr::tree7b4d1rT tree({-1.0, -1.0, -1.0, -1.0},
                        { 1.0,  1.0,  1.0,  1.0});

  BOOST_TEST_CHECK(tree.ccc_get_top_cell()                         == 0x40404040 );
  BOOST_TEST_CHECK(tree.ccc_cell_level(0x40404040)                 == 0          );

  BOOST_TEST_CHECK(tree.ccc_cell_quarter_width(0x40404040)         == 0x20       ); 
  BOOST_TEST_CHECK(tree.ccc_cell_half_width(0x40404040)            == 0x40       ); 
  BOOST_TEST_CHECK(tree.ccc_cell_full_width(0x40404040)            == 0x80       ); 

  BOOST_TEST_CHECK(tree.ccc_cell_get_corner_min(0x40404040)        == 0x00000000 );
  BOOST_TEST_CHECK(tree.ccc_cell_get_corner_max(0x40404040)        == 0x80808080 );

  for(int i=0; i<2; i++) {
    BOOST_TEST_CHECK(tree.dom_at(tree.diti_to_drpt(0x00000000), i) == -1.0,    boost::test_tools::tolerance(0.00001) );  
    BOOST_TEST_CHECK(tree.dom_at(tree.diti_to_drpt(0x20202020), i) == -0.5,    boost::test_tools::tolerance(0.00001) );
    BOOST_TEST_CHECK(tree.dom_at(tree.diti_to_drpt(0x40404040), i) ==  0.0,    boost::test_tools::tolerance(0.00001) );
    BOOST_TEST_CHECK(tree.dom_at(tree.diti_to_drpt(0x80808080), i) ==  1.0,    boost::test_tools::tolerance(0.00001) );  

    BOOST_TEST_CHECK(tree.dom_at(tree.get_bbox_min(), i)           == -1.0,    boost::test_tools::tolerance(0.00001) );
    BOOST_TEST_CHECK(tree.dom_at(tree.get_bbox_max(), i)           ==  1.0,    boost::test_tools::tolerance(0.00001) );
    BOOST_TEST_CHECK(tree.dom_at(tree.get_bbox_delta(), i)         ==  1.0/64, boost::test_tools::tolerance(0.00001) );
  }

  BOOST_TEST_CHECK(tree.dom_at(tree.diti_to_drpt(0x00804020), 0)   == -0.5,    boost::test_tools::tolerance(0.00001) );
  BOOST_TEST_CHECK(tree.dom_at(tree.diti_to_drpt(0x00804020), 1)   ==  0.0,    boost::test_tools::tolerance(0.00001) );
  BOOST_TEST_CHECK(tree.dom_at(tree.diti_to_drpt(0x00804020), 2)   ==  1.0,    boost::test_tools::tolerance(0.00001) );
  BOOST_TEST_CHECK(tree.dom_at(tree.diti_to_drpt(0x00804020), 3)   == -1.0,    boost::test_tools::tolerance(0.00001) );

  BOOST_TEST_CHECK(tree.cuc_get_crd(0xD1C1B1A1, 0)                 == 0xA1       );
  BOOST_TEST_CHECK(tree.cuc_get_crd(0xD1C1B1A1, 1)                 == 0xB1       );
  BOOST_TEST_CHECK(tree.cuc_get_crd(0xD1C1B1A1, 2)                 == 0xC1       );
  BOOST_TEST_CHECK(tree.cuc_get_crd(0xD1C1B1A1, 3)                 == 0xD1       );

  BOOST_TEST_CHECK(tree.cuc_inc_crd(0xD1C1B1A1, 0, 0x1)            == 0xD1C1B1A2 );
  BOOST_TEST_CHECK(tree.cuc_dec_crd(0xD1C1B1A1, 0, 0x1)            == 0xD1C1B1A0 );

  BOOST_TEST_CHECK(tree.cuc_inc_crd(0xD1C1B1A1, 1, 0x1)            == 0xD1C1B2A1 );
  BOOST_TEST_CHECK(tree.cuc_dec_crd(0xD1C1B1A1, 1, 0x1)            == 0xD1C1B0A1 );

  BOOST_TEST_CHECK(tree.cuc_inc_crd(0xD1C1B1A1, 2, 0x1)            == 0xD1C2B1A1 );
  BOOST_TEST_CHECK(tree.cuc_dec_crd(0xD1C1B1A1, 2, 0x1)            == 0xD1C0B1A1 );

  BOOST_TEST_CHECK(tree.cuc_inc_crd(0xD1C1B1A1, 3, 0x1)            == 0xD2C1B1A1 );
  BOOST_TEST_CHECK(tree.cuc_dec_crd(0xD1C1B1A1, 3, 0x1)            == 0xD0C1B1A1 );

  BOOST_TEST_CHECK(tree.cuc_dec_all_crd(0xD1C1B1A1, 0x1)           == 0xD0C0B0A0 );
  BOOST_TEST_CHECK(tree.cuc_inc_all_crd(0xD1C1B1A1, 0x1)           == 0xD2C2B2A2 );

  BOOST_TEST_CHECK(tree.cuc_set_all_crd(0xA1)                      == 0xA1A1A1A1 );

}
