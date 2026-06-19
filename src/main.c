#define SIM_SCGC5 (*((volatile unsigned int*)0x40048038))

#define PORTB_PCR19 (*((volatile unsigned int*)0x4004A04C))

#define GPIOB_PDDR (*((volatile unsigned int*)0x400FF054))

#define GPIOB_PDOR (*((volatile unsigned int*)0x400FF040))

#define GPIOB_PSOR (*((volatile unsigned int*)0x400FF044))

#define GPIOB_PCOR (*((volatile unsigned int*)0x400FF048))

#define GPIOB_PTOR (*((volatile unsigned int*)0x400FF04C))



void delayMs(int n) {
	volatile int i; // volatile impede otimizacoes do compilador
	volatile int j;
	for (i = 0; i < n; i++){
        for (j = 0; j < 7000; j++) {}
    }
}

int main(void){
    
	SIM_SCGC5 |= (1 << 10); // seta somente o bit 10 com valor 1

	PORTB_PCR19 |= 0x00000100; 

	GPIOB_PDDR |= (1 << 19); // pin 19 como output

	while (1)
	{
		GPIOB_PDOR |= (1 << 19); // seta valor 1 no pino 19

		//GPIOB_PCOR = (1 << 19);

		delayMs(1000);

		GPIOB_PDOR &= ~(1 << 19);

		//GPIOB_PSOR = (1 << 19);

		delayMs(1000);
	}
	
}
