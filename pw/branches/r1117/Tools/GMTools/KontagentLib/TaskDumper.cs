using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using log4net;

namespace KontagentLib
{
  public interface ITaskDumper
  {
    bool HasDumpedTasks { get; }
    void Dump(IEnumerable<IKontagentTask> tasks);
    IEnumerable<IKontagentTask> Restore(int count);
  }

  public class TaskFileDumper : ITaskDumper
  {
    private static ILog _log = LogManager.GetLogger(typeof (TaskFileDumper));

    private readonly string filename;
    private const string TMP = ".tmp";
    public static readonly object filelocker = new object();

    public bool HasDumpedTasks { get; private set; }

    public TaskFileDumper(string filename)
    {
      if (String.IsNullOrEmpty(filename)) throw new ArgumentNullException("filename");
      this.filename = filename;

      lock (filelocker)
      {
        HasDumpedTasks = File.Exists(filename);
      }
    }

    public void Dump(IEnumerable<IKontagentTask> tasks)
    {
      _log.InfoFormat("Dump {0} tasks to file {1}", tasks.Count(), filename);
      var sb = new StringBuilder();
      foreach (var t in tasks)
      {
        string s = SerializeTask(t);
        if (!String.IsNullOrEmpty(s))
          sb.AppendLine(s);
      }

      lock (filelocker)
      {
        bool success = false;
        try
        {
          using (var sw = new StreamWriter(filename, true, Encoding.UTF8))
            sw.Write(sb.ToString());
          success = true;
        }
        catch (Exception ex)
        {
          _log.Error("Failed to dump tasks in " + filename, ex);
        }
        // если не получилось записать в нормальный файл, начинаем извращаться
        if (!success) 
        {
          int i = 1;
          do
          {
            try
            {
              // попытка записать в файл filename.2 filename.3 итд
              using (var sw = new StreamWriter(filename + "." + ++i, true, Encoding.UTF8))
                sw.Write(sb.ToString());
              success = true;
            }
            catch (Exception ex)
            {
              _log.Error("Failed to dump tasks in " + filename + "." + i, ex);
            }
          } while (!success && i < 5);
        }
        if (!success)
          throw new Exception("Cannot dump task in any file.");
        HasDumpedTasks = true;
      }
    }

    public IEnumerable<IKontagentTask> Restore(int count)
    {
      var files = Directory.GetFiles(Environment.CurrentDirectory, filename + "*");
      HasDumpedTasks = files.Length > 0;
      if (!HasDumpedTasks)
        return null;

      foreach (var file in files)
      {
        try
        {
          var tasks = new List<IKontagentTask>();
          var usetmpfile = false;
          lock (filelocker)
          {
            using (var sr = new StreamReader(file, Encoding.UTF8))
            {
              for (int i = 0; i < count && !sr.EndOfStream; i++)
              {
                var str = sr.ReadLine();
                var t = DeserializeTask(str);
                if (t == null)
                  continue;
                tasks.Add(t);
              }
              // Если в исходном файле еще что-то осталось, то остаток пишется во временный файл
              if (!sr.EndOfStream)
              {
                using (var swtmp = new StreamWriter(file + TMP, false, Encoding.UTF8))
                  while (!sr.EndOfStream)
                    swtmp.WriteLine(sr.ReadLine());
                usetmpfile = true;
              }
            }
            File.Delete(file);
            // Если был создан временный файл, то он перезаписывает собой исходный
            if (usetmpfile)
              File.Move(file + TMP, file);
            HasDumpedTasks = usetmpfile || files.Length > 1; // Не убираем флаг HasDumpedTasks если остались еще файлы
          }
          _log.InfoFormat("Restored {0} tasks", tasks.Count);
          return tasks;
        }
        catch (Exception ex)
        {
          _log.Error("Cannot restore tasks from " + file, ex);
        }
      }
      return null;
    }

    public string SerializeTask(IKontagentTask task)
    {
      var fields = new List<string> {task.GetType().FullName};

      foreach (var prop in task.GetType().GetProperties(BindingFlags.Public | BindingFlags.Instance))
        fields.Add(String.Format("{0}:{1}", prop.Name, prop.GetValue(task, null)));

      return String.Join(";", fields.ToArray());
    }

    public IKontagentTask DeserializeTask(string serialized)
    {
      try
      {
        if (String.IsNullOrEmpty(serialized))
          return null;

        var fields = serialized.Split(';');
        if (fields.Length < 2) 
          throw new Exception("fields count = " + fields.Length);
        
        var taskType = Type.GetType(fields[0], true);
        var task = Activator.CreateInstance(taskType);
        for (int i = 1; i < fields.Length; i++)
        {
          string[] pair = fields[i].Split(':');
          if (pair.Length != 2)
            throw new Exception("invalid field " + fields[i]);
          
          var prop = taskType.GetProperty(pair[0]);
          object value;
          if (prop.PropertyType == typeof(String))
            value = pair[1];
          else if (prop.PropertyType == typeof(Int32))
            value = Int32.Parse(pair[1]);
          else if (prop.PropertyType == typeof(Int64))
            value = Int64.Parse(pair[1]);
          else if (prop.PropertyType == typeof(bool))
            value = Boolean.Parse(pair[1]);
          else
            throw new Exception("unexpected field type " + prop.PropertyType.Name);

          prop.SetValue(task, value, null);
        }
        return (IKontagentTask)task;
      }
      catch (Exception ex)
      {
        _log.ErrorFormat("Cannot deserialize task string = \"{0}\", error message: {1}", serialized, ex);
        return null;
      }
    }
  }
}