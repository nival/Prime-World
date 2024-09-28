#include "defines.h"
#include "cryptolib.rc4.h"

static __inline void swap_bytes(unsigned char *a, unsigned char *b)
{
	unsigned char temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

EXTERN_C size_t __stdcall rc4_alg_get_size()
{
	return sizeof(RC4_STATE);
}

EXTERN_C void __stdcall rc4_init(PRC4_STATE state, const unsigned char *key, size_t keylen)
{
	unsigned char j;
	int i;

	for (i = 0; i < 256; i++) {
		state->perm[i] = (unsigned char)i; 
	}

	state->index1 = 0;
	state->index2 = 0;
  
	for (j = 0, i = 0; i < 256; i++) {
		j += state->perm[i] + key[i % keylen]; 
		swap_bytes(&state->perm[i], &state->perm[j]);
	}
}

EXTERN_C void __stdcall rc4_crypt(PRC4_STATE state, const unsigned char *inbuf, unsigned char *outbuf, size_t buflen)
{
	size_t i;
	unsigned char j;

	for (i = 0; i < buflen; i++) 
	{
    	state->index1++;
		state->index2 = (unsigned char)(state->index2  + state->perm[state->index1]);

		swap_bytes(&state->perm[state->index1],
		    &state->perm[state->index2]);

		j = state->perm[state->index1] + state->perm[state->index2];
		outbuf[i] = inbuf[i] ^ state->perm[j];
	}
}
