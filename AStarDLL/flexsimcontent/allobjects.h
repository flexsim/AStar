
// cpp objects


#ifndef allobjects_h


#define allobjects_h


#ifdef COMPILING_FLEXSIM_CONTENT
#include "all.h"
#define FS_CONTENT_DLL_FUNC __declspec(dllexport)
#else
#define FS_CONTENT_DLL_FUNC __declspec(dllimport)
#endif
#define node_b_behaviour Nb_behaviour
#define node_b_cppfunctions Nb_cppfunctions
#define node_b_cppvariables Nb_cppvariables
#define node_b_eventfunctions Nb_eventfunctions
#define node_b_userfunctions Nb_userfunctions
#define node_b_classes Nb_classes
#define node_b_superclasses Nb_superclasses
#define node_b_connections Nb_connections
#define node_b_connectionsin Nb_connectionsin
#define b_connectionsin Nb_connectionsin->safedatafloat()[0]
#define node_b_connectionsout Nb_connectionsout
#define b_connectionsout Nb_connectionsout->safedatafloat()[0]
#define node_b_connectionscenter Nb_connectionscenter
#define b_connectionscenter Nb_connectionscenter->safedatafloat()[0]
#define node_b_itemtype Nb_itemtype
#define b_itemtype Nb_itemtype->safedatafloat()[0]
#define node_b_labels Nb_labels
#define node_b_variables Nb_variables
#define node_b_listeners Nb_listeners
#define node_b_OnReset Nb_OnReset
#define node_b_OnMessage Nb_OnMessage
#define node_b_OnTimerEvent Nb_OnTimerEvent
#define node_b_OnDraw Nb_OnDraw
#define node_b_OnPreDraw Nb_OnPreDraw
#define node_b_OnDrawPlanar Nb_OnDrawPlanar
#define node_b_OnPreDrawPlanar Nb_OnPreDrawPlanar
#define node_b_OnInOpen Nb_OnInOpen
#define node_b_OnOutOpen Nb_OnOutOpen
#define node_b_OnReceive Nb_OnReceive
#define node_b_OnSend Nb_OnSend
#define node_b_OnEntering Nb_OnEntering
#define node_b_OnExiting Nb_OnExiting
#define node_b_OnCompile Nb_OnCompile
#define node_b_OnCreate Nb_OnCreate
#define node_b_OnDestroy Nb_OnDestroy
#define node_b_OnUndo Nb_OnUndo
#define node_b_OnClick Nb_OnClick
#define node_b_OnRunStart Nb_OnRunStart
#define node_b_OnRunWarm Nb_OnRunWarm
#define node_b_OnRunEnd Nb_OnRunEnd
#define node_b_OnListen Nb_OnListen
#define node_b_OnPreListen Nb_OnPreListen
#define node_b_OnStateChange Nb_OnStateChange
#define node_b_OnDrag Nb_OnDrag
#define node_b_stats Nb_stats
#define node_b_state_current Nb_state_current
#define node_b_state_since Nb_state_since
#define node_b_state_profile Nb_state_profile
#define node_b_state_profiles Nb_state_profiles
#define node_b_stats_content Nb_stats_content
#define node_b_stats_staytime Nb_stats_staytime
#define node_b_stats_contentmin Nb_stats_contentmin
#define b_stats_contentmin Nb_stats_contentmin->safedatafloat()[0]
#define node_b_stats_contentmax Nb_stats_contentmax
#define b_stats_contentmax Nb_stats_contentmax->safedatafloat()[0]
#define node_b_stats_contentavg Nb_stats_contentavg
#define b_stats_contentavg Nb_stats_contentavg->safedatafloat()[0]
#define node_b_stats_contentupdates Nb_stats_contentupdates
#define b_stats_contentupdates Nb_stats_contentupdates->safedatafloat()[0]
#define node_b_stats_contentsince Nb_stats_contentsince
#define b_stats_contentsince Nb_stats_contentsince->safedatafloat()[0]
#define node_b_stats_contentgraph Nb_stats_contentgraph
#define node_b_stats_contentgraphmaxpoints Nb_stats_contentgraphmaxpoints
#define b_stats_contentgraphmaxpoints Nb_stats_contentgraphmaxpoints->safedatafloat()[0]
#define node_b_stats_staytimemin Nb_stats_staytimemin
#define node_b_stats_staytimemax Nb_stats_staytimemax
#define node_b_stats_staytimeavg Nb_stats_staytimeavg
#define node_b_stats_staytimeupdates Nb_stats_staytimeupdates
#define node_b_stats_staytimesince Nb_stats_staytimesince
#define node_b_stats_staytimegraph Nb_stats_staytimegraph
#define node_b_stats_staytimegraphmaxpoints Nb_stats_staytimegraphmaxpoints
#define node_b_stats_staytimehisto Nb_stats_staytimehisto
#define node_b_stats_throughput Nb_stats_throughput
#define node_b_stats_lastmovetime Nb_stats_lastmovetime
#define b_stats_lastmovetime Nb_stats_lastmovetime->safedatafloat()[0]
#define node_b_stats_creationtime Nb_stats_creationtime
#define b_stats_creationtime Nb_stats_creationtime->safedatafloat()[0]
#define node_b_stats_input Nb_stats_input
#define node_b_stats_output Nb_stats_output
#define node_b_stream Nb_stream
#define b_stream Nb_stream->safedatafloat()[0]
#define node_b_spatialx Nb_spatialx
#define b_spatialx Nb_spatialx->safedatafloat()[0]
#define node_b_spatialy Nb_spatialy
#define b_spatialy Nb_spatialy->safedatafloat()[0]
#define node_b_spatialz Nb_spatialz
#define b_spatialz Nb_spatialz->safedatafloat()[0]
#define node_b_spatialsx Nb_spatialsx
#define b_spatialsx Nb_spatialsx->safedatafloat()[0]
#define node_b_spatialsy Nb_spatialsy
#define b_spatialsy Nb_spatialsy->safedatafloat()[0]
#define node_b_spatialsz Nb_spatialsz
#define b_spatialsz Nb_spatialsz->safedatafloat()[0]
#define node_b_spatialrx Nb_spatialrx
#define b_spatialrx Nb_spatialrx->safedatafloat()[0]
#define node_b_spatialry Nb_spatialry
#define b_spatialry Nb_spatialry->safedatafloat()[0]
#define node_b_spatialrz Nb_spatialrz
#define b_spatialrz Nb_spatialrz->safedatafloat()[0]
#define node_b_offsetx Nb_offsetx
#define b_offsetx Nb_offsetx->safedatafloat()[0]
#define node_b_offsety Nb_offsety
#define b_offsety Nb_offsety->safedatafloat()[0]
#define node_b_offsetz Nb_offsetz
#define b_offsetz Nb_offsetz->safedatafloat()[0]
#define node_b_offsetrx Nb_offsetrx
#define b_offsetrx Nb_offsetrx->safedatafloat()[0]
#define node_b_offsetry Nb_offsetry
#define b_offsetry Nb_offsetry->safedatafloat()[0]
#define node_b_offsetrz Nb_offsetrz
#define b_offsetrz Nb_offsetrz->safedatafloat()[0]
#define node_b_offsetsx Nb_offsetsx
#define b_offsetsx Nb_offsetsx->safedatafloat()[0]
#define node_b_offsetsy Nb_offsetsy
#define b_offsetsy Nb_offsetsy->safedatafloat()[0]
#define node_b_offsetsz Nb_offsetsz
#define b_offsetsz Nb_offsetsz->safedatafloat()[0]
#define node_b_color Nb_color
#define node_b_centroid Nb_centroid
#define b_centroid Nb_centroid->safedatafloat()[0]
#define node_b_drawflags Nb_drawflags
#define b_drawflags Nb_drawflags->safedatafloat()[0]
#define node_b_imageobject Nb_imageobject
#define node_b_imageindexobject Nb_imageindexobject
#define b_imageindexobject Nb_imageindexobject->safedatafloat()[0]
#define node_b_imagebase Nb_imagebase
#define node_b_imageindexbase Nb_imageindexbase
#define b_imageindexbase Nb_imageindexbase->safedatafloat()[0]
#define node_b_shape Nb_shape
#define node_b_shapeindex Nb_shapeindex
#define b_shapeindex Nb_shapeindex->safedatafloat()[0]
#define node_b_drawsurrogate Nb_drawsurrogate
#define node_b_sound Nb_sound
#define node_b_soundindex Nb_soundindex
#define b_soundindex Nb_soundindex->safedatafloat()[0]
#define node_b_guifocus Nb_guifocus
#define node_b_guifocusclass Nb_guifocusclass
#define node_b_stored Nb_stored
#define node_b_objectinfo Nb_objectinfo
#define node_b_frame Nb_frame
#define b_frame Nb_frame->safedatafloat()[0]
#define node_b_uniqueid Nb_uniqueid
#define b_uniqueid Nb_uniqueid->safedatafloat()[0]
#define node_b_animationinfo Nb_animationinfo
#define node_b_resizeinfo Nb_resizeinfo


// Constants



// Constants


#define iterate(__start__, __end__, __inc__) for (double count = __start__; __inc__ > 0 ? count < __end__ + .001 * __inc__ : count > __end__ + 0.001 * __inc__; count += __inc__)
#define inheritcode() _inheritcode(callPoint)
#define local(index) __local__(index, callPoint)
#define localarray(qty, datatype) __localarray__(qty, datatype, callPoint)

#ifdef THIS_SHOULD_NEVER_BE_DEFINED_BECAUSE_IT_SHOULD_ONLY_BE_SEEN_BY_FLEXSCRIPT
	#define forobjecttreeunder(__top__) for (treenode a = first(__top__); objectexists(a); a = nextforobjecttreeunder(a, __top__))
	#define forobjectlayerunder(__top__) for (treenode a = first(__top__); objectexists(a); a = next(a))
	#define forobjectsbefore(__node__) for (treenode a = prev(__node__); objectexists(a) && getrank(a) >= 1; a = prev(a))
	#define forobjectsbehind(__node__) for (treenode a = next(__node__); objectexists(a); a = next(a))
	#define max(__left__, __right__) ((__left__ >= __right__) ? __left__ : __right__)
	#define min(__left__, __right__) ((__left__ <= __right__) ? __left__ : __right__)
	#define eq(__a__, __b__) (__a__ == __b__)
	#define ne(__a__, __b__) (__a__ != __b__)
#endif

#define makearray(__size__) __size__
#define partype(__a__) _partype(__a__,callPoint)
#define msgparam(__a__) _param(__a__ + 1, callPoint)
#define param(__a__) _param(__a__, callPoint)
#define parval(__a__) _parval(__a__, callPoint)
#define parnode(__a__) _parnode(__a__, callPoint)
#define parstr(__a__) _parstr(__a__, callPoint)
#define parqty() _parqty(callPoint)
#define setcurrent(__a__) __setcurrent__(__a__, callPoint)
#define setitem(__a__) __setitem__(__a__, callPoint)
#define setport(__a__) __setport__(__a__, callPoint)

// Constants group: GLOBAL
#define GLOBAL_DELAYINDEFINITE  1000000000
#define GLOBAL_UNREACHABLE  340282346600000000000000000000000000000.0
#define UNIXSECSB4OADATETIME 9435312000.0
#define INT_MAX 2147483647

// Constants group: EVENT
#define EVENT_OPENINPUTS  1
#define EVENT_OPENOUTPUTS  2
#define EVENT_PROCESSFINISH  3
#define EVENT_CREATEPART  4
#define EVENT_DESTROYPRODUCT  5
#define EVENT_CONVEYEND  6
#define EVENT_BEGINLOADTIME  7
#define EVENT_BEGINUNLOADTIME  8
#define EVENT_ENDLOADTIME  9
#define EVENT_ENDUNLOADTIME  10
#define EVENT_ENDDELAYTIME  11
#define EVENT_BEGINDOWNTIME  12
#define EVENT_ENDDOWNTIME  13
#define EVENT_ENDDOWNTIMENORESUME  14
#define EVENT_ENDWAITTIME  15
#define EVENT_MEETBATCHQTY  16
#define EVENT_ENDTRAVELTIME  17
#define EVENT_ENDSETUP  18
#define EVENT_SENDMESSAGE  19
#define EVENT_RECORDER_LISTEN  20
#define EVENT_COLLISIONCHECK  21
#define EVENT_STARTLOADTIME  22
#define EVENT_STARTUNLOADTIME  23
#define EVENT_USEROPENOUTPUT  24
#define EVENT_USEROPENINPUT  25
#define EVENT_TICK  26
#define EVENT_TRAVELERBLOCKED  27
#define EVENT_STARTSIMULATION  28
#define EVENT_ENDCHANGEOVER  29
#define EVENT_BEGINRUN  30
#define EVENT_NEXTTIME  31
#define EVENT_RELEASEPALLET  32
#define EVENT_CONV_AT_BLOCKED_LENGTH  33
#define EVENT_PE_GREEN  34
#define EVENT_PE_YELLOW  35
#define EVENT_PE_RED  36
#define EVENT_MSHOLD  37
#define EVENT_MSLOOPITEM  38
#define EVENT_DP_COVER_FRONT  39
#define EVENT_DP_CLEAR_BACK  40
#define EVENT_DP_CLEAR_BACK_SPACE  41
#define EVENT_REPEAT  42
#define EVENT_FIREEVENT  43

//Excel flags
#define EXCEL_DATA_AUTOMATIC 0x01
#define EXCEL_DATA_STRING 0x02
#define EXCEL_DATA_NUMBER 0x04
#define EXCEL_DATE_AS_NUM 0x08
#define EXCEL_USE_COLUMNHEADERS 0x20
#define EXCEL_USE_ROWHEADERS 0x40

// Constants group: TASKTYPE
#define TASKTYPE_LOAD  1
#define TASKTYPE_FRLOAD  2
#define TASKTYPE_UNLOAD  3
#define TASKTYPE_FRUNLOAD  4
#define TASKTYPE_UTILIZE  5
#define TASKTYPE_STOPREQUESTBEGIN  6
#define TASKTYPE_STOPREQUESTFINISH  7
#define TASKTYPE_TRAVEL  8
#define TASKTYPE_TRAVELTOLOC  9
#define TASKTYPE_TRAVELRELATIVE  10
#define TASKTYPE_BREAK  11
#define TASKTYPE_DELAY  12
#define TASKTYPE_SENDMESSAGE  13
#define TASKTYPE_TE_ALLOCATED  14
#define TASKTYPE_MOVEOBJECT  15
#define TASKTYPE_DESTROYOBJECT  16
#define TASKTYPE_SETNODENUM  17
#define TASKTYPE_PICKOFFSET  18
#define TASKTYPE_PLACEOFFSET  19
#define TASKTYPE_TAG  20
#define TASKTYPE_CT_ALLOCATE  21
#define TASKTYPE_CT_DEALLOCATE  22
#define TASKTYPE_CT_SYNC  23
#define TASKTYPE_CALLSUBTASKS  24
#define TASKTYPE_TE_RETURN  25
#define TASKTYPE_TE_STOP  26
#define TASKTYPE_MILESTONE  27
#define TASKTYPE_CT_MULTIALLOCATE  28
#define TASKTYPE_NODEFUNCTION  29
#define TASKTYPE_STARTANIMATION  30
#define TASKTYPE_STOPANIMATION  31
#define TASKTYPE_FREEOPERATORS  32
#define TASKTYPE_WAITFORTASK  33

// Constants group: TASK
#define TASK_TYPE  1
#define TASK_INVOLVED1  2
#define TASK_INVOLVED2  3
#define TASK_VAR1  4
#define TASK_VAR2  5
#define TASK_VAR3  6
#define TASK_VAR4  7
#define TASK_CONTENT  3

// Constants group: TASKSTATE
#define TASKSTATE_UNFINISHED  1
#define TASKSTATE_ACTIVE  2
#define TASKSTATE_FINISHED  3
#define TASKSTATE_COORDINATED  4

// Constants group: PREEMPT
#define PREEMPT_NOT  0
#define PREEMPT_ONLY  1
#define PREEMPT_AND_ABORT_ACTIVE  2
#define PREEMPT_AND_ABORT_ALL  3

// Constants group: STATE
#define STATE_IDLE  1
#define STATE_PROCESSING  2
#define STATE_BUSY  3
#define STATE_BLOCKED  4
#define STATE_GENERATING  5
#define STATE_EMPTY  6
#define STATE_COLLECTING  7
#define STATE_RELEASING  8
#define STATE_WAITING_FOR_OPERATOR  9
#define STATE_WAITING_FOR_TRANSPORT  10
#define STATE_BREAKDOWN  11
#define STATE_SCHEDULED_DOWN  12
#define STATE_CONVEYING  13
#define STATE_TRAVEL_EMPTY  14
#define STATE_TRAVEL_LOADED  15
#define STATE_OFFSET_TRAVEL_EMPTY  16
#define STATE_OFFSET_TRAVEL_LOADED  17
#define STATE_LOADING  18
#define STATE_UNLOADING  19
#define STATE_DOWN  20
#define STATE_SETUP  21
#define STATE_UTILIZE  22
#define STATE_FULL  23
#define STATE_NOT_EMPTY  24
#define STATE_FILLING  25
#define STATE_STARVED  26
#define STATE_MIXING  27
#define STATE_FLOWING  28
#define STATE_ALLOCATED_IDLE  29
#define STATE_OFF_SHIFT  30
#define STATE_CHANGE_OVER  31
#define STATE_REPAIR  32
#define STATE_MAINTENANCE  33
#define STATE_LUNCH  34
#define STATE_ON_BREAK  35
#define STATE_SUSPEND  36
#define STATE_AVAILABLE  37
#define STATE_PREPROCESSING  38
#define STATE_POSTPROCESSING  39
#define STATE_INSPECTING  40
#define STATE_OPERATING  41
#define STATE_STANDBY  42
#define STATE_PURGING  43
#define STATE_CLEANING  44
#define STATE_ACCELERATING  45
#define STATE_MAXSPEED  46
#define STATE_DECELERATING  47
#define STATE_STOPPED  48
#define STATE_WAITING  49
#define STATE_ACCUMULATING  50
#define STATE_END  51

// Constants group: DATATYPE
#define DATATYPE_NUMBER  1
#define DATATYPE_STRING  2
#define DATATYPE_COUPLING  3
#define DATATYPE_OBJECT  4
#define DATATYPE_PARTICLE  5
#define DATATYPE_BUNDLE  6
#define DATATYPE_SIMPLE  7

// Constants group: VARTYPE
#define VAR_TYPE_NULL 0
#define VAR_TYPE_NUMBER 1
#define VAR_TYPE_NODE 2
#define VAR_TYPE_STRING 3
#define VAR_TYPE_INTARRAY 4
#define VAR_TYPE_DOUBLEARRAY 5
#define VAR_TYPE_TREENODEARRAY 6
#define VAR_TYPE_STRINGARRAY 7

// Constants group: SM
#define SM_RESET  1
#define SM_MESSAGE  2
#define SM_EVENT  3
#define SM_DRAW  4
#define SM_INOPEN  5
#define SM_OUTOPEN  6
#define SM_ACCEPT  7
#define SM_GIVE  8
#define SM_ENTER  9
#define SM_EXIT   10
#define SM_COMPILE   11
#define SM_CREATE   12
#define SM_DESTROY   13
#define SM_LOAD   14
#define SM_CLICK   15
#define SM_RUNSTART   16
#define SM_RUNWARM   17
#define SM_RUNEND   18
#define SM_PRELISTEN   19
#define SM_LISTEN   20
#define SM_PREDRAW   21
#define SM_DRAWPLANAR   22
#define SM_PREDRAWPLANAR   23
#define SM_STATECHANGE   24
#define SM_DRAG   25

// Constants group: ARRIVALMODE
#define ARRIVALMODE_INTERARRIVALTIME  1
#define ARRIVALMODE_SCHEDULE  2
#define ARRIVALMODE_SEQUENCE  3

// Constants group: FRSTATE
#define FRSTATE_INQUEUE  1
#define FRSTATE_READY  2
#define FRSTATE_MOVEREQUESTED  3

// Constants group: SPACING
#define SPACING_LENGTH  1
#define SPACING_LENGTHPLUSSETVALUE  2
#define SPACING_SETVALUE  3
#define SPACING_LENGTHTIMESSETVALUE  4

// Constants group: PORT
#define PORT_OPENVARIABLE  1
#define PORT_INSIDECOUPLING  2
#define PORT_EXTRAVAR1  3
#define PORT_EXTRAVAR2  4
#define PORT_EXTRAVAR3  5
#define PORT_EXTRAVAR4  6
#define PORT_EXTRAVAR5  7
#define PORT_EXTRAVAR6  8
#define PORT_EXTRAVAR7  9
#define PORT_EXTRAVAR8  10
#define PORT_EXTRAVAR9  11
#define PORT_EXTRAVAR10  12
#define PORT_EXTRAVAR11  13
#define PORT_EXTRAVAR12  14
#define PORT_EXTRAVAR13  15
#define PORT_EXTRAVAR14  16
#define PORT_EXTRAVAR15  17

// Constants group: VISUALOBJECT
#define VISUALOBJECT_PLANE  1
#define VISUALOBJECT_CUBE  2
#define VISUALOBJECT_COLUMN  3
#define VISUALOBJECT_SPHERE  4
#define VISUALOBJECT_MODEL  5
#define VISUALOBJECT_TEXT  6
#define VISUALOBJECT_SLIDE  7
#define VISUALOBJECT_FLOOR  8

// Constants group: EDGE
#define EDGE_NOCONNECTION  1
#define EDGE_PASSING  2
#define EDGE_NONPASSING  3

// Constants group: DEBUG
#define DEBUG__FLEXSIMOBJECT  1
#define DEBUG__NAVIGATOR  2
#define DEBUG__FIXEDRESOURCE  3
#define DEBUG__TASKEXECUTER  4
#define DEBUG__NETWORKNAVIGATOR  5
#define DEBUG__NETWORKNODE  6
#define DEBUG__PROCESSOR  7
#define DEBUG__SOURCE  8
#define DEBUG__QUEUE  9
#define DEBUG__CONVEYOR  10
#define DEBUG__COMBINER  11
#define DEBUG__SEPARATOR  12
#define DEBUG__RACK  13
#define DEBUG__DISPATCHER  14
#define DEBUG__OPERATOR  15
#define DEBUG__TRANSPORTER  16
#define DEBUG__CRANE  17
#define DEBUG__ASRSVEHICLE  18
#define DEBUG__SINK  19
#define DEBUG__MODEL  20
#define DEBUG__NORECYCLE  21

// Constants group: CONVSECTYPE
#define CONVSECTYPE_STRAIGHT  1
#define CONVSECTYPE_CURVED  2

// Constants group: CONVSEC
#define CONVSEC_TYPE  1
#define CONVSEC_LENGTH  2
#define CONVSEC_RISE  3
#define CONVSEC_ANGLE  4
#define CONVSEC_RADIUS  5
#define CONVSEC_NROFLEGS  6
#define CONVSEC_SECLENGTH  7
#define CONVSEC_STARTLENGTH  8
#define CONVSEC_STARTX  9
#define CONVSEC_STARTY  10
#define CONVSEC_STARTZ  11
#define CONVSEC_STARTANGLE  12

// Constants group: CLASSTYPE
#define CLASSTYPE_ODT  1
#define CLASSTYPE_FLEXSIMOBJECT  2
#define CLASSTYPE_FIXEDRESOURCE  4
#define CLASSTYPE_DISPATCHER  8
#define CLASSTYPE_TASKEXECUTER  0x10
#define CLASSTYPE_NAVIGATOR  0x20
#define CLASSTYPE_PROCESSOR  0x40
#define CLASSTYPE_NETWORKNODE  0x80
#define CLASSTYPE_VISUALTOOL  0x100
#define CLASSTYPE_CONVEYOR  0x200
#define CLASSTYPE_TRAFFICCONTROLLER  0x400
#define CLASSTYPE_MTBFMTTR  0x800
#define CLASSTYPE_MERGESORT  0x1000
#define CLASSTYPE_WANTCONNECTLOGIC  0x2000
#define CLASSTYPE_FLUIDOBJECT  0x4000
#define CLASSTYPE_FLUIDOBJECT2  0x8000
#define CLASSTYPE_LINECONTROLLER  0x10000
#define CLASSTYPE_SYSTEMCONTROLLER  0x20000
#define CLASSTYPE_FLEXSIMEVENTHANDLER 0x40000
#define CLASSTYPE_OWNERDRAWN		0x80000000

// Constants group: RECORDER_DATA
#define RECORDER_DATA_TABLE  1
#define RECORDER_DATA_STANDARD  2
#define RECORDER_DATA_USERDEFINED  3

// Constants group: RECORDER_GRAPH
#define RECORDER_GRAPH_BAR  1
#define RECORDER_GRAPH_PIE  2
#define RECORDER_GRAPH_LINE  3
#define RECORDER_GRAPH_HISTO  4

// Constants group: RECORDER_OUTPUT
#define RECORDER_OUTPUT_GRAPH  1
#define RECORDER_OUTPUT_POINT  2
#define RECORDER_OUTPUT_TABLE  3

// Constants group: DBMODE
#define DBMODE_CLOSED  0
#define DBMODE_SQL  1
#define DBMODE_TABLE  2

// Constants group: ATTCOPY
#define ATTCOPY_ALL  1
#define ATTCOPY_SPATIAL  2
#define ATTCOPY_OFFSETS  4
#define ATTCOPY_VISUAL  8
#define ATTCOPY_MEDIA  16
#define ATTCOPY_LABELS  32
#define ATTCOPY_VARIABLES  64
#define ATTCOPY_DESCRIPTIVE  128
#define ATTCOPY_TABLES  256

// Constants group: SOCKET
#define SOCKET_BLOCK  0
#define SOCKET_NOBLOCK  1

// Constants group: ADV_FUNC
#define ADV_FUNC_CLASSTYPE  1
#define ADV_FUNC_DRAGCONNECTION  2
#define ADV_FUNC_CLICK  3
#define ADV_FUNC_KEYEDCLICK  4
#define ADV_FUNC_ONPREEMPT  5

// kinematic flags
#define KINEMATIC_MANAGE_ROTATIONS 0x1
#define KINEMATIC_DO_NOT_PRUNE 0x2
#define KINEMATIC_NO_UPDATE 0x4
#define KINEMATIC_RELATIVE_LOCS 0x8
#define KINEMATIC_RESET_BUFFER 0x10
#define KINEMATIC_MANAGE_ROT_OVERRIDE 0x20

// Constants group: KINEMATIC
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
#define KINEMATIC_STARTANGLE  39
#define KINEMATIC_TURNANGLE  40
#define KINEMATIC_TURNRADIUS  41
#define KINEMATIC_PRUNE  42

#define KINEMATIC_TRAVEL  1
#define KINEMATIC_ROTATE  2
#define KINEMATIC_TURN_XY  3
#define KINEMATIC_TURN_YZ  4
#define KINEMATIC_TURN_ZX  5

// Constants group: MTBF_MTTR
#define MTBF_MTTR_BEGIN_DOWN_TIME  1
#define MTBF_MTTR_BEGIN_DOWN_TIME_NO_RESUME  2
#define MTBF_MTTR_FINISH_DOWN_TIME  3
#define MTBF_MTTR_FINISH_DOWN_TIME_NO_RESUME  4

// commands
#define OPT_VARIABLE 1
#define OPT_CONSTRAINT 2
#define OPT_OBJECTIVE 3
#define OPT_SETTINGS 4
#define OPT_STATUS 5
#define OPT_ENGINE 6
#define OPT_PREPARE 7

// variables/constraints/singleObj (action)
#define OPT_ADD 1
#define OPT_SETVALUE 2
#define OPT_GETVALUE 3
#define OPT_GETVALUE_N 4

// types (numparams)

#define OPT_TYPE_CONTINUOUS   1
#define OPT_TYPE_DISCRETE     2
#define OPT_TYPE_DESIGN       3
#define OPT_TYPE_INTEGER      4
#define OPT_TYPE_BINARY       5
#define OPT_TYPE_PERMUTATION  6
#define OPT_TYPE_USERCONTROLLED  7
#define OPT_ADD_PERMUTATION_GROUP 8

// multi-objective (action)
#define OPT_ADD_MW_MASTER 5
#define OPT_ADD_MW_WEIGHT 6
#define OPT_ADD_MW_GOAL 7
#define OPT_ADD_MW_RANGE 8
#define OPT_ADD_PTRN_MASTER 9
#define OPT_ADD_PTRN_SUB 10

#define OPT_GETVALUE_MASTER 11
#define OPT_GETVALUE_SUB 12
#define OPT_GETVALUE_MASTER_N 13
#define OPT_GETVALUE_SUB_N 14

// setting (action)
// replications
#define OPT_SET_MAX_REPS 1
#define OPT_SET_MIN_REPS 2
#define OPT_SET_CONFIDENCE 3
#define OPT_USE_REPS 4

// stop conditions
#define OPT_SET_STOPITERATION 5
#define OPT_SET_STOPTIME 6
#define OPT_SET_USERSTOP 7

#define OPT_EVAL_IN_ORDER 8

#define OPT_LOG_SETUP 9
#define OPT_LOG_SOLUTIONS 10

// status (action)
#define OPT_ITERATION 1
#define OPT_FRONTIER 2
#define OPT_TIME 3
#define OPT_PAUSED 4

// queries (numparam)
#define OPT_ISFEASIBLE 5
#define OPT_ISPARETO 6
#define OPT_GET_STDDEV 7
#define OPT_GET_NUMREPS 8
#define OPT_ISLASTREP 9
#define OPT_ISMETCONF 10
#define OPT_TERMINATION 11

// Confidence Types (numparam)
#define OPT_CONF0 0
#define OPT_CONF1 1
#define OPT_CONF2 2

// engine
#define OPT_OPTIMIZE 1
#define OPT_STOP 2
#define OPT_PAUSE 3
#define OPT_CONTINUE 4 
#define OPT_RESET 5
#define OPT_READY 6

// scenario
#define OPT_CREATE_BLANK_SOLUTION 1
#define OPT_SUGGEST_SOLUTION 2

#define ITEMVAR_PROCESSBEGINTIME 1
#define ITEMVAR_PROCESSTIME 2
#define ITEMVAR_SETUPTIME 3

#ifdef DOUBLE_CLICK
	#undef DOUBLE_CLICK
#endif
#define DOUBLE_CLICK 1
#define LEFT_PRESS 2
#define LEFT_RELEASE 3
#define RIGHT_PRESS 4
#define RIGHT_RELEASE 5

#define SCI_START 2000
#define SCI_OPTIONAL_START 3000
#define SCI_LEXER_START 4000
#define SCI_ADDTEXT 2001
#define SCI_ADDSTYLEDTEXT 2002
#define SCI_INSERTTEXT 2003
#define SCI_CLEARALL 2004
#define SCI_CLEARDOCUMENTSTYLE 2005
#define SCI_GETLENGTH 2006
#define SCI_GETCHARAT 2007
#define SCI_GETCURRENTPOS 2008
#define SCI_GETANCHOR 2009
#define SCI_GETSTYLEAT 2010
#define SCI_REDO 2011
#define SCI_SETUNDOCOLLECTION 2012
#define SCI_SELECTALL 2013
#define SCI_SETSAVEPOINT 2014
#define SCI_GETSTYLEDTEXT 2015
#define SCI_CANREDO 2016
#define SCI_MARKERLINEFROMHANDLE 2017
#define SCI_MARKERDELETEHANDLE 2018
#define SCI_GETUNDOCOLLECTION 2019
#define SCWS_INVISIBLE 0
#define SCWS_VISIBLEALWAYS 1
#define SCWS_VISIBLEAFTERINDENT 2
#define SCI_GETVIEWWS 2020
#define SCI_SETVIEWWS 2021
#define SCI_POSITIONFROMPOINT 2022
#define SCI_POSITIONFROMPOINTCLOSE 2023
#define SCI_GOTOLINE 2024
#define SCI_GOTOPOS 2025
#define SCI_SETANCHOR 2026
#define SCI_GETCURLINE 2027
#define SCI_GETENDSTYLED 2028
#define SC_EOL_CRLF 0
#define SC_EOL_CR 1
#define SC_EOL_LF 2
#define SCI_CONVERTEOLS 2029
#define SCI_GETEOLMODE 2030
#define SCI_SETEOLMODE 2031
#define SCI_STARTSTYLING 2032
#define SCI_SETSTYLING 2033
#define SCI_GETBUFFEREDDRAW 2034
#define SCI_SETBUFFEREDDRAW 2035
#define SCI_SETTABWIDTH 2036

#define SCI_MARKERDEFINE 2040
#define SCI_MARKERSETFORE 2041
#define SCI_MARKERSETBACK 2042
#define SCI_MARKERADD 2043
#define SCI_MARKERDELETE 2044
#define SCI_MARKERDELETEALL 2045
#define SCI_MARKERGET 2046
#define SCI_MARKERNEXT 2047
#define SCI_MARKERPREVIOUS 2048
#define SCI_MARKERDEFINEPIXMAP 2049
#define SCI_MARKERADDSET 2466
#define SCI_MARKERSETALPHA 2476

#define FS_MARKER_MARKLINE 0
#define FS_MARKER_BREAK_POINT 1
#define FS_MARKER_DISABLED_BREAK_POINT 2
#define FS_MARKER_CODE_POINT 3

#define SC_MARK_ROUNDRECT 1
#define SC_MARK_ARROW 2
#define SC_MARK_SMALLRECT 3
#define SC_MARK_SHORTARROW 4
#define SC_MARK_EMPTY 5
#define SC_MARK_ARROWDOWN 6
#define SC_MARK_MINUS 7
#define SC_MARK_PLUS 8
#define SC_MARK_VLINE 9
#define SC_MARK_LCORNER 10
#define SC_MARK_TCORNER 11
#define SC_MARK_BOXPLUS 12
#define SC_MARK_BOXPLUSCONNECTED 13
#define SC_MARK_BOXMINUS 14
#define SC_MARK_BOXMINUSCONNECTED 15
#define SC_MARK_LCORNERCURVE 16
#define SC_MARK_TCORNERCURVE 17
#define SC_MARK_CIRCLEPLUS 18
#define SC_MARK_CIRCLEPLUSCONNECTED 19
#define SC_MARK_CIRCLEMINUS 20
#define SC_MARK_CIRCLEMINUSCONNECTED 21
#define SC_MARK_BACKGROUND 22
#define SC_MARK_DOTDOTDOT 23
#define SC_MARK_ARROWS 24
#define SC_MARK_PIXMAP 25
#define SC_MARK_FULLRECT 26
#define SC_MARK_LEFTRECT 27
#define SC_MARK_AVAILABLE 28
#define SC_MARK_UNDERLINE 29

#define SC_MARGIN_SYMBOL 0
#define SC_MARGIN_NUMBER 1
#define SC_MARGIN_BACK 2
#define SC_MARGIN_FORE 3
#define SC_MARGIN_TEXT 4
#define SC_MARGIN_RTEXT 5

