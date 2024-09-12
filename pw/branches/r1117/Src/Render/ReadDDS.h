#pragma once

namespace Render {
HRESULT CreateTextureFromDDSFileInMemory(const char *_data, UINT _dataSize, UINT _skipMipLevels, PDIRECT3DBASETEXTURE9* _ppTex);
} // namespace Render