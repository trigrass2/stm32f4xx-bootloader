/**
 * startup_stm32f4xx.c
 * Código de startup para microcontroladores STM32F4xx
 * Baseado no arquivo "startup_stm32f4xx.s" distribuído pela ST
 * Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

/* start address for the initialization values of the .data section. 
defined in linker script */
extern unsigned long  _etext;
/* start address for the .data section. defined in linker script */  
extern unsigned long  _data;
/* end address for the .data section. defined in linker script */
extern unsigned long  _edata;
/* start address for the .bss section. defined in linker script */
extern unsigned long  _bss;
/* end address for the .bss section. defined in linker script */
extern unsigned long  _ebss;

extern void SystemInit (void);
extern void SysTick_Handler (void);
extern int main (void);
extern void SystemCoreClockUpdate (void);

void Reset_Handler (void) {

    unsigned long *srcPtr, *dstPtr, *bss;
    
    srcPtr = &_etext;
    for (dstPtr = &_data; dstPtr < &_edata; *dstPtr++ = *srcPtr++)
        ;

    // Zera o bss (inicializa as variáveis sem inicialização
    for (bss = &_bss; bss < &_ebss; *bss++ = 0)
        ;

    // Inicia o hardware do sistema
    SystemInit();
	SystemCoreClockUpdate();

    // Branch para o main()
    main();

    // Se retornar do main... o que não deve ocorrer
    while (1)
        ;
}

void NMI_Handler (void) {
    while (1)
        ;
}

void HardFault_Handler (void) {
    while (1)
        ;
}

void IntDefault_Handler (void) {
    while (1)
        ;
}

// Espaço reservado para a stack do microcontrolador
static unsigned long pulStack[128];

