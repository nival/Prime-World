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
  public partial class BroadcastMessage : TBase
  {
    private string _Locale;
    private string _Text;

    public string Locale
    {
      get
      {
        return _Locale;
      }
      set
      {
        __isset.Locale = true;
        this._Locale = value;
      }
    }

    public string Text
    {
      get
      {
        return _Text;
      }
      set
      {
        __isset.Text = true;
        this._Text = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool Locale;
      public bool Text;
    }

    public BroadcastMessage() {
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
            if (field.Type == TType.String) {
              Locale = iprot.ReadString();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 2:
            if (field.Type == TType.String) {
              Text = iprot.ReadString();
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
      TStruct struc = new TStruct("BroadcastMessage");
      oprot.WriteStructBegin(struc);
      TField field = new TField();
      if (Locale != null && __isset.Locale) {
        field.Name = "Locale";
        field.Type = TType.String;
        field.ID = 1;
        oprot.WriteFieldBegin(field);
        oprot.WriteString(Locale);
        oprot.WriteFieldEnd();
      }
      if (Text != null && __isset.Text) {
        field.Name = "Text";
        field.Type = TType.String;
        field.ID = 2;
        oprot.WriteFieldBegin(field);
        oprot.WriteString(Text);
        oprot.WriteFieldEnd();
      }
      oprot.WriteFieldStop();
      oprot.WriteStructEnd();
    }

    public override string ToString() {
      StringBuilder sb = new StringBuilder("BroadcastMessage(");
      sb.Append("Locale: ");
      sb.Append(Locale);
      sb.Append(",Text: ");
      sb.Append(Text);
      sb.Append(")");
      return sb.ToString();
    }

  }

}
