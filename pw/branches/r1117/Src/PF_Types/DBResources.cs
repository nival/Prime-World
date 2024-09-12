using libdb.DB;
using System.Collections.Generic;
using System.ComponentModel;
using Render.DBRenderResources;

namespace PF_GameLogic.DBResources
{
  public class CurrencyDescription
  {
    [Custom("Social")]
    [Description("Currency id")]
    public string Id;
    [Custom("Social")]
    [Description("Currency description")]
    public TextRef Description;
    [Custom("Social")]
    [Description("Currency icon")]
    public DBPtr<Texture> Icon;
  }

  [DBVersion(0)]
  [UseTypeName("CRLS")]
  public class CurrencyDescriptionList : DBResource
  {
    [Custom("Social")]
    public List<CurrencyDescription> CurrencyList;
  }
}