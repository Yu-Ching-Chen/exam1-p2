#ifndef _FILTER_H_
#define _FILTER_H_

#include <iostream>
using namespace std;

#include <systemc>
using namespace sc_dt;
using namespace sc_core;

#include "filter_def.h"
#include "ready_valid_port.h"

class filter : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  
  sc_fifo_in<sc_ufixed_fast<5, 0> > i_x_port;
  sc_fifo_out<sc_ufixed_fast<8, 3> > o_y_port;

  void do_filter() {
    while (true) {
        _o_y = 0;

        _i_x = i_x_port.read();
        wait();

        _o_y = _o_y + _i_x * filter_coef[2];
        wait();

        _i_x = i_x_port.read();
        wait();

        _o_y = _o_y + _i_x * filter_coef[1];
        wait();

        _i_x = i_x_port.read();
        wait();

        _o_y = _o_y + _i_x * filter_coef[0];
        o_y_port.write(_o_y);
        wait();
    }
  }

  SC_HAS_PROCESS(filter);
  filter(sc_module_name name, int i) : id(i){ 

    SC_THREAD(do_filter);  
    sensitive << i_clk.pos();
    dont_initialize();
    //reset_signal_is(i_rst, false); 
  }

  sc_ufixed_fast<5, 0> i_x() { return _i_x;}
  sc_ufixed_fast<8, 3> o_y() { return _o_y; }

private:
  const int id;
  sc_ufixed_fast<5, 0> _i_x;
  sc_ufixed_fast<8, 3> _o_y;
};

#endif
