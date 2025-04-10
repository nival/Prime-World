#ifndef PSA_CRYPTED_TRAFFIC_HEADER_INCLUDED
#define PSA_CRYPTED_TRAFFIC_HEADER_INCLUDED

// Crypto library - using rsa, rc4 and sha algorithms from it
#include "cryptolib\\cryptolib.asymmetric.h"
#include "cryptolib\\cryptolib.rc4.h"
#include "cryptolib\\cryptolib.sha1.h"
#include "cryptolib\\cryptolib.pkcs1.h"


//Namespace contains implementation of server crypto part
namespace PSA_CryptedTraffic
{
	// RSA key
	struct CryptedTrafficKey
	{
		size_t KeySizeInBytes;			// Size of RSA key (current implementation
										// support only 128-byte or 256-byte keys)
		unsigned char const *Modulus;	// Little-endian, size is KeySizeInBytes
		unsigned char const *Exponent;	// Exponent, little-endian, size is
										// KeySizeInBytes
	};

	class CryptedTrafficException {};
	class InvalidKeySize : public CryptedTrafficException{ };
	class InvalidInitBlockSize : public CryptedTrafficException{ };
	class RsaInitializationFailed : public CryptedTrafficException	{};
	class ShaInitializationFailed : public CryptedTrafficException	{};
	class RsaDecryptionFailed : public CryptedTrafficException	{};

	class CryptedTraffic
	{
		__declspec( align( 8 ) ) RC4_STATE m_rc4Encrypt;
		__declspec( align( 8 ) ) RC4_STATE m_rc4Decrypt;

	public:
		// Constructor (receives initialization block from PSA_CryptedTrafficOpen as argument) and server private key
		CryptedTraffic( BYTE* initBlock, size_t initBlockSize, CryptedTrafficKey* privateKey );

		void Encrypt( BYTE* input, BYTE* output, size_t dataSize );
		void Decrypt( BYTE* input, BYTE* output, size_t dataSize );
	};
}

#endif
