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

/// @file clock.c

/// @brief Test Case Example for Clock API

#include <tinyara/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <tinyara/time.h>
#include <sys/time.h>
#include "utc_internal.h"
#include <iotbus_gpio.h>
#include <iotbus_error.h>
#ifdef CONFIG_ARCH_CHIP_STM32
#endif

iotbus_gpio_context_h gpio;
iotbus_gpio_context_h gpio2;

static int gpio_callback_flag = 0;

static int utc_gpio_open2(int gpiopin)
{
	iotbus_gpio_context_h m_gpio = iotbus_gpio_open(gpiopin);
	if (!m_gpio) {
		return 0;
	}
	gpio2 = m_gpio;
	return 1;
}

static void utc_gpio_open_p(void)
{
#ifdef CONFIG_ARCH_CHIP_STM32
	iotbus_gpio_context_h m_gpio = iotbus_gpio_open(GPIO_PORTA_PIN5);
	TC_ASSERT_NOT_NULL("iotbus_gpio_open", m_gpio);
	gpio = m_gpio;
	TC_SUCCESS_RESULT();
#elif CONFIG_ARCH_CHIP_S5J
	iotbus_gpio_context_h m_gpio = iotbus_gpio_open(41);
	TC_ASSERT_NOT_NULL("iotbus_gpio_open", m_gpio);
	gpio = m_gpio;
	TC_SUCCESS_RESULT();
#endif
}