// Vetor de interruções
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((unsigned long)pulStack + sizeof(pulStack)),
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    IntDefault_Handler,				// MemManage_Handler
	IntDefault_Handler,				// BusFault_Handler
    IntDefault_Handler,				// UsageFault_Handler
    0,
    0,
    0,
    0,
    IntDefault_Handler,				// SVC_Handler
    IntDefault_Handler,				// DebugMon_Handler
    0,
    IntDefault_Handler,				// PendSV_Handler
    SysTick_Handler,				// SysTick    
    
    // Handlers específicos para o STM32F4xx
    IntDefault_Handler, /* Window WatchDog   */                                        
    IntDefault_Handler, /* PVD through EXTI Line detection */                        
    IntDefault_Handler, /* Tamper and TimeStamps through the EXTI line */            
    IntDefault_Handler, /* RTC Wakeup through the EXTI line */                      
    IntDefault_Handler, /* FLASH */                                          
    IntDefault_Handler, /* RCC */
    IntDefault_Handler, /* EXTI Line0                   */                        
    IntDefault_Handler, /* EXTI Line1                   */                          
    IntDefault_Handler, /* EXTI Line2                   */                          
    IntDefault_Handler, /* EXTI Line3                   */                          
    IntDefault_Handler, /* EXTI Line4                   */                          
    IntDefault_Handler, /* DMA1 Stream 0                */                  
    IntDefault_Handler, /* DMA1 Stream 1                */                   
    IntDefault_Handler, /* DMA1 Stream 2                */                   
    IntDefault_Handler, /* DMA1 Stream 3                */                   
    IntDefault_Handler, /* DMA1 Stream 4                */                   
    IntDefault_Handler, /* DMA1 Stream 5                */                   
    IntDefault_Handler, /* DMA1 Stream 6                */                   
    IntDefault_Handler, /* ADC1, ADC2 and ADC3s         */                   
    IntDefault_Handler, /* CAN1 TX                      */                         
    IntDefault_Handler, /* CAN1 RX0                     */                          
    IntDefault_Handler, /* CAN1 RX1                     */                          
    IntDefault_Handler, /* CAN1 SCE                     */                          
    IntDefault_Handler, /* External Line[9:5]s          */                          
    IntDefault_Handler, /* TIM1 Break and TIM9          */         
    IntDefault_Handler, /* TIM1 Update and TIM10        */         
    IntDefault_Handler, /* TIM1 Trigger and Commutation and TIM11 */
    IntDefault_Handler, /* TIM1 Capture Compare         */                          
    IntDefault_Handler, /* TIM2                         */                   
    IntDefault_Handler, /* TIM3                         */                   
    IntDefault_Handler, /* TIM4                         */                   
    IntDefault_Handler, /* I2C1 Event                   */                          
    IntDefault_Handler, /* I2C1 Error                   */                          
    IntDefault_Handler, /* I2C2 Event                   */                          
    IntDefault_Handler, /* I2C2 Error                   */                            
    IntDefault_Handler, /* SPI1                         */                   
    IntDefault_Handler, /* SPI2                         */                   
    IntDefault_Handler, /* USART1                       */                   
    IntDefault_Handler, /* USART2                       */                   
    IntDefault_Handler, /* USART3                       */                   
    IntDefault_Handler, /* External Line[15:10]s        */                          
    IntDefault_Handler, /* RTC Alarm (A and B) through EXTI Line */                 
    IntDefault_Handler, /* USB OTG FS Wakeup through EXTI line*/
    IntDefault_Handler, /* TIM8 Break and TIM12         */         
    IntDefault_Handler, /* TIM8 Update and TIM13        */         
    IntDefault_Handler, /* TIM8 Trigger and Commutation and TIM14 */
    IntDefault_Handler, /* TIM8 Capture Compare         */                          
    IntDefault_Handler, /* DMA1 Stream7                 */                          
    IntDefault_Handler, /* FSMC                         */                   
    IntDefault_Handler, /* SDIO                         */                   
    IntDefault_Handler, /* TIM5                         */                   
    IntDefault_Handler, /* SPI3                         */                   
    IntDefault_Handler, /* UART4                        */                   
    IntDefault_Handler, /* UART5                        */                   
    IntDefault_Handler, /* TIM6 and DAC1&2 underrun errors */                   
    IntDefault_Handler, /* TIM7                         */
    IntDefault_Handler, /* DMA2 Stream 0                */                   
    IntDefault_Handler, /* DMA2 Stream 1                */                   
    IntDefault_Handler, /* DMA2 Stream 2                */                   
    IntDefault_Handler, /* DMA2 Stream 3                */                   
    IntDefault_Handler, /* DMA2 Stream 4                */                   
    IntDefault_Handler, /* Ethernet                     */                   
    IntDefault_Handler, /* Ethernet Wakeup through EXTI line */                     
    IntDefault_Handler, /* CAN2 TX                      */                          
    IntDefault_Handler, /* CAN2 RX0                     */                          
    IntDefault_Handler, /* CAN2 RX1                     */                          
    IntDefault_Handler, /* CAN2 SCE                     */                          
    IntDefault_Handler, /* USB OTG FS                   */                   
    IntDefault_Handler, /* DMA2 Stream 5                */                   
    IntDefault_Handler, /* DMA2 Stream 6                */                   
    IntDefault_Handler, /* DMA2 Stream 7                */                   
    IntDefault_Handler, /* USART6                       */                    
    IntDefault_Handler, /* I2C3 event                   */                          
    IntDefault_Handler, /* I2C3 error                   */                          
    IntDefault_Handler, /* USB OTG HS End Point 1 Out   */                   
    IntDefault_Handler, /* USB OTG HS End Point 1 In    */                   
    IntDefault_Handler, /* USB OTG HS Wakeup through EXTI */                         
    IntDefault_Handler, /* USB OTG HS                   */                   
    IntDefault_Handler, /* DCMI                         */                   
    IntDefault_Handler, /* CRYP crypto                  */                   
    IntDefault_Handler, /* Hash and Rng                 */
    IntDefault_Handler /* FPU                          */
};

