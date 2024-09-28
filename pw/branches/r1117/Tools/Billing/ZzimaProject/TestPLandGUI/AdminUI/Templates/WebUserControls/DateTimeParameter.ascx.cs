using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Globalization;

namespace ZzimaBilling.AdminUI.Templates.WebUserControls
{
    public partial class DateTimeParameter : System.Web.UI.UserControl
    {
        private DateTime? value;
        
        public bool timeSign { get;set; }
        private bool _enabled = true;

        public DateTimeParameter()
        {
            timeSign = true;
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                FillHours(ddlTime);
                if (value == null)
                    value = DateTime.Now;
                RenderValue();
            }
            else
                DateTime = this.DateTime;

        }

        protected void FillHours(DropDownList ddl)
        {
            if (!timeSign)      
            {
                ddl.Visible = false;
                idTdTime.Visible = false;
                return;
            }

            ddl.Items.Clear();
            for (int i = 0; i <= 23; i++)
            {
                ddl.Items.Add(new ListItem(i.ToString() + ":00", i.ToString()));
            }
        }

        private void RenderValue()
        {
            if (datePicker == null)
                return;
            
            datePicker.Enabled = this.Enabled;

            if (value != null)
            {
                CultureInfo ci = CultureInfo.CreateSpecificCulture("en-GB");
                ci.DateTimeFormat.ShortDatePattern = "dd/MM/yyyy";
                ci.DateTimeFormat.DateSeparator = "-";
                datePicker.Text = value.Value.ToString("dd-MM-yyyy", ci);
            }
            else
                datePicker.Text = "";
        }

        public DateTime DateTime
        {
            get
            {
                if (value == null)
                    value = DateTime.Now;

                if (ddlTime == null || datePicker == null ||String.IsNullOrEmpty(datePicker.Text))
                    return value.Value;

                int hours = 0;
                if (ddlTime.SelectedIndex != -1)
                    hours = Int32.Parse(ddlTime.SelectedItem.Value);

                CultureInfo ci = CultureInfo.CreateSpecificCulture("en-GB");
                ci.DateTimeFormat.ShortDatePattern = "dd/MM/yyyy";
                ci.DateTimeFormat.DateSeparator = "-";

                DateTime dateTime = Convert.ToDateTime(datePicker.Text, ci);

                int year = dateTime.Year;
                int month = dateTime.Month;
                int day = dateTime.Day;

                value = new DateTime(dateTime.Year, dateTime.Month, dateTime.Day, hours, 0, 0);

                return value.Value;
            }

            set
            {
                RenderValue();
                this.value = value;
            }
        }

        public  bool Enabled
        {
            set
            {
                _enabled = value;
                cmpvDatePicker.Enabled = value;
                rfvDatePicker.Enabled = value;
            }
            get
            {
                return _enabled;
            }
        }

        //protected void cstvDatePicker_ServerValidate(object source, ServerValidateEventArgs args)
        //{
        //    string timeString = datePicker.Text;
        //    DateTime temp;
        //    args.IsValid = DateTime.TryParseExact(timeString, "dd-MM-yyyy", CultureInfo.InvariantCulture, DateTimeStyles.None, out temp);
        //}
    }
}
