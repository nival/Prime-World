/*
* Base64.cpp
*
*  Created on: 19.01.2009
*      Author: earnol
*/
#include "stdafx.h"
#include "Base64.h"
#include <iostream>

//Translation Table as described in RFC1113
const char Base64::cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";
const char Base64::cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const nstl::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static const nstl::string base64url_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789-_";

static inline bool is_base64(unsigned char c) 
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}

static inline bool is_base64url(unsigned char c) 
{
  return (isalnum(c) || (c == '-') || (c == '_'));
}

nstl::string Base64::base64url_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  nstl::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64url_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64url_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

nstl::string Base64::base64url_decode(nstl::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  nstl::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64url(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64url_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64url_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}

nstl::string Base64::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  nstl::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

nstl::string Base64::base64_decode(nstl::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  nstl::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}

void Base64::Encode(Stream &infile, Stream &outfile, int linesize)
{
  unsigned char in[3], out[4];
  int i, len, blocksout = 0;

  while(infile.GetPosition() < infile.GetSize()) 
  {
    len = 0;
    for(i = 0; i < 3; i++ ) 
    {
      if(infile.GetPosition() < infile.GetSize()) 
      {
        infile.Read(&in[i], sizeof(in[i]));
        len++;
      }
      else 
      {
        in[i] = 0;
      }
    }
    if(len > 0) 
    {
      encodeblock(in, out, len);
      outfile.Write(out, sizeof(out));
      blocksout++;
    }
    if(linesize != 0x0FFFFFFF && (blocksout >= (linesize/4) || (infile.GetPosition() >= infile.GetSize())) ) 
    {
      if(blocksout > 0) 
      {
        static char const *pCRLF = "\r\n";
        outfile.Write(pCRLF, strlen(pCRLF));
      }
      blocksout = 0;
    }
  }
}


void Base64::encodeblock(unsigned char in[3], unsigned char out[4], int len)
{
  out[0] = cb64[ in[0] >> 2 ];
  out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
  out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
  out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}

void Base64::decodeblock(unsigned char in[4], unsigned char out[3])
{   
  out[0] = (unsigned char)   ((in[0] << 2 | in[1] >> 4) & 0xFF);
  out[1] = (unsigned char)   ((in[1] << 4 | in[2] >> 2) & 0xFF);
  out[2] = (unsigned char) ((((in[2] << 6) & 0xc0) | in[3]) & 0xFF);
}

void Base64::Decode(Stream &infile, Stream &outfile)
{
  unsigned char in[4], out[3], v;
  int i, len;
  bool  bEOS = false;


  while(infile.GetPosition() < infile.GetSize()) 
  {
    for(len = 0, i = 0; i < 4 && (infile.GetPosition() < infile.GetSize()); i++ ) 
    {
      v = 0;
      while((infile.GetPosition() < infile.GetSize()) && v == 0 ) 
      {
        infile.Read(&v, sizeof(v));
        bEOS = infile.GetPosition() >= infile.GetSize();
        v = (unsigned char) ((v < 43 || v > 122) ? 0 : cd64[v - 43]);
        if(v) 
        {
          v = (unsigned char) ((v == '$') ? 0 : v - 61);
        }
      }
      if(!bEOS) 
      {
        len++;
        if(v) 
        {
          in[i] = (unsigned char) (v - 1);
        }
      }
      else 
      {
        in[i] = 0;
      }
    }
    if(len) 
    {
      decodeblock(in, out);
      for(i = 0; i < len - 1; i++) 
      {
        outfile.Write(&out[i], sizeof(out[i]));
      }
    }
  }
}
