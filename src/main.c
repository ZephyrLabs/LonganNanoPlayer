#include "gd32vf103.h"
#include "fatfs/tf_card.h"
#include "lcd.h"
#include "gfx.h"
#include "led.h"
#include <string.h>

// ------------------------------------------------------------------------
// Framebuffer and other globals.
// ------------------------------------------------------------------------

//uint16_t g_fb[LCD_FRAMEBUFFER_PIXELS]; // LCD Color: RGB565 (MSB rrrrrggggggbbbbb LSB)
unsigned char g_fb[2*LCD_FRAMEBUFFER_PIXELS];
FATFS fs;

void init_uart0(void)
{	
	/* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

    /* connect port to USARTx_Tx */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    /* connect port to USARTx_Rx */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

	/* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200U);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_parity_config(USART0, USART_PM_NONE);
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);

    usart_interrupt_enable(USART0, USART_INT_RBNE);
}

uint16_t bgcolxy(int x, int y)
{
    x -= LCD_WIDTH >> 1;
    y -= LCD_HEIGHT >> 1;
    y <<= 1;
    int r = x*x + y*y;
    return r >> 11;
}

uint16_t bgcol(int p)
{
    int y = p / LCD_WIDTH;
    int x = p - y * LCD_WIDTH;
    return bgcolxy(x, y);
}

int main(void)
{
    uint8_t mount_is_ok = 1; /* 0: mount successful ; 1: mount failed */
    int offset = 0; // pointer offset
    FIL fil;        // pointer to file object
    FRESULT fr;     // FatFS return codes
    UINT br;        // pointer to number of bytes to read

    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1|GPIO_PIN_2);

    init_uart0();
    led_init();
    lcd_init();

    // Clear the framebuffer.
    /*
    for (int i=0; i < LCD_FRAMEBUFFER_PIXELS/2; i++)
        g_fb[i] = bgcol(i);
    */

    fr = f_mount(&fs, "", 1);
    if (fr == 0)
        mount_is_ok = 0;
    else
        mount_is_ok = 1;

    if (mount_is_ok == 0){ // do something here after the file system is mounted

        while(1)
        {
            fr = f_open(&fil, "logo.bin", FA_READ);
            if (fr) printf("open error: %d!\n\r", (int)fr);
            offset = 0;

           fr = f_read(&fil, g_fb, sizeof(g_fb), &br);
                lcd_write_u8(0,0,160, 80, g_fb);

                offset += 51200;
                f_lseek(&fil, offset);
                LEDB_TOG;

            delay_1ms(1500);
            f_close(&fil);

            fr = f_open(&fil, "bmp.bin", FA_READ);
            if (fr) printf("open error: %d!\n\r", (int)fr);
            offset = 0;

            for (int i=0; i<5640;i++)
            {
                fr = f_read(&fil, g_fb, sizeof(g_fb), &br);
                lcd_write_u8(0,0,160, 80, g_fb);
                offset += 51200;
                f_lseek(&fil, offset);
                LEDB_TOG;
                delay_1ms(46);
            }

            /* Close the file */
            f_close(&fil);
        }
    }
    else
    {
        while (1)
        {
            LEDR_TOG;
            delay_1ms(200);
            LEDG_TOG;
            delay_1ms(200);
            LEDB_TOG;
            delay_1ms(200);
        }
    }

}

int _put_char(int ch)
{
    usart_data_transmit(USART0, (uint8_t) ch );
    while ( usart_flag_get(USART0, USART_FLAG_TBE)== RESET){
    }

    return ch;
}
