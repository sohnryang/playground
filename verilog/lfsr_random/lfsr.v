module lfsr(
  input clk,
  input rst,
  output [3:0] out
);
  reg [3:0] output_reg;
  wire feedback;
  assign feedback = ~(out[3] ^ out[2]);

  always @(posedge clk, posedge rst)
  begin
    if (rst)
      output_reg = 4'b0;
    else
      output_reg = {output_reg[2:0], feedback};
  end
  assign out = output_reg;
endmodule
