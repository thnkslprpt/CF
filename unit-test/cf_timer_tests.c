/************************************************************************
 * NASA Docket No. GSC-18,447-1, and identified as “CFS CFDP (CF)
 * Application version 3.0.0”
 *
 * Copyright (c) 2019 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/* cf testing includes */
#include "cf_test_utils.h"
#include "cf_timer.h"

/*******************************************************************************
**
**  cf_timer_tests Setup and Teardown
**
*******************************************************************************/

void cf_timer_tests_Setup(void)
{
    cf_tests_Setup();
}

void cf_timer_tests_Teardown(void)
{
    cf_tests_Teardown();
}

/*******************************************************************************
**
**  CF_Timer_Sec2Ticks tests
**
*******************************************************************************/

void Test_CF_Timer_Sec2Ticks_ReturnExpectedValue(void)
{
    /* Arrange */
    CF_Timer_Seconds_t arg_sec          = Any_uint32();
    uint32             ticks_per_second = Any_uint32();
    CF_ConfigTable_t   config_table;

    CF_AppData.config_table                   = &config_table;
    CF_AppData.config_table->ticks_per_second = ticks_per_second;

    /* Act */
    UtAssert_UINT32_EQ(CF_Timer_Sec2Ticks(arg_sec), arg_sec * ticks_per_second);
}

/*******************************************************************************
**
**  CF_Timer_InitRelSec tests
**
*******************************************************************************/

void Test_CF_Timer_InitRelSec_ReceiveExpectedValue(void)
{
    /* Arrange */
    uint32      arg_rel_sec = Any_uint32();
    CF_Timer_t  timer;
    CF_Timer_t *arg_t = &timer;

    /* Arrange unstubbalbe: CF_Timer_Sec2Ticks in same file */
    uint32           ticks_per_second = Any_uint32();
    CF_ConfigTable_t config_table;

    CF_AppData.config_table                   = &config_table;
    CF_AppData.config_table->ticks_per_second = ticks_per_second;

    arg_t->tick = ticks_per_second;

    /* Act */
    CF_Timer_InitRelSec(arg_t, arg_rel_sec);

    /* Assert */
    UtAssert_UINT32_EQ(arg_t->tick, arg_rel_sec * ticks_per_second);
}

/*******************************************************************************
**
**  CF_Timer_Expired tests
**
*******************************************************************************/

void Test_CF_Timer_Expired_When_t_tick_Is_0_Return_1(void)
{
    /* Arrange */
    CF_Timer_t timer;
    timer.tick                        = 0;
    const CF_Timer_t *arg_t           = &timer;
    int               expected_result = 1;

    /* Act */
    UtAssert_INT32_EQ(CF_Timer_Expired(arg_t), expected_result);
}

void Test_CF_Timer_Expired_When_t_tick_Is_1_Return_0(void)
{
    /* Arrange */
    CF_Timer_t timer;
    timer.tick                        = 1;
    const CF_Timer_t *arg_t           = &timer;
    int               expected_result = 0;

    /* Act */
    UtAssert_INT32_EQ(CF_Timer_Expired(arg_t), expected_result);
}

void Test_CF_Timer_Expired_When_t_tick_IsAnyIntegerExcept_0_Return_0(void)
{
    /* Arrange */
    CF_Timer_t timer;
    timer.tick                        = Any_int_Except(0);
    const CF_Timer_t *arg_t           = &timer;
    int               expected_result = 0;

    /* Act */
    UtAssert_INT32_EQ(CF_Timer_Expired(arg_t), expected_result);
}

/*******************************************************************************
**
**  CF_Timer_Tick tests
**
*******************************************************************************/

void Test_CF_Timer_Tick_When_t_tick_Is_non0_Decrement_t_tick(void)
{
    /* Arrange */
    uint32      initial_tick = Any_uint32_Except(0);
    CF_Timer_t  t;
    CF_Timer_t *arg_t = &t;

    arg_t->tick = initial_tick;

    /* Act */
    CF_Timer_Tick(arg_t);

    /* Assert */
    UtAssert_UINT32_EQ(arg_t->tick, initial_tick - 1);
}

/*******************************************************************************
**
**  cf_timer_tests UtTest_Add groups
**
*******************************************************************************/

void add_CF_Timer_Sec2Ticks_tests(void)
{
    UtTest_Add(Test_CF_Timer_Sec2Ticks_ReturnExpectedValue, cf_timer_tests_Setup, cf_timer_tests_Teardown,
               "Test_CF_Timer_Sec2Ticks_ReturnExpectedValue");
}

void add_CF_Timer_InitRelSec_tests(void)
{
    UtTest_Add(Test_CF_Timer_InitRelSec_ReceiveExpectedValue, cf_timer_tests_Setup, cf_timer_tests_Teardown,
               "Test_CF_Timer_InitRelSec_ReceiveExpectedValue");
}

void add_CF_Timer_Expired_tests(void)
{
    UtTest_Add(Test_CF_Timer_Expired_When_t_tick_Is_0_Return_1, cf_timer_tests_Setup, cf_timer_tests_Teardown,
               "Test_CF_Timer_Expired_When_t_tick_Is_0_Return_1");

    UtTest_Add(Test_CF_Timer_Expired_When_t_tick_Is_1_Return_0, cf_timer_tests_Setup, cf_timer_tests_Teardown,
               "Test_CF_Timer_Expired_When_t_tick_Is_1_Return_0");

    UtTest_Add(Test_CF_Timer_Expired_When_t_tick_IsAnyIntegerExcept_0_Return_0, cf_timer_tests_Setup,
               cf_timer_tests_Teardown, "Test_CF_Timer_Expired_When_t_tick_IsAnyIntegerExcept_0_Return_0");
}

void add_CF_Timer_Tick_tests(void)
{
    UtTest_Add(Test_CF_Timer_Tick_When_t_tick_Is_non0_Decrement_t_tick, cf_timer_tests_Setup, cf_timer_tests_Teardown,
               "Test_CF_Timer_Tick_When_t_tick_Is_non0_Decrement_t_tick");
}

/*******************************************************************************
**
**  cf_timer_tests test UtTest_Setup
**
*******************************************************************************/

void UtTest_Setup(void)
{
    TestUtil_InitializeRandomSeed();

    add_CF_Timer_Sec2Ticks_tests();

    add_CF_Timer_InitRelSec_tests();

    add_CF_Timer_Expired_tests();

    add_CF_Timer_Tick_tests();
}