/*
  Copyright (c) 2020 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifdef __cplusplus

#ifndef _SAFE_RING_BUFFER_
#define _SAFE_RING_BUFFER_

#include "RingBuffer.h"
#include "sync.h"

template <int N>
class SafeRingBufferN : public RingBufferN<N>
{
  public:
    int read_char();
    void store_char(uint16_t c ) ;
};

typedef SafeRingBufferN<SERIAL_BUFFER_SIZE> SafeRingBuffer;

template <int N>
int SafeRingBufferN<N>::read_char() {
  msynchronized {
    return RingBufferN<N>::read_char();
  }

  // We should never reached this line because the synchronized {} block gets
  // executed at least once. However the compiler gets confused and prints a
  // warning about control reaching the end of a non-void function. This
  // silences that warning.
  return -1;
}

template <int N>
void SafeRingBufferN<N>::store_char(uint16_t c) {
  msynchronized {
    RingBufferN<N>::store_char(c);
  }
}

#endif /* _SAFE_RING_BUFFER_ */
#endif /* __cplusplus */
