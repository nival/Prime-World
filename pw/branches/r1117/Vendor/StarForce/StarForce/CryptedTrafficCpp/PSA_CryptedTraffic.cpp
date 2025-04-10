#include "PSA_CryptedTraffic.h"

namespace PSA_CryptedTraffic
{
	// Constructor (receives initialization block from PSA_CryptedTrafficOpen as argument) and server private key
	CryptedTraffic::CryptedTraffic( BYTE* initBlock, size_t initBlockSize, CryptedTrafficKey* privateKey )
	{
		// Check rsa key size
		if( privateKey->KeySizeInBytes != 128 && privateKey->KeySizeInBytes != 256 ) throw InvalidKeySize();

		// Check initialization block size
		if( initBlockSize < privateKey->KeySizeInBytes )throw InvalidInitBlockSize();

		// Initialize rsa 
		RSA_ALGORITHM rsaAlg;
		CRYPTOLIB_STATUS  status = rsa_alg_create( &rsaAlg, (SIZE_T)(privateKey->KeySizeInBytes * 8), privateKey->Modulus, 0, privateKey->Exponent, 0, 0, 0, 0, 0 );
		if( status != STATUS_CRYPTOLIB_SUCCESS )throw RsaInitializationFailed();

		PKCS1_RSAES_OAEP_STACK_FRAME stackFrame;
		SHA1_ALGORITHM sha1;
		status = sha1_alg_create( &sha1 );
		if( status != STATUS_CRYPTOLIB_SUCCESS )throw ShaInitializationFailed();

		BYTE sessionKey[SHA1_HASH_SIZE];
		size_t sessionKeySize = 0;

		// Decrypt session key
		status = pkcs1_rsaes_oaep_decrypt( &stackFrame, &rsaAlg, (PHASH_ALGORITHM)&sha1, PKCS1_MGF1_ID, 0, 0, initBlock, &sessionKey[0], (PSIZE_T) &sessionKeySize );
		if( status != STATUS_CRYPTOLIB_SUCCESS )throw RsaDecryptionFailed();

		rsa_alg_delete( &rsaAlg );

		// Initialize encryptors for input and output traffic with session key
		rc4_init( &m_rc4Encrypt, sessionKey, sessionKeySize );
		rc4_init( &m_rc4Decrypt, sessionKey, sessionKeySize );
	}

	void CryptedTraffic::Encrypt( BYTE* input, BYTE* output, size_t dataSize )
	{
		rc4_crypt( &m_rc4Encrypt, input, output, dataSize );
	}

	void CryptedTraffic::Decrypt(  BYTE* input, BYTE* output, size_t dataSize )
	{
		rc4_crypt( &m_rc4Decrypt, input, output, dataSize );
	}
}