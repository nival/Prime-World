def enum(*args, **kwargs):
    class Enum:
        def __init__(self, args):
            self.__dict__.update(args)
            self.__reversed = {}
            for name, value in args.items():
                assert value not in self.__reversed
                self.__reversed[str(value)] = name
        def __getitem__(self, value):
            return self.__reversed.get(str(value), value)
        def __call__(self, param):
            return self.__dict__.get(param, None)
        def FromString(self, _param):
            param = str(_param)
            value = self.__dict__.get(param, None)
            if value == None:
                value = self.__reversed.get(param, None)
                if value != None:
                    value = self.__dict__.get(value, None)
                else:
                    raise Exception('Enum value %r not found' % param)
            return value
    values = {}
    rvalues = {}
    for index, name in enumerate(args):
        values[name] = index
        rvalues[index] = name        
    for name, index in kwargs.items():
        assert index not in rvalues, "Dublicated enum value (name=%r value=%r existing_name=%r)" % (name, index, rvalues[index])
        values[name] = index
    return Enum(values)
