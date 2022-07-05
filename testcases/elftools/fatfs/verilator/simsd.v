import "DPI-C" context function void initspi();
import "DPI-C" context function void writespi(input bit[31:0] in);
import "DPI-C" context function bit[31:0] readspi();

module simsd(input wire		clk,
	       input wire		cs,
	       input wire [31:0]	bus_addr,
	       input wire [31:0]	bus_wr_val,	
	       input wire [3:0]		bus_bytesel,
	       output reg		bus_ack,
	       output reg [31:0]	bus_data
);

reg [31:0] readval;

initial begin
	bus_ack = 1'b0;
	bus_data = 32'b0;
        initspi();
end


always @(posedge clk) begin
       bus_data <= 32'b0;
          if (cs && bus_bytesel[3:0] == 4'b0001) begin
		if (bus_addr[3:0] == 4'b1000) begin
			writespi({24'b0,bus_wr_val[7:0]});
                        readval <= readspi();
		end
          end else if (cs) begin
		if (bus_addr[3:0] == 4'b1000) begin
			bus_data <= readval;
		end
	  end
	bus_ack <=  cs;
end

endmodule
