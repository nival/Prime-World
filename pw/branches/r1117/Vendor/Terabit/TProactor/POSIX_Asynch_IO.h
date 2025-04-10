/* -*- C++ -*- */
//=============================================================================
/**
 *  @file    POSIX_Asynch_IO.h
 *
 *  POSIX_Asynch_IO.h,v 4.33 2002/11/09 23:51:29 shuston Exp
 *
 *  The implementation classes for POSIX implementation of Asynch
 *  Operations are defined here in this file.
 *
 *  @author Irfan Pyarali <irfan@cs.wustl.edu>
 *  @author Tim Harrison <harrison@cs.wustl.edu>
 *  @author Alexander Babu Arulanthu <alex@cs.wustl.edu>
 *  @author Roger Tragin <r.tragin@computer.org>
 *  @author Alexander Libman <alibman@baltimore.com>
 */
//=============================================================================

#ifndef TRB_POSIX_ASYNCH_IO_H 
#define TRB_POSIX_ASYNCH_IO_H 

#include "ace/pre.h"

#include "TProactor/TPROACTOR_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

#include "TProactor/Asynch_IO_Impl.h"

#if defined (ACE_HAS_AIO_EMULATION)
#  include "TProactor/POSIX_AIO_Emulation.h"
#endif

#if defined(ACE_HAS_LINUX_LIBAIO)
#  include  <libaio.h>    // Linux native aio calls
#endif //ACE_HAS_LINUX_LIBAIO


#if !defined (ACE_HAS_AIO_EMULATION)
#  include "ace/os_include/os_aio.h"
#endif /* ACE_HAS_AIO_EMULATION */

#include "TProactor/Asynch_File_Transmitter.h"
#include "TProactor/Single_List_T.h"
#include "TProactor/Double_List_T.h"
#include "TProactor/Monitor_T.h"
#include "ace/Synch_T.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

class TRB_POSIX_Proactor;
/////////////////////////////////////////////////////////////
/**
 * @class TRB_POSIX_Asynch_Result
 *
 * This class provides concrete implementation for TRB_Asynch_Result
 * for POSIX4 platforms. This class extends @c aiocb and makes it more
 * useful.
 */
class TPROACTOR_Export TRB_POSIX_Asynch_Result :
    public TRB_Asynch_Result_Impl
{
public:

  LinkS_T <TRB_POSIX_Asynch_Result>  * get_link () const;

  // This method will be called by Emulation Providers
  // to execute operation.
  // Return codes:
  //  2 - AIO finished, next operation possible on this fd
  //  1 - AIO finished, next operation may be possible on this fd
  //  0 - not finished
  virtual int execute (void) = 0;

  struct aiocb *get_aiocb(void) { return &this->aio_.aiocb_; }

#if defined(ACE_HAS_LINUX_LIBAIO)
  struct iocb  *get_iocb(void) { return &this->aio_.iocb_; }
#endif

  // fill the embedded aiocb structure based on 
  // original TRB_Asynch_Result
  void build_aiocb (void);

  TRB_POSIX_Proactor      *posix_proactor ()
    {
      return this->posix_proactor_;
    }


protected:

  /// Constructor.
  TRB_POSIX_Asynch_Result (
       ACE_Allocator            *allocator,
       void                     *area,
       const TRB_Asynch_Result&  original,
       TRB_POSIX_Proactor       *posix_proactor);
       
  virtual ~TRB_POSIX_Asynch_Result  ();

  /// TRB_Asynch_Result_Impl methods

  // start implementation must be overriden for each Result
  virtual int start_impl ();
  
  // post implementation is common for all Results
  virtual int post_impl ();

private:
  // prohibit copy and assignment
  TRB_POSIX_Asynch_Result (const TRB_POSIX_Asynch_Result& other);
  TRB_POSIX_Asynch_Result & operator = (const TRB_POSIX_Asynch_Result& other);

  /// link element
  mutable LinkS_T <TRB_POSIX_Asynch_Result> link_;

  
  // Platform specific data
  // aiocb is required for POSIX AIO
  // iocb is required for LINUX AIO
  // both of them are never used by provider
  // BTW, Emulatuion Providers do need these fields at all
  union 
  {
     aiocb aiocb_;

#if defined(ACE_HAS_LINUX_LIBAIO)
     iocb  iocb_;
#endif // ACE_HAS_LINUX_LIBAIO

  } aio_;

  TRB_POSIX_Proactor      *posix_proactor_;
};

