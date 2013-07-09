

// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.



// object containers
DECLARE_ATTRIBUTE(0,behaviour,"Behaviour function lists container")
DECLARE_ATTRIBUTE(0,cppfunctions,"c++ functions list")
DECLARE_ATTRIBUTE(0,cppvariables,"c++ variables container")
DECLARE_ATTRIBUTE(0,eventfunctions,"Eventfunctions list")
DECLARE_ATTRIBUTE(0,userfunctions,"Userfunctions list")
DECLARE_ATTRIBUTE(0,classes,"Classes list")
DECLARE_ATTRIBUTE(0,superclasses,"Superclasses list")
DECLARE_ATTRIBUTE(0,connections,"Port connection lists container")
DECLARE_ATTRIBUTE(0,connectionsin,"In-port connections list")
DECLARE_ATTRIBUTE(0,connectionsout,"Out-port connections list")
DECLARE_ATTRIBUTE(0,connectionscenter,"Center-port connections list")
DECLARE_ATTRIBUTE(0,events,"Pending events list")
DECLARE_ATTRIBUTE(0,instances,"Instance list")
DECLARE_ATTRIBUTE(0,itemtype,"Itemtype")
DECLARE_ATTRIBUTE(0,labels,"Labels list")
DECLARE_ATTRIBUTE(0,variables,"Variables container")
DECLARE_ATTRIBUTE(0,tables,"Table container")
DECLARE_ATTRIBUTE(0,listeners,"Listeners")

// object events
DECLARE_ATTRIBUTE(0,OnReset,"Function node executed on reset")
DECLARE_ATTRIBUTE(0,OnMessage,"Function node executed on message")
DECLARE_ATTRIBUTE(0,OnTimerEvent,"Function node executed on timer event")
DECLARE_ATTRIBUTE(0,OnDraw,"Function node executed on scene draw for that object")
DECLARE_ATTRIBUTE(0,OnPreDraw,"Function node executed on before scene draw for that object")
DECLARE_ATTRIBUTE(0,OnDrawPlanar,"Function node executed on scene draw for that object")
DECLARE_ATTRIBUTE(0,OnPreDrawPlanar,"Function node executed on scene draw for that object")
DECLARE_ATTRIBUTE(0,OnInOpen,"Function node executed on passthrough on input port")
DECLARE_ATTRIBUTE(0,OnOutOpen,"Function node executed on passthrough on output port")
DECLARE_ATTRIBUTE(0,OnReceive,"Function node executed on accepting an object")
DECLARE_ATTRIBUTE(0,OnSend,"Function node executed on giving an object")
DECLARE_ATTRIBUTE(0,OnEntering,"Function node executed on going into an object")
DECLARE_ATTRIBUTE(0,OnExiting,"Function node executed on leaving an object")
DECLARE_ATTRIBUTE(0,OnCompile,"Function node executed on compilation complete")
DECLARE_ATTRIBUTE(0,OnCreate,"Function node executed on creation")
DECLARE_ATTRIBUTE(0,OnDestroy,"Function node executed on destruction")
DECLARE_ATTRIBUTE(0,OnLoad,"Function node executed on project load")
DECLARE_ATTRIBUTE(0,OnCollision,"Function node executed on collision with an object")
DECLARE_ATTRIBUTE(0,OnClick,"Function node executed on getting a mouse button event")
DECLARE_ATTRIBUTE(0,OnRunStart,"Function node executed on replication start")
DECLARE_ATTRIBUTE(0,OnRunWarm,"Function node executed on replication warm up")
DECLARE_ATTRIBUTE(0,OnRunEnd,"Function node executed on replication end")
DECLARE_ATTRIBUTE(0,OnInterrupted,"Not used")// can't delete because some dlls bind to it
DECLARE_ATTRIBUTE(0,OnCaptured,"Not used")// can't delete because some dlls bind to it
DECLARE_ATTRIBUTE(0,OnListen,"Function node executed on any event happening: after dispatch, when event has been removed")
DECLARE_ATTRIBUTE(0,OnPreListen,"Function node executed on any event happening: before dispatch, when event is still in list")
DECLARE_ATTRIBUTE(0,OnStateChange,"Function node executed when object state changes")
DECLARE_ATTRIBUTE(1,OnDrag,"Node function executed on object drag out from an icongrid, or when moving/resizing")
DECLARE_ATTRIBUTE(0,OnUndo,"Attribute fired on content-defined undo action")

