`timescale 1ns / 1ps

module lfsr_tb();
  reg clk, rst;
  wire [3:0] out;
  initial begin
    $dumpfile("wave.vcd");
    $dumpvars();

    clk = 0;
    rst = 1;
    #15
    rst = 0;
    #200
    $finish();
  end

  always begin
    #5
    clk = ~clk;
  end

  lfsr rng(clk, rst, out);
endmodule
