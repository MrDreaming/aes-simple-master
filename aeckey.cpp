#include <stdlib.h>
#include <string.h>
#include "aeckey.h"
#include "random.h"

using namespace aec_master;

CAesKey::CAesKey(void){
	aes = NULL;
}

CAesKey::~CAesKey(void){
	if(aes){
		AES_Free(aes);
		aes = NULL;
	}
}
void CAesKey::SetKey(unsigned char * pInitVec,unsigned char * key){
	memcpy(m_InitVec,pInitVec,AES_BLOCK_SIZE);
	memcpy(m_key,key,m_bit/8);
	AES_SetKey(aes, m_key, m_bit);
	EncReset();
	DecReset();
}

bool CAesKey::Create(unsigned char * pInitVec,unsigned char * key,int bit){
	aes = AES_New();
	if (aes == NULL)
		return false;

	if(pInitVec)
		memcpy(m_InitVec,pInitVec,AES_BLOCK_SIZE);
	else
		RAND_bytes(m_InitVec, AES_BLOCK_SIZE);

	if(key)
		memcpy(m_key,key,bit/8);
	else
		RAND_bytes(m_key, bit/8);

	m_bit = bit;

	AES_SetMode(aes, AES_MODE_CTR);
	AES_SetKey(aes, m_key, m_bit);
	EncReset();
	DecReset();
	return true;
}

void CAesKey::GetKey(unsigned char * pInitVec,unsigned char * key){
	memcpy(pInitVec,m_InitVec,AES_BLOCK_SIZE);
	memcpy(key,m_key,m_bit/8);
}

void CAesKey::EncReset(){
	AES_SetEncInitVec(aes, m_InitVec);
}

void CAesKey::DecReset(){
	AES_SetDecInitVec(aes, m_InitVec);
}

void CAesKey::DecData(unsigned char * pInBuf,unsigned char * pOutBuf,int dlen)
{
	AES_DataDecrypt(aes, pInBuf, pOutBuf, dlen);
}
/*
void CAesKey::AesReset(void) {
	AES_SetMode(aes, AES_MODE_CTR);
	AES_SetKey(aes, m_key, 256);
	AES_SetDecInitVec(aes, m_InitVec);
}*/

void CAesKey::EncData(unsigned char * pInBuf,unsigned char * pOutBuf,int dlen){
	AES_SetMode(aes, AES_MODE_CTR);
        AES_SetKey(aes, m_key, 256);
        AES_SetEncInitVec(aes, m_InitVec);
        AES_DataEncrypt(aes, pInBuf, pOutBuf, dlen);
}