/**
 * @class LinkS_Functor_T <TRB_POSIX_Asynch_Result>
 * functor-converter:
 *   input:  address of TRB_POSIX_Asynch_Result
 *   output: address of link field
 */
template <> 
class LinkS_Functor_T <TRB_POSIX_Asynch_Result> : 
    public std::unary_function <TRB_POSIX_Asynch_Result, 
                                LinkS_T <TRB_POSIX_Asynch_Result> > 
{
public :
    LinkS_T <TRB_POSIX_Asynch_Result> * 
    operator () (const  TRB_POSIX_Asynch_Result * x)  const 
    {
        return x->get_link ();
    }
};

class Result2Link 
{
public :
    LinkS_T <TRB_POSIX_Asynch_Result> * 
    operator () (const  TRB_POSIX_Asynch_Result * x)  const 
    {
        return x->get_link ();
    }
};

/**
 * @class TRB_POSIX_Asynch_Result_List
 * @class TRB_POSIX_Asynch_Result_Queue
 */
typedef 
Single_List_T  <TRB_POSIX_Asynch_Result, Result2Link> 
TRB_POSIX_Asynch_Result_List;

typedef 
Single_Queue_T <TRB_POSIX_Asynch_Result, Result2Link> 
TRB_POSIX_Asynch_Result_Queue;



/**
 * @class TRB_POSIX_Asynch_Read_Stream_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Read_Stream::Result class.
 *
 */

class TRB_POSIX_Asynch_Read_Stream_Result :
    public TRB_POSIX_Asynch_Result
{
public:
  typedef TRB_Asynch_Read_Stream_Result User_Result;

  TRB_POSIX_Asynch_Read_Stream_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Read_Stream_Result&  original,
                             TRB_POSIX_Proactor *posix_proactor);
                           
  
  /// Destructor.
  virtual ~TRB_POSIX_Asynch_Read_Stream_Result (void);

  /// Proactor will call this method to execute asynch operation
  virtual int execute ();

  virtual TRB_Asynch_Result & get_original_result ();

private:
  // prohibit copy and assignment
  TRB_POSIX_Asynch_Read_Stream_Result (const TRB_POSIX_Asynch_Read_Stream_Result& other);
  TRB_POSIX_Asynch_Read_Stream_Result & operator = (const TRB_POSIX_Asynch_Read_Stream_Result& other);

  TRB_Asynch_Read_Stream_Result  original_;
};



/**
 * @class TRB_POSIX_Asynch_Write_Stream_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Write_Stream::Result class.
 *
 */

class TRB_POSIX_Asynch_Write_Stream_Result :
  public TRB_POSIX_Asynch_Result
{
public:

  typedef TRB_Asynch_Write_Stream_Result User_Result;

  TRB_POSIX_Asynch_Write_Stream_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Write_Stream_Result&  original,
                             TRB_POSIX_Proactor *posix_proactor);
                           

  /// Destructor.
  virtual ~TRB_POSIX_Asynch_Write_Stream_Result (void);

  /// Proactor will call this method to execute asynch operation
  virtual int execute ();

  virtual TRB_Asynch_Result & get_original_result ();
  
private:
  // prohibit copy and assignment
  TRB_POSIX_Asynch_Write_Stream_Result (const TRB_POSIX_Asynch_Write_Stream_Result& other);
  TRB_POSIX_Asynch_Write_Stream_Result & operator = (const TRB_POSIX_Asynch_Write_Stream_Result& other);

  TRB_Asynch_Write_Stream_Result original_;
};

