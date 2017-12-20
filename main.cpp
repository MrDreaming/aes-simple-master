#include <stdio.h>
#include "aeckey.h"
#include "AES.h"
#include "random.h"
#include <stdlib.h>
#include <string.h>
#include "master_aes_object.h"

int main(){
	char sendBuf[32] = {0};
	unsigned char result[32] = {0};
	strcpy(sendBuf, (char*)"12345678901234567890aabbcc");
	int length = strlen(sendBuf);
	//AZLAES * aes = AZLAES::GetAZLAES();
	CreateAES();
	printf("%10s : %s\n", "source", sendBuf);
	//aes->EncData((unsigned char *)sendBuf, strlen(sendBuf));
        EncData((unsigned char *)sendBuf, result, strlen(sendBuf));
        //printf("%10s : %s\n", "encode", (char*)result);
	printf("%10s : ", "encode");
	for(int i=0; i<length; i++){
		printf("%02x ", (unsigned char)result[i]);
		if((i+1)%10==0)
			printf("\n%10s : ", "");
	}
	printf("\n");
        memcpy(sendBuf, result, length);
	//printf("%s\n", sendBuf);
	///


	//AZLAES * aes = AZLAES::GetAZLAES();
	memset(result, 0, sizeof(result));
        //aes->DecData((unsigned char *)sendBuf, result, strlen(sendBuf));
        CreateAES();
	EncData((unsigned char *)sendBuf, result, strlen(sendBuf));
	printf("%10s : %s\n", "decode", (char*)result);

	return 0;
}