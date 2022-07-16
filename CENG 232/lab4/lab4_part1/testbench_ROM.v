`timescale 1ns / 1ps

module testbench_ROM(  // Example testbenches to modify
    );
	reg [3:0] romAddr; 
	wire[4:0] romOutput;
	integer result = 0;
	//instance
	lab4ROM ROM(romAddr,romOutput);

	initial begin
	
		$display("Starting Testbench");
		
		//sample 2 cases
		#1; 
		romAddr=4'b0000; //address 0
		#7; 
		if (romOutput==5'b00000) result = result + 1; 	
			else $display("time:",$time,":For romAddr:%b Error in romOutput:%b",romAddr,romOutput);	

		#1; 
		
		romAddr=4'b0010;  //address 2
		#7; 
		if (romOutput==5'b00110) result = result + 1; 	
			else $display("time:",$time,":For romAddr:%b Error in romOutput:%b",romAddr,romOutput);	

		#1; 

		
		//fill the remaining cases...
	
		$display("Result %d",result);	
		$display("Testbench was finished");	
		$finish;
	end
	
	
endmodule

