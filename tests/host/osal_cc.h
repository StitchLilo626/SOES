/*
 * Licensed under the GNU General Public License version 2 with exceptions. See
 * LICENSE file in the project root for full license information
 */

/* Minimal stand-in for the shared compiler macros supplied by OSAL.
 * Deliberately use CC_H and omit SOES's EC_*_ENDIAN flags, as OSAL does.
 * Keep the regression self-contained; no OSAL checkout or hardware is needed.
 */
#ifndef CC_H
#define CC_H

#define CC_PACKED_BEGIN
#define CC_PACKED_END
#define CC_PACKED __attribute__ ((packed))
#define CC_ALIGNED(n) __attribute__((aligned (n)))

#endif /* CC_H */
