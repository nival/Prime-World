using System;
using System.Data;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.DAL;
using System.Collections.Generic;
using System.Text;


namespace ZzimaBilling.SL
{
    public class ZzimaMembershipProvider : MembershipProvider
    {
        private String _strName;
        private String _strApplicationName;
        private Boolean _boolEnablePasswordReset;
        private Boolean _boolEnablePasswordRetrieval;
        private Boolean _boolRequiresQuestionAndAnswer;
        private Boolean _boolRequiresUniqueEMail;
        //private int _iPasswordAttemptThreshold;
        private MembershipPasswordFormat _oPasswordFormat = new MembershipPasswordFormat();

	    public ZzimaMembershipProvider()
        {
            _strName = "";
            _strApplicationName = "";

            _boolRequiresQuestionAndAnswer = false;
            _boolEnablePasswordReset = false;
            _boolEnablePasswordRetrieval = false;
            _boolRequiresQuestionAndAnswer = false;
            _boolRequiresUniqueEMail = false;
        } 

    	public override void Initialize(string strName, System.Collections.Specialized.NameValueCollection config)
	    {
            _strName = strName;
            _strApplicationName = "/";

            _boolRequiresQuestionAndAnswer=false;
            _boolEnablePasswordReset = true;
            _boolEnablePasswordRetrieval = true;
            _boolRequiresQuestionAndAnswer=false ;
            _boolRequiresUniqueEMail=true;
	    }

        public override bool ValidateUser(string username, string password)
        {
            bool bRes = false;
            try
            {
                Employer adm = EmployeeDAL.Authorize(username, password);
                System.Web.HttpContext.Current.Session[Employer.SESSION_KEY] = adm;
                bRes = true;
            }
            catch (Exception)
            {
            }
            return bRes;
        }

	    public override string GetPassword(string strName, string strAnswer)
	    {
		    throw new Exception("The method or operation is not implemented.");
	    }

        public override string ApplicationName
        {
            get
            {
                return _strApplicationName;
            }
            set
            {
                _strApplicationName = value;
            }
        }

        public override string Name
        {
            get
            {
                return _strName;
            }
        }

        public override bool EnablePasswordReset
        {
            get
            {

                return _boolEnablePasswordReset;
            }
        }

        public override bool EnablePasswordRetrieval
        {
            get
            {
                return _boolEnablePasswordRetrieval;
            }
        }

        public override int MaxInvalidPasswordAttempts
        {
            get { throw new NotImplementedException(); }
        }

        public override int MinRequiredPasswordLength
        {
            get { throw new NotImplementedException(); }
        }

        public override int MinRequiredNonAlphanumericCharacters
        {
            get { throw new NotImplementedException(); }
        }

        public override string PasswordStrengthRegularExpression
        {
            get { throw new NotImplementedException(); }
        }

        public override MembershipPasswordFormat PasswordFormat
        {
            get
            {
                return _oPasswordFormat;
            }
        }

        public override bool RequiresQuestionAndAnswer
        {
            get
            {
                return _boolRequiresQuestionAndAnswer;
            }
        }

        public override int PasswordAttemptWindow
        {
            get 
            { 
                throw new Exception("The method or operation is not implemented."); 
            }
        }

        public override bool RequiresUniqueEmail
        {
            get
            {
                return _boolRequiresUniqueEMail;
            }
        }

        public override MembershipUser CreateUser(	
			string username, 
	                string password, 
	                string email, 
	                string passwordQuestion, 
	                string passwordAnswer, 
	                bool isApproved, 
	                object userId, 
	                out MembershipCreateStatus status)
        {
            throw new Exception("The method or operation is not implemented."); 
        }

        public override string GetUserNameByEmail(string strEmail)
        {
            throw new Exception("The method or operation is not implemented."); 
        }
       
	    public override string ResetPassword(string strName, string strAnswer)
	    {
            throw new Exception("The method or operation is not implemented."); 
	    }

	    public override bool ChangePassword(string strName, string strOldPwd, string strNewPwd)
	    {
            throw new Exception("The method or operation is not implemented."); 
	    }

	    public override int GetNumberOfUsersOnline()
	    {
            throw new Exception("The method or operation is not implemented."); 
	    }

	    public override bool ChangePasswordQuestionAndAnswer(string strName, string strPassword, string strNewPwdQuestion, string strNewPwdAnswer)
	    {	
	        throw new Exception("The method or operation is not implemented.");
	    }

	    public override MembershipUser GetUser(string strName, bool boolUserIsOnline)
	    {
           throw new Exception("The method or operation is not implemented."); 
	    }

	    public override bool DeleteUser(string strName, bool boolDeleteAllRelatedData)
	    {
            throw new Exception("The method or operation is not implemented.");
        }

	    public override MembershipUserCollection FindUsersByEmail(string strEmailToMatch, int iPageIndex, int iPageSize, out int iTotalRecords)
	    {
            throw new Exception("The method or operation is not implemented.");
	    }

	    public override MembershipUserCollection FindUsersByName(string strUsernameToMatch, int iPageIndex, int iPageSize, out int iTotalRecords)
	    {
            throw new Exception("The method or operation is not implemented.");
	    }

	    public override MembershipUserCollection GetAllUsers(int iPageIndex, int iPageSize, out int iTotalRecords)
	    {
            throw new Exception("The method or operation is not implemented.");
	    }

        public override void UpdateUser(MembershipUser user)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        public override bool UnlockUser(string strUserName)
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public override MembershipUser GetUser(object providerUserKey, bool userIsOnline)
        {
            throw new Exception("The method or operation is not implemented.");
        }
    }
}
