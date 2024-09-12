using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Globalization;

namespace ZzimaBilling.AdminUI.Templates.WebUserControls
{
    public partial class NumericalControl : System.Web.UI.UserControl
    {
        #region Constants

        public const decimal MIN = 0;
        public const decimal MAX = int.MaxValue;

        #endregion


        #region Properties

        /// <summary>
        /// Minimum value
        /// </summary>
        public decimal From
        {
            get
            {
                NumericalControlResult res = GetData();
                return res != null ? res.FromValue : 0;
            }
        }

        /// <summary>
        /// Maximum value
        /// </summary>
        public decimal To
        {
            get
            {
                NumericalControlResult res = GetData();
                return res != null ? res.ToValue : 0;
            }
        }

        /// <summary>
        /// Current mode of filtering
        /// </summary>
        private NumericalControlMode Mode
        {
            get
            {
                string currentValue = this.Request.Form.Get(this.ClientID + "_ddl");
                return currentValue.ToNumericalControlMode();
            }
        }

        public string SelectedValue
        {
            get
            {
                if (ViewState["SelectedValue"] == null)
                    return "any";
                else
                    return ViewState["SelectedValue"].ToString();
            }
            set
            {
                ViewState["SelectedValue"] = value;
            }
        }


        #endregion

        private NumericalControlResult GetData()
        {
            if (!IsValid())
                return null;

            NumericalControlResult res = new NumericalControlResult();

            switch (Mode)
            {
                case NumericalControlMode.Equal:
                    res.FromValue = ParseValue(tbxFirst.Text);
                    res.ToValue = ParseValue(tbxFirst.Text);
                    break;
                case NumericalControlMode.Range:
                    res.FromValue = ParseValue(tbxFirst.Text);
                    res.ToValue = ParseValue(tbxSecond.Text);
                    break;

                case NumericalControlMode.LessThan:
                    res.ToValue = ParseValue(tbxFirst.Text);
                    break;
                case NumericalControlMode.GreatThan:
                    res.FromValue = ParseValue(tbxFirst.Text);
                    break;
                case NumericalControlMode.Any:
                default:
                    break;
            }
            return res;
        }

        //Validation Method for control
        public bool IsValid()
        {
           
                switch (Mode)
                {
                    case NumericalControlMode.Any:
                        return true;

                    case NumericalControlMode.Equal:
                        {
                            try
                            {
                                return (!(string.IsNullOrEmpty(tbxFirst.Text)) && Convert.ToDecimal(tbxFirst.Text) >= 0);
                            }
                            catch (Exception)
                            {
                                return false;
                            }
                        }

                    case NumericalControlMode.Range:
                        {
                            try
                            {
                                return !(string.IsNullOrEmpty(tbxFirst.Text)) && Convert.ToDecimal(tbxFirst.Text) >= 0
                                    && !(string.IsNullOrEmpty(tbxSecond.Text)) && Convert.ToDecimal(tbxSecond.Text) >= 0
                                    && ((Convert.ToDecimal(tbxSecond.Text) >= Convert.ToDecimal(tbxFirst.Text)));
                            }
                            catch (Exception)
                            {
                                return false;
                            }
                        }

                    case NumericalControlMode.LessThan:
                        {
                            try
                            {
                                return (!(string.IsNullOrEmpty(tbxFirst.Text)) && Convert.ToDecimal(tbxFirst.Text) > 0);
                            }
                            catch (Exception)
                            {
                                return false;
                            }
                        }

                    case NumericalControlMode.GreatThan:
                        {
                            try
                            {
                                return (!(string.IsNullOrEmpty(tbxFirst.Text)) && Convert.ToDecimal(tbxFirst.Text) >= 0);
                            }
                            catch (Exception)
                            {
                                return false;
                            }
                        }
                    default:
                        return true;
              
            }
        }

        //Validation Method for list of controls
        public static bool IsValid(List<NumericalControl> list)
        {
            foreach (var item in list)
            {
                if (!item.IsValid())
                    return false;
            }
            return true;
        }

        private decimal ParseValue(String tbx)
        {
            return Convert.ToDecimal(tbx);
        }

        protected void Page_Load(object sender, EventArgs e)
        {

            if (IsPostBack)///Íóæíî ïðîèíèöèàëèçèðîâàòü âûáðàííîå çíà÷åíèå èëè óñòàíîâèòü äåôîëòíîå
                SelectedValue = this.Request.Form.Get(this.ClientID + "_ddl");
            lblError.Visible = !IsValid();
        }
    }

    public enum NumericalControlMode
    {
        Any,
        LessThan,
        GreatThan,
        Equal,
        Range
    }

    public class NumericalControlResult
    {
        public decimal FromValue { get; set; }
        public decimal ToValue { get; set; }
        public NumericalControlResult()
        {
            FromValue = NumericalControl.MIN;
            ToValue = NumericalControl.MAX;
        }
    }

    public static class HelperClass
    {
        public static NumericalControlMode ToNumericalControlMode(this string strMode)
        {
            switch (strMode)
            {
                case "lessthan":
                    return NumericalControlMode.LessThan;
                case "greatthan":
                    return NumericalControlMode.GreatThan;
                case "equal":
                    return NumericalControlMode.Equal;
                case "range":
                    return NumericalControlMode.Range;
                default:
                    return NumericalControlMode.Any;
            }
        }
    }
}
