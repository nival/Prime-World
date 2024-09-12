using System;
using System.Collections.Generic;
using System.Text;

namespace River.Core
{
  /// <summary>
  /// Common part of the context, lives on the master, accessed remotely
  /// </summary>
  public interface ISyncContext
	{
		/// <summary>
		/// Returns list of bots where runned specified test
		/// </summary>
		/// <param name="type">Type of test</param>
		/// <returns>Descriptions of bots, empty array is specified test not running</returns>
		/// <exception cref="System.ArgumentNullException">If type is null</exception>
		/// <exception cref="System.ArgumentException">If type is not derived from ITest</exception>
    BotDescription[] GetBotsWithTest( string type );

		/// <summary>
		/// Incerement value of specified variable
    /// New variables start with value of 0
    /// </summary>
		/// <param name="var">Name of variable to increment</param>
		/// <exception cref="System.ArgumentNullException">If name is null</exception>
		/// <exception cref="System.ArgumentException">If name is not valid variable name</exception>
    void SyncInc( string name );

		/// <summary>
		/// Decrement value of specified variable
    /// New variables start with value of 0
    /// </summary>
		/// <param name="var">Name of variable to decrement</param>
		/// <exception cref="System.ArgumentNullException">If name is null</exception>
		/// <exception cref="System.ArgumentException">If name is not valid variable name</exception>
    void SyncDec( string name );

		/// <summary>
		/// Wait for specified value for variable
		/// </summary>
		/// <param name="name">Name of variable for checking</param>
		/// <param name="value">Value of variable to wait</param>
		/// <param name="timeout">Specify timeout for waiting. Use TimeOut.Zero to just check variable value. Use TimeOut.MaxValue to wait infinitly</param>
		/// <returns>Returns true if variable has specified value or false if function terminated due timeout</returns>
		/// <exception cref="System.ArgumentNullException">If name is null</exception>
		/// <exception cref="System.ArgumentException">If name is not valid variable name</exception>
    bool SyncWait( string name, int value, TimeSpan timeout );

		/// <summary>
		/// Informs about progress during current task (install or execute)
		/// </summary>
		/// <param name="progress">Progress value (0-100). Use negative value to indicate that progress not changed</param>
		/// <param name="message">Message to inform</param>
    void Progress( int progress, string message );

    /// <summary>
    /// выложить локальный файл на сервер, как результат работы сценария 
    /// </summary>
    /// <param name="filePath">имя файла (relative)</param>
    /// <param name="fileData">сам файл</param>
    void PutFile( BotDescription bot, string filePath, byte[] fileData );
  }

  /// <summary>
  /// Local instance of the context, passed to the scenario, delegates all calls to SyncContext remotely
  /// </summary>
  public interface IContext
  {
    /// <summary>
    /// Returns list of bots where runned specified test
    /// </summary>
    /// <param name="type">Type of test</param>
    /// <returns>Descriptions of bots, empty array is specified test not running</returns>
    /// <exception cref="System.ArgumentNullException">If type is null</exception>
    /// <exception cref="System.ArgumentException">If type is not derived from ITest</exception>
    BotDescription[] GetBotsWithTest( string typeName );

    BotDescription MyBot { get; }

    /// <summary>
    /// Incerement value of specified variable
    /// New variables start with value of 0
    /// </summary>
    /// <param name="var">Name of variable to increment</param>
    /// <exception cref="System.ArgumentNullException">If name is null</exception>
    /// <exception cref="System.ArgumentException">If name is not valid variable name</exception>
    void SyncInc( string name );

    /// <summary>
    /// Decrement value of specified variable
    /// New variables start with value of 0
    /// </summary>
    /// <param name="var">Name of variable to decrement</param>
    /// <exception cref="System.ArgumentNullException">If name is null</exception>
    /// <exception cref="System.ArgumentException">If name is not valid variable name</exception>
    void SyncDec( string name );

    /// <summary>
    /// Wait for specified value for variable
    /// </summary>
    /// <param name="name">Name of variable for checking</param>
    /// <param name="value">Value of variable to wait</param>
    /// <param name="timeout">Specify timeout for waiting. Use TimeOut.Zero to just check variable value. Use TimeOut.MaxValue to wait infinitly</param>
    /// <returns>Returns true if variable has specified value or false if function terminated due timeout</returns>
    /// <exception cref="System.ArgumentNullException">If name is null</exception>
    /// <exception cref="System.ArgumentException">If name is not valid variable name</exception>
    bool SyncWait( string name, int value, TimeSpan timeout );

    /// <summary>
    /// Informs about progress during current task (install or execute)
    /// </summary>
    /// <param name="progress">Progress value (0-100). Use negative value to indicate that progress not changed</param>
    /// <param name="message">Message to inform</param>
    void Progress( int progress, string message );
    void Progress( int progress );
    void Progress( string format, params object[] args );
    void Progress( int progress, string format, params object[] args );

    /// <summary>
    /// выложить локальные файл(ы) на сервер, как результат работы сценария 
    /// возможно использованием в имени файлов например ./logs/*.log или ./logs/*.*
    /// </summary>
    /// <param name="filePath"></param>
    void PutFile( string filePath );
  }
}
