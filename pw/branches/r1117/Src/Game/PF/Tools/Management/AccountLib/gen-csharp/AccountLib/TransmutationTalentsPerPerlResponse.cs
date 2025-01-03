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

namespace AccountLib
{

  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class TransmutationTalentsPerPerlResponse : TBase
  {
    private RequestResult _result;
    private List<TransmutationTalentsPerPerl> _talentsPerPerlEvents;
    private int _talentsDefault;

    /// <summary>
    /// 
    /// <seealso cref="RequestResult"/>
    /// </summary>
    public RequestResult Result
    {
      get
      {
        return _result;
      }
      set
      {
        __isset.result = true;
        this._result = value;
      }
    }

    public List<TransmutationTalentsPerPerl> TalentsPerPerlEvents
    {
      get
      {
        return _talentsPerPerlEvents;
      }
      set
      {
        __isset.talentsPerPerlEvents = true;
        this._talentsPerPerlEvents = value;
      }
    }

    public int TalentsDefault
    {
      get
      {
        return _talentsDefault;
      }
      set
      {
        __isset.talentsDefault = true;
        this._talentsDefault = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool result;
      public bool talentsPerPerlEvents;
      public bool talentsDefault;
    }

    public TransmutationTalentsPerPerlResponse() {
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
            if (field.Type == TType.I32) {
              Result = (RequestResult)iprot.ReadI32();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 2:
            if (field.Type == TType.List) {
              {
                TalentsPerPerlEvents = new List<TransmutationTalentsPerPerl>();
                TList _list214 = iprot.ReadListBegin();
                for( int _i215 = 0; _i215 < _list214.Count; ++_i215)
                {
                  TransmutationTalentsPerPerl _elem216 = new TransmutationTalentsPerPerl();
                  _elem216 = new TransmutationTalentsPerPerl();
                  _elem216.Read(iprot);
                  TalentsPerPerlEvents.Add(_elem216);
                }
                iprot.ReadListEnd();
              }
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 3:
            if (field.Type == TType.I32) {
              TalentsDefault = iprot.ReadI32();
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
      TStruct struc = new TStruct("TransmutationTalentsPerPerlResponse");
      oprot.WriteStructBegin(struc);
      TField field = new TField();
      if (__isset.result) {
        field.Name = "result";
        field.Type = TType.I32;
        field.ID = 1;
        oprot.WriteFieldBegin(field);
        oprot.WriteI32((int)Result);
        oprot.WriteFieldEnd();
      }
      if (TalentsPerPerlEvents != null && __isset.talentsPerPerlEvents) {
        field.Name = "talentsPerPerlEvents";
        field.Type = TType.List;
        field.ID = 2;
        oprot.WriteFieldBegin(field);
        {
          oprot.WriteListBegin(new TList(TType.Struct, TalentsPerPerlEvents.Count));
          foreach (TransmutationTalentsPerPerl _iter217 in TalentsPerPerlEvents)
          {
            _iter217.Write(oprot);
          }
          oprot.WriteListEnd();
        }
        oprot.WriteFieldEnd();
      }
      if (__isset.talentsDefault) {
        field.Name = "talentsDefault";
        field.Type = TType.I32;
        field.ID = 3;
        oprot.WriteFieldBegin(field);
        oprot.WriteI32(TalentsDefault);
        oprot.WriteFieldEnd();
      }
      oprot.WriteFieldStop();
      oprot.WriteStructEnd();
    }

    public override string ToString() {
      StringBuilder sb = new StringBuilder("TransmutationTalentsPerPerlResponse(");
      sb.Append("Result: ");
      sb.Append(Result);
      sb.Append(",TalentsPerPerlEvents: ");
      sb.Append(TalentsPerPerlEvents);
      sb.Append(",TalentsDefault: ");
      sb.Append(TalentsDefault);
      sb.Append(")");
      return sb.ToString();
    }

  }

}
