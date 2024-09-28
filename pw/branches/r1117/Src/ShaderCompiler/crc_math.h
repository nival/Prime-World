#pragma once

/**
* @brief   Calculate CRC32 value for selected memory block
* @return  CRC 32 value
* @param   pBuf buffer to be calculated
* @param   nLen length of buffer to be calculated
*/
unsigned int CRC32(char const *pBuf, unsigned int nLen);
