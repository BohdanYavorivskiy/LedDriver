#include <project.h>
#include "constants.h"
#include "buffer.h"
#include "dma.h"

// 
int16 lineNum = 0;
CY_ISR_PROTO(LineWrited);
CY_ISR(LineWrited)
{
	++lineNum;
	if (lineNum >= LineCount)
		lineNum = 0;

	transferEnableWithNewAddr((bufferPtr() + (SizeLine * lineNum)));
}

void restartLoadData()
{
	TransferControlReg_Write(0);
	transferEnableWithNewAddr((bufferPtr()));
	lineNum = 0; // -1 because will increment while interrupt
	TransferControlReg_Write(1);
}

int main()
{
	LineUpdateTimer_WriteCounter((LineUpdateTimerClockG / 1000000)/*clock in one uS*/ * TimeForLineUs);
	LineUpdateTimer_Start();	
		
	LineWrited_StartEx(LineWrited);
    CyGlobalIntEnable; 
	
	initBuff();

	initDma();	
    transferEnable(); 
    
	
    CyDelay(1000u);
    SPIM_Start();
	CyDelay(20u);
	
	TransferControlReg_Write(1);
    
    for(;;)
    {
		// reset
		CyDelay(1000u);
		restartLoadData();
		// TransferControlReg_Write(0);
		break;
		// CyDelayUs(10u);
    }
}


/* [] END OF FILE */
