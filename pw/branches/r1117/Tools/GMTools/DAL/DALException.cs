using System;

namespace DAL
{
  /// <summary>
  /// Исключение слоя доступа к данным.
  /// </summary>
  public class DALException : Exception
  {
   public DALException(string message)
      : base(message)
    {
    }
    
    public DALException(string message, Exception innerException)
      : base(message, innerException)
    {
    }
  }
}