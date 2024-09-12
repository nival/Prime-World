using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using ZZServiceClient.ZZServiceReference;


namespace ZZServiceClient
{
  class Program
  {
    static byte[] emptycrc = new byte[16];

    static void Main(string[] args)
    {
      var zzima = new ZZServiceWebSoapClient();
      
      if (args.Length == 0)
      {
        Console.WriteLine("Incorrect arguments");
        return;
      }

      switch (args[0])
      {
        case "register":
          var req_register = new RegisterUserReq
                               {
                                 userName = "user_0001",
                                 userPassword = MD5.Create().ComputeHash(Encoding.UTF8.GetBytes("0001")),
                                 userEmail = "user_0001@nival.com",
                                 fromServiceName = "pw",
                                 crc = MD5.Create().ComputeHash(Encoding.UTF8.GetBytes("password"))
                               };
          Console.WriteLine("RegisterUser request: userName={0}, userEmail={1}", req_register.userName, req_register.userEmail);
          var resp_register = zzima.RegisterUser(req_register);
          Console.WriteLine("RegisterUser response: accountName={0}, userId={1}, code={2}, message={3}",
                            resp_register.accountName, resp_register.userId, resp_register.code, resp_register.message);
          break;

        case "balance":
          var req_balance = new GetUserBalanceReq
                              {
                                userName = "user_0001",
                                fromServiceName = "pw",
                                crc = emptycrc
                              };
          Console.WriteLine("GetUserBalance request: userName={0}", req_balance.userName);
          var resp_balance = zzima.GetUserBalance(req_balance);
          Console.WriteLine("GetUserBalance response: amount={0}, code={1}, message={2}",
                            resp_balance.amount, resp_balance.code, resp_balance.message);

          break;

        case "replenish":
          var req_replenish = new AccountReplenishmentReq
                          {
                            amount = 135,
                            paymentSystem = "RM-1",
                            fromServiceName = "pw",
                            reason = "test operation",
                            userName = "user_0001",
                            crc = emptycrc
                          };
          Console.WriteLine("AccountReplenish request: userName={0}, paymentSystem={1}, amount={2}",
                            req_replenish.userName, req_replenish.paymentSystem, req_replenish.amount);
          var resp_replenish = zzima.AccountReplenish(req_replenish);
          Console.WriteLine("AccountReplenish response: code={0}, message={1}",
                            resp_replenish.code, resp_replenish.message);
          break;

        case "writeoff":
          var req_writeoff = new AccountWriteOffReq
                               {
                                 amount = 50,
                                 fromServiceName = "pw",
                                 reason = "test writeoff",
                                 userName = "user_0001",
                                 crc = emptycrc
                               };
          Console.WriteLine("AccountWriteOff request: userName={0}, amount={1}",
                            req_writeoff.userName, req_writeoff.amount);
          var resp_writeoff = zzima.AccountWriteOff(req_writeoff);
          Console.WriteLine("AccountWriteOff response: code={0}, message={1}",
                            resp_writeoff.code, resp_writeoff.message);
          break;

        case "reserve":
          var req_reserve = new ReserveAmountReq
                              {
                                amount = 20,
                                fromServiceName = "pw",
                                reason = "test reserve amount",
                                userName = "user_0001",
                                crc = emptycrc
                              };
          Console.WriteLine("ReserveAmount request: userName={0}, amount={1}",
                            req_reserve.userName, req_reserve.amount);
          var resp_reserve = zzima.ReserveAmount(req_reserve);
          Console.WriteLine("ReserveAmount response: reserveId={0}, code={1}, message={2}",
                            resp_reserve.reserveId, resp_reserve.code, resp_reserve.message);
          break;

        case "confirm":
          if (args.Length < 2) break;


          var req_confirm = new ConfirmWriteOffReq()
                              {
                                fromServiceName = "pw",
                                reserveId = Int32.Parse(args[1]),
                                crc = emptycrc
                              };
          Console.WriteLine("ConfirmWriteOffReq request: reserveId={0}", req_confirm.reserveId);
          var resp_confirm = zzima.ConfirmWriteOff(req_confirm);
          Console.WriteLine("ReserveAmount response: code={0}, message={1}",
                            resp_confirm.code, resp_confirm.message);
          break;
      }

      
//      string rq = "test string";
//      string rs = zzima.A_ToBase64(rq);
//      Console.WriteLine("rq={0}; rs={1};", rq, rs);
    }

    public static byte[] getCrc(byte[] password)
    {
      byte[] svc = Encoding.UTF8.GetBytes("pw");
      var content = new MemoryStream();
      content.Write(svc, 0, svc.Length);
      content.Write(password, 0, password.Length);
      byte[] res = content.ToArray();
      MD5 md5Hasher = MD5.Create();
      return md5Hasher.ComputeHash(res, 0, res.Length);
    }
  }
}
