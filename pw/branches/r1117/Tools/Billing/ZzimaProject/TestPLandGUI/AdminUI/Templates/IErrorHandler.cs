using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ZzimaBilling.AdminUI.Templates
{
    interface IErrorHandler
    {
        void showMessage(bool err, string shortMsg, string fullMsg);
        void resetMessage();
    }
}