#define SCI_SETMARGINTYPEN 2240
#define SCI_GETMARGINTYPEN 2241
#define SCI_SETMARGINWIDTHN 2242
#define SCI_GETMARGINWIDTHN 2243
#define SCI_SETMARGINMASKN 2244
#define SCI_GETMARGINMASKN 2245
#define SCI_SETMARGINSENSITIVEN 2246
#define SCI_GETMARGINSENSITIVEN 2247

#define SCI_GETTABWIDTH 2121
#define SCI_SETINDENT 2122
#define SCI_GETINDENT 2123
#define SCI_SETUSETABS 2124
#define SCI_GETUSETABS 2125
#define SCI_SETLINEINDENTATION 2126
#define SCI_GETLINEINDENTATION 2127
#define SCI_GETLINEINDENTPOSITION 2128
#define SCI_GETCOLUMN 2129
#define SCI_SETHSCROLLBAR 2130
#define SCI_GETHSCROLLBAR 2131
#define SCI_SETINDENTATIONGUIDES 2132
#define SCI_GETINDENTATIONGUIDES 2133
#define SCI_SETHIGHLIGHTGUIDE 2134
#define SCI_GETHIGHLIGHTGUIDE 2135
#define SCI_GETLINEENDPOSITION 2136
#define SCI_GETCODEPAGE 2137
#define SCI_GETCARETFORE 2138
#define SCI_GETUSEPALETTE 2139
#define SCI_GETREADONLY 2140
#define SCI_SETCURRENTPOS 2141
#define SCI_SETSELECTIONSTART 2142
#define SCI_GETSELECTIONSTART 2143
#define SCI_SETSELECTIONEND 2144
#define SCI_GETSELECTIONEND 2145
#define SCI_SETPRINTMAGNIFICATION 2146
#define SCI_GETPRINTMAGNIFICATION 2147
#define SC_PRINT_NORMAL 0
#define SC_PRINT_INVERTLIGHT 1
#define SC_PRINT_BLACKONWHITE 2
#define SC_PRINT_COLOURONWHITE 3
#define SC_PRINT_COLOURONWHITEDEFAULTBG 4
#define SCI_SETPRINTCOLOURMODE 2148
#define SCI_GETPRINTCOLOURMODE 2149
#define SCFIND_WHOLEWORD 2
#define SCFIND_MATCHCASE 4
#define SCFIND_WORDSTART 0x00100000
#define SCFIND_REGEXP 0x00200000
#define SCFIND_POSIX 0x00400000
#define SCI_FINDTEXT 2150
#define SCI_FORMATRANGE 2151
#define SCI_GETFIRSTVISIBLELINE 2152
#define SCI_GETLINE 2153
#define SCI_GETLINECOUNT 2154
#define SCI_SETMARGINLEFT 2155
#define SCI_GETMARGINLEFT 2156
#define SCI_SETMARGINRIGHT 2157
#define SCI_GETMARGINRIGHT 2158
#define SCI_GETMODIFY 2159
#define SCI_SETSEL 2160
#define SCI_GETSELTEXT 2161
#define SCI_GETTEXTRANGE 2162
#define SCI_HIDESELECTION 2163
#define SCI_POINTXFROMPOSITION 2164
#define SCI_POINTYFROMPOSITION 2165
#define SCI_LINEFROMPOSITION 2166
#define SCI_POSITIONFROMLINE 2167
#define SCI_LINESCROLL 2168
#define SCI_SCROLLCARET 2169
#define SCI_REPLACESEL 2170
#define SCI_SETREADONLY 2171
#define SCI_NULL 2172
#define SCI_CANPASTE 2173
#define SCI_CANUNDO 2174
#define SCI_EMPTYUNDOBUFFER 2175
#define SCI_UNDO 2176
#define SCI_CUT 2177
#define SCI_COPY 2178
#define SCI_PASTE 2179
#define SCI_CLEAR 2180
#define SCI_SETTEXT 2181
#define SCI_GETTEXT 2182
#define SCI_GETTEXTLENGTH 2183
#define SCI_GETDIRECTFUNCTION 2184
#define SCI_GETDIRECTPOINTER 2185

#define SCI_SETTARGETSTART 2190
#define SCI_GETTARGETSTART 2191
#define SCI_SETTARGETEND 2192
#define SCI_GETTARGETEND 2193
#define SCI_REPLACETARGET 2194
#define SCI_REPLACETARGETRE 2195
#define SCI_SEARCHINTARGET 2197
#define SCI_SETSEARCHFLAGS 2198
#define SCI_GETSEARCHFLAGS 2199

#define SCI_WORDSTARTPOSITION 2266
#define SCI_WORDENDPOSITION 2267

#define SCI_TARGETFROMSELECTION 2287

#define SCI_SEARCHANCHOR 2366
#define SCI_SEARCHNEXT 2367
#define SCI_SEARCHPREV 2368


/* BeginMode */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007
#define GL_QUAD_STRIP                     0x0008
#define GL_POLYGON                        0x0009

/* enabling/disabling*/
#define GL_FOG                            0x0B60
#define GL_LIGHTING                       0x0B50
#define GL_TEXTURE_2D                     0x0DE1
#define GL_DEPTH_TEST                     0x0B71
#define GL_TEXTURE_GEN_S                  0x0C60
#define GL_TEXTURE_GEN_T                  0x0C61
#define GL_TEXTURE_GEN_R                  0x0C62
#define GL_TEXTURE_GEN_Q                  0x0C63


/* AttribMask */
#define GL_LIGHTING_BIT                   0x00000040
#define GL_ENABLE_BIT                     0x00002000
#define GL_ALL_ATTRIB_BITS                0x000fffff

/* Mesh Class */
#define MESH_POSITION               0x0
#define MESH_TEX_COORD1             0x0010000
#define MESH_TEX_COORD2             0x0020000
#define MESH_TEX_COORD3             0x0040000
#define MESH_NORMAL                 0x0080000
#define MESH_AMBIENT                0x0100000
#define MESH_DIFFUSE                0x0200000
#define MESH_DIFFUSE4               0x0400000
#define MESH_AMBIENT_AND_DIFFUSE    0x0800000
#define MESH_AMBIENT_AND_DIFFUSE4   0x1000000
#define MESH_SPECULAR               0x2000000
#define MESH_SHININESS              0x4000000
#define MESH_EMISSIVE               0x8000000

#define MESH_STATIC_DRAW 			0x1
#define MESH_DYNAMIC_DRAW 			0x2
#define MESH_INDEXED 				0x4

#define MESH_PER_VERTEX_ATTRIBS 1
#define MESH_PER_MESH_ATTRIBS 2
#define MESH_FLAGS 3
#define MESH_NR_VERTS 4
#define MESH_GET_INDEX 5

#define MESH_COLOR_RED 0
#define MESH_COLOR_GREEN 1
#define MESH_COLOR_BLUE 2
#define MESH_COLOR_ALPHA 3
#define MESH_POS_X 0
#define MESH_POS_Y 1
#define MESH_POS_Z 2
#define MESH_TEX_S 0
#define MESH_TEX_T 1
#define MESH_TEX_R 2
#define MESH_TEX_Q 3

// Texture Channels
#define TEX_UNIT_SHADOWS 1
#define TEX_UNIT_HEIGHT 2
#define TEX_UNIT_NORMAL 3

// this should be the same as -FLT_MAX
#define DISPATCHER_ABORT_QUEUE_STRATEGY -340282346600000000000000000000000000000.0

#define NETWORK_INFO_ORIGIN_NET_NODE_RANK 1
#define NETWORK_INFO_DEST_NET_NODE_RANK 2
#define NETWORK_INFO_DISTANCE 3
#define NETWORK_INFO_CUR_DIST_ALONG_EDGE 4
#define NETWORK_INFO_CUR_TRAVEL_DEST_RANK 5
#define NETWORK_INFO_CUR_TRAVEL_ORIGIN_RANK 6

#define LICENSE_TYPE_NONE 0
#define LICENSE_TYPE_STANDARD 1
#define LICENSE_TYPE_RUNTIME 2
#define LICENSE_TYPE_EDUCATIONAL 3
#define LICENSE_TYPE_CUSTOM 4

#define CLF_ADMIN				0x00000010
#define CLF_DRAG_DROP_CONNECT	0x00000800
#define CLF_CREATE_OBJECTS		0x00000400
#define CLF_NO_MODEL_LIMIT		0x00000200
#define CLF_STOCHASTICS			0x00000100
#define CLF_ENTIRE_TREE			0x00008000
#define CLF_MODEL_TREE			0x00004000
#define CLF_CONSOLE_SCRIPT		0x00002000
#define CLF_COMPILE				0x00001000
#define CLF_COMMERCIAL_USE		0x00080000
#define CLF_EXPERTFIT			0x00040000
#define CLF_OPTQUEST			0x00020000
#define CLF_XMLSAVELOAD			0x00010000

#define UNDO_AGGREGATED 1
#define UNDO_MOVE_SIZE_ROTATE 2
#define UNDO_MOVE_SIZE_ROTATE_GROUP 3
#define UNDO_SELECTION_CHANGE 4
#define UNDO_CREATE_OBJECT 5 // creates an object/node
#define UNDO_DELETE_OBJECT 6 // deletes an object/node
#define UNDO_CHANGE_DATA 7 // includes set(), sets(), nodeadddata, etc.
#define UNDO_CHANGE_RANK 8
#define UNDO_CHANGE_NAME 9
#define UNDO_MOVE_OBJECT 10
#define UNDO_DELETE_COUPLING 11
#define UNDO_BREAK_COUPLING 12
#define UNDO_AGGREGATED_FIRST_RECORD 13 // a no-op record that serves as a simple placeholder for the "current record" pointer when doing and aggregated undo
#define UNDO_DESTROY_BRANCH 14
#define UNDO_CHANGE_FLAGS 15
#define UNDO_REPLACE_OBJECT 16
#define UNDO_CUSTOM 17
#define UNDO_CALLBACK 18
#define UNDO_CHANGE_NUMBER_DATA 19 // used only as a sub-record of a move/size/rotate
#define UNDO_UPDATE_LINKS_ON_UNDO 20
#define UNDO_UPDATE_LINKS_ON_REDO 21

#define UNDO_UPDATE_ADD_SELECTION 1
#define UNDO_UPDATE_ADD_UNSELECTION 2

#define USC_RESET_VIEW_SELECTIONS 1
#define USC_SELECT_SUB_TREE 2
#define USC_UNSELECT_SUB_TREE 3

#define PICK_OPERATOR_SETUP 1
#define PICK_OPERATOR_PROCESS 2
#define PICK_OPERATOR_SETUP_RELEASE 3
#define PICK_OPERATOR_PROCESS_RELEASE 4

#define REMEMBER_WINDOW_SIZES !objectexists(node("VIEW:/environment/dev"))

#define TC_ON_ENTRY_REQUEST_DEFAULT 0
#define TC_ON_ENTRY_REQUEST_ALLOW 1
#define TC_ON_ENTRY_REQUEST_QUEUE 2

#define TCI_NR_ACTIVE_TRAVELERS 1
#define TCI_ACTIVE_TRAVELER 2
#define TCI_ACTIVE_TRAVELER_COUPLING 3
#define TCI_ACTIVE_TRAVELER_RANK_FROM_TRAVELER 4
#define TCI_NR_MEMBERS 5
#define TCI_MEMBER 6
#define TCI_MEMBER_COUPLING 7
#define TCI_MEMBER_RANK_FROM_NETWORK_NODE 8
#define TCI_NR_ENTRY_REQUESTS 9
#define TCI_ENTRY_REQUEST_TRAVELER 10
#define TCI_ENTRY_REQUEST_NETWORK_NODE 11
#define TCI_ENTRY_REQUEST_NODE 12
#define TCI_ALLOW_ENTRY 13
#define TCI_SET_ENTRY_REQUEST_RANK 14

#define LA_PROCESS_ASR_FROM_BUFFER 1
#define LA_PROCESS_ASR_FROM_FILE 2
#define LA_PROCESS_ACTIVATION_RESPONSE_FROM_BUFFER 3
#define LA_PROCESS_ACTIVATION_RESPONSE_FROM_FILE 4
#define LA_SUBMIT_ACTIVATION_REQUEST 5
#define LA_WRITE_ACTIVATION_REQUEST_TO_FILE 6
#define LA_SET_ACTIVATION_SERVER_PARAMS 7
#define LA_SET_PROXY_DETAILS 8
#define LA_DISPLAY_TRUSTED_STORAGE_CONTENTS 9
#define LA_RETURN_FULFILLMENT_RECORD 10
#define LA_REPAIR_FULFILLMENT_RECORD 11
#define LA_SET_ENTITLEMENT_ID 12
#define LA_SET_FULFILLMENT_ID 13
#define LA_GET_TRUSTED_STORAGE_CONTENTS_INFO 14
#define LA_WRITE_REPAIR_REQUEST_TO_FILE 15
#define LA_PROCESS_REPAIR_RESPONSE_FROM_FILE 16
#define LA_DELETE_FULFILLMENT_RECORD 17
#define LA_SET_EXPIRATIONDATE 18
#define LA_LF_BORROW_CHECKOUT 19
#define LA_GET_LF_BORROWED_CONTENTS_INFO 20
#define LA_PROCESS_RETURN_RESPONSE_FROM_FILE 21
#define LA_LF_BORROW_RETURN 22
#define LA_HAS_TRUSTED_STORAGE_CONTENTS 23
#define LA_SEND_UPGRADE_REQUEST 24
#define LA_REEVALUATE_LICENSE 25

#define ANIM_INFO_BODIES 1
#define ANIM_INFO_ANIMATIONS 2
#define ANIM_INFO_VARIABLES 3

#define ANIM_VAR_SURROGATE 1
#define ANIM_VAR_KEYFRAME_VAL 2
#define ANIM_VAR_COMPONENT_VAL 3
#define ANIM_VAR_KEYFRAME_GAP 4
#define ANIM_VAR_COMPONENT 5

#define ANIMATION_CONTENT 12
#define ANIMATION_KEYFRAMES 1
#define ANIMATION_REPEAT_TYPE 2
#define ANIMATION_REPEAT_VALUE 3
#define ANIMATION_TIME_TYPE 4
#define ANIMATION_START_STATE 5
#define ANIMATION_START_TIME 6
#define ANIMATION_TIME_SCALE 7
#define ANIMATION_CUR_REPEAT_TYPE 8
#define ANIMATION_CUR_REPEAT_VALUE 9
#define ANIMATION_LAST_UPDATE_TIME 10
#define ANIMATION_TRIGGERS 11
#define ANIMATION_CLIPS 12

#define REPEAT_TYPE_DEFAULT 0
#define REPEAT_TYPE_NONE 1
#define REPEAT_TYPE_IMMEDIATE 2
#define REPEAT_TYPE_NR_ITERATIONS 3
#define REPEAT_TYPE_USE_TIME 4
#define REPEAT_TYPE_TIME_AFTER_END 5

#define KEYFRAME_CONTENT 2
#define KEYFRAME_BODIES 1
#define KEYFRAME_TRIGGER 2

#define KEYFRAME_BODY_X 1
#define KEYFRAME_BODY_Y 2
#define KEYFRAME_BODY_Z 3
#define KEYFRAME_BODY_SX 4
#define KEYFRAME_BODY_SY 5
#define KEYFRAME_BODY_SZ 6
#define KEYFRAME_BODY_RX 7
#define KEYFRAME_BODY_RY 8
#define KEYFRAME_BODY_RZ 9
#define KEYFRAME_BODY_RED 10
#define KEYFRAME_BODY_GREEN 11
#define KEYFRAME_BODY_BLUE 12
#define KEYFRAME_BODY_SHAPE_FRAME 13

#define START_STATE_BODY_SCALE_X 10
#define START_STATE_BODY_SCALE_Y 11
#define START_STATE_BODY_SCALE_Z 12
#define START_STATE_BODY_SCALE_SX 13
#define START_STATE_BODY_SCALE_SY 14
#define START_STATE_BODY_SCALE_SZ 15

#define SPEED_TYPE_DEFAULT 0
#define SPEED_TYPE_DURATION 1
#define SPEED_TYPE_MULTIPLIER 2

#define RESIZE_INFO_BASE_SIZE 1
#define RESIZE_INFO_BODIES 2

#define RESIZE_BODY_X 1
#define RESIZE_BODY_Y 2
#define RESIZE_BODY_Z 3
#define RESIZE_BODY_RX 4
#define RESIZE_BODY_RY 5
#define RESIZE_BODY_RZ 6
#define RESIZE_BODY_SX 7
#define RESIZE_BODY_SY 8
#define RESIZE_BODY_SZ 9
#define RESIZE_BODY_X_MAP 10
#define RESIZE_BODY_Y_MAP 11
#define RESIZE_BODY_Z_MAP 12

#define DEBUG_STOP 0
#define DEBUG_STEP 1
#define DEBUG_CONTINUE 2
#define DEBUG_IS_STOPPED 3
#define DEBUG_GET_LINE_NR 4
#define DEBUG_DUMP_VARIABLES 5
#define DEBUG_STOP_SIMULATION 6
#define DEBUG_REFRESH_BREAK_POINTS 7
#define DEBUG_ADD_BREAK_POINT 8
#define DEBUG_DELETE_BREAK_POINT 9
#define DEBUG_GET_WATCH_VARIABLE 10
#define DEBUG_ENABLE_CODE_PROFILING 11
#define DEBUG_PRINT_CODE_PROFILING_INFO 12
#define DEBUG_RESET_CODE_PROFILING 13
#define DEBUG_DUMP_CALL_STACK 14
#define DEBUG_STEP_INTO 15

#define ELI_GET_OBJECTPATH 1
#define ELI_GET_INVOLVEDPATH 2
#define ELI_GET_OTHERPATH 3
#define ELI_EVENTTYPE_NAME 4
#define ELI_LOGGEDEVENTTYPE_NAME 5


#define PICK_SIZER -1

#define PICK_CONNECTOR -2

#define PICK_ADDINPUTCONNECTOR -10
#define PICK_REMOVEINPUTCONNECTOR -11
#define PICK_ADDOUTPUTCONNECTOR -12
#define PICK_REMOVEOUTPUTCONNECTOR -13
#define PICK_ADDCENTRECONNECTOR -14
#define PICK_REMOVECENTRECONNECTOR -15
#define PICK_ITEMDATA -16
#define PICK_ITEMLABEL -17
#define PICK_EXPANDER -18
#define PICK_TEXTAREA -19
#define PICK_SIZERVERTICAL -20
#define PICK_TREEICONTOP -21
#define PICK_TREEICONBOTTOM -22
#define PICK_SIZERX -30
#define PICK_SIZERY -31
#define PICK_SIZERZ -32
#define PICK_SIZERXNEG -33
#define PICK_SIZERYNEG -34
#define PICK_SIZERZNEG -35

#define OBJECT_PART_SIZER_X 1
#define OBJECT_PART_SIZER_Y 2
#define OBJECT_PART_SIZER_Z 3
#define OBJECT_PART_SIZER_X_NEG 4
#define OBJECT_PART_SIZER_Y_NEG 5
#define OBJECT_PART_SIZER_Z_NEG 6
#define OBJECT_PART_YELLOW_HIGHLIGHT 7
#define OBJECT_PART_HOVER_HIGHLIGHT 8
#define OBJECT_PART_GREEN_HIGHLIGHT 9
#define OBJECT_PART_RED_HIGHLIGHT 10

#define PICK_OBJECT 1
#define PICK_TYPE 2
#define PICK_SECONDARY_OBJECT 3

#define DRAG_INFO_DX 1
#define DRAG_INFO_DY 2
#define DRAG_INFO_DZ 3
#define DRAG_INFO_MDX 4
#define DRAG_INFO_MDY 5
#define DRAG_INFO_BUTTON_STATE 6
#define DRAG_INFO_SET_DX 7
#define DRAG_INFO_SET_DY 8
#define DRAG_INFO_SET_DZ 9
#define DRAG_INFO_SET_MDX 10
#define DRAG_INFO_SET_MDY 11
#define DRAG_INFO_SET_BUTTON_STATE 12
#define DRAG_INFO_SNAPPED_DX 13
#define DRAG_INFO_SNAPPED_DY 14
#define DRAG_INFO_SNAPPED_DZ 15

#define PICK_ASRS_RAIL_X 1
#define PICK_ASRS_RAIL_X_NEG 2

#define PICK_CRANE_LEG_X 10
#define PICK_CRANE_LEG_Y 11
#define PICK_CRANE_BEAM_Y 12
#define PICK_CRANE_BEAM_Z 13
#define PICK_CRANE_BRIDGE_X 14
#define PICK_CRANE_BRIDGE_Z 15
#define PICK_CRANE_FRAME_X 16
#define PICK_CRANE_FRAME_Y 17
#define PICK_CRANE_FRAME_Z 18

#define PICK_ELEVATOR_FRAME_Z 20

#define DETECT_DRAG_XY 0
#define DETECT_DRAG_XZ 1
#define DETECT_DRAG_YZ 2
#define DETECT_DRAG_X 3
#define DETECT_DRAG_Y 4
#define DETECT_DRAG_Z 5

#define DASHBOARD_WINDOW_MODE_MOVING 1
#define DASHBOARD_WINDOW_MODE_RESIZING_X 2
#define DASHBOARD_WINDOW_MODE_RESIZING_SX 3
#define DASHBOARD_WINDOW_MODE_RESIZING_Y 4
#define DASHBOARD_WINDOW_MODE_RESIZING_SY 5
#define DASHBOARD_WINDOW_MODE_RESIZING_XY 6
#define DASHBOARD_WINDOW_MODE_RESIZING_SXY 7
#define DASHBOARD_WINDOW_MODE_RESIZING_SXSY 8
#define DASHBOARD_WINDOW_MODE_RESIZING_XSY 9

#define CHART_TYPE_HORIZONTAL_BAR 1
#define CHART_TYPE_VERTICAL_BAR 2
#define CHART_TYPE_PIE 3
#define CHART_TYPE_LINE 4
#define CHART_TYPE_DATA_TABLE 5
#define CHART_TYPE_TIME_PLOT 6
#define CHART_TYPE_TIME_SERIES_HISTOGRAM 7
#define CHART_TYPE_FINANCIAL 8
#define CHART_TYPE_GANTT 9

#define CURSOR_DEFAULT 1
#define CURSOR_SIZE_XY 8
#define CURSOR_SIZE_YX 9
#define CURSOR_SIZE_X 10
#define CURSOR_SIZE_Y 11
#define CURSOR_MOVE 12

#define STAT_SUCCESS 0
#define STAT_ERR_UNABLE -1
#define STAT_ERR_AGGREGATE -2

#define STAT_DRAW_INVLD_DATA 1
#define STAT_DRAW_FILTERED 2
#define STAT_DRAW_MAXTIME 3
#define STAT_DRAW_SKIP 4

#define AGGREGATION_TYPE_NONE 0
#define AGGREGATION_TYPE_ONE 1
#define AGGREGATION_TYPE_MANY 2
#define AGGREGATION_TYPE_NAMED_LIST 3

#define STAT_CONTENT 0
#define STAT_CONTENT_AVG 1
#define STAT_CONTENT_MIN 2
#define STAT_CONTENT_MAX 3
#define STAT_INPUT 4
#define STAT_OUTPUT 5
#define STAT_STAYTIME_AVG 6
#define STAT_STAYTIME_MIN 7
#define STAT_STAYTIME_MAX 8
#define STAT_STATE_TOTAL 9
#define STAT_STATE_PERCENT 10
#define STAT_STATE_AVG 11
#define STAT_COMBINED 12
#define STAT_INPUT_AVG 13
#define STAT_OUTPUT_AVG 14
#define STAT_STAYTIME 15

#define APPLY_LINKS_ON_OPEN 1
#define APPLY_LINKS_ON_CHANGE_OBJECT 2

#define EXP_VAR_TYPE 1
#define EXP_VAR_NAME 2
#define EXP_VAR_SAVE_DATA 3

#define EXP_VAR_ON_REMOVE 1
#define EXP_VAR_SET_SCENARIO 2

#define EXP_VAR_CONTENT 3

#define BUNDLE_FLAG_UNPAGED 0x1
#define BUNDLE_FLAG_KEYED 0x2
#define BUNDLE_FLAG_SORTED 0x4

#define BUNDLE_FIELD_TYPE_DOUBLE 1
#define BUNDLE_FIELD_TYPE_INT 2
#define BUNDLE_FIELD_TYPE_STR 3
#define BUNDLE_FIELD_TYPE_FLOAT 4


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
#define SM_LOAD 14
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

#define LISTENER_INFO_CODE 1
#define LISTENER_INFO_ASSOCIATED 2
#define LISTENER_INFO_COUPLING 3

#define CWSM_END 0
#define CWSM_DOUBLE 1
#define CWSM_NODE 2
#define CWSM_STRING 3
#define CWSM_BUNDLE_DATA 4
#define CWSM_BUNDLE_HEADER 5
#define CWSM_BUNDLE_RANGE 6
#define CWSM_BUNDLE 7
#define CWSM_BINARY_BYTEBLOCK 8
#define CWSM_JSON 9

#define STATE_PROFILE_CURRENT 1
#define STATE_PROFILE_SINCE 2
#define STATE_PROFILE_LIST 3

// Constants group: TIME
#define TIME_NAME  1
#define TIME_PLURAL_NAME  2
#define TIME_ABBREVIATION  3
#define TIME_MULTIPLE  4

// Constants group: LENGTH
#define LENGTH_NAME  11
#define LENGTH_PLURAL_NAME  12
#define LENGTH_ABBREVIATION  13
#define LENGTH_MULTIPLE  14

// Constants group: FLUID
#define FLUID_NAME  21
#define FLUID_PLURAL_NAME  22
#define FLUID_ABBREVIATION  23
#define FLUID_MULTIPLE  24
#define FLUID_TYPE 25

//Constants group: DATE & TIME
#define DATE_TIME_NODE 31
#define START_TIME 32
#define START_TIME_NODE 33
#define CURRENT_TIME 34
#define CURRENT_TIME_NODE 35
#define STOP_TIME 36
#define STOP_TIME_NODE 37
#define TIME_FORMAT 38
#define DATE_FORMAT 39

//Constants group: START TIME
#define START_YEAR 41
#define START_MONTH 42
#define START_DAY 43
#define START_DAYOFWEEK 44
#define START_HOUR 45
#define START_MINUTE 46
#define START_SECOND 47
#define START_MILLISECOND 48

//Constants group: CURRENT TIME
#define CURRENT_YEAR 51
#define CURRENT_YEAR_OF_TIME 52
#define CURRENT_MONTH_OF_YEAR 53
#define CURRENT_DAY 54
#define CURRENT_DAY_OF_MONTH 55
#define CURRENT_DAY_OF_WEEK 56
#define CURRENT_HOUR 57
#define CURRENT_HOUR_OF_DAY 58
#define CURRENT_MINUTE 59
#define CURRENT_MINUTE_OF_HOUR 60
#define CURRENT_SECOND 61
#define CURRENT_SECOND_OF_MINUTE 62
#define CURRENT_MILLISECOND 63
#define CURRENT_MILLISECOND_OF_SECOND 64

#define START_TIME_STR 71
#define CURRENT_TIME_STR 72
#define STOP_TIME_STR 73

// Constants group: FLUID CONVEYOR
#define FLUID_CONVEYOR_DIRECTION_FORWARD  1
#define FLUID_CONVEYOR_DIRECTION_REVERSE  2

#define FLUID_CONVEYOR_LAYOUT_AUX_CONVEYOR_ALPHA  1
#define FLUID_CONVEYOR_LAYOUT_AUX_ENDPOINTS  2
#define FLUID_CONVEYOR_LAYOUT_AUX_NORMALS  3
#define FLUID_CONVEYOR_LAYOUT_AUX_DIRECTION_INDICATORS  4

#define FLUID_CONVEYOR_LAYOUT_AUX_DIRECTION_INDICATORS_VERTICES  1
#define FLUID_CONVEYOR_LAYOUT_AUX_DIRECTION_INDICATORS_COLORS  2

#define FLUID_CONVEYOR_INFO_LEAD_X_POSITION_1_BASED  1
#define FLUID_CONVEYOR_INFO_MID_X_POSITION_1_BASED  2
#define FLUID_CONVEYOR_INFO_LEAD_RIGHT_Y_POSITION_1_BASED  3
#define FLUID_CONVEYOR_INFO_MID_RIGHT_Y_POSITION_1_BASED  4
#define FLUID_CONVEYOR_INFO_LEAD_LEFT_Y_POSITION_1_BASED  5
#define FLUID_CONVEYOR_INFO_MID_LEFT_Y_POSITION_1_BASED  6
#define FLUID_CONVEYOR_INFO_CONTENT_Z_FACTOR_1_BASED  7
#define FLUID_CONVEYOR_INFO_CONTENT_Z_FACTOR  8
#define FLUID_CONVEYOR_INFO_INVERSE_Z_FACTOR  9
#define FLUID_CONVEYOR_INFO_COUNT  9

#define FLUID_CONVEYOR_PREVIOUS_LAYOUT_NUMBER_OF_SLICES  1
#define FLUID_CONVEYOR_PREVIOUS_LAYOUT_LENGTH  2
#define FLUID_CONVEYOR_PREVIOUS_LAYOUT_INPUT_WIDTH  3
#define FLUID_CONVEYOR_PREVIOUS_LAYOUT_OUTPUT_WIDTH  4
#define FLUID_CONVEYOR_PREVIOUS_LAYOUT_CENTERLINE_OFFSET  5

#define FLUID_CONVEYOR_INPUTS_OBJECT  1
#define FLUID_CONVEYOR_INPUTS_START_RANGE  2
#define FLUID_CONVEYOR_INPUTS_END_RANGE  3
#define FLUID_CONVEYOR_INPUTS_START_SLICE_INDEX  4
#define FLUID_CONVEYOR_INPUTS_END_SLICE_INDEX  5
#define FLUID_CONVEYOR_INPUTS_INPORT_NUMBER  6
#define FLUID_CONVEYOR_INPUTS_COUNT  6

#define FLUID_CONVEYOR_OUTPUTS_OBJECT  1
#define FLUID_CONVEYOR_OUTPUTS_POSITION  2
#define FLUID_CONVEYOR_OUTPUTS_FORWARD_PERCENTAGE  3
#define FLUID_CONVEYOR_OUTPUTS_REVERSE_PERCENTAGE  4
#define FLUID_CONVEYOR_OUTPUTS_STOPPED_RATE  5
#define FLUID_CONVEYOR_OUTPUTS_OUTPORT_NUMBER  6
#define FLUID_CONVEYOR_OUTPUTS_AUX_ROW  7
#define FLUID_CONVEYOR_OUTPUTS_COUNT 7

#define FLUID_CONVEYOR_OUTPUTS_AUX_OUTPORT_NUMBER  1
#define FLUID_CONVEYOR_OUTPUTS_AUX_POSITION  2
#define FLUID_CONVEYOR_OUTPUTS_AUX_FORWARD_PERCENTAGE  3
#define FLUID_CONVEYOR_OUTPUTS_AUX_REVERSE_PERCENTAGE  4
#define FLUID_CONVEYOR_OUTPUTS_AUX_STOPPED_RATE  5
#define FLUID_CONVEYOR_OUTPUTS_AUX_STOPPED_PER_TICK  6
#define FLUID_CONVEYOR_OUTPUTS_AUX_MATERIAL_LEAVING  7
#define FLUID_CONVEYOR_OUTPUTS_AUX_OUTPUT_PERCENTAGE  8
#define FLUID_CONVEYOR_OUTPUTS_AUX_OUTSLICE_INDEX  9
#define FLUID_CONVEYOR_OUTPUTS_AUX_COUNT  9

#define FLUID_CONVEYOR_SENSORS_START_RANGE  1
#define FLUID_CONVEYOR_SENSORS_END_RANGE  2
#define FLUID_CONVEYOR_SENSORS_TYPE  3
#define FLUID_CONVEYOR_SENSORS_LOW_VALUE  4
#define FLUID_CONVEYOR_SENSORS_MID_VALUE  5
#define FLUID_CONVEYOR_SENSORS_HIGH_VALUE  6
#define FLUID_CONVEYOR_SENSORS_PREVIOUS_VALUE  7
#define FLUID_CONVEYOR_SENSORS_STATE  8
#define FLUID_CONVEYOR_SENSORS_START_SLICE_INDEX  9
#define FLUID_CONVEYOR_SENSORS_END_SLICE_INDEX  10
#define FLUID_CONVEYOR_SENSORS_COUNT 10

#define FLUID_CONVEYOR_SENSOR_TYPE_VOLUME  1
#define FLUID_CONVEYOR_SENSOR_TYPE_PEAK_HEIGHT  2


// Constants group: PFM
#define PFM_EXPERIMENT_DATA 1
#define PFM_EVALUATOR 2
#define PFM_STATISTIC 2
#define PFM_UNIT_NAME 3

#define BYPASS_NONE 0
#define BYPASS_ALL 0xffffffff
#define BYPASS_PULL_REQUIREMENT  0x1
#define BYPASS_SEND_TO 0x2
#define BYPASS_OUTPUT_CLOSED 0x4
#define BYPASS_OUTPUT_PORT_CLOSED 0x8
#define BYPASS_INPUT_CLOSED 0x10
#define BYPASS_UPSTREAM_STOPPED 0x20
#define BYPASS_STOPPED 0x40

#define PULL_REEVALUATE_ON_READY -2
#define PORT_STATE_REEVALUATE 2

#define OFFSET_NONE 0
#define OFFSET_BY_TE_LOGIC 1
#define OFFSET_NONE_AND_BLOCK 2
#define OFFSET_BY_NAV_LOGIC 3

// reasons for adding a module dependency to a model
#define DEPENDANT_BECAUSE_OBJECT_CREATED 1 // added when a user drops an object into the model
#define DEPENDANT_BECAUSE_NEW_MODEL 2 // added because the user checked a box or something on a new model
#define DEPENDANT_BECAUSE_SUB_DEPENDENCY 3 // added because another module dependency was added for a module that is dependent on this module
#define DEPENDANT_BECAUSE_USER_INPUT 4 // added because the user explicitly pushed some button or chose a menu option (maybe through the model settings window)
#define DEPENDANT_BECAUSE_OTHER 0 // added for some other reason

#define DOCK_PANE_MAIN 1
#define DOCK_PANE_LEFT 2
#define DOCK_PANE_RIGHT 4
#define DOCK_PANE_TOP 8
#define DOCK_PANE_BOTTOM 16
#define DOCK_TOOL_LEFT 32
#define DOCK_TOOL_RIGHT 64
#define DOCK_TOOL_TOP 128
#define DOCK_TOOL_BOTTOM 256

#define DOCK_TYPE_DOCUMENT 101
#define DOCK_TYPE_TOOL 102

