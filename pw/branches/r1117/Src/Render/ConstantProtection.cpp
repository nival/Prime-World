#pragma once

#include "stdafx.h"
#include "ConstantProtection.h"

namespace Render
{

ConstantProtectionChecker::ConstantProtectionChecker()
	: currentConstantContext(CCONTEXT_NOT_PROTECTED)
{
	memset(constantsContext, 0, sizeof(ConstantInfo) * MAX_CONSTANTS);
}

void ConstantProtectionChecker::SetShaderConstants(unsigned int begin, unsigned int count, int shaderType)
{
	for (unsigned int i = 0; i < count; i++)
	{
		ContextType &context = constantsContext[i+begin].context[shaderType];
		NI_ASSERT(context == currentConstantContext || context == CCONTEXT_NOT_PROTECTED, "Writing to protected constant");
		context = currentConstantContext;
	}
}

void ConstantProtectionChecker::Reset(ContextType context)
{
	for (int i = 0; i < MAX_CONSTANTS; i++)
	{
		if (constantsContext[i].context[0] == context)
			constantsContext[i].context[0] = CCONTEXT_NOT_PROTECTED;
		if (constantsContext[i].context[1] == context)
			constantsContext[i].context[1] = CCONTEXT_NOT_PROTECTED;
	}
}

}