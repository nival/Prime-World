using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Flash.Utils;
using UnityEngine;

namespace Flash
{
  /// <summary>
  /// Агрегатор данных шрифта. Вычитываются только нужные таблицы, по этому при модификации нужно быть аккуратным со смещениями.
  /// http://http://www.microsoft.com/typography/tt/ttf_spec/ttch02.doc
  /// http://developer.apple.com/fonts/TTRefMan/RM06/Chap6.html#Directory
  /// </summary>
  internal sealed class FontDataTTF
  {
    private const string KERN = "kern";
    private const string HEAD = "head";
    private const string CMAP = "cmap";
    //---
    private string _name;
    private OffsetSubTable _subTable;
    private Dictionary<string, TableDir> _tableDirs = new Dictionary<string, TableDir>();
    // Cached tables
    private HeaderTable? _head = null;
    private EncodingSubTable_Format4 _cmap = null;
    private KerningTable_Format0 _kern = null;
    private bool _hasKern = false;


    public FontDataTTF( string name )
    {
      _name = name;
    }
    public void ReadData( BinaryReader reader )
    {
      //Debug.Log("Read TTF data " + _name);

      _subTable = new OffsetSubTable();
      _subTable.ReadData( reader );

      // Parse dirs
      for ( UInt16 i = 0; i < _subTable.NumTables; ++i )
      {
        TableDir table = new TableDir();
        table.ReadData( reader );
        // Dont check head table
        if ( table.Tag != HEAD && !table.ValidateChecksum( reader ) )
          throw new ReadTTFException( "TableDir checksum validation failed." );

        _tableDirs.Add( table.Tag, table );
      }

      // Read tables
      if ( _tableDirs.ContainsKey( HEAD ) )
        _head = ReadHead( reader, _tableDirs[HEAD] );
      if ( _tableDirs.ContainsKey( CMAP ) )
        _cmap = ReadCmap( reader, _tableDirs[CMAP] );
      if ( _tableDirs.ContainsKey( KERN ) )
        _kern = ReadKern( reader, _tableDirs[KERN] );

      if ( _head == null || _cmap == null || _kern == null )
        Debug.LogError( _name + " font doesn't contains some tables:\n" + _head + "\n" + _cmap + "\n" + _kern );
      else
        _hasKern = true;
    }
    public float GetKern( char left, char right )
    {
      if ( !_hasKern )
        return 0;

      UInt16 ileft;
      UInt16 iright;
      Int16 kerning = 0;
      if ( _cmap.Cmap.TryGetValue( left, out ileft ) && _cmap.Cmap.TryGetValue( right, out iright ) )
      {
        if ( _kern.KernPairs.TryGetValue( MathUtils.ConcatShort( ileft, iright ), out kerning ) )
        {
          return (float)kerning / _head.Value.UnitsPerEm;
        }
      }

      return 0;
    }
    //---
    private EncodingSubTable_Format4 ReadCmap( BinaryReader reader, TableDir tableDir )
    {
      SeekTable( reader, tableDir );

      long pos = reader.BaseStream.Position;
#pragma warning disable 219
      UInt16 version = MathUtils.ReverseBytes( reader.ReadUInt16() );
#pragma warning restore 219
      UInt16 nTables = MathUtils.ReverseBytes( reader.ReadUInt16() );

      // Read tables
      EncodingTable[] encTables = new EncodingTable[nTables];
      for ( int i = 0; i < nTables; ++i )
      {
        encTables[i] = new EncodingTable();
        encTables[i].ReadData( reader );
      }

      // Read subtables
      for ( int i = 0; i < nTables; ++i )
      {
        reader.BaseStream.Seek( pos, SeekOrigin.Begin );
        reader.BaseStream.Seek( encTables[i].Offset, SeekOrigin.Current );
        UInt16 format  = MathUtils.ReverseBytes( reader.ReadUInt16() );
        reader.BaseStream.Seek( -2, SeekOrigin.Current );
        if ( encTables[i].PlatformID == 3 && encTables[i].EncodingID == 1 && format == 4 )
        {
          EncodingSubTable_Format4 cmapSubTable = new EncodingSubTable_Format4();
          cmapSubTable.ReadData( reader );
          return cmapSubTable;
        }
      }

      return null;
    }
    private KerningTable_Format0 ReadKern( BinaryReader reader, TableDir tableDir )
    {
      SeekTable( reader, tableDir );
#pragma warning disable 219
      UInt16 version = MathUtils.ReverseBytes( reader.ReadUInt16() );
#pragma warning restore 219
      UInt16 nTables = MathUtils.ReverseBytes( reader.ReadUInt16() );

      KerningSubTable[] kerningSubTables = new KerningSubTable[nTables];
      for ( int i = 0; i < nTables; ++i )
      {
        kerningSubTables[i] = new KerningSubTable();
        kerningSubTables[i].ReadData( reader );

        uint horizontal = kerningSubTables[i].Coverage & 0x0001U;
        uint minimum = kerningSubTables[i].Coverage & 0x0002U;
        uint format = kerningSubTables[i].Coverage & 0xFF00U;
        if ( horizontal == 1 && format == 0 && minimum == 0 )
        {
          KerningTable_Format0 table0 = new KerningTable_Format0();
          table0.ReadData( reader );
          return table0;
        }
        else
        {
          reader.BaseStream.Seek( -6 + kerningSubTables[i].Length, SeekOrigin.Current );
        }
      }

      return null;
    }
    private HeaderTable ReadHead( BinaryReader reader, TableDir tableDir )
    {
      SeekTable( reader, tableDir );
      HeaderTable headerTable = new HeaderTable();
      headerTable.ReadData( reader );
      return headerTable;
    }
    private void SeekTable( BinaryReader reader, TableDir tableDir )
    {
      reader.BaseStream.Seek( tableDir.Offset, SeekOrigin.Begin );
    }


