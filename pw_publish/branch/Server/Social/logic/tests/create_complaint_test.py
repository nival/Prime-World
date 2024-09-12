import sys

sys.path.append('../')
sys.path.append('../..')
from logic.create_complaint import *
from logic.reset_complaints import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC


class create_complaint_test:
    def create_complaint_test(self, env):
        modeldata = env.acc.model
        assert modeldata.LordInfo.ComplaintsLeft == env.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + modeldata.LordInfo.ExtraComplaints

        requests = [(Create_complaint, CreateComplaintRequest(modeldata,
                                                              {"toauid": ["3"], "category": ["1"], "text": ["test"],
                                                               "source": ["0"],
                                                               "sessionid": ["0"], "kills": ["0"], "deaths": ["0"],
                                                               "assists": ["0"], "points": ["0"],
                                                               "prime": ["0"], "leave": ["0"], "distance": ["0"],
                                                               "afks": ["0"], "post_data": [""]}, False))]

        changeList = env.execActions(requests)

        assert modeldata.LordInfo.ComplaintsLeft == (
                                                    env.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + modeldata.LordInfo.ExtraComplaints) - 1

    def reset_complaint_test(self, env):
        modeldata = env.acc.model

        assert modeldata.LordInfo.ComplaintsLeft == env.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + modeldata.LordInfo.ExtraComplaints

        requests = [(Create_complaint, CreateComplaintRequest(modeldata,
                                                              {"toauid": ["3"], "category": ["1"], "text": ["test"],
                                                               "source": ["0"],
                                                               "sessionid": ["0"], "kills": ["0"], "deaths": ["0"],
                                                               "assists": ["0"], "points": ["0"],
                                                               "prime": ["0"], "leave": ["0"], "distance": ["0"],
                                                               "afks": ["0"], "post_data": [""]}, False))]

        changeList = env.execActions(requests)
        assert modeldata.LordInfo.ComplaintsLeft == (
                                                    env.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + modeldata.LordInfo.ExtraComplaints) - 1

        requests = [(Reset_complaints, ResetComplaintsRequest(modeldata, {}, False))]
        changeList = env.execActions(requests)
        assert modeldata.LordInfo.ComplaintsLeft == (
        env.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + modeldata.LordInfo.ExtraComplaints)

        modeldata.LordInfo.ComplaintsLeft = 1
        modeldata.resetComplaints(env.acc)
        assert modeldata.LordInfo.ComplaintsLeft == 1

    def exceed_complaint_test(self, env):
        modeldata = env.acc.model

        modeldata.LordInfo.ComplaintsLeft = 0

        requests = [(Create_complaint, CreateComplaintRequest(modeldata,
                                                              {"toauid": ["3"], "category": ["1"], "text": ["test"],
                                                               "source": ["0"],
                                                               "sessionid": ["0"], "kills": ["0"], "deaths": ["0"],
                                                               "assists": ["0"], "points": ["0"],
                                                               "prime": ["0"], "leave": ["0"], "distance": ["0"],
                                                               "afks": ["0"], "post_data": [""]}, False))]

        changeList = env.execActions(requests)
        assert modeldata.LordInfo.ComplaintsLeft == 0

    def create_complaint_extra_test(self, env):
        modeldata = env.acc.model
        modeldata.LordInfo.ExtraComplaints = 5
        modeldata.LordInfo.ResetComplaintsTime = 0
        modeldata.resetComplaints(env.acc)

        assert modeldata.LordInfo.ComplaintsLeft == env.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + modeldata.LordInfo.ExtraComplaints
        for i in xrange(env.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + modeldata.LordInfo.ExtraComplaints):
            requests = [(Create_complaint, CreateComplaintRequest(modeldata,
                                                                  {"toauid": ["3"], "category": ["1"], "text": ["test"],
                                                                   "source": ["0"],
                                                                   "sessionid": ["0"], "kills": ["0"], "deaths": ["0"],
                                                                   "assists": ["0"], "points": ["0"],
                                                                   "prime": ["0"], "leave": ["0"], "distance": ["0"],
                                                                   "afks": ["0"], "post_data": [""]}, False))]

            changeList = env.execActions(requests)

            assert modeldata.LordInfo.ComplaintsLeft == (
                                                        env.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + modeldata.LordInfo.ExtraComplaints) - i - 1

    def create_complaint_extra1_test(self, env):
        modeldata = env.acc.model
        modeldata.LordInfo.ExtraComplaints = index = 5
        modeldata.LordInfo.ResetComplaintsTime = 0
        modeldata.resetComplaints(env.acc)

        assert modeldata.LordInfo.ComplaintsLeft == env.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + modeldata.LordInfo.ExtraComplaints
        for i in xrange(modeldata.LordInfo.ExtraComplaints):
            requests = [(Create_complaint, CreateComplaintRequest(modeldata,
                                                                  {"toauid": ["3"], "category": ["1"], "text": ["test"],
                                                                   "source": ["0"],
                                                                   "sessionid": ["0"], "kills": ["0"], "deaths": ["0"],
                                                                   "assists": ["0"], "points": ["0"],
                                                                   "prime": ["0"], "leave": ["0"], "distance": ["0"],
                                                                   "afks": ["0"], "post_data": [""]}, False))]

            changeList = env.execActions(requests)

            assert modeldata.LordInfo.ComplaintsLeft == (
                                                        env.acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + modeldata.LordInfo.ExtraComplaints) - i - 1

        modeldata.LordInfo.ComplaintsLeft -= modeldata.LordInfo.ExtraComplaints
        modeldata.LordInfo.ExtraComplaints = 0
        requests = [(Create_complaint, CreateComplaintRequest(modeldata,
                                                              {"toauid": ["3"], "category": ["1"], "text": ["test"],
                                                               "source": ["0"],
                                                               "sessionid": ["0"], "kills": ["0"], "deaths": ["0"],
                                                               "assists": ["0"], "points": ["0"],
                                                               "prime": ["0"], "leave": ["0"], "distance": ["0"],
                                                               "afks": ["0"], "post_data": [""]}, False))]

        changeList = env.execActions(requests)

        assert modeldata.LordInfo.ComplaintsLeft <= 0
        assert changeList.get(index).get("ec") == EC.TOO_MANY_COMPLAINTS


    def create_complaint_extra_session_test(self, env):
        modeldata = env.acc.model
        modeldata.LordInfo.ComplaintsSessionLeft =7
        modeldata.LordInfo.ExtraComplaintsSession = index = 5
        modeldata.LordInfo.ResetComplaintsTime = 0
        modeldata.resetComplaints(env.acc)

        assert modeldata.LordInfo.ComplaintsSessionLeft == env.acc.getConfig().ComplaintsSettings.MAX_COMPLAITS_PER_SESSION + modeldata.LordInfo.ExtraComplaintsSession
        for i in xrange(modeldata.LordInfo.ExtraComplaintsSession):
            requests = [(Create_complaint, CreateComplaintRequest(modeldata,
                                                                  {"toauid": ["3"], "category": ["1"], "text": ["test"],
                                                                   "source": ["1"],
                                                                   "sessionid": ["0"], "kills": ["0"], "deaths": ["0"],
                                                                   "assists": ["0"], "points": ["0"],
                                                                   "prime": ["0"], "leave": ["0"], "distance": ["0"],
                                                                   "afks": ["0"], "post_data": [""]}, False))]

            changeList = env.execActions(requests)

            assert modeldata.LordInfo.ComplaintsSessionLeft == (
                                                        env.acc.getConfig().ComplaintsSettings.MAX_COMPLAITS_PER_SESSION + modeldata.LordInfo.ExtraComplaintsSession) - i - 1

        modeldata.LordInfo.ComplaintsSessionLeft -= modeldata.LordInfo.ExtraComplaintsSession
        modeldata.LordInfo.ExtraComplaintsSession = 0
        requests = [(Create_complaint, CreateComplaintRequest(modeldata,
                                                              {"toauid": ["3"], "category": ["1"], "text": ["test"],
                                                               "source": ["1"],
                                                               "sessionid": ["0"], "kills": ["0"], "deaths": ["0"],
                                                               "assists": ["0"], "points": ["0"],
                                                               "prime": ["0"], "leave": ["0"], "distance": ["0"],
                                                               "afks": ["0"], "post_data": [""]}, False))]

        changeList = env.execActions(requests)

        assert modeldata.LordInfo.ComplaintsSessionLeft <= 0
        assert changeList.get(index).get("ec") == EC.TOO_MANY_COMPLAINTS

