#pragma once

namespace Render
{
	enum ERenderLockType
	{
		LOCK_DISCARD,
		LOCK_NOOVERWRITE,
		LOCK_DEFAULT,
		LOCK_READONLY,
	};
}; // namespace Render
