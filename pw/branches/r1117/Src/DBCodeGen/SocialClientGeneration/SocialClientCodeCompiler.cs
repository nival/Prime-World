//using System;
//using System.Collections.Generic;
//using System.IO;
//using System.Reflection;
//using System.Text.RegularExpressions;
//using DBCodeGen.CodeGeneration;
//using DBCodeGen.Utils;
//using DBCodeGen.VisualStudioSupport;
//using libdb.DB;
//using System.Diagnostics;

//namespace DBCodeGen.SocialClientGeneration
//{
//  public static class SocialClientCodeCompiler
//  {
//    private static IEnumerable<string> ProcessFile(CodeFile file, List<Type> types, VCSProject resultProject, string customName, string outFolder)
//    {
//      Trace.TraceInformation("Generate types ({3}) for file {0} from project {1} for component {2}...",
//        file.Name, file.Project, componentDescriptor, string.IsNullOrEmpty(target) ? "all" : target);

//      List<string> files = new List<string>();
//      if (types == null || types.Count == 0)
//      {
//        Trace.TraceWarning("No types for file {0} from project {1}", file.Name, file.Project);
//        return files;
//      }
//      //load dependencies
//      List<CodeFile> dependencies = new List<CodeFile>();
//      List<CodeFile> forwardFiles = new List<CodeFile>();
//      List<Type> forwardTypes = new List<Type>();
//      Assembly fileAssembly = types[0].Assembly;

//      foreach (Type type in types)
//      {
//        foreach (FieldInfo field in GetFields(type, false, customName, null))
//        {
//          Type fieldType = field.FieldType;
//          for (Type listType = TypeUtils.GetTypeFromList(fieldType); listType != null; listType = TypeUtils.GetTypeFromList(fieldType))
//            fieldType = listType;

//          if (fieldType.IsSubclassOf(typeof(DBResource)))
//          {
//            Trace.TraceError("Field {1} of class {0} contains DBResource type without DBPtr.", type.Name, field.Name);
//            return files;
//          }

//          if (fieldType.IsSubclassOf(typeof(DBPtrBase)))
//          {
//            Type ptrType = TypeUtils.GetTypeFromPtr(fieldType);

//            CodeFile forwardFile = CodeFile.CreateFile(ptrType);
//            if (string.IsNullOrEmpty(customName) && forwardFile != null && forwardFile != file && !forwardFiles.Contains(forwardFile))
//              forwardFiles.Add(forwardFile);

//            if (ptrType != null && !forwardTypes.Contains(ptrType))
//              forwardTypes.Add(ptrType);
//          }
//          else if (string.IsNullOrEmpty(customName) && !DBCodeGen.IsSimpleType(type) && !DBCodeGen.IsSimpleType(fieldType) && type.Namespace != typeof(DBPtr<>).Namespace && !TypeUtils.HasAttribute<NoCodeAttribute>(fieldType, false))
//          {
//            CodeFile dependenceFile = CodeFile.CreateFile(fieldType);
//            if (dependenceFile != null && dependenceFile != file && !dependencies.Contains(dependenceFile))
//              dependencies.Add(dependenceFile);
//          }
//        }

//        if (string.IsNullOrEmpty(customName))
//        {
//          for (Type baseType = type.BaseType; baseType != null && !DBCodeGen.IsSimpleType(baseType); baseType = baseType.BaseType)
//          {
//            CodeFile dependenceFile = CodeFile.CreateFile(baseType);
//            if (dependenceFile != null && dependenceFile != file && !dependencies.Contains(dependenceFile) && baseType.Namespace != typeof(DBPtr<>).Namespace)
//              dependencies.Add(dependenceFile);
//          }
//        }
//      }
//      dependencies.Sort(CodeFile.Compare);

//      //split all types from file to enums, structs and classes
//      List<Type> enums = new List<Type>();
//      List<Type> structs = new List<Type>();
//      List<Type> classes = new List<Type>();

//      int csTypes = 0;
//      int cppTypes = 0;
//      foreach (Type type in types)
//      {
//        if (type.IsEnum)
//          enums.Add(type);
//        else if (DBCodeGen.IsResource(type))
//          classes.Add(type);
//        else if (DBCodeGen.IsStruct(type))
//          structs.Add(type);

//        if (!string.IsNullOrEmpty(customName) || !TypeUtils.HasAttribute<NoCSCodeAttribute>(type, false))
//          ++csTypes;
//        if (!string.IsNullOrEmpty(customName) || !TypeUtils.HasAttribute<NoCodeAttribute>(type, false))
//          ++cppTypes;
//      }

//      if (enums.Count == 0 && structs.Count == 0 && classes.Count == 0)
//        return files;

//      enums.Sort(TypeUtils.Compare);
//      if (!SortTypesByDependencies(structs, CollectFieldDependencies))
//      {
//        Trace.TraceError("Found circular dependencies in structures for file {0}\\{1}", file.Project, file.Name);
//        return files;
//      }

//      if (!SortTypesByDependencies(classes, CollectHierarcyDependencies))
//      {
//        Trace.TraceError("Found circular dependencies in structures for file {0}\\{1}", file.Project, file.Name);
//        return files;
//      }

//      string componentDirectory = GetPathToDescriptor(componentDescriptor);
//      string hFileName = Path.Combine(componentDirectory, file.Name + ".h");
//      string cppFileName = Path.Combine(componentDirectory, file.Name + ".cpp");
//      string csFileName = Path.Combine(componentDirectory, file.Name + ".cs");

//      Project project = null;
//      if (solution != null && !solution.IsEmpty && target != "cs")
//      {
//        project = solution.GetProject(file.Project);
//        if (project == null)
//        {
//          Trace.TraceError("Cannot find project \"{0}\" for file \"{1}\"", file.Project, file.Name);
//          return files;
//        }
//      }

//      if (target != "cs")
//      {
//        files.Add(file.Name + ".h");
//        files.Add(file.Name + ".cpp");
//      }
//      if (target != "cpp")
//        files.Add(file.Name + ".cs");

//      string projectPath = outFolder;
//      if (project != null && cppTypes > 0)
//      {
//        project.AddFile(hFileName);
//        project.AddFile(cppFileName);
//        projectPath = project.ProjectPath;
//      }

//      string resultProjectPath = projectPath;
//      if (resultProject != null && csTypes > 0)
//      {
//        resultProject.AddFile(csFileName);
//        resultProjectPath = resultProject.ProjectPath;
//      }

//      CodeWriter hFile = new CodeWriter(Path.Combine(projectPath, hFileName));
//      CodeWriter cppFile = new CodeWriter(Path.Combine(projectPath, cppFileName));
//      CodeWriter csFile = new CodeWriter(Path.Combine(resultProjectPath, csFileName));

//      Header.WriteHeader(hFile);
//      Code.WriteHeader(cppFile, file, forwardFiles);
//      CSCode.WriteHeader(csFile, dependencies);

//      Header.WriteIncludes(hFile, dependencies);
//      Header.WriteFactoryForwardDeclarations(hFile, CollectFactoriesForwards(classes));

//      Header.WriteOpenNamespace(hFile);
//      if (enums.Count > 0)
//        CodeGeneration.Enum.DeclareBuffer(cppFile);
//      Code.WriteRegistration(cppFile, classes, customName);
//      Code.WriteFactoryIncludes(cppFile, CollectFactoriesIncludes(classes));

//      Code.WriteOpenNamespace(cppFile);

//      forwardTypes.Sort(TypeUtils.Compare);
//      Header.WriteForwardDeclarations(hFile, forwardTypes);

//      foreach (Type type in enums)
//        CodeGeneration.Enum.Write(type, customName, hFile, cppFile, csFile, 0);

//      foreach (Type type in structs)
//        Struct.Write(type, false, customName, hFile, cppFile, csFile, 0);

//      foreach (Type type in classes)
//        Struct.Write(type, true, customName, hFile, cppFile, csFile, 0);

//      Header.WriteCloseNamespace(hFile);
//      Code.WriteCloseNamespace(cppFile);
//      CSCode.WriteCloseNamespace(csFile);

//      hFile.Close(dryRun || cppTypes == 0 || target == "cs");
//      cppFile.Close(dryRun || cppTypes == 0 || target == "cs");
//      csFile.Close(dryRun || csTypes == 0 || target == "cpp");

//      return files;
//    }
//  }
//}

