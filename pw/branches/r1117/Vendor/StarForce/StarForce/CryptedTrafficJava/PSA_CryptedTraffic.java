import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

// Crypted traffic cryptor
public class PSA_CryptedTraffic
{
	// Session algorithms
	private Cipher m_rc4Encrypt;
	private Cipher m_rc4Decrypt;
	
	// Constructor (receives initialization block from PSA_CryptedTrafficOpen as argument)
	public PSA_CryptedTraffic( byte[] initBlock, PrivateKey key ) throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException, BadPaddingException, IllegalBlockSizeException, InvalidAlgorithmParameterException
	{
		// Initialize RSA (NOTE: Java Cryptography Extension Unlimited Strength Jurisdiction Policy Files required)
		Cipher rsa = Cipher.getInstance( "RSA/ECB/OAEPWithSha1AndMGF1Padding" );
		rsa.init( Cipher.DECRYPT_MODE, key );

		// Decrypt session key
		byte[] rc4key = rsa.doFinal( initBlock );

		// Initialize encryptors for input and output traffic
		SecretKey sk = new SecretKeySpec( rc4key, "RC4" );
		m_rc4Encrypt = Cipher.getInstance( "RC4" );
		m_rc4Encrypt.init( Cipher.ENCRYPT_MODE, sk );	
		m_rc4Decrypt = Cipher.getInstance( "RC4" );
		m_rc4Decrypt.init( Cipher.DECRYPT_MODE, sk );	
	}
	
	// Encrypt data
	public byte[] Encrypt( byte[] data ) throws BadPaddingException, IllegalBlockSizeException
	{
		return m_rc4Encrypt.update( data );
	}
	
	// Decrypt data
	public byte[] Decrypt( byte[] data ) throws BadPaddingException, IllegalBlockSizeException
	{
		return m_rc4Decrypt.update( data );
	}
}
