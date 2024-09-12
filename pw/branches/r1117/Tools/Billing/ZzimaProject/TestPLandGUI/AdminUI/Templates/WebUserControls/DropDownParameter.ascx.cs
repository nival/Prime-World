using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using ZzimaBilling.AdminUI.Templates.WebUserControls;

namespace ZzimaBilling.UI
{
    public partial class DropDownParameter : System.Web.UI.UserControl
    {
        public string ParameterTitle
        {
            get { return lblParameterName.Text; }
            set { lblParameterName.Text = value; }
        }

        public string ParameterValueText
        {
            get { return ddlValues.SelectedItem.Text; }
        }

        public string ParameterValue
        {
            get { return ddlValues.SelectedItem.Value; }
        }
        
        
        protected void Page_Load(object sender, EventArgs e)
        {
            ddlValues.SelectedIndex = 1;
        }

        public override void DataBind()
        {
            base.DataBind();
        }
    }
}