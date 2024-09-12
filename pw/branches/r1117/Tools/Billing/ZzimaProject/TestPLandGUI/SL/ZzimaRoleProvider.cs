using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.Security;
using System.Web;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.DAL;

namespace ZzimaBilling.SL
{
    public class ZzimaRoleProvider : RoleProvider
    {

        public override string[] GetRolesForUser(string username)
        {

            List<string> roles = new List<string>();
            roles.Add("*");
            int groupid = EmployeeDAL.GetGroup(username);
            /*Employer empl = null;
            if ( System.Web.HttpContext.Current.Session!=null)
                empl = (Employer) System.Web.HttpContext.Current.Session[Employer.SESSION_KEY];
            if (empl!=null)
            {  */
            switch (groupid)
            {
                case 1:
                    roles.Add("Admin");
                    //roles.Add("Power");
                    break;
                case 2:
                    roles.Add("Power");
                    break;
                case 4:
                    roles.Add("PWTest");
                    break;
                default:
                    break;
            }
            //}
            return roles.ToArray();

        }

        public override void AddUsersToRoles(string[] usernames, string[] roleNames)
        {
            throw new NotImplementedException();
        }

        public override string ApplicationName
        {
            get; set;
        }

        public override void CreateRole(string roleName)
        {
            throw new NotImplementedException();
        }

        public override bool DeleteRole(string roleName, bool throwOnPopulatedRole)
        {
            throw new NotImplementedException();
        }

        public override string[] FindUsersInRole(string roleName, string usernameToMatch)
        {
            throw new NotImplementedException();
        }

        public override string[] GetAllRoles()
        {
            List<string> roles = new List<string>();
            roles.Add("*");
            roles.Add("Power");
            roles.Add("Admin");

            return roles.ToArray();
        }

        public override string[] GetUsersInRole(string roleName)
        {
            throw new NotImplementedException();
        }

        public override bool IsUserInRole(string username, string roleName)
        {
            throw new NotImplementedException();
        }

        public override void RemoveUsersFromRoles(string[] usernames, string[] roleNames)
        {
            throw new NotImplementedException();
        }

        public override bool RoleExists(string roleName)
        {
            throw new NotImplementedException();
        }
    }
}


