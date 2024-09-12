#include "stdafx.h"
#include "TextureImporter.h"
#include "StringUtils.h"

#include <gcroot.h>
#include <nvtt.h>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace libdb::Diagnostics;

using namespace EditorNative::TextureImporter;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InternalOutputHandler : public nvtt::OutputHandler
{
  gcroot<System::IO::Stream^> outputOptions;

public:
	InternalOutputHandler( System::IO::Stream^ _output ) : outputOptions( _output ) {}

  virtual void beginImage( int size, int width, int height, int depth, int face, int miplevel ) { }

  virtual bool writeData( const void* data, int size )
	{
    array<Byte>^ managedData = gcnew array<Byte>( size );
    System::Runtime::InteropServices::Marshal::Copy( System::IntPtr( const_cast<void*>( data ) ), managedData, 0, size );
    outputOptions->Write( managedData, 0, size );

		return true;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InternalErrorHandler : public nvtt::ErrorHandler
{
  bool hasErrors;

public:
  InternalErrorHandler() : hasErrors( false ) { }

  virtual void error( nvtt::Error e )
  {
    hasErrors = true;
    Log::TraceError( EditorNative::FromMBCS( nvtt::errorString( e ) ) );
  }

  bool HasErrors() const { return hasErrors; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetNormalMap( nvtt::InputOptions& inputOptions )
{
	inputOptions.setNormalMap( true );
	inputOptions.setConvertToNormalMap( false );
	inputOptions.setGamma( 1.0f, 1.0f );
	inputOptions.setNormalizeMipmaps( true );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetColorMap( nvtt::InputOptions& inputOptions )
{
	inputOptions.setNormalMap( false );
	inputOptions.setConvertToNormalMap( false );
	inputOptions.setGamma( 2.2f, 2.2f );
	inputOptions.setNormalizeMipmaps( false );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TextureImporter::Import( System::Drawing::Bitmap^ source, System::IO::Stream^ output, 
                             DBTypes::EPixelFormat format, bool normal, bool noMipmaps, int startMipmapLevel, array<int>^ passes,
                             int fType, float fParam1, float fParam2, float fParam3 )
{
  // represent image like array of bytes
  System::Drawing::Rectangle sourceBounds = System::Drawing::Rectangle( 0, 0, source->Width, source->Height );
  System::Drawing::Imaging::BitmapData^ sourceBitmapData = source->LockBits( sourceBounds, System::Drawing::Imaging::ImageLockMode::ReadOnly, System::Drawing::Imaging::PixelFormat::Format32bppArgb );
  int size = sourceBitmapData->Stride * source->Height;
  array<Byte>^ sourceData = gcnew array<Byte>( size );
  System::Runtime::InteropServices::Marshal::Copy( sourceBitmapData->Scan0, sourceData, 0, size );
  source->UnlockBits( sourceBitmapData );

  // prepare nvtt::InputOptions for nvtt
  pin_ptr<Byte> sourceDataPtr = &sourceData[0];
  nvtt::InputOptions inputOptions;
  inputOptions.setTextureLayout( nvtt::TextureType_2D, source->Width, source->Height );
  inputOptions.setMipmapData( sourceDataPtr, source->Width, source->Height );
  switch( fType )
  {
  case 1: 
    inputOptions.setMipmapFilter( nvtt::MipmapFilter_Triangle ); break;
  case 2: 
    inputOptions.setMipmapFilter( nvtt::MipmapFilter_Kaiser ); break;
  case 3: 
    inputOptions.setMipmapFilter( nvtt::MipmapFilter_Lanczos ); break;
  case 4: 
    inputOptions.setMipmapFilter( nvtt::MipmapFilter_Mitchell ); break;
  case 5: 
    inputOptions.setMipmapFilter( nvtt::MipmapFilter_Sinc ); break;
  default:
    inputOptions.setMipmapFilter( nvtt::MipmapFilter_Box ); break;
  }
  inputOptions.setKaiserParameters( fParam3, fParam1, fParam2 );
  if ( noMipmaps )
    inputOptions.setMipmapGeneration( false );
	else if ( startMipmapLevel > 0 )
		inputOptions.setStartMipmapLevel( startMipmapLevel );
  if ( normal )
    SetNormalMap( inputOptions );
  else
    SetColorMap( inputOptions );
	if ( !ReferenceEquals( passes, nullptr ) )
	{
		pin_ptr<int> passesPtr = &passes[0];
		inputOptions.setPasses((const unsigned int*)passesPtr, passes->Length);
	}

  // prepare nvtt::OutputOptions for nvtt
  InternalOutputHandler outputHandler( output );
  InternalErrorHandler errorHandler;
  nvtt::OutputOptions outputOptions;
	outputOptions.setOutputHandler( &outputHandler );
	outputOptions.setErrorHandler( &errorHandler );

  // prepare nvtt::CompressionOptions for nvtt
	nvtt::CompressionOptions compressionOptions;
  compressionOptions.setQuality(nvtt::Quality_Normal);
  switch( format )
  {
  case DBTypes::EPixelFormat::DXT1:
    compressionOptions.setFormat( nvtt::Format_DXT1 );
    break;
  case DBTypes::EPixelFormat::DXT5:
    compressionOptions.setFormat( nvtt::Format_DXT5 );
    break;
  case DBTypes::EPixelFormat::RGBA:
    compressionOptions.setFormat( nvtt::Format_RGBA );
		//compressionOptions.setLuminance();
    break;
	case DBTypes::EPixelFormat::L8:
    compressionOptions.setFormat( nvtt::Format_RGBA );
		compressionOptions.setLuminance();
    break;
  default:
    compressionOptions.setFormat( nvtt::Format_RGBA );
  }

	nvtt::Compressor compressor;
	compressor.enableCudaAcceleration( true );
  return compressor.process( inputOptions, compressionOptions, outputOptions );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
