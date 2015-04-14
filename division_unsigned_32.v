`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:38:09 04/12/2015 
// Design Name: 
// Module Name:    division_unsigned_32 
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
module division_unsigned_32(clock, start, operand1, operand2, result, finish, illegal); //32-bit unsigned integer divider
	input clock; //clock signal
	input start; //start signal
	input [31:0] operand1, operand2; //two 32-bit operands
	output reg [63:0] result; //64位相除结果，低32位为商，高32位余数
	output reg finish; //计算完成信号，计算完后为1，否则为0
	output illegal; //非法信号，除数为0则为1，否则为0
	
	reg [63:0] temp_operand1, temp_operand2; //两个64位临时寄存器，分别承接除数被除数
	reg [5:0] step; //时钟周期计数

	always @(posedge clock) begin //在时钟信号的上升沿
		if (start) begin
			temp_operand1 = operand1; //将被除数拓展为64位，其在低32位
			temp_operand2 = {operand2, 32'b0}; //将除数拓展为64位，其在高32位
			finish = 0; //计算完成信号置0
			step = 0; //重置移位次数，进入下一个移位循环
		end
		if(step == 32) begin //如果已移位32次
			result = temp_operand1; //获取计算结果
			finish = 1; //计算完成
		end else begin //未移够32位
			temp_operand1 = temp_operand1 << 1; //被除数左移一位
			if (temp_operand1 >= temp_operand2) temp_operand1 = temp_operand1 - temp_operand2 + 1;
			//如果被除数比除数大，则被除数减去除数并加一
			step = step + 1; //递增移位次数
		end
	end

	assign illegal = (operand2 == 0) ? 1 : 0; //除数为0则非法信号为1

endmodule
