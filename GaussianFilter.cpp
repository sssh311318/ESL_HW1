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
      val_r= 0; val_g= 0; val_b = 0;
    for (unsigned int v = 0; v < MASK_Y; ++v) {
      for (unsigned int u = 0; u < MASK_X; ++u) {
        unsigned char red = i_r.read();
        unsigned char green = i_g.read();
        unsigned char blue = i_b.read();
          val_r +=   (red * mask[u][v]);
          val_g +=   (green * mask[u][v]);
          val_b +=   (blue * mask[u][v]);
      }
    }
   
    int result_r = (val_r * val_r);
    int result_g = (val_g * val_g);
    int result_b = (val_b * val_b);
    o_result_r.write(std::sqrt(result_r) );
    o_result_g.write(std::sqrt(result_g) );
    o_result_b.write(std::sqrt(result_b) );
    wait(10); //emulate module delay
  }
}
