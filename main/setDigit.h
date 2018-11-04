/* Pins for tube digit [0-9] */
#define PIN_A 18
#define PIN_B 19
#define PIN_C 22
#define PIN_D 23

extern void setDigit(int number) 
{
    if (number > 9 || number < 0) return;
    switch(number) {
        case 1:
            gpio_set_level(PIN_A, 1);
            gpio_set_level(PIN_B, 0);
            gpio_set_level(PIN_C, 0);
            gpio_set_level(PIN_D, 0);
            break;
        case 2:
            gpio_set_level(PIN_A, 0);
            gpio_set_level(PIN_B, 1);
            gpio_set_level(PIN_C, 0);
            gpio_set_level(PIN_D, 0);
            break;
        case 3:
            gpio_set_level(PIN_A, 1);
            gpio_set_level(PIN_B, 1);
            gpio_set_level(PIN_C, 0);
            gpio_set_level(PIN_D, 0);
            break;
        case 4:
            gpio_set_level(PIN_A, 0);
            gpio_set_level(PIN_B, 0);
            gpio_set_level(PIN_C, 1);
            gpio_set_level(PIN_D, 0);
            break;
        case 5:
            gpio_set_level(PIN_A, 1);
            gpio_set_level(PIN_B, 0);
            gpio_set_level(PIN_C, 1);
            gpio_set_level(PIN_D, 0);
            break;
        case 6:
            gpio_set_level(PIN_A, 0);
            gpio_set_level(PIN_B, 1);
            gpio_set_level(PIN_C, 1);
            gpio_set_level(PIN_D, 0);
            break;
        case 7:
            gpio_set_level(PIN_A, 1);
            gpio_set_level(PIN_B, 1);
            gpio_set_level(PIN_C, 1);
            gpio_set_level(PIN_D, 0);
            break;
        case 8:
            gpio_set_level(PIN_A, 0);
            gpio_set_level(PIN_B, 0);
            gpio_set_level(PIN_C, 0);
            gpio_set_level(PIN_D, 1);
            break;
        case 9:
            gpio_set_level(PIN_A, 1);
            gpio_set_level(PIN_B, 0);
            gpio_set_level(PIN_C, 0);
            gpio_set_level(PIN_D, 1);
            break;
        case 0:
        default:
            gpio_set_level(PIN_A, 0);
            gpio_set_level(PIN_B, 0);
            gpio_set_level(PIN_C, 0);
            gpio_set_level(PIN_D, 0);
            break;
    }
}