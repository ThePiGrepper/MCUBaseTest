#include "stm32f30x.h"

void retarget_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  /*  Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  /* GPRS Port Configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);
  /* USART Configuration */
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;
  USART_Init(USART2, &USART_InitStructure);
  USART_Cmd(USART2, ENABLE);
}

int _write(int fd, char *ptr, int len)
{
  /* Write "len" of char from "ptr" to file id "fd"
   * Return number of char written.
   * Need implementing with UART here.
   */
  //int n;
  /* Write "len" of char from "ptr" to file id "fd"
   * Return number of char written.
   * Need implementing with UART here. */
    int i = 0;
    while (*ptr && (i < len)) {
        //usart_send_blocking(USART6, *ptr);
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);
        USART_SendData(USART2, (uint16_t) *ptr);
        if (*ptr == '\n') {
            //usart_send_blocking(USART6, '\r');
            while (USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);
            USART_SendData(USART2, (uint16_t) '\r');
        }
        i++;
        ptr++;
    }
  return i;
//
//  for (n = 0; n < len; n++) {
//    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);
//    USART_SendData(USART2, (uint16_t) *ptr);
//    ptr++;
//  }
//  return len;
}

int _read(int fd, char *ptr, int len)
{
  /* Read "len" of char to "ptr" from file id "fd"
   * Return number of char read.
   * Need implementing with UART here.
   */
  return len;
}

void _ttywrch(int ch)
{
  /* Write one char "ch" to the default console
   * Need implementing with UART here.
   */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);
  USART_SendData(USART2, (uint16_t) ch);
}

///* SystemInit will be called before main */
//void SystemInit()
//{
//    retarget_init();
//}
