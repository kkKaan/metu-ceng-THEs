// Created by Kaan Karacanta

`timescale 1ns / 1ps 

module lab4_2(// INPUTS
              input wire      mode,
              input wire[2:0] opCode,
              input wire[3:0] value,
              input clk,
              input reset,
              // OUTPUTS
              output reg[9:0] result,
              output reg cacheFull,
              output reg invalidOp,
              output reg overflow);

    //================//
    // INITIAL BLOCK  //
    //================//
    //Modify the lines below to implement your design
    reg [6:0] accumulator [31:0];
    integer i;
    reg [5:0] accIndex;
    reg [4:0] executeIndex;
    reg [4:0] startIndex;
    reg [9:0] populationCount;
    reg [9:0] p0; // prev value 1
    reg [9:0] p1; // prev value 2
    reg [17:0] summ; // a value to simplify some calculations, not necessarily be a sum of 2 variables

    initial begin
        for(i = 0; i < 32; i = i+1)
        begin
            accumulator[i] = 7'd0;
        end
        accIndex = 6'd0;
        executeIndex = 5'd0;
        startIndex = 5'd0;
        populationCount = 10'd0;
        p0 = 10'd0;
        p1 = 10'd0;
        summ = 18'd0;
        result = 10'd0;
        cacheFull = 0;
        invalidOp = 0;
        overflow = 0;
    end

    //================//
    //      LOGIC     //
    //================//
    //Modify the lines below to implement your design
    always @(posedge clk or posedge reset)
    begin
        invalidOp = 0; 
        if(reset == 1) // very similar to initial block, except invalidOp
        begin
            for(i = 0; i < 32; i = i+1)
            begin
                accumulator[i] = 7'd0;
            end
            accIndex = 6'd0;
            executeIndex = 5'd0;
            startIndex = 5'd0;
            populationCount = 10'd0;
            p0 = 10'd0; 
            p1 = 10'd0; 
            summ = 18'd0;
            result = 10'd0;
            cacheFull = 0;
            overflow = 0;
        end
        else
        begin
            case (mode)
                1'b0: // load 
                begin
                    if(accIndex == 6'd32)
                    begin
                        cacheFull = 1;
                    end
                    else
                    begin
                        if(opCode == 3'b011 || opCode == 3'b111) // check if the code is invalid
                        begin
                            invalidOp = 1;
                        end
                        else
                        begin
                            accumulator[accIndex] = {opCode[2:0], value[3:0]};
                            accIndex = accIndex + 1;
                        end
                    end
                end
                1'b1: // calculate
                begin
                    case (accumulator[executeIndex][6:4])
                        3'b000: // add
                        begin
                            if((1024 - accumulator[executeIndex][3:0]) <= p0) // overflow check, most of the operations have some check similar to that
                            begin 
                                overflow = 1;
                            end
                            result = (p0 + accumulator[executeIndex][3:0]) % 1024;
                        end
                        3'b001: // add2
                        begin
                            summ = p0 + p1;
                            if((1024 - accumulator[executeIndex][3:0]) <= summ) 
                            begin 
                                overflow = 1;
                            end
                            result = (p0 + p1 + accumulator[executeIndex][3:0]) % 1024;
                        end
                        3'b010: // fused multiply add
                        begin
                            summ = p0 * p1;
                            if((1024 - accumulator[executeIndex][3:0]) <= summ) 
                            begin 
                                overflow = 1;
                            end
                            result = (p0 * p1 + accumulator[executeIndex][3:0]) % 1024;
                        end
                        3'b100: // population count
                        begin
                            populationCount = 0;
                            for(i = 0; i < 10; i = i + 1) // calculate the number of 1's in result
                            begin
                                if(p0[i] == 1) begin populationCount = populationCount + 1; end
                            end
                            result = populationCount;
                            overflow = 0; 
                        end
                        3'b101: // bit reverse
                        begin
                            for(i = 0; i < 10; i = i + 1)
                            begin
                                result[i] = p0[9-i];  
                            end
                            overflow = 0; 
                        end
                        3'b110: // set return
                        begin
                            startIndex = accumulator[executeIndex][3:0];
                        end
                    endcase

                    if(accumulator[executeIndex][6:4] != 3'b110) // adjusting previous 2 values
                    begin
                        p1 = p0;
                        p0 = result;
                    end 

                    executeIndex = executeIndex + 1; 
                    if(executeIndex == accIndex) // check whether the incremented index is the number of elements in the accumulator
                    begin
                        executeIndex = startIndex;
                    end
                end
            endcase
        end
    end

endmodule