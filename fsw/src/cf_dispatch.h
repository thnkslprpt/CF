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

/**
 * @file
 *
 * The CF Application main application header file
 */

#ifndef CF_DISPATCH_H
#define CF_DISPATCH_H

#include "cfe.h"

/**************************************************************************
 **
 ** Function definitions
 **
 **************************************************************************/

/************************************************************************/
/** @brief Process any ground command contained in the given message.
 *
 * @par Assumptions, External Events, and Notes:
 *       BufPtr must not be NULL.
 *
 * @param BufPtr   Pointer to command message
 */
void CF_ProcessGroundCommand(const CFE_SB_Buffer_t *BufPtr);

/************************************************************************/
/** @brief CF message processing function
 *
 * @par Description
 *       Process message packets received via the Software Bus command pipe
 *
 * @par Assumptions, External Events, and Notes:
 *       BufPtr must not be NULL.
 *
 * @param[in] BufPtr Software Bus message pointer
 *
 */
void CF_AppPipe(const CFE_SB_Buffer_t *BufPtr);

#endif /* !CF_DISPATCH_H */