    internal struct OffsetSubTable
    {
      public UInt32 ScalerType;
      public UInt16 NumTables;
      public UInt16 SearchRange;
      public UInt16 EntrySelector;
      public UInt16 RangeShift;


      public void ReadData( BinaryReader reader )
      {
        ScalerType = MathUtils.ReverseBytes( reader.ReadUInt32() );
        NumTables = MathUtils.ReverseBytes( reader.ReadUInt16() );
        SearchRange = MathUtils.ReverseBytes( reader.ReadUInt16() );
        EntrySelector = MathUtils.ReverseBytes( reader.ReadUInt16() );
        RangeShift = MathUtils.ReverseBytes( reader.ReadUInt16() );
      }
      public override string ToString()
      {
        return String.Format( "ScalerType = {0} NumTables = {1} SearchRange = {2} EntrySelector = {3} RangeShift = {4}", ScalerType, NumTables, SearchRange, EntrySelector, RangeShift );
      }
    }

    internal struct TableDir
    {
      public string Tag;
      public UInt32 CheckSum;
      public UInt32 Offset;
      public UInt32 Length;


      public void ReadData( BinaryReader reader )
      {
        Tag = Encoding.ASCII.GetString( reader.ReadBytes( 4 ) );
        CheckSum = MathUtils.ReverseBytes( reader.ReadUInt32() );
        Offset = MathUtils.ReverseBytes( reader.ReadUInt32() );
        Length = MathUtils.ReverseBytes( reader.ReadUInt32() );
      }
      public bool ValidateChecksum( BinaryReader reader )
      {
        long pos = reader.BaseStream.Position;

        reader.BaseStream.Seek( Offset, SeekOrigin.Begin );

        UInt32 sum = 0;
        UInt32 nLongs = ( Length + 3 ) / 4;
        while ( nLongs-- > 0 )
          sum += MathUtils.ReverseBytes( reader.ReadUInt32() );

        reader.BaseStream.Seek( pos, SeekOrigin.Begin );
        return CheckSum == sum;
      }
      public override string ToString()
      {
        return String.Format( "Tag = {0} CheckSum = {1} Offset = {2} Length = {3}", Tag, CheckSum, Offset, Length );
      }
    }

