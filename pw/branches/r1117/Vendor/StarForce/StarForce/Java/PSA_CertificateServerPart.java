package ServerTest;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.IOException;

import java.security.DigestException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;


// Certificate manager
public class PSA_CertificateServerPart
{
	// Byte array to int and long conversion
	static class ByteMisc
    {
        static public byte[] long2arr( long value )
        {
            byte[] result = new byte[ 8 ];

            result[ 0 ] = ( byte ) value;
            result[ 1 ] = ( byte ) ( value >> 8 );
            result[ 2 ] = ( byte ) ( value >> 8 * 2 );
            result[ 3 ] = ( byte ) ( value >> 8 * 3 );
            result[ 4 ] = ( byte ) ( value >> 8 * 4 );
            result[ 5 ] = ( byte ) ( value >> 8 * 5 );
            result[ 6 ] = ( byte ) ( value >> 8 * 6 );
            result[ 7 ] = ( byte ) ( value >> 8 * 7 );

            return result;
        }
        static public long arr2long( byte[] arr, int offsetInArr )
        {
            if( arr.length - offsetInArr < 8 )
			{
                throw new IllegalArgumentException( "Input array is not enough size" );
			}
            
            long result;
            long mask = 0xFF;

            result = ( long )  arr[ offsetInArr ] & mask;
            result |= (( long ) arr[ offsetInArr + 1 ] & mask ) << 8 ;
            result |= (( long ) arr[ offsetInArr + 2 ] & mask ) << 8 * 2;
            result |= (( long ) arr[ offsetInArr + 3 ] & mask ) << 8 * 3;
            result |= (( long ) arr[ offsetInArr + 4 ] & mask ) << 8 * 4;
            result |= (( long ) arr[ offsetInArr + 5 ] & mask ) << 8 * 5;
            result |= (( long ) arr[ offsetInArr + 6 ] & mask ) << 8 * 6;
            result |= (( long ) arr[ offsetInArr + 7 ] & mask )<< 8 * 7;

            return result;
        }
        static public short arr2short( byte[] arr,  int offsetInArr )
        {
        	if( arr.length - offsetInArr < 2 )
			{
                throw new IllegalArgumentException( "Input array is not enough size" );
			}
        	short result;
        	short mask = 0xFF;
        	
            result = (short) ( ( short )arr[ offsetInArr ] & mask );
            result |= ( ( short ) arr[ offsetInArr + 1 ] & mask ) << 8;
            
            return result;
        }
        static public byte[] short2arr( short value )
        {
        	byte[] result = new byte[2];
        	
            result[ 0 ] = ( byte ) value;
            result[ 1 ] = ( byte ) ( value >> 8 );

            return result;
        }        
    }

	// Certificate
    public class PSA_Certificate
    {
        // Constants
    	static final int CertificateHeaderSize = 18;
        static final int SignatureSize = 16;
        static final int TimeFieldBinarySize = 8;
        
		public long 	m_startTime;
		public long 	m_endTime;        
        // User data
        byte[] 			m_userData;
        public long 	m_signatureLow;
        public long 	m_signatureHigh;

        public int CertificateSize()
        {
        	return CertificateHeaderSize + ExtractUserDataSize() + SignatureSize;
        }
  
		// Extract start time from certificate
        public long ExtractStartTime()
        {
            return m_startTime;
        }

		// Extract end time from certificate
        public long ExtractEndTime()
        {
            return m_endTime;
        }
        
        public short ExtractUserDataSize()
        {
        	if( m_userData == null )return 0;
        	return (short)m_userData.length;        
        }
        
        public byte[] ExtractUserData( )
        {
        	short userDataSize = ExtractUserDataSize();        	
        	byte[] result = null;
        	
        	if( userDataSize != 0)
       		{
        		result = new byte[userDataSize];
       			System.arraycopy( m_userData, 0, result, 0, userDataSize );
       		}
        	return result;        	
        }
        
		// Extract signature from certificate
        public byte[] ExtractSignature()
        {
            byte[] result = new byte[ SignatureSize ];
            System.arraycopy( ByteMisc.long2arr(m_signatureLow), 0, result, 0, TimeFieldBinarySize );
            System.arraycopy( ByteMisc.long2arr(m_signatureHigh), 0, result, TimeFieldBinarySize, TimeFieldBinarySize );
            return result;
        }

        // Certificate as byte array; format of certificate in memory is:
        //   startTime - 8 bytes
        //   endTime   - 8 bytes
        //	 userDataSize - 2 bytes
        //   userData - array of bytes of size userDataSize
        //   signature - 16 bytes
        
