
#include "sdr_sdram.h"
#define SDRAM_BIT_BANKS    (2)
#define SDRAM_BIT_ROWS     (13)
#define SDRAM_BIT_COLS     (9)
#define SDRAM_SIZE         (2 << (SDRAM_BIT_ROWS + SDRAM_BIT_COLS + SDRAM_BIT_BANKS))



class Sdr : public SensitiveProcess{
public:
	vluint8_t *clk, *cs_n, *ras_n, *cas_n, *we_n, *ba, *dqm;
    vluint16_t *addr;
    vluint16_t *dq_in, *dq_out;
    SDRAM *sdr;
	Sdr(CData *clk, CData *cs_n,  CData *ras_n,  CData *cas_n, 
    CData *we_n,  CData *ba, SData *addr, CData  *dqm,   SData *dq_in, SData* dq_out){
    vluint8_t sdram_flags = FLAG_DATA_WIDTH_16;
        this->clk = clk;
        this->cs_n = cs_n;
        this->ras_n = ras_n;
        this->cas_n = cas_n;
        this->we_n = we_n;
        this->ba = ba;
        this->addr = addr;
        this->dqm  = dqm;
        this->dq_in = dq_in;
        this->dq_out = dq_out;
        this->sdr  = new SDRAM(SDRAM_BIT_ROWS, SDRAM_BIT_COLS, sdram_flags, NULL);
    }

virtual void tick(uint64_t time){
        //printf("TIME:%d\r\n");
		sdr->eval(time, (*clk)^1, 1,
        *cs_n, *ras_n, *cas_n, *we_n,
        *ba, *addr, *dqm, *dq_out, (vluint64_t&)*dq_in);
		}
};
