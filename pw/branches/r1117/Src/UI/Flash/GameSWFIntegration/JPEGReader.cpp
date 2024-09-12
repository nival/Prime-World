#include "TamarinPCH.h"

#include "SwfStreamReader.h"
#include "JPEGReader.h"

#include <Vendor/jpeglib/include/jpeglib.h>

namespace jpegreader
{
	static const int	IO_BUF_SIZE = 4096;

  struct ReadWriteSource : public jpeg_source_mgr
	{
    flash::SwfStreamReader* streamReader; 
		JOCTET	buffer[IO_BUF_SIZE];
    bool startOfFile;


    ReadWriteSource() : streamReader(0) {}

		ReadWriteSource( flash::SwfStreamReader* _streamReader ) :
      streamReader( _streamReader ),
      startOfFile(true)
		{
			init_source = InitSource;
			fill_input_buffer = FillInputBuffer;
			skip_input_data = SkipInputData;
			resync_to_restart = jpeg_resync_to_restart;	// use default method
			term_source = TermSource;

			bytes_in_buffer = 0;
			next_input_byte = NULL;
		}

    static void InitSource( j_decompress_ptr cinfo )
		{
			ReadWriteSource*	src = (ReadWriteSource*) cinfo->src;
			src->startOfFile = true;
		}

		static boolean FillInputBuffer( j_decompress_ptr cinfo )
		{
			ReadWriteSource*	src = (ReadWriteSource*) cinfo->src;

			size_t	bytes_read = src->streamReader->readBuffer( src->buffer, IO_BUF_SIZE );

			if ( bytes_read <= 0 ) 
      {
        NI_ASSERT( !src->startOfFile, "empty jpeg source stream" );

        src->buffer[0] = (JOCTET) 0xFF;
				src->buffer[1] = (JOCTET) JPEG_EOI;

				bytes_read = 2;
			}

			// Hack to work around SWF bug: sometimes data
			// starts with FFD9FFD8, when it should be
			// FFD8FFD9!
			if (src->startOfFile && bytes_read >= 4)
			{
				if (src->buffer[0] == 0xFF
				    && src->buffer[1] == 0xD9 
				    && src->buffer[2] == 0xFF
				    && src->buffer[3] == 0xD8)
				{
					src->buffer[1] = 0xD8;
					src->buffer[3] = 0xD9;
				}
			}

			// Expose buffer state to clients.
			src->next_input_byte = src->buffer;
			src->bytes_in_buffer = bytes_read;
			src->startOfFile = false;

			return TRUE;
		}

		static void	SkipInputData( j_decompress_ptr cinfo, long num_bytes )
		{
			ReadWriteSource*	src = (ReadWriteSource*) cinfo->src;

			// According to jpeg docs, large skips are
			// infrequent.  So let's just do it the simple
			// way.
			if (num_bytes > 0) {
				while (num_bytes > (long) src->bytes_in_buffer) {
					num_bytes -= (long) src->bytes_in_buffer;
					FillInputBuffer(cinfo);
				}
				// Handle remainder.
				src->next_input_byte += (size_t) num_bytes;
				src->bytes_in_buffer -= (size_t) num_bytes;
			}
		}

		static void TermSource( j_decompress_ptr cinfo ) {}

		void	DiscardPartialBuffer()
		{
			bytes_in_buffer = 0;
			next_input_byte = NULL;
		}
	};

	
	//
	// Error handler
	//

	void	JpegErrorExit(j_common_ptr cinfo)
	{
    NI_ALWAYS_ASSERT( "Internal error in jpeglib" );
  }

	//
	// wrappers
	//


	class InputImpl : public IInput, public BaseObjectST
	{
    NI_DECLARE_REFCOUNT_CLASS_2( InputImpl, IInput, BaseObjectST );

  public:

		// State needed for input.
		struct jpeg_decompress_struct	m_cinfo;
		struct jpeg_error_mgr	m_jerr;

		bool	m_compressor_opened;

    ReadWriteSource readWriteSource;

		enum SWF_DEFINE_BITS_JPEG2 { SWF_JPEG2 };
		enum SWF_DEFINE_BITS_JPEG2_HEADER_ONLY { SWF_JPEG2_HEADER_ONLY };

		InputImpl( flash::SwfStreamReader* _streamReader ) :
			m_compressor_opened( false ),
      readWriteSource( _streamReader )
		{
      jpeg_std_error(&m_jerr);
      m_jerr.error_exit = JpegErrorExit;
			m_cinfo.err = &m_jerr;

			// Initialize decompression object.
			jpeg_create_decompress(&m_cinfo);

      m_cinfo.src = &readWriteSource;

			StartImage();
		}

		InputImpl( SWF_DEFINE_BITS_JPEG2_HEADER_ONLY e, flash::SwfStreamReader* _streamReader ) :
			m_compressor_opened(false),
      readWriteSource( _streamReader )
		{
      jpeg_std_error(&m_jerr);
      m_jerr.error_exit = JpegErrorExit;
			m_cinfo.err = &m_jerr;

			// Initialize decompression object.
			jpeg_create_decompress(&m_cinfo);

      m_cinfo.src = &readWriteSource;

			// Read the encoding tables.
			jpeg_read_header(&m_cinfo, FALSE);

			// Don't start reading any image data!
			// App does that manually using start_image.
		}

		~InputImpl()
		// Destructor.  Clean up our jpeg reader state.
		{
			FinishImage();

			m_cinfo.src = NULL;

			jpeg_destroy_decompress(&m_cinfo);
		}

		void	StartImage()
		{
			// Now, read the image header.
			// hack, 202 means that found SOS, ready for start_decompress
			while (m_cinfo.global_state != 202)
			{
				jpeg_read_header(&m_cinfo, FALSE);
			}
			jpeg_start_decompress(&m_cinfo);
			m_compressor_opened = true;
		}

		void	FinishImage()
		{
			if (m_compressor_opened)
			{
				jpeg_finish_decompress(&m_cinfo);
				m_compressor_opened = false;
			}
		}

    int	GetHeight() const { return m_cinfo.output_height; } 

    int	GetWidth() const { return m_cinfo.output_width; }

		int	GetComponents() const { return m_cinfo.output_components; }

    void	DiscardPartialBuffer() { readWriteSource.DiscardPartialBuffer(); }

		void	ReadScanline(unsigned char* rgb_data)
		// Read a scanline's worth of image data into the
		// given buffer.  The amount of data read is
		// get_width() * get_components().
		{
			assert(m_compressor_opened);
			assert(m_cinfo.output_scanline < m_cinfo.output_height);
			int	lines_read = jpeg_read_scanlines(&m_cinfo, &rgb_data, 1);
			assert(lines_read == 1);
			lines_read = lines_read;	// avoid warning in NDEBUG
		}

    private:
      InputImpl() {}
	};


IInput* Create( flash::SwfStreamReader * streamReader )
{
  return new InputImpl( streamReader );
}

IInput* CreateHeaderOnly( flash::SwfStreamReader * streamReader )
{
  return new InputImpl( InputImpl::SWF_JPEG2_HEADER_ONLY, streamReader );
}

}

