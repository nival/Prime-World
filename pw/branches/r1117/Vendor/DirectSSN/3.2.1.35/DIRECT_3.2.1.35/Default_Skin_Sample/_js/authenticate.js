function Authenticate() {
    this.onShow = null;
    this.onHide = null;
    this.authenticateInfo = null;
    this.authenticateStage = 0;
}

Authenticate.prototype.internalRaiseShow = function(info) {
    if (this.onShow !== null) {
        this.onShow(info);
    } else {
        this.cancel();
    }
};

Authenticate.prototype.internalRaiseHide = function(info) {
    if (this.onHide !== null) {
        this.onHide(info);
    }
    this.authenticateInfo = null;
};

Authenticate.prototype.attach = function() {
    var self = this;
    host.app.onWillAuthenticateWebGetTarget = function(info) {
        return self.onAuthenticateWebGetTarget(info);
    };
};

Authenticate.prototype.cancel = function() {
    this.authenticateStage = -1;

    this.internalRaiseHide({});
};

Authenticate.prototype.ok = function(username, password) {
    this.authenticateStage = 1;

    host.app.setCredential(this.authenticateInfo.type, this.authenticateInfo.host, this.authenticateInfo.realm, username, password);

    this.internalRaiseHide({});
};

Authenticate.prototype.onAuthenticateWebGetTarget = function(info) {
    var returnValue, userCredential;

    userCredential = JSON.parse(host.app.getCredential(info.type, info.host, info.realm));

    if (this.authenticateStage === 0) {
        if (info.username !== userCredential.username || info.password !== userCredential.password) {
            // Use the credential name in the store
            this.authenticateStage = 1;
        } else if (this.authenticateInfo === null) {
            this.authenticateInfo = info;
            info.userCredential = userCredential;
            this.internalRaiseShow(info);
        }
    }

    if (this.authenticateStage < 0) {
        returnValue = { "cancel": true };
        this.authenticateStage = 0;
    } else if (this.authenticateStage === 0) {
        returnValue = { "cancel": false };
    } else {
        returnValue = {
            "username": userCredential.username,
            "password": userCredential.password,
            "cancel": false
        };
        this.authenticateStage = 0;
    }

    return JSON.stringify(returnValue);
};

var authenticate = new Authenticate();
