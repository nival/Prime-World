#include "stdafx.h"
#include "dxutils.h"
#include "smartrenderer.h"
#include "MeshResource.h"
#include "MaterialSpec.h"
#include "VertexColorStream.h"

namespace Render
{

void MeshVertexColors::Bind(int /*primIndex*/)
{
  if (pVB1)
    SmartRenderer::BindVertexBuffer(1U, Get(pVB1), sizeof(unsigned int), 0U);

  if (pVB2)
    SmartRenderer::BindVertexBuffer(2U, Get(pVB2), sizeof(unsigned int), 0U);
}

void MeshVertexColors::InitializeBuffer(const MeshGeometry &mesh, bool fake)
{
  struct Local
  {
    static bool InitializeBuffer(DXVertexBufferRef& vb, const unsigned numVertices, const bool fake)
    {
      vb = CreateVB(numVertices * sizeof(nival::uint32_t), RENDER_POOL_MANAGED);

      if (!vb)
        return false;

      nival::uint32_t* pColors = LockVB<nival::uint32_t>(Get(vb), 0U);

      NI_VERIFY(pColors != NULL, "Unable to lock vertex buffer when assigning vertex colors.", return false);

      nstl::fill_n(pColors, numVertices, (fake ? 0x01000000U : 0x01FFFFFFU));

      vb->Unlock();

      return true;
    }
  };

  NI_ASSERT(mesh.fragmentCount != 0, "Mesh contains no primitives when trying to assign vertex colors. Should be checked earlier.");

  // already initialized (e.g. read from file in game)
	if (numColors > 0 && !fake)
		return;

  // otherwise it seems we're in editor (?)
  // then we need to allocate vertex buffer for colors and initialize it with white

  // we rely on the fact that there's single VB for the whole mesh (checked below)
  DXVertexBufferRef vb = mesh.primitives[0]->GetVertexBuffer();

  // also, size of VB is equal to the total number of vertices in all primitives
  unsigned int numVertices = 0;
  for (unsigned short i = 0; i < mesh.fragmentCount; ++i)
  {
    NI_VERIFY(mesh.primitives[i]->GetVertexBuffer() == vb, "Primitives in mesh use different vertex buffer which is unexpected.", return);
    numVertices += mesh.primitives[i]->GetDipDescriptor().numVertices;
  }

  // allocate additional color buffer
  const bool ok =
    Local::InitializeBuffer(pVB1, numVertices, fake) &&
    Local::InitializeBuffer(pVB2, numVertices, fake);

  if (ok)
    numColors = numVertices;
}

}
