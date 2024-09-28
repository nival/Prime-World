#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/utils/ByteArray.h"
#include "../Natives/utils/ObjectInput.h"
#include "../Natives/utils/ObjectOutput.h"
#include "ByteArray_builtin.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetByteArrayPool(AvmCore * core)
  {
    return AVM_INIT_BUILTIN_ABC(ByteArray_builtin, core);
  }
}
