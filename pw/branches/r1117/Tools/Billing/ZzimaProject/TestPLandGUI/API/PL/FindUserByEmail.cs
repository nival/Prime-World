using System.IO;
using ZzimaBilling.API.Common;

namespace ZzimaBilling.API.PL
{
    //record for findUserByEmail
    public class UsernameAndPartnerRecord
    {
        public string userName;
        public string partnerName;
    }
    
    public class FindUserByEmailReq : ServiceRequest
    {
        public string email;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, email);
            return stm;
        }
        public override void validate()
        {
            base.validate();

            if (email == null || (email.Trim().Length == 0))
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Some of required fields are empty");
        }
    }

    public class FindUserByEmailResponse : Response
    {
        public UsernameAndPartnerRecord[] userAndPartners; 
    }
}