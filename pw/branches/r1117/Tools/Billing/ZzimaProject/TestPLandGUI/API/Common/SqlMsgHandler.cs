using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.SqlClient;

namespace ZzimaBilling.API.Common
{
    public class SqlMsgHandler
    {
        public string msg = "";
        public void conn_InfoMessage(object sender, SqlInfoMessageEventArgs e)
        {
            foreach (SqlError err in e.Errors)
            {
                if (err.Class < 16)
                    continue;
                msg += err.Message + "\n";
            }
        }
    }
}
