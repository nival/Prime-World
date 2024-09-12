#pragma once

namespace flash
{
  class SwfStreamReader;
}

namespace jpegreader
{
	// wrapper around jpeg_decompress_struct.

  _interface IInput : public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1( IInput, IBaseInterfaceST )

		virtual void DiscardPartialBuffer() = 0;
		virtual void StartImage() = 0;
		virtual void FinishImage() = 0;

		virtual int	GetHeight() const = 0;
		virtual int	GetWidth() const = 0;
		virtual void ReadScanline( unsigned char* _data ) = 0;
	};

  IInput*	Create( flash::SwfStreamReader * streamReader );
  IInput*	CreateHeaderOnly( flash::SwfStreamReader * streamReader );
};

