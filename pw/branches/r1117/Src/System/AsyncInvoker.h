#ifndef THREADWITHTASK_H_4FF430BA_CE8C_4
#define THREADWITHTASK_H_4FF430BA_CE8C_4

#include "SyncPrimitives.h"
#include "Thread.h"
#include "StarForce/StarForce.h"

namespace threading
{
namespace detail 
{
  // Сохранение результата вызова функции, даже если этот результат void
  template< class T >
  struct ResultStorage
  {
    T t;

    ResultStorage(): t() {}
    ResultStorage(const T &t): t(t) {}
    template<class FncT> void Call( const FncT &fn ) { t = fn(); }
    const T &Result() const { return t; }
  };

  template<>
  struct ResultStorage<void>
  {
    template<class FncT> void Call( const FncT &fn ) { fn(); }
    void Result() const {}
  };  
}
  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Класс предназначен для выполнения произвольных задач в отдельном потоке. 
// Задачей считается код помещённый в оператор вызова функции типа TaskT, вызов которого должен 
// возвращать тип ResultT.
// Класс позволяет обрабатывать только одну задачу одновременно, которая будет выполнена в
// неявно созданном потоке. При попытке добавления новой задачи в процессе выполнения предыдущей
// вызывающий поток будет заблокирован до конца её выполнения. Очередь задач не поддерживается.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
template< class TaskT, class ResultT = void >
class AsyncInvoker: private Thread, private detail::ResultStorage<ResultT>
{
  typedef detail::ResultStorage<ResultT> ResultStorage;
  
public:

  // Конструктор создаёт поток, который будет ожидать поступления задач
  AsyncInvoker(): needStop(false), m_task()
  {
    hCanStartTaskEvent = CreateEvent( 0, FALSE, FALSE, 0 );
    NI_ASSERT( hCanStartTaskEvent != NULL, "" );
    
    hTaskCompleateEvent = CreateEvent( 0, FALSE, FALSE, 0 );
    NI_ASSERT( hTaskCompleateEvent != NULL, "" );
    
    hTaskMutex = CreateMutex( 0, FALSE, 0 );
    NI_ASSERT( hTaskMutex != NULL, "" );
     
    Thread::Resume();
  }
  
  // Деструктор ожидает окончания выполнения задач и завершает поток
  ~AsyncInvoker()
  {
    NI_VERIFY_NO_RET( WaitObject(hTaskMutex), "" );  
    needStop = true;  
    NI_VERIFY_NO_RET( SetEvent(hCanStartTaskEvent), "" );
    NI_VERIFY_NO_RET( ReleaseMutex(hTaskMutex), "" );
     
    NI_VERIFY_NO_RET( Thread::Wait(), "" );     
    NI_VERIFY_NO_RET( CloseHandle(hCanStartTaskEvent), "" );
    NI_VERIFY_NO_RET( CloseHandle(hTaskCompleateEvent), "" );
    NI_VERIFY_NO_RET( CloseHandle(hTaskMutex), "" );
  }
 
  // Запустить выполнение задачи task. Задача будет выполнена в отдельном потоке. 
  // Если в данный момент времени выполняется другая задача, то вызывающий поток 
  // будет заблокирован до конца её выполнения.  
  // Для ожидания выполнения задачи предназначены EndInvoke() и Sync() 
  STARFORCE_FORCE_INLINE void BeginInvoke( const TaskT &task )
  {
    NI_VERIFY_NO_RET( WaitObject(hTaskMutex), "" ); 
     
    // Уже есть задача, которая планируется к выполнения но ещё не выполнена
    if( CheckObject(hCanStartTaskEvent) )
    {
      //Выполним задачу в вызывающем потоке
      ResultStorage::Call(m_task);     
    }
    
    m_task = task; 
      
    NI_VERIFY_NO_RET( SetEvent(hCanStartTaskEvent), "" );
    
    //Сбрасываем событие о завершение предыдущей задачи.
    //Это нужно для того чтобы предотвратить ситуацию, когда при последовательности 
    //вызовов [BeginInvoke, BeginInvoke, EndInvoke] внутренний код EndInvoke получает 
    //управление раньше чем функция потока, и тогда EndInvoke будет завершаться досрочно, 
    //ещё до завершения второго задания. 
    NI_VERIFY_NO_RET( ResetEvent(hTaskCompleateEvent), "" );
    
    NI_VERIFY_NO_RET( ReleaseMutex(hTaskMutex), "" );
  }
  