#define VIEW_TYPE_TREE 0
#define VIEW_TYPE_PLANAR 1
#define VIEW_TYPE_3D 2
#define VIEW_TYPE_GUI 4
#define VIEW_TYPE_TABLE 5
#define VIEW_TYPE_GRAPH 6
#define VIEW_TYPE_SCRIPT 8
#define VIEW_TYPE_BUTTON 100
#define VIEW_TYPE_EDIT 101
#define VIEW_TYPE_PANEL 102
#define VIEW_TYPE_STATIC 103
#define VIEW_TYPE_CHECKBOX 105
#define VIEW_TYPE_RADIOBUTTON 106
#define VIEW_TYPE_COMBOBOX 109
#define VIEW_TYPE_LISTBOX 114
#define VIEW_TYPE_TAB_CONTROL 115
#define VIEW_TYPE_TOOLBAR 116
#define VIEW_TYPE_TAB_CONTROL_BOTTOM 118
#define VIEW_TYPE_TRACKER 122
#define VIEW_TYPE_HTML 124

#define CONSOLE_OUTPUT 1
#define CONSOLE_SYSTEM 2
#define CONSOLE_COMPILER 3
#define CONSOLE_TRACE 4

// nodefunction listen event macros
#define NFL_PRE_LISTEN 0x1
#define NFL_LISTEN 0x2
#define NFL_PERSIST 0x4
#define NFL_PASS_THROUGH_PARAMS 0x8
#define NFL_LISTEN_ONCE 0x10

#define NFL_STOP_LISTENING -1

#define EVENT_PRE_LISTEN 0x1
#define EVENT_LISTEN 0x2
#define EVENT_PERSIST 0x4
#define EVENT_PASS_THROUGH_PARAMS 0x8
#define EVENT_LISTEN_ONCE 0x10

#define EVENT_STOP_LISTENING -1

#define RESUME_AT_SAME_POS 0
#define RESUME_AT_NEXT_KEYFRAME 1
#define RESUME_AT_TIME 2

#define FLEXSIM_MESSAGE_USER_CALLBACK 2001
#define FLEXSIM_MESSAGE_USER_NODEFUNCTION 2002

#define OVERRIDE_DRAW_SIZER_X      0x10
#define OVERRIDE_DRAW_SIZER_Y      0x20
#define OVERRIDE_DRAW_SIZER_Z      0x80
#define OVERRIDE_DRAW_SIZER_X_NEG  0x100
#define OVERRIDE_DRAW_SIZER_Y_NEG  0x200
#define OVERRIDE_DRAW_SIZER_Z_NEG  0x400
#define OVERRIDE_DRAW_SIZER_ALL    0x800
#define OVERRIDE_DRAW_YELLOW_BOX   0x1000
#define OVERRIDE_DRAW_GREEN_BOX    0x1000
#define OVERRIDE_DRAW_REDBOX       0x2000
#define OVERRIDE_DRAW_HOVERBOX     0x4000
#define OVERRIDE_DRAW_ALL          0x7ff0

#define STAT_MEAN 1
#define STAT_AVERAGE 1
#define STAT_CURRENT 2
#define STAT_CONF_INTERVAL_HALF_WIDTH 2
#define STAT_MIN 3
#define STAT_MAX 4
#define STAT_TIME_AT_VALUE 5
#define STAT_VARIANCE 5
#define STAT_STD_DEV 6
#define STAT_SUM 7
#define STAT_COUNT 8
// this should be the same as FLT_MAX
#define STAT_UNDEFINED 340282346600000000000000000000000000000.0

#define DRAW_FLAG_BILLBOARD_MASK 0x3
#define DRAW_FLAG_ONE_SIDED 0x4
#define DRAW_FLAG_TWO_SIDED 0x8
#define DRAW_FLAG_NO_DEPTH_TEST 0x10
#define DRAW_FLAG_REFLECTIVE 0x20
#define DRAW_FLAG_LUMINOUS 0x40
#define DRAW_FLAG_SCALE_CHILDREN 0x80
#define DRAW_FLAG_IGNORE_PICKING 0x100
#define DRAW_FLAG_NO_ON_DRAW 0x200
#define DRAW_FLAG_NO_ON_PRE_DRAW 0x400
#define DRAW_FLAG_SKIP_ALL_DRAW 0x800

// drawimage
#define NO_SCALE 0
#define SCALE_DOWN 1
#define SCALE_UP_DOWN 2
#define SCALE_INDEPENDENT 3

#define DB_SQL_FLAG_FORWARD_ONLY_CURSOR 0x1

#define IGNORE_CASE 1

#define EDIT_MODE_GET_MODE_NUM -1
#define EDIT_MODE_GET_MODE_DELEGATE -2

#define PARAM_TYPE_NUMBER 1
#define PARAM_TYPE_NODE 2
#define PARAM_TYPE_STRING 3

#define FGL_INFO_SHADERTYPE 1
#define FGL_INFO_SHADOWTYPE 2

// shader pass macros
#define SHADERTYPE_DEFAULT 0
#define SHADERTYPE_RENDER_SHADOWS 1
#define SHADERTYPE_BLUR 2
#define SHADERTYPE_SUM_AREA_TABLE 3

#define SHADOWTYPE_NONE 0
#define SHADOWTYPE_HARD 1
#define SHADOWTYPE_VSM 2
#define SHADOWTYPE_PCSS 3
#define SHADOWTYPE_PCSS_SAVSM 4

#define LIST_PULL_ALL_OR_NOTHING 0x1
#define LIST_PARSE_QUERY 0x2
#define LIST_PULL_ENTRY_NODES 0x4
#define LIST_DO_NOT_REMOVE 0x8
#define LIST_DO_NOT_BACK_ORDER 0x10
#define LIST_PULL_BACK_ORDERS 0x20
#define LIST_DO_NOT_FULFILL 0x40

// Config
#define VREC_DEBUG_NOOUTPUT 0

// Paths
#define VREC_PATH_FFMPEG concat(pdir(), "ffmpeg\\ffmpeg.exe")
#define VREC_PATH_TOOLS concat(pdir(), "ffmpeg\\")
#define VREC_PATH_TOOL_RUNFFMPEG concat(VREC_PATH_TOOLS, "run_ffmpeg.bat")
#define VREC_PATH_TOOL_CLEANUP concat(VREC_PATH_TOOLS, "cleanup.bat")

// Messages
#define VREC_MSG_JOBS_RUN 1
#define VREC_MSG_JOB_START 2
#define VREC_MSG_JOB_STOP 3
#define VREC_MSG_SEQ_START 4
#define VREC_MSG_SEQ_STOP 5
#define VREC_MSG_FRAME 6

// Size modes
#define VREC_SIZEMODE_CUSTOM 0
#define VREC_SIZEMODE_INHERIT 1
#define VREC_SIZEMODE_VIEW 2

// Record modes
#define VREC_RECMODE_ALL 1
#define VREC_RECMODE_ONE 2

// Metrics
#define VREC_METRIC_OUT_TIME 1
#define VREC_METRIC_OUT_FRAMES 2
#define VREC_METRIC_SEQ_TIME 3
#define VREC_METRIC_SEQ_FRAMES 4
#define VREC_METRIC_SEQ_INTERVAL 5
#define VREC_METRIC_LAY_WIDTH 6
#define VREC_METRIC_LAY_HEIGHT 7
#define VREC_METRIC_LAY_VFLIP 8

// Layer types
#define VREC_LAYER_COLOR 1
#define VREC_LAYER_VIEW 2

// Animation
//// Coordinates
#define VREC_COORD_X 1
#define VREC_COORD_Y 2
//// Margin types
#define VREC_MARGIN_PIXELS 1
#define VREC_MARGIN_PERCENT 2
//// Alignment types
#define VREC_ALIGN_MIN 1
#define VREC_ALIGN_MID 2
#define VREC_ALIGN_MAX 3
//// Interpolation types
#define VREC_INTERPOLATE_LINEAR 1
#define VREC_INTERPOLATE_COSINE 2

// Event Listener
#define EVENT_PARAM_1 "%$1$%"
#define EVENT_PARAM_2 "%$2$%"
#define EVENT_PARAM_3 "%$3$%"
#define EVENT_PARAM_4 "%$4$%"
#define EVENT_PARAM_5 "%$5$%"
#define EVENT_PARAM_6 "%$6$%"
#define EVENT_PARAM_7 "%$7$%"
#define EVENT_PARAM_8 "%$8$%"
#define EVENT_PARAM_9 "%$9$%"
#define EVENT_PARAM_10 "%$A$%"

// Event Listener Aliases
#define LIST_ON_FULFILL_VALUE "%$1$%"
#define LIST_ON_FULFILL_NUM_FULFILLED "%$2$%"
#define LIST_ON_FULFILL_TOTAL_FULFILLED "%$3$%"
#define LIST_ON_FULFILL_NUM_REQUESTED "%$4$%"
#define LIST_ON_FULFILL_NUM_REQUIRED "%$5$%"
#define LIST_ON_PULL_VALUE "%$1$%"

#define EVENT_INFO_TABLE_COL_NAME 1
#define EVENT_INFO_TABLE_COL_REF 2
#define EVENT_INFO_TABLE_COL_FLAGS 3
#define EVENT_INFO_TABLE_COL_PARAMS 4
#define EVENT_INFO_TABLE_COL_REQUIREMENTS 5

#define EVENT_INFO_PARAMS 0x1
#define EVENT_INFO_DEFAULT_CODE 0x2
#define EVENT_INFO_CATEGORY 0x3
#define EVENT_INFO_LOCALIZED_TITLE 0x4
#define EVENT_INFO_REQUIREMENTS 0x5

#define BIND_EVENT_ENUMERATE 1
#define BIND_EVENT_ASSERT 2
#define BIND_EVENT_ON_LOAD 3
#define BIND_EVENT_FILL_BINDING_ENTRY 4

#define EVENT_TYPE_MASK 0x7
#define EVENT_TYPE_DEFAULT 0x1
#define EVENT_TYPE_VALUE_GETTER 0x2
#define EVENT_TYPE_VALUE_NOTIFIER 0x4

// A flag to not allow the event binding to a node based on the byte offset from the sdt memory pointer.&lt;/summary&gt;
#define EVENT_DO_NOT_BIND_BYTE_OFFSET 0x100
#define EVENT_ATTRIBUTE 0x200
#define EVENT_NO_DEFAULT_CODE 0x400
#define EVENT_RELAYED 0x800

// the mask around all requirments flags
#define EVENT_REQUIREMENTS 0x30000
// shift the requirements masked value 16 bits to get the number of requirements
#define EVENT_REQUIREMENTS_BIT_SHIFT 16
#define EVENT_1_REQUIREMENT 0x10000
#define EVENT_2_REQUIREMENTS 0x20000
#define EVENT_3_REQUIREMENTS 0x30000

#define STAT_INFO_REQUIREMENTS 0x1
#define STAT_INFO_LOCALIZED_TITLE 0x2

#define BIND_STAT_ENUMERATE 1
#define BIND_STAT_ASSERT 2
#define BIND_STAT_ON_LOAD 3
#define BIND_STAT_FILL_BINDING_ENTRY 4
#define BIND_STAT_ON_RUNWARM 5

#define STAT_TYPE_MASK 0x7
#define STAT_TYPE_LEVEL 0x1 
#define STAT_TYPE_CUMULATIVE 0x2
#define STAT_TYPE_TIME_SERIES 0x3
#define STAT_TYPE_CATEGORICAL 0x4

#define STAT_RELAYED 0x100
#define STAT_TIME_WEIGHTED 0x200

#define STAT_REQUIREMENTS 0x30000
#define STAT_REQUIREMENTS_BIT_SHIFT 16
#define STAT_1_REQUIREMENT 0x10000
#define STAT_2_REQUIREMENTS 0x20000
#define STAT_3_REQUIREMENTS 0x30000

#define STAT_DERIVE_CUR 0x1
#define STAT_DERIVE_MIN 0x2
#define STAT_DERIVE_MAX 0x4
#define STAT_DERIVE_AVG 0x8

#define STAT_ENUM_REQS_INVALID 0
#define STAT_ENUM_REQS_STATIC 1
#define STAT_ENUM_REQS_DYNAMIC 2

#define STAT_USE_HISTORY 0x10
#define STAT_USE_PROFILE 0x20
#define STAT_IGNORE_WARMUP 0x40

#define XL_DATETIME 1
#define FS_DATETIME 2
#define MODEL_TIME 3
#define DATE_STR 4
#define TIME_STR 5
#define DATETIME_STR 6


// Include Header
#include <float.h>

// The following #defines can be changed to customize the connection controls.
// The following keys are already in use and should NOT be used here : A, Q, S, W, O, T, N, P, X
//#include ".\include\eventstruct.h"
typedef treenode treenode;

#define INOUT_KEY1 'J'
#define INOUT_KEY2 'U'
#define CENTER_KEY1 'K'
#define CENTER_KEY2 'I'

#define DEFAULTZERO = 0
#define DEFAULTNULL = 0x0
#define DEFAULTONE = 1
#define DEFAULTPARAM(val) = val

class FlexSimEventHandler;

class FlexSimObject;

class Dispatcher;

class TaskExecuter;

class FixedResource;

class Navigator;

class NetworkNode;

class NetworkNavigator;

class FlowItem;

class SplineEndPoint;


///////////////////////////////////////////////////////
// Travel Requests
///////////////////////////////////////////////////////
class TravelRequest : public SimpleDataType
{
  public:
	virtual const char* getClassFactory() {return "TravelRequest";}
	virtual void bind();
	treenode traveler;
	treenode staticTravelMemberNode; // the rank of the coupling node in the Navigator's travelers variable.
	double beginTime; // the begin time of the travel request.
	double totalDist;// the total distance to travel.
	double endSpeed;
};

class NavigatorRequest : public TravelRequest
{
public:
	virtual const char* getClassFactory() {return "NavigatorRequest";}
	virtual void bind();
	double rotationTime; // the time it will take to rotate around
	int initRY;
	int initRZ;
	int rotateY;
	int rotateZ;
};

class NetworkRequest : public TravelRequest
{
public:
	virtual const char* getClassFactory() {return "NetworkRequest";}
	virtual void bind();
	treenode destination; // the requested destination
	int destCol; // the column of the destination node.
	int originCol; // the column of the original origin node.
	int initRZ; // start z rotation
	unsigned short outPort; // the current output port of the network node
	#define NETREQSTATE_TRAVEL 1
	#define NETREQSTATE_WAIT 2
	unsigned char state;
	double nodeBeginTime; // the time that the traveller entered into the current node.
	treenode curNetNode; // the current network node that is managing the object
	unsigned short curTControlRank; // the rank of the traffic control that I'm attempting to enter
	int flipped;
	float lastUpdatedDistAlongEdge;
	float distTraveled;
	float edgeAccDist;
	float edgeDecDist;
	float edgeEndSpeed;
	double nextNodeArrivalTime;
	float edgeMaxV;
	treenode kinematics;
};

class NetworkNodeMember : public CouplingDataType
{
public:
	virtual const char* getClassFactory() {return "NetworkNodeMember";}
	virtual void bind();
	struct ConnectionInfo
	{
		int tableRow;
		float distance;
		int outPort;
	};
	std::vector<ConnectionInfo> connections;
	std::vector<float> distanceTable;
	std::vector<unsigned char> nextOutPortTable;
	NetworkNode* getNetNode();
};

class TrafficControlRequest
{
	public:
	treenode travelreqnode;
	NetworkNode* tonetnode;
	unsigned short nextport;
	unsigned short fromrank;
	unsigned short torank;

	static char* displaydata(treenode thenode, int verbose);
};

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


class TaskSequence : public SimpleDataType{
	public:
	TaskSequence() : labelsNode(0) {}
	~TaskSequence() {if (labelsNode) delete labelsNode;}
	float priority; 
	unsigned char preempt; 
	unsigned char coordinated; // if the task is coordinated
	unsigned int curtask; // this number is the rank of the task that is currently being worked on.
	treenode owner; // this is only used in coordinated tasks.  It is there so that the proxy task executers have a reference back to the dispatcher that has the task sequence
	unsigned int milestone; // this is the rank of the current milestone
	unsigned int nrofallocations; // this is the current number of objects allocated or whose allocation has been requested
	virtual const char* getClassFactory() {return "TaskSequence";}
	virtual void bind();
	virtual char* toString(int verbose);
	virtual treenode getObjectTree();
	virtual TreeNode* getLabelNode(const char* labelName, bool assert);
	virtual TreeNode* getLabelNode(int labelRank, bool assert);
	treenode labelsNode;
	void reset();
};

class Task : public SimpleDataType{
	public:
	unsigned short type;
	// The state variable will usually go from UNFINISHED, to ACTIVE, to FINISHED.  However, if it is coordinated, it will go to COORDINATED instead of ACTIVE,
	// so that the proxy executer knows that it's a coordinated, and should be finished by the Dispatcher that is coordinating the tasks.
	unsigned short state;
	// The following are the most used variables of the task.
	treenode involved1;
	treenode involved2;
	double var1;
	double var2;
	double var3;
	double var4;

	// syncnextkey is only used in coordinated tasks.  The dispatcher, when coordinating tasks, may immediately run through several proxy tasks for the same 
	// executer.  However, it will not tell a proxy executer to begin a task until all of the previous tasks for that executer have been finished.  If it gets to a 
	// proxy task, and the executer is busy on a previous proxy task, it will set the syncenextkey variable of the previous proxy task to the rank of this task.  
	// Then it will trigger the next task once the executer is finished.
	unsigned int syncnextkey;
	// The executerkey is specified by the user.  This is a reference to the rank of an allocate task, and specifies the executer that will execute a proxy task.
	unsigned int executerkey;
	virtual const char* getClassFactory() {return "Task";}
	virtual void bind();
	virtual char* toString(int verbose);
};

class SendMessageEvent : public FlexSimEvent {
	public:
	double par1;
	double par2;
	double par3;
	SendMessageEvent() : FlexSimEvent(), par1(0), par2(0), par3(0)
		{}
	SendMessageEvent(treenode toobject, double time, treenode fromobject, double par1, double par2, double par3) 
			: FlexSimEvent(toobject, time, fromobject, EVENT_SENDMESSAGE, NULL),
			par1(par1), par2(par2), par3(par3)
		{}
	virtual void execute();
	virtual const char* getClassFactory() {return "SendMessageEvent";}
	virtual void bind();
};

class SimulationStartEvent : public FlexSimEvent {
public:
	SimulationStartEvent() : FlexSimEvent() {}
	SimulationStartEvent(FlexSimEventHandler* firstObject);
	virtual void execute();
	virtual const char* getClassFactory() {return "SimulationStartEvent";}
	virtual void bind();
	FS_CONTENT_DLL_FUNC static void addObject(FlexSimEventHandler* object);
private:
	std::vector<ObjRef<FlexSimEventHandler>> objects;
	static ObjRef<SimulationStartEvent> simulationStartEvent;
};

class FRItemInfo : public SimpleDataType
{
friend class FixedResource;
friend class TaskExecuter;
public:
	FRItemInfo() : state(0), sendto(0), involved(0), transportOutCompleteObject(0), transportInCompleteObject(0) {}
	virtual const char* getClassFactory() {return "FRItemInfo";}
	virtual void bind();
	void reset();
private:
	FixedResource* curFR;
	int state;
	int sendto;
	double vars[3];
	treenode involved;
public:
	treenode transportOutCompleteObject;
	treenode transportInCompleteObject;
};

class PullIterator
{
public:
	virtual TreeNode* getNext() = 0;
	static PullIterator* s_customPullIterator;
};

class FifoPullIterator : public PullIterator
{
protected:
	int numReleased;
	int numChecked;
	int curRank;
	int totalContent;
	int outPort;
	TreeNode* frNodeBranch;
public:
	static FifoPullIterator fifoPullIterator;
	virtual TreeNode* getNext() override;
	void init(FixedResource*, int outPort);
};

class LifoPullIterator : public FifoPullIterator
{
public:
	static LifoPullIterator lifoPullIterator;
	virtual TreeNode* getNext() override;
	void init(FixedResource*, int outPort);
};

struct conviteminfostruct : public SimpleDataType {
	virtual const char* getClassFactory() {return "conviteminfostruct";}
	virtual void bind();
	double entrytime;
	double distbehindkinematic; 
	double totalspacebefore; 
	double spacing; 
	double prodlength; 
	int frontedgepe; 
	int backedgepe;
	// used for basic conveyors
	double position;
	int frontedgedp;
	int backedgedp; 
	int backspacedp; 
};

struct bciteminfostruct{
};

extern char * tasktypenames[];

extern treenode* nexttreeunderstack;
extern int nexttreeunderstacktop;
extern int nexttreeunderstacksize;

struct delayedmessagedata
{
	int nrofparams;
	double params[7];
};

#define INTO_GLOBAL_SCOPE return 0;}catch(...){return 0;}}
#define OUT_OF_GLOBAL_SCOPE(NAME) double dummy##NAME##Function(){try{

extern int globalnouserreset;
extern treenode _defaultNetworkNavigator;

extern double messageeventfilter_p1;
extern double messageeventfilter_p2;
extern double messageeventfilter_p3;

#define NR_CONTENT_EVENT_TYPES 95
extern int g_logeventtypes[];
extern int * g_logeventtypesenabled[]; 
extern int * g_eventloggingenabled;

extern int g_tasksequencecounter;
// these are array indexes used to reference eventtype indexes in the LOGEVENT() macro
#define LE_interarrivaltime 0
#define LE_sendtoport 1
#define LE_transportdispatcher 2
#define LE_resettrigger 3
#define LE_messagetrigger 4
#define LE_creationtrigger 5
#define LE_entrytrigger 6
#define LE_exittrigger 7
#define LE_receivefromport 8
#define LE_pullrequirement 9
#define LE_endcollectingtrigger 10
#define LE_setuptime 11
#define LE_cycletime 12
#define LE_processdispatcher 13
#define LE_setupfinishtrigger 14
#define LE_processfinishtrigger 15
#define LE_splitquantity 16
#define LE_photoeyecovertrigger 17
#define LE_photoeyeuncovertrigger 18
#define LE_conveyendtrigger 19
#define LE_sendrequirement 20
#define LE_itemspeed 21
#define LE_placeinbay 22
#define LE_placeinlevel 23
#define LE_minimumstaytime 24
#define LE_enddwelltimetrigger 25
#define LE_inflowrate 26
#define LE_outflowrate 27
#define LE_risethroughhighmarktrigger 28
#define LE_fallthroughhighmarktrigger 29
#define LE_risethroughmiddlemarktrigger 30
#define LE_fallthroughmiddlemarktrigger 31
#define LE_risethroughlowmarktrigger 32
#define LE_fallthroughlowmarktrigger 33
#define LE_passto 34
#define LE_queuestrategy 35
#define LE_onresourceavailable 36
#define LE_loadtime 37
#define LE_unloadtime 38
#define LE_breakto 39
#define LE_loadtrigger 40
#define LE_unloadtrigger 41
#define LE_collisiontrigger 42
#define LE_entrytrigger_nn 43
#define LE_arrivaltrigger 44
#define LE_requesttrigger 45
#define LE_onbeginoffset 46
#define LE_onfinishoffset 47
#define LE_pickoffset 48
#define LE_placeoffset 49
#define LE_stop 50
#define LE_resume 51
#define LE_advancedfunctions 52
#define LE_transportinnotify 53
#define LE_transportincomplete 54
#define LE_transportoutnotify 55
#define LE_transportoutcomplete 56
#define LE_oncover_dp 57
#define LE_onclear_dp 58
#define LE_lowmarktrigger 59
#define LE_midmarktrigger 60
#define LE_highmarktrigger 61
#define LE_adjustinputrates 62
#define LE_adjustoutputrates 63
#define LE_emptytrigger 64
#define LE_fulltrigger 65
#define LE_beforedelaytrigger 66
#define LE_afterdelaytrigger 67
#define LE_begintask_travel 68
#define LE_begintask_load 69
#define LE_begintask_frload 70
#define LE_begintask_unload 71
#define LE_begintask_frunload 72
#define LE_begintask_utilize 73
#define LE_begintask_delay 74
#define LE_begintask_break 75
#define LE_begintask_callsubtasks 76
#define LE_begintask_stoprequestbegin 77
#define LE_begintask_stoprequestfinish 78
#define LE_begintask_sendmessage 79
#define LE_begintask_traveltoloc 80
#define LE_begintask_travelrelative 81
#define LE_begintask_pickoffset 82
#define LE_begintask_placeoffset 83
#define LE_begintask_moveobject 84
#define LE_begintask_destroyobject 85
#define LE_begintask_setnodenum 86
#define LE_begintask_milestone 87
#define LE_begintask_nodefunction 88
#define LE_tasksequence_receivets 89
#define LE_tasksequence_begints 90
#define LE_tasksequence_finishts 91
#define LE_begintask_startanimation 92
#define LE_begintask_stopanimation 93
#define LE_begintask_freeoperators 94



template <class Number>
class Vec4Generic 
{
public:
	union {
		struct {
			Number x;
			Number y;
			Number z;
			Number w;
		};
		struct {
			Number r;
			Number g;
			Number b;
			Number a;
		};
		Number loc[4];
	};
	template <class OtherVec>
	Vec4Generic(const OtherVec& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
	template <class OtherNumber>
	Vec4Generic(const OtherNumber* other) : x(other[0]), y(other[1]), z(other[2]), w(other[3]) {}
	template <class OtherNumber>
	Vec4Generic(OtherNumber* other) : x(other[0]), y(other[1]), z(other[2]), w(other[3]) {}
	Vec4Generic(Number x, Number y, Number z, Number w) : x(x), y(y), z(z), w(w) {}
	Vec4Generic() {}
	#if _MSC_VER >= 1800
	template <class OtherNumber>
	Vec4Generic(std::initializer_list<OtherNumber> list) 
	{
		int index = 0;
		for (auto x = list.begin(); x != list.end() && index < 4; x++, index++)
			this->operator [] (index) = (Number)*x;
	}
	template <class OtherNumber>
	Vec4Generic& operator = (std::initializer_list<OtherNumber> list) { ::new (this) (list); return *this; }
	#endif

	operator Number* () {return loc;}
	const Vec4Generic operator + (const Vec4Generic& a) const {return Vec4Generic(x + a.x, y + a.y, z + a.z, w + a.w);}
	const Vec4Generic operator - (const Vec4Generic& a) const {return Vec4Generic(x - a.x, y - a.y, z - a.z, w - a.w);}
	const Vec4Generic operator - () const {return Vec4Generic(-x, -y, -z, -w);}
	const Vec4Generic operator / (const Vec4Generic& other) const {return Vec4Generic(x / other.x, y / other.y, z / other.z, w / other.w);}
	const Vec4Generic operator / (Number mult) const {return Vec4Generic(x / mult, y / mult, z / mult, w / mult);}
	const Vec4Generic operator * (const Vec4Generic& other) const {return Vec4Generic(x * other.x, y * other.y, z * other.z, w * other.w);}
	const Vec4Generic operator * (Number mult) const {return Vec4Generic(x * mult, y * mult, z * mult, w * mult);}
	Vec4Generic& operator += (const Vec4Generic& other) {x += other.x; y += other.y; z += other.z; w += other.w; return *this;}
	Vec4Generic& operator -= (const Vec4Generic& other) {x -= other.x; y -= other.y; z -= other.z; w += other.w; return *this;}
	const bool operator == (const Vec4Generic& other) const {return x == other.x && y == other.y && z == other.z && w == other.w;}
	const bool operator != (const Vec4Generic& other) const {return x != other.x || y != other.y || z != other.z || w != other.w;}

	template <class OtherNumber>
	Vec4Generic& operator = (const Vec4Generic<OtherNumber>& other) {x = other.x; y = other.y; z = other.z; w = other.w; return *this;}
	Number& operator [] (int index) {return loc[index];}
	Number const& operator [] (int index) const {return loc[index];}

	Number getLength() const {return sqrt(x * x + y * y + z * z + w * w);}
	Number getDistanceTo(const Vec4Generic& other) const {return Vec3(x - other.x, y - other.y, z - other.z, w - other.w).getLength();}
	Number getDotProduct(const Vec4Generic& other) const {return x * other.x + y * other.y + z * other.z + w * other.w;}
	Number getXYAngle() const {return radianstodegrees(atan2(y, x));}
	Number getYZAngle() const {return radianstodegrees(atan2(z, y));}
	Number getZXAngle() const {return radianstodegrees(atan2(x, z));}
	template <class OtherNumber>
	void copyTo(OtherNumber* dest) const {dest[0] = (OtherNumber)x; dest[1] = (OtherNumber)y; dest[2] = (OtherNumber)z; dest[3] = (OtherNumber)w;}
	void normalize() 
	{
		Number length = getLength();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}
	#define VEC4_ROTATE_A_B(degs, a, b) \
		Number rads = degreestoradians(degrees); \
		Number cosRads = cos(rads); \
		Number sinRads = sin(rads); \
		Vec4Generic temp = *this; \
		a = cosRads * temp.a - sinRads * temp.b; \
		b = sinRads * temp.a + cosRads * temp.b;
		
	void rotateXY(Number degrees) 
	{
		VEC4_ROTATE_A_B(degrees, x, y)
	}
	void rotateYZ(Number degrees) 
	{
		VEC4_ROTATE_A_B(degrees, y, z)
	}
	void rotateZX(Number degrees) 
	{
		VEC4_ROTATE_A_B(degrees, z, x)
	}
	static Vec4Generic fromRotAndDist(Number degs, Number length, Number zComp = 0) 
	{
		Number rads = degreestoradians(degs); 
		return Vec4Generic(length * cos(rads), length * sin(rads), zComp);
	}
};


template <class Number>
class Vec3Generic 
{
public:
	union {
		struct {
			Number x;
			Number y;
			Number z;
		};
		struct {
			Number r;
			Number g;
			Number b;
		};
		Number loc[3];
	};
	template <class OtherVec>
	Vec3Generic(const OtherVec& other) : x(other.x), y(other.y), z(other.z) {}
	template <class OtherNumber>
	Vec3Generic(const OtherNumber* other) : x(other[0]), y(other[1]), z(other[2]) {}
	template <class OtherNumber>
	Vec3Generic(OtherNumber* other) : x(other[0]), y(other[1]), z(other[2]) {}
	Vec3Generic(Number x, Number y, Number z) : x(x), y(y), z(z) {}
	Vec3Generic() {}
	#if _MSC_VER >= 1800
	template <class OtherNumber>
	Vec3Generic(std::initializer_list<OtherNumber> list) 
	{
		int index = 0;
		for (auto x = list.begin(); x != list.end() && index < 3; x++, index++)
			this->operator [] (index) = (Number)*x;
	}
	template <class OtherNumber>
	Vec3Generic& operator = (std::initializer_list<OtherNumber> list) { ::new (this) (list); return *this; }
	#endif

	operator Number* () {return loc;}
	Vec3Generic operator + (const Vec3Generic& a) const {return Vec3Generic(x + a.x, y + a.y, z + a.z);}
	Vec3Generic operator - (const Vec3Generic& a) const {return Vec3Generic(x - a.x, y - a.y, z - a.z);}
	Vec3Generic operator - () const {return Vec3Generic(-x, -y, -z);}
	Vec3Generic operator / (const Vec3Generic& other) const {return Vec3Generic(x / other.x, y / other.y, z / other.z);}
	Vec3Generic operator / (Number mult) const {return Vec3Generic(x / mult, y / mult, z / mult);}
	Vec3Generic operator * (const Vec3Generic& other) const {return Vec3Generic(x * other.x, y * other.y, z * other.z);}
	Vec3Generic operator * (Number mult) const {return Vec3Generic(x * mult, y * mult, z * mult);}
	Vec3Generic& operator += (const Vec3Generic& other) {x += other.x; y += other.y; z += other.z; return *this;}
	Vec3Generic& operator -= (const Vec3Generic& other) {x -= other.x; y -= other.y; z -= other.z; return *this;}
	bool operator == (const Vec3Generic& other) const {return x == other.x && y == other.y && z == other.z;}
	bool operator != (const Vec3Generic& other) const {return x != other.x || y != other.y || z != other.z;}

	template <class OtherNumber>
	Vec3Generic& operator = (const Vec3Generic<OtherNumber>& other) {x = other.x; y = other.y; z = other.z; return *this;}
	Number& operator [] (int index) {return loc[index];}
	Number const& operator [] (int index) const {return loc[index];}

	Number getLength() const {return sqrt(x * x + y * y + z * z);}
	Number getDistanceTo(const Vec3Generic& other) const {return Vec3Generic(x - other.x, y - other.y, z - other.z).getLength();}
	Number getDotProduct(const Vec3Generic& other) const {return x * other.x + y * other.y + z * other.z;}
	Number getXYAngle() const {return radianstodegrees(atan2(y, x));}
	Number getYZAngle() const {return radianstodegrees(atan2(z, y));}
	Number getZXAngle() const {return radianstodegrees(atan2(x, z));}
	template <class OtherNumber>
	void copyTo(OtherNumber* dest) const {dest[0] = (OtherNumber)x; dest[1] = (OtherNumber)y; dest[2] = (OtherNumber)z;}
	void normalize() 
	{
		Number length = getLength();
		x /= length;
		y /= length;
		z /= length;
	}
	#define VEC3_ROTATE_A_B(degs, a, b) \
		Number rads = degreestoradians(degrees); \
		Number cosRads = cos(rads); \
		Number sinRads = sin(rads); \
		Vec3Generic temp = *this; \
		a = cosRads * temp.a - sinRads * temp.b; \
		b = sinRads * temp.a + cosRads * temp.b;
		
	void rotateXY(Number degrees) 
	{
		VEC3_ROTATE_A_B(degrees, x, y)
	}
	void rotateYZ(Number degrees) 
	{
		VEC3_ROTATE_A_B(degrees, y, z)
	}
	void rotateZX(Number degrees) 
	{
		VEC3_ROTATE_A_B(degrees, z, x)
	}
	static Vec3Generic fromRotAndDist(Number degs, Number length, Number zComp = 0) 
	{
		Number rads = degreestoradians(degs); 
		return Vec3Generic(length * cos(rads), length * sin(rads), zComp);
	}
};

template <class Number>
class Vec2Generic 
{
public:
	union {
		struct {
			Number x;
			Number y;
		};
		Number loc[2];
	};
	template <class OtherVec>
	Vec2Generic(const OtherVec& other) : x(other.x), y(other.y) {}
	Vec2Generic(Number x, Number y) : x(x), y(y) {}
	template <class OtherNumber>
	Vec2Generic(const OtherNumber* other) : x(other[0]), y(other[1]) {}
	template <class OtherNumber>
	Vec2Generic(OtherNumber* other) : x(other[0]), y(other[1]) {}
	Vec2Generic() {}
	#if _MSC_VER >= 1800
	template <class OtherNumber>
	Vec2Generic(std::initializer_list<OtherNumber> list) 
	{
		int index = 0;
		for (auto x = list.begin(); x != list.end() && index < 2; x++, index++)
			this->operator [] (index) = (Number)*x;
	}
	template <class OtherNumber>
	Vec2Generic& operator = (std::initializer_list<OtherNumber> list) { ::new (this) (list); return *this; }
	#endif

