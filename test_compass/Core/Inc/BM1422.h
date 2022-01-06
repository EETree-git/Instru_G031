/*****************************************************************************
  BM1422AGMV.h

 Copyright (c) 2017 ROHM Co.,Ltd.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
******************************************************************************/
#ifndef _BM1422AGMV_H_
#define _BM1422AGMV_H_
#include "main.h"
#include "i2c.h"
#ifdef __cplusplus

extern "C" {

#endif

#define BM1422AGMV_DEVICE_ADDRESS_0E   (0x0E)    // 7bit Addrss
#define BM1422AGMV_DEVICE_ADDRESS_0F   (0x0F)    // 7bit Address
#define BM1422AGMV_WIA_VAL             (0x41)

#define BM1422AGMV_WIA                 (0x0F)
#define BM1422AGMV_DATAX               (0x10)
#define BM1422AGMV_STA1                (0x18)
#define BM1422AGMV_CNTL1               (0x1B)
#define BM1422AGMV_CNTL2               (0x1C)
#define BM1422AGMV_CNTL3               (0x1D)
#define BM1422AGMV_AVE_A               (0x40)
#define BM1422AGMV_CNTL4               (0x5C)

#define BM1422AGMV_STA1_RD_DRDY        (1 << 6)

#define BM1422AGMV_CNTL1_FS1           (1 << 1)
#define BM1422AGMV_CNTL1_ODR_100Hz      (1 << 3)
#define BM1422AGMV_CNTL1_RST_LV        (1 << 5)
#define BM1422AGMV_CNTL1_OUT_BIT       (1 << 6)
#define BM1422AGMV_CNTL1_PC1           (1 << 7)

#define BM1422AGMV_CNTL2_DRP           (1 << 2)
#define BM1422AGMV_CNTL2_DREN          (1 << 3)

#define BM1422AGMV_CNTL3_FORCE         (1 << 6)

#define BM1422AGMV_AVE_A_AVE4          (0 << 2)

#define BM1422AGMV_CNTL1_VAL           (BM1422AGMV_CNTL1_FS1 | BM1422AGMV_CNTL1_OUT_BIT | BM1422AGMV_CNTL1_PC1)
#define BM1422AGMV_CNTL2_VAL           0//(BM1422AGMV_CNTL2_DREN)
#define BM1422AGMV_CNTL3_VAL           (BM1422AGMV_CNTL3_FORCE)
#define BM1422AGMV_CNTL4_VAL           (0x0000)
#define BM1422AGMV_AVE_A_VAL           (BM1422AGMV_AVE_A_AVE4)

#define BM1422AGMV_14BIT_SENS          (24)
#define BM1422AGMV_12BIT_SENS          (6)


void setBM1422AGMV(int slave_address);
uint8_t BM1422AGMVinit(void) ;
uint8_t BM1422AGMVget_rawval(unsigned char *data);
uint8_t BM1422AGMVget_val(float *data);
void BM1422AGMVconvert_uT(signed short *rawdata, float *data);
void BM1422AGMVset_drdy_flg(void);
uint8_t BM1422AGMVwrite(unsigned char memory_address, unsigned char *data, unsigned char size);
uint8_t BM1422AGMVread(unsigned char memory_address, unsigned char *data, int size);
void BM1422AGMVisr_func(int pin, void func(void));

int _device_address;
unsigned char _sens;
volatile int _drdy_flg;

#ifdef __cplusplus

}

#endif
#endif // _BM1422AGMV_H_