static void utc_gpio_open_n(void)
{
	TC_ASSERT_EQ("iotbus_gpio_open", iotbus_gpio_open(-1), NULL);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_direction_p_IOTBUS_GPIO_DIRECTION_NONE(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_direction", iotbus_gpio_set_direction(gpio, IOTBUS_GPIO_DIRECTION_NONE), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_direction_p_IOTBUS_GPIO_DIRECTION_OUT(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_direction", iotbus_gpio_set_direction(gpio, IOTBUS_GPIO_DIRECTION_OUT), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_direction_p_IOTBUS_GPIO_DIRECTION_IN(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_direction", iotbus_gpio_set_direction(gpio, IOTBUS_GPIO_DIRECTION_IN), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_direction_n(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_direction", iotbus_gpio_set_direction(gpio, -1), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_get_direction_p(void)
{
	iotbus_gpio_direction_e direction;
	iotbus_gpio_get_direction(gpio, &direction);
	TC_ASSERT_EQ("iotbus_gpio_get_direction", direction, IOTBUS_GPIO_DIRECTION_OUT);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_get_direction_n(void)
{
	iotbus_gpio_direction_e direction;
	TC_ASSERT_EQ("iotbus_gpio_get_direction", iotbus_gpio_get_direction(0, &direction), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_edge_mode_p_IOTBUS_GPIO_EDGE_NONE(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_edge_mode", iotbus_gpio_set_edge_mode(gpio, IOTBUS_GPIO_EDGE_NONE), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_edge_mode_p_IOTBUS_GPIO_EDGE_BOTH(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_edge_mode", iotbus_gpio_set_edge_mode(gpio, IOTBUS_GPIO_EDGE_BOTH), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_edge_mode_p_IOTBUS_GPIO_EDGE_RISING(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_edge_mode", iotbus_gpio_set_edge_mode(gpio, IOTBUS_GPIO_EDGE_RISING), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_edge_mode_p_IOTBUS_GPIO_EDGE_FALLING(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_edge_mode", iotbus_gpio_set_edge_mode(gpio, IOTBUS_GPIO_EDGE_FALLING), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_edge_mode_n(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_edge_mode", iotbus_gpio_set_edge_mode(gpio, -1), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_get_edge_mode_p(void)
{
	iotbus_gpio_edge_e edgemode;
	iotbus_gpio_get_edge_mode(gpio, &edgemode);
	TC_ASSERT_EQ("iotbus_gpio_get_edge_mode", edgemode, IOTBUS_GPIO_EDGE_FALLING);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_get_edge_mode_n(void)
{
	iotbus_gpio_edge_e edgemode;
	TC_ASSERT_EQ("iotbus_gpio_get_edge_mode", iotbus_gpio_get_edge_mode(NULL, &edgemode), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_drive_mode_p_IOTBUS_GPIO_DRIVE_NONE(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_drive_mode", iotbus_gpio_set_drive_mode(gpio, IOTBUS_GPIO_DRIVE_NONE), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_drive_mode_p_IOTBUS_GPIO_DRIVE_PULLUP(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_drive_mode", iotbus_gpio_set_drive_mode(gpio, IOTBUS_GPIO_DRIVE_PULLUP), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_drive_mode_p_IOTBUS_GPIO_DRIVE_PULLDOWN(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_drive_mode", iotbus_gpio_set_drive_mode(gpio, IOTBUS_GPIO_DRIVE_PULLDOWN), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_drive_mode_p_IOTBUS_GPIO_DRIVE_FLOAT(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_drive_mode", iotbus_gpio_set_drive_mode(gpio, IOTBUS_GPIO_DRIVE_FLOAT), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_drive_mode_p_IOTBUS_GPIO_DRIVE_PUSHPULL(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_drive_mode", iotbus_gpio_set_drive_mode(gpio, IOTBUS_GPIO_DRIVE_PUSHPULL), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_set_drive_mode_n(void)
{
	TC_ASSERT_EQ("iotbus_gpio_set_drive_mode", iotbus_gpio_set_drive_mode(NULL, -1), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_get_drive_mode_p(void)
{
	iotbus_gpio_drive_e drivemode;
	iotbus_gpio_get_drive_mode(gpio, &drivemode);
	TC_ASSERT_EQ("iotbus_gpio_get_drive_mode", drivemode, IOTBUS_GPIO_DRIVE_PUSHPULL);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_get_drive_mode_n(void)
{
	iotbus_gpio_drive_e drivemode;
	TC_ASSERT_EQ("iotbus_gpio_get_drive_mode", iotbus_gpio_get_drive_mode(NULL, &drivemode), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_write_p(void)
{
	TC_ASSERT_EQ("iotbus_gpio_write", iotbus_gpio_write(gpio, 1), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_write_n(void)
{
	TC_ASSERT_EQ("iotbus_gpio_write", iotbus_gpio_write(NULL, -1), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_read_p(void)
{
	TC_ASSERT_EQ("iotbus_gpio_read", iotbus_gpio_read(gpio2), 1);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_read_n(void)
{
	TC_ASSERT_EQ("iotbus_gpio_read", iotbus_gpio_read(NULL), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_get_pin_p(void)
{
#ifdef CONFIG_ARCH_CHIP_STM32
	TC_ASSERT_EQ("iotbus_gpio_get_pin", iotbus_gpio_get_pin(gpio), GPIO_PORTA_PIN5);
#elif CONFIG_ARCH_CHIP_S5J
	TC_ASSERT_EQ("iotbus_gpio_get_pin", iotbus_gpio_get_pin(gpio), 41);
#endif
	TC_SUCCESS_RESULT();
}

static void utc_gpio_get_pin_n(void)
{
	TC_ASSERT_EQ("iotbus_gpio_get_pin", iotbus_gpio_get_pin(NULL), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

void gpio_callback_event(void *user_data)
{
	iotbus_gpio_context_h hnd = (iotbus_gpio_context_h) user_data;
	int value = iotbus_gpio_read(hnd);
	if (value < 0) {
		gpio_callback_flag = 0;
		return;
	}
	gpio_callback_flag = 1;
	return;
}

static void utc_gpio_register_p(void)
{
	gpio_callback_flag = 0;

	int ret = iotbus_gpio_register_cb(gpio2, IOTBUS_GPIO_EDGE_RISING, gpio_callback_event, (void *)gpio2);
	int data = 0;
	iotbus_gpio_write(gpio, data);
	sleep(1);
	data = 1;
	iotbus_gpio_write(gpio, data);
	sleep(2);

	TC_ASSERT_EQ("iotbus_gpio_register_cb", (ret == IOTBUS_ERROR_NONE && gpio_callback_flag == 1 ? 1 : 0), 1);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_register_n(void)
{
	int ret = iotbus_gpio_register_cb(gpio2, -1, NULL, NULL);

	TC_ASSERT_EQ("iotbus_gpio_register_cb", (ret == IOTBUS_ERROR_INVALID_PARAMETER ? 1 : 0), 1);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_unregister_p(void)
{
	TC_ASSERT_EQ("iotbus_gpio_unregister_cb", iotbus_gpio_unregister_cb(gpio2), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_unregister_n(void)
{
	TC_ASSERT_EQ("iotbus_gpio_unregister_cb", iotbus_gpio_unregister_cb(NULL), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_close_p(void)
{
	TC_ASSERT_EQ("iotbus_gpio_close", iotbus_gpio_close(gpio), IOTBUS_ERROR_NONE);
	TC_SUCCESS_RESULT();
}

static void utc_gpio_close_n(void)
{
	TC_ASSERT_EQ("iotbus_gpio_close", iotbus_gpio_close(NULL), IOTBUS_ERROR_INVALID_PARAMETER);
	TC_SUCCESS_RESULT();
}

int utc_gpio_main(void)
{
	iotapi_initialize();

	utc_gpio_open_p();
	utc_gpio_open_n();

#ifdef CONFIG_ARCH_CHIP_STM32
	utc_gpio_open2(GPIO_PORTA_PIN6);
#elif CONFIG_ARCH_CHIP_S5J
	utc_gpio_open2(57);
#endif

	utc_gpio_set_direction_p_IOTBUS_GPIO_DIRECTION_NONE();
	utc_gpio_set_direction_p_IOTBUS_GPIO_DIRECTION_OUT();
	utc_gpio_set_direction_p_IOTBUS_GPIO_DIRECTION_IN();
	utc_gpio_set_direction_n();

	iotbus_gpio_set_direction(gpio, IOTBUS_GPIO_DIRECTION_OUT);	// for stm
	iotbus_gpio_set_direction(gpio2, IOTBUS_GPIO_DIRECTION_IN);	// for stm

	utc_gpio_get_direction_p();
	utc_gpio_get_direction_n();
	utc_gpio_set_edge_mode_p_IOTBUS_GPIO_EDGE_NONE();
	utc_gpio_set_edge_mode_p_IOTBUS_GPIO_EDGE_BOTH();
	utc_gpio_set_edge_mode_p_IOTBUS_GPIO_EDGE_RISING();
	utc_gpio_set_edge_mode_p_IOTBUS_GPIO_EDGE_FALLING();
	utc_gpio_set_edge_mode_n();
	utc_gpio_get_edge_mode_p();
	utc_gpio_get_edge_mode_n();

	iotbus_gpio_set_direction(gpio, IOTBUS_GPIO_DIRECTION_OUT);	// for stm
	iotbus_gpio_set_direction(gpio2, IOTBUS_GPIO_DIRECTION_IN);	// for stm

	utc_gpio_set_drive_mode_p_IOTBUS_GPIO_DRIVE_NONE();
	utc_gpio_set_drive_mode_p_IOTBUS_GPIO_DRIVE_PULLUP();
	utc_gpio_set_drive_mode_p_IOTBUS_GPIO_DRIVE_PULLDOWN();
	utc_gpio_set_drive_mode_p_IOTBUS_GPIO_DRIVE_FLOAT();
	utc_gpio_set_drive_mode_p_IOTBUS_GPIO_DRIVE_PUSHPULL();
	utc_gpio_set_drive_mode_n();
	utc_gpio_get_drive_mode_p();
	utc_gpio_get_drive_mode_n();
	utc_gpio_write_p();
	utc_gpio_write_n();
	utc_gpio_read_p();
	utc_gpio_read_n();
	utc_gpio_get_pin_p();
	utc_gpio_get_pin_n();
	utc_gpio_register_p();
	utc_gpio_register_n();
	utc_gpio_unregister_p();
	utc_gpio_unregister_n();
	utc_gpio_close_n();
	utc_gpio_close_p();

	return 0;
}
