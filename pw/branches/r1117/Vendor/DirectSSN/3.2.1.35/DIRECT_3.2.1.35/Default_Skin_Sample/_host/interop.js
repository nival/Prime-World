var _Interop = function() {
    this._instanceArray = [];
};

var NativeInterop;
if (!NativeInterop) {
    NativeInterop = document.NativeInterop;
}

_Interop.prototype =
{
    createInstance: function(typeName, typeCreator) {
        var instanceId = NativeInterop.createInstance(typeName);

        var instance = new typeCreator(instanceId);
        this._instanceArray[instanceId] = instance;
        return instance;
    },

    releaseInstance: function(instanceId) {
        NativeInterop.releaseInstance(instanceId);
        delete this._instanceArray[instanceId];
    },

    instanceById: function(instanceId) {
        return this._instanceArray[instanceId];
    },

    invoke: function(instanceId, methodBinding) {
        return JSON.parse(NativeInterop.invoke(instanceId, JSON.stringify(methodBinding))).returnValue;
    }
};

var Interop = new _Interop();

function DispatchInteropCallback(instanceId, callbackInfo) {
    var callback = JSON.parse(callbackInfo);

    var obj = Interop.instanceById(instanceId);
    if (obj !== null && obj !== undefined && obj[callback.method] !== null && obj[callback.method] !== undefined) {
        var returnValue = { "returnValue": obj[callback.method](callback) };
        return JSON.stringify(returnValue);
    }

    return null;
}