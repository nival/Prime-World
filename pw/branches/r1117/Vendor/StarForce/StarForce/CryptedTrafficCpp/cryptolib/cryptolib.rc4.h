#pragma once

typedef struct _RC4_STATE
{
	unsigned char perm[256];
	unsigned char index1;
	unsigned char index2;
} RC4_STATE, *PRC4_STATE;

EXTERN_C size_t __stdcall rc4_alg_get_size();
EXTERN_C void __stdcall rc4_init(PRC4_STATE state, const unsigned char *key, size_t keylen);
EXTERN_C void __stdcall rc4_crypt(PRC4_STATE state, const unsigned char *inbuf, unsigned char *outbuf, size_t buflen);
