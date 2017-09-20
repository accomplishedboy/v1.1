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
/****************************************************************************
 * kernel/clock/clock_systimespec.c
 *
 *   Copyright (C) 2014, 2016 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>

#include <stdint.h>
#include <time.h>
#include <errno.h>

#include <tinyara/arch.h>
#include <tinyara/clock.h>
#include <tinyara/rtc.h>

#ifdef CONFIG_RTC_HIRES
#include <tinyara/rtc.h>
#endif

#include "clock/clock.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: clock_systimespec
 *
 * Description:
 *   Return the current value of the system timer counter as a struct
 *   timespec.  The returned time is the elapsed time since power up.
 *
 * Parameters:
 *   ts - Location to return the time
 *
 * Return Value:
 *   Current version always returns OK
 *
 * Assumptions:
 *
 ****************************************************************************/

int clock_systimespec(FAR struct timespec *ts)
{
#ifdef CONFIG_RTC_HIRES
	/* Do we have a high-resolution RTC that can provide us with the time? */

	if (g_rtc_enabled) {
		/* Get the hi-resolution time from the RTC */

		int ret;

		/* Get the hi-resolution time from the RTC.  This will return the
		 * current time, not the time since power up.
		 */

		ret = up_rtc_gettime(ts);
		if (ret < 0) {
			return ret;
		}

		/* Subtract the base time to this in order to convert this to the
		 * time since power up.
		 */

		DEBUGASSERT(ts->tv_sec >= g_basetime.tv_sec);
		if (ts->tv_sec < g_basetime.tv_sec) {
			/* Negative times are not supported */

			return -ENOSYS;
		}

		ts->tv_sec -= g_basetime.tv_sec;
		if (ts->tv_nsec < g_basetime.tv_nsec) {
			/* Borrow */

			if (ts->tv_sec < 1) {
				/* Negative times are not supported */

				return -ENOSYS;
			}

			ts->tv_sec--;
			ts->tv_nsec += NSEC_PER_SEC;
		}

		ts->tv_nsec -= g_basetime.tv_nsec;
		return OK;

	} else
#endif
	{
#if defined(CONFIG_SCHED_TICKLESS)
		/* In tickless mode, all timing is controlled by platform-specific
		 * code.  Let the platform timer do the work.
		 */

		return up_timer_gettime(ts);

#elif defined(CONFIG_HAVE_LONG_LONG) && (CONFIG_USEC_PER_TICK % 1000) != 0
		/* 64-bit microsecond calculations should improve our accuracy. */

		uint64_t usecs;
		uint64_t secs;
		uint64_t nsecs;

		/* Get the time since power-on in seconds and milliseconds */

		usecs = TICK2MSEC(clock_systimer());
		secs  = usecs / USEC_PER_SEC;

		/* Return the elapsed time in seconds and nanoseconds */

		nsecs = (usecs - (secs * USEC_PER_SEC)) * NSEC_PER_USEC;

		ts->tv_sec  = (time_t)secs;
		ts->tv_nsec = (long)nsecs;
		return OK;

#else
		/* 32-bit millisecond calculations should be just fine. */

		systime_t msecs;
		systime_t secs;
		systime_t nsecs;

		/* Get the time since power-on in seconds and milliseconds */

		msecs = TICK2MSEC(clock_systimer());
		secs  = msecs / MSEC_PER_SEC;

		/* Return the elapsed time in seconds and nanoseconds */

		nsecs = (msecs - (secs * MSEC_PER_SEC)) * NSEC_PER_MSEC;

		ts->tv_sec  = (time_t)secs;
		ts->tv_nsec = (long)nsecs;
		return OK;
#endif
	}
}