        void FromStream( java.io.InputStream dataStream ) throws IOException
        {
        	byte[] valBuffer = new byte[8];
        	dataStream.read( valBuffer, 0, 8 );
        	m_startTime = ByteMisc.arr2long( valBuffer, 0 );
        	
        	dataStream.read(valBuffer, 0, 8 );
        	m_endTime = ByteMisc.arr2long( valBuffer, 0 );
        	
        	dataStream.read(valBuffer, 0, 2 );
        	short userDataSize = ByteMisc.arr2short( valBuffer, 0 );
        	
        	m_userData = new byte[userDataSize];
        	dataStream.read( m_userData );
        	
        	dataStream.read(valBuffer, 0, 8 );
        	m_signatureLow = ByteMisc.arr2long( valBuffer, 0 );
        	
        	dataStream.read(valBuffer, 0, 8 );
        	m_signatureHigh = ByteMisc.arr2long( valBuffer, 0 );
        }
        void ToStream( java.io.OutputStream dataStream) throws IOException
        {
        	dataStream.write(ByteMisc.long2arr( m_startTime ));
        	dataStream.write(ByteMisc.long2arr( m_endTime ));
        	
        	dataStream.write(ByteMisc.short2arr( (short)m_userData.length ));
        	dataStream.write( m_userData );
        	
        	dataStream.write( ByteMisc.long2arr(m_signatureLow));
        	dataStream.write( ByteMisc.long2arr(m_signatureHigh));
        }

		// Constructor (from byte array)
        public PSA_Certificate( byte[] byteArray )
        {       
        	try
        	{
        		FromStream( new ByteArrayInputStream(byteArray));
        	}
        	catch( IOException ioExc )
        	{
                throw new IllegalArgumentException( "Invalid source array size, failed to parse certificate header" );
        	}
        }
       
		// Constructor (from file)
        public PSA_Certificate( String certFileName ) throws IOException
        {
        	try
        	{
        		//Read bytes from source file
        		java.io.FileInputStream certStream = new FileInputStream( certFileName );

        		FromStream( certStream );
           
            	certStream.close();
        	}
        	catch( IOException ioExc )
        	{
        		throw new IllegalArgumentException( "Invalid source array size, failed to read certificate" );
        	}
        }

		// Get certificate as byte array
        public byte[] AsArray()
        {
        	ByteArrayOutputStream byteStream = new ByteArrayOutputStream();

        	try
        	{
        		ToStream( byteStream );
        	}
        	catch (IOException ioExc)//Doubt that it possible with ByteArrayOutputStream 
        	{
        		return null;
        	}

        	return byteStream.toByteArray();
        }
    }

    // Server certificate 
    PSA_Certificate m_cert;

    // Hash provider
    MessageDigest m_hashFunc;

    // Size of hash calculated
    int GetHashSize()
    {
    	return m_hashFunc.getDigestLength();
    }

    // Response is hash and certificate without signature fields 
	// Get size of response
    public int GetResponseSize()
    {
    	return m_cert.CertificateSize() -  PSA_Certificate.SignatureSize + GetHashSize();
    }

	// Initialize hash algorithm
    void InitHash() throws NoSuchAlgorithmException
    {
    	m_hashFunc = MessageDigest.getInstance( "MD5" );
    }    
    
	// Constructor (create certificate from file)
    public PSA_CertificateServerPart( String pathToCert ) throws IOException, NoSuchAlgorithmException
    {
        m_cert = new PSA_Certificate( pathToCert );
        InitHash();
    }

	// Constructor (use created certificate)
    public PSA_CertificateServerPart( PSA_Certificate certToUse ) throws NoSuchAlgorithmException
    {
        if( certToUse == null )
		{
            throw new IllegalArgumentException( "Certificate cannot be null" );
		}
        m_cert = certToUse;
        InitHash();
    }
    
	// Calculate hash
    void CalculateHash( byte[] inBuffer, int inOffset, int inSize, byte[] outHashBuf, int outOffset ) throws DigestException
    {
        m_hashFunc.reset();
        m_hashFunc.update( inBuffer, inOffset, inSize );
        m_hashFunc.digest( outHashBuf, outOffset, outHashBuf.length - outOffset  );
    }

	// Create response to client
    public void CreateResponseToClient( byte[] clientSeed, byte[] responseBuffer, int offset ) throws DigestException 
    {
        if( responseBuffer == null || ( responseBuffer.length - offset ) < GetResponseSize() )
		{
            throw new IllegalArgumentException( "Response buffer size is not valid" );
		}
        
        // Concatenate client seed and certificate, temp buffer contains seed + full certificate
        byte[] temp = new byte[ clientSeed.length + m_cert.CertificateSize() ];
        // Copy client seed to temp buffer
        System.arraycopy( clientSeed, 0, temp, 0, clientSeed.length );
        // Copy certificate to temp buffer, after client seed
        byte[] certAsArray = m_cert.AsArray();
        System.arraycopy( certAsArray, 0, temp, clientSeed.length, certAsArray.length );

        int certSizeWithoutSignature = certAsArray.length - PSA_Certificate.SignatureSize;

        // Copy certificate without signature to response buffer
       	System.arraycopy( certAsArray, 0, responseBuffer, offset, certSizeWithoutSignature );        
        
       	// Calculate  hash on seed + full certificate and copy it to position of hash in response buffer
       	CalculateHash( temp, 0, temp.length, responseBuffer, offset + certSizeWithoutSignature );
     }
}
