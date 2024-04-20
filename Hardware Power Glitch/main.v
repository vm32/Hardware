`timescale 1ns / 1ps
module main(
    input sw0,
    input clk,
    input btns,
	 input [0:7] sw,
    output led0,
    output led1,
    output JB1
    );
	 
	 reg [31:0] counter;
	 reg glitch_reg;
	 reg led0_reg;
	 reg led1_reg;
	 reg [1:0] state;
	 
	 localparam idle = 0;
	 localparam glitch = 1;
	 localparam holdoff = 2;
	 
	 assign led0 = led0_reg;
	 assign led1 = led1_reg;
	 assign JB1 = glitch_reg;
	 
	 initial begin
		counter <= 0;
		glitch_reg <= 1;
		led0_reg <= 1;
		led1_reg <= 1;
		state <= idle;
	 end
	 
	 always @(posedge clk) begin
		case(state)
			idle: begin
				led0_reg <= 1;
				led1_reg <= 1;
				counter <= 0;
				glitch_reg <= 1;
				if(btns==1) begin
					state <= glitch;
				end
			end
			glitch: begin
				led0_reg <= 0;
				led1_reg <= 0;
				counter <= counter +1;
				glitch_reg <= 0;
				if(counter==(sw<<1)) begin
					state <= holdoff;
					counter <= 0;
				end
			end
			holdoff: begin
				led0_reg <= 0;
				led1_reg <= 1;
				counter <= counter +1;
				glitch_reg <= 1;
				if(counter==50000000) begin
					state <= idle;
					counter <= 0;
				end
			end
		endcase
	 end


endmodule
