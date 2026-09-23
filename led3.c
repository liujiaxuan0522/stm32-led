#define RCC_APB2ENR  (*(volatile unsigned int *)0x40021018)

#define GPIOA_CRL    (*(volatile unsigned int *)0x40010800)
#define GPIOA_CRH    (*(volatile unsigned int *)0x40010804)
#define GPIOA_IDR    (*(volatile unsigned int *)0x40010808)
#define GPIOA_ODR    (*(volatile unsigned int *)0x4001080C)
#define GPIOA_BSRR   (*(volatile unsigned int *)0x40010810)
#define GPIOA_BRR    (*(volatile unsigned int *)0x40010814)

#define GPIOB_CRL    (*(volatile unsigned int *)0x40010C00)
#define GPIOB_CRH    (*(volatile unsigned int *)0x40010C04)
#define GPIOB_IDR    (*(volatile unsigned int *)0x40010C08)
#define GPIOB_ODR    (*(volatile unsigned int *)0x40010C0C)
#define GPIOB_BSRR   (*(volatile unsigned int *)0x40010C10)
#define GPIOB_BRR    (*(volatile unsigned int *)0x40010C14)

#define GPIOC_CRL    (*(volatile unsigned int *)0x40011000)
#define GPIOC_CRH    (*(volatile unsigned int *)0x40011004)
#define GPIOC_IDR    (*(volatile unsigned int *)0x40011008)
#define GPIOC_ODR    (*(volatile unsigned int *)0x4001100C)
#define GPIOC_BSRR   (*(volatile unsigned int *)0x40011010)
#define GPIOC_BRR    (*(volatile unsigned int *)0x40011014)

#define STK_CTRL     (*(volatile unsigned int *)0xE000E010)
#define STK_LOAD     (*(volatile unsigned int *)0xE000E014)
#define STK_VAL      (*(volatile unsigned int *)0xE000E018)

#define SYSCLK_HZ   72000000UL

static void delay_ms(unsigned int ms)
{
    unsigned int i;

    STK_LOAD = SYSCLK_HZ / 1000 - 1;
    STK_VAL  = 0;
    STK_CTRL = 0x05;

    for (i = 0; i < ms; i++)
    {
        while ((STK_CTRL & (1u << 16)) == 0)
        {
        }
    }

    STK_CTRL = 0;
}

static void LED_Init(void)
{
    RCC_APB2ENR |= (1u << 2) | (1u << 3) | (1u << 4);

    GPIOB_CRL &= ~(0xFu << 0);
    GPIOB_CRL |=  (0x3u << 0);

    GPIOA_CRL &= ~(0xFu << 0);
    GPIOA_CRL |=  (0x3u << 0);

    GPIOC_CRH &= ~(0xFu << 20);
    GPIOC_CRH |=  (0x2u << 20);

    GPIOA_BSRR = (1u << 16);
    GPIOB_BSRR = (1u << 16);
    GPIOC_BSRR = (1u << 13);
}

int main(void)
{
    LED_Init();

    while (1)
    {
        GPIOB_BSRR = (1u << 0);
        GPIOA_BSRR = (1u << 16);
        GPIOC_BSRR = (1u << 13);
        delay_ms(1000);

        GPIOC_BSRR = (1u << (13 + 16));
        GPIOB_BSRR = (1u << 16);
        GPIOA_BSRR = (1u << 16);
        delay_ms(1000);

        GPIOA_BSRR = (1u << 0);
        GPIOB_BSRR = (1u << 16);
        GPIOC_BSRR = (1u << 13);
        delay_ms(1000);
    }
}
