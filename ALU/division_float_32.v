`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:17:57 04/13/2015 
// Design Name: 
// Module Name:    division_float_32 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module division_float_32(clock, start, operand1, operand2, result, finish, illegal);
	input clock; //clock signal
	input start; //start signal
	input [31:0] operand1, operand2; //两个32位操作数
	output reg [31:0] result; //32位相除结果
	output reg finish; //计算完成信号，计算完后为1，否则为0
	output illegal; //非法信号，除数为0则为1，否则为0
	reg [7:0] exponent;
	reg [23:0] significand1, significand2;
	reg [95:0] temp_operand1, temp_operand2; //两个64位临时寄存器，分别承接除数被除数
	reg [95:0] sub_result;
	reg [5:0] step; //时钟周期计数
	
	always @(posedge clock) begin //在时钟信号的上升沿
		if(start) begin
			significand1 = {1'b1, operand1[22:0]};
			significand2 = {1'b1, operand2[22:0]};
			temp_operand1 = {significand1, 24'b0}; //将被除数拓展为96位，其在低48位
			temp_operand2 = {significand2, 48'b0}; //将除数拓展为96位，其在高48位
			finish = 0;
			step = 0;
		end
		if(step == 48) begin //如果已移位48次
			sub_result = temp_operand1; //获取计算结果
			exponent = 127 + operand1[30:23] - operand2[30:23];
			if(sub_result[72:48] * 2 > significand2) begin
				sub_result = sub_result + 1;
			end
			if(sub_result[24]) begin
				result[22:0] = sub_result[23:1];
			end else begin
				exponent = exponent - 1;
				result[22:0] = sub_result[22:0];
			end
			if((127 + operand1[30:23]) < operand2[30:23]) begin
				exponent = 0;
			end
			result[31] = operand1[31] ^ operand2[31];
			result[30:23] = exponent;
			if(operand1 == 0) result = 0;
			finish = 1;
		end else begin //未移够48位
			temp_operand1 = temp_operand1 << 1; //被除数左移一位
			if (temp_operand1 >= temp_operand2) temp_operand1 = temp_operand1 - temp_operand2 + 1;
			//如果被除数比除数大，则被除数减去除数并加一
			step = step + 1; //递增移位次数
		end
	end

	assign illegal = (operand2 == 0) ? 1 : 0; //除数为0则非法信号为1

endmodule
