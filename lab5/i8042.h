#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

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

#endif /* _LCOM_I8042_H */
