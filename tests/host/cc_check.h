/*
 * Licensed under the GNU General Public License version 2 with exceptions. See
 * LICENSE file in the project root for full license information
 */

#include <string.h>

#if defined(EC_LITTLE_ENDIAN) == defined(EC_BIG_ENDIAN)
#error "Exactly one SOES byte order flag must be defined"
#endif

static int check_layout (size_t expected_size, size_t expected_offset)
{
   const uint8_t sm_wire[] = {0x00, 0x10, 0x80, 0x00, 0x76, 0x2b, 0xc3, 0x03};
   const uint8_t mbx_wire[] = {0x20, 0x00, 0x34, 0x12, 0x95, 0xa3};
   const uint8_t info_wire[] = {0x85, 0x00, 0x02, 0x00};
   _ESCsm sm;
   _MBXh mbx;
   _INFOh info;

   if (sizeof (sm) != sizeof (sm_wire) ||
       sizeof (mbx) != sizeof (mbx_wire) ||
       sizeof (info) != sizeof (info_wire) ||
       sizeof (_ESCvar) != expected_size ||
       offsetof (_ESCvar, watchdogcnt) != expected_offset)
   {
      return 1;
   }

   memcpy (&sm, sm_wire, sizeof (sm));
   memcpy (&mbx, mbx_wire, sizeof (mbx));
   memcpy (&info, info_wire, sizeof (info));
   if (sm.Mode != 2 || sm.Direction != 1 || sm.IntECAT != 1 ||
       sm.IntPDI != 1 || sm.WTE != 1 || sm.IntW != 1 || sm.IntR != 1 ||
       sm.MBXstat != 1 || sm.BUFstat != 2 || sm.ECsm != 1 || sm.ECrep != 1 ||
       sm.EClatchEC != 1 || sm.EClatchPDI != 1 || sm.PDIsm != 1 || sm.PDIrep != 1 ||
       mbx.channel != 0x15 || mbx.priority != 2 ||
       mbx.mbxtype != 3 || mbx.mbxcnt != 10 ||
       info.opcode != 5 || info.incomplete != 1)
   {
      return 1;
   }

   /* Exercise accesses to the real global defined in ecat_slv.c. */
   if (ESCvar.watchdogcnt != 0x12345678)
   {
      return 1;
   }
   ESCvar.SM[3] = sm;
   ESCvar.watchdogcnt = 0x23456789;
   return 0;
}