    internal struct HeaderTable
    {
      public float Version;
      public float FontRevision;
      public UInt32 CheckSumAdjustment;
      public UInt32 MagicNumber;
      public UInt16 Flags;
      public UInt16 UnitsPerEm;


      public void ReadData( BinaryReader reader )
      {
        Version = MathUtils.FixedToFloat( MathUtils.ReverseBytes( reader.ReadUInt32() ) );
        FontRevision = MathUtils.FixedToFloat( MathUtils.ReverseBytes( reader.ReadUInt32() ) );
        CheckSumAdjustment = MathUtils.ReverseBytes( reader.ReadUInt32() );
        MagicNumber = MathUtils.ReverseBytes( reader.ReadUInt32() );
        if ( MagicNumber != 0x5F0F3CF5 )
          throw new ReadTTFException( "Wrong magic number!" );
        Flags = MathUtils.ReverseBytes( reader.ReadUInt16() );
        UnitsPerEm = MathUtils.ReverseBytes( reader.ReadUInt16() );
      }
      public override string ToString()
      {
        return String.Format( "Version = {0} FontRevision = {1} Flags = {2} UnitsPerEm = {3}", Version, FontRevision, Flags, UnitsPerEm );
      }
    }

    internal struct EncodingTable
    {
      public UInt16 PlatformID;
      public UInt16 EncodingID;
      public UInt32 Offset;


      public void ReadData( BinaryReader reader )
      {
        PlatformID = MathUtils.ReverseBytes( reader.ReadUInt16() );
        EncodingID = MathUtils.ReverseBytes( reader.ReadUInt16() );
        Offset = MathUtils.ReverseBytes( reader.ReadUInt32() );
      }
      public override string ToString()
      {
        return String.Format( "PlatformID = {0} EncodingID = {1} Offset = {2}", PlatformID, EncodingID, Offset );
      }
    }

    internal class EncodingSubTable_Format4
    {
#pragma warning disable 414
      private UInt16 _format;
      private UInt16 _length;
      private UInt16 _version;
      private UInt16 _segCountX2;
      private UInt16 _searchRange;
      private UInt16 _entrySelector;
      private UInt16 _rangeShift;
      private UInt16[] _endCode;
      private UInt16 _reservePad;
      private UInt16[] _startCode;
      private UInt16[] _idDelta;
      private UInt16[] _idRangeOffset;
#pragma warning restore 414
      private Dictionary<char, UInt16> _cmap = new Dictionary<char, UInt16>();
      public Dictionary<char, UInt16> Cmap
      {
        get { return _cmap; }
      }
      //public Dictionary<UInt16, char> map = new Dictionary<UInt16, char>(); 


