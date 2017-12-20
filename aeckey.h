#ifndef _DPLIB_AESKEY_HEADER_
#define _DPLIB_AESKEY_HEADER_
#include "AES.h"
#include <malloc.h>

namespace aec_master{

class CAesKey
{
public:
	CAesKey(void);
	~CAesKey(void);

	bool Create(unsigned char * pInitVec = NULL,unsigned char * key = NULL,int bit = 256);
	void SetKey(unsigned char * pInitVec,unsigned char * key);
	void GetKey(unsigned char * pInitVec,unsigned char * key);
	void EncReset();
	void DecReset();
	void EncData(unsigned char * pInBuf,unsigned char * pOutBuf,int dlen);
	void DecData(unsigned char * pInBuf,unsigned char * pOutBuf,int dlen);
	AES *aes;
	unsigned char m_InitVec[AES_BLOCK_SIZE];  
	unsigned char m_key[32];
	int m_bit;
};
}
#endif
