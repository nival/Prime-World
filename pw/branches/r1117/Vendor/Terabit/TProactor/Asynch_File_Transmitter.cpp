// Asynch_File_Transmitter.cpp

#include "TProactor/Asynch_File_Transmitter.h"

#if (defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION))
// This only works on platforms with Asynchronous IO

#include "TProactor/Proactor.h"
#include "ace/OS_NS_sys_stat.h"
#include "ace/OS_NS_errno.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// ************************************************************
// TRB_Asynch_File_Transmitter
// ************************************************************
TRB_Asynch_File_Transmitter::TRB_Asynch_File_Transmitter
      (Callback & cb,
       const TRB_Asynch_Transmit_File_Result& original)
  : TRB_Handler ()
  , cb_ (cb)
  , original_ (original)
  , mb_                (original.bytes_per_send ())
  , file_offset_       (0)
  , remain_bytes_      (0)
  , bytes_transferred_ (0)
  , rf_ ()
  , ws_ ()
{
}

TRB_Asynch_File_Transmitter::~TRB_Asynch_File_Transmitter (void)
{
}

TRB_Asynch_Transmit_File_Result &
TRB_Asynch_File_Transmitter::get_original_result ()
{
  return this->original_;
}

int
TRB_Asynch_File_Transmitter::check_params (void)
{
  // Adjust these parameters if there are default values specified.
  this->remain_bytes_ = ACE_OS::filesize (this->original_.file ());

  if (this->remain_bytes_ ==  (size_t)-1)
    ACE_ERROR_RETURN ((LM_ERROR,
        ACE_TEXT("TRB_Asynch_File_Transmitter: filesize failed\n")),
        -1);

  this->file_offset_ = this->original_.offset();

  if (this->file_offset_ > this->remain_bytes_)
    ACE_ERROR_RETURN ((LM_ERROR,
        ACE_TEXT("TRB_Asynch_File_Transmitter: File size is less than offset\n")),
        1);

  this->remain_bytes_ -= this->file_offset_;
  
  size_t bytes_to_write = this->original_.bytes_to_write ();

  if (bytes_to_write != 0 &&
      bytes_to_write < this->remain_bytes_)
    this->remain_bytes_ = bytes_to_write;

  size_t bytes_per_send = this->original_.bytes_per_send();

  if (bytes_per_send == 0)
    bytes_per_send = this->remain_bytes_;
  
  if (bytes_per_send > 16384)
    bytes_per_send = 16384;

  return this->mb_.size (bytes_per_send); 
}

int
TRB_Asynch_File_Transmitter::transmit (void)
{
  if (this->check_params () < 0)
    return -1;
  // Do the transmission.
  // Initiate transmitting the header. When that completes
  // handle_write_stream will be called, there start transmitting the file.
  TRB_Proactor *proactor = this->proactor ();

  if (proactor == 0)
    {
      proactor = original_.get_handler ()->proactor ();
      this->proactor (proactor);

      if (proactor == 0)
        ACE_ERROR_RETURN ((LM_ERROR,
            "TRB_Asynch_File_Transmitter: no proactor given\n"),
             -1);
    }
         

  // Open Asynch_Read_File.
  if (this->rf_.open (*this,
                      this->original_.file (),
                      this->original_.completion_key (),
                      proactor) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "TRB_Asynch_File_Transmitter: read_file open failed\n"),
                      -1);

  // Open Asynch_Write_Stream.
  if (this->ws_.open (*this,
                      this->original_.socket (),
                      this->original_.completion_key (),
                      proactor) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "TRB_Asynch_File_Transmitter: write_stream open failed\n"),
                      -1);

  return this->transmit_header ();
}

void
TRB_Asynch_File_Transmitter::handle_write_stream (const TRB_Asynch_Write_Stream::Result &result)
{
  // Update bytes transferred so far.
  this->bytes_transferred_ += result.bytes_transferred ();

  // Check for error
  u_long error = result.error();
  if (error != 0)
    {
      this->set_completion (error);
    }
  else  // Write stream successful. 
    {
      int unsent_data = result.bytes_to_write () - result.bytes_transferred ();
      if (unsent_data != 0)
        {
          // Partial write to socket. this is ok!!
          // retry remaining data
          if (this->initiate_write_stream (result.message_block (),
                                           unsent_data,
                                           result.act ()) == 0)
            {
              return;  // write started
            }
          // else we have errors and are done
        }
      else
        {
          // Not a partial write. A full write.
          // Check ACT to see what was sent.
          long act = reinterpret_cast<long> (result.act ());
          switch (act)
            {
            case TRAILER_ACT:
              this->set_completion (0); // no errors
              break ;                   // all done

            case HEADER_ACT:
            case DATA_ACT:
              // If header/data was sent, initiate the file data transmission.
              if (initiate_read_file () == 0)
                {
                  return ; // read started
                }
              break;

            default:
              // @@ Handle this error.
              ACE_ERROR ((LM_ERROR,
                  ACE_TEXT("TRB_Asynch_File_Transmitter: Unexpected act\n")));

              this->set_completion (EFAULT);
              break;
            }
        }
    }
  // all done 
  this->cb_.on_complete(*this);
}

