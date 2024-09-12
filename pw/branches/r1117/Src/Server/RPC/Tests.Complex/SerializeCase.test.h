#pragma once

#include "../System/nstring.h"
#include "../System/nvector.h"

namespace SerializeTest
{
  struct CVec3
  {
    float x;
    float y;
    float z;
  };

  struct CVec2i
  {
    int x;
    int y;
  };

  struct Header : rpc::Data
  {
    SERIALIZE_ID();
    ZDATA
    int numLines;
    nstl::vector<int> numSubLines;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&numLines); f.Add(3,&numSubLines); return 0; }
  };

  struct PersonalInfo : rpc::Data
  {
    SERIALIZE_ID();
    ZDATA
    nstl::string name;
    nstl::vector<int> ages;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&name); f.Add(3,&ages); return 0; }
  };

  struct BaseData : rpc::Data
  {
    SERIALIZE_ID();
    ZDATA
    nstl::string basename;
    Header header;
    CVec3 pos;
    nstl::vector<PersonalInfo> infos;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&basename); f.Add(3,&header); f.Add(4,&pos); f.Add(5,&infos); return 0; }
  };

  
  REMOTE class Analyzer : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1(Analyzer, BaseObjectMT);
    RPC_ID();
    BaseData data;
  public:
    REMOTE const BaseData& Do ( const BaseData& rdata )
    {
      data = rdata;
      data.basename = "DoDone!";
      data.header.numLines += 10;
      for ( int i = 0; i < data.header.numSubLines.size(); i++ )
      {
        data.header.numSubLines[i] += 10;
      }
      data.pos.x = 11.0f;
      data.pos.y = 12.0f;
      data.pos.z = 13.0f;

      for ( int i = 0; i < data.infos.size(); i++ )
      {
        data.infos[i].name += "updated";
        for ( int k = 0; k < data.infos[i].ages.size(); k++ )
        {
          data.infos[i].ages[k] += 10;
        }
      }
      return data;
    }
  };
}
