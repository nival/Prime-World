#include "stdafx.h"
#include "../Render/VertexColorStream.h"
#include "../Scene/StaticSceneComponent.h"
#include "VertexColorManager.h"
#include "../System/ChunklessSaver.h"
#include "../System/InlineProfiler.h"

using namespace Render;

namespace NScene
{

namespace
{

  inline DWORD GetSceneCompCRC(StaticSceneComponent *comp)
  {
    Crc32Checksum crc;
    comp->AddGeometryCRC(crc);
    return crc.Get();
  }

}

AutoPtr<MeshVertexColors> MeshVertexColorsManager::RequestVertexColorStream(int componentIdx, StaticSceneComponent *comp)
{
  struct Local
  {
    static bool FillBuffer(DXVertexBufferRef& vb, const vector<Render::Color>& colors)
    {
      NI_VERIFY(sizeof(Render::Color) == sizeof(nival::uint32_t), "Color size mismatch", return false);

      const int size = sizeof(nival::uint32_t) * colors.size();

      vb = CreateVB(size, RENDER_POOL_MANAGED);

      if (!vb)
        return false;

      FillVB(Get(vb), size, &colors[0]);

      return true;
    }
  };

  NI_ASSERT(comp, "Component must already be created and initialized");

  if (m_bEditorMode)
  {
    return AutoPtr<MeshVertexColors>(new MeshVertexColors);
  }

  if (m_curAdvMapObjIdx == -1 || m_curSceneObjDBIDHash == 0)
  {
    return AutoPtr<MeshVertexColors>(NULL);
  }

  AutoPtr<MeshVertexColors> pMVC(new MeshVertexColors);

  if (m_curAdvMapObjIdx < m_objects.size())
  {
    TObjectColors::iterator it = m_objects[m_curAdvMapObjIdx].find(m_curSceneObjDBIDHash);

    if (it != m_objects[m_curAdvMapObjIdx].end())
    {
      if (componentIdx < (it->second).size())
      {
        TSceneCompColors &sc = it->second[componentIdx];

        const bool hasColors =
          !sc.colors0.empty() &&
          !sc.colors1.empty();

        if (hasColors)
        {
          // if signature approved copy colors from file
          // otherwise leave colors uninitialized
          const bool verified =
            (sc.colors0.size() == sc.colors1.size()) &&
            (sc.sign == GetSceneCompCRC(comp));

          if ( verified )
          {
            pMVC->numColors = sc.colors0.size();

            const bool loaded =
              Local::FillBuffer(pMVC->pVB1, sc.colors0) &&
              Local::FillBuffer(pMVC->pVB2, sc.colors1);

            if (loaded)
              return pMVC;
          }
          else
          {
            systemLog(NLogg::LEVEL_MESSAGE) << "Baked vertex colors signature mismatch. StaticSceneComponent(" << comp->FormatDescription() << ") will have default colors." << endl;
          }
        }
        else
        {
            systemLog(NLogg::LEVEL_MESSAGE) << "Baked lighting requested but color buffer is empty. StaticSceneComponent(" << comp->FormatDescription() << ") will have default colors." << endl;
        }
      }
      else
      {
        systemLog(NLogg::LEVEL_MESSAGE) << "Baked lighting requested but insufficient number of components in database. StaticSceneComponent(" << comp->FormatDescription() << ") will have default colors." << endl;
      }
    }
    else
    {
      systemLog(NLogg::LEVEL_MESSAGE) << "Baked lighting requested but scene object not found in database. StaticSceneComponent(" << comp->FormatDescription() << ") will have default colors." << endl;
    }
  }
  else
  {
    systemLog(NLogg::LEVEL_MESSAGE) << "Baked lighting requested but scene object not found in database. StaticSceneComponent(" << comp->FormatDescription() << ") will have default colors." << endl;
  }

  return AutoPtr<MeshVertexColors>(0);
}

void MeshVertexColorsManager::SceneComponentVCStore(int componentIdx, StaticSceneComponent *comp)
{
  NI_ASSERT(m_curAdvMapObjIdx != -1, "No AdvMapObject processing in progress");
  NI_ASSERT(m_curSceneObjDBIDHash != 0, "No SceneObject processing in progress");

  //DebugTrace( "%s", comp->GetDBID().GetId().c_str() );

  // create obj colors if needed
  if (m_curAdvMapObjIdx >= m_objects.size())
  {
    m_objects.resize(m_curAdvMapObjIdx + 1);
  }
  TSceneObjColors &sobj = m_objects[m_curAdvMapObjIdx][m_curSceneObjDBIDHash];

  // create scene component colors if needed
  if (componentIdx >= sobj.size())
  {
    sobj.resize(componentIdx + 1);
  }

  TSceneCompColors &sc = sobj[componentIdx];

  // store colors
  if (comp->GetVertexColors())
  {
    if (DXVertexBufferRef vb = comp->GetVertexColors()->pVB1)
    {
      D3DVERTEXBUFFER_DESC desc;
      vb->GetDesc(&desc);
      int numVertices = desc.Size / sizeof(Render::Color);

      Render::Color *colors = LockVB<Render::Color>(Get(vb), 0);

      sc.colors0.resize(numVertices);

      for (int j = 0; j < numVertices; ++j)
        sc.colors0[j] = colors[j];

      vb->Unlock();
    }

    if (DXVertexBufferRef vb = comp->GetVertexColors()->pVB2)
    {
      D3DVERTEXBUFFER_DESC desc;
      vb->GetDesc(&desc);
      int numVertices = desc.Size / sizeof(Render::Color);

      Render::Color *colors = LockVB<Render::Color>(Get(vb), 0);

      sc.colors1.resize(numVertices);

      for (int j = 0; j < numVertices; ++j)
        sc.colors1[j] = colors[j];

      vb->Unlock();
    }

    // calculate CRC
    sc.sign = GetSceneCompCRC(comp);
  }
}

void MeshVertexColorsManager::Save( const string& fileName )
{
	CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
	NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open vertex color file for writing %s", fileName ), return );
	
  pStream->SetSize( m_objects.size() * 4096 );
  CObj<IBinSaver> pSaver = CreateChunklessSaver( pStream, 0, false );// CreateWriteBinSaver(pStream, 0, false);
  pSaver->Add(1, &m_objects);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshVertexColorsManager::Load( const string& fileName )
{
  NI_PROFILE_FUNCTION

	CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	if( !pStream || !pStream->IsOk() )
  {
    return;
  }

  CObj<IBinSaver> pSaver = CreateChunklessSaver( pStream, 0, true );//CreateReadBinSaver(pStream, 0);
  pSaver->Add(1, &m_objects);
}

}