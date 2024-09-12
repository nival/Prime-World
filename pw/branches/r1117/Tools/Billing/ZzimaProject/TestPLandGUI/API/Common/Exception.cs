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

namespace ZzimaBilling.API.Common
{
    /**
     * Base class for API exceptions 
     */
    public class ApiException : Exception
    {
        /**
         * Possible error codes
         */
        public enum ErrorCode
        {
            /** Incorrect parameters */
            E_INVALID_ARG = -1000,
            /** Incorrect CRC/unable to authorize request source */
            E_CRC = -1001,
            /** User with such email already exists */
            E_EMAIL_EXISTS = -1002,
            /** User with such name already exists */
            E_USER_EXISTS = -1003,
            /** No such user */
            E_INVALID_USER = -1004,
            /** Invalid user name or password */
            E_INVALID_PASSWORD = -1005,
            /** Unknown payments system */
            E_UNKNOWN_PAYMENT_SYSTEM = -1006,
            /** Cannot find account or this account id conflicts with other parameters */
            E_INVALID_ACCOUNT = -1007,
            /** Insufficient founds */
            E_OVERDRAFT = -1008,
            /** Service already subscribed */
            E_ALREADY_SUBSCRIBED = -1009,
            /** Service non-subscribed */
            E_UNSUBSCRIBED = -1010,
            /** No service with such name */
            E_INVALID_SERVICE = -1011,
            /** ban, access denied or fraud detected */
            E_ACCESS = -1012,
            /** invalid promo-code */
            E_INVALID_PROMO = -1013,

            E_UNEXPECTED = -2000

        };

        private int _code;
        private string _description;

        public int code {   get
            {
                return _code;
            }
        }

        public string description
        {
            get
            {
                return _description;
            }
        }

        public ApiException(int cd)
            : this((int)cd, "")
        {
        }

        public ApiException(ErrorCode cd, string description)
            : this((int)cd,description)
        {
        }
        
        public ApiException(int cd, string description)
            : base(getCodeDescription(cd) + " ( " + cd + " )" 
                + ((description!=null && description.Length != 0)?(" :[" + description + "]"):""))
        {


            _code = cd;
            _description = description;
        }

        protected static string getCodeDescription(int code)
        {
            switch ((ErrorCode)code)
            {
                case ErrorCode.E_INVALID_ARG:
                    return "Invalid arguments";
                case ErrorCode.E_CRC:
                    return "Invalid CRC validation result";
                case ErrorCode.E_EMAIL_EXISTS:
                    return "Email with the same name already exists";
                case ErrorCode.E_USER_EXISTS:
                    return "User with the same name already exists";
                case ErrorCode.E_INVALID_USER:
                    return "No user with such name";
                case ErrorCode.E_INVALID_PASSWORD:
                    return "Invalid password";
                case ErrorCode.E_UNKNOWN_PAYMENT_SYSTEM:
                    return "Unknown payment system";
                case ErrorCode.E_INVALID_ACCOUNT:
                    return "Invalid account";
                case ErrorCode.E_OVERDRAFT:
                    return "Insufficient founds";
                case ErrorCode.E_ALREADY_SUBSCRIBED:
                    return "User already subscribed to service";
                case ErrorCode.E_UNSUBSCRIBED:
                    return "User does not subscribed to service";
                case ErrorCode.E_INVALID_SERVICE:
                    return "No service with such name/id";
                case ErrorCode.E_ACCESS:
                    return "Access denied";
                case ErrorCode.E_INVALID_PROMO:
                    return "Invalid promo-code";
                default:
                case ErrorCode.E_UNEXPECTED:
                    return "Unexpected error";

            }
        }
    }
}
