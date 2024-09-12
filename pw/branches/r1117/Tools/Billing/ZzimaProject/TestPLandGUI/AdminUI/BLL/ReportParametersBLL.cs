using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Microsoft.Reporting.WebForms;

namespace ZzimaBilling.AdminUI.BLL
{
    public class ReportParametersBLL
    {
        public string ReportName { get; set; }
        public string ReportTitle { get; set; }
        public List<ReportParameter> Parameters { get; set; }

        public ReportParametersBLL()
        {
            Parameters = new List<ReportParameter>();
        }

        private void AddParameter(ReportParameter reportParameter)
        {
            if (reportParameter != null)
            {
                Parameters.Add(reportParameter);
            }
        }

        public void AddParameter(string parameterName, string parameterValue)
        {
            if (!string.IsNullOrEmpty(parameterName))
            {
                ReportParameter reportParameter = new ReportParameter(parameterName, parameterValue);
                AddParameter(reportParameter);
            }
        }

        public void AddParameterWithNullValue(string parameterName)
        {
            if (!string.IsNullOrEmpty(parameterName))
            {
                ReportParameter reportParameter = new ReportParameter(parameterName);
                reportParameter.Values[0] = null;
                AddParameter(reportParameter);
            }
        }

        public void AddParameter(string parameterName, List<string> parameterValues)
        {
            if (!string.IsNullOrEmpty(parameterName)&&parameterValues.Count>0)
            {
                ReportParameter reportParameter = new ReportParameter(parameterName);
                foreach (var parameterValue in parameterValues)
                    reportParameter.Values.Add(parameterValue);
                AddParameter(reportParameter);
            }
        }

        public void AddParameter(string parameterName, List<int> parameterValues)
        {
            if (!string.IsNullOrEmpty(parameterName) && parameterValues.Count > 0)
            {
                ReportParameter reportParameter = new ReportParameter(parameterName);
                foreach (var parameterValue in parameterValues)
                    reportParameter.Values.Add(parameterValue.ToString());
                AddParameter(reportParameter);
            }
        }

        public void ClearReportParameters()
        {
            Parameters = new List<ReportParameter>();
        }
    }
}
