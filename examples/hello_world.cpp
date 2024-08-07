// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      hello_world.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2024-07-13
 @brief     Minimal example for MR_rect_tree/MR_cell_cplx/MR_rt_to_cc.@EOL
 @keywords  surface plot 2d 3d
 @std       C++23
 @see       
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
typedef mjr::tree15b2d1rT          tt_t;
typedef mjr::MRccT5                cc_t;
typedef mjr::MR_rt_to_cc<tt_t, cc_t> tc_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tt_t::rrpt_t damp_cos_wave(tt_t::drpt_t xvec) {
  double x = xvec[0];
  double y = xvec[1];
  double d = x*x+y*y;
  double z = std::exp(-d/4)*std::cos(4*std::sqrt(d));
  return z;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  tt_t tree({-2.1, -2.1}, 
            { 2.1,  2.1});
  cc_t ccplx;
  tc_t bridge;

  tree.refine_grid(7, damp_cos_wave);   // Sample on a uniform grid
  tree.dump_tree(5);                   // Dump some of the tree

  // Convert the tree to poly data
  bridge.construct_geometry_fans(ccplx,
                                 tree,
                                 2,
                                 {{tc_t::val_src_spc_t::DOMAIN, 0}, 
                                  {tc_t::val_src_spc_t::DOMAIN, 1},
                                  {tc_t::val_src_spc_t::RANGE,  0}});

  ccplx.write_xml_vtk("hello_world.vtu", "hello_world");
}
/** @endcond */
