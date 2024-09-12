/*
 * DataExecutor.h
 *
 *  Created on: 19.01.2009
 *      Author: earnol
 */

#ifndef BASE64_H_
#define BASE64_H_

class Base64
{
public:
  static void Encode(Stream &instream, Stream &outstream) { Encode(instream, outstream, 0x0FFFFFFF);}
  static void Encode(Stream &instream, Stream &outstream, int linesize);
  static void Decode(Stream &instream, Stream &outstream);

  static nstl::string base64_encode(unsigned char const* , unsigned int len);
  static nstl::string base64_decode(nstl::string const& s);

  static nstl::string base64url_encode(unsigned char const* , unsigned int len);
  static nstl::string base64url_decode(nstl::string const& s);

private:
  static const char cd64[];
  static const char cb64[];
  static void encodeblock(unsigned char in[3], unsigned char out[4], int len);
  static void decodeblock(unsigned char in[4], unsigned char out[3]);
};

#endif /* BASE64_H_ */
