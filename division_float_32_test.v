`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   22:09:49 04/13/2015
// Design Name:   division_float_32
// Module Name:   /home/lin/program/ISE/2015/ALU/division_float_32_test.v
// Project Name:  ALU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: division_float_32
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module division_float_32_test;

	// Inputs
	reg clock;
	reg start;
	reg [31:0] operand1;
	reg [31:0] operand2;

	// Outputs
	wire [31:0] result;
	wire finish;
	wire illegal;

	parameter PERIOD = 20;
	parameter real DUTY_CYCLE = 0.5;

	// Instantiate the Unit Under Test (UUT)
	division_float_32 uut (
		.clock(clock), 
		.start(start),
		.operand1(operand1), 
		.operand2(operand2), 
		.result(result), 
		.finish(finish), 
		.illegal(illegal)
	);

	initial begin
		// Initialize Inputs
		clock = 0;
		operand1 = 0;
		operand2 = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		#15000;
		operand1 = 32'h40133333;
		operand2 = 32'hc0933333;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#15000;
		operand1 = 32'h40900000;
		operand2 = 32'hc0900000;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#15000;
		operand1 = 32'h400000;
		operand2 = 32'h40000000;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#15000;
		operand1 = 32'h40600000;
		operand2 = 32'h3f000000;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#15000;
		operand1 = 32'h40666666;
		operand2 = 32'h3f333333;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#15000;
		operand1 = 32'h40600000;
		operand2 = 32'h0;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#15000;
		operand1 = 32'h35b0903c;
		operand2 = 32'h42f76666;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#15000;
		operand1 = 32'h0;
		operand2 = 32'h40600000;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#15000;
		operand1 = 32'h800000;
		operand2 = 32'h8000000;
		#10;
		start = 1;
		#10;
		start = 0;
		
	end

	initial
		forever begin
			clock = 1'b0;
			#(PERIOD - (PERIOD * DUTY_CYCLE))
			clock = 1'b1;
			#(PERIOD * DUTY_CYCLE);
		end
		
endmodule