// object stats
DECLARE_ATTRIBUTE(0,state_current,"Current state index")
DECLARE_ATTRIBUTE(0,state_since,"Time of last state update")
DECLARE_ATTRIBUTE(0,state_profile,"Cumulative state durations container")
DECLARE_ATTRIBUTE(0,state_profiles,"Cumulative state durations container")
DECLARE_ATTRIBUTE(0,state_percent,"Percentage cumulative state durations container")
DECLARE_ATTRIBUTE(0,state_graph,"State history container")
DECLARE_ATTRIBUTE(0,state_histo,"State history histogram container")
DECLARE_ATTRIBUTE(0,stats_content,"Content value")
DECLARE_ATTRIBUTE(0,stats_staytime,"Last staytime value")
DECLARE_ATTRIBUTE(0,stats_contentmin,"Minimum recorded content")
DECLARE_ATTRIBUTE(0,stats_contentmax,"Maximum recorded content")
DECLARE_ATTRIBUTE(0,stats_contentavg,"Average recorded content")
DECLARE_ATTRIBUTE(0,stats_contentupdates,"Number of content updates")
DECLARE_ATTRIBUTE(0,stats_contentsince,"Time of last content update")
DECLARE_ATTRIBUTE(0,stats_contentgraph,"Content history data container")
DECLARE_ATTRIBUTE(0,stats_contentgraphmaxpoints,"Maximum content hsitory size")
DECLARE_ATTRIBUTE(0,stats_contenthisto,"Content histogram data container") // /1 params /2 data points
DECLARE_ATTRIBUTE(0,stats_staytimemin,"Minimum recorded staytime")
DECLARE_ATTRIBUTE(0,stats_staytimemax,"Maximum recorded staytime")
DECLARE_ATTRIBUTE(0,stats_staytimeavg,"Average recorded staytime")
DECLARE_ATTRIBUTE(0,stats_staytimeupdates,"Number of staytime updates")
DECLARE_ATTRIBUTE(0,stats_staytimesince,"Time of last recorded staytime update")
DECLARE_ATTRIBUTE(0,stats_staytimegraph,"History of staytime data container")
DECLARE_ATTRIBUTE(0,stats_staytimegraphmaxpoints,"Maximum staytime history size")
DECLARE_ATTRIBUTE(0,stats_staytimehisto,"Staytime histogram data container")
DECLARE_ATTRIBUTE(0,stats_throughput,"Throughput count")
DECLARE_ATTRIBUTE(0,stats_throughputgraph,"Throughput history data container")
DECLARE_ATTRIBUTE(0,stats_throughputgraphmaxpoints,"Maximum throughput history size")
DECLARE_ATTRIBUTE(0,stats_throughputhisto,"Throughput histogram data container")
DECLARE_ATTRIBUTE(0,stats_customgraphs,"Customgraph data container")
DECLARE_ATTRIBUTE(0,stats_lastmovetime,"Time of last move")
DECLARE_ATTRIBUTE(0,stats_creationtime,"Creation time")
DECLARE_ATTRIBUTE(0,stats_input,"Input count")
DECLARE_ATTRIBUTE(0,stats_output,"Output count")

// object spatial and visual
DECLARE_ATTRIBUTE(0,spatialx,"x co-ordinate")
DECLARE_ATTRIBUTE(0,spatialy,"y co-ordinate")
DECLARE_ATTRIBUTE(0,spatialz,"z co-ordinate")
DECLARE_ATTRIBUTE(1,spatialsx,"x scaling")
DECLARE_ATTRIBUTE(1,spatialsy,"y scaling")
DECLARE_ATTRIBUTE(1,spatialsz,"z scaling")
DECLARE_ATTRIBUTE(0,spatialrx,"about-x rotation")
DECLARE_ATTRIBUTE(0,spatialry,"about-y rotation")
DECLARE_ATTRIBUTE(0,spatialrz,"about-z rotation")
DECLARE_ATTRIBUTE(0,offsetx,"Adjustment factor")
DECLARE_ATTRIBUTE(0,offsety,"Adjustment factor")
DECLARE_ATTRIBUTE(0,offsetz,"Adjustment factor")
DECLARE_ATTRIBUTE(0,offsetrx,"Adjustment factor")
DECLARE_ATTRIBUTE(0,offsetry,"Adjustment factor")
DECLARE_ATTRIBUTE(0,offsetrz,"Adjustment factor")
DECLARE_ATTRIBUTE(1,offsetsx,"Adjustment factor")
DECLARE_ATTRIBUTE(1,offsetsy,"Adjustment factor")
DECLARE_ATTRIBUTE(1,offsetsz,"Adjustment factor")
DECLARE_ATTRIBUTE(0,nochildscale,"Do not apply scaling to child objects")
DECLARE_ATTRIBUTE(0,nochildrotate,"Do not apply rotation to child objects")
DECLARE_ATTRIBUTE(0,color,"Contains red, green and blue nodes specifying color")
DECLARE_ATTRIBUTE(0,description,"Full description")
DECLARE_ATTRIBUTE(0,picture,"Iconic bitmap")
DECLARE_ATTRIBUTE(0,title,"Descriptive title")
DECLARE_ATTRIBUTE(0,centroid,"Rotate about center of bounding cuboid instead of the cuboid origin")
DECLARE_ATTRIBUTE(0,ignoredraw,"Be transparent to picking in OpenGL window")
DECLARE_ATTRIBUTE(0,ignorezbuffer,"Ignore depth test when drawing in OpenGL window")
DECLARE_ATTRIBUTE(0,luminous,"Appear luminous")
DECLARE_ATTRIBUTE(0,reflective,"Appear reflective")
DECLARE_ATTRIBUTE(0,billboard,"Fast object draw")
DECLARE_ATTRIBUTE(0,noondraw,"Disable OnDraw")
DECLARE_ATTRIBUTE(0,nopredraw,"Disable Predraw")
DECLARE_ATTRIBUTE(0,shapetype,"Face culling: 0=no, 1=yes")
DECLARE_ATTRIBUTE(0,distcutoff,"Distance to stop drawing: 0=always draw, postive=combine with global setting, negative=override global setting")

