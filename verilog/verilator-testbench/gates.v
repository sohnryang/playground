module gates (
    input clk,
    input rst,
    input a,
    input b,
    input valid,
    output reg out
);
  always @(posedge clk, posedge rst) begin
    if (rst) begin
      out <= 0;
    end else if (valid) begin
      out <= a & b;
    end
  end
endmodule
// vim: set ft=verilog:
