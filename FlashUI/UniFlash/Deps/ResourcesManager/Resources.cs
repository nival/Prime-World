using System;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using Object = UnityEngine.Object;

namespace ResourcesManager
{
  public static class Resources
  {
    public const string INFO_FILE_NAME = "info";
    public const string INFO_FILE_EXTENSION = "txt";

    public const string CONTENT_FILE_NAME = "content";
    public const string CONTENT_FILE_EXTENSION = "txt";

    private class Bundle
    {
      public AssetBundle Data { get; private set; }
      public string Info { get; private set; }

      public int AssetsCount
      {
        get { return _assets.Count; }
      }

      private readonly List<string> _assets = new List<string>();

      public Bundle(AssetBundle bundle)
      {
        Data = bundle;
        var info = Data.LoadAsset(INFO_FILE_NAME) as TextAsset;
        if (info != null)
          Info = info.text;

        var assetsInfo = Data.LoadAsset(CONTENT_FILE_NAME) as TextAsset;
        if (assetsInfo != null)
        {
          var assets = assetsInfo.text.Replace("\r", "").Split(new[] {"\n"},
            StringSplitOptions.
              RemoveEmptyEntries);
          _assets.AddRange(assets);
        }
      }

      public void Unload(bool unloadAllObjects)
      {
        if (Data != null)
          Data.Unload(unloadAllObjects);
      }

      public bool Contains(string assetPath)
      {
        return _assets.Contains(assetPath.ToLowerInvariant());
      }
    }

    private static readonly Dictionary<string, Bundle> _bundles = new Dictionary<string, Bundle>();

    public static string Register(string bundleFilePath)
    {
      string logs = string.Empty;
      if (_bundles.ContainsKey(bundleFilePath))
      {
        logs += string.Format("trying to load bundle '{0}', but it already loaded", bundleFilePath);
        return logs;
      }

      // Build: Data/Resources/
      // Editor trunk/Resources/
      string dataPackDirectory = Application.dataPath;
      if (Application.isEditor)
      {
        var di = new DirectoryInfo(dataPackDirectory);
        if (di.Parent != null && di.Parent.Parent != null && di.Parent.Parent.Parent != null)
        {
          dataPackDirectory = di.Parent.Parent.Parent.FullName;
        }
      }

      dataPackDirectory += Path.DirectorySeparatorChar + "Resources" + Path.DirectorySeparatorChar;

      var time = Time.realtimeSinceStartup;
      var dataFilePath = dataPackDirectory + bundleFilePath;

      AssetBundle aBundle = null;
      if (File.Exists(dataFilePath))
      {
        aBundle = AssetBundle.LoadFromFile(dataFilePath);
      }
      if (aBundle == null)
      {
        logs += string.Format("unable to load '{0}'", dataFilePath);
        return logs;
      }

      var bundle = new Bundle(aBundle);
      _bundles.Add(bundleFilePath, bundle);
      logs += string.Format("bundle '{0}' with {1} assets was loaded in {2}s. info:\n{3}",
        bundleFilePath, bundle.AssetsCount, Time.realtimeSinceStartup - time, bundle.Info);

      return logs;
    }

    private static AssetBundle FindBundleForResource(string resourcePath)
    {
      foreach (var b in _bundles)
        if (b.Value.Contains(resourcePath))
          return b.Value.Data;
      return null;
    }

    public static Object Load(string path)
    {
      var result = UnityEngine.Resources.Load(path);
      if (result == null)
      {
        var b = FindBundleForResource(path);
        if (b != null)
          result = b.LoadAsset(path);
      }

      return result;
    }

    public static Object Load(string path, Type systemTypeInstance)
    {
      var result = UnityEngine.Resources.Load(path, systemTypeInstance);
      if (result == null)
      {
        var b = FindBundleForResource(path);
        if (b != null)
          result = b.LoadAsset(path, systemTypeInstance);
      }
      return result;
    }

    public static AsyncOperation UnloadUnusedAssets()
    {
      return UnityEngine.Resources.UnloadUnusedAssets();
    }

    public static Object[] LoadAll(string path)
    {
      return UnityEngine.Resources.LoadAll(path);
    }

    public static void UnloadExternalResources()
    {
      foreach (var bundle in _bundles)
        bundle.Value.Unload(false);
    }
  }
}