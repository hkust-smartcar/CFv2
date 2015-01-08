/*
 * syscall.c
 *
 *  Created on: Jan 8, 2015
 *      Author: Harrison
 */
#include "uart.h"
#include <ansi_parms.h>


#include "console_io.h"
#include "sys/uart_console_config.h"

#include <ewl_misra_types.h>

int_t __write_console(__file_handle handle, uchar_t * buffer, size_t * count)
{
//#if __dest_os == __starcore
//	#pragma unused(handle,ref_con)
//#else
//	#pragma unused(handle)
//#endif
//	MISRA_QUIET_UNUSED_ARGS()

	/* skip the initialization if this is a TDEV
	** Note there is no OS mask for TDEV or
	** no console IO currently.
	*/
//
//	if (__init_uart_console() != kUARTNoError) {
//		MISRA_EXCEPTION_RULE_14_7()
//		return (int_t)__io_error;
//	}
//
//	if (WriteUARTN(buffer, (uint32_t)*count) != kUARTNoError) {
//		*count = 0u;
//		MISRA_EXCEPTION_RULE_14_7()
//		return (int_t)__io_error;
//	}

	uart_putstr(1,(char*)buffer);
//	return (int_t)__no_io_error;

}
