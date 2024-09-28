using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Xml;

namespace ZzimaBilling.API.Legacy.Command
{
    public abstract class ILegacyCommand
    {
        protected XmlNode request;

        public ILegacyCommand(XmlNode nd)
        {
            request = nd;
        }
        
        public abstract void Execute(HttpContext context);
    }
}
