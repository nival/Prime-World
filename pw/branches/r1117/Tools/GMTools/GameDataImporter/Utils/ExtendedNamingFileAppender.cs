using System;
using log4net.Appender;

namespace GameDataImporter.Utils
{
  /// <summary>
  /// Ќазначение этого класса всего лишь в том чтобы уметь создавать лог файлы в формате
  /// yyyy.MM.dd-HH.mm.ss-им€сервиса, но чтобы этот файл ротировалс€ только по дн€м
  /// </summary>
  public class ExtendedNamingFileAppender : RollingFileAppender
  {
    private string suffixmarker = "TIME";

    protected override void OpenFile(string fileName, bool append)
    {
      string suffix = DateTime.UtcNow.ToString("HH.mm.ss");
      DatePattern = DatePattern.Replace(suffixmarker, suffix);
      suffixmarker = suffix;

      base.OpenFile(fileName, append);
    }
  }
}