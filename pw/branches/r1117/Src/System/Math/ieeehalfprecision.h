#ifndef IEEEHALFPRECISION_H_INCLUDED
#define IEEEHALFPRECISION_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

int singles2halfp( void * target, void * source, int numel );
int doubles2halfp( void * target, void * source, int numel );
int halfp2singles( void * target, void * source, int numel );
int halfp2doubles( void * target, void * source, int numel );

#ifdef __cplusplus
} //extern "C"
#endif //__cplusplus

#endif //IEEEHALFPRECISION_H_INCLUDED