	operator Number* () {return loc;}
	Vec2Generic operator + (const Vec2Generic& a) const {return Vec2Generic(x + a.x, y + a.y);}
	Vec2Generic operator - (const Vec2Generic& a) const {return Vec2Generic(x - a.x, y - a.y);}
	Vec2Generic operator - () const {return Vec2Generic(-x, -y);}
	Vec2Generic operator / (const Vec2Generic& other) const {return Vec2Generic(x / other.x, y / other.y);}
	Vec2Generic operator / (Number mult) const {return Vec2Generic(x / mult, y / mult);}
	Vec2Generic operator * (const Vec2Generic& other) const {return Vec2Generic(x * other.x, y * other.y);}
	Vec2Generic operator * (Number mult) const {return Vec2Generic(x * mult, y * mult);}
	Vec2Generic& operator += (const Vec2Generic& other) {x += other.x; y += other.y; return *this;}
	Vec2Generic& operator -= (const Vec2Generic& other) {x -= other.x; y -= other.y; return *this;}
	bool operator == (const Vec2Generic& other) const {return x == other.x && y == other.y;}
	bool operator != (const Vec2Generic& other) const {return x != other.x || y != other.y;}
	
	template <class OtherNumber>
	Vec2Generic& operator = (const Vec2Generic<OtherNumber>& other) {x = other.x; y = other.y; return *this;}
	Number& operator [] (int index) {return loc[index];}
	Number const& operator [] (int index) const {return loc[index];}

	Number getLength() const {return sqrt(x * x + y * y);}
	Number getDistanceTo(const Vec2Generic& other) const {return Vec2Generic(x - other.x, y - other.y).getLength();}
	Number getDotProduct(const Vec2Generic& other) const {return x * other.x + y * other.y;}
	Number getAngle() const {return radianstodegrees(atan2(y, x));}
	Number getDeterminant(const Vec2Generic& other) const {return x * other.y - y * other.x;}
	template <class OtherNumber>
	void copyTo(OtherNumber* dest) const {dest[0] = (OtherNumber)x; dest[1] = (OtherNumber)y;}
	void normalize() 
	{
		Number length = getLength();
		x /= length;
		y /= length;
	}
	void rotate(Number degrees) 
	{
		Number rads = degreestoradians(degrees);
		Number cosRads = cos(rads);
		Number sinRads = sin(rads);
		Vec2Generic temp = *this;
		x = cosRads * temp.x - sinRads * temp.y;
		y = sinRads * temp.x + cosRads * temp.y;
	}
	static Vec2Generic fromRotAndDist(Number degs, Number length) 
	{
		Number rads = degreestoradians(degs); 
		return Vec2Generic(length * cos(rads), length * sin(rads));
	}

};

typedef Vec4Generic<double> Vec4;
typedef Vec4Generic<float> Vec4f;
typedef Vec3Generic<double> Vec3;
typedef Vec3Generic<float> Vec3f;
typedef Vec2Generic<double> Vec2;
typedef Vec2Generic<float> Vec2f;

class NetNodeEdge: public CouplingDataType
{
public:
	NetNodeEdge() : isInputOpen(false), distance(0.0), filledLength(0.0), lastExitTime(0.0), lastExitSize(0.0), 
					lastEntryPort(0), spacing(0.0), isSplineOwner(false), maxSpeed(0.0), userDistance(0.0), splineEndRot(0.0), blockedLength(0.0),
					activeTravelersNode(0), entryRequestsNode(0), spline(0), arrowMeshIndex(0)
		{}
	NetworkNode* netNode;
	double isOpen;
	treenode insideCoupling;

	// connectionType: one of: EDGE_NOCONNECTION EDGE_PASSING EDGE_NONPASSING
	double connectionType;
	bool isInputOpen;
	double distance;
	double filledLength;
	treenode activeTravelersNode;
	NodeListArray<NetworkRequest>::SdtSubNodeType activeTravelers;
	treenode entryRequestsNode;
	NodeListArray<>::NodePtrType entryRequests;
	double lastExitTime;
	double lastExitSize;
	int lastEntryPort;
	double spacing;
	bool isSplineOwner;
	treenode spline;
	double maxSpeed;
	double userDistance;
	double splineEndRot;
	double blockedLength;
	int arrowMeshIndex;
	int splinePointIndex;
	static const int arrowNrVerts = 8;
	
