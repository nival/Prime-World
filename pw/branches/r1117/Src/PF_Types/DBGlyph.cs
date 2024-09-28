//#include "DBMinimap.cs"
using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBStats;
using Scene.DBSceneBase;
using Foundation.DBSystem;
using PF_GameLogic.DBGameLogic;

namespace PF_GameLogic.DBUnit
{

  public enum EGlyph
  {
    DoubleDamager,
    LifeRestorer,
    EnergyRestorer,
    Refresher,
    Booster,
    Invisibler,
  };

  [TypeId(0xF61DC00)]
  [UseTypeName("GLPH")]
  public class Glyph : Ability
  {
    public EGlyph id = EGlyph.DoubleDamager;

    public DBPtr<SingleStateObject> gameObject;
    public HDRColor color = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    [FieldCategory("Logic")]
    public int naftaCost = 0;

    [Description("Radius to open warfog at glyph (0 to disable)")]
    public float openWarFogRadius = 0.0f;

    public EMinimapIcons minimapIcon = EMinimapIcons.None;

    public DBPtr<Ability> pickupAbility;
  }

  public class GlyphEntry
  {
    public DBPtr<Glyph> glyph;
    [IntMin(1)]
    public int weight = 1;
  }

  [UseTypeName("GLDB")]
  public class GlyphsDB : DBResource
  {
    public List<GlyphEntry> glyphs = new List<GlyphEntry>();
  }
   
  [TypeId(0xF61DC01)]
  [UseTypeName( "GLSPN" )]
  public class GlyphSpawner : GameObject 
  {
    [Description("Использовать глобальные настройки глифов?")]
    public bool useGlyphManager = true;

    [Description( "Кастомные параметры спавна глифов" )]
    public GlyphSettings settings = new GlyphSettings();

    [Description( "Кастомный список глифов" )]
    public DBPtr<GlyphsDB> glyphs = null;
  }
  
}