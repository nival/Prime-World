/*
#about Просчет crc32 у игровых сущностей 
*/

/*
#ref Types.DBTypes.dll
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using DBTypes;

public static class HashCalculator
{
}

public class SyncExcelTalents
{
  #region Crc32

  private static uint[] _crc32Table = null;

  private static void InitCRC32Table()
  {
    _crc32Table = new uint[256];
    uint crc;

    unchecked
    {
      // Инициалиазация таблицы
      for ( uint i = 0; i < 256; ++i )
      {
        crc = i;

        for ( uint j = 0; j < 8; ++j )
        {
          if ( ( crc & 1 ) != 0 )
            crc = ( crc >> 1 ) ^ 0xEDB88320;
          else
            crc >>= 1;
        }

        _crc32Table[i] = crc;
      }
    }
  }

  private static uint CalculateCRC32( string str )
  {
    if ( System.String.IsNullOrEmpty( str ) )
      return 0;

    if ( _crc32Table == null )
    {
      InitCRC32Table();
    }

    uint crc = 0xFFFFFFFF;

    unchecked
    {
      for ( int it = 0; it < str.Length; ++it )
      {
        crc = _crc32Table[( crc ^ (byte)( str[it] ) ) & 0xFF] ^ ( crc >> 8 );
      }
    }

    return ( crc ^ 0xFFFFFFFF );
  }

  #endregion

  private List<T> GetItems<T>( EditorLib.IEditorCommonApplication app, string path, bool recursive, bool includeDeriven ) where T : DBResource, new()
  {
    List<DBID> dbids;
    ObjectsSelector.CollectObjects( app, path, typeof( T ), recursive, includeDeriven, out dbids );

    List<T> result = new List<T>();
    foreach( var dbid in dbids )
      result.Add( DataBase.Get<T>( dbid ).Get() );

    return result;
  }

  delegate string GetItemIdFunc<T>( T item ) where T : DBResource;
  delegate TextRef GetItemNameFunc<T>( T item ) where T : DBResource;

  private void DumpPersistentId<T>( IEnumerable<T> items, GetItemIdFunc<T> getId, GetItemNameFunc<T> getNameA, GetItemNameFunc<T> getNameB ) where T : DBResource
  {
    foreach( var item in items )
    {
      var id = getId( item );
      if ( string.IsNullOrEmpty( id ) )
        continue;

      var nameA = getNameA == null ? string.Empty : getNameA( item ).ToString();
      if (nameA.Length > 50)
        nameA = nameA.Substring(0, 50);

      var nameB = getNameB == null ? string.Empty : getNameB( item ).ToString();
      string name = string.Empty;
      if ( string.IsNullOrEmpty( nameB ) || nameB == nameA )
      {
        if ( !string.IsNullOrEmpty( nameA ) )
          name = string.Format( " ({0})", nameA );
      }
      else if ( string.IsNullOrEmpty( nameA ) )
        name = string.Format( " ({0})", nameB );
      else
        name = string.Format( " ({0}/{1})", nameA, nameB );

      var crc32 = CalculateCRC32( id );
      Log.TraceMessage( "{0}:{1}{4} = {2} ({3})", typeof( T ).Name, id, crc32, (int)crc32, name );
    }
  }

  public IEnumerable Main( EditorLib.IEditorCommonApplication app )
  {
    DumpPersistentId( GetItems<DBTypes.Talent>( app, "/Items/Talents", true, false ), talent => talent.persistentId, talent => talent.name, null );
    DumpPersistentId( GetItems<DBTypes.Hero>( app, "/Heroes", true, false ), hero => hero.persistentId, hero => hero.heroNameA, hero => hero.heroNameB );
    DumpPersistentId( GetItems<DBTypes.HeroSkin>( app, "/Heroes", true, false ), skin => skin.persistentId, skin => skin.heroName, null );
    DumpPersistentId( GetItems<DBTypes.Constructon>( app, "/Social/Constructions", true, true ), con => con.persistentId, con => con.CaptionA, con => con.CaptionB );
    DumpPersistentId( GetItems<DBTypes.Quest>( app, "/Dialog", true, false ), quest => quest.persistentId, quest => quest.Title, null );
    DumpPersistentId( GetItems<DBTypes.OneTimeGuildShopItem>( app, "/Items/ClanItems", true, false ), item => item.persistentId, item => item.description, null );
    DumpPersistentId( GetItems<DBTypes.Lootbox>( app, "/Social/Lootboxes", true, false ), item => item.persistentId, item => item.tooltip, null );
    DumpPersistentId( GetItems<DBTypes.LootboxGuildShopItem>( app, "/Items/ClanItems", true, false ), item => item.lootbox.Get().persistentId, item => item.lootbox.Get().tooltip, null );
    DumpPersistentId( GetItems<DBTypes.TalentGuildShopItem>( app, "/Items/ClanItems", true, false ), item => item.talent.Get().persistentId, item => item.talent.Get().name, null );
    DumpPersistentId( GetItems<DBTypes.MarketingEventRollItem>( app, "/Items/Coupon", true, false ), item => item.persistentId, null, null );
    DumpPersistentId( GetItems<DBTypes.RerollShopGroup>( app, "/Items/RerollShop", true, false ), item => item.persistentId, null, null );
    DumpPersistentId( GetItems<DBTypes.LootboxRerollSlot>( app, "/Items/RerollShop", true, false ), item => item.lootbox.Get().persistentId, item => item.lootbox.Get().tooltip, null );
    DumpPersistentId( GetItems<DBTypes.ResourceRerollSlot>( app, "/Items/RerollShop", true, false ), item => item.persistentId, item => item.nameA, null );
    DumpPersistentId( GetItems<DBTypes.TalentsListRerollSlot>( app, "/Items/RerollShop", true, false ), item => item.persistentId, null, null );

    DumpPersistentId( GetItems<DBTypes.HeroRerollSlot>( app, "/Items/RerollShop", true, false ), item => item.persistentId, null, null );
    DumpPersistentId( GetItems<DBTypes.LampRerollSlot>( app, "/Items/RerollShop", true, false ), item => item.persistentId, null, null );
    DumpPersistentId( GetItems<DBTypes.SkinRerollSlot>( app, "/Items/RerollShop", true, false ), item => item.persistentId, null, null );
    DumpPersistentId( GetItems<DBTypes.TalentRerollSlot>( app, "/Items/RerollShop", true, false ), item => item.persistentId, null, null );
    DumpPersistentId( GetItems<DBTypes.PremiumRerollSlot>( app, "/Items/RerollShop", true, false ), item => item.persistentId, null, null );

    DumpPersistentId( GetItems<DBTypes.SkinGuildShopItem>( app, "/Items/ClanItems", true, false ), item => item.persistentId, null, null );
    DumpPersistentId( GetItems<DBTypes.FlagGuildShopItem>( app, "/Items/ClanItems", true, false ), item => item.persistentId, null, null );
    yield return true;
  }
}