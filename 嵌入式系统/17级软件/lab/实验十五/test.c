#include "..\INC\config.h"

void Main()
{
    char p;
    Target_Init(); //目标初始化

    while (1)
    {
        switch (key_number)
        {
        case 0:
            send_byte(cmd_test); //测试键
            break;

        case 1:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 2:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 3:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 4:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 5:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 6:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 7:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 8:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 9:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 10:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 11:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 12:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 13:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 14:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        case 15:
            send_byte(0xA1);
            long_delay();
            send_byte(0xC8);
            write7279(decode1 + 5, key_number / 16 * 8);
            write7279(decode1 + 4, key_number & 0x0f);
            break;
        }
        key_number = 0xff;
        Delay(50);
    }
}
