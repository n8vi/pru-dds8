// Copyright (c) 2014 Brad J. Tarratt

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "util.h"
#include "dsb_bin.h"
#include <string.h>


#define IRAM (mypru()+2)

int main (int argc, char **argv)
{
  unsigned char *buf;

  pruinit(&argc, argv, AUXPRU);

  buf = mydram();

  memset(buf, 127, 8192);
    
  printf("starting DSB Modulator on PRU %d\n", mypru());

  prussdrv_pru_disable ( mypru() );
  prussdrv_pru_write_memory(IRAM, 0, (unsigned int *)dsb, sizeof(dsb));
  prussdrv_pru_enable ( mypru() );

  return(0);
}
