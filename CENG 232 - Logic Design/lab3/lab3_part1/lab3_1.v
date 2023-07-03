// Created by Kaan Karacanta

`timescale 1ns / 1ps

module ab(input A, input B, input clk, output reg Q);

	 // output reg Q;
    initial Q = 0;

    // You can implement your code here
    // ...
	 
	 always@(posedge clk)
		case({A,B})
			2'b00: Q <= Q;
			2'b01: Q <= 1;
			2'b10: Q <= 0;
			2'b11: Q <= ~Q;
		endcase

endmodule

module ic1337(// Inputs
              input I0,
              input I1,
              input I2,
              input clk,
              // Outputs
              output Q0,
              output Q1,
              output Z);

    // You can implement your code here
    // ...
	 
	 ab ff1((~I2) & (~((~I1) | I0)), I2, clk, Q0);
	 ab ff2(~I2, (I0) ~^ (~(I2 | (~I1))), clk, Q1);
	 
	 assign Z = (Q0^Q1); // just a simple implementation according to the hw
	 
endmodule
