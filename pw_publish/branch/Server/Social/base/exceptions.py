__author__ = 'danil.lavrentyuk'

class SSError(Exception):
    "Standard exception for internal error indictions."
    pass


class ModelDataError(SSError):
    "ModelData logic and internals error"
    pass

class ModelChangeApplicatorError(ModelDataError):
    "Change applicator logic error"
    pass

class CollectZeroError(ModelDataError):
    "Try to collect from not ready building"
    pass

class RecruitmentError(SSError):
    "Any guild recruitment logic errors"
    pass

class NoRecruitApplicationError(RecruitmentError):
    "Recruit application not found"
    pass

class RecruitAppliationDeclinedError(RecruitmentError):
    "Recruit application exists but is outdated"
    pass

class DisplaceLoginError(SSError):
    "Exception for logouting old users"
    pass

class BadModelDataError(SSError):
    "Exception bad mm session "
    pass
