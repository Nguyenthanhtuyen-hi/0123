#include "stm32f10x.h"

int main(void)
{
    // 1. Bật clock cho Port A và Port C
    RCC->APB2ENR |= (1<<2);  // Bit 2: IOPAEN
    RCC->APB2ENR |= (1<<4);  // Bit 4: IOPCEN

    // 2. Cấu hình PA0 làm Input (Floating)
    GPIOA->CRL &= ~(0xF << (0 * 4));  // Xóa 4 bit cấu hình của PA0
    GPIOA->CRL |=  (0x4 << (0 * 4));  // MODE=00 (Input), CNF=01 (Floating Input)

    // 3. Cấu hình PC13 làm Output (Push-pull)
    GPIOC->CRH &= ~(0xF << ((13 - 8) * 4)); // Xóa cấu hình cũ của PC13
    GPIOC->CRH |=  (0x2 << ((13 - 8) * 4)); // MODE=10 (Output 2MHz), CNF=00 (Push-pull)

    while(1)
    {
        // 4. Đọc trạng thái PA0
        if (GPIOA->IDR & (1<<0))  // Nếu PA0 = 1 (chưa nhấn)
        {
            GPIOC->BSRR = (1<<13);    // Đặt PC13 = 1 (Tắt LED)
        }
        else                       // Nếu PA0 = 0 (nhấn)
        {
            GPIOC->BRR = (1<<13);     // Đặt PC13 = 0 (Bật LED)
        }
    }
}
