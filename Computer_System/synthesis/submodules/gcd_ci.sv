module gcd_ci(
	input clk,                     // clock
	input reset,                 // reset, active low
	input clk_en,                      // clock enable, active high
	input [31:0] s0_dataa,     // input A
	input [31:0] s1_datab,     // input B
	output reg [31:0] s2_result, // output
	input start,                   // start signal 
	output reg done                // operation is completed
);
	logic [31:0] a = 0;
	logic [31:0] b = 0;
	logic running = 0;

	always @(posedge clk) begin
		if(clk_en) begin
			//on start of calculation, grab inputs and set running to true
			if(start) begin
				a <= s0_dataa;
				b <= s1_datab;
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
					s2_result <= a;
					done <= 1;
				end
			end
		end
		//if clock is not enabled, then set done to zero
		else begin
			done <= 0;
		end
	end
endmodule
