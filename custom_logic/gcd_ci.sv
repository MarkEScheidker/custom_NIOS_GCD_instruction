module gcd_ci(
   input csi_clk,                     // clock
   input rsi_reset_n,                 // reset, active low
	input clk_en,                      // clock enable, active high
   input avs_s0_write,                // input A is being written to
   input avs_s1_write,                // input B is being written to
   input avs_s2_read,                 // output is being read from
   input [31:0] avs_s0_writedata,     // input A
   input [31:0] avs_s1_writedata,     // input B
   output reg [31:0] avs_s2_readdata, // output
   input avs_start,                   // start signal 
   output reg avs_done                // operation is completed
);


endmodule