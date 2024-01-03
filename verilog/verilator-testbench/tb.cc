#include <cstdint>
#include <iostream>
#include <memory>

#include <verilated.h>
#include <verilated_vcd_c.h>

#include "Vgates.h"

int main(int argc, char **argv) {
  auto ctx = std::make_unique<VerilatedContext>();
  ctx->commandArgs(argc, argv);
  ctx->traceEverOn(true);

  auto gates = std::make_unique<Vgates>(ctx.get());
  gates->rst = 0;
  gates->clk = 0;
  gates->a = 0;
  gates->b = 0;
  gates->valid = 0;

  auto traces = std::make_unique<VerilatedVcdC>();
  gates->trace(traces.get(), 99);
  traces->open("waveform.vcd");

  const uint64_t max_ticks = 100;
  while (ctx->time() < max_ticks) {
    ctx->timeInc(1);
    std::cout << "time = " << ctx->time() << std::endl;
    gates->clk ^= 1;

    if (ctx->time() <= 3) {
      gates->rst = 1;
      gates->valid = 0;
      std::cout << "resetting" << std::endl;
    } else if (gates->clk) {
      gates->rst = 0;
      gates->a = (ctx->time() >> 1) & 1;
      gates->b = (ctx->time() >> 2) & 1;
      gates->valid = 1;
      std::cout << "a = " << (int)gates->a << ", b = " << (int)gates->b
                << std::endl;
    } else {
      if ((gates->a & gates->b) != gates->out)
        std::cout << "FAIL" << std::endl;
      else
        std::cout << "pass" << std::endl;
    }

    gates->eval();
    std::cout << "out = " << (int)gates->out << std::endl;
    traces->dump(ctx->time());
  }
  gates->final();
  traces->close();

  return 0;
}
