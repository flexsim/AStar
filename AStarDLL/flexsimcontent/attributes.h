

// COPYRIGHT 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

// object containers
DECLARE_ATTRIBUTE(0,behaviour,"Behaviour function lists container", 0)
DECLARE_ATTRIBUTE(0,cppfunctions,"c++ functions list", 0)
DECLARE_ATTRIBUTE(0,cppvariables,"c++ variables container", 0)
DECLARE_ATTRIBUTE(0,eventfunctions,"Eventfunctions list", 0)
DECLARE_ATTRIBUTE(0,userfunctions,"Userfunctions list", 0)
DECLARE_ATTRIBUTE(0,classes,"Classes list", 0)
DECLARE_ATTRIBUTE(0,superclasses,"Superclasses list", 0)
DECLARE_ATTRIBUTE(0,connections,"Port connection lists container", 0)
DECLARE_ATTRIBUTE(0,connectionsin,"In-port connections list", 1)
DECLARE_ATTRIBUTE(0,connectionsout,"Out-port connections list", 1)
DECLARE_ATTRIBUTE(0,connectionscenter,"Center-port connections list", 1)
DECLARE_ATTRIBUTE(0,itemtype,"Itemtype", 1)
DECLARE_ATTRIBUTE(0,labels,"Labels list", 0)
DECLARE_ATTRIBUTE(0,variables,"Variables container", 0)
DECLARE_ATTRIBUTE(0,listeners,"Listeners", 0)

// object events
DECLARE_ATTRIBUTE(0,OnReset,"Function node executed on reset", 0)
DECLARE_ATTRIBUTE(0,OnMessage,"Function node executed on message", 0)
DECLARE_ATTRIBUTE(0,OnTimerEvent,"Function node executed on timer event", 0)
DECLARE_ATTRIBUTE(0,OnDraw,"Function node executed on scene draw for that object", 0)
DECLARE_ATTRIBUTE(0,OnPreDraw,"Function node executed on before scene draw for that object", 0)
DECLARE_ATTRIBUTE(0,OnDrawPlanar,"Function node executed on scene draw for that object", 0)
DECLARE_ATTRIBUTE(0,OnPreDrawPlanar,"Function node executed on scene draw for that object", 0)
DECLARE_ATTRIBUTE(0,OnInOpen,"Function node executed on passthrough on input port", 0)
DECLARE_ATTRIBUTE(0,OnOutOpen,"Function node executed on passthrough on output port", 0)
DECLARE_ATTRIBUTE(0,OnReceive,"Function node executed on accepting an object", 0)
DECLARE_ATTRIBUTE(0,OnSend,"Function node executed on giving an object", 0)
DECLARE_ATTRIBUTE(0,OnEntering,"Function node executed on going into an object", 0)
DECLARE_ATTRIBUTE(0,OnExiting,"Function node executed on leaving an object", 0)
DECLARE_ATTRIBUTE(0,OnCompile,"Function node executed on compilation complete", 0)
DECLARE_ATTRIBUTE(0,OnCreate,"Function node executed on creation", 0)
DECLARE_ATTRIBUTE(0,OnDestroy,"Function node executed on destruction", 0)
DECLARE_ATTRIBUTE(0,OnUndo,"Attribute fired on content-defined undo action", 0)
DECLARE_ATTRIBUTE(0,OnClick,"Function node executed on getting a mouse button event", 0)
DECLARE_ATTRIBUTE(0,OnRunStart,"Function node executed on replication start", 0)
DECLARE_ATTRIBUTE(0,OnRunWarm,"Function node executed on replication warm up", 0)
DECLARE_ATTRIBUTE(0,OnRunEnd,"Function node executed on replication end", 0)
DECLARE_ATTRIBUTE(0,OnListen,"Function node executed on any event happening: after dispatch, when event has been removed", 0)
DECLARE_ATTRIBUTE(0,OnPreListen,"Function node executed on any event happening: before dispatch, when event is still in list", 0)
DECLARE_ATTRIBUTE(0,OnStateChange,"Function node executed when object state changes", 0)
DECLARE_ATTRIBUTE(1,OnDrag,"Node function executed on object drag out from an icongrid, or when moving/resizing", 0)

