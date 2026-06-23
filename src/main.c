#define SIM_SCGC5 (*((volatile unsigned int*)0x40048038)) //Habilita o sinal de relógio (clock) para os periféricos de baixa energia, especificamente as portas de GPIO

#define PORTB_PCR19 (*((volatile unsigned int*)0x4004A04C))
/*Controla a multiplexação do pino 19 do Port B. 
Cada pino físico do microcontrolador pode assumir várias funções 
(GPIO, saída de PWM, canal ADC, UART, etc.). 
O campo MUX (bits 8, 9 e 10 deste registador) decide qual função está ativa.*/

#define GPIOB_PDDR (*((volatile unsigned int*)0x400FF054))//Define a direção dos pinos do Port B

// controla o nível lógico de saída de todos os pinos do Port B
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
	// ativa o clock especificamente para o PORTB (o bit 10 controla o fornecimento de energia/clock do PORTB)

	PORTB_PCR19 |= 0x00000100; 
	//coloca o valor binário 001 no campo MUX, o que configura o pino explicitamente para operar como GPIO

	GPIOB_PDDR |= (1 << 19); // configura o pino 19 como uma saída digital.

	while (1)
	{
		GPIOB_PDOR |= (1 << 19); // seta valor 1 SOMENTE no pino 19 => pino 19 fica em valor alto => desliga o led(lógica invertida para os LED)

		//GPIOB_PCOR = (1 << 19);

		delayMs(1000);

		GPIOB_PDOR &= ~(1 << 19); // seta valor 0 SOMENTE no pino 19 => pino 19 fica em valor baixo => liga o led(lógica invertida para os LED)


		//GPIOB_PSOR = (1 << 19);

		delayMs(1000);
	}
	
}
