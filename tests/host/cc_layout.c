/*
 * Licensed under the GNU General Public License version 2 with exceptions. See
 * LICENSE file in the project root for full license information
 */

#include <stdio.h>
#include <string.h>
#include "esc.h"

int check_osal_first (size_t expected_size, size_t expected_offset);
int check_soes_first (size_t expected_size, size_t expected_offset);

int main (void)
{
   const uint8_t expected16[] = {0x34, 0x12};
   const uint8_t expected32[] = {0x78, 0x56, 0x34, 0x12};
   uint16_t value16 = htoes (0x1234);
   uint32_t value32 = htoel (0x12345678);

   if (memcmp (&value16, expected16, sizeof (value16)) != 0 ||
       memcmp (&value32, expected32, sizeof (value32)) != 0 ||
       etohs (value16) != 0x1234 || etohl (value32) != 0x12345678)
   {
      return 1;
   }

   ESCvar.watchdogcnt = 0x12345678;
   if (check_osal_first (sizeof (_ESCvar), offsetof (_ESCvar, watchdogcnt)) ||
       ESCvar.watchdogcnt != 0x23456789 || ESCvar.SM[3].Mode != 2)
   {
      return 1;
   }
   ESCvar.watchdogcnt = 0x12345678;
   if (check_soes_first (sizeof (_ESCvar), offsetof (_ESCvar, watchdogcnt)) ||
       ESCvar.watchdogcnt != 0x23456789 || ESCvar.SM[3].Mode != 2)
   {
      return 1;
   }

   printf ("SM=%zu MBX=%zu INFO=%zu ESCvar=%zu watchdog=%zu\n",
         sizeof (_ESCsm), sizeof (_MBXh), sizeof (_INFOh),
         sizeof (_ESCvar), offsetof (_ESCvar, watchdogcnt));
   return 0;
}
