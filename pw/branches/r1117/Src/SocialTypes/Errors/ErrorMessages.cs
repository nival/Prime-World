

using System.Collections.Generic;
using libdb.DB;

namespace SocialTypes.DBTypes
{
  [IndexField( "ErrorCode", true )]
  public class ErrorKeyMessagePair
  {
    public int ErrorCode;
    public ErrorMessage Message;
  }

  public class ErrorMessage
  {
    public bool CloseApplicationAfterDialog = false;
    public TextRef Text;
  }

  public class ErrorMessagesTable : DBResource
  {
    public List<ErrorKeyMessagePair> Errors = new List<ErrorKeyMessagePair>();
  }
}
