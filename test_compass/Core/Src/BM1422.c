
#include "BM1422.h"


void setBM1422AGMV(int slave_address)
{
  _device_address = slave_address ;
}

uint8_t BM1422AGMVinit(void)
{
  uint8_t rc;
  unsigned char reg;
  unsigned char buf[2];

  _drdy_flg = 0;

  rc = BM1422AGMVread(BM1422AGMV_WIA, &reg, sizeof(reg));
  if (rc != 0) {
//    Serial.println(F("Can't access BM1422AGMV"));
    return (rc);
  }
//  Serial.print(F("BM1422AGMV_WIA Register Value = 0x"));
//  Serial.println(reg, HEX);

  if (reg != BM1422AGMV_WIA_VAL) {
//    Serial.println(F("Can't find BM1422AGMV"));
    return (rc);
  }

  // Step1
  reg = BM1422AGMV_CNTL1_VAL;
  rc = BM1422AGMVwrite(BM1422AGMV_CNTL1, &reg, sizeof(reg));
  if (rc != 0) {
//    Serial.println(F("Can't write BM1422AGMV_CNTL1 Register"));
    return (rc);
  }

  // Check 12bit or 14bit
  buf[0] = (BM1422AGMV_CNTL1_VAL & BM1422AGMV_CNTL1_OUT_BIT);
  if (buf[0] == BM1422AGMV_CNTL1_OUT_BIT) {
    _sens = BM1422AGMV_14BIT_SENS;
  } else {
    _sens = BM1422AGMV_12BIT_SENS;
  }

  HAL_Delay(1);

  buf[0] = (BM1422AGMV_CNTL4_VAL >> 8) & 0xFF;
  buf[1] = (BM1422AGMV_CNTL4_VAL & 0xFF);
  rc = BM1422AGMVwrite(BM1422AGMV_CNTL4, buf, sizeof(buf));
  if (rc != 0) {
//    Serial.println(F("Can't write BM1422AGMV_CNTL4 Register"));
    return (rc);
  }

  // Step2
  reg = BM1422AGMV_CNTL2_VAL;
  rc = BM1422AGMVwrite(BM1422AGMV_CNTL2, &reg, sizeof(reg));
  if (rc != 0) {
//    Serial.println(F("Can't write BM1422AGMV_CNTL2 Register"));
    return (rc);
  }

  // Step3

  // Option
  reg = BM1422AGMV_AVE_A_VAL;
  rc = BM1422AGMVwrite(BM1422AGMV_AVE_A, &reg, sizeof(reg));
  if (rc != 0) {
//    Serial.println(F("Can't write BM1422AGMV_AVE_A Register"));
    return (rc);
  }

  return (rc);
}

uint8_t BM1422AGMVget_rawval(unsigned char *data)
{
  uint8_t rc;
  unsigned char reg;

  // Step4
  reg = BM1422AGMV_CNTL3_VAL;
  rc = BM1422AGMVwrite(BM1422AGMV_CNTL3, &reg, sizeof(reg));
  if (rc != 0) {
//    Serial.println(F("Can't write BM1422AGMV_CNTL3 Register"));
    return (rc);
  }

//  while(_drdy_flg == 0) {
//	  HAL_Delay(100);
//  };
//  _drdy_flg = 0;

  rc = BM1422AGMVread(BM1422AGMV_DATAX, data, 6);
  if (rc != 0) {
//    Serial.println(F("Can't get BM1422AGMV magnet values"));
  }

  return (rc);
}

uint8_t BM1422AGMVget_val(float *data)
{
  uint8_t rc;
  unsigned char val[6];
  signed short mag[3];

  rc = BM1422AGMVget_rawval(val);
  if (rc != 0) {
    return (rc);
  }

  mag[0] = ((signed short)val[1] << 8) | (val[0]);
  mag[1] = ((signed short)val[3] << 8) | (val[2]);
  mag[2] = ((signed short)val[5] << 8) | (val[4]);

  BM1422AGMVconvert_uT(mag, data);

  return (rc);
}

void BM1422AGMVconvert_uT(signed short *rawdata, float *data)
{
  // LSB to uT
  data[0] = (float)rawdata[0] / _sens;
  data[1] = (float)rawdata[1] / _sens;
  data[2] = (float)rawdata[2] / _sens;
}

void BM1422AGMVset_drdy_flg(void)
{
  _drdy_flg = 1;
}

uint8_t BM1422AGMVwrite(unsigned char memory_address, unsigned char *data, unsigned char size)
{
  uint8_t rc;
  rc = HAL_I2C_Mem_Write(&hi2c2, _device_address, memory_address, I2C_MEMADD_SIZE_8BIT, data, size, 500);
//  Wire.beginTransmission(_device_address);
//  Wire.write(memory_address);
//  Wire.write(data, size);
//  rc = Wire.endTransmission();
  return (rc);
}

uint8_t BM1422AGMVread(unsigned char memory_address, unsigned char *data, int size)
{
  uint8_t rc;
  unsigned char cnt;
  rc = HAL_I2C_Mem_Read(&hi2c2, _device_address, memory_address, I2C_MEMADD_SIZE_8BIT, data, size, 500);
//  Wire.beginTransmission(_device_address);
//  Wire.write(memory_address);
//  rc = Wire.endTransmission(false);
//  if (rc != 0) {
//    return (rc);
//  }
//
//  Wire.requestFrom(_device_address, size, true);
//  cnt = 0;
//  while(Wire.available()) {
//    data[cnt] = Wire.read();
//    cnt++;
//  }

  return (rc);
}

void BM1422AGMVisr_func(int int_num, void func(void))
{
//  if (BM1422AGMV_CNTL2_VAL & BM1422AGMV_CNTL2_DRP) {
//    attachInterrupt(int_num, func, RISING);
//  } else {
//    attachInterrupt(int_num, func, FALLING);
//  }
}
