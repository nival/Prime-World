import gameApp

TEST_APPLICATIONS = [
  gameApp.GameApp
]

def getProjects():
  return [app.project() for app in TEST_APPLICATIONS]

def configureApplications(settings):
  for app in TEST_APPLICATIONS:
    app.configure(settings)
