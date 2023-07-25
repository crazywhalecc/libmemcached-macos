/*  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 * 
 *  Libmemcached library
 *
 *  Copyright (C) 2011 Data Differential, http://datadifferential.com/
 *  Copyright (C) 2006-2009 Brian Aker All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *      * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *  copyright notice, this list of conditions and the following disclaimer
 *  in the documentation and/or other materials provided with the
 *  distribution.
 *
 *      * The names of its contributors may not be used to endorse or
 *  promote products derived from this software without specific prior
 *  written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "mem_config.h"
#include "libmemcached/byteorder.h"

/* Byte swap a 64-bit number. */
#if !defined(htonll) && !defined(ntohll)
#if __BYTE_ORDER == __LITTLE_ENDIAN
# if defined(__FreeBSD__)
#  include <sys/endian.h>
#  define htonll(x) bswap64(x)
#  define ntohll(x) bswap64(x)
# elif defined(__APPLE__)
#  include <libkern/OSByteOrder.h>
#  define htonll(x) OSSwapInt64(x)
#  define ntohll(x) OSSwapInt64(x)
# elif defined(__OpenBSD__)
#  include <sys/types.h>
#  define htonll(x) swap64(x)
#  define ntohll(x) swap64(x)
# elif defined(__NetBSD__)
#  include <sys/types.h>
#  include <machine/bswap.h>
#  if defined(__BSWAP_RENAME) && !defined(__bswap_32)
#   define htonll(x) bswap64(x)
#   define ntohll(x) bswap64(x)
#  endif
# elif defined(__sun) || defined(sun)
#  include <sys/byteorder.h>
#  define htonll(x) BSWAP_64(x)
#  define ntohll(x) BSWAP_64(x)
# elif defined(_MSC_VER)
#  include <stdlib.h>
#  define htonll(x) _byteswap_uint64(x)
#  define ntohll(x) _byteswap_uint64(x)
# else
#  include <byteswap.h>
#  ifndef bswap_64
   /* Little endian, flip the bytes around until someone makes a faster/better
   * way to do this. */
   static inline uint64_t bswap_64(uint64_t in)
   {
      uint64_t rv= 0;
      for (uint8_t x= 0; x < 8; x++)
      {
        rv= (rv << 8) | (in & 0xff);
        in >>= 8;
      }
      return rv;
   }
#  endif
#  define htonll(x) bswap_64(x)
#  define ntohll(x) bswap_64(x)
# endif
#else
# define htonll(x) (x)
# define ntohll(x) (x)
#endif
#endif

uint64_t memcached_ntohll(uint64_t value)
{
  return ntohll(value);
}

uint64_t memcached_htonll(uint64_t value)
{
  return htonll(value);
}
