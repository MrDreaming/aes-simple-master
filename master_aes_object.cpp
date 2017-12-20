#include "master_aes_object.h"

static StaticLock * m_aes_lock; 
static aec_master::CAesKey m_aes;

void CreateAES(){
        if(m_aes_lock != NULL){
            return;
        }
        m_aes_lock = new StaticLock;
	m_aes.Create(const_cast<unsigned char *>(MasterAesIv), const_cast<unsigned char *>(MasterAesKey));
}

void EncData(unsigned char * pInBuf,unsigned char * pOutBuf,int dlen) {
	m_aes_lock->lockon();
	m_aes.EncReset();
	m_aes.EncData(pInBuf, pOutBuf, dlen);
	m_aes_lock->lockoff();
}

void DecData(unsigned char * pInBuf,unsigned char * pOutBuf,int dlen){
	m_aes_lock->lockon();
	m_aes.DecReset();
	m_aes.DecData(pInBuf, pOutBuf, dlen);
	m_aes_lock->lockoff();
}