void
TRB_Asynch_File_Transmitter::handle_read_file (const TRB_Asynch_Read_File::Result &result)
{
  // Check for error
  u_long error = result.error();
  if (error != 0)
    {
      this->set_completion (error);
    }
  else if (result.bytes_transferred () == 0) 
    {
      // End of File
      if (transmit_trailer () == 0)
        {
          return;  // write started
        }
      // trailer is done OK or with ERRORS, but finished
    }
  else
    {
      // Read successful.
      // Increment offset.
      this->file_offset_  += result.bytes_transferred ();
      this->remain_bytes_ -= result.bytes_transferred ();

      // Write data to network.
      if (this->initiate_write_stream (result.message_block (),
                                   result.bytes_transferred (),
                                   (const void *) DATA_ACT) == 0)
        {
          return;  // write started
        }
    }

  // all is done 
  this->cb_.on_complete(*this);
}

int
TRB_Asynch_File_Transmitter::transmit_header (void)
{
    TRB_Asynch_Transmit_File::Header_And_Trailer * header_and_trailer =
      this->original_.header_and_trailer();

    if (header_and_trailer == 0)
      {
        return this->initiate_read_file ();
      }

    ACE_Message_Block * mb = header_and_trailer->header();
    size_t nbytes = header_and_trailer->header_bytes ();

    if (mb == 0 || nbytes == 0)
      {
        return this->initiate_read_file ();
      }

    return this->initiate_write_stream (*mb,
                                        nbytes,
                                        (const void *) HEADER_ACT);
}

int
TRB_Asynch_File_Transmitter::transmit_trailer (void)
{
    TRB_Asynch_Transmit_File::Header_And_Trailer * header_and_trailer =
        this->original_.header_and_trailer();

    if (header_and_trailer == 0)
      {
        this->set_completion (0);
        return 1;   // done OK
      }

    ACE_Message_Block * mb = header_and_trailer->trailer ();
    size_t nbytes = header_and_trailer->trailer_bytes ();

    if (mb == 0 || nbytes == 0)
      {
        this->set_completion (0);
        return 1;  // done OK
      }

    return this->initiate_write_stream (*mb,
                                        nbytes,
                                        (const void *) TRAILER_ACT);
}


int
TRB_Asynch_File_Transmitter::initiate_write_stream (
                              ACE_Message_Block& mb,
                              size_t             nbytes,
                              const void        *act)
{
  if (this->ws_.write (mb,
                       nbytes,
                       act,
                       this->original_.priority (),
                       this->original_.signal_number ()) == -1)
    {
      // @@ Handle this error.
      u_long error = ACE_OS::last_error ();
      if (error == 0)
        error = EFAULT;

      this->set_completion (error);

      ACE_ERROR_RETURN ((LM_ERROR,
        ACE_TEXT("TRB_Asynch_File_Transmitter: write stream failed\n")),
        -1);
    }

  return 0;
}

int
TRB_Asynch_File_Transmitter::initiate_read_file (void)
{
  size_t bytes_to_read = this->remain_bytes_;

  if (bytes_to_read > this->mb_.size ())
    bytes_to_read = this->mb_.size ();

  // Is there something to read.
  if (bytes_to_read == 0)
    {
      return transmit_trailer (); // File is sent. Send the trailer.
    }

  this->mb_.reset ();
  if (this->rf_.read (this->mb_,
                      bytes_to_read,
                      this->file_offset_,
                      0, // @@ offset_high !!! if aiocb64 is used.
                      0, // Act
                      this->original_.priority (),
                      this->original_.signal_number ()) == -1)
    {
      // @@ Handle this error.
      u_long error = ACE_OS::last_error ();
      if (error == 0)
        error = EFAULT;

      this->set_completion (error);
  
      ACE_ERROR_RETURN ((LM_ERROR,
            ACE_TEXT("TRB_Asynch_File_Transmitter: read file failed\n")),
            -1);
    }
    return 0;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_WIN32 || ACE_HAS_AIO_CALLS */