/**
 * @class TRB_POSIX_Asynch_Read_Dgram_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Read_Dgram::Result class.
 *
 */

class TRB_POSIX_Asynch_Read_Dgram_Result :
    public TRB_POSIX_Asynch_Result
{
public:
  typedef TRB_Asynch_Read_Dgram_Result User_Result;

  TRB_POSIX_Asynch_Read_Dgram_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Read_Dgram_Result&  original,
                             TRB_POSIX_Proactor *posix_proactor);
                         

  /// Destructor.
  virtual ~TRB_POSIX_Asynch_Read_Dgram_Result (void);

  /// Proactor will call this method to execute asynch operation
  virtual int execute ();

  virtual TRB_Asynch_Result & get_original_result ();

private:
  // prohibit copy and assignment
  TRB_POSIX_Asynch_Read_Dgram_Result (const TRB_POSIX_Asynch_Read_Dgram_Result& other);
  TRB_POSIX_Asynch_Read_Dgram_Result & operator = (const TRB_POSIX_Asynch_Read_Dgram_Result& other);
  
  TRB_Asynch_Read_Dgram_Result  original_;
};

/**
 * @class TRB_POSIX_Asynch_Write_Dgram_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Write_Dgram::Result class.
 *
 */

class TRB_POSIX_Asynch_Write_Dgram_Result :
    public TRB_POSIX_Asynch_Result
{
public:
  typedef TRB_Asynch_Write_Dgram_Result User_Result;

  TRB_POSIX_Asynch_Write_Dgram_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Write_Dgram_Result&  original,
                             TRB_POSIX_Proactor *posix_proactor);

                           
  /// Destructor.
  virtual ~TRB_POSIX_Asynch_Write_Dgram_Result (void);

  /// Proactor will call this method to execute asynch operation
  virtual int execute ();

  virtual TRB_Asynch_Result & get_original_result ();

private:
  // prohibit copy and assignment
  TRB_POSIX_Asynch_Write_Dgram_Result (const TRB_POSIX_Asynch_Write_Dgram_Result& other);
  TRB_POSIX_Asynch_Write_Dgram_Result & operator = (const TRB_POSIX_Asynch_Write_Dgram_Result& other);
  
  TRB_Asynch_Write_Dgram_Result original_;
};

/**
 * @class TRB_POSIX_Asynch_Connect_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Connect::Result class.
 *
 */

class TRB_POSIX_Asynch_Connect_Result :
    public TRB_POSIX_Asynch_Result
{
public:
  typedef TRB_Asynch_Connect_Result User_Result;

  TRB_POSIX_Asynch_Connect_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Connect_Result&  original,
                             TRB_POSIX_Proactor *posix_proactor);
                           

  /// Destructor.
  virtual ~TRB_POSIX_Asynch_Connect_Result (void);

  /// Proactor will call this method to execute asynch operation
  virtual int execute ();
  
  virtual TRB_Asynch_Result & get_original_result ();
  
  /// Connect operation specific method.
  /// Initiates connect in non-bloking mode,
  /// therefore, we can wait for completion
  /// return:
  /// 0  - connect started, will complete later
  /// -1 - errors, connect has not been started
  virtual int start_impl ();

private:
  // prohibit copy and assignment
  TRB_POSIX_Asynch_Connect_Result (const TRB_POSIX_Asynch_Connect_Result& other);
  TRB_POSIX_Asynch_Connect_Result & operator = (const TRB_POSIX_Asynch_Connect_Result& other);
  
  TRB_Asynch_Connect_Result original_;
};

/**
 * @class TRB_POSIX_Asynch_Accept_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Accept::Result class.
 *
 */

