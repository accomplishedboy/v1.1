/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

/// @file environ.c

/// @brief Test Case Example for Environ API

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <tinyara/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <termios.h>

#include <iotbus_uart.h>
#include "utc_internal.h"
#include "iotbus_error.h"

iotbus_uart_context_h uart;

static void utc_uart_initialize_p(void)
{
#ifdef CONFIG_ARCH_CHIP_STM32
	iotbus_uart_context_h m_uart = iotbus_uart_init("/dev/ttyS1");
	TC_ASSERT_NOT_NULL("iotbus_uart_init", m_uart);
	uart = m_uart;
	TC_SUCCESS_RESULT();
#elif CONFIG_ARCH_CHIP_S5J
	iotbus_uart_context_h m_uart = iotbus_uart_init("/dev/ttyS2");
	TC_ASSERT_NOT_NULL("iotbus_uart_init", m_uart);
	uart = m_uart;
	TC_SUCCESS_RESULT();
#endif
}

static void utc_uart_initialize_n(void)
{
	TC_ASSERT_EQ("iotbus_uart_init", iotbus_uart_init(NULL), NULL);
	TC_SUCCESS_RESULT();
}

static void utc_uart_set_baudrate_p(void)
{
	TC_ASSERT_EQ("iotbus_uart_set_baudrate", iotbus_uart_set_baudrate(uart, 115200), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_uart_set_baudrate_n(void)
{
	TC_ASSERT_EQ("iotbus_uart_set_baudrate", iotbus_uart_set_baudrate(uart, 0), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_uart_set_mode_P_IOTBUS_UART_PARITY_NONE(void)
{
	TC_ASSERT_EQ("iotbus_uart_set_mode", iotbus_uart_set_mode(uart, 8, IOTBUS_UART_PARITY_NONE, 1), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_uart_set_mode_p_IOTBUS_UART_PARITY_EVEN(void)
{
	TC_ASSERT_EQ("iotbus_uart_set_mode", iotbus_uart_set_mode(uart, 8, IOTBUS_UART_PARITY_EVEN, 1), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_uart_set_mode_p_IOTBUS_UART_PARITY_ODD(void)
{
	TC_ASSERT_EQ("iotbus_uart_set_mode", iotbus_uart_set_mode(uart, 8, IOTBUS_UART_PARITY_ODD, 1), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_uart_set_mode_n(void)
{
	TC_ASSERT_EQ("iotbus_uart_set_mode", iotbus_uart_set_mode(uart, 8, -1, 1), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_uart_set_flowcontrol_p_START_STOP(void)
{
	TC_ASSERT_EQ("iotbus_uart_set_flowcontrol", iotbus_uart_set_flowcontrol(uart, 1, 0), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_uart_set_flowcontrol_p_RTC_CTC(void)
{
	TC_ASSERT_EQ("iotbus_uart_set_flowcontrol", iotbus_uart_set_flowcontrol(uart, 0, 1), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_uart_set_flowcontrol_n(void)
{
	TC_ASSERT_EQ("iotbus_uart_set_flowcontrol", iotbus_uart_set_flowcontrol(uart, -1, -1), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_uart_write_p(void)
{
	char tbuf[32] = "UART READ/WRITE LoopBack TEST!";
	TC_ASSERT_GT("iotbus_uart_write", iotbus_uart_write(uart, tbuf, sizeof(tbuf)), 0);
	TC_SUCCESS_RESULT();
}

static void utc_uart_write_n(void)
{
	char tbuf[32] = "UART READ/WRITE LoopBack TEST!";
	TC_ASSERT_EQ("iotbus_uart_write", iotbus_uart_write(uart, NULL, sizeof(tbuf)), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_uart_read_p(void)
{
	char rbuf[32];
	TC_ASSERT_GT("iotbus_uart_read", iotbus_uart_read(uart, rbuf, sizeof(rbuf)), 0);
	TC_SUCCESS_RESULT();
}

static void utc_uart_read_n(void)
{
	TC_ASSERT_EQ("iotbus_uart_read", iotbus_uart_read(uart, NULL, 0), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_uart_flush_p(void)
{
	TC_ASSERT_EQ("iotbus_uart_flush", iotbus_uart_flush(uart), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_uart_flush_n(void)
{
	TC_ASSERT_EQ("iotbus_uart_flush", iotbus_uart_flush(NULL), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_uart_stop_p(void)
{
	TC_ASSERT_EQ("iotbus_uart_stop", iotbus_uart_stop(uart), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_uart_stop_n(void)
{
	TC_ASSERT_EQ("iotbus_uart_stop", iotbus_uart_stop(NULL), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

int utc_uart_main(void)
{
	utc_uart_initialize_p();
	utc_uart_initialize_n();
	utc_uart_set_baudrate_p();
	utc_uart_set_baudrate_n();	
	utc_uart_set_mode_P_IOTBUS_UART_PARITY_NONE();
	utc_uart_set_mode_p_IOTBUS_UART_PARITY_EVEN();
	utc_uart_set_mode_p_IOTBUS_UART_PARITY_ODD();
	utc_uart_set_mode_n();
	utc_uart_set_flowcontrol_p_START_STOP();
	utc_uart_set_flowcontrol_p_RTC_CTC();
	utc_uart_set_flowcontrol_n();
	utc_uart_write_p();
	utc_uart_write_n();
	utc_uart_read_p();
	utc_uart_read_n();
	utc_uart_flush_p();
	utc_uart_flush_n();
	utc_uart_stop_n();
	utc_uart_stop_p();

	return 0;
}
