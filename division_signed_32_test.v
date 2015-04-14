`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   20:23:27 04/13/2015
// Design Name:   division_signed_32
// Module Name:   /home/lin/program/ISE/2015/ALU/division_signed_32_test.v
// Project Name:  ALU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: division_signed_32
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module division_signed_32_test;

	// Inputs
	reg clock;
	reg start;
	reg [31:0] operand1;
	reg [31:0] operand2;

	// Outputs
	wire [63:0] result;
	wire finish;
	wire illegal;

	parameter PERIOD = 20;
	parameter real DUTY_CYCLE = 0.5;

	// Instantiate the Unit Under Test (UUT)
	division_signed_32 uut (
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
		#7000;
		operand1 = 31'h10000000;
		operand2 = 31'h10;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#7000;
		operand1 = 2222;
		operand2 = 2;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#7000;
		operand1 = 200;
		operand2 = 0;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#7000;
		operand1 = -42;
		operand2 = 5;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#7000;
		operand1 = -42;
		operand2 = -5;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#7000;
		operand1 = 42;
		operand2 = -5;
		#10;
		start = 1;
		#10;
		start = 0;
		
		#7000;
		operand1 = 42;
		operand2 = 5;
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

