/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using Thrift;
using Thrift.Collections;
using System.Runtime.Serialization;
using Thrift.Protocol;
using Thrift.Transport;

namespace StatisticCore.Thrift
{

  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class GuildDailyStatsVassalInfo : TBase
  {
    private long _guildid;
    private long _guildpoints;

    public long Guildid
    {
      get
      {
        return _guildid;
      }
      set
      {
        __isset.guildid = true;
        this._guildid = value;
      }
    }

    public long Guildpoints
    {
      get
      {
        return _guildpoints;
      }
      set
      {
        __isset.guildpoints = true;
        this._guildpoints = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool guildid;
      public bool guildpoints;
    }

    public GuildDailyStatsVassalInfo() {
    }

    public void Read (TProtocol iprot)
    {
      TField field;
      iprot.ReadStructBegin();
      while (true)
      {
        field = iprot.ReadFieldBegin();
        if (field.Type == TType.Stop) { 
          break;
        }
        switch (field.ID)
        {
          case 1:
            if (field.Type == TType.I64) {
              Guildid = iprot.ReadI64();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 2:
            if (field.Type == TType.I64) {
              Guildpoints = iprot.ReadI64();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          default: 
            TProtocolUtil.Skip(iprot, field.Type);
            break;
        }
        iprot.ReadFieldEnd();
      }
      iprot.ReadStructEnd();
    }

    public void Write(TProtocol oprot) {
      TStruct struc = new TStruct("GuildDailyStatsVassalInfo");
      oprot.WriteStructBegin(struc);
      TField field = new TField();
      if (__isset.guildid) {
        field.Name = "guildid";
        field.Type = TType.I64;
        field.ID = 1;
        oprot.WriteFieldBegin(field);
        oprot.WriteI64(Guildid);
        oprot.WriteFieldEnd();
      }
      if (__isset.guildpoints) {
        field.Name = "guildpoints";
        field.Type = TType.I64;
        field.ID = 2;
        oprot.WriteFieldBegin(field);
        oprot.WriteI64(Guildpoints);
        oprot.WriteFieldEnd();
      }
      oprot.WriteFieldStop();
      oprot.WriteStructEnd();
    }

    public override string ToString() {
      StringBuilder sb = new StringBuilder("GuildDailyStatsVassalInfo(");
      sb.Append("Guildid: ");
      sb.Append(Guildid);
      sb.Append(",Guildpoints: ");
      sb.Append(Guildpoints);
      sb.Append(")");
      return sb.ToString();
    }

  }

}
