1. Method
int open (ACE_Handler &handler,
            ACE_HANDLE handle = ACE_INVALID_HANDLE,
            const void *completion_key = 0,
            ACE_Proactor *proactor = 0,
            int pass_ownership = 0);


has new parameter pass_ownership.
The default value is 0 and compatible with old behavior.
If pass_ownership != 0, then internal handler will take 
ownership of the socket/file handle and close the handle
during cancel()/close() or in destructor.


2. Improved cancel() method. If it has been called once,
then Asynch_Stream will never start new AIO on internal 
streams.

3. Minimized context switching and reduced number of post-completions.
If SSL state machine was activated from the internal handler callbacks,
i.e. from 
ACE_SSL_Asynch_Stream::handle_write_stream ()
ACE_SSL_Asynch_Stream::handle_read_stream ()
than we can do upcalls to the external handler directly and
avoid post_completion. 

4. ACE_SSL_Asynch_Stream now can be used in combained 
Proactor/Reactor event loop as the parameter
event was added to the internal  ACE_SSL_Asynch_Result 
    ACE_SSL_Asynch_Result (ACE_Handler & handler, 
                           ACE_HANDLE event);

instead of 
    ACE_SSL_Asynch_Result (ACE_Handler & handler);


5. Significanly improved performance during handshake:
implemented read ahead.

int
ACE_SSL_Asynch_Stream::ssl_bio_read (char * buf,
                                     size_t len,
                                     int & errval)
{
  ...

  if (this->handle_ == ACE_INVALID_HANDLE)
    {
      errval = ERR_CANCELED;
      return -1;
    }

  if (len < 16384)  // !!!!! do read ahead 
    len = 16384;

  ...