using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ControlCenter.Areas.GM
{
    public struct ASPNETKeyValuePair<TKey, TValue>
    {
        public TKey Key { set; get; }
        public TValue Value { set; get; }
    }
}