class TRB_POSIX_Asynch_Accept_Result :
    public TRB_POSIX_Asynch_Result
{
public:
  typedef TRB_Asynch_Accept_Result User_Result;

  
  TRB_POSIX_Asynch_Accept_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Accept_Result&  original,
                             TRB_POSIX_Proactor *posix_proactor);
                           
  /// Destructor.
  virtual ~TRB_POSIX_Asynch_Accept_Result (void);

  /// Proactor will call this method to execute asynch operation
  virtual int execute ();

  virtual TRB_Asynch_Result & get_original_result ();

private:
  // prohibit copy and assignment
  TRB_POSIX_Asynch_Accept_Result (const TRB_POSIX_Asynch_Accept_Result& other);
  TRB_POSIX_Asynch_Accept_Result & operator = (const TRB_POSIX_Asynch_Accept_Result& other);

  TRB_Asynch_Accept_Result original_;
};

/**
 * @class TRB_POSIX_Asynch_Transmit_File_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Transmit_File::Result class.
 *
 */

class TRB_POSIX_Asynch_Transmit_File_Result :
   public TRB_POSIX_Asynch_Result,
   public TRB_Asynch_File_Transmitter::Callback
{
public:
  typedef TRB_Asynch_Transmit_File_Result User_Result;

  TRB_POSIX_Asynch_Transmit_File_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Transmit_File_Result&  original,
                             TRB_POSIX_Proactor *posix_proactor);
                         
  /// Destructor.
  virtual ~TRB_POSIX_Asynch_Transmit_File_Result (void);

  /// Proactor will call this method to execute asynch operation
  virtual int execute ();

  virtual TRB_Asynch_Result & get_original_result ();

  /// Transmit-file operation specific method.
  /// Initiates transmission in non-bloking mode,
  /// therefore, we can wait for completion
  /// return:
  /// 0  - transmit started, will complete later
  /// -1 - errors, transmit has not been started
  virtual int start_impl ();

  /// TRB_Asynch_File_Transmitter::Callback interface 
  virtual void on_complete (TRB_Asynch_File_Transmitter& transmitter);

private:
  // prohibit copy and assignment
  TRB_POSIX_Asynch_Transmit_File_Result (const TRB_POSIX_Asynch_Transmit_File_Result& other);
  TRB_POSIX_Asynch_Transmit_File_Result & operator = (const TRB_POSIX_Asynch_Transmit_File_Result& other);

  TRB_Asynch_File_Transmitter transmitter_;
};

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
template <class RESULT>
class TRB_POSIX_Asynch_Result_T :
  public TRB_POSIX_Asynch_Result
{
public:
  typedef RESULT User_Result;
  
  TRB_POSIX_Asynch_Result_T (ACE_Allocator  *allocator,
                             void           *area,
                             const RESULT &  original,
                             TRB_POSIX_Proactor *posix_proactor)
  : TRB_POSIX_Asynch_Result (allocator, 
                             area,
                             original,
                             posix_proactor)
  , original_               (original)
    {
    }
                             
  /// Destructor.
  virtual ~TRB_POSIX_Asynch_Result_T (void)
    {
    }

  /// Proactor will call this method to execute asynch operation
  virtual int execute ()
    {
       return -1;
    }
  virtual TRB_Asynch_Result & get_original_result ()
    {
      return this->original_;
    }

private:
  // prohibit copy and assignment
  TRB_POSIX_Asynch_Result_T (const TRB_POSIX_Asynch_Result_T<RESULT> & other);
  TRB_POSIX_Asynch_Result_T & operator = (const TRB_POSIX_Asynch_Result_T<RESULT> & other);

  RESULT            original_;
};

typedef 
  TRB_POSIX_Asynch_Result_T<TRB_Asynch_Timer>
  TRB_POSIX_Asynch_Timer;


typedef 
  TRB_POSIX_Asynch_Result_T<TRB_Wakeup_Completion>
  TRB_POSIX_Wakeup_Completion;

typedef 
  TRB_POSIX_Asynch_Result_T<TRB_Asynch_User_Result>
  TRB_POSIX_Asynch_User_Result;

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */

#include "ace/post.h"

#endif //TRB_POSIX_ASYNCH_IO_H 
