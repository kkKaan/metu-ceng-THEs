`timescale 1ns / 1ps

// https://en.wikipedia.org/wiki/Double_dabble
// There was a bug in this code output register size was
// wrong edited it
module bin2bcd
 #( parameter                W = 10)  // input width
  ( input      [W-1      :0] bin   ,  // binary
    output reg [4 *((W+(W-4)) / 3):0] bcd   ); // bcd {...,thousands,hundreds,tens,ones}

  integer i,j;

  always @(bin) begin
    for(i = 0; i <= W+(W-4)/3; i = i+1) bcd[i] = 0;     // initialize with zeros
    bcd[W-1:0] = bin;                                   // initialize with input vector
    for(i = 0; i <= W-4; i = i+1)                       // iterate on structure depth
      for(j = 0; j <= i/3; j = j+1)                     // iterate on structure width
        if (bcd[W-i+4*j -: 4] > 4)                      // if > 4
          bcd[W-i+4*j -: 4] = bcd[W-i+4*j -: 4] + 4'd3; // add 3
  end
endmodule

module Board232 (
	input mclk,
	input [3:0] btn,
	input [7:0] sw,
	output [7:0] led,
	output reg [6:0] seg,
	output reg [3:0] an,
	output dp,
	output [2:1] OutBlue,
	output [2:0] OutGreen,
	output [2:0] OutRed,
	output HS,
	output VS
    );

	assign dp = 1'b1;
	assign led[1] = 0;
    assign led[3] = 0;
    assign led[7:5] = 0;
	initial begin
        seg[6:0] = 7'b0111111;
        an[3:0]  = 4'b1111;
	end

	// adjust board clock
	reg [26:0] mclk_counter;
	initial mclk_counter<= 0;
	always @(posedge mclk) mclk_counter = mclk_counter+1;
	// select clock : 26->slower | 24->faster
	reg clk;
	initial clk = 1'b0;
	always@(btn[3] or mclk_counter[25] or btn[0])
	begin
		if(btn[3])
			clk = mclk_counter[25];
		else
			clk = btn[0];
	end

	wire [9:0] result;
	wire [15:0] bcd_result;
    reg [4:0] tmp_digit;

    // Bin to Binary Coded Decimal (input is 10 bit wide)
    bin2bcd #(10) B2BCD(result, bcd_result);

	lab4_2 HH (
			sw[7],   // mode
            sw[6:4], // opcode
            sw[3:0], // value
			clk,
            btn[2],  // reset
            result,
            led[0],  // cacheFull
            led[2],  // invalidOp
            led[4]   // overflow
	);

	always @(mclk_counter[18:17])
	begin
		case (mclk_counter[18:17])
			2'b00:
				begin
					an = 4'b0111;
                    if(sw[7]) // EXEC MODE
                        tmp_digit = bcd_result[15:12];
                    else // LOAD MODE
                        tmp_digit = 5'd16; // PRINT DASH
				end
			2'b01:
				begin
					an = 4'b1011;
					if(sw[7]) // EXEC MODE
                        tmp_digit = bcd_result[11:8];
                    else // LOAD MODE
                        tmp_digit = 4'd1; // PRINT ONE, looks like l

				end
			2'b10:
				begin
					an = 4'b1101;
					if(sw[7]) // EXEC MODE
                        tmp_digit = bcd_result[7:4];
                    else // LOAD MODE
                        tmp_digit = 4'hD; // PRINT D
				end
            default:
                begin
					an = 4'b1110;
					if(sw[7]) // EXEC MODE
                        tmp_digit = bcd_result[3:0];
                    else // LOAD MODE
                        tmp_digit = 5'd16; // PRINT DASH

				end
		endcase

		case (tmp_digit)
			5'd0: seg <= ~7'h3F;
			5'd1: seg <= ~7'h06;
			5'd2: seg <= ~7'h5B;
			5'd3: seg <= ~7'h4F;
			5'd4: seg <= ~7'h66;
			5'd5: seg <= ~7'h6D;
			5'd6: seg <= ~7'h7D;
			5'd7: seg <= ~7'h07;
			5'd8: seg <= ~7'h7F;
			5'd9: seg <= ~7'h6F;
			5'd10: seg <= ~7'h77;
			5'd11: seg <= ~7'h7C;
			5'd12: seg <= ~7'h39;
			5'd13: seg <= ~7'h5E;
			5'd14: seg <= ~7'h79;
			5'd15: seg <= ~7'h71;
            // SPECIAL CASES
            // DASH
            5'd16: seg <= ~7'h40;
			default: seg <= ~7'b0000000;
		endcase

	end

	// VGA
	assign OutBlue = 0;
	assign OutGreen = 0;
	assign OutRed = 0;
	assign HS = 0;
	assign VS = 0;

endmodule
