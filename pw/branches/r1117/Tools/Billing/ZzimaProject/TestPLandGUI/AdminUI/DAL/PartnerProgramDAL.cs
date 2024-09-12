using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.DAL
{
    public class PartnerProgramDAL
    {
        public List<PartnerProgram> Select()
        {
            List<PartnerProgram> list = new List<PartnerProgram>();
            using (BillingDataContext db = new BillingDataContext())
            {
                list = (from pp in db.PartnerPrograms
                                            select pp).ToList<PartnerProgram>();
            }
            return list;
        }

        public PartnerProgram Select(int id)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                return (from pp in db.PartnerPrograms
                        where pp.id == id
                        select pp).Single<PartnerProgram>();
            }
        }
    }
}