      public void ReadData( BinaryReader reader )
      {
        long pos = reader.BaseStream.Position;

        _format = MathUtils.ReverseBytes( reader.ReadUInt16() );
        _length = MathUtils.ReverseBytes( reader.ReadUInt16() );
        _version = MathUtils.ReverseBytes( reader.ReadUInt16() );
        _segCountX2 = MathUtils.ReverseBytes( reader.ReadUInt16() );
        _searchRange = MathUtils.ReverseBytes( reader.ReadUInt16() );
        _entrySelector = MathUtils.ReverseBytes( reader.ReadUInt16() );
        _rangeShift = MathUtils.ReverseBytes( reader.ReadUInt16() );
        int segCount = _segCountX2 / 2;

        long end =  pos + _length;
        long frontEndPos = reader.BaseStream.Position;

        _endCode = new UInt16[segCount];
        for ( int i = 0; i < segCount; ++i )
          _endCode[i] = MathUtils.ReverseBytes( reader.ReadUInt16() );

        _reservePad = MathUtils.ReverseBytes( reader.ReadUInt16() );
        if ( _reservePad != 0 )
          throw new ReadTTFException( "Pad != 0" );

        _startCode = new UInt16[segCount];
        for ( int i = 0; i < segCount; ++i )
          _startCode[i] = MathUtils.ReverseBytes( reader.ReadUInt16() );

        _idDelta = new UInt16[segCount];
        for ( int i = 0; i < segCount; ++i )
          _idDelta[i] = MathUtils.ReverseBytes( reader.ReadUInt16() );

        _idRangeOffset = new UInt16[segCount];
        for ( int i = 0; i < segCount; ++i )
        {
          _idRangeOffset[i] = MathUtils.ReverseBytes( reader.ReadUInt16() );
          frontEndPos = frontEndPos > reader.BaseStream.Position ? frontEndPos : reader.BaseStream.Position;

          if ( _endCode[i] == UInt16.MaxValue )
            break;

          long savedPos = reader.BaseStream.Position;
          for ( UInt16 unicode = _startCode[i]; unicode <= _endCode[i]; ++unicode )
          {
            if ( _idRangeOffset[i] != 0 )
            {
              long glyphPos = savedPos - 2 + _idRangeOffset[i] + 2 * ( unicode - _startCode[i] );
              reader.BaseStream.Seek( glyphPos, SeekOrigin.Begin );

              UInt16 glyph = MathUtils.ReverseBytes( reader.ReadUInt16() );
              frontEndPos = frontEndPos > reader.BaseStream.Position ? frontEndPos : reader.BaseStream.Position;

              reader.BaseStream.Seek( savedPos, SeekOrigin.Begin );

              if ( glyph == 0 )
                continue;
              _cmap.Add( (char)unicode, glyph );
            }
            else
            {
              _cmap.Add( (char)unicode, (UInt16)( unicode + _idDelta[i] ) );
            }
          }
        }

        if ( end != frontEndPos )
        {
          Debug.LogWarning( String.Format( "end = {0} != lastPos = {1}", end, frontEndPos ) );
        }
      }
    }

    internal struct KerningSubTable
    {
      public UInt16 Version;
      public UInt16 Length;
      public UInt16 Coverage;


      public void ReadData( BinaryReader reader )
      {
        Version = MathUtils.ReverseBytes( reader.ReadUInt16() );
        Length = MathUtils.ReverseBytes( reader.ReadUInt16() );
        Coverage = MathUtils.ReverseBytes( reader.ReadUInt16() );
      }
      public override string ToString()
      {
        return String.Format( "Version = {0} Length = {1} Coverage = {2}", Version, Length, Coverage );
      }
    }

    internal class KerningTable_Format0
    {
      private UInt16 _nPairs;
      private UInt16 _searchRange;
      private UInt16 _entrySelector;
      private UInt16 _rangeShift;
      private Dictionary<UInt32, Int16> _kernPairs;
      public Dictionary<UInt32, Int16> KernPairs
      {
        get { return _kernPairs; }
      }


      public void ReadData( BinaryReader reader )
      {
        _nPairs = MathUtils.ReverseBytes( reader.ReadUInt16() );
        _searchRange = MathUtils.ReverseBytes( reader.ReadUInt16() );
        _entrySelector = MathUtils.ReverseBytes( reader.ReadUInt16() );
        _rangeShift = MathUtils.ReverseBytes( reader.ReadUInt16() );

        _kernPairs = new Dictionary<UInt32, Int16>( _nPairs );

        for ( int i = 0; i < _nPairs; ++i )
        {
          UInt16 left = MathUtils.ReverseBytes( reader.ReadUInt16() );
          UInt16 rigth = MathUtils.ReverseBytes( reader.ReadUInt16() );
          Int16 value = MathUtils.ReverseBytes( reader.ReadInt16() );
          UInt32 pair = MathUtils.ConcatShort( left, rigth );
          _kernPairs.Add( pair, value );
        }
      }
      public override string ToString()
      {
        return String.Format( "_nPairs = {0} _searchRange = {1} _entrySelector = {2} _rangeShift = {3}", _nPairs, _searchRange, _entrySelector, _rangeShift );
      }
    }

    internal class ReadTTFException : Exception
    {
      public ReadTTFException( string message ) : base( message ) { }
    }
  }
}


