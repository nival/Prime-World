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
    public class LegacyErrorConverter
    {
        // Data not transferred 
        public const string E_LGC_UNEXPECTED     = "1";        
        // User not found
        public const string E_LGC_INVALID_USER	= "003";
        // User blocked
        public const string E_LGC_ACCESS	    = "011";
        // CRC signature error
        public const string E_LGC_CRC	        = "004";
        // Invalid ClientID (service password)
        public const string E_LGC_INVALID_SERVICE= "006";
        // User for transmission can not be found
        public const string E_LGC_INVALID_ACCOUNT= "008";
        // Not enough money on main account
        public const string E_LGC_OVERDRAFT	    = "009";


        // Password error
        public const string E_LGC_PASSWORD	    = "39";


        public static string convert(ApiException.ErrorCode code)
        {
            switch (code)
            {
                case ApiException.ErrorCode.E_INVALID_ARG:
                case ApiException.ErrorCode.E_EMAIL_EXISTS:
                case ApiException.ErrorCode.E_USER_EXISTS:
                case ApiException.ErrorCode.E_UNKNOWN_PAYMENT_SYSTEM:
                case ApiException.ErrorCode.E_ALREADY_SUBSCRIBED:
                case ApiException.ErrorCode.E_UNSUBSCRIBED:
                case ApiException.ErrorCode.E_INVALID_PROMO:
                case ApiException.ErrorCode.E_UNEXPECTED:
                default:
                    return E_LGC_UNEXPECTED;
                case ApiException.ErrorCode.E_CRC:
                    return E_LGC_CRC;
                case ApiException.ErrorCode.E_INVALID_USER:
                    return E_LGC_INVALID_USER;
                case ApiException.ErrorCode.E_INVALID_PASSWORD:
                    return E_LGC_PASSWORD;
                case ApiException.ErrorCode.E_OVERDRAFT:
                    return E_LGC_OVERDRAFT;
                case ApiException.ErrorCode.E_INVALID_SERVICE:
                    return E_LGC_INVALID_SERVICE;
                case ApiException.ErrorCode.E_ACCESS:
                    return E_LGC_ACCESS;
                case ApiException.ErrorCode.E_INVALID_ACCOUNT:
                    return E_LGC_INVALID_ACCOUNT;
            }
        }
    }
}
