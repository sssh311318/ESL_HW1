#include <cmath>

#include "gaussianFilter.h"

gaussianFilter::gaussianFilter(sc_module_name n) : sc_module(n) {
  SC_THREAD(do_filter);
  sensitive << i_clk.pos();
  dont_initialize();
  reset_signal_is(i_rst, false);
}

// gaussian mask
const float mask[MASK_X][MASK_Y] = {{0.077847, 0.123317, 0.077847}, {0.123317, 0.195346, 0.123317}, {0.077847, 0.123317, 0.077847}};



void gaussianFilter::do_filter() {
  while (true) {
    unsigned int val = 0;
    for (unsigned int v = 0; v < MASK_Y; ++v) {
      for (unsigned int u = 0; u < MASK_X; ++u) {
        unsigned char grey = (i_r.read() + i_g.read() + i_b.read()) / 3;
          val += grey * mask[u][v];
      }
    }
    double total = 0;
    total = val * val ;
    int result = (int)(std::sqrt(total));
    o_result.write(result);
    wait(10); //emulate module delay
  }
}
