#pragma once

namespace Render
{

// Constant context
enum ContextType
{
	CCONTEXT_NOT_PROTECTED  = 0,
	CCONTEXT_GLOBALCONSTANT,
	CCONTEXT_RENDER_TIME,
	CCONTEXT_WATER,
	CCONTEXT_TERRAIN,
	CCONTEXT_USER
};

class ConstantProtectionChecker
{
public:
	ConstantProtectionChecker();

	void BeginBlock(ContextType context) { currentConstantContext = context; }
	void EndBlock() { currentConstantContext = CCONTEXT_NOT_PROTECTED; }
	void Reset(ContextType context);

	void SetVertexShaderConstants(unsigned int begin, unsigned int count) { SetShaderConstants(begin, count, 0); }
	void SetPixelShaderConstants(unsigned int begin, unsigned int count) { SetShaderConstants(begin, count, 1); }

private:
	void SetShaderConstants(unsigned int begin, unsigned int count, int shaderType);

	enum { MAX_CONSTANTS = 256 };

	struct ConstantInfo
	{
		ContextType context[2];
	};

	ContextType currentConstantContext;
	ConstantInfo constantsContext[MAX_CONSTANTS];
};

}