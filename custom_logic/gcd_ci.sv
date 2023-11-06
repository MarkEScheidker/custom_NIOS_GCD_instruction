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
	logic [31:0] a = 0;
	logic [31:0] b = 0;
	logic running = 0;

	always @(posedge csi_clk) begin
		//on start of calculation, grab inputs and set running to true
		if(avs_start) begin
			a <= avs_s0_writedata;
			b <= avs_s1_writedata;
			running <= 1;
		end
		
		//running state
		else if(running) begin
			//euclid's algorithm
         if (a > b) begin
            a <= a - b;
         end
         else if (b > a) begin
            b <= b - a;
         end
			//if a result has been reached, then output the data
         else if (a == b && a != 0) begin
				running <= 0;
				avs_s2_readdata <= a;
				avs_done <= 1;
         end
      end
		//if not running
		else begin
			avs_done <= 0;
		end
	end
endmodule
