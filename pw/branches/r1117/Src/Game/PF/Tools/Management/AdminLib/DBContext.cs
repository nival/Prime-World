using System;
using Npgsql;

namespace AdminLib
{
  /// <summary>
  /// Класс для хранения информации об источнике данных.
  /// </summary>
  public class DBContext
  {
    internal string ConnectionString { get; set; }

    public DBContext(string connectionString)
    {
      if (String.IsNullOrEmpty(connectionString)) throw new ArgumentNullException("connectionString");

      ConnectionString = connectionString;
    }

    public DBContext(string connectionString, string login, string password)
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