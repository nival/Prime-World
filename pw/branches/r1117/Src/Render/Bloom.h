#pragma once

namespace Render {

class Bloom
{
public:
  Bloom();
  ~Bloom();

  bool Prepare(Texture2DRef const& pTexture);

  Texture2D* GetBlendSource();

private:
	void InitKernels();
	void MakePass(char const* pShaderName);

private:
	Render::Texture2DRef pBuffer[2];
	int curIdx;

	float exposure;
	float sigma;

	static const int KERNEL_SIZE = 7;
	CVec4 kernelH[1 + KERNEL_SIZE / 2];
	CVec4 kernelV[1 + KERNEL_SIZE / 2];
};

} // namespace Render
