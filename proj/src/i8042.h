#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

/** @defgroup i8042 i8042
 *
 */

#define BIT(n) (0x01<<(n))

#define DELAY_US      20000
#define KBD_IRQ       1
#define MSB_2BYTES    0xE0
#define STAT_REG      0x64
#define KBC_CMD_REG   0x64
#define OUT_BUF       0x60
#define IN_BUF        0x60
#define IBF           BIT(1)
#define OBF           BIT(0)
#define PAR_ERR       BIT(7)
#define TO_ERR        BIT(6)
#define KBC_CMD_READ  0x20
#define KBC_CMD_WRITE 0x60
#define KBC_COMMAND   0xD4

//keyboard makecodes
#define ESC            0x81
#define AA			   0x1E
#define BB             0x30
#define CC             0x27
#define CCC            0x2E
#define DD             0x20
#define EE             0x12
#define FF             0x21
#define GG             0x22
#define HH             0x23
#define II             0x17
#define JJ             0x24
#define KK             0x25
#define LL             0x26
#define MM             0x32
#define NN             0x31
#define OO             0x18
#define PP             0x19
#define QQ             0x10
#define RR             0x13
#define SS             0x1F
#define TT             0x14
#define UU             0x16
#define VV             0x2F
#define WW             0x11
#define XX             0x2D
#define YY             0x15
#define ZZ             0x2C
#define ZERO           0x0B
#define ONE            0x02
#define TWO            0x03
#define THREE          0x04
#define FOUR           0x05
#define FIVE           0x06
#define SIX            0x07
#define SEVEN          0x08
#define EIGHT          0x09
#define NINE           0x0A
#define SPACE          0x39
#define SPACE_BC       0xB9
#define DELETE         0x0E

//mouse macros
#define MOUSE_IRQ       12
#define MOUSE_CMD_READ  0x20
#define MOUSE_CMD_WRITE 0x60
#define ENABLE_MOUSE    0xA8
#define DISABLE_MOUSE   0xA7
#define CHECK_MOUSE     0xA9
#define ACK             0xFA
#define NACK            0xFE
#define ERROR           0xFC
#define STREAM_MODE     0xEA
#define ENABLE_STREAM   0xF4
#define DISABLE_STREAM  0xF5
#define SET_REMOTE      0xF0
#define READ_DATA       0xEB

//rtc macros
#define RTC_YEAR		9
#define RTC_MONTH		8
#define RTC_DAY 		7
#define RTC_HOURS		4
#define RTC_MINUTES		2
#define RTC_SECONDS		0
#define RTC_REGA		10
#define RTC_REGB		11
#define RTC_ADDRESS		0x70
#define RTC_DATA		0x71
#define RTC_REGA_UIP	BIT(7)
#define RTC_REGB_DM		BIT(2)

/**@}*/

#endif /* _LCOM_I8042_H */
