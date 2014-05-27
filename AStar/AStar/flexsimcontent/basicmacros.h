
#ifndef basicmacros_h
#define basicmacros_h

// Exception macros
//#define USE_X_EXCEPTIONS
//#define USE_XX_EXCEPTIONS

#ifdef USE_X_EXCEPTIONS
#define XS try{
#define XE }catch(...){throw 0;}
#endif

#ifdef USE_XX_EXCEPTIONS
#define XXS try{
#define XXE(m) }catch(...){EX(m,"");throw 0;}
#endif

#ifndef USE_X_EXCEPTIONS
#define XS 
#define XE 
#endif

#ifndef USE_XX_EXCEPTIONS
#define XXS
#define XXE(m) 
#endif

// Flexsim interface parameters
#define FLEXSIMINTERFACE int code, TreeNode * c, TreeNode * thisClass, \
void * input, void * output, TreeNode *i, CallPoint * callPoint
#define FLEXSIMINTERFACEPARAMETERS code, c, thisClass, input, output, i, callPoint


#define CHECKNEW(p,m)\
{\
  if (!p) \
  {\
   char buffer[1024];\
   /*mpt(m);*/\
  }\
}

#define optionalthrow throw
//#define optionalthrow mpt("warning: throw - code may have been terminated."); mpr(); 

#define guardstart(name) try{

#define guardend(name) }catch(...){  mpt("exception: "); mpt(#name);mpr();  optionalthrow;}

#define GUARD(x,y)  try{x;}catch(...){ mpt(y); mpt("\n"); optionalthrow;}

#define n10argsdefaultinterface double n1=0,double n2=0,double n3=0,double n4=0,double n5=0,double n6=0,double n7=0,double n8=0,double n9=0,double n10=0

#define n10argsinterface double n1,double n2,double n3,double n4,double n5,double n6,double n7,double n8,double n9,double n10

#define n10args n1,n2,n3,n4,n5,n6,n7,n8,n9,n10

#define n30argsinterface double n1,double n2,double n3,double n4,double n5,double n6,double n7,double n8,double n9,double n10,\
  double n11,double n12,double n13,double n14,double n15,double n16,double n17,double n18,double n19,double n20,\
double n21,double n22,double n23,double n24,double n25,double n26,double n27,double n28,double n29,double n30

#define n30argsdefaultinterface double n1=0,double n2=0,double n3=0,double n4=0,double n5=0,double n6=0,double n7=0,double n8=0,double n9=0,double n10=0,\
  double n11=0,double n12=0,double n13=0,double n14=0,double n15=0,double n16=0,double n17=0,double n18=0,double n19=0,double n20=0,\
double n21=0,double n22=0,double n23=0,double n24=0,double n25=0,double n26=0,double n27=0,double n28=0,double n29=0,double n30=0

#define n30args n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,\
  n11,n12,n13,n14,n15,n16,n17,n18,n19,n20,\
n21,n22,n23,n24,n25,n26,n27,n28,n29,n30

#define visible extern "C" __declspec(dllexport)

#define RETURN_TYPE_UNRESOLVED 0
#define RETURN_TYPE_NUMBER 1
#define RETURN_TYPE_STRING 2

#define TYPE_CHECK_NUMBER_BIT 0x1
#define TYPE_CHECK_STRING_BIT 0x2
#define TYPE_CHECK_NODE_BIT 0x4
#define TYPE_CHECK_ALL_BITS 0x7

#define CALLBACKPARAMS HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam

#define SAFENODE &core->failsafelink

# define parametersinterface CallPoint * callpoint
# define parameters callpoint

#define o(type,instance) (*(instance->object<type>()))
#define objectAs(T) object<T>()

#define CppStart 
#define CppEnd 
#define ObjectFunctionStart try { int functionlocaliterator=0; double count=0;
#define ObjectFunctionEnd(functionname) return 0; } catch(...) {\
		reportobjectfunctionexception(functionname, c, i, thisClass);mpr();\
		logevent("EXCEPTION", c, i);\
	} 
#define ObjectMethodStart try {
#define ObjectMethodEnd(objectname) } catch(...) {reportobjectfunctionexception(objectname, this->holder, NULL, NULL); throw;} 
#define ObjectMethodEndStatic(objectname) } catch(...) {reportobjectfunctionexception(objectname, NULL, NULL, NULL); throw;} 
#define GlobalFunctionStart try {
#define GlobalFunctionEnd(functionname) } catch(...) {reportobjectfunctionexception(functionname, NULL, NULL, NULL); throw;} 

#define iterate(a,b,c) for(int count=a;c>0?count<=b:count>=b;count+=c)
#define forobjecttreeunder(topnode)\
for(treenode a = first(topnode); validlink(a,""); nextforobjecttreeunder(&a, topnode))
#define forobjectlayerunder(node)\
for (treenode a = first(node);objectexists(a);a=next(a))
#define forobjectsbefore(node)\
for (treenode a = prev(node);objectexists(a) && getrank(a) >= 1;a=prev(a))
#define forobjectsbehind(node)\
for (treenode a = next(node);objectexists(a);a=next(a))
#define forobjectselectionset(node)\
for(treenode a = NULL, nextforobjectselectionset(&a, node); objectexists(a); nextforobjectselectionset(&a, node))

