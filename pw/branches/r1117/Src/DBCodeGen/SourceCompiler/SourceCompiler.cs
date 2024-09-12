using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text.RegularExpressions;
using DBCodeGen.Utils;

namespace DBCodeGen.SourceCompiler
{
  public static class SourceCompiler
  {
    private static List<string> CollectSources(IEnumerable<string> sources, SearchFolders searchFolders)
    {
      List<string> result = new List<string>();
      foreach (var source in sources)
      {
        string sourceFullName = searchFolders.GetFullFileName(string.Empty, source);
        if (string.IsNullOrEmpty(sourceFullName))
        {
          Trace.TraceError("Source file \"{0}\" not found", source);
          return null;
        }

        result.Add(sourceFullName);
      }

      result.Sort();
      return result;
    }

    private static List<string> CollectIncludes(string fileName)
    {
      List<string> result = new List<string>();
      Regex includeRegex = new Regex("\\#include\\s+\\\"([A-Za-z0-9_\\.\\\\\\/]+)\\\"");
      using (LinesReader reader = new LinesReader(new FileStream(fileName, FileMode.Open, FileAccess.Read)))
      {
        int lineNumber = 1;
        foreach (string line in reader)
        {
          if (line.TrimStart(' ', '\t', '/').StartsWith("#include"))
          {
            Match m = includeRegex.Match(line);
            if (!m.Success)
            {
              Trace.TraceError("{0} ({1}): Invalid syntax of #inclide directive", fileName, lineNumber);
              return null;
            }
            string includeFileName = m.Groups[1].Value;
            result.Add(includeFileName);
          }

          ++lineNumber;
        }
      }

      return result;
    }

    private static List<string> CollectIncludes(IEnumerable<string> files, SearchFolders searchFolders)
    {
      Dictionary<string, string> includeFiles = new Dictionary<string, string>();
      foreach (var fileName in files)
        if (!includeFiles.ContainsKey(fileName.ToLower()))
          includeFiles.Add(fileName.ToLower(), string.Empty);
      List<string> fileNames = new List<string>(files);

      while (fileNames.Count > 0)
      {
        string fileName = fileNames[0];
        fileNames.RemoveAt(0);
        List<string> includes = CollectIncludes(fileName);
        if (includes != null)
        {
          foreach (var include in includes)
          {
            string fullFileName = searchFolders.GetFullFileName(Path.GetDirectoryName(fileName), include);
            if (string.IsNullOrEmpty(fullFileName))
            {
              Trace.TraceError("{0}: Cannot find included file \"{1}\"", fileName, include);
              return null;
            }
            if (!includeFiles.ContainsKey(fullFileName.ToLower()))
            {
              includeFiles.Add(fullFileName.ToLower(), fullFileName);
              fileNames.Add(fullFileName);
            }
          }
        }
      }

      List<string> result = new List<string>();
      foreach (var fileName in includeFiles.Values)
      {
        if (!string.IsNullOrEmpty(fileName))
          result.Add(fileName);
      }
      result.Sort();

      return result;
    }

    private static Assembly CompileFromSources(string[] sources, Assembly include, string suffix)
    {
      CompilerParameters compilerParameters = new CompilerParameters();
      compilerParameters.GenerateInMemory = false;
      compilerParameters.WarningLevel = 4;
      compilerParameters.IncludeDebugInformation = true;
      compilerParameters.OutputAssembly = Path.Combine(Path.GetTempPath(), Path.GetFileNameWithoutExtension(Path.GetRandomFileName())) + suffix + ".dll";
      compilerParameters.ReferencedAssemblies.Add("mscorlib.dll");
      compilerParameters.ReferencedAssemblies.Add("System.dll");
      compilerParameters.ReferencedAssemblies.Add(Path.GetFullPath(Assembly.GetEntryAssembly().Location));

      foreach (var assemblyName in Assembly.GetEntryAssembly().GetReferencedAssemblies())
      {
        Assembly assembly = Assembly.Load(assemblyName);
        if (IsSameLocation(assembly, Assembly.GetEntryAssembly()))
          compilerParameters.ReferencedAssemblies.Add(Path.GetFullPath(assembly.Location));
      }

      if (include != null)
        compilerParameters.ReferencedAssemblies.Add(include.Location);

      CodeDomProvider provider = CodeDomProvider.CreateProvider("CSharp");
      CompilerResults results = provider.CompileAssemblyFromFile(compilerParameters, sources);
      if (results.Errors.HasErrors)
      {
        foreach (CompilerError error in results.Errors)
          Trace.TraceError("{0}({1}): {2}: {3}", error.FileName, error.Line, error.ErrorNumber, error.ErrorText);
        return null;
      }

      return results.CompiledAssembly;
    }

    public static Assembly Compile(IEnumerable<string> sources, SearchFolders searchFolders)
    {
      List<string> sourcesFullNames = CollectSources(sources, searchFolders);
      if (sourcesFullNames == null)
        return null;

      List<string> allIncludes = CollectIncludes(sourcesFullNames, searchFolders);

      Assembly includeAssembly = null;
      if (allIncludes != null && allIncludes.Count > 0)
      {
        includeAssembly = CompileFromSources(allIncludes.ToArray(), null, "_include");
        if (includeAssembly == null)
          return null;
      }

      return CompileFromSources(sourcesFullNames.ToArray(), includeAssembly, "_sources");
    }

    public static bool IsSameLocation(Assembly a, Assembly b)
    {
      return string.Compare(Path.GetDirectoryName(Path.GetFullPath(a.Location)), Path.GetDirectoryName(Path.GetFullPath(b.Location)), StringComparison.InvariantCultureIgnoreCase) == 0;
    }
  }
}
