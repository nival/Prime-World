using System;
using Npgsql;

namespace DataLogging
{
  /// <summary>
  /// Класс для хранения информации об источнике данных.
  /// </summary>
  public class DataLoggingContext
  {
    internal string ConnectionString { get; set; }

    public DataLoggingContext(string connectionString)
    {
      if (String.IsNullOrEmpty(connectionString)) throw new ArgumentNullException("connectionString");

      ConnectionString = connectionString;
    }

    public DataLoggingContext(string connectionString, string login, string password)
    {
      if (String.IsNullOrEmpty(connectionString)) throw new ArgumentNullException("connectionString");
      if (String.IsNullOrEmpty(login)) throw new ArgumentNullException("login");
      if (String.IsNullOrEmpty(password)) throw new ArgumentNullException("password");

      var builder = new NpgsqlConnectionStringBuilder(connectionString)
      {
        UserName = login,
        Password = password
      };
      ConnectionString = builder.ToString();
    }
  }
}