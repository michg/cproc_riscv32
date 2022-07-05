#include "VBriey.h"
#include "verilated.h"
#ifdef FST
    #include "verilated_fst_c.h" 
#else
    #include "verilated_vcd_c.h"
#endif

#include "../simframework/framework.h"
#include "../simframework/uart.h"

Workspace<VBriey> *murax;
uint8_t trig = 0;

class MuraxWorkspace : public Workspace<VBriey>{
public:
	MuraxWorkspace(int vcd) : Workspace("VBriey", vcd){
		
		ClockDomain *mainClk = new ClockDomain(&top->io_axiClk,NULL,20,300);
		AsyncReset *asyncReset = new AsyncReset(&top->io_asyncReset,500, 0, 400); 
        UartRx *uartRx = new UartRx(&top->io_uart_txd,1.0e9/115200, NULL, 'k');
		UartTx *uartTx = new UartTx(&top->io_uart_rxd,1.0e9/115200);
		//Profile *prof = new Profile(&top->vsim->picorv32->reg_pc, 0x4A88, 0x4A8C);
        //CheckTrigger *PCtrig = new CheckTrigger(&top->vsim->picorv32->reg_pc, 0x00004680, &trig); //0x45D4=sdcard_sdtest, 0x46B4 (Init), 0x4728 (sector count)
        //setTrigger(&trig);
	    
	   
		timeProcesses.push_back(mainClk);
  		timeProcesses.push_back(asyncReset);
		timeProcesses.push_back(uartRx);
		timeProcesses.push_back(uartTx); 
		//checkProcesses.push_back(PCtrig);
		//checkProcesses.push_back(prof);
	}
};





int main(int argc, char **argv, char **env) {

	int vcd=0;
    Verilated::randReset(2);
	Verilated::commandArgs(argc, argv);
    if(argc==2 && strcmp(argv[1],"vcd")==0) vcd = 1; 
	printf("BOOT\n");

	murax  = new MuraxWorkspace(vcd);
	murax->run(10000e6); //100e6

	exit(0);
}

double sc_time_stamp ()
{ double tmp;
  tmp=murax->gettime();
  return tmp;

} 