// object stats
DECLARE_ATTRIBUTE(0,stats, "Parent node that holds various stats", 0)
DECLARE_ATTRIBUTE(0,state_current,"Current state index", 0)
DECLARE_ATTRIBUTE(0,state_since,"Time of last state update", 0)
DECLARE_ATTRIBUTE(0,state_profile,"Cumulative state durations container", 0)
DECLARE_ATTRIBUTE(0,state_profiles,"Cumulative state durations container", 0)
DECLARE_ATTRIBUTE(0,stats_content,"Content value", 0)
DECLARE_ATTRIBUTE(0,stats_staytime,"Last staytime value", 0)
DECLARE_ATTRIBUTE(0,stats_contentmin,"Minimum recorded content", 1)
DECLARE_ATTRIBUTE(0,stats_contentmax,"Maximum recorded content", 1)
DECLARE_ATTRIBUTE(0,stats_contentavg,"Average recorded content", 1)
DECLARE_ATTRIBUTE(0,stats_contentupdates,"Number of content updates", 1)
DECLARE_ATTRIBUTE(0,stats_contentsince,"Time of last content update", 1)
DECLARE_ATTRIBUTE(0,stats_contentgraph,"Content history data container", 0)
DECLARE_ATTRIBUTE(0,stats_contentgraphmaxpoints,"Maximum content hsitory size", 1)
DECLARE_ATTRIBUTE(0,stats_staytimemin,"Minimum recorded staytime", 0)
DECLARE_ATTRIBUTE(0,stats_staytimemax,"Maximum recorded staytime", 0)
DECLARE_ATTRIBUTE(0,stats_staytimeavg,"Average recorded staytime", 0)
DECLARE_ATTRIBUTE(0,stats_staytimeupdates,"Number of staytime updates", 0)
DECLARE_ATTRIBUTE(0,stats_staytimesince,"Time of last recorded staytime update", 0)
DECLARE_ATTRIBUTE(0,stats_staytimegraph,"History of staytime data container", 0)
DECLARE_ATTRIBUTE(0,stats_staytimegraphmaxpoints,"Maximum staytime history size", 0)
DECLARE_ATTRIBUTE(0,stats_staytimehisto,"Staytime histogram data container", 0)
DECLARE_ATTRIBUTE(0,stats_throughput,"Throughput count", 0)
DECLARE_ATTRIBUTE(0,stats_lastmovetime,"Time of last move", 1)
DECLARE_ATTRIBUTE(0,stats_creationtime,"Creation time", 1)
DECLARE_ATTRIBUTE(0,stats_input,"Input count", 0)
DECLARE_ATTRIBUTE(0,stats_output,"Output count", 0)
DECLARE_ATTRIBUTE(0,stream,"Object unique random stream", 1)

// object spatial and visual
DECLARE_ATTRIBUTE(0,spatialx,"x co-ordinate", 1)
DECLARE_ATTRIBUTE(0,spatialy,"y co-ordinate", 1)
DECLARE_ATTRIBUTE(0,spatialz,"z co-ordinate", 1)
DECLARE_ATTRIBUTE(1,spatialsx,"x scaling", 1)
DECLARE_ATTRIBUTE(1,spatialsy,"y scaling", 1)
DECLARE_ATTRIBUTE(1,spatialsz,"z scaling", 1)
DECLARE_ATTRIBUTE(0,spatialrx,"about-x rotation", 1)
DECLARE_ATTRIBUTE(0,spatialry,"about-y rotation", 1)
DECLARE_ATTRIBUTE(0,spatialrz,"about-z rotation", 1)
DECLARE_ATTRIBUTE(0,offsetx,"Adjustment factor", 1)
DECLARE_ATTRIBUTE(0,offsety,"Adjustment factor", 1)
DECLARE_ATTRIBUTE(0,offsetz,"Adjustment factor", 1)
DECLARE_ATTRIBUTE(0,offsetrx,"Adjustment factor", 1)
DECLARE_ATTRIBUTE(0,offsetry,"Adjustment factor", 1)
DECLARE_ATTRIBUTE(0,offsetrz,"Adjustment factor", 1)
DECLARE_ATTRIBUTE(1,offsetsx,"Adjustment factor", 1)
DECLARE_ATTRIBUTE(1,offsetsy,"Adjustment factor", 1)
DECLARE_ATTRIBUTE(1,offsetsz,"Adjustment factor", 1)
DECLARE_ATTRIBUTE(0,color,"Contains red, green and blue nodes specifying color", 0)
DECLARE_ATTRIBUTE(0,centroid,"Rotate about center of bounding cuboid instead of the cuboid origin", 1)
DECLARE_ATTRIBUTE(0,drawflags,"Bitwise flags for draw settings: 0x1 = one-sided, 0x2 two-sided, 0x4 = no depth test, 0x8 = reflective, 0x10 = luminous", 1)

// object media
DECLARE_ATTRIBUTE(0,imageobject,"Texture to be used on the object's 3D model", 0)
DECLARE_ATTRIBUTE(0,imageindexobject,"Index binding to imageobject", 1)
DECLARE_ATTRIBUTE(0,imagebase,"Image to appear on the image base, AKA \"2D shape\"", 0)
DECLARE_ATTRIBUTE(0,imageindexbase,"Index binding to imagebase", 1)
DECLARE_ATTRIBUTE(0,shape,"Filename path to 3D model to represent the object", 0)
DECLARE_ATTRIBUTE(0,shapeindex,"Index binding to shape", 1)
DECLARE_ATTRIBUTE(0,drawsurrogate,"Path to an object to draw as part of this object's shape", 0)
DECLARE_ATTRIBUTE(0,sound,"Filename path to .wav sound file", 0)
DECLARE_ATTRIBUTE(0,soundindex,"Index binding for sound", 1)

// object gui links
DECLARE_ATTRIBUTE(0,guifocus,"Node path to view to be used for editing object properties", 0)
DECLARE_ATTRIBUTE(0,guifocusclass,"Node path to view to be used for editing object parameters", 0)

DECLARE_ATTRIBUTE(0,stored,"General purpose node for storage", 0)
DECLARE_ATTRIBUTE(0,objectinfo,"List containing strings to be displayed next to the object's name (2D/3D views).", 0)
DECLARE_ATTRIBUTE(0,frame,"Current frame for 3d shape", 1)

DECLARE_ATTRIBUTE(0,uniqueid,"A Unique ID number for a flowitem. Used by the Full History.", 1)
DECLARE_ATTRIBUTE(0,animationinfo,"An attribute containing animation information", 0)
DECLARE_ATTRIBUTE(0,resizeinfo,"An attribute containing sub-component resizing information", 0)

// COPYRIGHT 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