	FS_CONTENT_DLL_FUNC NetNodeEdge* getEdgePartner();
	FS_CONTENT_DLL_FUNC NetworkNode* getNetNodePartner();
	FS_CONTENT_DLL_FUNC TreeNode* getSplineHead() {return first(isSplineOwner ? spline : getEdgePartner()->spline);}
	FS_CONTENT_DLL_FUNC TreeNode* getNearSplinePoint() {return isSplineOwner ? first(spline) : last(getEdgePartner()->spline);}
	FS_CONTENT_DLL_FUNC TreeNode* getFarSplinePoint() {return isSplineOwner ? last(spline) : first(getEdgePartner()->spline);}
	FS_CONTENT_DLL_FUNC virtual const char* getClassFactory() {return "NetNodeEdge";}
	FS_CONTENT_DLL_FUNC virtual void bind();
	FS_CONTENT_DLL_FUNC void init(char connectionType, bool isSplineOwner);
	FS_CONTENT_DLL_FUNC virtual void reset(treenode returnTravelersTo);
	// buildMesh: adds the edge's vertices to the mesh. Here I pass a void* instead of a vector<Vec3f> because I don't want allobjects.h to 
	// include <vector> (modules must include allobjects.h, so I don't want to force <vector> upon them)
	FS_CONTENT_DLL_FUNC void buildMeshEdges(Mesh& mesh, bool includeSplineLines);
	FS_CONTENT_DLL_FUNC void buildMeshPoints(Mesh& mesh);
	FS_CONTENT_DLL_FUNC void buildMeshQuads(Mesh& mesh);
};

class NetworkTravelMember : public CouplingDataType
{
	public:
	FS_CONTENT_DLL_FUNC virtual const char* getClassFactory() {return "NetworkTravelMember";}
	FS_CONTENT_DLL_FUNC void bind();
	ObjRef<NetworkNode> resetNode;
	treenode currentNodeRefNode;
	NodeRef currentNodeRef;
	NodeRef reqNode;
	int blockingState;
};

void searchhelpmanual(string searchStr, treenode destNode);

;



// Global Functions
Variant pounddefines();

visible double addsphere(treenode obj, double xval, double yval, double zval, double radius);

visible void addsystemcontrolleritem(treenode controller, int prodid, int linenum, double target, double starttime, double num1, double num2, double num3, double num4);

visible treenode  bcgetitemkinematics(treenode conveyor, treenode item, int kintype);

visible double  bcgetitemposition(treenode conveyor, treenode item);

visible double  bcsetdirection(treenode conveyor, int direction);

visible double bcsetitemconveystate(treenode conveyor, treenode item, double startpoint, double startspeed, double destspeed, double accdec);

visible int calloperator(treenode dispatcher, treenode origin, treenode involved, double priority, int preempt);

visible double changeconveyorspeed(treenode conveyor, double newspeed);

visible treenode changetask(treenode tasksequence, int taskrank, unsigned short type, treenode involved1 DEFAULTNULL, treenode involved2 DEFAULTNULL, double var1 DEFAULTZERO, double var2 DEFAULTZERO, double var3 DEFAULTZERO, double var4 DEFAULTZERO);

Variant checkforcollisions(treenode obj);

unsigned int classtype(treenode involved);

Variant closenodeedge(treenode curnode, char* edgename);

visible double closenodeedge(treenode curnode, int edgenum);

Variant containerdragconnection(treenode fromobject, treenode toobject, char characterpressed);

visible double containerentry(treenode container, treenode item);

visible double containerexit(treenode container, treenode item);

visible double contextdragconnection(treenode fromobject, treenode toobject, char keypressed);

Variant contextdragconnection(treenode fromobject, treenode toobject, string keypressed);

visible treenode createcoordinatedtasksequence(treenode dispatcher);

visible treenode createdelaytask(treenode dispatcher,double delaytime,double state,double priority,int preempt);

visible treenode createemptytasksequence(treenode dispatcher, double priority, int preempt);

visible treenode createglobaltasksequence(string name, treenode dispatcher, treenode d1, treenode d2, treenode d3, treenode d4, treenode d5);

visible treenode createloadtask(treenode dispatcher,treenode destination,treenode flowitem,double priority,int preempt);

visible treenode createsendmessagetask(treenode dispatcher,treenode receiver, double priority,int preempt,double param1,double param2,double param3);

visible treenode createstandardtask(treenode dispatcher,treenode origin,treenode destination,treenode flowitem,double priority,int preempt);

visible treenode createtravelloadtask(treenode dispatcher,treenode destination,treenode flowitem,double priority,int preempt);

visible treenode createtraveltask(treenode dispatcher,treenode destination,double priority,int preempt);

visible treenode createtraveltolocandwaittask(treenode dispatcher,double relativeloc,double xloc,double yloc,double zloc,double endspeed,double state,double priority,int preempt);

visible treenode createtraveltoloctask(treenode dispatcher,int relativeloc,double xloc,double yloc,double zloc,double endspeed,double priority,int preempt);

visible treenode createtravelunloadtask(treenode dispatcher,treenode destination,treenode flowitem,double priority,int preempt);

visible treenode createunloadtask(treenode dispatcher,treenode destination,treenode flowitem,double priority,int preempt);

treenode createwaittask(treenode dispatcher,double state,double priority,int preempt);

visible double defaultdragconnection(treenode fromobject, treenode toobject, char characterpressed);

visible treenode derefcoupling(treenode coupling);

int destroymessageeventfilter(treenode object, double simtime, int code, void* data, treenode involved);

Variant destroymessageevents(treenode object, double simtime, treenode fromobj, double p1 DEFAULTPARAM(FLT_MAX), double p2 DEFAULTPARAM(FLT_MAX), double p3 DEFAULTPARAM(FLT_MAX));

visible double dispatchcoordinatedtasksequence(treenode tasksequence, treenode dispatcher DEFAULTNULL);

visible double dispatchtasksequence(treenode tasksequence, treenode dispatcher DEFAULTNULL);

visible double distancetotravel(treenode traveler, treenode destination);

visible double drawspheres(treenode object, treenode view);

Variant draw_spheres(treenode whose, treenode window, double color[4]);

visible int emptyfluidobject(treenode curobj);

visible int enablecode(treenode target, int mode DEFAULTZERO);

visible double endwaittask(treenode dispatcher);

treenode* enumerateteam(treenode team, int * returnnrofoperators, int recursivecall DEFAULTZERO);

visible int evaluatepullcriteria(treenode fr, treenode item, int port, int bypassflags);

__declspec(dllexport) Variant fglinfo(int op, treenode view);

treenode findnextclassvariable(treenode*curclass, treenode curvariable);

visible double freeoperators(treenode dispatcher, treenode involved);

Variant fsRotatexy(double matrix[4][4], double rz);

Variant fsScalexy(double matrix[4][4], double sx, double sy);

Variant fsTranslatexy(double matrix[4][4], double x, double y);

visible treenode getallocatedfromkey(treenode tasksequence, int key);

visible treenode getcoordinatedtasksequence(treenode dispatcher, int tsrank);

visible double getcurtask(treenode tasksequence);

visible treenode getdashboardcontrol(char* id, treenode startnode);

visible double getedgedist(treenode netnode, int edgenum);

visible double getedgespeedlimit(treenode netnode, int edgenum);

visible double geteventtime(char *eventname, double mode);

Variant geteventtime(string eventname, double mode);

visible treenode getiteminvolved(treenode item);

visible int getitemsendto(treenode item);

visible int getitemstate(treenode item);

visible double getitemvar(treenode item, int index);

visible double getlinecontrollerdata(treenode controller, int data, int column);

visible treenode getnetnode(treenode object, int index);

visible treenode getnetnodespline(treenode netnode, int outport);

visible double getnetworkdistance(int fromCol, int toCol);

visible treenode getnextparametersobject(treenode curobj, string focus, int useclass, int forward);

visible int getnextnetnodeoutport(int fromnn, int tonn);

visible int getnextnetnode(int fromnn, int tonn);

treenode getnextpullitem();

visible double getnroftasks(treenode tasksequence);

visible unsigned int getpreempt(treenode tasksequence);

visible double getpriority(treenode tasksequence);

visible double getreportnum(treenode tableobj, int column, int rowsback);

visible treenode gettaskinvolved(treenode tasksequence, unsigned int rankrequested, unsigned int involvednum);

visible treenode gettasksequence(treenode dispatcher, double tsrank);

visible treenode gettasksequencequeue(treenode dispatcher);

visible double gettaskstate(treenode tasksequence, unsigned int rankrequested);

visible unsigned int gettasktype(treenode tasksequence, int rankrequested);

visible double gettaskvariable(treenode tasksequence, unsigned int rankrequested, unsigned int varnum);

visible treenode gettenavigator(treenode te);

visible treenode gettenetnode(treenode te);

visible double gettenetworkinfo(treenode te, treenode destobj, int info);

visible double gettotalnroftasks(treenode tasksequence);

visible double gettrackedvariable(char* name);

__declspec(dllexport) double gettrackedvariable(char* name, int valtype);

__declspec(dllexport) double gettrackedvariable(treenode trackedvar);

__declspec(dllexport) double gettrackedvariable(treenode trackedvar, int valtype);

visible treenode getutilizedobject(treenode team, treenode item, treenode station, int operatornr);

visible treenode getvirtualexit(treenode netnode, int index);

Variant groupaddmember(treenode child, treenode parent, char* groupname);

Variant groupdelete(treenode child, char* groupname);

treenode groupmember(treenode child, char* groupname, unsigned int membernum);

Variant groupnrofmembers(treenode child, char* groupname);

treenode groupparent(treenode child, char *groupname);

Variant groupremovemember(treenode child, char* groupname);

visible double holditem(treenode item);

visible int inititem(treenode item);

int initpull(treenode object, int outPort);

visible int insertallocatetask(treenode tasksequence, treenode dispatcher, double priority, double preempt, int noblock DEFAULTZERO);

visible int insertdeallocatetask(treenode tasksequence, int executerkey, int noblock DEFAULTZERO);

visible int insertmultiallocatetask(treenode tasksequence, int range);

visible int insertproxytask(treenode tasksequence, unsigned int executerkey, unsigned int  type, treenode involved1, treenode involved2,double var1 DEFAULTZERO, double var2  DEFAULTZERO, double var3 DEFAULTZERO, double var4 DEFAULTZERO);

__declspec(dllexport) int insertproxytask(treenode tasksequence, unsigned int executerkey, unsigned int  type, treenode involved1, int involved2,double var1 DEFAULTZERO, double var2 DEFAULTZERO, double var3 DEFAULTZERO, double var4 DEFAULTZERO);

__declspec(dllexport) int insertproxytask(treenode tasksequence, unsigned int executerkey, unsigned int  type, int involved1, treenode involved2,double var1 DEFAULTZERO, double var2 DEFAULTZERO, double var3 DEFAULTZERO, double var4 DEFAULTZERO);

__declspec(dllexport) int insertproxytask(treenode tasksequence, unsigned int executerkey, unsigned int  type, int involved1, int involved2,double var1 DEFAULTZERO, double var2 DEFAULTZERO, double var3 DEFAULTZERO, double var4 DEFAULTZERO);

__declspec(dllexport) int insertproxytask(treenode tasksequence, unsigned int executerkey, unsigned int  type, int involved1);

__declspec(dllexport) int insertproxytask(treenode tasksequence, unsigned int executerkey, unsigned int  type, treenode involved1);

__declspec(dllexport) int insertproxytask(treenode tasksequence, unsigned int executerkey, unsigned int  type);

visible int insertsynctask(treenode tasksequence, int taskkey);

visible treenode inserttask(treenode tasksequence,  unsigned int  type, treenode involved1 DEFAULTNULL, treenode involved2 DEFAULTNULL , double var1 DEFAULTZERO , double var2 DEFAULTZERO , double var3 DEFAULTZERO , double var4 DEFAULTZERO);

visible int isedgeforward(treenode netnode, int outport);

Variant loadnodestate(treenode loadnode, treenode* nodes DEFAULTNULL);

Variant loadstatelayer(treenode layer);

visible treenode loaduserlibrary(string filename, treenode libraryview DEFAULTNULL, int reloadmedia DEFAULTZERO, int changeitemcurrent DEFAULTZERO, int autoinstall DEFAULTZERO);

double memberadd(treenode child, string parentname, int type);

double memberremove(treenode child, string parentname, int type);

double memberremoveall(string parentname, int type);

Variant modelupdatelayer(treenode layer, char* newversion, char *oldversion);

visible double movetasksequence(treenode tasksequence, treenode dispatcher);

visible treenode netnodefromrank(int netnoderank);

visible double notifylinecontroller(treenode obj, int therank, double objoutput, int sendinglast);

Variant opennodeedge(treenode curnode, char* edgename);

visible double opennodeedge(treenode curnode, int edgenum);

visible double optimizenetwork();

visible double pickoffsetx(treenode station, treenode item, treenode otherobject);

visible double pickoffsety(treenode station, treenode item, treenode otherobject);

visible double pickoffsetz(treenode station, treenode item, treenode otherobject);

visible double placeoffsetx(treenode station, treenode item, treenode otherobject);

visible double placeoffsety(treenode station, treenode item, treenode otherobject);

visible double placeoffsetz(treenode station, treenode item, treenode otherobject);

visible double profiletasksequence(treenode ts);

visible int pullitem(treenode fr, treenode item, int port, int bypassflags DEFAULTZERO);

visible void pushitem(treenode item, treenode toFR, int outPort, int inPort);

visible double rackdrawfilledcell(treenode rack, int bay, int level, double x, double y, double z, double sx, double sy, double sz, double red, double green, double blue, int glbeginend DEFAULTONE);

visible double rackdrawvirtualcontent(treenode rack,double bayfillperc, double levelfillperc, double itemdepth, double red, double green, double blue, double virtualonly DEFAULTONE);

visible double rackgetbaycontent(treenode rack, int bay);

visible double rackgetbayofitem(treenode rack, treenode item);

visible double rackgetbayloc(treenode rack,int bay);

visible double rackgetbaysize(treenode rack,int bay);

visible double rackgetcellcontent(treenode rack, int bay, int level);

visible double rackgetcellvar(treenode rack, int bay, int level, int varnum, treenode storedlabel DEFAULTNULL);

visible treenode rackgetcontenttable(treenode rack);

visible double rackgetitemcellrank(treenode rack, treenode item);

visible treenode rackgetitembybaylevel(treenode rack, int bay, int level, int itemrank DEFAULTONE);

visible double rackgetlevelofitem(treenode rack, treenode item);

visible double rackgetlevelloc(treenode rack,int bay, int level);

visible double rackgetlevelsize(treenode rack,int bay, int level);

visible double rackgetnrofbays(treenode rack);

visible double rackgetnroflevels(treenode rack, int bay DEFAULTONE);

visible double rackrecycleitem(treenode rack, treenode item, int binrank);

visible treenode rackrestoreitem(treenode rack, int binrank, int bay, int level, int position);

visible double racksetcellcontent(treenode rack, int bay, int level, int contentval);

visible double racksetcellvar(treenode rack, int bay, int level, int varnum, double value, treenode storedlabel DEFAULTNULL);

visible int rankfromnetnode(treenode netnode);

visible double reassignnetnode(treenode taskexecuter, treenode netnode);

visible double receiveitem(treenode station);

__declspec(dllexport) double receiveitem(treenode station, int port);

treenode recycledtasksequences();

treenode recycledtasks();

treenode recycledtravelrequests();

treenode recyclednetworkrequests();

visible double recycleitem(treenode item, int binrank);

visible double recyclenode(treenode node, treenode containerbranch);

visible double redirectnetworktraveler(treenode traveler, treenode newdest);

visible double releaseitem(treenode item);

__declspec(dllexport) double releaseitem(treenode item, int port);

Variant releaseoperators(treenode dispatcher, treenode involved);

visible double reordertasks(treenode involved);

visible double requestoperators(treenode dispatcher, treenode station, treenode involved, int nrofops, double priority, int preempt);

visible double rerankbesttask(treenode involved);

treenode restorenode(treenode containerbranch, treenode destcontainer);

__declspec(dllexport) double resumeobject(treenode involved, int id, int stateprofile);

__declspec(dllexport) double resumeobject(treenode involved);

visible double resumeobject(treenode involved, int id);

visible double resumetransportsin(treenode object, int rank DEFAULTZERO);

visible double resumetransportsout(treenode object, int rank DEFAULTZERO);

visible double rotationproject(treenode originSpace, double rx, double ry, double rz, treenode ontoSpace, double* rotationsOut);

Variant savenodestate(treenode savenode, int size DEFAULTZERO, int nrofpointers DEFAULTONE, treenode* nodes DEFAULTNULL);

Variant savestatelayer(treenode layer);

visible double savestoppedtransportin(treenode object, treenode transporter);

visible double savestoppedtransportout(treenode object, treenode transporter);

visible double senddelayedmessage(treenode toobject, double delaytime, treenode fromobject, double par1, double par2 DEFAULTZERO, double par3 DEFAULTZERO);

Variant senddelayedmessage(treenode toobject, double delaytime, treenode fromobject);

visible double setcollisioncheck(treenode collisionobj, double val,double interval DEFAULTZERO);

visible double seteventtime(char *eventname, double timeval, double mode, double newevent);

Variant seteventtime(string eventname, double timeval, double mode, double newevent);

visible double setiteminvolved(treenode item, treenode involved);

visible double setitemsendto(treenode item, int sendto);

visible double setitemvar(treenode item, int index, double val);

visible double setpreempt(treenode tasksequence, unsigned int newpreempt);

visible double setpriority(treenode tasksequence, double newpriority);

visible double setresetposition(treenode obj);

visible double settrackedvariable(char* name, double value);

__declspec(dllexport) double settrackedvariable(treenode trackedvar, double value);

__declspec(dllexport) double stopobject(treenode involved, int state, int id, double priority, int stateprofile);

__declspec(dllexport) double stopobject(treenode involved, int state);

visible double stopobject(treenode involved, int state, int id, double priority);

Variant syncmember(treenode child, char * groupname);

Variant syncmemberauto(treenode child, char * groupname);

Variant syncquantity(treenode child, char* groupname);

visible double trackdefaultsoncreate(treenode item);

visible double trackdefaultsondestroy(treenode item);

visible double trafficcontrolinfo(treenode tc, int info, double _a, double _b);

visible double transportincomplete(treenode object, treenode item, int portnumber DEFAULTZERO, treenode transporter DEFAULTNULL);

visible double transportoutcomplete(treenode object, treenode item, int portnumber DEFAULTZERO, treenode transporter DEFAULTNULL);

visible double updatelocations(treenode object);

visible void updatestates();

visible void updatetoolsmenu();

__declspec(dllexport) double updatereport(double reportnum);

__declspec(dllexport) double updatereport(char* reportname);

__declspec(dllexport) double updatereport(treenode thereport);

Variant updateconveyorsectioninfo(treenode conveyor);


// FlexSimEventHandler
class FlexSimEventHandler : public ObjectDataType
{
public:


// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onDestroy(treenode view);

FS_CONTENT_DLL_FUNC virtual double onDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double onDrawPlanar(treenode view);

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double onOutOpen(int port);

FS_CONTENT_DLL_FUNC virtual double onInOpen(int port);

FS_CONTENT_DLL_FUNC virtual double onClick(treenode view, int code);

FS_CONTENT_DLL_FUNC virtual Variant onMessage(treenode fromobject, const Variant& par1, const Variant& par2, const Variant& par3);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onStartSimulation();

FS_CONTENT_DLL_FUNC virtual double onDrag(treenode view);

FS_CONTENT_DLL_FUNC virtual double onRunWarm();

FS_CONTENT_DLL_FUNC virtual double onUndo(bool isUndo, treenode undoRecord);

FS_CONTENT_DLL_FUNC virtual double stopObject(int stopstate, int id, double priority DEFAULTZERO, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject(int id, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject();

FS_CONTENT_DLL_FUNC virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC virtual double getPickOffset(treenode involvedobj, treenode toobject, double* returnarray);

FS_CONTENT_DLL_FUNC virtual double getPlaceOffset(treenode involvedobj, treenode fromobject,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual double rotateAroundAxis(double angle, double x, double y);

FS_CONTENT_DLL_FUNC virtual double flipAroundAxis(const Vec2& point1, const Vec2& point2);

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode fromObj);

FS_CONTENT_DLL_FUNC static double toggleCppVarsOnCreate(treenode theobject);

FS_CONTENT_DLL_FUNC virtual double onTransportInNotify(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onTransportOutNotify(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onTransportOutComplete(treenode item, int portnumber, treenode transporter DEFAULTNULL);

FS_CONTENT_DLL_FUNC virtual double onTransportInComplete(treenode item, int portnumber, treenode transporter DEFAULTNULL);

FS_CONTENT_DLL_FUNC treenode getEventInfoObject(const char* eventName);

FS_CONTENT_DLL_FUNC static treenode s_getEventInfoObject(treenode holder, const char* eventTitle);

FS_CONTENT_DLL_FUNC double resetLabels();

FS_CONTENT_DLL_FUNC virtual void bindEvents();

FS_CONTENT_DLL_FUNC virtual void bindStatistics();

FS_CONTENT_DLL_FUNC treenode stateProfileResolver(const Variant& p1);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FlexSimObject
class FlexSimObject : public FlexSimEventHandler
{
public:

TreeNode* node_v_messagetrigger;
TreeNode* node_v_ondrawtrigger;
TreeNode* node_v_timetables;
#define v_timetables node_v_timetables->safedatafloat()[0]
TreeNode* node_v_networknodes;
#define v_networknodes node_v_networknodes->safedatafloat()[0]
TreeNode* node_v_timeoflaststop;
#define v_timeoflaststop node_v_timeoflaststop->safedatafloat()[0]
TreeNode* node_v_nrofstops;
#define v_nrofstops node_v_nrofstops->safedatafloat()[0]
TreeNode* node_v_statebeforestop;
#define v_statebeforestop node_v_statebeforestop->safedatafloat()[0]
TreeNode* node_v_collisionspheres;
#define v_collisionspheres node_v_collisionspheres->safedatafloat()[0]
TreeNode* node_v_collisionobjects;
#define v_collisionobjects node_v_collisionobjects->safedatafloat()[0]
TreeNode* node_v_resettrigger;
TreeNode* node_v_savedstate;
#define v_savedstate node_v_savedstate->safedatafloat()[0]
TreeNode* node_v_resetposition;
#define v_resetposition node_v_resetposition->safedatafloat()[0]
TreeNode* node_v_doanimations;
#define v_doanimations node_v_doanimations->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC  FlexSimObject();

FS_CONTENT_DLL_FUNC virtual double onDestroy(treenode view);

FS_CONTENT_DLL_FUNC virtual double onDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double onKeyedClick(treenode view, int code, char key);

FS_CONTENT_DLL_FUNC virtual Variant onMessage(treenode fromobject, const Variant& par1, const Variant& par2, const Variant& par3);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double stopObject(int stopstate, int id, double priority DEFAULTZERO, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual void onInitialStop();

FS_CONTENT_DLL_FUNC virtual double resumeObject(int id, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject();

FS_CONTENT_DLL_FUNC virtual void onFinalResume();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC double drawStopped(double red, double blue, double green);

FS_CONTENT_DLL_FUNC virtual double getPickOffset(treenode involvedobj, treenode toobject, double* returnarray);

FS_CONTENT_DLL_FUNC virtual double getPlaceOffset(treenode involvedobj, treenode fromobject,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC double execDelayedMessage(treenode involved, void * datastring);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual double saveState();

FS_CONTENT_DLL_FUNC virtual double loadState();

FS_CONTENT_DLL_FUNC virtual double updateVersion(char* newversion, char* oldversion);

FS_CONTENT_DLL_FUNC double drawPortInfo(treenode view);

FS_CONTENT_DLL_FUNC virtual int checkCollisions();

FS_CONTENT_DLL_FUNC static double catchError(string stra, string strb);

FS_CONTENT_DLL_FUNC double moveToResetPosition();

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);

FS_CONTENT_DLL_FUNC static char* displayMessageData(int code, char* edata);

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// c++ attributes
double* protectLocs;

unsigned char portInfoFlag;

treenode pickOffset = nullptr;

treenode placeOffset = nullptr;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FixedResource
class FixedResource : public FlexSimObject
{
public:

TreeNode* node_v_nrreleased;
#define v_nrreleased node_v_nrreleased->safedatafloat()[0]
TreeNode* node_v_pull;
#define v_pull node_v_pull->safedatafloat()[0]
TreeNode* node_v_sendtoport;
TreeNode* node_v_receivefromport;
TreeNode* node_v_pullrequirement;
TreeNode* node_v_entrytrigger;
TreeNode* node_v_exittrigger;
TreeNode* node_v_usetransport;
#define v_usetransport node_v_usetransport->safedatafloat()[0]
TreeNode* node_v_transportpriority;
#define v_transportpriority node_v_transportpriority->safedatafloat()[0]
TreeNode* node_v_preempttransport;
#define v_preempttransport node_v_preempttransport->safedatafloat()[0]
TreeNode* node_v_transportdispatcher;
TreeNode* node_v_nroftransportsout;
#define v_nroftransportsout node_v_nroftransportsout->safedatafloat()[0]
TreeNode* node_v_nroftransportsin;
#define v_nroftransportsin node_v_nroftransportsin->safedatafloat()[0]
TreeNode* node_v_outwaitinfo;
#define v_outwaitinfo node_v_outwaitinfo->safedatafloat()[0]
TreeNode* node_v_sendtocontinuous;
#define v_sendtocontinuous node_v_sendtocontinuous->safedatafloat()[0]
TreeNode* node_v_pullcontinuous;
#define v_pullcontinuous node_v_pullcontinuous->safedatafloat()[0]
TreeNode* node_v_lifo;
#define v_lifo node_v_lifo->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC  FixedResource();

FS_CONTENT_DLL_FUNC double onOutOpen(int port);

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC virtual double releaseItem(treenode item);

FS_CONTENT_DLL_FUNC virtual double releaseItem(treenode item, int port);

FS_CONTENT_DLL_FUNC inline int releaseItemToPort(treenode item, int porttoopen);

FS_CONTENT_DLL_FUNC virtual double outOpenEvent(FixedResource* otherobject, int search, int port, int otherport);

FS_CONTENT_DLL_FUNC virtual double receiveItem();

FS_CONTENT_DLL_FUNC virtual double receiveItem(int port);

FS_CONTENT_DLL_FUNC inline int receiveItemFromPort(int porttoopen);

FS_CONTENT_DLL_FUNC virtual double inOpenEvent(FixedResource* otherobject, int search, double port );

FS_CONTENT_DLL_FUNC virtual double pushItem(treenode item, FixedResource* otherobject, int port, int otherport);

FS_CONTENT_DLL_FUNC virtual double pullItem(treenode item, int port, int bypassflags);

FS_CONTENT_DLL_FUNC virtual double evaluatePullCriteria(treenode item, int port, int bypassflags);

FS_CONTENT_DLL_FUNC virtual double onTransportInNotify(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onTransportOutNotify(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onTransportOutComplete(treenode item, int portnumber, treenode transporter DEFAULTNULL);

FS_CONTENT_DLL_FUNC virtual double onTransportInComplete(treenode item, int portnumber, treenode transporter DEFAULTNULL);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC static inline FRItemInfo* getItemInfo(treenode flowitem);

FS_CONTENT_DLL_FUNC int initItem(treenode flowitem);

FS_CONTENT_DLL_FUNC static int setItemVar(treenode flowitem, int varnum, double val);

FS_CONTENT_DLL_FUNC static double getItemVar(treenode flowitem, int varnum);

FS_CONTENT_DLL_FUNC static int setItemInvolved(treenode flowitem, treenode involved);

FS_CONTENT_DLL_FUNC static treenode getItemInvolved(treenode flowitem);

FS_CONTENT_DLL_FUNC static FixedResource* getItemCurFR(treenode flowitem);

FS_CONTENT_DLL_FUNC double holdItem(treenode flowitem);

FS_CONTENT_DLL_FUNC static inline double getItemState(treenode flowitem);

FS_CONTENT_DLL_FUNC static double setItemState(treenode flowitem, int state);

FS_CONTENT_DLL_FUNC static int getItemSendTo(treenode flowitem);

FS_CONTENT_DLL_FUNC static int setItemSendTo(treenode flowitem, int sendto);

FS_CONTENT_DLL_FUNC double cleanItemData(treenode item);

FS_CONTENT_DLL_FUNC double closeInvolvedPorts(treenode item);

FS_CONTENT_DLL_FUNC virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC treenode createMoveTaskSequence(treenode dispatcher, treenode involved, treenode origin, treenode destination, double outportnumber, double inportnumber);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject();

FS_CONTENT_DLL_FUNC double saveState();

FS_CONTENT_DLL_FUNC double loadState();

FS_CONTENT_DLL_FUNC double resumeTransportsOut(int trank DEFAULTZERO);

FS_CONTENT_DLL_FUNC double resumeTransportsIn(int trank DEFAULTZERO);

FS_CONTENT_DLL_FUNC double saveStoppedTransportOut(treenode transporter);

FS_CONTENT_DLL_FUNC double saveStoppedTransportIn(treenode transporter);

FS_CONTENT_DLL_FUNC virtual PullIterator& initPull(int outPort);

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// c++ attributes
double inPort;

treenode lastReleased;

treenode curTransporter;

int pullItemCalled;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Navigator
class Navigator : public FlexSimObject
{
public:

TreeNode* node_v_travelmembers;
#define v_travelmembers node_v_travelmembers->safedatafloat()[0]
TreeNode* node_v_activetravelmembers;
#define v_activetravelmembers node_v_activetravelmembers->safedatafloat()[0]
TreeNode* node_v_lastupdatetime;
#define v_lastupdatetime node_v_lastupdatetime->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC virtual double navigateToObject(treenode traveler, treenode destination, double endSpeed);

FS_CONTENT_DLL_FUNC virtual double navigateToLoc(treenode traveler, double* destLoc, double endSpeed);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC treenode createTravelMemberNode(TaskExecuter* involvedtaskexecuter, FlexSimObject* destination, double totaldistance, double extravars);

FS_CONTENT_DLL_FUNC virtual double abortTravel(treenode traveler, treenode newts);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double updateLocations(TaskExecuter* te);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual double queryDistance(TaskExecuter* taskexecuter, FlexSimObject* destination);

FS_CONTENT_DLL_FUNC double saveState();

FS_CONTENT_DLL_FUNC double loadState();

FS_CONTENT_DLL_FUNC static float saveTravelRequestState(treenode reqnode);

FS_CONTENT_DLL_FUNC static float loadTravelRequestState(treenode reqnode);

FS_CONTENT_DLL_FUNC virtual treenode addMember(TaskExecuter* te);

FS_CONTENT_DLL_FUNC virtual treenode addCopiedMember(TaskExecuter* te, TaskExecuter* original);

FS_CONTENT_DLL_FUNC virtual void bindTEEvents(TaskExecuter* te);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// GlobalTable
class GlobalTable : public ObjectDataType
{
public:

TreeNode* node_v_data;
#define v_data node_v_data->safedatafloat()[0]
TreeNode* node_v_rows;
#define v_rows node_v_rows->safedatafloat()[0]
TreeNode* node_v_columns;
#define v_columns node_v_columns->safedatafloat()[0]
TreeNode* node_v_initonreset;
#define v_initonreset node_v_initonreset->safedatafloat()[0]
TreeNode* node_v_width;
#define v_width node_v_width->safedatafloat()[0]
TreeNode* node_v_height;
#define v_height node_v_height->safedatafloat()[0]
TreeNode* node_v_cellwidth;
#define v_cellwidth node_v_cellwidth->safedatafloat()[0]
TreeNode* node_v_cellheight;
#define v_cellheight node_v_cellheight->safedatafloat()[0]

// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// UserEvent
class UserEvent : public ObjectDataType
{
public:

TreeNode* node_v_time;
#define v_time node_v_time->safedatafloat()[0]
TreeNode* node_v_repeat;
#define v_repeat node_v_repeat->safedatafloat()[0]
TreeNode* node_v_event;
TreeNode* node_v_reset;
#define v_reset node_v_reset->safedatafloat()[0]
TreeNode* node_v_firsttime;
#define v_firsttime node_v_firsttime->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double updateVersion(char* newversion, char* oldversion);

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// MTBFMTTR
class MTBFMTTR : public ObjectDataType
{
public:

TreeNode* node_v_members;
#define v_members node_v_members->safedatafloat()[0]
TreeNode* node_v_mtbf;
TreeNode* node_v_mttr;
TreeNode* node_v_state;
#define v_state node_v_state->safedatafloat()[0]
TreeNode* node_v_firstmtbf;
TreeNode* node_v_applyindividuals;
#define v_applyindividuals node_v_applyindividuals->safedatafloat()[0]
TreeNode* node_v_downtrigger;
TreeNode* node_v_uptrigger;
TreeNode* node_v_downfunction;
TreeNode* node_v_upfunction;
TreeNode* node_v_mtbfstates;
#define v_mtbfstates node_v_mtbfstates->safedatafloat()[0]
TreeNode* node_v_accuracy;
#define v_accuracy node_v_accuracy->safedatafloat()[0]
TreeNode* node_v_rangecutoff;
#define v_rangecutoff node_v_rangecutoff->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double updateVersion(char* newversion, char* oldversion);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual void bindEvents();

FS_CONTENT_DLL_FUNC virtual treenode getEventInfoObject(const char* eventName);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// TimeTable
class TimeTable : public ObjectDataType
{
public:

TreeNode* node_v_table;
#define v_table node_v_table->safedatafloat()[0]
TreeNode* node_v_members;
#define v_members node_v_members->safedatafloat()[0]
TreeNode* node_v_repeattime;
#define v_repeattime node_v_repeattime->safedatafloat()[0]
TreeNode* node_v_rows;
#define v_rows node_v_rows->safedatafloat()[0]
TreeNode* node_v_modelstarttime;
#define v_modelstarttime node_v_modelstarttime->safedatafloat()[0]
TreeNode* node_v_repeattype;
#define v_repeattype node_v_repeattype->safedatafloat()[0]
TreeNode* node_v_calendarstarttime;
#define v_calendarstarttime node_v_calendarstarttime->safedatafloat()[0]
TreeNode* node_v_snapto;
#define v_snapto node_v_snapto->safedatafloat()[0]
TreeNode* node_v_downtrigger;
TreeNode* node_v_uptrigger;
TreeNode* node_v_downfunction;
TreeNode* node_v_upfunction;

// c++ member functions

FS_CONTENT_DLL_FUNC virtual void bindEvents();

FS_CONTENT_DLL_FUNC virtual treenode getEventInfoObject(const char* eventName);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// NetworkNavigator
class NetworkNavigator : public Navigator
{
public:

TreeNode* node_v_nodemembers;
#define v_nodemembers node_v_nodemembers->safedatafloat()[0]
TreeNode* node_v_nrtofirstnode;
#define v_nrtofirstnode node_v_nrtofirstnode->safedatafloat()[0]
TreeNode* node_v_modified;
#define v_modified node_v_modified->safedatafloat()[0]
TreeNode* node_v_nodesize;
#define v_nodesize node_v_nodesize->safedatafloat()[0]
TreeNode* node_v_arrowsize;
#define v_arrowsize node_v_arrowsize->safedatafloat()[0]
TreeNode* node_v_connecting;
#define v_connecting node_v_connecting->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC virtual double navigateToObject(treenode traveler, treenode destination, double endspeed);

FS_CONTENT_DLL_FUNC virtual double navigateToLoc(treenode traveler, double* destLoc, double endSpeed);

FS_CONTENT_DLL_FUNC double finishTravel(treenode reqnode, int blocking DEFAULTZERO);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double generateDistanceTable();

FS_CONTENT_DLL_FUNC virtual treenode addMember(TaskExecuter* te);

FS_CONTENT_DLL_FUNC virtual NetworkTravelMember* addMember(TaskExecuter* taskexecuter, NetworkNode* networknode);

FS_CONTENT_DLL_FUNC virtual treenode addCopiedMember(TaskExecuter* te, TaskExecuter* original);

FS_CONTENT_DLL_FUNC int getNextOutPort(NetworkRequest* netreq);

FS_CONTENT_DLL_FUNC int getNextOutPort(NetworkNode* from, NetworkNode* to);

FS_CONTENT_DLL_FUNC double getNextOutPort(int fromRow, int toCol);

FS_CONTENT_DLL_FUNC double getDistRemaining(NetworkNode * netnode, int destcol);

FS_CONTENT_DLL_FUNC double toggleAllShowModes(double newmode, int selectedonly);

FS_CONTENT_DLL_FUNC virtual double abortTravel(treenode taskexecuternode, treenode newts);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC double reassignNetNode(treenode membernode, NetworkNode* tonetnode, int onreset DEFAULTZERO);

FS_CONTENT_DLL_FUNC double queryDistance(TaskExecuter* te, FlexSimObject* destobj);

FS_CONTENT_DLL_FUNC double queryDistanceEx(TaskExecuter* te, FlexSimObject* destobj, NetworkNode* originnetnode, NetworkNode** bestorigin DEFAULTNULL, NetworkNode** bestdestnode DEFAULTNULL, int * bestoriginrow DEFAULTNULL, int * bestdestcol DEFAULTNULL, double* bestdist DEFAULTNULL);

FS_CONTENT_DLL_FUNC double queryDistance(NetworkNode* from, NetworkNode* to);

FS_CONTENT_DLL_FUNC double queryDistance(int fromCol, int toCol);

FS_CONTENT_DLL_FUNC double getTravelerInfo(TaskExecuter* te, FlexSimObject * destobj, int info);

FS_CONTENT_DLL_FUNC virtual double updateVersion(char* newversion, char* oldversion);

FS_CONTENT_DLL_FUNC double redirectTraveler(treenode traveler, treenode newdest);

FS_CONTENT_DLL_FUNC virtual double saveState();

FS_CONTENT_DLL_FUNC virtual double loadState();

FS_CONTENT_DLL_FUNC static float saveNetworkRequestState(treenode reqnode);

FS_CONTENT_DLL_FUNC static float loadNetworkRequestState(treenode reqnode);

FS_CONTENT_DLL_FUNC double validateTravelMemberStructure(treenode curtmemnode);

FS_CONTENT_DLL_FUNC static treenode getTENetNode(treenode membernode);

FS_CONTENT_DLL_FUNC static NetworkNavigator* getInstance();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// VideoRecorder
class VideoRecorder : public ObjectDataType
{
public:

TreeNode* node_v_outputs;
#define v_outputs node_v_outputs->safedatafloat()[0]
TreeNode* node_v_sequences;
#define v_sequences node_v_sequences->safedatafloat()[0]
TreeNode* node_v_jobscallback;
TreeNode* node_v_preview;
#define v_preview node_v_preview->safedatafloat()[0]
TreeNode* node_v_active;
#define v_active node_v_active->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double getMetric(int metric, string sout, treenode seq, string slay);

FS_CONTENT_DLL_FUNC double getMetric(int metric, string sout, string sseq, string slay);

FS_CONTENT_DLL_FUNC double getMetric(int metric, string sout);

FS_CONTENT_DLL_FUNC double getMetric(int metric);

FS_CONTENT_DLL_FUNC treenode resolveSequence(treenode seqSubNode);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Mixer
class Mixer : public FixedResource
{
public:

TreeNode* node_v_batchquantity;
#define v_batchquantity node_v_batchquantity->safedatafloat()[0]
TreeNode* node_v_mixtime;
#define v_mixtime node_v_mixtime->safedatafloat()[0]
TreeNode* node_v_cleanuptime;
#define v_cleanuptime node_v_cleanuptime->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double resetVariables();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// GlobalVarGen
class GlobalVarGen : public ObjectDataType
{
public:

TreeNode* node_v_definecode;
TreeNode* node_v_loadcode;
TreeNode* node_v_table;
#define v_table node_v_table->safedatafloat()[0]
TreeNode* node_v_usercode;
TreeNode* node_v_commands;
#define v_commands node_v_commands->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double updateCode();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// WatchList
class WatchList : public ObjectDataType
{
public:

TreeNode* node_v_watchtable;
#define v_watchtable node_v_watchtable->safedatafloat()[0]
TreeNode* node_v_tablerowtemplate;
#define v_tablerowtemplate node_v_tablerowtemplate->safedatafloat()[0]
TreeNode* node_v_numwatches;
#define v_numwatches node_v_numwatches->safedatafloat()[0]
TreeNode* node_v_onchangetrigger;

// c++ member functions

FS_CONTENT_DLL_FUNC treenode findNode(treenode startnode, char *name);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// PreLoad
class PreLoad : public ObjectDataType
{
public:


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// DelayPipe
class DelayPipe : public FixedResource
{
public:

TreeNode* node_v_delaytime;
TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]
TreeNode* node_v_pipesections;
#define v_pipesections node_v_pipesections->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double resetVariables();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// ExcelAuto
class ExcelAuto : public ObjectDataType
{
public:

TreeNode* node_v_needtocompile;
#define v_needtocompile node_v_needtocompile->safedatafloat()[0]
TreeNode* node_v_excellocation;
TreeNode* node_v_curworkbook;
TreeNode* node_v_importexcelfiles;
#define v_importexcelfiles node_v_importexcelfiles->safedatafloat()[0]
TreeNode* node_v_importtable;
#define v_importtable node_v_importtable->safedatafloat()[0]
TreeNode* node_v_exporttable;
#define v_exporttable node_v_exporttable->safedatafloat()[0]
TreeNode* node_v_rowtemplate;
#define v_rowtemplate node_v_rowtemplate->safedatafloat()[0]
TreeNode* node_v_exporttemplate;
#define v_exporttemplate node_v_exporttemplate->safedatafloat()[0]
TreeNode* node_v_filetemplate;
#define v_filetemplate node_v_filetemplate->safedatafloat()[0]
TreeNode* node_v_sheet;
TreeNode* node_v_tname;
TreeNode* node_v_headerval;
#define v_headerval node_v_headerval->safedatafloat()[0]
TreeNode* node_v_datadistinctval;
#define v_datadistinctval node_v_datadistinctval->safedatafloat()[0]
TreeNode* node_v_usepostimportcode;
#define v_usepostimportcode node_v_usepostimportcode->safedatafloat()[0]
TreeNode* node_v_OnImport;
TreeNode* node_v_CustomImport;
TreeNode* node_v_CustomExport;
TreeNode* node_v_desccustomimport;
TreeNode* node_v_desccustomexport;

// c++ member functions

FS_CONTENT_DLL_FUNC double doImport();

FS_CONTENT_DLL_FUNC double doExport();

FS_CONTENT_DLL_FUNC double reimport();

FS_CONTENT_DLL_FUNC double importTables(int onreset);

FS_CONTENT_DLL_FUNC double updateProgress(string status, double value);

FS_CONTENT_DLL_FUNC double updateProgressExport(string status, double value);

FS_CONTENT_DLL_FUNC double excelFileChanged(treenode file);

FS_CONTENT_DLL_FUNC double getAndOpenWorkBook();

FS_CONTENT_DLL_FUNC double openWorkBook();

FS_CONTENT_DLL_FUNC double getRowHeaders(int startrow, int rows, int col);

FS_CONTENT_DLL_FUNC double getColHeaders(int startcol, int cols, int row);

FS_CONTENT_DLL_FUNC int getBundleColHeaders(int startcol, int cols, int row);

FS_CONTENT_DLL_FUNC double importData(int startrow, int startcol, int rows, int cols, int curtable, double percentdone, double percentmain);

FS_CONTENT_DLL_FUNC double importBundleData(int startrow, int startcol, int rows, int cols, int curtable, double percentdone, double percentmain);

FS_CONTENT_DLL_FUNC double exportData(int startrow, int startcol, int headers, int curtable, double percentdone, double percentmain);

FS_CONTENT_DLL_FUNC int isNumber(string str);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// DiscreteCombiner
class DiscreteCombiner : public FixedResource
{
public:

TreeNode* node_v_curaccum;
#define v_curaccum node_v_curaccum->safedatafloat()[0]
TreeNode* node_v_boxcollected;
#define v_boxcollected node_v_boxcollected->safedatafloat()[0]
TreeNode* node_v_packqty;
#define v_packqty node_v_packqty->safedatafloat()[0]
TreeNode* node_v_cycletime;
TreeNode* node_v_processfinishtrigger;
TreeNode* node_v_recycle;
#define v_recycle node_v_recycle->safedatafloat()[0]
TreeNode* node_v_curheight;
#define v_curheight node_v_curheight->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC double resetVariables();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// DiscreteGenerator
class DiscreteGenerator : public FixedResource
{
public:

TreeNode* node_v_rate;
#define v_rate node_v_rate->safedatafloat()[0]
TreeNode* node_v_scale;
#define v_scale node_v_scale->safedatafloat()[0]
TreeNode* node_v_timezerocreate;
#define v_timezerocreate node_v_timezerocreate->safedatafloat()[0]
TreeNode* node_v_interarrivaltime;
#define v_interarrivaltime node_v_interarrivaltime->safedatafloat()[0]
TreeNode* node_v_creationtrigger;
TreeNode* node_v_flowitemclass;
#define v_flowitemclass node_v_flowitemclass->safedatafloat()[0]
TreeNode* node_v_flowitembin;
#define v_flowitembin node_v_flowitembin->safedatafloat()[0]
TreeNode* node_v_flowitemtype;
#define v_flowitemtype node_v_flowitemtype->safedatafloat()[0]
TreeNode* node_v_flowitemname;

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double generateItem(double curitemtype, string itemname);


// c++ attributes
treenode flowitemtocreate;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// DiscreteProcessor
class DiscreteProcessor : public FixedResource
{
public:

TreeNode* node_v_rate;
#define v_rate node_v_rate->safedatafloat()[0]
TreeNode* node_v_processtime;
#define v_processtime node_v_processtime->safedatafloat()[0]
TreeNode* node_v_scale;
#define v_scale node_v_scale->safedatafloat()[0]
TreeNode* node_v_loss;
#define v_loss node_v_loss->safedatafloat()[0]
TreeNode* node_v_processfinishtrigger;
TreeNode* node_v_useprocessoperators;
#define v_useprocessoperators node_v_useprocessoperators->safedatafloat()[0]
TreeNode* node_v_processoperatorpriority;
#define v_processoperatorpriority node_v_processoperatorpriority->safedatafloat()[0]
TreeNode* node_v_preemptprocessoperators;
#define v_preemptprocessoperators node_v_preemptprocessoperators->safedatafloat()[0]
TreeNode* node_v_processdispatcher;
TreeNode* node_v_convey;
#define v_convey node_v_convey->safedatafloat()[0]
TreeNode* node_v_recycle;
#define v_recycle node_v_recycle->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double updateLocations();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FlowNode
class FlowNode : public FixedResource
{
public:

TreeNode* node_v_itemspeed;
TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]
TreeNode* node_v_sideoffset;
#define v_sideoffset node_v_sideoffset->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double releaseItem(treenode item);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Reservoir
class Reservoir : public FixedResource
{
public:

TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]
TreeNode* node_v_curcontent;
#define v_curcontent node_v_curcontent->safedatafloat()[0]
TreeNode* node_v_highmark;
#define v_highmark node_v_highmark->safedatafloat()[0]
TreeNode* node_v_middlemark;
#define v_middlemark node_v_middlemark->safedatafloat()[0]
TreeNode* node_v_lowmark;
#define v_lowmark node_v_lowmark->safedatafloat()[0]
TreeNode* node_v_lastouttime;
#define v_lastouttime node_v_lastouttime->safedatafloat()[0]
TreeNode* node_v_lastintime;
#define v_lastintime node_v_lastintime->safedatafloat()[0]
TreeNode* node_v_unitsinitem;
#define v_unitsinitem node_v_unitsinitem->safedatafloat()[0]
TreeNode* node_v_risethroughhighmarktrigger;
TreeNode* node_v_fallthroughhighmarktrigger;
TreeNode* node_v_risethroughmiddlemarktrigger;
TreeNode* node_v_fallthroughmiddlemarktrigger;
TreeNode* node_v_risethroughlowmarktrigger;
TreeNode* node_v_fallthroughlowmarktrigger;
TreeNode* node_v_inflowrate;
TreeNode* node_v_outflowrate;

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double drawBox(double minZ, double maxZ);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Recorder
class Recorder : public FlexSimObject
{
public:

TreeNode* node_v_timedriven;
#define v_timedriven node_v_timedriven->safedatafloat()[0]
TreeNode* node_v_timebetweenchecks;
#define v_timebetweenchecks node_v_timebetweenchecks->safedatafloat()[0]
TreeNode* node_v_outputtype;
#define v_outputtype node_v_outputtype->safedatafloat()[0]
TreeNode* node_v_datatype;
#define v_datatype node_v_datatype->safedatafloat()[0]
TreeNode* node_v_standardtype;
#define v_standardtype node_v_standardtype->safedatafloat()[0]
TreeNode* node_v_graphtype;
#define v_graphtype node_v_graphtype->safedatafloat()[0]
TreeNode* node_v_weighttype;
#define v_weighttype node_v_weighttype->safedatafloat()[0]
TreeNode* node_v_objectrank;
#define v_objectrank node_v_objectrank->safedatafloat()[0]
TreeNode* node_v_drawbackground;
#define v_drawbackground node_v_drawbackground->safedatafloat()[0]
TreeNode* node_v_histomin;
#define v_histomin node_v_histomin->safedatafloat()[0]
TreeNode* node_v_histomax;
#define v_histomax node_v_histomax->safedatafloat()[0]
TreeNode* node_v_histobuckets;
#define v_histobuckets node_v_histobuckets->safedatafloat()[0]
TreeNode* node_v_numpoints;
#define v_numpoints node_v_numpoints->safedatafloat()[0]
TreeNode* node_v_autodomain;
#define v_autodomain node_v_autodomain->safedatafloat()[0]
TreeNode* node_v_autorange;
#define v_autorange node_v_autorange->safedatafloat()[0]
TreeNode* node_v_xmin;
#define v_xmin node_v_xmin->safedatafloat()[0]
TreeNode* node_v_xmax;
#define v_xmax node_v_xmax->safedatafloat()[0]
TreeNode* node_v_ymin;
#define v_ymin node_v_ymin->safedatafloat()[0]
TreeNode* node_v_ymax;
#define v_ymax node_v_ymax->safedatafloat()[0]
TreeNode* node_v_tablexval;
TreeNode* node_v_tableyval;
TreeNode* node_v_linecolor;
#define v_linecolor node_v_linecolor->safedatafloat()[0]
TreeNode* node_v_graphtitle;
TreeNode* node_v_draw3dgraph;
#define v_draw3dgraph node_v_draw3dgraph->safedatafloat()[0]
TreeNode* node_v_datapointer;
#define v_datapointer node_v_datapointer->safedatafloat()[0]
TreeNode* node_v_numwatches;
#define v_numwatches node_v_numwatches->safedatafloat()[0]
TreeNode* node_v_graphdata;
#define v_graphdata node_v_graphdata->safedatafloat()[0]
TreeNode* node_v_watchtable;
#define v_watchtable node_v_watchtable->safedatafloat()[0]
TreeNode* node_v_bucketnames;
#define v_bucketnames node_v_bucketnames->safedatafloat()[0]
TreeNode* node_v_tablerowtemplate;
#define v_tablerowtemplate node_v_tablerowtemplate->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC treenode findNode(treenode startnode, char *name);

FS_CONTENT_DLL_FUNC double generateOutput();

FS_CONTENT_DLL_FUNC double drawHisto(treenode view);

FS_CONTENT_DLL_FUNC double drawBar(treenode view);

FS_CONTENT_DLL_FUNC double drawXYGraph(treenode view);

FS_CONTENT_DLL_FUNC double drawPieGraph(treenode view);

FS_CONTENT_DLL_FUNC double drawUserGraph(treenode view);

FS_CONTENT_DLL_FUNC double drawBarChart(treenode view, void * graphdata,int nrofinstances,double xmin, double xmax, double ymin, double ymax, char * charttitle);

FS_CONTENT_DLL_FUNC double drawLineGraph(treenode view, void * graphdata,int nrofinstances,double xmin, double xmax, double ymin, double ymax, char * charttitle);

FS_CONTENT_DLL_FUNC double drawPieChart(treenode view, void * graphdata,int nrofinstances,double xmin, double xmax, double ymin, double ymax, char * charttitle);

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// VisualTool
class VisualTool : public FlexSimObject
{
public:

TreeNode* node_v_shapetypes;
#define v_shapetypes node_v_shapetypes->safedatafloat()[0]
TreeNode* node_v_divisions;
#define v_divisions node_v_divisions->safedatafloat()[0]
TreeNode* node_v_repeatx;
#define v_repeatx node_v_repeatx->safedatafloat()[0]
TreeNode* node_v_repeaty;
#define v_repeaty node_v_repeaty->safedatafloat()[0]
TreeNode* node_v_nroftexts;
#define v_nroftexts node_v_nroftexts->safedatafloat()[0]
TreeNode* node_v_settextloc;
#define v_settextloc node_v_settextloc->safedatafloat()[0]
TreeNode* node_v_containercontent;
#define v_containercontent node_v_containercontent->safedatafloat()[0]
TreeNode* node_v_objectref;
TreeNode* node_v_textcode;
TreeNode* node_v_textnode;
TreeNode* node_v_textsize;
#define v_textsize node_v_textsize->safedatafloat()[0]
TreeNode* node_v_viewmagnification;
#define v_viewmagnification node_v_viewmagnification->safedatafloat()[0]
TreeNode* node_v_viewdistance;
#define v_viewdistance node_v_viewdistance->safedatafloat()[0]
TreeNode* node_v_textthickness;
#define v_textthickness node_v_textthickness->safedatafloat()[0]
TreeNode* node_v_billboardtype;
#define v_billboardtype node_v_billboardtype->safedatafloat()[0]
TreeNode* node_v_showcontents;
#define v_showcontents node_v_showcontents->safedatafloat()[0]
TreeNode* node_v_connectinputs;
TreeNode* node_v_connectoutputs;

// c++ member functions

FS_CONTENT_DLL_FUNC  VisualTool();

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onDestroy(treenode view);

FS_CONTENT_DLL_FUNC double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double buildMesh();

FS_CONTENT_DLL_FUNC double drawPlane();

FS_CONTENT_DLL_FUNC double drawCube();

FS_CONTENT_DLL_FUNC double drawColumn();

FS_CONTENT_DLL_FUNC double drawSphere();

FS_CONTENT_DLL_FUNC double drawString(treenode view);

FS_CONTENT_DLL_FUNC double drawFloor(treenode view);

FS_CONTENT_DLL_FUNC double arrangeObject(double posx, double posy, double posz, double rotx, double roty, double rotz, double size);

FS_CONTENT_DLL_FUNC double addText(treenode newtextobj);

FS_CONTENT_DLL_FUNC double removeText(treenode textobj);

FS_CONTENT_DLL_FUNC double containerEntry(treenode item);

FS_CONTENT_DLL_FUNC double containerExit(treenode item);

FS_CONTENT_DLL_FUNC double regenStayTimeHisto();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);

FS_CONTENT_DLL_FUNC double doConnectIndirection(treenode otherobject, char characterpressed, int tome);


// c++ attributes
Mesh shapeMesh;

int meshShapeType;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// StatisticObject
class StatisticObject : public ObjectDataType
{
public:


// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual Variant onMessage(treenode from, const Variant& p1, const Variant& p2, const Variant& p3);

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual double onRunWarm();

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode  view);

FS_CONTENT_DLL_FUNC virtual double onListen(treenode listenedto, treenode listenercoupling, int listenercode, int ecode, treenode involved, char* edata);

FS_CONTENT_DLL_FUNC virtual double hasAbility(int ability);

FS_CONTENT_DLL_FUNC virtual double drawGraph(treenode view);

FS_CONTENT_DLL_FUNC virtual double getAggregationType();

FS_CONTENT_DLL_FUNC virtual double enumerateAggregationList(treenode from);

FS_CONTENT_DLL_FUNC virtual double aggregateData(treenode destNode, treenode statNode, treenode pfm);

FS_CONTENT_DLL_FUNC virtual double getData(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOnlineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOfflineDependencies(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineInitializer(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineData(treenode from, treenode repDataNode);

FS_CONTENT_DLL_FUNC virtual double createCSV(char* filePath);

FS_CONTENT_DLL_FUNC virtual treenode addCopiedMember(treenode newObj, treenode original, treenode memberCoupling);

FS_CONTENT_DLL_FUNC virtual treenode addMember(treenode newObj);

FS_CONTENT_DLL_FUNC int checkDestroy();

FS_CONTENT_DLL_FUNC treenode getStateProfile(treenode object, int profileNum);

FS_CONTENT_DLL_FUNC double getStateTime(treenode profile, int state);

FS_CONTENT_DLL_FUNC int getStateUsed(treenode profile, int state);

FS_CONTENT_DLL_FUNC string getStateName(treenode profile, int stateNum);

FS_CONTENT_DLL_FUNC int getNumStates(treenode profile);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// StateChart
class StateChart : public StatisticObject
{
public:

TreeNode* node_v_objects;
#define v_objects node_v_objects->safedatafloat()[0]
TreeNode* node_v_colors;
#define v_colors node_v_colors->safedatafloat()[0]
TreeNode* node_v_charttype;
#define v_charttype node_v_charttype->safedatafloat()[0]
TreeNode* node_v_customnames;
#define v_customnames node_v_customnames->safedatafloat()[0]
TreeNode* node_v_statestrings;
#define v_statestrings node_v_statestrings->safedatafloat()[0]
TreeNode* node_v_usecollecttime;
#define v_usecollecttime node_v_usecollecttime->safedatafloat()[0]
TreeNode* node_v_mincollecttime;
#define v_mincollecttime node_v_mincollecttime->safedatafloat()[0]
TreeNode* node_v_maxcollecttime;
#define v_maxcollecttime node_v_maxcollecttime->safedatafloat()[0]
TreeNode* node_v_collecthistory;
#define v_collecthistory node_v_collecthistory->safedatafloat()[0]
TreeNode* node_v_filtermintime;
#define v_filtermintime node_v_filtermintime->safedatafloat()[0]
TreeNode* node_v_filtermaxtime;
#define v_filtermaxtime node_v_filtermaxtime->safedatafloat()[0]
TreeNode* node_v_filterednow;
#define v_filterednow node_v_filterednow->safedatafloat()[0]
TreeNode* node_v_showtotals;
#define v_showtotals node_v_showtotals->safedatafloat()[0]
TreeNode* node_v_showlegend;
#define v_showlegend node_v_showlegend->safedatafloat()[0]
TreeNode* node_v_stacked;
#define v_stacked node_v_stacked->safedatafloat()[0]
TreeNode* node_v_doutilization;
#define v_doutilization node_v_doutilization->safedatafloat()[0]
TreeNode* node_v_fontsize;
#define v_fontsize node_v_fontsize->safedatafloat()[0]
TreeNode* node_v_barsize;
#define v_barsize node_v_barsize->safedatafloat()[0]
TreeNode* node_v_precision;
#define v_precision node_v_precision->safedatafloat()[0]
TreeNode* node_v_utilizedstates;
#define v_utilizedstates node_v_utilizedstates->safedatafloat()[0]
TreeNode* node_v_data;
TreeNode* node_v_basedata;
TreeNode* node_v_colordata;
TreeNode* node_v_validdata;
#define v_validdata node_v_validdata->safedatafloat()[0]
TreeNode* node_v_useprofilenr;
#define v_useprofilenr node_v_useprofilenr->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual double onRunWarm();

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode  view);

FS_CONTENT_DLL_FUNC virtual double onListen(treenode listenedto, treenode listenercoupling, int listenercode, int ecode, treenode involved, char* edata);

FS_CONTENT_DLL_FUNC virtual double hasAbility(int ability);

FS_CONTENT_DLL_FUNC virtual double drawGraph(treenode view);

FS_CONTENT_DLL_FUNC virtual double getAggregationType();

FS_CONTENT_DLL_FUNC virtual double enumerateAggregationList(treenode from);

FS_CONTENT_DLL_FUNC virtual double aggregateData(treenode destNode, treenode statNode, treenode pfm);

FS_CONTENT_DLL_FUNC virtual double getData(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOnlineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOfflineDependencies(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineInitializer(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineData(treenode from, treenode repDataNode);

FS_CONTENT_DLL_FUNC virtual double createCSV(char* filePath);

FS_CONTENT_DLL_FUNC int initalizeObjects();

FS_CONTENT_DLL_FUNC int getMaxGroupNameWidth();

FS_CONTENT_DLL_FUNC int getMaxObjectNameWidth();

FS_CONTENT_DLL_FUNC int initializeObjectMember(treenode membernode);

FS_CONTENT_DLL_FUNC treenode getNextMemberNode(treenode membernode);

FS_CONTENT_DLL_FUNC int updateAllCurStates();

FS_CONTENT_DLL_FUNC int updateCurState(treenode membernode, int entrynr);

FS_CONTENT_DLL_FUNC int updateCurStateString(treenode membernode, int entrynr);

FS_CONTENT_DLL_FUNC int updateStates();

FS_CONTENT_DLL_FUNC int updateAllStates(treenode membernode, int entrynr, int onreset);

FS_CONTENT_DLL_FUNC int saveBaseStates(treenode membernode, int entrynr);

FS_CONTENT_DLL_FUNC int filterAllByTime(treenode view);

FS_CONTENT_DLL_FUNC int filterByTime(treenode membernode);

FS_CONTENT_DLL_FUNC int unfilterAll(treenode graph);

FS_CONTENT_DLL_FUNC double getTotalTime();

FS_CONTENT_DLL_FUNC double setProperties(treenode view);

FS_CONTENT_DLL_FUNC int applyProperties(treenode graph);

FS_CONTENT_DLL_FUNC treenode refreshUtilizedStates();

FS_CONTENT_DLL_FUNC treenode onChangeObjectSet();

FS_CONTENT_DLL_FUNC int countNrInGroup(treenode objnode);

FS_CONTENT_DLL_FUNC treenode getMember(int nr);

FS_CONTENT_DLL_FUNC treenode getMember(treenode memberNode);

FS_CONTENT_DLL_FUNC virtual treenode addMember(treenode newObj);

FS_CONTENT_DLL_FUNC treenode addGroup(int groupRank);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// StatChart
class StatChart : public StatisticObject
{
public:

TreeNode* node_v_objects;
#define v_objects node_v_objects->safedatafloat()[0]
TreeNode* node_v_colors;
#define v_colors node_v_colors->safedatafloat()[0]
TreeNode* node_v_charttype;
#define v_charttype node_v_charttype->safedatafloat()[0]
TreeNode* node_v_usecollecttime;
#define v_usecollecttime node_v_usecollecttime->safedatafloat()[0]
TreeNode* node_v_mincollecttime;
#define v_mincollecttime node_v_mincollecttime->safedatafloat()[0]
TreeNode* node_v_maxcollecttime;
#define v_maxcollecttime node_v_maxcollecttime->safedatafloat()[0]
TreeNode* node_v_collecthistory;
#define v_collecthistory node_v_collecthistory->safedatafloat()[0]
TreeNode* node_v_filtermintime;
#define v_filtermintime node_v_filtermintime->safedatafloat()[0]
TreeNode* node_v_filtermaxtime;
#define v_filtermaxtime node_v_filtermaxtime->safedatafloat()[0]
TreeNode* node_v_filterednow;
#define v_filterednow node_v_filterednow->safedatafloat()[0]
TreeNode* node_v_timeinterval;
#define v_timeinterval node_v_timeinterval->safedatafloat()[0]
TreeNode* node_v_showlegend;
#define v_showlegend node_v_showlegend->safedatafloat()[0]
TreeNode* node_v_fontsize;
#define v_fontsize node_v_fontsize->safedatafloat()[0]
TreeNode* node_v_barsize;
#define v_barsize node_v_barsize->safedatafloat()[0]
TreeNode* node_v_precision;
#define v_precision node_v_precision->safedatafloat()[0]
TreeNode* node_v_stacked;
#define v_stacked node_v_stacked->safedatafloat()[0]
TreeNode* node_v_statistics;
#define v_statistics node_v_statistics->safedatafloat()[0]
TreeNode* node_v_data;
TreeNode* node_v_basedata;
TreeNode* node_v_timedata;
TreeNode* node_v_colordata;
TreeNode* node_v_validdata;
#define v_validdata node_v_validdata->safedatafloat()[0]
TreeNode* node_v_useprofilenr;
#define v_useprofilenr node_v_useprofilenr->safedatafloat()[0]
TreeNode* node_v_generallisten;
#define v_generallisten node_v_generallisten->safedatafloat()[0]
TreeNode* node_v_aggregatelisten;
#define v_aggregatelisten node_v_aggregatelisten->safedatafloat()[0]
TreeNode* node_v_systemwarmuptime;
#define v_systemwarmuptime node_v_systemwarmuptime->safedatafloat()[0]
TreeNode* node_v_timescale;
#define v_timescale node_v_timescale->safedatafloat()[0]
TreeNode* node_v_xaxistitle;
TreeNode* node_v_yaxistitle;

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual double onRunWarm();

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode  view);

FS_CONTENT_DLL_FUNC virtual double onListen(treenode listenedto, treenode listenercoupling, int listenercode, int ecode, treenode involved, char* edata);

FS_CONTENT_DLL_FUNC virtual double hasAbility(int ability);

FS_CONTENT_DLL_FUNC virtual double drawGraph(treenode view);

FS_CONTENT_DLL_FUNC virtual double getAggregationType();

FS_CONTENT_DLL_FUNC virtual double enumerateAggregationList(treenode from);

FS_CONTENT_DLL_FUNC virtual double aggregateData(treenode destNode, treenode statNode, treenode pfm);

FS_CONTENT_DLL_FUNC virtual double getData(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOnlineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOfflineDependencies(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineInitializer(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineData(treenode from, treenode repDataNode);

FS_CONTENT_DLL_FUNC virtual double createCSV(char* filePath);

FS_CONTENT_DLL_FUNC int initializeObjects();

FS_CONTENT_DLL_FUNC int getMaxGroupNameWidth();

FS_CONTENT_DLL_FUNC int getMaxObjectNameWidth();

FS_CONTENT_DLL_FUNC int initializeObjectMember(treenode membernode, treenode bundlenode, int listen DEFAULTZERO);

FS_CONTENT_DLL_FUNC int initializeAggregateMember(treenode groupnode);

FS_CONTENT_DLL_FUNC treenode getNextMemberNode(treenode membernode);

FS_CONTENT_DLL_FUNC int updateAllStats();

FS_CONTENT_DLL_FUNC int updateMemberStats(treenode membernode, int entrynr);

FS_CONTENT_DLL_FUNC double updateTimeStats();

FS_CONTENT_DLL_FUNC double calculateAvgContent(treenode obj, treenode statnode, int savingbase DEFAULTZERO);

FS_CONTENT_DLL_FUNC double calculateAvgStayTime(treenode obj, treenode statnode);

FS_CONTENT_DLL_FUNC int saveBaseStats(treenode membernode, int entrynr);

FS_CONTENT_DLL_FUNC int filterAllByTime(treenode view);

FS_CONTENT_DLL_FUNC int filterByTime(treenode membernode, int entrynr);

FS_CONTENT_DLL_FUNC int unfilterAll(treenode graph);

FS_CONTENT_DLL_FUNC double getTotalTime();

FS_CONTENT_DLL_FUNC double setProperties(treenode view);

FS_CONTENT_DLL_FUNC int applyProperties(treenode graph);

FS_CONTENT_DLL_FUNC treenode onChangeObjectSet();

FS_CONTENT_DLL_FUNC int countNrInGroup(treenode objnode);

FS_CONTENT_DLL_FUNC treenode getMember(int nr);

FS_CONTENT_DLL_FUNC treenode getMember(treenode memberNode);

FS_CONTENT_DLL_FUNC virtual treenode addMember(treenode newObj);

FS_CONTENT_DLL_FUNC treenode addGroup(int groupRank);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// CustomChart
class CustomChart : public StatisticObject
{
public:

TreeNode* node_v_associations;
#define v_associations node_v_associations->safedatafloat()[0]
TreeNode* node_v_colors;
#define v_colors node_v_colors->safedatafloat()[0]
TreeNode* node_v_charttype;
#define v_charttype node_v_charttype->safedatafloat()[0]
TreeNode* node_v_numcategories;
TreeNode* node_v_categorytitle;
TreeNode* node_v_numseries;
TreeNode* node_v_seriestitle;
TreeNode* node_v_datapointvalue;
TreeNode* node_v_usecollecttime;
#define v_usecollecttime node_v_usecollecttime->safedatafloat()[0]
TreeNode* node_v_mincollecttime;
#define v_mincollecttime node_v_mincollecttime->safedatafloat()[0]
TreeNode* node_v_maxcollecttime;
#define v_maxcollecttime node_v_maxcollecttime->safedatafloat()[0]
TreeNode* node_v_collecthistory;
#define v_collecthistory node_v_collecthistory->safedatafloat()[0]
TreeNode* node_v_timeinterval;
#define v_timeinterval node_v_timeinterval->safedatafloat()[0]
TreeNode* node_v_showlegend;
#define v_showlegend node_v_showlegend->safedatafloat()[0]
TreeNode* node_v_fontsize;
#define v_fontsize node_v_fontsize->safedatafloat()[0]
TreeNode* node_v_barsize;
#define v_barsize node_v_barsize->safedatafloat()[0]
TreeNode* node_v_precision;
#define v_precision node_v_precision->safedatafloat()[0]
TreeNode* node_v_stacked;
#define v_stacked node_v_stacked->safedatafloat()[0]
TreeNode* node_v_reloadbundle;
#define v_reloadbundle node_v_reloadbundle->safedatafloat()[0]
TreeNode* node_v_data;
TreeNode* node_v_timedata;
TreeNode* node_v_colordata;
TreeNode* node_v_validdata;
#define v_validdata node_v_validdata->safedatafloat()[0]
TreeNode* node_v_systemwarmuptime;
#define v_systemwarmuptime node_v_systemwarmuptime->safedatafloat()[0]
TreeNode* node_v_timescale;
#define v_timescale node_v_timescale->safedatafloat()[0]
TreeNode* node_v_xaxistitle;
TreeNode* node_v_yaxistitle;

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual double onRunWarm();

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode  view);

FS_CONTENT_DLL_FUNC virtual double onListen(treenode listenedto, treenode listenercoupling, int listenercode, int ecode, treenode involved, char* edata);

FS_CONTENT_DLL_FUNC virtual double hasAbility(int ability);

FS_CONTENT_DLL_FUNC virtual double drawGraph(treenode view);

FS_CONTENT_DLL_FUNC virtual double getAggregationType();

FS_CONTENT_DLL_FUNC virtual double enumerateAggregationList(treenode from);

FS_CONTENT_DLL_FUNC virtual double aggregateData(treenode destNode, treenode statNode, treenode pfm);

FS_CONTENT_DLL_FUNC virtual double getData(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOnlineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOfflineDependencies(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineInitializer(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineData(treenode from, treenode repDataNode);

FS_CONTENT_DLL_FUNC virtual double createCSV(char* filePath);

FS_CONTENT_DLL_FUNC int getMaxObjectNameWidth();

FS_CONTENT_DLL_FUNC int initializeAggregateMember(treenode groupnode);

FS_CONTENT_DLL_FUNC treenode getNextMemberNode(treenode membernode);

FS_CONTENT_DLL_FUNC int updateAllStats();

FS_CONTENT_DLL_FUNC double updateTimeStats();

FS_CONTENT_DLL_FUNC double getTotalTime();

FS_CONTENT_DLL_FUNC double setProperties(treenode view);

FS_CONTENT_DLL_FUNC int applyProperties(treenode graph);

FS_CONTENT_DLL_FUNC treenode onChangeAssociationSet();

FS_CONTENT_DLL_FUNC treenode getMember(int nr);

FS_CONTENT_DLL_FUNC treenode getMember(treenode memberNode);

FS_CONTENT_DLL_FUNC virtual treenode addMember(treenode newNode);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// GanttChart
class GanttChart : public StatisticObject
{
public:

TreeNode* node_v_objects;
#define v_objects node_v_objects->safedatafloat()[0]
TreeNode* node_v_colors;
#define v_colors node_v_colors->safedatafloat()[0]
TreeNode* node_v_charttype;
#define v_charttype node_v_charttype->safedatafloat()[0]
TreeNode* node_v_tracerequirementtrigger;
TreeNode* node_v_itemnametrigger;
TreeNode* node_v_usecollecttime;
#define v_usecollecttime node_v_usecollecttime->safedatafloat()[0]
TreeNode* node_v_mincollecttime;
#define v_mincollecttime node_v_mincollecttime->safedatafloat()[0]
TreeNode* node_v_maxcollecttime;
#define v_maxcollecttime node_v_maxcollecttime->safedatafloat()[0]
TreeNode* node_v_showlegend;
#define v_showlegend node_v_showlegend->safedatafloat()[0]
TreeNode* node_v_fontsize;
#define v_fontsize node_v_fontsize->safedatafloat()[0]
TreeNode* node_v_barsize;
#define v_barsize node_v_barsize->safedatafloat()[0]
TreeNode* node_v_itemtrace;
#define v_itemtrace node_v_itemtrace->safedatafloat()[0]
TreeNode* node_v_timescale;
#define v_timescale node_v_timescale->safedatafloat()[0]
TreeNode* node_v_xaxistitle;
TreeNode* node_v_reloadbundles;
#define v_reloadbundles node_v_reloadbundles->safedatafloat()[0]
TreeNode* node_v_newtime;
#define v_newtime node_v_newtime->safedatafloat()[0]
TreeNode* node_v_includedstates;
#define v_includedstates node_v_includedstates->safedatafloat()[0]
TreeNode* node_v_series;
TreeNode* node_v_entrylegend;
TreeNode* node_v_data;
TreeNode* node_v_colordata;
TreeNode* node_v_validdata;
#define v_validdata node_v_validdata->safedatafloat()[0]
TreeNode* node_v_useprofilenr;
#define v_useprofilenr node_v_useprofilenr->safedatafloat()[0]
TreeNode* node_v_wrap;
#define v_wrap node_v_wrap->safedatafloat()[0]
TreeNode* node_v_wraptime;
#define v_wraptime node_v_wraptime->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual double onRunWarm();

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode  view);

FS_CONTENT_DLL_FUNC virtual double onListen(treenode listenedto, treenode listenercoupling, int listenercode, int ecode, treenode involved, char* edata);

FS_CONTENT_DLL_FUNC int getLastEntryNum(int series);

FS_CONTENT_DLL_FUNC virtual double hasAbility(int ability);

FS_CONTENT_DLL_FUNC virtual double drawGraph(treenode view);

FS_CONTENT_DLL_FUNC virtual double getAggregationType();

FS_CONTENT_DLL_FUNC virtual double enumerateAggregationList(treenode from);

FS_CONTENT_DLL_FUNC virtual double aggregateData(treenode destNode, treenode statNode, treenode pfm);

FS_CONTENT_DLL_FUNC virtual double getData(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOnlineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOfflineDependencies(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineInitializer(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineData(treenode from, treenode repDataNode);

FS_CONTENT_DLL_FUNC virtual double createCSV(char* filePath);

FS_CONTENT_DLL_FUNC int initalizeObjects();

FS_CONTENT_DLL_FUNC int getMaxObjectNameWidth();

FS_CONTENT_DLL_FUNC int initializeObjectMember(treenode membernode);

FS_CONTENT_DLL_FUNC treenode getNextMemberNode(treenode membernode);

FS_CONTENT_DLL_FUNC double updateCurrentStates();

FS_CONTENT_DLL_FUNC double getTotalTime();

FS_CONTENT_DLL_FUNC double setProperties(treenode view);

FS_CONTENT_DLL_FUNC int applyProperties(treenode graph);

FS_CONTENT_DLL_FUNC treenode refreshStates();

FS_CONTENT_DLL_FUNC virtual treenode onChangeObjectSet();

FS_CONTENT_DLL_FUNC treenode getMember(int nr);

FS_CONTENT_DLL_FUNC treenode getMember(treenode memberNode);

FS_CONTENT_DLL_FUNC virtual treenode addMember(treenode newObj);

FS_CONTENT_DLL_FUNC treenode addGroup(int groupRank);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// CustomGanttChart
class CustomGanttChart : public GanttChart
{
public:

TreeNode* node_v_associations;
#define v_associations node_v_associations->safedatafloat()[0]
TreeNode* node_v_lockmodeltime;
#define v_lockmodeltime node_v_lockmodeltime->safedatafloat()[0]
TreeNode* node_v_chartendtime;
#define v_chartendtime node_v_chartendtime->safedatafloat()[0]
TreeNode* node_v_ordered;
#define v_ordered node_v_ordered->safedatafloat()[0]
TreeNode* node_v_numseries;
TreeNode* node_v_seriestitle;
TreeNode* node_v_seriesspan;
TreeNode* node_v_numentries;
TreeNode* node_v_starttime;
TreeNode* node_v_endtime;
TreeNode* node_v_legend;
TreeNode* node_v_legendtitle;
TreeNode* node_v_legendshow;
TreeNode* node_v_clickcallback;
TreeNode* node_v_spanbarsize;
#define v_spanbarsize node_v_spanbarsize->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onRunWarm();

FS_CONTENT_DLL_FUNC virtual double drawGraph(treenode view);

FS_CONTENT_DLL_FUNC double updateOrderedStats();

FS_CONTENT_DLL_FUNC double updateUnorderedStats();

FS_CONTENT_DLL_FUNC virtual double getOfflineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC double setProperties(treenode view);

FS_CONTENT_DLL_FUNC int applyProperties(treenode graph);

FS_CONTENT_DLL_FUNC treenode onChangeAssociationSet();

FS_CONTENT_DLL_FUNC treenode getMember(treenode memberNode);

FS_CONTENT_DLL_FUNC virtual treenode addMember(treenode newNode);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// TrackedVariableChart
class TrackedVariableChart : public StatisticObject
{
public:

TreeNode* node_v_trackedvariables;
#define v_trackedvariables node_v_trackedvariables->safedatafloat()[0]
TreeNode* node_v_colors;
#define v_colors node_v_colors->safedatafloat()[0]
TreeNode* node_v_charttype;
#define v_charttype node_v_charttype->safedatafloat()[0]
TreeNode* node_v_showlegend;
#define v_showlegend node_v_showlegend->safedatafloat()[0]
TreeNode* node_v_nrbuckets;
#define v_nrbuckets node_v_nrbuckets->safedatafloat()[0]
TreeNode* node_v_normalize;
#define v_normalize node_v_normalize->safedatafloat()[0]
TreeNode* node_v_colordata;
TreeNode* node_v_timescale;
#define v_timescale node_v_timescale->safedatafloat()[0]
TreeNode* node_v_xaxistitle;
TreeNode* node_v_yaxistitle;

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double hasAbility(int ability);

FS_CONTENT_DLL_FUNC virtual double drawGraph(treenode view);

FS_CONTENT_DLL_FUNC virtual double getAggregationType();

FS_CONTENT_DLL_FUNC virtual double enumerateAggregationList(treenode from);

FS_CONTENT_DLL_FUNC virtual double aggregateData(treenode destNode, treenode statNode, treenode pfm);

FS_CONTENT_DLL_FUNC virtual double getData(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOnlineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOfflineInitializer(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineDependencies(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineData(treenode from, treenode repDataNode);

FS_CONTENT_DLL_FUNC virtual double createCSV(char* filePath);

FS_CONTENT_DLL_FUNC double setProperties(treenode view);

FS_CONTENT_DLL_FUNC int applyProperties(treenode graph);

FS_CONTENT_DLL_FUNC double initializeData(treenode view);

FS_CONTENT_DLL_FUNC double updateData(treenode view);

FS_CONTENT_DLL_FUNC virtual treenode addMember(treenode newNode);

FS_CONTENT_DLL_FUNC treenode addMember(treenode object, const Variant& stat);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// HtmlStatistic
class HtmlStatistic : public StatisticObject
{
public:

TreeNode* node_v_userhtml;
TreeNode* node_v_userheader;
TreeNode* node_v_hasdynamicflexscript;
#define v_hasdynamicflexscript node_v_hasdynamicflexscript->safedatafloat()[0]
TreeNode* node_v_flexscriptprocessor;
TreeNode* node_v_elementid;

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double drawGraph(treenode view);

FS_CONTENT_DLL_FUNC virtual double getOfflineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOnlineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC double parseUserHtml();

FS_CONTENT_DLL_FUNC double dumpHtml(treenode toNode, int replace);

FS_CONTENT_DLL_FUNC  HtmlStatistic();

FS_CONTENT_DLL_FUNC  ~HtmlStatistic();


// c++ attributes
HWND console;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FinancialAnalysis
class FinancialAnalysis : public StatisticObject
{
public:

TreeNode* node_v_objects;
#define v_objects node_v_objects->safedatafloat()[0]
TreeNode* node_v_charttype;
#define v_charttype node_v_charttype->safedatafloat()[0]
TreeNode* node_v_currency;
TreeNode* node_v_precision;
#define v_precision node_v_precision->safedatafloat()[0]
TreeNode* node_v_fontsize;
#define v_fontsize node_v_fontsize->safedatafloat()[0]
TreeNode* node_v_usecollecttime;
#define v_usecollecttime node_v_usecollecttime->safedatafloat()[0]
TreeNode* node_v_mincollecttime;
#define v_mincollecttime node_v_mincollecttime->safedatafloat()[0]
TreeNode* node_v_maxcollecttime;
#define v_maxcollecttime node_v_maxcollecttime->safedatafloat()[0]
TreeNode* node_v_data;
TreeNode* node_v_displaydata;
TreeNode* node_v_validdata;
#define v_validdata node_v_validdata->safedatafloat()[0]
TreeNode* node_v_reset;
#define v_reset node_v_reset->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual double onRunWarm();

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode  view);

FS_CONTENT_DLL_FUNC virtual double onListen(treenode listenedto, treenode listenercoupling, int listenercode, int ecode, treenode involved, char* edata);

FS_CONTENT_DLL_FUNC virtual double hasAbility(int ability);

FS_CONTENT_DLL_FUNC virtual double drawGraph(treenode view);

FS_CONTENT_DLL_FUNC virtual double getAggregationType();

FS_CONTENT_DLL_FUNC virtual double enumerateAggregationList(treenode from);

FS_CONTENT_DLL_FUNC virtual double aggregateData(treenode destNode, treenode statNode, treenode pfm);

FS_CONTENT_DLL_FUNC virtual double getData(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOnlineHtml(treenode destNode, int chartNum);

FS_CONTENT_DLL_FUNC virtual double getOfflineDependencies(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineInitializer(treenode destNode);

FS_CONTENT_DLL_FUNC virtual double getOfflineData(treenode from, treenode repDataNode);

FS_CONTENT_DLL_FUNC virtual double createCSV(char* filePath);

FS_CONTENT_DLL_FUNC int initalizeObjects();

FS_CONTENT_DLL_FUNC treenode getNextMemberNode(treenode membernode);

FS_CONTENT_DLL_FUNC int getMaxObjectNameWidth();

FS_CONTENT_DLL_FUNC int initializeObjectMember(treenode membernode);

FS_CONTENT_DLL_FUNC int updateAllStats();

FS_CONTENT_DLL_FUNC double updateMemberStats(treenode membernode, double totalTime, int entrynr);

FS_CONTENT_DLL_FUNC double updateTotals();

FS_CONTENT_DLL_FUNC double getTotalTime();

FS_CONTENT_DLL_FUNC int isGroup(treenode membernode);

FS_CONTENT_DLL_FUNC double setProperties(treenode view);

FS_CONTENT_DLL_FUNC int applyProperties(treenode graph);

FS_CONTENT_DLL_FUNC treenode onChangeObjectSet();

FS_CONTENT_DLL_FUNC treenode getMember(int nr);

FS_CONTENT_DLL_FUNC treenode getMember(treenode memberNode);

FS_CONTENT_DLL_FUNC virtual treenode addMember(treenode newObj);

FS_CONTENT_DLL_FUNC treenode addGroup(int groupRank);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Source
class Source : public FixedResource
{
public:

TreeNode* node_v_arrivalmode;
#define v_arrivalmode node_v_arrivalmode->safedatafloat()[0]
TreeNode* node_v_interarrivaltime;
TreeNode* node_v_timezerocreate;
#define v_timezerocreate node_v_timezerocreate->safedatafloat()[0]
TreeNode* node_v_interarrivalitemtype;
#define v_interarrivalitemtype node_v_interarrivalitemtype->safedatafloat()[0]
TreeNode* node_v_itemclass;
#define v_itemclass node_v_itemclass->safedatafloat()[0]
TreeNode* node_v_schedule;
#define v_schedule node_v_schedule->safedatafloat()[0]
TreeNode* node_v_repeat;
#define v_repeat node_v_repeat->safedatafloat()[0]
TreeNode* node_v_sequence;
#define v_sequence node_v_sequence->safedatafloat()[0]
TreeNode* node_v_sequencecurrow;
#define v_sequencecurrow node_v_sequencecurrow->safedatafloat()[0]
TreeNode* node_v_creationtrigger;
TreeNode* node_v_flowitembin;
#define v_flowitembin node_v_flowitembin->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double generateItem(double curitemtype, const string& itemname, double rownumber);

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// c++ attributes
treenode flowitemtocreate;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Queue
class Queue : public FixedResource
{
public:

TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]
TreeNode* node_v_usebatching;
#define v_usebatching node_v_usebatching->safedatafloat()[0]
TreeNode* node_v_batchsize;
#define v_batchsize node_v_batchsize->safedatafloat()[0]
TreeNode* node_v_maxwaittime;
#define v_maxwaittime node_v_maxwaittime->safedatafloat()[0]
TreeNode* node_v_flush;
#define v_flush node_v_flush->safedatafloat()[0]
TreeNode* node_v_currentbatchsize;
#define v_currentbatchsize node_v_currentbatchsize->safedatafloat()[0]
TreeNode* node_v_endcollectingtrigger;
TreeNode* node_v_placemode;
#define v_placemode node_v_placemode->safedatafloat()[0]
TreeNode* node_v_stackinitz;
#define v_stackinitz node_v_stackinitz->safedatafloat()[0]
TreeNode* node_v_curxfringe;
#define v_curxfringe node_v_curxfringe->safedatafloat()[0]
TreeNode* node_v_curyloc;
#define v_curyloc node_v_curyloc->safedatafloat()[0]
TreeNode* node_v_curmaxysize;
#define v_curmaxysize node_v_curmaxysize->safedatafloat()[0]
TreeNode* node_v_curzloc;
#define v_curzloc node_v_curzloc->safedatafloat()[0]
TreeNode* node_v_curmaxzsize;
#define v_curmaxzsize node_v_curmaxzsize->safedatafloat()[0]
TreeNode* node_v_productspacing;
#define v_productspacing node_v_productspacing->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC  Queue();

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onTransportInNotify(treenode item, int port);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double getPlaceOffset(treenode involvedobj, treenode fromobject,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual double getPickOffset(treenode involvedobj, treenode toobject, double* returnarray);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double setLocations(int uptorank);

FS_CONTENT_DLL_FUNC virtual double checkReceiveItem();

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// c++ attributes
int lastpredrawoutput;

int lastpredrawinput;

bool blockRecursiveReceive;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Processor
class Processor : public FixedResource
{
public:

TreeNode* node_v_cycletime;
TreeNode* node_v_setuptime;
TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]
TreeNode* node_v_useprocessoperators;
#define v_useprocessoperators node_v_useprocessoperators->safedatafloat()[0]
TreeNode* node_v_usesetupoperators;
#define v_usesetupoperators node_v_usesetupoperators->safedatafloat()[0]
TreeNode* node_v_nrofprocessoperators;
#define v_nrofprocessoperators node_v_nrofprocessoperators->safedatafloat()[0]
TreeNode* node_v_processoperatorpriority;
#define v_processoperatorpriority node_v_processoperatorpriority->safedatafloat()[0]
TreeNode* node_v_preemptprocessoperators;
#define v_preemptprocessoperators node_v_preemptprocessoperators->safedatafloat()[0]
TreeNode* node_v_processdispatcher;
TreeNode* node_v_setupfinishtrigger;
TreeNode* node_v_processfinishtrigger;
TreeNode* node_v_mtbf;
TreeNode* node_v_breakdowntrigger;
TreeNode* node_v_mttr;
TreeNode* node_v_repairtrigger;
TreeNode* node_v_usedownoperators;
#define v_usedownoperators node_v_usedownoperators->safedatafloat()[0]
TreeNode* node_v_nrofdownoperators;
#define v_nrofdownoperators node_v_nrofdownoperators->safedatafloat()[0]
TreeNode* node_v_downoperatorpriority;
#define v_downoperatorpriority node_v_downoperatorpriority->safedatafloat()[0]
TreeNode* node_v_preemptdownoperators;
#define v_preemptdownoperators node_v_preemptdownoperators->safedatafloat()[0]
TreeNode* node_v_downdispatcher;
TreeNode* node_v_curdowndispatcher;
#define v_curdowndispatcher node_v_curdowndispatcher->safedatafloat()[0]
TreeNode* node_v_nextdown;
#define v_nextdown node_v_nextdown->safedatafloat()[0]
TreeNode* node_v_convey;
#define v_convey node_v_convey->safedatafloat()[0]
TreeNode* node_v_nextrepairtime;
#define v_nextrepairtime node_v_nextrepairtime->safedatafloat()[0]
TreeNode* node_v_usesameop;
#define v_usesameop node_v_usesameop->safedatafloat()[0]
TreeNode* node_v_nrofsetupoperators;
#define v_nrofsetupoperators node_v_nrofsetupoperators->safedatafloat()[0]
TreeNode* node_v_processingdownflag;
#define v_processingdownflag node_v_processingdownflag->safedatafloat()[0]
TreeNode* node_v_mtbfstates;
#define v_mtbfstates node_v_mtbfstates->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC  Processor();

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double onTransportInNotify(treenode item, int port);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject();

FS_CONTENT_DLL_FUNC virtual double callProcessOperators( treenode item, int trigger);

FS_CONTENT_DLL_FUNC virtual double releaseProcessOperators( treenode item);

FS_CONTENT_DLL_FUNC virtual double processorEvents(double code, treenode involved, char * datastr);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC double checkSetupOpCall( treenode item, double cursetuptime);

FS_CONTENT_DLL_FUNC double checkProcessOpCall(treenode item, double curcycletime);

FS_CONTENT_DLL_FUNC double checkSetupOpFree(treenode item);

FS_CONTENT_DLL_FUNC double checkProcessOpFree(treenode item);

FS_CONTENT_DLL_FUNC virtual double startSetupTime(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// c++ attributes
bool blockRecursiveReceive;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Sink
class Sink : public FixedResource
{
public:

TreeNode* node_v_recycle;
#define v_recycle node_v_recycle->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double onTransportInNotify(treenode item, int portnumber);

FS_CONTENT_DLL_FUNC virtual double updateLocations();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Combiner
class Combiner : public Processor
{
public:

TreeNode* node_v_collectingcontainer;
#define v_collectingcontainer node_v_collectingcontainer->safedatafloat()[0]
TreeNode* node_v_componentlist;
#define v_componentlist node_v_componentlist->safedatafloat()[0]
TreeNode* node_v_currentcomponentsum;
#define v_currentcomponentsum node_v_currentcomponentsum->safedatafloat()[0]
TreeNode* node_v_targetcomponentsum;
#define v_targetcomponentsum node_v_targetcomponentsum->safedatafloat()[0]
TreeNode* node_v_pack;
#define v_pack node_v_pack->safedatafloat()[0]
TreeNode* node_v_overriddenreceivefromport;
TreeNode* node_v_overriddenpullrequirement;
TreeNode* node_v_recycle;
#define v_recycle node_v_recycle->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC  Combiner();

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onClick(treenode view, int code);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double generateCompList();

FS_CONTENT_DLL_FUNC double receiveItem();

FS_CONTENT_DLL_FUNC virtual double onTransportInNotify(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onTransportInComplete(treenode item, int port, treenode transporter DEFAULTNULL);

FS_CONTENT_DLL_FUNC virtual double getPlaceOffset(treenode involvedobj, treenode fromobject,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual double updateVersion(char* newversion, char* oldversion);

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);


// c++ attributes
bool blockRecursiveReceive;

bool internalMove;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Separator
class Separator : public Processor
{
public:

TreeNode* node_v_unpack;
#define v_unpack node_v_unpack->safedatafloat()[0]
TreeNode* node_v_splitquantity;
TreeNode* node_v_overriddensendtoport;
TreeNode* node_v_recycle;
#define v_recycle node_v_recycle->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onTransportInNotify(treenode item, int port);


// c++ attributes
bool movingItemsNow = false;;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// MultiProcessor
class MultiProcessor : public FixedResource
{
public:

TreeNode* node_v_optable;
#define v_optable node_v_optable->safedatafloat()[0]
TreeNode* node_v_nrofprocesses;
#define v_nrofprocesses node_v_nrofprocesses->safedatafloat()[0]
TreeNode* node_v_curdispatcher;
#define v_curdispatcher node_v_curdispatcher->safedatafloat()[0]
TreeNode* node_v_processfinishtrigger;
TreeNode* node_v_nrofdownoperators;
#define v_nrofdownoperators node_v_nrofdownoperators->safedatafloat()[0]
TreeNode* node_v_downdispatcher;
TreeNode* node_v_downoppriority;
#define v_downoppriority node_v_downoppriority->safedatafloat()[0]
TreeNode* node_v_downoppreempt;
#define v_downoppreempt node_v_downoppreempt->safedatafloat()[0]
TreeNode* node_v_mtbf;
TreeNode* node_v_mttr;
TreeNode* node_v_breakdowntrigger;
TreeNode* node_v_repairtrigger;
TreeNode* node_v_nextdown;
#define v_nextdown node_v_nextdown->safedatafloat()[0]
TreeNode* node_v_nextrepair;
#define v_nextrepair node_v_nextrepair->safedatafloat()[0]
TreeNode* node_v_convey;
#define v_convey node_v_convey->safedatafloat()[0]
TreeNode* node_v_nonestate;
#define v_nonestate node_v_nonestate->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Rack
class Rack : public FixedResource
{
public:

TreeNode* node_v_placeinbay;
TreeNode* node_v_placeinlevel;
TreeNode* node_v_minimumstaytime;
TreeNode* node_v_enddwelltimetrigger;
TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]
TreeNode* node_v_contenttable;
#define v_contenttable node_v_contenttable->safedatafloat()[0]
TreeNode* node_v_locationtable;
#define v_locationtable node_v_locationtable->safedatafloat()[0]
TreeNode* node_v_sizetable;
#define v_sizetable node_v_sizetable->safedatafloat()[0]
TreeNode* node_v_rackdrawmode;
#define v_rackdrawmode node_v_rackdrawmode->safedatafloat()[0]
TreeNode* node_v_pickplaceyoffset;
#define v_pickplaceyoffset node_v_pickplaceyoffset->safedatafloat()[0]
TreeNode* node_v_tiltvalue;
#define v_tiltvalue node_v_tiltvalue->safedatafloat()[0]
TreeNode* node_v_tiltangle;
#define v_tiltangle node_v_tiltangle->safedatafloat()[0]
TreeNode* node_v_markreadytogo;
#define v_markreadytogo node_v_markreadytogo->safedatafloat()[0]
TreeNode* node_v_floorstorage;
#define v_floorstorage node_v_floorstorage->safedatafloat()[0]
TreeNode* node_v_opacity;
#define v_opacity node_v_opacity->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC  Rack();

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onKeyedClick(treenode view, int code, char key);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double getPickOffset(treenode item, treenode toobject, double* returnarray);

FS_CONTENT_DLL_FUNC virtual double getPlaceOffset(treenode item, treenode fromobject,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual void assertCellAssignment(treenode item, int& bay, int& level);

FS_CONTENT_DLL_FUNC virtual int assignBay(treenode item);

FS_CONTENT_DLL_FUNC virtual int assignLevel(treenode item, int bay);

FS_CONTENT_DLL_FUNC virtual double onTransportInNotify(treenode item, int portnumber);

FS_CONTENT_DLL_FUNC double getBayXCenter(double baynumber);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC double getBayOfItem(treenode item);

FS_CONTENT_DLL_FUNC double getBayLoc(int bay);

FS_CONTENT_DLL_FUNC double getBaySize(int bay);

FS_CONTENT_DLL_FUNC double getItemCellRank(treenode item);

FS_CONTENT_DLL_FUNC double getLevelOfItem(treenode item);

FS_CONTENT_DLL_FUNC double getLevelLoc(int bay, int level);

FS_CONTENT_DLL_FUNC double getLevelSize(int bay, int level);

FS_CONTENT_DLL_FUNC treenode getItemByBayLevel(int bay, int level, int rankincell DEFAULTONE);

FS_CONTENT_DLL_FUNC double getBayContent(int bay);

FS_CONTENT_DLL_FUNC double getCellContent(int bay, int level);

FS_CONTENT_DLL_FUNC double getNrOfBays();

FS_CONTENT_DLL_FUNC double getNrOfLevels(int bay DEFAULTONE);

FS_CONTENT_DLL_FUNC double getCellVar(int bay, int level, int varnum, treenode storedlabel DEFAULTNULL);

FS_CONTENT_DLL_FUNC double setCellVar(int bay, int level, int varnum, double value, treenode storedlabel DEFAULTNULL);

FS_CONTENT_DLL_FUNC virtual double drawFilledCell(int bay, int level, double x, double y, double z, double sx, double sy, double sz, int red, int green, int blue, int glbeginend DEFAULTONE);

FS_CONTENT_DLL_FUNC double recycleItem(treenode item, int binrank);

FS_CONTENT_DLL_FUNC treenode  restoreItem(int binrank, int bay, int level, int position);

FS_CONTENT_DLL_FUNC double setCellContent(int bay, int level, int contentval);

FS_CONTENT_DLL_FUNC virtual double addItemToContentTable(treenode item, int bay, int level);

FS_CONTENT_DLL_FUNC virtual double removeItemFromContentTable(treenode item);

FS_CONTENT_DLL_FUNC virtual double setItemEntryLocation(treenode item, treenode tablecell, int bay, int level, int position);

FS_CONTENT_DLL_FUNC virtual double drawVirtualContent(double bayfillperc, double levelfillperc, double itemdepth, double red, double green, double blue, int onlyvirtual DEFAULTONE);

FS_CONTENT_DLL_FUNC double saveState();

FS_CONTENT_DLL_FUNC double loadState();

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);

FS_CONTENT_DLL_FUNC double buildMeshes();

FS_CONTENT_DLL_FUNC double buildFullMeshes();

FS_CONTENT_DLL_FUNC double buildFlatCellMesh();

FS_CONTENT_DLL_FUNC double buildBasicMesh();

FS_CONTENT_DLL_FUNC double refreshTable();

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// c++ attributes
int lastpredrawoutput;

int lastpredrawinput;

IndexedMesh structuralMesh;

Mesh platformsMesh;

bool rebuildMeshes;

double meshSY;

int meshDrawMode;

int meshFloorStorage;

bool blockRecursiveReceive;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Conveyor
class Conveyor : public FixedResource
{
public:

TreeNode* node_v_speed;
#define v_speed node_v_speed->safedatafloat()[0]
TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]
TreeNode* node_v_accumulating;
#define v_accumulating node_v_accumulating->safedatafloat()[0]
TreeNode* node_v_conveyendtrigger;
TreeNode* node_v_lastexittime;
#define v_lastexittime node_v_lastexittime->safedatafloat()[0]
TreeNode* node_v_lastentrytime;
#define v_lastentrytime node_v_lastentrytime->safedatafloat()[0]
TreeNode* node_v_lastexitsize;
#define v_lastexitsize node_v_lastexitsize->safedatafloat()[0]
TreeNode* node_v_conveytimesle;
#define v_conveytimesle node_v_conveytimesle->safedatafloat()[0]
TreeNode* node_v_conveyorlength;
#define v_conveyorlength node_v_conveyorlength->safedatafloat()[0]
TreeNode* node_v_needinputevent;
#define v_needinputevent node_v_needinputevent->safedatafloat()[0]
TreeNode* node_v_filledlength;
#define v_filledlength node_v_filledlength->safedatafloat()[0]
TreeNode* node_v_spacingmode;
#define v_spacingmode node_v_spacingmode->safedatafloat()[0]
TreeNode* node_v_spacing;
#define v_spacing node_v_spacing->safedatafloat()[0]
TreeNode* node_v_zoffset;
#define v_zoffset node_v_zoffset->safedatafloat()[0]
TreeNode* node_v_siderelative;
#define v_siderelative node_v_siderelative->safedatafloat()[0]
TreeNode* node_v_sideheight;
#define v_sideheight node_v_sideheight->safedatafloat()[0]
TreeNode* node_v_nroflegs;
#define v_nroflegs node_v_nroflegs->safedatafloat()[0]
TreeNode* node_v_legsrelative;
#define v_legsrelative node_v_legsrelative->safedatafloat()[0]
TreeNode* node_v_legheight;
#define v_legheight node_v_legheight->safedatafloat()[0]
TreeNode* node_v_texturedist;
#define v_texturedist node_v_texturedist->safedatafloat()[0]
TreeNode* node_v_prodzoffset;
#define v_prodzoffset node_v_prodzoffset->safedatafloat()[0]
TreeNode* node_v_sections;
#define v_sections node_v_sections->safedatafloat()[0]
TreeNode* node_v_lastentrysize;
#define v_lastentrysize node_v_lastentrysize->safedatafloat()[0]
TreeNode* node_v_photoeyes;
#define v_photoeyes node_v_photoeyes->safedatafloat()[0]
TreeNode* node_v_photoeyecovertrigger;
TreeNode* node_v_photoeyeuncovertrigger;
TreeNode* node_v_orientationmode;
#define v_orientationmode node_v_orientationmode->safedatafloat()[0]
TreeNode* node_v_zorient;
#define v_zorient node_v_zorient->safedatafloat()[0]
TreeNode* node_v_yorient;
#define v_yorient node_v_yorient->safedatafloat()[0]
TreeNode* node_v_userlength;
#define v_userlength node_v_userlength->safedatafloat()[0]
TreeNode* node_v_scaleitemsize;
#define v_scaleitemsize node_v_scaleitemsize->safedatafloat()[0]
TreeNode* node_v_sectiontotallength;
#define v_sectiontotallength node_v_sectiontotallength->safedatafloat()[0]
TreeNode* node_v_blockedlength;
#define v_blockedlength node_v_blockedlength->safedatafloat()[0]
TreeNode* node_v_notifyofblockedlength;
#define v_notifyofblockedlength node_v_notifyofblockedlength->safedatafloat()[0]
TreeNode* node_v_zerospeedtime;
#define v_zerospeedtime node_v_zerospeedtime->safedatafloat()[0]
TreeNode* node_v_lastpositivespeed;
#define v_lastpositivespeed node_v_lastpositivespeed->safedatafloat()[0]
TreeNode* node_v_convkinematic;
TreeNode* node_v_totalexitedspace;
#define v_totalexitedspace node_v_totalexitedspace->safedatafloat()[0]
TreeNode* node_v_curtexper;
#define v_curtexper node_v_curtexper->safedatafloat()[0]
TreeNode* node_v_drawcont;
#define v_drawcont node_v_drawcont->safedatafloat()[0]
TreeNode* node_v_drawstop;
#define v_drawstop node_v_drawstop->safedatafloat()[0]
TreeNode* node_v_textureincrement;
#define v_textureincrement node_v_textureincrement->safedatafloat()[0]
TreeNode* node_v_movewhilepaused;
#define v_movewhilepaused node_v_movewhilepaused->safedatafloat()[0]
TreeNode* node_v_lastdrawtime;
#define v_lastdrawtime node_v_lastdrawtime->safedatafloat()[0]
TreeNode* node_v_texremainder;
#define v_texremainder node_v_texremainder->safedatafloat()[0]
TreeNode* node_v_sideoffset;
#define v_sideoffset node_v_sideoffset->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC  Conveyor();

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onDrawPlanar(treenode view);

FS_CONTENT_DLL_FUNC double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC double onKeyedClick(treenode view, int code, char key);

FS_CONTENT_DLL_FUNC double setAllLocations();

FS_CONTENT_DLL_FUNC double setOneLocation(treenode item, double tempmaxloc, double curzoffset);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double updateSectionInfo();

FS_CONTENT_DLL_FUNC virtual double getPickOffset(treenode involvedobj, treenode toobject, double* returnarray);

FS_CONTENT_DLL_FUNC virtual double getPlaceOffset(treenode involvedobj, treenode fromobject,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC double resumeObject();

FS_CONTENT_DLL_FUNC virtual double photoEyeEntryLogic(treenode item);

FS_CONTENT_DLL_FUNC virtual double checkCreatePEYellow(treenode item, double itempos, int onexit DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double checkCreatePEGreen(treenode item, double itembackedgepos, int pe, int onexit DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double photoEyeExitLogic(treenode item);

FS_CONTENT_DLL_FUNC double alignNextLoc();

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC double getProdLength(treenode item);

FS_CONTENT_DLL_FUNC virtual double changeSpeed(double newspeed);

FS_CONTENT_DLL_FUNC virtual double blockedLengthNotify(double length);

FS_CONTENT_DLL_FUNC virtual double blockedLengthNotifyUpstream(double length);

FS_CONTENT_DLL_FUNC virtual double resetConveyorKinematics();

FS_CONTENT_DLL_FUNC virtual double flipAroundAxis(const Vec2& point1, const Vec2& point2);

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);

FS_CONTENT_DLL_FUNC double initItem(treenode item);

FS_CONTENT_DLL_FUNC double buildBaseMesh(treenode cursection);

FS_CONTENT_DLL_FUNC double buildConveyorMesh(treenode cursection);


// c++ attributes
treenode cursection;

double cursecstartx;

double cursecstarty;

double cursecstartz;

double cursecstartangle;

double cursectype;

double cursecstartlength;

double curseclength;

double cursecrise;

double cursecangle;

double cursecradius;

double accummaxloc;

double drawangle;

Mesh legMesh;

Mesh photoeyeMesh;

Mesh conveyorMesh;

bool baseMeshBuilt;

double builtY;

double builtZ;

bool builtRelative;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// MergeSort
class MergeSort : public Conveyor
{
public:

TreeNode* node_v_inputtable;
#define v_inputtable node_v_inputtable->safedatafloat()[0]
TreeNode* node_v_outputtable;
#define v_outputtable node_v_outputtable->safedatafloat()[0]
TreeNode* node_v_sortedtable;
#define v_sortedtable node_v_sortedtable->safedatafloat()[0]
TreeNode* node_v_sendrequirement;
TreeNode* node_v_blocktime;
#define v_blocktime node_v_blocktime->safedatafloat()[0]
TreeNode* node_v_madeattempt;
#define v_madeattempt node_v_madeattempt->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onClick(treenode view, int code);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double updatePortTables();

FS_CONTENT_DLL_FUNC double updateLocations();

FS_CONTENT_DLL_FUNC double setAllLocations(double updatetime);

FS_CONTENT_DLL_FUNC double releaseItem(treenode item, int port);

FS_CONTENT_DLL_FUNC double receiveItem(int port);

FS_CONTENT_DLL_FUNC virtual double inOpenEvent(FixedResource* otherobject, int search, double port );

FS_CONTENT_DLL_FUNC double drawInPort(int port);

FS_CONTENT_DLL_FUNC double drawOutPort(int port);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);

FS_CONTENT_DLL_FUNC virtual double onTransportInNotify(treenode item, int port);

FS_CONTENT_DLL_FUNC double buildPortMesh();


// c++ attributes
Mesh inputMesh;

Mesh outputMesh;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// BasicConveyor
class BasicConveyor : public Conveyor
{
public:

TreeNode* node_v_decisionpointtable;
#define v_decisionpointtable node_v_decisionpointtable->safedatafloat()[0]
TreeNode* node_v_dptablecache;
TreeNode* node_v_recycledkinematics;
#define v_recycledkinematics node_v_recycledkinematics->safedatafloat()[0]
TreeNode* node_v_recyclednodes;
#define v_recyclednodes node_v_recyclednodes->safedatafloat()[0]
TreeNode* node_v_direction;
#define v_direction node_v_direction->safedatafloat()[0]
TreeNode* node_v_lastupdatetime;
#define v_lastupdatetime node_v_lastupdatetime->safedatafloat()[0]
TreeNode* node_v_cleardpevents;
#define v_cleardpevents node_v_cleardpevents->safedatafloat()[0]
TreeNode* node_v_inactivecouplings;
#define v_inactivecouplings node_v_inactivecouplings->safedatafloat()[0]
TreeNode* node_v_stopresume;

// c++ member functions

FS_CONTENT_DLL_FUNC inline treenode getMainItemKinematics(treenode item);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double updateLocations();

FS_CONTENT_DLL_FUNC double setAllLocations();

FS_CONTENT_DLL_FUNC double initItem(treenode item);

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);

FS_CONTENT_DLL_FUNC double setItemConveyState(treenode item, double startpoint, double startspeed, double targetspeed, double accdec);

FS_CONTENT_DLL_FUNC double setConveyStatesByRange(double frompos, double topos, double startspeed, double targetspeed, double accdec);

FS_CONTENT_DLL_FUNC double getDPsFromPosition(double position, double prodlength, double space, int* frontdp, int* backdp, int* backspacedp);

FS_CONTENT_DLL_FUNC double onSpaceCleared(treenode item);

FS_CONTENT_DLL_FUNC double createDPClearEvent(treenode item, int backedgetype);

FS_CONTENT_DLL_FUNC double getItemPosition(treenode item);

FS_CONTENT_DLL_FUNC double setDirection(int direction);

FS_CONTENT_DLL_FUNC double updateAllPositions(int forceupdate DEFAULTZERO);

FS_CONTENT_DLL_FUNC double resetKinematicsBehind(treenode item);

FS_CONTENT_DLL_FUNC double getFilledLength();

FS_CONTENT_DLL_FUNC virtual double getPickOffset(treenode involvedobj, treenode toobject, double* returnarray);

FS_CONTENT_DLL_FUNC treenode getItemKinematics(treenode item, int kintype);

FS_CONTENT_DLL_FUNC static char* showDPCacheInfo(treenode dpcache, int verbose);

FS_CONTENT_DLL_FUNC static double getItemInfo(treenode item, int val);

FS_CONTENT_DLL_FUNC double destroyItemEvent(treenode item, int event);

FS_CONTENT_DLL_FUNC double cleanItemEvent(treenode item, int event);

FS_CONTENT_DLL_FUNC double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC double resumeObject();

FS_CONTENT_DLL_FUNC double buildDecisionMesh();


// c++ attributes
struct dptableentry{int row; double position; bool spaceneeded; int coverstate;};;

treenode exitingitem;;

Mesh decisionPointMesh;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// BasicFR
class BasicFR : public FixedResource
{
public:

TreeNode* node_v_transportinnotifycomplete;
TreeNode* node_v_transportoutnotifycomplete;
TreeNode* node_v_stopresume;
TreeNode* node_v_pickplaceoffset;
TreeNode* node_v_advancedfunctions;
TreeNode* node_v_statechange;
TreeNode* node_v_poffsetx;
#define v_poffsetx node_v_poffsetx->safedatafloat()[0]
TreeNode* node_v_poffsety;
#define v_poffsety node_v_poffsety->safedatafloat()[0]
TreeNode* node_v_poffsetz;
#define v_poffsetz node_v_poffsetz->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject(int id, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onTransportInNotify(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTransportOutNotify(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTransportOutComplete(treenode item, int port, treenode transporter DEFAULTNULL);

FS_CONTENT_DLL_FUNC double onTransportInComplete(treenode item, int port, treenode transporter DEFAULTNULL);

FS_CONTENT_DLL_FUNC double getPickOffset(treenode item, treenode toobject, double* returnarray);

FS_CONTENT_DLL_FUNC double getPlaceOffset(treenode item, treenode fromobject,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC double onClick(treenode view, int code);

FS_CONTENT_DLL_FUNC double onKeyedClick(treenode view, int code, char key);

FS_CONTENT_DLL_FUNC double onStateChange(int toState, treenode stateProfile);

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Dispatcher
class Dispatcher : public FlexSimObject
{
public:

TreeNode* node_v_tasksequencequeue;
#define v_tasksequencequeue node_v_tasksequencequeue->safedatafloat()[0]
TreeNode* node_v_coordinatedtasks;
#define v_coordinatedtasks node_v_coordinatedtasks->safedatafloat()[0]
TreeNode* node_v_passimmediately;
#define v_passimmediately node_v_passimmediately->safedatafloat()[0]
TreeNode* node_v_passto;
TreeNode* node_v_queuestrategy;
TreeNode* node_v_onresourceavailable;
TreeNode* node_v_onreceivets;

// c++ member functions

FS_CONTENT_DLL_FUNC double onOutOpen(int port);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC virtual double receiveTaskSequence(treenode newtasksequence);

FS_CONTENT_DLL_FUNC virtual double finishUtilize(treenode involveditem);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double rankInOrder(treenode tasksequence);

FS_CONTENT_DLL_FUNC virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC virtual double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC double resumeObject(int id, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject();

FS_CONTENT_DLL_FUNC double reorder();

FS_CONTENT_DLL_FUNC double rerankbest();

FS_CONTENT_DLL_FUNC virtual treenode findBestTS();

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC double updateVersion(char* newversion, char* oldversion);

FS_CONTENT_DLL_FUNC double executeTasks(treenode tasksequence);

FS_CONTENT_DLL_FUNC double executeProxyTask(treenode curtask, Task* taskdata, Task* allocatetaskdata);

FS_CONTENT_DLL_FUNC double finishProxyTask(treenode task, treenode executer);

FS_CONTENT_DLL_FUNC double makeMultipleAllocations(treenode tasksequence, treenode alreadyallocatedtask);

FS_CONTENT_DLL_FUNC double onAllocationNotify(treenode executer, treenode task);

FS_CONTENT_DLL_FUNC inline double finishDeallocation(Task* taskdata, Task* allocatetaskdata, TaskSequence* tsdata);

FS_CONTENT_DLL_FUNC static int recycleTaskSequence(treenode tasksequence);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double onResourceAvailable(int port);

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// TaskExecuter
class TaskExecuter : public Dispatcher
{
public:

TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]
TreeNode* node_v_loadtime;
TreeNode* node_v_loadtrigger;
TreeNode* node_v_unloadtime;
TreeNode* node_v_unloadtrigger;
TreeNode* node_v_maxspeed;
#define v_maxspeed node_v_maxspeed->safedatafloat()[0]
TreeNode* node_v_acceleration;
#define v_acceleration node_v_acceleration->safedatafloat()[0]
TreeNode* node_v_deceleration;
#define v_deceleration node_v_deceleration->safedatafloat()[0]
TreeNode* node_v_navigator;
#define v_navigator node_v_navigator->safedatafloat()[0]
TreeNode* node_v_oldbreakrequirement;
#define v_oldbreakrequirement node_v_oldbreakrequirement->safedatafloat()[0]
TreeNode* node_v_breakto;
TreeNode* node_v_modifyrotation;
#define v_modifyrotation node_v_modifyrotation->safedatafloat()[0]
TreeNode* node_v_useoffsets;
#define v_useoffsets node_v_useoffsets->safedatafloat()[0]
TreeNode* node_v_offsettingnow;
#define v_offsettingnow node_v_offsettingnow->safedatafloat()[0]
TreeNode* node_v_offsetbegintime;
#define v_offsetbegintime node_v_offsetbegintime->safedatafloat()[0]
TreeNode* node_v_offsettotaltime;
#define v_offsettotaltime node_v_offsettotaltime->safedatafloat()[0]
TreeNode* node_v_offsetlocx;
#define v_offsetlocx node_v_offsetlocx->safedatafloat()[0]
TreeNode* node_v_offsetlocy;
#define v_offsetlocy node_v_offsetlocy->safedatafloat()[0]
TreeNode* node_v_offsetlocz;
#define v_offsetlocz node_v_offsetlocz->safedatafloat()[0]
TreeNode* node_v_offsetbeginx;
#define v_offsetbeginx node_v_offsetbeginx->safedatafloat()[0]
TreeNode* node_v_offsetbeginy;
#define v_offsetbeginy node_v_offsetbeginy->safedatafloat()[0]
TreeNode* node_v_offsetbeginz;
#define v_offsetbeginz node_v_offsetbeginz->safedatafloat()[0]
TreeNode* node_v_offsetbeginxrot;
#define v_offsetbeginxrot node_v_offsetbeginxrot->safedatafloat()[0]
TreeNode* node_v_offsetbeginyrot;
#define v_offsetbeginyrot node_v_offsetbeginyrot->safedatafloat()[0]
TreeNode* node_v_offsetbeginzrot;
#define v_offsetbeginzrot node_v_offsetbeginzrot->safedatafloat()[0]
TreeNode* node_v_loadedspeed;
#define v_loadedspeed node_v_loadedspeed->safedatafloat()[0]
TreeNode* node_v_emptyspeed;
#define v_emptyspeed node_v_emptyspeed->safedatafloat()[0]
TreeNode* node_v_curloadunloadtime;
#define v_curloadunloadtime node_v_curloadunloadtime->safedatafloat()[0]
TreeNode* node_v_lastupdatedspeed;
#define v_lastupdatedspeed node_v_lastupdatedspeed->safedatafloat()[0]
TreeNode* node_v_travelvstart;
#define v_travelvstart node_v_travelvstart->safedatafloat()[0]
TreeNode* node_v_travelvend;
#define v_travelvend node_v_travelvend->safedatafloat()[0]
TreeNode* node_v_lastspeedupdatetime;
#define v_lastspeedupdatetime node_v_lastspeedupdatetime->safedatafloat()[0]
TreeNode* node_v_collisiontrigger;
TreeNode* node_v_collcheckinterval;
#define v_collcheckinterval node_v_collcheckinterval->safedatafloat()[0]
TreeNode* node_v_drawcollspheres;
#define v_drawcollspheres node_v_drawcollspheres->safedatafloat()[0]
TreeNode* node_v_incollision;
#define v_incollision node_v_incollision->safedatafloat()[0]
TreeNode* node_v_collcheckstate;
#define v_collcheckstate node_v_collcheckstate->safedatafloat()[0]
TreeNode* node_v_totaltraveldist;
#define v_totaltraveldist node_v_totaltraveldist->safedatafloat()[0]
TreeNode* node_v_kinematics;
TreeNode* node_v_flipthreshold;
#define v_flipthreshold node_v_flipthreshold->safedatafloat()[0]
TreeNode* node_v_availableonstart;
#define v_availableonstart node_v_availableonstart->safedatafloat()[0]
TreeNode* node_v_activetasksequence;
#define v_activetasksequence node_v_activetasksequence->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC  TaskExecuter();

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC virtual double onDestinationArrival(double finalspeed);

FS_CONTENT_DLL_FUNC virtual double receiveTaskSequence(treenode newts);

FS_CONTENT_DLL_FUNC double cleanupAbortedTS(treenode ts);

FS_CONTENT_DLL_FUNC virtual double beginTask(treenode task);

FS_CONTENT_DLL_FUNC virtual double beginLoadUnloadTask(treenode task, int isLoad, int eventCode, char* eventName, int logId);

FS_CONTENT_DLL_FUNC virtual double finishTask(treenode task);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double getEntryLoc(treenode involved,  double* returnarray);

FS_CONTENT_DLL_FUNC double offsetByNavigator(double endSpeed);

FS_CONTENT_DLL_FUNC virtual double beginOffset(double endspeed, treenode item);

FS_CONTENT_DLL_FUNC virtual double beginOffsetDefault(double endspeed, treenode item);

FS_CONTENT_DLL_FUNC virtual double updateOffset();

FS_CONTENT_DLL_FUNC virtual double finishOffset();

FS_CONTENT_DLL_FUNC treenode  findDefaultNavigator();

FS_CONTENT_DLL_FUNC virtual double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC double resumeObject(int id, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject();

FS_CONTENT_DLL_FUNC virtual double preemptActive(treenode task, treenode activets, int preempttype, treenode newts);

FS_CONTENT_DLL_FUNC static treenode findNextDurativeTask(treenode tasksequencenode, int alloctaskrank DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onPreempt();

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual double reassignNetNode(NetworkNode* netnode);

FS_CONTENT_DLL_FUNC virtual double getPlaceOffset(treenode involvedobj, treenode fromobject,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual double getPickOffset(treenode item, treenode toobject, double* returnarray);

FS_CONTENT_DLL_FUNC double saveState();

FS_CONTENT_DLL_FUNC double loadState();

FS_CONTENT_DLL_FUNC double queryDistance(FlexSimObject* destination);

FS_CONTENT_DLL_FUNC double resumeLoad(treenode fromstation);

FS_CONTENT_DLL_FUNC double resumeUnload(treenode tostation);

FS_CONTENT_DLL_FUNC double setCollisionCheck(int val, double interval);

FS_CONTENT_DLL_FUNC double drawSpheres(treenode view, double * drawcolor);

FS_CONTENT_DLL_FUNC double catchTaskError(treenode task);

FS_CONTENT_DLL_FUNC virtual int checkCollisions();

FS_CONTENT_DLL_FUNC double setObjectInfo();

FS_CONTENT_DLL_FUNC virtual void onBeginTask(treenode task);

FS_CONTENT_DLL_FUNC virtual void onEndTask(treenode task);

FS_CONTENT_DLL_FUNC virtual void onOffsetFinishNotify();

FS_CONTENT_DLL_FUNC virtual double onResourceAvailable(int port);

FS_CONTENT_DLL_FUNC virtual double onStartSimulation();

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// c++ attributes
double offsetloc[3] ;

treenode activetask;

IndexedMesh spheresMesh;

treenode onPreemptTrigger = nullptr;

treenode onStartTaskTrigger = nullptr;

treenode onFinishTaskTrigger = nullptr;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Operator
class Operator : public TaskExecuter
{
public:


// c++ member functions

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double beginOffset(double endspeed, treenode item);

FS_CONTENT_DLL_FUNC double finishOffset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual void onBeginTask(treenode task);

FS_CONTENT_DLL_FUNC virtual void onEndTask(treenode task);

FS_CONTENT_DLL_FUNC virtual double getEntryLoc(treenode involved,  double* returnarray);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Transporter
class Transporter : public TaskExecuter
{
public:

TreeNode* node_v_forkspeed;
#define v_forkspeed node_v_forkspeed->safedatafloat()[0]
TreeNode* node_v_forkinitialheight;
#define v_forkinitialheight node_v_forkinitialheight->safedatafloat()[0]
TreeNode* node_v_forkdestheight;
#define v_forkdestheight node_v_forkdestheight->safedatafloat()[0]
TreeNode* node_v_forkbegintime;
#define v_forkbegintime node_v_forkbegintime->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double getForkHeight();

FS_CONTENT_DLL_FUNC double beginOffset(double endspeed,treenode item);

FS_CONTENT_DLL_FUNC double finishOffset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual void onBeginTask(treenode task);

FS_CONTENT_DLL_FUNC virtual double updateOffset();

FS_CONTENT_DLL_FUNC virtual double getEntryLoc(treenode involved,  double* returnarray);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Elevator
class Elevator : public TaskExecuter
{
public:

TreeNode* node_v_shellzloc;
#define v_shellzloc node_v_shellzloc->safedatafloat()[0]
TreeNode* node_v_xconvey;
#define v_xconvey node_v_xconvey->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onClick(treenode view, int code);

FS_CONTENT_DLL_FUNC virtual double beginOffset(double endspeed, treenode item);

FS_CONTENT_DLL_FUNC virtual double updateOffset();

FS_CONTENT_DLL_FUNC virtual double getEntryLoc(treenode involvedobj,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC double scaleComponents();

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double onDrag(treenode view);


// c++ attributes
double lastzloc;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Robot
class Robot : public TaskExecuter
{
public:

TreeNode* node_v_motionmethod;
#define v_motionmethod node_v_motionmethod->safedatafloat()[0]
TreeNode* node_v_extensionspeed;
#define v_extensionspeed node_v_extensionspeed->safedatafloat()[0]
TreeNode* node_v_rotationspeed;
#define v_rotationspeed node_v_rotationspeed->safedatafloat()[0]
TreeNode* node_v_yrotspeed;
#define v_yrotspeed node_v_yrotspeed->safedatafloat()[0]
TreeNode* node_v_robotkinematics;
#define v_robotkinematics node_v_robotkinematics->safedatafloat()[0]
TreeNode* node_v_clamporientation;
#define v_clamporientation node_v_clamporientation->safedatafloat()[0]
TreeNode* node_v_clampwidth;
#define v_clampwidth node_v_clampwidth->safedatafloat()[0]
TreeNode* node_v_lastpathnum;
#define v_lastpathnum node_v_lastpathnum->safedatafloat()[0]
TreeNode* node_v_nextpathselected;
#define v_nextpathselected node_v_nextpathselected->safedatafloat()[0]
TreeNode* node_v_pathtables;
#define v_pathtables node_v_pathtables->safedatafloat()[0]
TreeNode* node_v_movetime;
TreeNode* node_v_speedtable;
#define v_speedtable node_v_speedtable->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double beginOffset(double endspeed, treenode item);

FS_CONTENT_DLL_FUNC double updateOffset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double updateVersion(char* newversion, char* oldversion);

FS_CONTENT_DLL_FUNC double moveArm(treenode item, int pathnum, int endrow) ;

FS_CONTENT_DLL_FUNC double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double drawSkeleton(double* d, double* a, double xtrans, double * color);

FS_CONTENT_DLL_FUNC double autoCalculateTable(double* d, double * a, double * xtrans);

FS_CONTENT_DLL_FUNC double applyJointsToItem(int orientationType);

FS_CONTENT_DLL_FUNC double applyItemToJoints(int orientationType);

FS_CONTENT_DLL_FUNC double calcApproachOffsetDist(treenode item, int orientationType);

FS_CONTENT_DLL_FUNC Vec3 calcApproachOffsetRot(int orientationType);

FS_CONTENT_DLL_FUNC Vec3 calcItemRot(int orientationType);

FS_CONTENT_DLL_FUNC double calcClampWidth(treenode item, int orientationType);


// c++ attributes

static const int CLAMP_Z_BY_X = 1;
static const int CLAMP_Z_BY_Y = 2;
static const int CLAMP_Z_NEG_BY_X = 3;
static const int CLAMP_Z_NEG_BY_Y = 4;
static const int CLAMP_Y_BY_Z = 5;
static const int CLAMP_Y_BY_X = 6;
static const int CLAMP_Y_NEG_BY_Z = 7;
static const int CLAMP_Y_NEG_BY_X = 8;
static const int CLAMP_X_BY_Y = 9;
static const int CLAMP_X_BY_Z = 10;
static const int CLAMP_X_NEG_BY_Y = 11;
static const int CLAMP_X_NEG_BY_Z = 12;



static const int MOTION_METHOD_SIMPLE = 1;
static const int MOTION_METHOD_MOVE_TIME = 2;
static const int MOTION_METHOD_SPEEDS = 3;
static const int MOTION_METHOD_PATHS = 4;



static const int PATH_CYCLETIME = 1;
static const int PATH_TABLE = 2;
static const int PATH_CLOSE_CLAMP_TIME = 3;
static const int PATH_OPEN_CLAMP_TIME = 4;
static const int PATH_NEXT_PATH = 5;
static const int PATH_CLAMP_ORIENTATION = 6;



// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Crane
class Crane : public TaskExecuter
{
public:

TreeNode* node_v_shellxloc;
#define v_shellxloc node_v_shellxloc->safedatafloat()[0]
TreeNode* node_v_shellyloc;
#define v_shellyloc node_v_shellyloc->safedatafloat()[0]
TreeNode* node_v_shellzloc;
#define v_shellzloc node_v_shellzloc->safedatafloat()[0]
TreeNode* node_v_moving;
#define v_moving node_v_moving->safedatafloat()[0]
TreeNode* node_v_liftheight;
#define v_liftheight node_v_liftheight->safedatafloat()[0]
TreeNode* node_v_travelsequence;
TreeNode* node_v_cranespeeds;
#define v_cranespeeds node_v_cranespeeds->safedatafloat()[0]
TreeNode* node_v_cranekinematics;
TreeNode* node_v_liftradius;
#define v_liftradius node_v_liftradius->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double getEntryLoc(treenode involvedobj,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual double beginOffset(double endspeed, treenode item);

FS_CONTENT_DLL_FUNC virtual double updateOffset();

FS_CONTENT_DLL_FUNC virtual double onPreempt();

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double updateVersion(char* newversion, char* oldversion);

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);

FS_CONTENT_DLL_FUNC virtual double rotateAroundAxis(double angle, double x, double y);

FS_CONTENT_DLL_FUNC virtual double flipAroundAxis(const Vec2& point1, const Vec2& point2);

FS_CONTENT_DLL_FUNC virtual double onDrag(treenode view);

FS_CONTENT_DLL_FUNC virtual double onClick(treenode view, int code);

FS_CONTENT_DLL_FUNC double scaleComponents(int picktype, double newsize);


// c++ attributes
double lastxloc;

double lastyloc;

double lastzloc;

double justcreated;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// ASRSvehicle
class ASRSvehicle : public TaskExecuter
{
public:

TreeNode* node_v_forkspeed;
#define v_forkspeed node_v_forkspeed->safedatafloat()[0]
TreeNode* node_v_forkinitialheight;
#define v_forkinitialheight node_v_forkinitialheight->safedatafloat()[0]
TreeNode* node_v_forkkinematics;
TreeNode* node_v_yconvey;
#define v_yconvey node_v_yconvey->safedatafloat()[0]
TreeNode* node_v_forkresetheight;
#define v_forkresetheight node_v_forkresetheight->safedatafloat()[0]
TreeNode* node_v_railx;
#define v_railx node_v_railx->safedatafloat()[0]
TreeNode* node_v_raily;
#define v_raily node_v_raily->safedatafloat()[0]
TreeNode* node_v_railz;
#define v_railz node_v_railz->safedatafloat()[0]
TreeNode* node_v_extensionspeed;
#define v_extensionspeed node_v_extensionspeed->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double getForkHeight();

FS_CONTENT_DLL_FUNC double beginOffset(double endspeed, treenode item);

FS_CONTENT_DLL_FUNC double finishOffset();

FS_CONTENT_DLL_FUNC double updateOffset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double getEntryLoc(treenode involvedobj,  double* returnarray);

FS_CONTENT_DLL_FUNC virtual double onDrag(treenode view);

FS_CONTENT_DLL_FUNC virtual double onClick(treenode view, int code);

FS_CONTENT_DLL_FUNC double scaleComponents();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// BasicTE
class BasicTE : public TaskExecuter
{
public:

TreeNode* node_v_onbeginoffset;
TreeNode* node_v_onupdateoffset;
TreeNode* node_v_onfinishoffset;
TreeNode* node_v_pickplaceoffset;
TreeNode* node_v_stopresume;
TreeNode* node_v_advancedfunctions;
TreeNode* node_v_statechange;
TreeNode* node_v_poffsetx;
#define v_poffsetx node_v_poffsetx->safedatafloat()[0]
TreeNode* node_v_poffsety;
#define v_poffsety node_v_poffsety->safedatafloat()[0]
TreeNode* node_v_poffsetz;
#define v_poffsetz node_v_poffsetz->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double beginOffset(double endspeed, treenode item);

FS_CONTENT_DLL_FUNC double updateOffset();

FS_CONTENT_DLL_FUNC double finishOffset();

FS_CONTENT_DLL_FUNC double getPickOffset(treenode item, treenode toobject, double* returnarray);

FS_CONTENT_DLL_FUNC double getPlaceOffset(treenode item, treenode fromobject,  double* returnarray);

FS_CONTENT_DLL_FUNC double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject(int id, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC double onClick(treenode view, int code);

FS_CONTENT_DLL_FUNC virtual double onPreempt();

FS_CONTENT_DLL_FUNC double onKeyedClick(treenode view, int code, char key);

FS_CONTENT_DLL_FUNC double onStateChange(int toState, treenode stateProfile);

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// NetworkNode
class NetworkNode : public FlexSimObject
{
public:

TreeNode* node_v_network;
#define v_network node_v_network->safedatafloat()[0]
TreeNode* node_v_travellers;
#define v_travellers node_v_travellers->safedatafloat()[0]
TreeNode* node_v_activetravellers;
#define v_activetravellers node_v_activetravellers->safedatafloat()[0]
TreeNode* node_v_stations;
#define v_stations node_v_stations->safedatafloat()[0]
TreeNode* node_v_showmode;
#define v_showmode node_v_showmode->safedatafloat()[0]
TreeNode* node_v_maxinactive;
#define v_maxinactive node_v_maxinactive->safedatafloat()[0]
TreeNode* node_v_lastxloc;
#define v_lastxloc node_v_lastxloc->safedatafloat()[0]
TreeNode* node_v_lastyloc;
#define v_lastyloc node_v_lastyloc->safedatafloat()[0]
TreeNode* node_v_lastzloc;
#define v_lastzloc node_v_lastzloc->safedatafloat()[0]
TreeNode* node_v_showme;
#define v_showme node_v_showme->safedatafloat()[0]
TreeNode* node_v_lastupdatetime;
#define v_lastupdatetime node_v_lastupdatetime->safedatafloat()[0]
TreeNode* node_v_entrytrigger;
TreeNode* node_v_arrivaltrigger;
TreeNode* node_v_clicked;
#define v_clicked node_v_clicked->safedatafloat()[0]
TreeNode* node_v_sideoffset;
#define v_sideoffset node_v_sideoffset->safedatafloat()[0]
TreeNode* node_v_disttosideoffset;
#define v_disttosideoffset node_v_disttosideoffset->safedatafloat()[0]
TreeNode* node_v_trafficcontrollers;
#define v_trafficcontrollers node_v_trafficcontrollers->safedatafloat()[0]
TreeNode* node_v_virtualexits;
#define v_virtualexits node_v_virtualexits->safedatafloat()[0]
TreeNode* node_v_notifyofblockedlength;
#define v_notifyofblockedlength node_v_notifyofblockedlength->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC  NetworkNode();

FS_CONTENT_DLL_FUNC double onCreate(double dropx, double dropy, double dropz, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onDrag(treenode view);

FS_CONTENT_DLL_FUNC double onPreDraw(treenode view);

FS_CONTENT_DLL_FUNC double onDrawPlanar(treenode view);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onKeyedClick(treenode view, int code, char key);

FS_CONTENT_DLL_FUNC treenode onMenuPopup(treenode view, treenode theMenu);

FS_CONTENT_DLL_FUNC double setViewMode(int viewMode);

FS_CONTENT_DLL_FUNC double onClick(treenode view, int code);

FS_CONTENT_DLL_FUNC double onDestroy(treenode view);

FS_CONTENT_DLL_FUNC virtual double onReceiveTraveler(treenode reqnode, int port, int beginning, int lastport);

FS_CONTENT_DLL_FUNC virtual double onSendTraveler(treenode reqnode, int nextport);

FS_CONTENT_DLL_FUNC virtual double releaseTraveler(treenode reqnode);

FS_CONTENT_DLL_FUNC virtual double receiveTraveler(int port);

FS_CONTENT_DLL_FUNC virtual double receiveInputRequest(treenode reqnode, int port, int lastport);

FS_CONTENT_DLL_FUNC static int pushTraveler(treenode reqnode, NetworkNode* tonetnode, int nextport);

FS_CONTENT_DLL_FUNC virtual double isTrafficControlMember(treenode tcontroller);

FS_CONTENT_DLL_FUNC static int resumePushTraveler(treenode reqnode, NetworkNode* tonetnode, int nextport);

FS_CONTENT_DLL_FUNC virtual double onTravelInNotify(treenode reqnode, int port);

FS_CONTENT_DLL_FUNC virtual double getSplinePos(int port, double perc, double * returnloc);

FS_CONTENT_DLL_FUNC virtual double getPlaceOffset(treenode traveler, treenode reqnode,  int port, double* returnarray);

FS_CONTENT_DLL_FUNC virtual double updateData();

FS_CONTENT_DLL_FUNC virtual double getBurden(int outport);

FS_CONTENT_DLL_FUNC virtual double getEdgeSpeedLimit(int outport);

FS_CONTENT_DLL_FUNC virtual double dragConnection(treenode toObj, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC virtual NetNodeEdge* addEdge(NetworkNode* otherNode, int toType, int backType, bool curved);

FS_CONTENT_DLL_FUNC virtual NetNodeEdge* createNewEdge();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double toggleShowMode(int newmode);

FS_CONTENT_DLL_FUNC virtual double abortTravel(treenode reqnode);

FS_CONTENT_DLL_FUNC virtual double deleteInRequest(treenode reqnode, int searchallports DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC double invalidateSpline(int port);

FS_CONTENT_DLL_FUNC NetworkNavigator* checkNetwork(int changename DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual char* getNavigatorName();

FS_CONTENT_DLL_FUNC unsigned int getClassType();

FS_CONTENT_DLL_FUNC double userCloseEdge(int portnum);

FS_CONTENT_DLL_FUNC double userOpenEdge(int portnum);

FS_CONTENT_DLL_FUNC virtual double updateVersion(char* newversion, char* oldversion);

FS_CONTENT_DLL_FUNC double saveState();

FS_CONTENT_DLL_FUNC double loadState();

FS_CONTENT_DLL_FUNC virtual double validateData(int notifyuser DEFAULTONE);

FS_CONTENT_DLL_FUNC virtual double rotateAroundAxis(double angle, double x, double y);

FS_CONTENT_DLL_FUNC virtual double flipAroundAxis(const Vec2& point1, const Vec2& point2);

FS_CONTENT_DLL_FUNC double buildStaticMeshes();

FS_CONTENT_DLL_FUNC double buildMesh();

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC virtual void setEdgeType(treenode edge, int type);

FS_CONTENT_DLL_FUNC virtual void setEdgeGeomType(treenode edgeNode, bool straight);

FS_CONTENT_DLL_FUNC double addSplineAtts(treenode obj);

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// c++ attributes
static Mesh pointMesh;

static Mesh selectionMesh;

static Mesh utilityMesh;

static bool staticMeshesBuilt;

bool isMeshDirty;

int meshEdgePointSplit;

int meshEnd;

Mesh mesh;

Mesh arrowMesh;

double meshCheckSum;

NodeListArray<NetNodeEdge>::CouplingSdtSubNodeType edges;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariablesDefault();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// TrafficControl
class TrafficControl : public FlexSimObject
{
public:

TreeNode* node_v_requests;
#define v_requests node_v_requests->safedatafloat()[0]
TreeNode* node_v_numberactive;
#define v_numberactive node_v_numberactive->safedatafloat()[0]
TreeNode* node_v_maxactive;
#define v_maxactive node_v_maxactive->safedatafloat()[0]
TreeNode* node_v_controlmode;
#define v_controlmode node_v_controlmode->safedatafloat()[0]
TreeNode* node_v_netnodemembers;
#define v_netnodemembers node_v_netnodemembers->safedatafloat()[0]
TreeNode* node_v_modetable;
#define v_modetable node_v_modetable->safedatafloat()[0]
TreeNode* node_v_curtablemode;
#define v_curtablemode node_v_curtablemode->safedatafloat()[0]
TreeNode* node_v_searchbestmode;
#define v_searchbestmode node_v_searchbestmode->safedatafloat()[0]
TreeNode* node_v_speedtable;
#define v_speedtable node_v_speedtable->safedatafloat()[0]
TreeNode* node_v_entrytrigger;
TreeNode* node_v_exittrigger;
TreeNode* node_v_requesttrigger;

// c++ member functions

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double requestEntry(treenode reqnode, NetworkNode* tonetnode, int nextport, int fromrank, int torank);

FS_CONTENT_DLL_FUNC virtual double leaveArea(treenode reqnode, treenode networknode);

FS_CONTENT_DLL_FUNC virtual double searchModeTable(int fromrank, int torank);

FS_CONTENT_DLL_FUNC virtual double findDifferentTableMatch(int fromrank, int torank);

FS_CONTENT_DLL_FUNC virtual double allowNewRequests();

FS_CONTENT_DLL_FUNC virtual double checkRowForConnection(int row, int fromrank, int torank);

FS_CONTENT_DLL_FUNC double modeError(int fromrank, int torank);

FS_CONTENT_DLL_FUNC unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC virtual double forceReceive(treenode reqnode, treenode netnode);

FS_CONTENT_DLL_FUNC virtual double abortRequest(treenode reqnode);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onKeyedClick(treenode view, int code, char key);

FS_CONTENT_DLL_FUNC double saveState();

FS_CONTENT_DLL_FUNC double loadState();

FS_CONTENT_DLL_FUNC static float saveTCRequestState(treenode reqnode);

FS_CONTENT_DLL_FUNC static float loadTCRequestState(treenode reqnode);

FS_CONTENT_DLL_FUNC virtual double getSpeedMultiple();

FS_CONTENT_DLL_FUNC virtual double copyVariables(treenode otherobject);

FS_CONTENT_DLL_FUNC virtual double info(int info, double _a, double _b);

FS_CONTENT_DLL_FUNC virtual void bindEvents();


// c++ attributes
struct travelrequest{treenode requester;short opnum; short fromnode; short destnode; treenode traveldata;};

int matchingcolumn;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidTicker
class FluidTicker : public FlexSimObject
{
public:

TreeNode* node_v_ticktime;
#define v_ticktime node_v_ticktime->safedatafloat()[0]
TreeNode* node_v_objectlist;
#define v_objectlist node_v_objectlist->safedatafloat()[0]
TreeNode* node_v_maxcomponents;
#define v_maxcomponents node_v_maxcomponents->safedatafloat()[0]
TreeNode* node_v_lasttick;
#define v_lasttick node_v_lasttick->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double defines();

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double sortObjectList();

FS_CONTENT_DLL_FUNC double quickSort(treenode table, int low, int high);

FS_CONTENT_DLL_FUNC double assignValue(treenode obj);

FS_CONTENT_DLL_FUNC treenode getLink(treenode obj);

FS_CONTENT_DLL_FUNC double doTick();

FS_CONTENT_DLL_FUNC double prepareForTick();

FS_CONTENT_DLL_FUNC double moveFluid();

FS_CONTENT_DLL_FUNC double completeTick();

FS_CONTENT_DLL_FUNC double getTransferAmount(treenode upstreamobj, treenode downstreamobj, int outportnum);

FS_CONTENT_DLL_FUNC static treenode findDefaultTicker();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidObject
class FluidObject : public FlexSimObject
{
public:

TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]
TreeNode* node_v_curcontent;
#define v_curcontent node_v_curcontent->safedatafloat()[0]
TreeNode* node_v_productid;
#define v_productid node_v_productid->safedatafloat()[0]
TreeNode* node_v_maxobjectinrate;
#define v_maxobjectinrate node_v_maxobjectinrate->safedatafloat()[0]
TreeNode* node_v_maxportinrate;
#define v_maxportinrate node_v_maxportinrate->safedatafloat()[0]
TreeNode* node_v_portinratescalefactors;
#define v_portinratescalefactors node_v_portinratescalefactors->safedatafloat()[0]
TreeNode* node_v_maxobjectoutrate;
#define v_maxobjectoutrate node_v_maxobjectoutrate->safedatafloat()[0]
TreeNode* node_v_maxportoutrate;
#define v_maxportoutrate node_v_maxportoutrate->safedatafloat()[0]
TreeNode* node_v_portoutratescalefactors;
#define v_portoutratescalefactors node_v_portoutratescalefactors->safedatafloat()[0]
TreeNode* node_v_lastinputamount;
#define v_lastinputamount node_v_lastinputamount->safedatafloat()[0]
TreeNode* node_v_lastoutputamount;
#define v_lastoutputamount node_v_lastoutputamount->safedatafloat()[0]
TreeNode* node_v_barlocx;
#define v_barlocx node_v_barlocx->safedatafloat()[0]
TreeNode* node_v_barlocy;
#define v_barlocy node_v_barlocy->safedatafloat()[0]
TreeNode* node_v_barlocz;
#define v_barlocz node_v_barlocz->safedatafloat()[0]
TreeNode* node_v_barrotx;
#define v_barrotx node_v_barrotx->safedatafloat()[0]
TreeNode* node_v_barroty;
#define v_barroty node_v_barroty->safedatafloat()[0]
TreeNode* node_v_barrotz;
#define v_barrotz node_v_barrotz->safedatafloat()[0]
TreeNode* node_v_barsizex;
#define v_barsizex node_v_barsizex->safedatafloat()[0]
TreeNode* node_v_barsizey;
#define v_barsizey node_v_barsizey->safedatafloat()[0]
TreeNode* node_v_barsizez;
#define v_barsizez node_v_barsizez->safedatafloat()[0]
TreeNode* node_v_barcylinder;
#define v_barcylinder node_v_barcylinder->safedatafloat()[0]
TreeNode* node_v_drawbar;
#define v_drawbar node_v_drawbar->safedatafloat()[0]
TreeNode* node_v_objectstats;
#define v_objectstats node_v_objectstats->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double onDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC double connectToTicker();

FS_CONTENT_DLL_FUNC double connectToTicker(treenode ticker);

FS_CONTENT_DLL_FUNC double copyProductId(treenode upstreamobj,double amount);

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);

FS_CONTENT_DLL_FUNC virtual double moveMaterialIn(double amount, int port);

FS_CONTENT_DLL_FUNC virtual double moveMaterialOut(double amount, int port);

FS_CONTENT_DLL_FUNC virtual double emptyObject();

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidTank
class FluidTank : public FluidObject
{
public:

TreeNode* node_v_lowmark;
#define v_lowmark node_v_lowmark->safedatafloat()[0]
TreeNode* node_v_midmark;
#define v_midmark node_v_midmark->safedatafloat()[0]
TreeNode* node_v_highmark;
#define v_highmark node_v_highmark->safedatafloat()[0]
TreeNode* node_v_lowmarktrigger;
TreeNode* node_v_midmarktrigger;
TreeNode* node_v_highmarktrigger;
TreeNode* node_v_adjustinputrates;
TreeNode* node_v_adjustoutputrates;
TreeNode* node_v_emptytrigger;
TreeNode* node_v_fulltrigger;
TreeNode* node_v_initialcontent;
#define v_initialcontent node_v_initialcontent->safedatafloat()[0]
TreeNode* node_v_initialproductid;
#define v_initialproductid node_v_initialproductid->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidGenerator
class FluidGenerator : public FluidObject
{
public:

TreeNode* node_v_refillmode;
#define v_refillmode node_v_refillmode->safedatafloat()[0]
TreeNode* node_v_refilldelay;
#define v_refilldelay node_v_refilldelay->safedatafloat()[0]
TreeNode* node_v_refillrate;
#define v_refillrate node_v_refillrate->safedatafloat()[0]
TreeNode* node_v_emptytrigger;
TreeNode* node_v_fulltrigger;
TreeNode* node_v_initialcontent;
#define v_initialcontent node_v_initialcontent->safedatafloat()[0]
TreeNode* node_v_initialproductid;
#define v_initialproductid node_v_initialproductid->safedatafloat()[0]
TreeNode* node_v_adjustoutputrates;

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidTerminator
class FluidTerminator : public FluidObject
{
public:

TreeNode* node_v_adjustinputrates;
TreeNode* node_v_totalinput;
#define v_totalinput node_v_totalinput->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double materialMovedIn(double amount, int port);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidMixer
class FluidMixer : public FluidObject
{
public:

TreeNode* node_v_curstep;
#define v_curstep node_v_curstep->safedatafloat()[0]
TreeNode* node_v_targetproductid;
#define v_targetproductid node_v_targetproductid->safedatafloat()[0]
TreeNode* node_v_steptable;
#define v_steptable node_v_steptable->safedatafloat()[0]
TreeNode* node_v_recipetable;
#define v_recipetable node_v_recipetable->safedatafloat()[0]
TreeNode* node_v_currentsteptable;
#define v_currentsteptable node_v_currentsteptable->safedatafloat()[0]
TreeNode* node_v_portcolortable;
#define v_portcolortable node_v_portcolortable->safedatafloat()[0]
TreeNode* node_v_adjustoutputrates;
TreeNode* node_v_emptytrigger;
TreeNode* node_v_beforedelaytrigger;
TreeNode* node_v_afterdelaytrigger;
TreeNode* node_v_indelay;
#define v_indelay node_v_indelay->safedatafloat()[0]
TreeNode* node_v_collecting;
#define v_collecting node_v_collecting->safedatafloat()[0]
TreeNode* node_v_usermaxoutrate;
#define v_usermaxoutrate node_v_usermaxoutrate->safedatafloat()[0]
TreeNode* node_v_batchstarttime;
#define v_batchstarttime node_v_batchstarttime->safedatafloat()[0]
TreeNode* node_v_totalbatchtime;
#define v_totalbatchtime node_v_totalbatchtime->safedatafloat()[0]
TreeNode* node_v_numbatches;
#define v_numbatches node_v_numbatches->safedatafloat()[0]
TreeNode* node_v_avgbatchtime;
#define v_avgbatchtime node_v_avgbatchtime->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double onDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double moveMaterialIn(double amount, int port);

FS_CONTENT_DLL_FUNC virtual double emptyObject();

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidBlender
class FluidBlender : public FluidObject
{
public:

TreeNode* node_v_maxtotalinrate;
#define v_maxtotalinrate node_v_maxtotalinrate->safedatafloat()[0]
TreeNode* node_v_targetproductid;
#define v_targetproductid node_v_targetproductid->safedatafloat()[0]
TreeNode* node_v_recipetable;
#define v_recipetable node_v_recipetable->safedatafloat()[0]
TreeNode* node_v_adjustoutputrates;
TreeNode* node_v_curoutrate;
#define v_curoutrate node_v_curoutrate->safedatafloat()[0]
TreeNode* node_v_avgoutrate;
#define v_avgoutrate node_v_avgoutrate->safedatafloat()[0]
TreeNode* node_v_numupdates;
#define v_numupdates node_v_numupdates->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidSplitter
class FluidSplitter : public FluidObject
{
public:

TreeNode* node_v_maxtotaloutrate;
#define v_maxtotaloutrate node_v_maxtotaloutrate->safedatafloat()[0]
TreeNode* node_v_recipetable;
#define v_recipetable node_v_recipetable->safedatafloat()[0]
TreeNode* node_v_adjustinputrates;
TreeNode* node_v_curinrate;
#define v_curinrate node_v_curinrate->safedatafloat()[0]
TreeNode* node_v_avginrate;
#define v_avginrate node_v_avginrate->safedatafloat()[0]
TreeNode* node_v_numupdates;
#define v_numupdates node_v_numupdates->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidPipe
class FluidPipe : public FluidObject
{
public:

TreeNode* node_v_maxflowrate;
#define v_maxflowrate node_v_maxflowrate->safedatafloat()[0]
TreeNode* node_v_tablerate;
#define v_tablerate node_v_tablerate->safedatafloat()[0]
TreeNode* node_v_transfertime;
#define v_transfertime node_v_transfertime->safedatafloat()[0]
TreeNode* node_v_flowmode;
#define v_flowmode node_v_flowmode->safedatafloat()[0]
TreeNode* node_v_accumulated;
#define v_accumulated node_v_accumulated->safedatafloat()[0]
TreeNode* node_v_futureoutputrates;
#define v_futureoutputrates node_v_futureoutputrates->safedatafloat()[0]
TreeNode* node_v_adjustinputrates;
TreeNode* node_v_adjustoutputrates;
TreeNode* node_v_emptytrigger;
TreeNode* node_v_fulltrigger;
TreeNode* node_v_pipesections;
#define v_pipesections node_v_pipesections->safedatafloat()[0]
TreeNode* node_v_curoutrate;
#define v_curoutrate node_v_curoutrate->safedatafloat()[0]
TreeNode* node_v_avgoutrate;
#define v_avgoutrate node_v_avgoutrate->safedatafloat()[0]
TreeNode* node_v_numupdates;
#define v_numupdates node_v_numupdates->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double drawPipe(double color1, double color2, double color3);

FS_CONTENT_DLL_FUNC double drawConveyor(double color1, double color2, double color3);

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double emptyObject();

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidProcessor
class FluidProcessor : public FluidObject
{
public:

TreeNode* node_v_maxflowrate;
#define v_maxflowrate node_v_maxflowrate->safedatafloat()[0]
TreeNode* node_v_tablerate;
#define v_tablerate node_v_tablerate->safedatafloat()[0]
TreeNode* node_v_transfertime;
#define v_transfertime node_v_transfertime->safedatafloat()[0]
TreeNode* node_v_loss;
#define v_loss node_v_loss->safedatafloat()[0]
TreeNode* node_v_accumulated;
#define v_accumulated node_v_accumulated->safedatafloat()[0]
TreeNode* node_v_futureoutputrates;
#define v_futureoutputrates node_v_futureoutputrates->safedatafloat()[0]
TreeNode* node_v_receiveportnumber;
TreeNode* node_v_destinationportnumber;
TreeNode* node_v_emptytrigger;
TreeNode* node_v_fulltrigger;
TreeNode* node_v_curoutrate;
#define v_curoutrate node_v_curoutrate->safedatafloat()[0]
TreeNode* node_v_avgoutrate;
#define v_avgoutrate node_v_avgoutrate->safedatafloat()[0]
TreeNode* node_v_numupdates;
#define v_numupdates node_v_numupdates->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double emptyObject();

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidObject2
class FluidObject2 : public FixedResource
{
public:

TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]
TreeNode* node_v_curcontent;
#define v_curcontent node_v_curcontent->safedatafloat()[0]
TreeNode* node_v_productid;
#define v_productid node_v_productid->safedatafloat()[0]
TreeNode* node_v_maxobjectinrate;
#define v_maxobjectinrate node_v_maxobjectinrate->safedatafloat()[0]
TreeNode* node_v_maxportinrate;
#define v_maxportinrate node_v_maxportinrate->safedatafloat()[0]
TreeNode* node_v_portinratescalefactors;
#define v_portinratescalefactors node_v_portinratescalefactors->safedatafloat()[0]
TreeNode* node_v_maxobjectoutrate;
#define v_maxobjectoutrate node_v_maxobjectoutrate->safedatafloat()[0]
TreeNode* node_v_maxportoutrate;
#define v_maxportoutrate node_v_maxportoutrate->safedatafloat()[0]
TreeNode* node_v_portoutratescalefactors;
#define v_portoutratescalefactors node_v_portoutratescalefactors->safedatafloat()[0]
TreeNode* node_v_lastinputamount;
#define v_lastinputamount node_v_lastinputamount->safedatafloat()[0]
TreeNode* node_v_lastoutputamount;
#define v_lastoutputamount node_v_lastoutputamount->safedatafloat()[0]
TreeNode* node_v_barlocx;
#define v_barlocx node_v_barlocx->safedatafloat()[0]
TreeNode* node_v_barlocy;
#define v_barlocy node_v_barlocy->safedatafloat()[0]
TreeNode* node_v_barlocz;
#define v_barlocz node_v_barlocz->safedatafloat()[0]
TreeNode* node_v_barrotx;
#define v_barrotx node_v_barrotx->safedatafloat()[0]
TreeNode* node_v_barroty;
#define v_barroty node_v_barroty->safedatafloat()[0]
TreeNode* node_v_barrotz;
#define v_barrotz node_v_barrotz->safedatafloat()[0]
TreeNode* node_v_barsizex;
#define v_barsizex node_v_barsizex->safedatafloat()[0]
TreeNode* node_v_barsizey;
#define v_barsizey node_v_barsizey->safedatafloat()[0]
TreeNode* node_v_barsizez;
#define v_barsizez node_v_barsizez->safedatafloat()[0]
TreeNode* node_v_barcylinder;
#define v_barcylinder node_v_barcylinder->safedatafloat()[0]
TreeNode* node_v_drawbar;
#define v_drawbar node_v_drawbar->safedatafloat()[0]
TreeNode* node_v_objectstats;
#define v_objectstats node_v_objectstats->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onOutOpen(int port);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double onDraw(treenode view);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC double copyProductId(treenode upstreamobj,double amount);

FS_CONTENT_DLL_FUNC double connectToTicker();

FS_CONTENT_DLL_FUNC double connectToTicker(treenode ticker);

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double emptyObject();

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);

FS_CONTENT_DLL_FUNC virtual double moveMaterialIn(double amount, int port);

FS_CONTENT_DLL_FUNC virtual double moveMaterialOut(double amount, int port);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC virtual double stopObjectAndSetState(int stopstate, int stateprofile DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double resumeObject();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// ItemToFluid
class ItemToFluid : public FluidObject2
{
public:

TreeNode* node_v_fluidunitsperdiscrete;
#define v_fluidunitsperdiscrete node_v_fluidunitsperdiscrete->safedatafloat()[0]
TreeNode* node_v_chunksize;
#define v_chunksize node_v_chunksize->safedatafloat()[0]
TreeNode* node_v_recycle;
#define v_recycle node_v_recycle->safedatafloat()[0]
TreeNode* node_v_initialproductid;
#define v_initialproductid node_v_initialproductid->safedatafloat()[0]
TreeNode* node_v_adjustoutputrates;
TreeNode* node_v_emptytrigger;
TreeNode* node_v_fulltrigger;

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onReceive(treenode item, int port);

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidToItem
class FluidToItem : public FluidObject2
{
public:

TreeNode* node_v_flowitemclass;
#define v_flowitemclass node_v_flowitemclass->safedatafloat()[0]
TreeNode* node_v_flowitemname;
TreeNode* node_v_flowitemtype;
#define v_flowitemtype node_v_flowitemtype->safedatafloat()[0]
TreeNode* node_v_fluidunitsperdiscrete;
#define v_fluidunitsperdiscrete node_v_fluidunitsperdiscrete->safedatafloat()[0]
TreeNode* node_v_chunksize;
#define v_chunksize node_v_chunksize->safedatafloat()[0]
TreeNode* node_v_creationtrigger;
TreeNode* node_v_flowitembin;
#define v_flowitembin node_v_flowitembin->safedatafloat()[0]
TreeNode* node_v_adjustinputrates;

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC double onReset();

FS_CONTENT_DLL_FUNC double onTimerEvent(treenode involved, int code, char *datastr);

FS_CONTENT_DLL_FUNC double onSend(treenode item, int port);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double generateItem(double curitemtype, string itemname);

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);


// c++ attributes
treenode flowitemtocreate;

int itemsmade;


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// FluidConveyor
class FluidConveyor : public FluidObject
{
public:

TreeNode* node_v_numberofslices;
#define v_numberofslices node_v_numberofslices->safedatafloat()[0]
TreeNode* node_v_slicewidth;
#define v_slicewidth node_v_slicewidth->safedatafloat()[0]
TreeNode* node_v_outputwidth;
#define v_outputwidth node_v_outputwidth->safedatafloat()[0]
TreeNode* node_v_centerlineoffset;
#define v_centerlineoffset node_v_centerlineoffset->safedatafloat()[0]
TreeNode* node_v_stats;
#define v_stats node_v_stats->safedatafloat()[0]
TreeNode* node_v_sidewallheight;
#define v_sidewallheight node_v_sidewallheight->safedatafloat()[0]
TreeNode* node_v_legheight;
#define v_legheight node_v_legheight->safedatafloat()[0]
TreeNode* node_v_layout_aux;
#define v_layout_aux node_v_layout_aux->safedatafloat()[0]
TreeNode* node_v_previouslayout;
#define v_previouslayout node_v_previouslayout->safedatafloat()[0]
TreeNode* node_v_materialcolor;
#define v_materialcolor node_v_materialcolor->safedatafloat()[0]
TreeNode* node_v_direction_default;
#define v_direction_default node_v_direction_default->safedatafloat()[0]
TreeNode* node_v_direction_current;
#define v_direction_current node_v_direction_current->safedatafloat()[0]
TreeNode* node_v_direction_target;
#define v_direction_target node_v_direction_target->safedatafloat()[0]
TreeNode* node_v_speed_default;
#define v_speed_default node_v_speed_default->safedatafloat()[0]
TreeNode* node_v_speed_current;
#define v_speed_current node_v_speed_current->safedatafloat()[0]
TreeNode* node_v_speed_target;
#define v_speed_target node_v_speed_target->safedatafloat()[0]
TreeNode* node_v_acceleration_default;
#define v_acceleration_default node_v_acceleration_default->safedatafloat()[0]
TreeNode* node_v_acceleration_current;
#define v_acceleration_current node_v_acceleration_current->safedatafloat()[0]
TreeNode* node_v_angleofrepose;
#define v_angleofrepose node_v_angleofrepose->safedatafloat()[0]
TreeNode* node_v_reposerate;
#define v_reposerate node_v_reposerate->safedatafloat()[0]
TreeNode* node_v_reposeend;
#define v_reposeend node_v_reposeend->safedatafloat()[0]
TreeNode* node_v_maxsliceheightdifference;
#define v_maxsliceheightdifference node_v_maxsliceheightdifference->safedatafloat()[0]
TreeNode* node_v_endslicefraction;
#define v_endslicefraction node_v_endslicefraction->safedatafloat()[0]
TreeNode* node_v_fallingslices;
#define v_fallingslices node_v_fallingslices->safedatafloat()[0]
TreeNode* node_v_slicesrotated;
#define v_slicesrotated node_v_slicesrotated->safedatafloat()[0]
TreeNode* node_v_allowspillage;
#define v_allowspillage node_v_allowspillage->safedatafloat()[0]
TreeNode* node_v_spillage;
#define v_spillage node_v_spillage->safedatafloat()[0]
TreeNode* node_v_lastspillageamount;
#define v_lastspillageamount node_v_lastspillageamount->safedatafloat()[0]
TreeNode* node_v_inputs;
#define v_inputs node_v_inputs->safedatafloat()[0]
TreeNode* node_v_outputs;
#define v_outputs node_v_outputs->safedatafloat()[0]
TreeNode* node_v_outputs_aux;
#define v_outputs_aux node_v_outputs_aux->safedatafloat()[0]
TreeNode* node_v_sensors;
#define v_sensors node_v_sensors->safedatafloat()[0]
TreeNode* node_v_conveyorcontent;
#define v_conveyorcontent node_v_conveyorcontent->safedatafloat()[0]
TreeNode* node_v_conveyorinfo;
#define v_conveyorinfo node_v_conveyorinfo->safedatafloat()[0]
TreeNode* node_v_lowmarktrigger;
TreeNode* node_v_midmarktrigger;
TreeNode* node_v_highmarktrigger;
TreeNode* node_v_emptytrigger;
TreeNode* node_v_fulltrigger;
TreeNode* node_v_initialcontent;
#define v_initialcontent node_v_initialcontent->safedatafloat()[0]
TreeNode* node_v_initialproductid;
#define v_initialproductid node_v_initialproductid->safedatafloat()[0]
TreeNode* node_v_maxcontent;
#define v_maxcontent node_v_maxcontent->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onCreate(double xloc, double yloc, double zloc, int iscopy DEFAULTZERO);

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double updateConveyorInfo(double slicewidth, double leftend_y, double rightend_y);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC virtual double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double sensorCheck();

FS_CONTENT_DLL_FUNC double rotateSlices();

FS_CONTENT_DLL_FUNC double materialRepose(double reposerate, int onlyfalling);

FS_CONTENT_DLL_FUNC virtual double prepareForTick(double ticktime);

FS_CONTENT_DLL_FUNC virtual double completeTick(double ticktime);

FS_CONTENT_DLL_FUNC int updateInputs();

FS_CONTENT_DLL_FUNC int updateOutputs();

FS_CONTENT_DLL_FUNC int updateSensors();

FS_CONTENT_DLL_FUNC virtual double emptyObject();

FS_CONTENT_DLL_FUNC virtual double updateStats(double ticktime);

FS_CONTENT_DLL_FUNC double statsFunction(double ticktime);

FS_CONTENT_DLL_FUNC virtual double moveMaterialIn(double amount, int port);

FS_CONTENT_DLL_FUNC virtual double moveMaterialOut(double amount, int port);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// LineController
class LineController : public TaskExecuter
{
public:

TreeNode* node_v_productdata;
#define v_productdata node_v_productdata->safedatafloat()[0]
TreeNode* node_v_changeover;
#define v_changeover node_v_changeover->safedatafloat()[0]
TreeNode* node_v_clearcheck;
#define v_clearcheck node_v_clearcheck->safedatafloat()[0]
TreeNode* node_v_startjobtrigger;
TreeNode* node_v_cleartrigger;
TreeNode* node_v_startjob;
TreeNode* node_v_finishjob;
TreeNode* node_v_curprodtype;
#define v_curprodtype node_v_curprodtype->safedatafloat()[0]
TreeNode* node_v_target;
#define v_target node_v_target->safedatafloat()[0]
TreeNode* node_v_starttime;
#define v_starttime node_v_starttime->safedatafloat()[0]
TreeNode* node_v_totaloutput;
#define v_totaloutput node_v_totaloutput->safedatafloat()[0]
TreeNode* node_v_netoutput;
#define v_netoutput node_v_netoutput->safedatafloat()[0]
TreeNode* node_v_members;
#define v_members node_v_members->safedatafloat()[0]
TreeNode* node_v_visibleconnections;
#define v_visibleconnections node_v_visibleconnections->safedatafloat()[0]
TreeNode* node_v_cleaning;
#define v_cleaning node_v_cleaning->safedatafloat()[0]
TreeNode* node_v_targetreachedtrigger;
TreeNode* node_v_changeovercompletetrigger;
TreeNode* node_v_forceclearout;
#define v_forceclearout node_v_forceclearout->safedatafloat()[0]
TreeNode* node_v_clearouttime;
#define v_clearouttime node_v_clearouttime->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC virtual Variant onMessage(treenode fromobject, const Variant& par1, const Variant& par2, const Variant& par3);

FS_CONTENT_DLL_FUNC double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double onKeyedClick(treenode view, int code, char key);

FS_CONTENT_DLL_FUNC virtual double updateLocations();

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double startSimulation();

FS_CONTENT_DLL_FUNC double beginRun(int prodtype, double target);

FS_CONTENT_DLL_FUNC double endChangeOver();

FS_CONTENT_DLL_FUNC double endOfLineCheck(treenode lineobj, double objoutput, int sendinglast);

FS_CONTENT_DLL_FUNC double endRun();

FS_CONTENT_DLL_FUNC double gotoNextRun();

FS_CONTENT_DLL_FUNC double clearOut();

FS_CONTENT_DLL_FUNC virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();

FS_CONTENT_DLL_FUNC double validateData();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// SystemController
class SystemController : public Dispatcher
{
public:

TreeNode* node_v_masterschedule;
#define v_masterschedule node_v_masterschedule->safedatafloat()[0]
TreeNode* node_v_inactivetasks;
#define v_inactivetasks node_v_inactivetasks->safedatafloat()[0]
TreeNode* node_v_lineavailabletrigger;
TreeNode* node_v_starttimetrigger;
TreeNode* node_v_productcolors;
#define v_productcolors node_v_productcolors->safedatafloat()[0]
TreeNode* node_v_drawindicators;
#define v_drawindicators node_v_drawindicators->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC virtual double onReset();

FS_CONTENT_DLL_FUNC virtual double onTimerEvent(treenode involved, int code, char *strdata);

FS_CONTENT_DLL_FUNC double onOutOpen(int port);

FS_CONTENT_DLL_FUNC virtual double onDraw(treenode view);

FS_CONTENT_DLL_FUNC double resetVariables();

FS_CONTENT_DLL_FUNC double startSimulation();

FS_CONTENT_DLL_FUNC double getAdditionalColumn(int row, int col);

FS_CONTENT_DLL_FUNC double nextTime();

FS_CONTENT_DLL_FUNC double onResourceAvailable(treenode linecontrol, int port);

FS_CONTENT_DLL_FUNC virtual unsigned int getClassType();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// ScoreCard
class ScoreCard : public FlexSimObject
{
public:

TreeNode* node_v_title;
TreeNode* node_v_values;
#define v_values node_v_values->safedatafloat()[0]
TreeNode* node_v_textsize;
#define v_textsize node_v_textsize->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double onDraw(treenode view);


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

// Report
class Report : public ObjectDataType
{
public:

TreeNode* node_v_starttime;
#define v_starttime node_v_starttime->safedatafloat()[0]
TreeNode* node_v_endtime;
#define v_endtime node_v_endtime->safedatafloat()[0]
TreeNode* node_v_interval;
#define v_interval node_v_interval->safedatafloat()[0]
TreeNode* node_v_columns;
#define v_columns node_v_columns->safedatafloat()[0]
TreeNode* node_v_data;
#define v_data node_v_data->safedatafloat()[0]
TreeNode* node_v_width;
#define v_width node_v_width->safedatafloat()[0]
TreeNode* node_v_height;
#define v_height node_v_height->safedatafloat()[0]
TreeNode* node_v_cellwidth;
#define v_cellwidth node_v_cellwidth->safedatafloat()[0]
TreeNode* node_v_cellheight;
#define v_cellheight node_v_cellheight->safedatafloat()[0]

// c++ member functions

FS_CONTENT_DLL_FUNC double updateTable();


// System

FS_CONTENT_DLL_FUNC virtual void bindVariables();

FS_CONTENT_DLL_FUNC static int getAllocSize();
};

#endif

