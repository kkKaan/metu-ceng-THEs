// Created by Kaan Karacanta

`timescale 1ns / 1ps

module lab4ROM (input [3:0] romAddr, output reg[4:0] romOutput);

/*Write your code here*/
	always@(romAddr)  
	begin
		case(romAddr)  // ROM values according to the text
			0: romOutput = 5'd0;
			1: romOutput = 5'd1;
			2: romOutput = 5'd6;
			3: romOutput = 5'd7;
			4: romOutput = 5'd11;
			5: romOutput = 5'd12;
			6: romOutput = 5'd13;
			7: romOutput = 5'd14;
			8: romOutput = 5'd29;
			9: romOutput = 5'd30;
			10: romOutput = 5'd31;
			11: romOutput = 5'd16;
			12: romOutput = 5'd23;
			13: romOutput = 5'd24;
			14: romOutput = 5'd25;
			15: romOutput = 5'd26;
		endcase
	end

endmodule
																							
module lab4RAM (
	input ramMode, //0:read, 1:write
	input [3:0] ramAddr, 
	input [4:0] ramInput,
	input  ramOp, //0:polynomial, 1:derivative
	input [1:0] ramArg,  //00:+1, 01:+2, 10:-1, 11:-2
	input CLK, 
	output reg [8:0] ramOutput);

/*Write your code here*/	
	reg [8:0] RAM [15:0];
	integer i = 0; 

	initial
	begin // makes each bit of RAM 0
		for(i = 0; i < 16; i = i+1)
		begin
			RAM[i] = 9'd0;
		end
		ramOutput = 9'd0;
	end

	always@(ramMode or ramAddr) // async = 0 // read
	begin
		if(ramMode == 0)
		begin
			ramOutput = RAM[ramAddr];
		end
	end

	always@(posedge CLK) // sync = 1 // write
	begin
		if(ramMode == 1)
		begin
			case(ramOp) // these cases can be combined actually
				1'b0: // original function
				begin
					case (ramArg)
						2'b00: RAM[ramAddr] = ((-1)**ramInput[4] * 1**4) + ((-1)**ramInput[3] * 1**3) + ((-1)**ramInput[2] * 1**2) + ((-1)**ramInput[1] * 1**1) + ((-1)**ramInput[0] * 1**0); 
						2'b01: RAM[ramAddr] = ((-1)**ramInput[4] * 2**4) + ((-1)**ramInput[3] * 2**3) + ((-1)**ramInput[2] * 2**2) + ((-1)**ramInput[1] * 2**1) + ((-1)**ramInput[0] * 2**0); 
						2'b10: RAM[ramAddr] = ((-1)**ramInput[4] * (-1)**4) + ((-1)**ramInput[3] * (-1)**3) + ((-1)**ramInput[2] * (-1)**2) + ((-1)**ramInput[1] * (-1)**1) + ((-1)**ramInput[0] * (-1)**0);
						2'b11: RAM[ramAddr] = ((-1)**ramInput[4] * (-2)**4) + ((-1)**ramInput[3] * (-2)**3) + ((-1)**ramInput[2] * (-2)**2) + ((-1)**ramInput[1] * (-2)**1) + ((-1)**ramInput[0] * (-2)**0); 
					endcase
				end
				1'b1: // derivative of the function
				begin
					case (ramArg)
						2'b00: RAM[ramAddr] = (((-1)**ramInput[4]) * 4 * (1**3)) + (((-1)**ramInput[3]) * 3 * (1**2)) + (((-1)**ramInput[2]) * 2 * (1**1)) + (((-1)**ramInput[1]) * 1 * (1**0)); 
						2'b01: RAM[ramAddr] = (((-1)**ramInput[4]) * 4 * (2**3)) + (((-1)**ramInput[3]) * 3 * (2**2)) + (((-1)**ramInput[2]) * 2 * (2**1)) + (((-1)**ramInput[1]) * 1 * (2**0)); 
						2'b10: RAM[ramAddr] = (((-1)**ramInput[4]) * 4 * ((-1)**3)) + (((-1)**ramInput[3]) * 3 * ((-1)**2)) + (((-1)**ramInput[2]) * 2 * ((-1)**1)) + (((-1)**ramInput[1]) * 1 * ((-1)**0));
						2'b11: RAM[ramAddr] = (((-1)**ramInput[4]) * 4 * ((-2)**3)) + (((-1)**ramInput[3]) * 3 * ((-2)**2)) + (((-1)**ramInput[2]) * 2 * ((-2)**1)) + (((-1)**ramInput[1]) * 1 * ((-2)**0)); 
					endcase
				end
			endcase

			if(RAM[ramAddr][8] == 1) // two's complement of the value on that ram address
			begin
				RAM[ramAddr] = ~RAM[ramAddr] + 1'b1;
				RAM[ramAddr][8] = 1;
			end
		end
	end

endmodule

module polMEM(input mode, input [3:0] memAddr, input op, input [1:0] arg, input CLK, output wire [8:0] memOutput); // a module given for combining ROM and RAM implementations

	/*Don't edit this module*/
	wire [4:0]  romOutput;

	lab4ROM RO(memAddr, romOutput);
	lab4RAM RA(mode, memAddr, romOutput, op, arg, CLK, memOutput);

endmodule
