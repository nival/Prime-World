using System;
using Npgsql;

namespace DAL
{
  /// <summary>
  /// Класс для хранения информации об источнике данных.
  /// </summary>
  public class DALContext
  {
    internal string ConnectionString { get; set; }

    public DALContext(string connectionString)
    {
      if (String.IsNullOrEmpty(connectionString)) throw new ArgumentNullException("connectionString");

      ConnectionString = connectionString;
    }

    public DALContext(string connectionString, string login, string password)
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