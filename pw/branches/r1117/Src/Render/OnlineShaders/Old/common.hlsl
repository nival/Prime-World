#ifdef VS	
	#define VS_CONSTANT( X ) X
#else
	#define VS_CONSTANT( X )
#endif

#ifdef PS	
	#define PS_CONSTANT( X ) X
#else
	#define PS_CONSTANT( X )
#endif