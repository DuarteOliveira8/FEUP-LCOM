#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define BIT(n) (0x01<<(n))

#define DELAY_US      20000
#define KBD_IRQ       1
#define ESC           0x81
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

#endif /* _LCOM_I8042_H */
