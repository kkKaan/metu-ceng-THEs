// Created by Kaan Karacanta

`timescale 1ns / 1ps 

module lab3_2(
			input[4:0] smartCode,
			input CLK, 
			input lab, // 0:Digital, 1:Mera
			input [1:0] mode, // 00:exit, 01:enter, 1x: idle 
			output reg [5:0] numOfStuInMera,
			output reg [5:0] numOfStuInDigital,
			output reg restrictionWarnMera,// 1:show warning, 0:do not show warning
			output reg isFullMera, // 1:full, 0:not full
			output reg isEmptyMera, // 1: empty, 0:not empty
			output reg unlockMera,	// 1:door is open, 0:closed
			output reg restrictionWarnDigital,// 1:show warning, 0:do not show warning
			output reg isFullDigital, // 1:full, 0:not full
			output reg isEmptyDigital, // 1: empty, 0:not empty
			output reg unlockDigital // 1:door is open, 0:closed
	);
	 
	// You may declare your variables below	
	
	initial begin
			numOfStuInMera=0;
			restrictionWarnMera=0;
			isFullMera=0;
			isEmptyMera=1'b1;
			unlockMera=0;

			numOfStuInDigital=0;
			restrictionWarnDigital=0;
			isFullDigital=0;
			isEmptyDigital=1'b1;
			unlockDigital=0;
	end
	//Modify the lines below to implement your design
	//always @(posedge CLK) 
	//...

  	integer sum = 0;
	integer i;
  
	always@(posedge CLK)
	begin // initializations
		unlockDigital = 0;
		unlockMera = 0;
		restrictionWarnDigital = 0;
		restrictionWarnMera = 0;
     
		begin 
			case (lab)
				1'b0: // Digital
					begin
						case (mode) 
							2'b00: // - count
                            	if(isEmptyDigital == 1'b0) // cannot exit | num -
                                	begin
                                    	unlockDigital = 1;
                                    	numOfStuInDigital <= numOfStuInDigital - 1;

										if(numOfStuInDigital == 0) 
											isEmptyDigital = 1'b1;
                                    end
							2'b01: // + count
								if(numOfStuInDigital < 15) // enter free | count + 
                                	begin
                                    	unlockDigital = 1;
                                    	numOfStuInDigital <= numOfStuInDigital + 1;

										if(numOfStuInDigital == 30)
											isFullDigital = 1;
                                    end
								else if(numOfStuInDigital >= 15)  // check for student codes
									if(isFullDigital == 0) // check if the lab is full
										begin
											for(i = 0; i < 5; i = i+1)
												begin
													sum = sum + smartCode[i];
												end
                                          	if((sum % 2) == 1) // oddd == 1 // entering condition | count + | unlock the door
												begin
													unlockDigital = 1;
													numOfStuInDigital <= numOfStuInDigital + 1; 

													if(numOfStuInDigital == 30)
														isFullDigital = 1;
												end
											else // restriction warn digital (should be cleared in the next clock)
												restrictionWarnDigital = 1;
										end 
							default: 
								unlockDigital = 0;
						endcase
					end
				1'b1: // Mera
					begin
						case (mode) // - count
							2'b00:
								if(isEmptyMera == 1'b0) // cannot exit from an empty lab, so check that
									begin
										unlockMera = 1;
                                    	numOfStuInMera <= numOfStuInMera - 1;

										if(numOfStuInMera == 0)
											isEmptyMera = 1'b1;
									end
							2'b01: // + count
								if(numOfStuInMera < 15)
                                	begin
										unlockMera = 1;
										numOfStuInMera <= numOfStuInDigital + 1;

										if(numOfStuInMera == 30)
											isFullMera = 1'b1;
                                    end
								else if(numOfStuInMera >= 15) // check codes
									if(isFullMera == 0)
										begin
											for(i = 0; i < 5; i = i+1)
												begin
													sum = sum + smartCode[i];
												end
                                          	if((sum % 2) == 0) // oddd == 0 | entering condition | count + | unlock the door
												begin
													unlockMera = 1;
													numOfStuInMera <= numOfStuInDigital + 1;

													if(numOfStuInMera == 30)
														isFullMera = 1'b1;
												end
											else // restriction warn mera (should be cleared in the next clock)
												restrictionWarnMera = 1;
										end
							default: 
								unlockMera = 0;
						endcase
					end
			endcase
		end
	end
	
endmodule

