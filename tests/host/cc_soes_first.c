/*
 * Licensed under the GNU General Public License version 2 with exceptions. See
 * LICENSE file in the project root for full license information
 */

#include "esc.h"
#include "osal_cc.h"
#include <cc.h>
#include <cc.h>
#include "cc_check.h"

int check_soes_first (size_t expected_size, size_t expected_offset)
{
   return check_layout (expected_size, expected_offset);
}
