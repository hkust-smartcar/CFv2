#ifndef __QSPI_H
#define __QSPI_H

#include "support_common.h"

typedef enum {QSPI0, QSPI1, QSPI2, QSPI3} QSPI;
typedef enum {Q_MODE0, Q_MODE1, Q_MODE2, Q_MODE3} QSPI_MODE;

void delay(void);
void qspi_init(QSPI qspi, QSPI_MODE mode, uint32_t baudrate);
uint8_t qspi_write(QSPI qspi, uint8_t byte);
uint8_t qspi_write_cmd(QSPI qspi, uint8_t reg, uint8_t cmd);
uint8_t qspi_read_data(QSPI qspi, uint8_t reg);
void qspi_write_nbytes(QSPI qspi, uint8_t reg, uint8_t length, uint8_t * pdata);
void qspi_read_nbytes(QSPI qspi, uint8_t reg, uint8_t length, uint8_t * pdata);

#endif