// object media
DECLARE_ATTRIBUTE(0,assertshape,"Override for shape index binding")
DECLARE_ATTRIBUTE(0,asserttexture,"Override for imageobject index binding")
DECLARE_ATTRIBUTE(0,imageobject,"Texture to be used on the object's 3D model")
DECLARE_ATTRIBUTE(0,imageindexobject,"Index binding to imageobject")
DECLARE_ATTRIBUTE(0,imagebase,"Image to appear on the image base, AKA \"2D shape\"")
DECLARE_ATTRIBUTE(0,imageindexbase,"Index binding to imagebase")
DECLARE_ATTRIBUTE(0,shape,"Filename path to 3D model to represent the object")
DECLARE_ATTRIBUTE(0,shapeindex,"Index binding to shape")
DECLARE_ATTRIBUTE(0,drawsurrogate,"Path to an object to draw as part of this object's shape")
DECLARE_ATTRIBUTE(0,sound,"Filename path to .wav sound file")
DECLARE_ATTRIBUTE(0,soundindex,"Index binding for sound")
DECLARE_ATTRIBUTE(0,textureaxis_s,"Contains S texture axis definition - four nodes: x,y,z,offset (imageobject)")
DECLARE_ATTRIBUTE(0,textureaxis_t,"Contains T texture axis definition - four nodes: x,y,z,offset (imageobject)")
DECLARE_ATTRIBUTE(0,packedmedia,"contains used media files")

// object gui links
DECLARE_ATTRIBUTE(0,guifocus,"Node path to view to be used for editing object properties")
DECLARE_ATTRIBUTE(0,guifocusclass,"Node path to view to be used for editing object parameters")

// object travelto
DECLARE_ATTRIBUTE(0,travelstarttime,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,traveldirection,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,travelendtime,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,traveltimealpha,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,traveltimebeta,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,travelvpeak,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,traveldistance,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,travelstartx,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,travelstarty,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,travelstartz,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,travelendx,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,travelendy,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,travelendz,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,travelvmax,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,travelacc,"Refer to help file for more details")
DECLARE_ATTRIBUTE(0,traveldec,"Refer to help file for more details")

DECLARE_ATTRIBUTE(0,stored,"General purpose node for storage")
DECLARE_ATTRIBUTE(0,objectinfo,"List containing strings to be displayed next to the object's name (2D/3D views).")
DECLARE_ATTRIBUTE(0,frame,"Current frame for 3d shape")


DECLARE_ATTRIBUTE(0,treeicontitle,"displayed name in tree, no editing")
DECLARE_ATTRIBUTE(0,treeiconindex,"displayed icon in tree, index based")
DECLARE_ATTRIBUTE(0,treeiconhide,"hide icon in tree")

DECLARE_ATTRIBUTE(0,uniqueid,"A Unique ID number for a flowitem. Used by the Full History.")
DECLARE_ATTRIBUTE(0,animationinfo,"An attribute containing animation information")
DECLARE_ATTRIBUTE(0,resizeinfo,"An attribute containing sub-component resizing information")














// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.














