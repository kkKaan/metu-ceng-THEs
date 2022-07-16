`timescale 1ns / 1ps
module testbench_RAM(  // Example testbenches to modify
    );

	reg ramMode; //0:read, 1:write
	reg [3:0] ramAddr; 
	reg [4:0] ramInput;
	reg ramOp; //0:polynomial, 1:derivative
	reg [1:0] ramArg; //00:+1, 01:+2, 10:-1, 11:-2
	reg CLK;
	wire [8:0] ramOutput;
	 
	//instance
	lab4RAM RAM(ramMode, ramAddr, ramInput, ramOp, ramArg, CLK, ramOutput);
	//Set initial values
	initial CLK = 0;	
	always #5 CLK = ~CLK;	 

	initial begin
	
		$display("Starting Testbench");
		ramMode=1'b1;//write
		ramAddr=4'b0100;
		ramInput=5'b01011;
		ramOp=1'b1; //derivative
		ramArg=2'b10; //-1
		#10;
		
		ramMode=1'b0;//read
		#1;
		if (ramOutput==9'b100001010) $display("CASE 1 passed..");	
			else $display("CASE 1: time:",$time,":For ramAddr:%b Error in ramOutput:%b",ramAddr,ramOutput);

		//You are free to add new cases...
		
		$display("Testbench was finished");	
		$finish;
	end

endmodule