#define BINDFLAG_PORTCACHE			0x00000001
#define UNBINDFLAG_PORTCACHE		0x00000002
#define BINDFLAG_IGNOREMEDIA		0x00000004
#define BINDFLAG_IGNORECLASSES		0x00000008
#define BINDFLAG_IGNORERESET		0x00000010
#define BINDFLAG_DESTROYONRESET		0x00000020
#define BINDFLAG_BINDVARIABLES		0x00000040

#define SM_RESET 1
#define SM_MESSAGE 2
#define SM_EVENT 3
#define SM_DRAW 4

#define SM_INOPEN 5
#define SM_OUTOPEN 6
#define SM_ACCEPT 7
#define SM_GIVE 8
#define SM_ENTER 9
#define SM_EXIT 10

#define SM_COMPILE 11
#define SM_CREATE 12
#define SM_DESTROY 13
#define SM_UNDO 14
#define SM_CLICK 15
#define SM_RUNSTART 16
#define SM_RUNWARM 17
#define SM_RUNEND 18
#define SM_PRELISTEN 19
#define SM_LISTEN 20
#define SM_PREDRAW 21
#define SM_DRAWPLANAR 22
#define SM_PREDRAWPLANAR 23

#define SM_STATECHANGE 24
#define SM_DRAG 25

#define SM_MAX_MESSAGES 27 // If you add more messages, make sure you change this to the max message plus 1

#define DATA_FLOAT 1
#define DATA_BYTEBLOCK 2
#define DATA_POINTERCOUPLING 3
#define DATA_OBJECT 4
#define DATA_PARTICLE 5
#define DATA_BUNDLE 6
#define DATA_SIMPLE 7

#define LISTENER_INFO_CODE 1
#define LISTENER_INFO_ASSOCIATED 2
#define LISTENER_INFO_COUPLING 3

// Constants
#define KINEMATIC_X  0
#define KINEMATIC_Y  1
#define KINEMATIC_Z  2
#define KINEMATIC_RX  3
#define KINEMATIC_RY  4
#define KINEMATIC_RZ  5
#define KINEMATIC_VX  6
#define KINEMATIC_VY  7
#define KINEMATIC_VZ  8
#define KINEMATIC_VRX  9
#define KINEMATIC_VRY  10
#define KINEMATIC_VRZ  11
#define KINEMATIC_NR  12
#define KINEMATIC_STARTTIME  13
#define KINEMATIC_ENDTIME  14
#define KINEMATIC_ARRIVALTIME  15
#define KINEMATIC_STARTSPEED  16
#define KINEMATIC_ENDSPEED  17
#define KINEMATIC_ACC1  18
#define KINEMATIC_ACC2  19
#define KINEMATIC_PEAKSPEED  20
#define KINEMATIC_ACC1TIME  21
#define KINEMATIC_PEAKTIME  22
#define KINEMATIC_ACC2TIME  23
#define KINEMATIC_TOTALDIST  24
#define KINEMATIC_CUMULATIVEDIST  25
#define KINEMATIC_TOTALX  26
#define KINEMATIC_TOTALY  27
#define KINEMATIC_TOTALZ  28
#define KINEMATIC_TOTALRDIST  29
#define KINEMATIC_CUMULATIVERDIST  30
#define KINEMATIC_TOTALRX  31
#define KINEMATIC_TOTALRY  32
#define KINEMATIC_TOTALRZ  33
#define KINEMATIC_VELOCITY  34
#define KINEMATIC_RVELOCITY  35
#define KINEMATIC_ENDDIST  36
#define KINEMATIC_ENDRDIST  37
#define KINEMATIC_TYPE  38

#define KINEMATIC_TRAVEL  1
#define KINEMATIC_ROTATE  2
#define KINEMATIC_TURNXY  3
#define KINEMATIC_TURNYZ  4
#define KINEMATIC_TURNZX  5

inline void * doubletoptr(double x)
{
//	return ((void**)&x)[0];
	return (void*)(size_t)x;
}
inline double ptrtodouble(void* x)
{
//	return ((double*)&x)[0];
	return (double)(size_t)x;
}

#ifdef FLEXSIM_ENGINE_COMPILE
	#define engine_export __declspec(dllexport)
	#define engine_private public
#else
	#define engine_export
	#define engine_private private
#endif

#if defined FLEXSIM_ENGINE_COMPILE || defined COMPILING_FLEXSIM_CONTENT
	#define content_private public
#else
	#define content_private private
#endif

#if defined FLEXSIM_ENGINE_COMPILE || defined COMPILING_FLEXSIM_CONTENT || defined COMPILING_MODULE_DLL
#define module_private public
#else
#define module_private private
#endif

template <class Dest, class Src>
Dest force_cast(Src src)
{
	union
	{
		Dest d;
		Src s;
	} convertor;
	convertor.s = src;
	return convertor.d;
}

#endif