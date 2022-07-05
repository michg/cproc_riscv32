#include "spi_sdcard.h"

class Spi : public TimeProcess{
public:

        CData *ss;
	    CData *sclk;
       	CData *miso;
        CData *mosi;

        struct spi_sdcard *sdcard;
	uint32_t spiTimeRate;
	Spi(CData *ss, CData *sclk, CData *miso, CData *mosi, uint32_t spiTimeRate){
		this->ss = ss;
        this->sclk = sclk;
        this->miso = miso;
        this->mosi = mosi;
        this->spiTimeRate = spiTimeRate;
        schedule(spiTimeRate/4);
        this->sdcard = spi_sdcard_new("card.bin");
        *(miso) = 1;
	}

	enum State {START, CLKL, CLKH, STOP};
	State state = START;
	unsigned char rxdata = 0xff;
    unsigned char txdata = 0;
	uint32_t counter;


	virtual void tick(){
		switch(state){
			case START:
				if(*sclk == 0){
					state = CLKL;
					counter = 0;
                    txdata = 0;
				} else {
                    state = START;
				}
				(*miso) = (rxdata >> (7-counter)) & 1;
                schedule(spiTimeRate/4);
			break;
			case CLKL:
				if(*sclk == 1) {
                    state = CLKH;
                    txdata |= (*mosi) << (7-counter);
                    
                    counter++;                    
                }
                else
                    state = CLKL;
				schedule(spiTimeRate/4);
			break; 
            case CLKH:				
				if(counter == 8)
                    state = STOP;
                else {                   
                    if(*sclk == 0) {
                        state = CLKL;
                        (*miso) = (rxdata >> (7-counter)) & 1;
                    } else
                        state = CLKH;
				}
				schedule(spiTimeRate/4);
			break;            
			case STOP:            
                spi_sdcard_next_byte_to_slave(sdcard, txdata & 0xff);
				rxdata = spi_sdcard_next_byte_to_master(sdcard) & 0xff;
                //printf("to SD:%x\r\n",txdata);
                //printf("from SD:%x\r\n\r\n",rxdata);
                
                state = START;
				schedule(spiTimeRate/4);				
			break;
		}
	}
};

