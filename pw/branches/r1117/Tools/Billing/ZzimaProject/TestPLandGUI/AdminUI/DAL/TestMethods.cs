using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Linq;

namespace ZzimaBilling.AdminUI.DAL
{
    public class TestMethods
    {
        /*     public static void CreateTestData()
             {
                 ReplenishmentForUserA_user1();
             }

             public static void ReplenishmentForUserA_user1()
             {
                 using (BillingSPDataContext db = new BillingSPDataContext())
                 {
                     string username = "A_user1";
                     string email = username + "@zzima.zzima";
                     int? error = 0;

                     //for each every PS
                     for (int ps = 5; ps <= 10; ps++)
                     {
                         //for every service
                         for (int sid = 12; sid <= 15; sid++)
                         {
                             Random random1 = new Random();
                             //times 

                             decimal amount = random1.Next(20, 2000);
                             string accountName;
                             using (BillingDataContext db2 = new BillingDataContext())
                             {
                                 //int? userid=(from users in db2.Users
                                 //            where users.name==username
                                 //            select users.id).SingleOrDefault<int>();

                            
                                 //db.sp_api_replenish(sid, username, accountName, PPSName(ps), amount, "P.Yermalovich testing", ref error);
                             }
                         }
                     }
                 }
             }

             public static void GlobalReplenishment()
             {
                 using (BillingSPDataContext db = new BillingSPDataContext())
                 {
                     for (int i = 1; i <= 20; i++)
                     {
                         string username = "A_user" + i.ToString();
                         string email = username + "@zzima.zzima";
                         int? error = 0;

                         //for each every PS
                         for (int ps = 5; ps <= 10; ps++)
                         { 
                             //for every service
                             for (int sid = 12; sid <= 15; sid++)
                             {
                                 Random random1 = new Random();
                                 //times 
                            
                                 decimal amount=random1.Next(20, 2000);
                                 db.sp_api_replenish(sid, username, null,PPSName(ps), amount, "P.Yermalovich testing", ref error);
                             }
                         }
                     }
                     db.SubmitChanges();
                 }
             }

             public static string PPSName(int id)
             {
                 using (BillingDataContext db = new BillingDataContext())
                 {
                     return (from ps in db.PaymentSystems
                             where ps.id == id
                             select ps.name).ToString();
                 }
             }
        
             public static void Create10Users()
             {
                 using (BillingSPDataContext db = new BillingSPDataContext())
                 {
                     for (int i = 1; i <= 20; i++)
                     {
                         string username = "A_user" + i.ToString();
                         string email=username+"@zzima.zzima";
                         int? error=0;
                         db.sp_api_createUser(username, email, StrToBinary(username), "p1"+i.ToString(), ref error);
                         db.SubmitChanges();
                     }
                 }
             }

             public static void Subscribe10UserTo10Service()
             {
                 using (BillingSPDataContext db = new BillingSPDataContext())
                 {
                     for (int i = 1; i <= 20; i++)
                     {
                         string username = "A_user" + i.ToString();
                         int? error = 0;

                         db.sp_api_subscribeUser(username, "HERO 3", StrToBinary(username), ref error);
                         db.sp_api_subscribeUser(username, "HERO 4", StrToBinary(username), ref error);
                         db.sp_api_subscribeUser(username, "HERO 5", StrToBinary(username), ref error);
                         db.sp_api_subscribeUser(username, "WAR CRAFT", StrToBinary(username), ref error); 

                         db.SubmitChanges();
                     }
                 }
             }

             public static void AthorizeUsers()
             {
                 using (BillingSPDataContext db = new BillingSPDataContext())
                 {
                     for (int i = 1; i <= 20; i++)
                     {
                         string username = "A_user" + i.ToString();
                         int? error = 0;

                         db.sp_api_authorizeUser(12, username, StrToBinary(username),ref error);
                         db.sp_api_authorizeUser(13, username, StrToBinary(username), ref error);
                         db.sp_api_authorizeUser(14, username, StrToBinary(username), ref error);
                         db.sp_api_authorizeUser(15, username, StrToBinary(username), ref error);

                         db.SubmitChanges();
                     }
                 }
             }

             public static byte[] StrToByteArray(string str)
             {
                 System.Text.ASCIIEncoding encoding = new System.Text.ASCIIEncoding();
                 return encoding.GetBytes(str);
             }

             public static Binary StrToBinary(string str)
             {
                 System.Text.ASCIIEncoding encoding = new System.Text.ASCIIEncoding();
                 var bytes= encoding.GetBytes(str);
                 return new Binary(bytes);
             }
         */
    }
 
}
