/*!
* \file oserror.js
* \brief File containing operating system helper functions
*/

/*!
* \class OSError
* \brief Operating system helper functions
*/
function OSError() {
    // Windows errors
    this.ERROR_SUCCESS = 0;
    this.ERROR_FILE_NOT_FOUND = 2;
    this.ERROR_PATH_NOT_FOUND = 3;
    this.ERROR_TOO_MANY_OPEN_FILES = 4;
    this.ERROR_ACCESS_DENIED = 5;
    this.ERROR_INVALID_DRIVE = 15;
    this.ERROR_WRITE_PROTECT = 19;
    this.ERROR_SHARING_VIOLATION = 32;
    this.ERROR_LOCK_VIOLATION = 33;
    this.ERROR_HANDLE_DISK_FULL = 39;
    this.ERROR_BAD_NET_NAME = 67;
    this.ERROR_FILE_EXISTS = 80;
    this.ERROR_DRIVE_LOCKED = 108;
    this.ERROR_DISK_FULL = 112;
    this.ERROR_INVALID_NAME = 123;
    this.ERROR_BAD_PATHNAME = 161;

    // Mac errors
    this.ESUCCESS = 0;
    this.EPERM = 1;
    this.ENOENT = 2;
    this.EBADF = 9;
    this.EAGAIN = 11;
    this.EACCES = 13;
    this.EBUSY = 16;
    this.EEXIST = 17;
    this.ENODEV = 19;
    this.EISDIR = 21;
    this.ENOTDIR = 20;
    this.ENFILE = 22;
    this.EFBIG = 27;
    this.ENOSPC = 28;
    this.ESPIPE = 29;
    this.EROFS = 30;
    this.EMLINK = 31;
    this.EDEADLK = 35;
    this.ENAMETOOLONG = 36;
}

OSError.prototype.nameFromIdWin = function(id) {
    switch (id) {
        case this.ERROR_SUCCESS:
            return "None";

        case this.ERROR_FILE_NOT_FOUND:
        case this.ERROR_INVALID_DRIVE:
        case this.ERROR_INVALID_NAME:
        case this.ERROR_BAD_PATHNAME:
        case this.ERROR_PATH_NOT_FOUND:
        case this.ERROR_ALREADY_EXISTS:
        case this.ERROR_FILE_EXISTS:
        case this.ERROR_BAD_NET_NAME:
        case this.ERROR_TOO_MANY_OPEN_FILES:
            return "AccessInvalid";

        case this.ERROR_ACCESS_DENIED:
        case this.ERROR_WRITE_PROTECT:
            return "AccessDenied";

        case this.ERROR_DRIVE_LOCKED:
        case this.ERROR_LOCK_VIOLATION:
        case this.ERROR_SHARING_VIOLATION:
            return "Locked";

        case this.ERROR_DISK_FULL:
        case this.ERROR_HANDLE_DISK_FULL:
            return "NotEnoughSpace";
    }

    return "Unknown";
};

OSError.prototype.nameFromIdMac = function(id) {
    switch (id) {
        case this.ESUCCESS:
            return "None";

        case this.EPERM:
        case this.EAGAIN:
        case this.EACCES:
        case this.EBUSY:
        case this.EROFS:
            return "AccessDenied";

        case this.ENOENT:
        case this.EBADF:
        case this.EEXIST:
        case this.ENODEV:
        case this.EISDIR:
        case this.ENOTDIR:
        case this.ENFILE:
        case this.EFBIG:
        case this.ESPIPE:
        case this.EMLINK:
        case this.ENAMETOOLONG:
            return "AccessInvalid";

        case this.ENOSPC:
            return "NotEnoughSpace";

        case this.EDEADLK:
            return "Locked";
    }

    return "Unknown";
};

/*!
* converts an error code to a string
* \tparam int id error code
* \type string
* \returns stringified name of error code
*/
OSError.prototype.nameFromId = function(id) {
    switch (host.app.expandString("{SystemShortName}".toLowerCase())) {
        case "win":
            return this.nameFromIdWin(id);

        case "mac":
            return this.nameFromIdMac(id);
    }

    return "Unknown";
};

/*!
* checks if the error code is handled
* \tparam int id error code
* \type bool
* \returns true if handled, false otherwise
*/
OSError.prototype.isUnknown = function(id) {
    if (this.nameFromId(id).toLowerCase() === "unknown") {
        return true;
    }

    return false;
};

/*!
* precreated global instance of OSError
* \type OSError
*/
var osError = new OSError();