  // Дождаться выполнения задачи и вернуть её результат.
  // Метод блокирует вызывающий поток до тех пор, пока не завершится 
  // текущая выполняемая задача или, если таковой нет, блокировка будет продолжаться 
  // до тех пор, пока третий поток не добавит такую задачу и она будет выполнена. 
  // После добавления задачи метод можно вызывать только один раз, т.к. повторный вызов приведёт 
  // к блокировке потока и ожиданию новых задач. Т.е. количество вызовов данного метода 
  // должно соответствовать количеству вызовов BeginInvoke(), SyncInvoke() и FakeInvoke()
  STARFORCE_FORCE_INLINE ResultT EndInvoke()
  {
    HANDLE rgSyncObjects[] = { hTaskCompleateEvent, hTaskMutex };

    NI_VERIFY_NO_RET( WaitObjects(rgSyncObjects), "" );
    
    //Нужно скопировать результат, т.к. после освобождения мьютекса 
    //может быть добавлена и выполнена новая задача
    ResultStorage resultCopy(*this);

    NI_VERIFY_NO_RET( ReleaseMutex(hTaskMutex), "" );
  
    return resultCopy.Result();
  }
    
  // Выполнить задачу в вызывающем потоке.
  // Метод схож с BeginInvoke(), за исключением того, что выполняет задачу вызывающий
  // поток. Для получения результата выполнения задачи также нужно вызвать EndInvoke()
  STARFORCE_FORCE_INLINE void SyncInvoke( const TaskT &task )
  {
    NI_VERIFY_NO_RET( WaitObject(hTaskMutex), "" ); 
    
    // Уже есть задача, которая планируется к выполнения но ещё не выполнена
    if( CheckObject(hCanStartTaskEvent) )
    {
      //Выполним задачу в вызывающем потоке
      ResultStorage::Call(m_task);     
    }
     
    m_task = task;   
    ResultStorage::Call(m_task);
        
    NI_VERIFY_NO_RET( SetEvent(hTaskCompleateEvent), "" );
    NI_VERIFY_NO_RET( ReleaseMutex(hTaskMutex), "" );
  }
  
  // Сымитировать выполнение задачи с результатом result.
  // Параметр result должен быть типа ResultT 
  // Данный метод, главным образом, предназначен для возможности последующего 
  // неблокирующего вызова EndInvoke(). Например, это полезно когда некоторая функция 
  // вызывает сначала EndInvoke(), а потом BeginEnvoke(), т.е. сначала обрабатывает результат 
  // выполнения прошлой задачи, и затем формирует новую задачу и отправляет её на выполнение. 
  // Тогда перед первым вызовом такой функции можно вызвать FakeInvoke() и тогда последующий 
  // вызов EndInvoke не будет заблокирован.
  // С другой стороны, если необходимо получить результат выполнения задачи перед
  // основным вызовом EndInvoke() можно воспользоваться следующим трюком:
  //      asyncInvoker.FakeInvoke( asyncInvoker.EndInvoke() );
  // он позволяет с одной стороны завершить выполнение задачи и получить результат, а с другой
  // сделать возможным последующий неблокирующий вызов EndInvoke(). Нужно помнить то, что
  // такой вызов неаттомарен и между вызовом EndInvoke() и FakeInvoke() может вклинится другой 
  // поток, см. также Sync()
  STARFORCE_FORCE_INLINE void FakeInvoke( const ResultStorage &result = ResultStorage() )
  {
    NI_VERIFY_NO_RET( WaitObject(hTaskMutex), "" ); 
    
    // Уже есть задача, которая планируется к выполнения но ещё не выполнена
    if( CheckObject(hCanStartTaskEvent) )
    {
      //Выполним задачу в вызывающем потоке
      ResultStorage::Call(m_task);     
    }
    
    static_cast<ResultStorage &>(*this) = result;   
    NI_VERIFY_NO_RET( SetEvent(hTaskCompleateEvent), "" );
    NI_VERIFY_NO_RET( ReleaseMutex(hTaskMutex), "" );
  }
  
  // Дождаться выполнения задачи, если она существует, а если нет - 
  // просто возвратить управление. 
  // Метод не изменяет внутреннее состояние и не влияет на возможность вызова EndInvoke() и
  // отличается от EndInvoke() тем, что не приводит к зависанию вне зависимости от того 
  // где и сколько раз он вызван.  
  STARFORCE_FORCE_INLINE void Sync()
  {
    NI_VERIFY_NO_RET( WaitObject(hTaskMutex), "" ); 
    
    // Мы захватили мьютекс и значит задача в данный момент не выполняется и  
    // возможны только следующие состояния:  
    // 1. Задача уже выполнена - делать ничего не надо
    // 2. Нет задачи для выполнения - тоже ничего делать не надо 
    // 3. Задача планируется к выполнения но ещё не выполнена - нужно выполнить явно
    
    if( CheckObject(hCanStartTaskEvent) )
    {
      //Выполним задачу в вызывающем потоке
      ResultStorage::Call(m_task);     
      NI_VERIFY_NO_RET( SetEvent(hTaskCompleateEvent), "" ); 
    } 

    NI_VERIFY_NO_RET( ReleaseMutex(hTaskMutex), "" );
  }
  
