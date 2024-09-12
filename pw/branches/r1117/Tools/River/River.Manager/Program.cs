using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Remoting;
using System.Text;
using River.Core;
using River.Core.Diagnostics;
using River.Manager.Properties;

namespace River.Manager
{
  class Program
  {
    private static void ShowHelp()
    {
      var sb = new StringBuilder();
      sb.AppendLine("Использование River.Manager:");
      sb.AppendLine("  river.manager --list|--start <suite> [--tag <tag>][--timestart <time to start>][--timestop <time to stop>]|--stop [--id <suiteId> |--tag <tag> | all]\n");
      sb.AppendFormat(" {0,-15} - Список запущенных наборов сценариев\n", "--list");
      sb.AppendFormat(" {0,-15} - Запуск набора сценариев на выполнение.\n", "--start");
      sb.AppendFormat(" {0,-15}   <suite> - имя файла с набором сценариев.\n", "");
      sb.AppendFormat(" {0,-15} - Добавление описания к набору, или же поиск по описанию.\n", "--tag");
      sb.AppendFormat(" {0,-15}   <tag> - краткое описание.\n", "");
      sb.AppendFormat(" {0,-15} - Старт набора сценариев по расписанию.\n", "--timestart");
      sb.AppendFormat(" {0,-15}   <time to start> - время запуска.\n", "");
      sb.AppendFormat(" {0,-15} - Остановка набора сценариев по расписанию.\n", "--timestop");
      sb.AppendFormat(" {0,-15}   <time to stop> - время остановки.\n", "");
      sb.AppendFormat(" {0,-15} - Остановка набора сценариев.\n", "--stop");
      sb.AppendFormat(" {0,-15} - Идентификатор останавливаемого набора.\n", "--id");
      sb.AppendFormat(" {0,-15}   <suiteId> - значение идентификатора (GUID).\n", "");
      Console.WriteLine(sb);
    }

    static void Main(string[] args)
    {
      RemotingConfiguration.Configure(Path.GetFileName(Assembly.GetEntryAssembly().Location) + ".config", false);

      IMaster master = Activator.GetObject(typeof(IMaster), Settings.Default.masterUrl) as IMaster;

      if (master == null)
      {
        Console.WriteLine("Не удалось найти Master.");
        return;
      }

      if (args == null || args.Length == 0)
      {
        ShowHelp();
        return;
      }
      
      // Разбор командной строки - это ад и кошмар! 
      // todo: прилепить сюда нормальный парсер, используемый в других проектах
      if (args[0] == "--list")
      {
        foreach (var inf in master.SuitesInfo())
        {
          Console.WriteLine(inf);
        }
      }
      else if (args[0] == "--start" && (args.Length == 2 || args.Length == 4 || args.Length == 8))
      {
        string tag = null;
        DateTime? timestart = null, timestop = null;
        for (int i = 2; i < args.Length; i+=2)
        {
          if (args[i] == "--tag") tag = args[i + 1];
          try
          {
            if (args[i] == "--timestart") timestart = DateTime.Parse(args[i + 1]);
            if (args[i] == "--timestop") timestop = DateTime.Parse(args[i + 1]);
          }
          catch (FormatException)
          {
            Console.WriteLine("Invalid date format");
            return;
          }
        }
        if (timestart == null ^ timestop == null)
        {
          Console.WriteLine("Both timestart and timestop parameters must be defined.");
          return;
        }

        try
        {
          master.ExecuteSuite(Path.GetFileName(args[1]), tag, File.ReadAllText(args[1]), Guid.NewGuid(), timestart, timestop);
        }
        catch(Exception e)
        {
          Console.WriteLine(e.Message);
        }
      }
      else if (args[0] == "--stop" && (
        (args.Length == 3 && (args[1] == "--id" || args[1] == "--tag")) ||
        (args.Length == 2 && args[1] == "all")
        ))
      {
        if (args[1] == "--id")
        {
          var id = new Guid(args[2]);
          master.HaltSuite(id);
        }
        else if (args[1] == "--tag")
        {
          master.HaltSuite(args[2]);
        }
        else if (args[1] == "all")
        {
          master.HaltAllSuites();
        }
      }
      else
      {
        ShowHelp();
      }
    }
  }
}
