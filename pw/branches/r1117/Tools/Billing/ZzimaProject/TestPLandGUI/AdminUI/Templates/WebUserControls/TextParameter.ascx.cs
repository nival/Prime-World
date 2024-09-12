using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using ZzimaBilling.AdminUI.Templates.WebUserControls;

namespace ZzimaBilling.UI
{
    public partial class TextParameter : System.Web.UI.UserControl
    {
        public string ParameterTitle
        {
            get { return lblParameterName.Text; }
            set { lblParameterName.Text = value; }
        }

        public string ParameterValue
        {
            get { return tbxParameterValue.Text; }
            set { tbxParameterValue.Text = value; }
        }
    }
}