  // Выполняется ли задача в данный момент и, главное, возможно ли добавить новую задачу без
  // ожидания в вызывающем потоке
  STARFORCE_FORCE_INLINE bool IsBusy() const
  {
    if( !CheckObject(hTaskMutex) )
    {
      //Сейчас мьютекс занят, значит задача выполняется
      return true;
    }
    
    //Мьютекс не занят и задача в данный момент не выполняется, но, возможно,
    //выполнение задачи запланировано и она скоро начнёт выполнение
    bool isBusyResult = false;
    
    if( CheckObject(hCanStartTaskEvent) )
    {
      isBusyResult = true;
      
      //Проверкой CheckObject() Event был сброшен, вернём как было
      NI_VERIFY_NO_RET( SetEvent(hCanStartTaskEvent), "" );
    }
    
    //Проверкой CheckObject() мьютекс был захвачен, вернём как было
    NI_VERIFY_NO_RET( ReleaseMutex(hTaskMutex), "" );
    
    return isBusyResult;
  }
    
  //Установить приоритет потока
  void SetPriority( int priority )
  {
    Thread::SetPriority(priority);  
  }
  
private:
  // Подождать один объект
  STARFORCE_FORCE_INLINE static bool WaitObject( HANDLE hObj )
  {
    return WaitForSingleObject(hObj, INFINITE) == WAIT_OBJECT_0;
  }  
  
  // Подождать несколько объектов
  template< size_t N >
  STARFORCE_FORCE_INLINE static bool WaitObjects( HANDLE (&arr)[N] )
  {
    return WaitForMultipleObjects(N, arr, TRUE, INFINITE) == WAIT_OBJECT_0;
  } 
  
  // Проверить текущее состояние объекта, сохранив, при этом, 
  // все побочные эффекты успешного ожидания
  STARFORCE_FORCE_INLINE static bool CheckObject( HANDLE hObj )
  {
    const DWORD res = WaitForSingleObject(hObj, 0);
    NI_ASSERT( res == WAIT_OBJECT_0 || res == WAIT_TIMEOUT, "" );
    return res == WAIT_OBJECT_0;
  }       

  //Рабочая функция потока
  STARFORCE_EXPORT virtual unsigned Work()
  {
    HANDLE rgSyncObjects[] = { hCanStartTaskEvent, hTaskMutex };
    
    for(;;)
    {
      NI_VERIFY_NO_RET( WaitObjects(rgSyncObjects), "" );
         
      if( needStop )
      {
        NI_VERIFY_NO_RET( ReleaseMutex(hTaskMutex), "" );
        return 0;  
      }
        
      ResultStorage::Call(m_task);     
      
      NI_VERIFY_NO_RET( SetEvent(hTaskCompleateEvent), "" );
      NI_VERIFY_NO_RET( ReleaseMutex(hTaskMutex), "" );
    }
  }

private:
  //Копия задачи, для использования во внутреннем потоке
  TaskT m_task; 
  
  //Мьютекс защищающий внутренние данные
  HANDLE hTaskMutex; 
  
  //Событие: Появилась задача для выполнения
  HANDLE hCanStartTaskEvent;
  
  //Событие: Выполнение задачи завершено. 
  //Понадобилось для предотвращения такой ситуации, когда между вызовами BeginInvoke() и EndInvoke() 
  //проходим слишком мало времени и рабочий поток не успевает захватить hTaskMutex
  HANDLE hTaskCompleateEvent;
  
  //Флаг заставляющий рабочий поток завершится
  bool needStop; 
}; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mock-объект выполняет задачи в вызывающем потоке, но сохраняет интерфейс AsyncInvoker
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class TaskT, class ResultT = void >
class FakeAsyncInvoker: private detail::ResultStorage<ResultT>
{
  typedef detail::ResultStorage<ResultT> ResultStorage;

public:
  FakeAsyncInvoker(): m_task() {}

  void BeginInvoke( const TaskT &task )
  {
    m_task = task;   
    ResultStorage::Call(m_task); 
  }

  ResultT EndInvoke()
  {
    return ResultStorage::Result();
  }
  
  void SyncInvoke( const TaskT &task )
  {
    m_task = task;   
    ResultStorage::Call(m_task);
  }
  
  void FakeInvoke( const ResultStorage &result = ResultStorage() )
  {
    static_cast<ResultStorage &>(*this) = result;   
  }

  void Sync() 
  {
    //Nothing
  }   
  
  bool IsBusy() const
  {
    return true;
  }
  
  void SetPriority( int priority ) 
  {
    (void) priority;
    //Nothing
  }

private:
  TaskT m_task; 
}; 



}

#endif //#define THREADWITHTASK_H_4FF430BA_CE8C_4