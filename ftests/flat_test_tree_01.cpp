// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      flat_test_tree_01.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2024-07-31
 @brief     Create a simple tree we can yse fir testing.@EOL
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
/** @cond exj */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MR_rect_tree.hpp"
#include "MR_cell_cplx.hpp"
#include "MR_rt_to_cc.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef mjr::tree15b2d1rT            tt_t;
typedef mjr::MRccT5                cc_t;
typedef mjr::MR_rt_to_cc<tt_t, cc_t> tc_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double zero2(std::array<double, 2> xvec) {
  double x = xvec[0];
  double y = xvec[1];
  return 0*(x+y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  tt_t tree;
  cc_t ccplx;
  tc_t bridge;

  tree.refine_grid(1, zero2);

  auto c1 = tree.ccc_get_children(tree.ccc_get_top_cell(), 0, -1);
  tree.refine_once(c1[0], zero2);

  auto c2 = tree.ccc_get_children(c1[0], 0, -1);
  tree.refine_recursive(c2[0], 4, zero2);

  tree.dump_tree(5);

  tree.balance_tree(1, zero2);

  tree.dump_tree(5);

  bridge.construct_geometry_fans(ccplx,
                                 tree,
                                 2,
                                 {{tc_t::val_src_spc_t::DOMAIN, 0}, 
                                  {tc_t::val_src_spc_t::DOMAIN, 1},
                                  {tc_t::val_src_spc_t::RANGE,  0}});

  ccplx.create_named_datasets({"x", "y", "f(x,y)"});

  ccplx.write_xml_vtk("flat_test_tree_01.vtu", "flat_test_tree_01");
}
