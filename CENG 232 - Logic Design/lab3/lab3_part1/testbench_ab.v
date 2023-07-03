`timescale 1ns / 1ps

module testbench_ab;
    // Inputs
	reg A;
	reg B;
	reg clk;
	// Outputs
	wire Q;

	// Instantiate the Unit Under Test (UUT)
	ab uut (
		.A(A),
		.B(B),
		.clk(clk),
		.Q(Q)
	);

	// At 5, 15, 25, .. clk will change 0->1
	// At 10, 20, 30, .. clk will change 1->0
    initial clk = 0;
	always #5 clk = ~clk;
	initial begin
		// Set monitor for inputs and outputs.
		$monitor("Time=%.2d | A=%b B=%b| Q=%b", $time, A, B, Q);

        //==========================//
        //       INITIAL VAL        //
        //==========================//
        // Assume initial value of Q is Zero
		#1; //(1ns)Check Initial Q value
		if (Q != 1'b0) $display("Initial value of Q is wrong");
		else $display("Successful");

        //==========================//
        //        SETO TO 1         //
        //==========================//
		#1; //(2ns) Set KB=01, (set to one)
		A = 1'b0; B = 1'b1;
		#5; //(7ns) Wait for clock edge
		if (Q != 1'b1) $display("Value of Q after Qprev=0 A=0 B=0 is wrong");
		else $display("Successful");

        //==========================//
        //       COMPLEMENT         //
        //==========================//
        #1; //(8ns) Set KB=11, complement
		A = 1'b1; B = 1'b1;
		#8; //(16ns) Wait for clock edge
		if (Q != 1'b0) $display("Value of Q after Qprev=1 A=1 B=1 is wrong");
		else $display("Successful");
        #10; //(26ns) Check the other cycle value
		if (Q != 1'b1) $display("Value of Q after Qprev=0 A=1 B=1 is wrong");
		else $display("Successful");

        //==========================//
        //       SET TO ZERO        //
        //==========================//
		#1; //(27ns) Set KB=10, set to zero
		A = 1'b1; B = 1'b0;
		#9; //(36ns) Wait for clock edge
		if (Q != 1'b0) $display("Value of Q after Qprev=1 A=1 B=0 is wrong");
		else $display("Successful");

        //==========================//
        //       NO CHANGE          //
        //==========================//
		#1; //(37ns) Set KB=00, no change
		A = 1'b0; B = 1'b0;
		#9; //(46ns) Wait for clock edge
		if (Q != 1'b0) $display("Value of Q after Qprev=0 A=0 B=0 is wrong");
		else $display("Successful");
		#10; //(56ns) Wait for clock edge again
		if (Q != 1'b0) $display("Value of Q after Qprev=1 A=1 B=0 is wrong");
		else $display("Successful");
		#5;
		$display("End of Sim!");
		$finish;
	end

endmodule

