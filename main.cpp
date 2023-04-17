#include "stim.h"
#include "filter.h"
#define CLOCK_PERIOD 1.0

using namespace sc_dt;
using namespace sc_core;

int sc_main(int argc, char *argv[]) {
  //Create modules and signals
  stim testbench("testbench");
  adder dut("dut", 1);
  sc_clock clk("clk", CLOCK_PERIOD, SC_NS);
  sc_signal<bool> rst("rst");

  //Create sc_fifo channels

  sc_fifo<sc_ufixed_fast<5, 0> > fifo_i_x;
  sc_fifo<sc_ufixed_fast<8, 3> > fifo_o_y;

  //Connect FIFO channels with modules
  testbench.i_clk(clk);
  testbench.o_rst(rst);
  dut.i_clk(clk);
  dut.i_rst(rst);
  testbench.o_x.msg(fifo_i_x);
  testbench.i_y.msg( fifo_o_y);
  dut.i_x_port.msg(fifo_i_x);
  dut.o_y_port.msg( fifo_o_y);

  sc_start(100, SC_NS);
  return 0;
}
