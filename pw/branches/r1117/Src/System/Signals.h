#pragma once

namespace Signals {

  // перехватываем abort (который у нас любит делать кое-кто, не будем показывать пальцем, но это ACE/IOTerabit)
  void CatchAbort();

} // namespace Signals
