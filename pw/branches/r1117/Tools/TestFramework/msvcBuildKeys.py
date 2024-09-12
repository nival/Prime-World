class Option:

    def __init__(self, name, value):
        self.name = name
        self.value = value
        
    def __call__(self):
        return """
				{0}=\"{1}\"""".format(self.name, self.value)
                        
keysTransition = {
    '/RTCc' : Option("SmallerTypeCheck", "true"),
    '/GF' : Option("StringPooling", "true"),
    '/Gm' : Option("MinimalRebuild", "true"),
    '/RTC1' : Option("BasicRuntimeChecks", 3),
    '/RTCs' : Option("BasicRuntimeChecks", 1),
    '/RTCu' : Option("BasicRuntimeChecks", 2),
    '/RTCsu' : Option("BasicRuntimeChecks", 3),
    '/Z7' : Option("DebugInformationFormat", 1),
    '/Zi' : Option("DebugInformationFormat", 3),
    '/ZI' : Option("DebugInformationFormat", 4),
    '/arch:SSE2' : Option("EnableEnhancedInstructionSet", 2),
    '/arch:SSE' : Option("EnableEnhancedInstructionSet", 1),
	'/J' : Option("DefaultCharIsUnsigned", "true"),
    '/Gd' : Option("CallingConvention", 0),
    '/Gr' : Option("CallingConvention", 1),
    '/Gz' : Option("CallingConvention", 2),
    '/WX' : Option("WarnAsError", "true"),
    '/X' : Option("IgnoreStandardIncludePath", "true"),
    '/Wp64' : Option("Detect64BitPortabilityProblems", "true"),
    '/GS' : Option("BufferSecurityCheck", "true"),
    '/GS-' : Option("BufferSecurityCheck", "false"),
    '/EH-' : Option("ExceptionHandling", 0),
    '/EHsc' : Option("ExceptionHandling", 1),
    '/EHa' : Option("ExceptionHandling", 2),
    '/Gy' : Option("EnableFunctionLevelLinking", "true"),
    '/MT' : Option("RuntimeLibrary", 0),
    '/MTd' : Option("RuntimeLibrary", 1),
    '/MD' : Option("RuntimeLibrary", 2),
    '/MDd' : Option("RuntimeLibrary", 3),
    '/W0' : Option("WarningLevel", 0),
    '/W1' : Option("WarningLevel", 1),
    '/W2' : Option("WarningLevel", 2),
    '/W3' : Option("WarningLevel", 3),
    '/W4' : Option("WarningLevel", 4),
    '/Od' : Option("Optimization", 0),
    '/O1' : Option("Optimization", 1),
    '/O2' : Option("Optimization", 2),
    '/Ox' : Option("Optimization", 3),
    '/Oi' : Option("EnableIntrinsicFunctions", "true"),
    '/Ob1' : Option("InlineFunctionExpansion", 1),
    '/Ob2' : Option("InlineFunctionExpansion", 2),
    '/Ot'  : Option("FavorSizeOrSpeed", 1),
    '/Os'  : Option("FavorSizeOrSpeed", 2),
    '/Oy'  : Option("OmitFramePointers", "true"),
    '/GL'  : Option("WholeProgramOptimization", "true"),
}

