// clk defines

#define fosc 12000000
#define cclk (5*fosc)
#define pclk (cclk/4)
#define ADclk 3000000
#define clkDiv_value ((pclk/ADclk)-1)

// SFRS
// ADCR
#define CLKDIV 8
#define PDN_BIT 21
#define START_CONV 24

#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3

// ADDR
#define RESULT 6
#define DONE_BIT 31

#define AIN0 0x00400000
#define AIN1 (1<<24)
#define AIN2 (1<<26)
#define AIN3 0x10000000

