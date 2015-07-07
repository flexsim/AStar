// The following license applies to all parts of this file.
/*************************************************
The MIT License

Copyright (c) <2008> <flexsim-dll-project contributors>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*************************************************/

/******************* - flexsimfuncs.h - Flexsim function definition and binding file - ******************/

// notify any other files that flexsim funcs has been included at least once
#ifndef FLEXSIM_FUNCS
	#define FLEXSIM_FUNCS
#endif

#include <functional>
#include <string>

#undef DECLARE_FLEXSIM_FUNCTION_1
#undef DECLARE_FLEXSIM_FUNCTION_2
#undef DECLARE_FLEXSIM_FUNCTION_3
#undef DECLARE_FLEXSIM_ATTRIBUTE
#undef DECLARE_FLEXSIM_GLOBAL_VARIABLE

#if DECLARATIONTYPE == FLEXSIM_DECLARATION_PHASE

	#define DECLARE_FLEXSIM_FUNCTION_1(name) extern _##name name;
	#define DECLARE_FLEXSIM_FUNCTION_2(name, strname) extern _##name name;
	#define DECLARE_FLEXSIM_FUNCTION_3(name, strname32, strname64) extern _##name name;
	#define DECLARE_FLEXSIM_ATTRIBUTE(name) extern attfunc name;
	#define DECLARE_FLEXSIM_GLOBAL_VARIABLE(name, type) extern type * _##name##_pointer;

#elif DECLARATIONTYPE == FLEXSIM_DEFINITION_PHASE

	// These are standard function definition. These should not be changed.
	#define DECLARE_FLEXSIM_FUNCTION_1(name) _##name name;
	#define DECLARE_FLEXSIM_FUNCTION_2(name, strname) _##name name;
	#define DECLARE_FLEXSIM_FUNCTION_3(name, strname32, strname64) _##name name;
	#define DECLARE_FLEXSIM_ATTRIBUTE(name) attfunc name;
	#define DECLARE_FLEXSIM_GLOBAL_VARIABLE(name, type) type * _##name##_pointer;

#elif DECLARATIONTYPE == FLEXSIM_BINDING_PHASE

	// These are standard function binding. These should not be changed.
	#define DECLARE_FLEXSIM_FUNCTION_1(name) \
		name = (_##name)getflexsimexportedfunction(#name);\
		if(!name){ nrUnboundFunctions++; unboundFunctions += #name; unboundFunctions += "\n"; name = (_##name)handleunboundfunction;}
	#define DECLARE_FLEXSIM_ATTRIBUTE(name) \
		name = (attfunc)getflexsimexportedfunction(#name);\
		if(!name){ nrUnboundFunctions++; unboundFunctions += #name; unboundFunctions += "\n"; name = (attfunc)handleunboundfunction;}
	#define DECLARE_FLEXSIM_FUNCTION_2(name, strname) \
		name = (_##name)getflexsimexportedfunction(strname);\
		if(!name){ nrUnboundFunctions++; unboundFunctions += #name; unboundFunctions += "\n"; name = (_##name)handleunboundfunction;}
	#ifndef _M_AMD64
		#define DECLARE_FLEXSIM_FUNCTION_3(name, strname32, strname64) \
			name = (_##name)getflexsimexportedfunction(strname32);\
			if(!name){ nrUnboundFunctions++; unboundFunctions += #name; unboundFunctions += "\n"; name = (_##name)handleunboundfunction;}
	#else
		#define DECLARE_FLEXSIM_FUNCTION_3(name, strname32, strname64) \
			name = (_##name)getflexsimexportedfunction(strname64);\
			if(!name){ nrUnboundFunctions++; unboundFunctions += #name; unboundFunctions += "\n"; name = (_##name)handleunboundfunction;}
	#endif

	#define DECLARE_FLEXSIM_GLOBAL_VARIABLE(name, type)\
		int _##name##_globalvariableindex = getglobalvariableindex(#name);\
		if(_##name##_globalvariableindex == 0)\
			{ nrUnboundFunctions++; unboundFunctions += #name; unboundFunctions += "\n"; }\
		else _##name##_pointer = &(getglobalvariableas##type(_##name##_globalvariableindex));

#endif

#ifndef TYPEDEFS
#define TYPEDEFS

	typedef treenode     (*attfunc)(treenode );
	typedef int          (*__executefsfile)(char* s, int direct);
	typedef double       (*__inheritcode)(CallPoint* callpoint);
	typedef int          (*__mpd)(int m);
	typedef int          (*__mpf)(double m);
	typedef int          (*__mpr)();
	typedef int          (*__mpr)();
	typedef int          (*__mpt)(char *m);
	typedef int          (*__mpt)(char*);
	#if FLEXSIM_TARGET_VERSION >= 710
	typedef int          (*__partype)(int index, CallPoint * callpoint);
	#endif
	typedef double       (*__parval)(int index, CallPoint * callpoint);
	typedef treenode       (*__parnode)(int index, CallPoint * callpoint);
	typedef const char*  (*___parstr)(int index, CallPoint * callpoint);
	typedef Variant     (*__param)(int index, CallPoint * callpoint);
	typedef int          (*_activateview)(treenode xx);
	typedef HWND         (*_activedocumentview)();
	typedef int          (*_activeview)();
	typedef double       (*_add)(double n1, double n2);
	typedef int          (*_addbundlefieldalias)(treenode x, char* fieldname, int type, int maxstrsize);
	typedef int          (*_addcommand)(treenode node, char *name, char * desc, char * par, char * examp, char * cppprefix, int group);
	typedef int          (*_addfullhistorymoverecord)(unsigned int _id, double _time, treenode _origin, treenode _destination, double _itemtype);
	typedef double       (*_addkinematicalias)(treenode infonode,double _x, double _y, double _z, double maxspeed, double acc, double dec, double  _startspeed, double  _endspeed, double  _starttime, unsigned short type);
	typedef treenode     (*_addlabel_importedfunction)(treenode object, char* labelname, double value);
	typedef double       (*_addsphere)(treenode obj, double xval, double yval, double zval, double radius);
	typedef treenode     (*_addtablecolalias)(treenode table, int col, int datatype);
	typedef treenode     (*_addtablerowalias)(treenode table, int row, int datatype);
	typedef void         (*_addtoeventtypelegendalias1)(int index, int parameter, int value, char* legendname);
	typedef void         (*_addtoeventtypelegendalias2)(char* name, int parameter, int value, char* legendname);
	typedef double       (*_addviewtextalias)(treenode target, char *);
	typedef int          (*_aggregateundorecordsalias)(TreeNode* view, char* description, int id1, int id2, int id3, int id4, int id5, int id6, int id7, int id8);
	typedef double       (*_and)(double, double);
	typedef treenode     (*_anode)(double x);
	typedef double       (*_anum)(char * x);
	typedef double       (*_applyeditstonode)(treenode view, treenode obj);
	typedef int          (*_applylinks)(treenode view, int reverse);
	typedef int          (*_applyshapefactors)(treenode);
	typedef double       (*_applytoedits)(treenode view, treenode obj);
	typedef void*        (*_aptr)(double);
	typedef treenode     (*_assertattributealias)(treenode object,char *name, int datatype);
	typedef treenode     (*_assertlabelalias)(treenode object,char *name, int datatype);
	typedef treenode     (*_assertsubnodealias)(treenode node,char *name, int datatype);
	typedef treenode     (*_assertvariablealias)(treenode object,char *name, int datatype);
	typedef treenode     (*_att)(treenode node, int index);
	typedef treenode     (*_att_s)(treenode node, char * name);
	typedef treenode     (*_attlink)(treenode N, char* s);
	typedef int          (*_autoloadallmedia)();
	typedef int          (*_autoloadimages)();
	typedef int          (*_autoloadshapes)();
	typedef int          (*_autoloadsounds)();
	typedef int          (*_aviadd)(treenode winnode);
	typedef int          (*_avifinish)(treenode winnode);
	typedef int          (*_avistart_importedfunction)(char* s, treenode winnode, double fps, double uc);
	typedef double       (*_backupfile)(char *f);
	typedef char*        (*_bbgetbuffer)(treenode thenode);
	typedef int          (*_bbgetsize)(treenode thenode);
	typedef char*        (*_bbgetstaticblock)();
	typedef int          (*_bbsetsize)(treenode thenode, int size);
	typedef treenode     (*_bcgetitemkinematics)(treenode conveyor,  treenode item, int kinematictype);
	typedef double       (*_bcgetitemposition)(treenode conveyor,  treenode item);
	typedef double       (*_bcsetdirection)(treenode conveyor,  int direction);
	typedef double       (*_bcsetitemconveystate)(treenode conveyor,  treenode item, double startpos, double startspeed, double targetspeed, double accdec);
	typedef int          (*_beginaggregatedundo)(treenode view, char* description);
	typedef void         (*_beginignoreundo)();
	typedef double       (*_bernoullialias)(double prob, double a, double b, int stream); // not in LK
	typedef double       (*_betaalias)( double a,      double b,     double shape1,    double shape2 , int stream);
	typedef void         (*_bindobjectclassvariable)(treenode object, treenode* binder, char* variablename, char* classname);
	typedef int          (*_bindtexture)(int textureid);
	typedef double       (*_binomialalias)( int    t,      double p, int stream);
	typedef int          (*_bitwiseand)(int, int);
	typedef int          (*_bitwisenot)(int);
	typedef int          (*_bitwiseor)(int, int);
	typedef double       (*_buildall)();
	typedef double       (*_buildnodeflexscript)(treenode node);
	typedef int          (*_calculate6DOFrobotinversekinematics)(double * loc, treenode planningItem, double* rotOffset, double approachoffset, treenode robot, double* d, double* a, double xtrans, double * returnval);
	typedef double       (*_calculateconfidence)(double stddev, double nrofdatapoints, double confidence);
	typedef double       (*_callwebscriptmethod)(treenode view, char* id, char* name, ...);
	typedef char*        (*_cdir_cstr)();
	typedef treenode     (*_cell)(treenode node, unsigned int xpos, unsigned int ypos);
	typedef treenode     (*_cellrowcolumn)(treenode node, unsigned int xpos, unsigned int ypos);
	typedef double       (*_cempiricalalias)( char *tablename, int stream);
	typedef treenode     (*_centerobject)(treenode, int);
	typedef double       (*_changeconveyorspeed)(treenode conveyor, double newspeed);
	typedef int          (*_changedisplay)(int width, int height, int depth, int fullscreen, int test);
	typedef treenode     (*_changetask)(treenode tasksequence, int taskrank, unsigned short type, treenode involved1, treenode involved2, double var1, double var2, double var3, double var4);
	typedef int          (*_checkdllconnection)(treenode node, int makeconnection);
	typedef int          (*_checkoutmodulefeature)(HANDLE moduleid, char* feature, char * version);
	typedef treenode     (*_classobject)(treenode);
	typedef int          (*_clearbundlealias)(treenode x, int resetflags);
	typedef int          (*_clearconsole)();
	typedef int          (*_clearcontents)(treenode );
	typedef double       (*_clearglobaltable_alias1)(char *table);
	typedef double       (*_clearglobaltable_alias2)(treenode table);
	typedef double       (*_clearglobaltable_alias3)(int table);
	typedef double       (*_clickcode)();
	typedef double       (*_clientclose)(int sock);
	typedef double       (*_clientclose)(int sock);
	typedef double       (*_clientconnectalias)(int skt, char *hostname, int port);
	typedef double       (*_clientcreate)();
	typedef double       (*_clientreceivealias)(int skt, char *Buf, int BufSize, int NoBlock);
	typedef double       (*_clientsendalias)(int skt, char *Msg, int len);
	typedef int          (*_closeallip)(treenode);
	typedef int          (*_closeallop)(treenode);
	typedef double       (*_closeinput)(treenode object);
	typedef double       (*_closeip)(treenode node, int index);
	typedef double       (*_closenodeedge)(treenode curnode, int edgenum);
	typedef double       (*_closeop)(treenode node, int index);
	typedef double       (*_closeoutput)(treenode object);
	typedef int          (*_closeview)(treenode xx);
	typedef double       (*_cm)(double val);
	typedef double       (*_cmdcompile)();
	typedef double       (*_cmddelete)();
	typedef double       (*_cmdexit)();
	typedef double       (*_cmdloadbyextension)(char * thename, int silent);
	typedef double       (*_cmdloadsession)(char * thename);
	typedef double       (*_cmdloadtree)(treenode thenode, char * thename, int nobuild);
	typedef double       (*_cmdnew)();
	typedef double       (*_cmdopen)();
	typedef double       (*_cmdsaveas)();
	typedef double       (*_cmdsavesession)(char * thename);
	typedef double       (*_cmdsavetree)(treenode thenode, char * thename);
	typedef double       (*_cauchyalias)( double locate, double scale, int stream);
	typedef int          (*_codetotemplate)(treenode thecode, treenode theedit, int firstcommentonly);
	typedef double       (*_codetotemplatetext)(treenode view, treenode destnode);
	typedef char*        (*_codetotemplatetext_cstr)(treenode thecode);
	typedef double       (*_coloraqua)(treenode involved);
	typedef double       (*_colorarrayalias1)(treenode involved, double val);
	typedef void         (*_colorarrayalias2)(int val, double * destcolor);
	typedef double       (*_colorblack)(treenode involved);
	typedef double       (*_colorblue)(treenode involved);
	typedef double       (*_colorbrown)(treenode involved);
	typedef double       (*_colorgray)(treenode involved);
	typedef double       (*_colorgreen)(treenode involved);
	typedef double       (*_colorlightblue)(treenode involved);
	typedef double       (*_colorlime)(treenode involved);
	typedef double       (*_colororange)(treenode involved);
	typedef double       (*_colorpink)(treenode involved);
	typedef double       (*_colorpurple)(treenode involved);
	typedef double       (*_colorrandom)(treenode involved);
	typedef double       (*_colorred)(treenode involved);
	typedef double       (*_colorrgb)(treenode involved, double red, double green, double blue);
	typedef double       (*_colorsilver)(treenode involved);
	typedef double       (*_colorteal)(treenode involved);
	typedef double       (*_colorwhite)(treenode involved);
	typedef double       (*_coloryellow)(treenode involved);
	typedef int          (*_combocurrentnode)(treenode thecombo);
	typedef int          (*_comborefresh)(treenode thecombo);
	typedef char*        (*_commandlineparam)(char* param);
	typedef int          (*_comparetextalias1)(char* str1, char* str2, int ignorecase);
	typedef int          (*_comparetrees)(treenode a, treenode b);
	typedef double       (*_consoleexecutecpp)(HWND in, HWND out);
	typedef double       (*_consoleexecutefs)(HWND in, HWND out);
	typedef double       (*_containerentry)(treenode container, treenode item);
	typedef double       (*_containerexit)(treenode container, treenode item);
	typedef int          (*_content)(treenode);
	typedef double       (*_contentobj)(treenode container);
	typedef int          (*_contentunderalias)(treenode, int objectsonly);
	typedef double       (*_contextdragconnection)(treenode fromobject, treenode toobject, char keypressed);
	typedef double       (*_controlpressed)();
	typedef treenode     (*_copyattributes)(treenode dest, treenode src, unsigned int mask); 
	typedef int          (*_cpcpno)(treenode, int);
	typedef int          (*_cppgetnumtokens)(treenode thetext);
	typedef int          (*_cppgetphrasetoken)(treenode thetext, int index, ByteBlock * resultblock);
	typedef int          (*_cppgettitletoken)(treenode thetext, int index, ByteBlock * resultblock);
	typedef int          (*_cppgettoken)(treenode thetext, int index, ByteBlock * resultblock);
	typedef int          (*_cppsettitletoken)(treenode thetext, int index, ByteBlock * resultblock, char * newtext);
	typedef int          (*_cppsettoken)(treenode thetext, int index, ByteBlock * resultblock, char * newtext);
	typedef std::function<Variant ()> QueryCallback;
	typedef int          (*_cpp_queryalias)(const char* queryStr, QueryCallback& p1,  QueryCallback& p2, QueryCallback& p3,  QueryCallback& p4,
									QueryCallback& p5,  QueryCallback& p6, QueryCallback& p7,  QueryCallback& p8, QueryCallback& p9);
	typedef treenode     (*_createcoordinatedtasksequence)(treenode dispatcher);
	typedef treenode     (*_createcopyalias)(treenode classobject, treenode instancecontainer, int samename, int inobject, int cached, int replace);
	typedef treenode     (*_createcoupling)(treenode container1, treenode container2);
	typedef treenode     (*_createdelaytask)(treenode dispatcher,double delaytime,double state,double priority,int preempt);
	typedef EventDataStruct* (*_createeds)(int code, char* string, void* data);
	typedef treenode     (*_createemptytasksequence)(treenode dispatcher, double priority, int preempt);
	typedef double       (*_createeventalias1)( treenode client, double time, unsigned int code, void *data, treenode involved);
	typedef double       (*_createeventex)( treenode client, double time, unsigned int code, void *data, treenode involved, int datasize);
	typedef treenode     (*_createinstancealias)(treenode CLASSNODE, treenode CONTAINERNODE, int nocreatemessage);
	typedef treenode     (*_createloadtask)(treenode dispatcher,treenode destination,treenode flowitem,double priority,int preempt);
	typedef int          (*_createpopup)(char* path, char* ofocus, char* vfocus, treenode relativeto, int x, int y, int sx, int sy);
	typedef treenode     (*_createsendmessagetask)(treenode dispatcher,treenode receiver, double priority,int preempt,double param1,double param2,double param3);
	typedef treenode     (*_createstandardtask)(treenode dispatcher,treenode origin,treenode destination,treenode flowitem,double priority,int preempt);
	typedef treenode     (*_createtravelloadtask)(treenode dispatcher,treenode destination,treenode flowitem,double priority,int preempt);
	typedef treenode     (*_createtraveltask)(treenode dispatcher,treenode destination,double priority,int preempt);
	typedef treenode     (*_createtraveltolocandwaittask)(treenode dispatcher,double relativeloc,double xloc,double yloc,double zloc,double endspeed,double state,double priority,int preempt);
	typedef treenode     (*_createtraveltoloctask)(treenode dispatcher,int relativeloc,double xloc,double yloc,double zloc,double endspeed,double priority,int preempt);
	typedef treenode     (*_createtravelunloadtask)(treenode dispatcher,treenode destination,treenode flowitem,double priority,int preempt);
	typedef int          (*_createundorecord)(treenode view, TreeNode* object, int undocode, double p1, double p2, double p3);
	typedef treenode     (*_createunloadtask)(treenode dispatcher,treenode destination,treenode flowitem,double priority,int preempt);
	typedef double       (*_createview)(char * a, char * b, char * c);
	typedef char*        (*_currentfile_cstr)();
	typedef double       (*_cursorinfo)(treenode,double, double, double);
	typedef int          (*customeventfilter)(treenode object, double simtime, int code, void* data, treenode involved);
	typedef double       (*_daemonstate)(int);
	typedef int          (*_dataplot)(treenode datanode, int type, int action , double x, double y, double z);
	typedef double       (*_days)(double val);
	typedef int          (*_dbchangetable)(char * dbname);
	typedef int          (*_dbclose)();
	typedef double       (*_dbexportnode)(treenode table, int startrow, int startcol, int numrows, int numcols);
	typedef double       (*_dbexporttable)(char *tablename, int startrow, int startcol, int numrows, int numcols);
	typedef char*        (*_dbgetfieldname)(int col);
	typedef int          (*_dbgetmetrics)();
	typedef int          (*_dbgetmode)();
	typedef int          (*_dbnextrow)();
	typedef int          (*_dbgetnumcols)();
	typedef int          (*_dbgetnumrows)();
	typedef char*        (*_dbgettablecell)(int row, int col);
	typedef double       (*_dbgettablenum)(int row, int col);
	typedef char*        (*_dbgettablestr)(double row, double col);
	typedef double       (*_dbimportnode)(treenode table, int startrow, int startcol, int numrows, int numcols);
	typedef double       (*_dbimporttable)(char *tablename, int startrow, int startcol, int numrows, int numcols);
	typedef int          (*_dbopenalias)(char * dbname, char *command, int tablemode, int loginprompt);
	typedef int          (*_dbsettablecell)(int row, int col, char* sval);
	typedef double       (*_dbsettablenum)(int row, int col, double val);
	typedef double       (*_dbsettablestr)(double row, double col, char *val);
	typedef int          (*_dbsqlqueryalias)(char * query, int flags);
	typedef int          (*_dbusername)(char * username, char * password);
	typedef int          (*_dbusernamealias)(char * username, char * password);
	typedef double       (*_dbviewtable)();
	typedef int          (*_dbwritechanges)();
	typedef void         (*_deactivatekinematics)(treenode infonode);
	typedef double       (*_defaultdragconnection)(treenode fromobject, treenode toobject, char characterpressed);
	typedef double       (*_degreestoradians)(double n);
	typedef double       (*_delayevents)(double dt);
	typedef double       (*_delayeventsofobject)(treenode object,double dt);
	typedef void         (*_deleteeds)(EventDataStruct* eds);
	typedef int          (*_deletetablecolalias)(treenode table, int col);
	typedef int          (*_deletetablerowalias)(treenode table, int row);
	typedef double       (*_dellabel)(treenode object, char* labelname);
	typedef double       (*_dempiricalalias)( char *tablename, int stream);
	typedef double       (*_deselectall)();
	typedef double       (*_destroyevent)(treenode thenode);
	typedef double       (*_destroyeventsofobjectalias1)(treenode object);
	typedef double       (*_destroyeventsofobjectalias2)(treenode object, double simtime, int code, char* data,  treenode involvedobject);
	typedef double       (*_destroyeventsofobjectalias3)(treenode object, double simtime, int code, char* data,  treenode involvedobject, customeventfilter filter);
	typedef int          (*_destroynode)(treenode object);
	typedef int          (*_destroyobject)(treenode object);
	typedef double       (*_diffsign)(double n1, double n2);
	typedef double       (*_dispatchcoordinatedtasksequencealias)(treenode tasksequence, treenode dispatcher);
	typedef double       (*_dispatchtasksequencealias)(treenode tasksequence, treenode dispatcher);
	typedef double       (*_distancetotravel)(treenode traveler, treenode destination);
	typedef double       (*_distfromviewpoint)(treenode theobject, treenode theview);
	typedef double       (*_divide)(double n1, double n2);
	typedef char*        (*_documentsdir_cstr)();
	typedef void         (*_documentusercommands)();
	typedef double       (*_draginfoalias)(int op, double val);
	typedef double       (*_draw2dcurve)(treenode view, double matrix[4][4],double xcenter, double ycenter, double radius, double startangle, double sweepangle, float red, float green, float blue );
	typedef double       (*_draw3dtext)(char * text);
	typedef double       (*_drawbox)(double xloc, double yloc, double zloc, double xsize, double ysize, double zsize, int glbeginend);
	typedef double       (*_drawcolumn)(double LocX, double LocY, double LocZ, double Sides, double BaseRadius, double TopRadius, double Height, double RotX, double RotY, double RotZ, double Red, double Green, double Blue, double Opacity, double ImageIndexObjectNum, double RepX, double RepY);
	typedef double       (*_drawcubealias1)(double LocX, double LocY, double LocZ, double SizeX, double SizeY, double SizeZ, double RotX, double RotY, double RotZ, double Red, double Green, double Blue, double Opacity, double ImageIndexObjectNum, double RepX, double RepY);
	typedef double       (*_drawcubealias2)(double LocX, double LocY, double LocZ, double SizeX, double SizeY, double SizeZ, double RotX, double RotY, double RotZ, double Red, double Green, double Blue);
	typedef double       (*_drawcylinderalias1)(double LocX, double LocY, double LocZ, double BaseRadius, double TopRadius, double Height, double RotX, double RotY, double RotZ, double Red, double Green, double Blue, double Opacity, double ImageIndexObjectNum);
	typedef double       (*_drawcylinderalias2)(double LocX, double LocY, double LocZ, double BaseRadius, double TopRadius, double Height, double RotX, double RotY, double RotZ, double Red, double Green, double Blue);
	typedef double       (*_drawdisk)(double LocX, double LocY, double LocZ, double InnerRadius, double OuterRadius, double StartAngle, double SweepAngle, double RotX, double RotY, double RotZ, double Red, double Green, double Blue, double Opacity, double ImageIndexObjectNum);
	typedef double       (*_drawflattext)(char * text);
	typedef double       (*_drawfont)(double f);
	typedef double       (*_drawline)(treenode viewnode, double x, double y, double z, double x2, double y2, double z2, double red, double green, double blue);
	typedef void         (*_drawobjectpart)(treenode viewobj, treenode object, int part);
	typedef double       (*_drawpie)(treenode viewnode, double x, double y, double z, double x2, double y2, double z2, double startangle, double endangle, double red, double green, double blue);
	typedef double       (*_drawquad)(treenode windownode, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4, double red, double green, double blue);
	typedef double       (*_drawrect)(treenode viewnode, double x, double y, double z, double x2, double y2, double z2, double red, double green, double blue);
	typedef double       (*_drawrectanglealias1)(double LocX, double LocY, double LocZ, double SizeX, double SizeY, double RotX, double RotY, double RotZ, double Red, double Green, double Blue, double Opacity, double ImageIndexObjectNum, double RepX, double RepY);
	typedef double       (*_drawrectanglealias2)(double LocX, double LocY, double LocZ, double SizeX, double SizeY, double RotX, double RotY, double RotZ, double Red, double Green, double Blue);
	typedef double       (*_drawshadow)(int phase);
	typedef double       (*_drawspherealias)(double x, double y, double z, double radius, double red, double green, double blue, double opacity, int textureindex);
	typedef double       (*_drawspheres)(treenode object, treenode view);
	typedef double       (*_drawtextalias)(treenode windownode, char * text, double x, double y, double z, double sx, double sy, double sz, double rx, double ry, double rz, double red, double green, double blue, double alpha);
	typedef double       (*_drawtomodelscale)(treenode object);
	typedef double       (*_drawtoobjectscale)(treenode object);
	typedef double       (*_drawtriangle)(treenode windownode, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double red, double green, double blue);
	typedef treenode     (*_dropnodefrom)();
	typedef treenode     (*_dropnodeto)();
	typedef double       (*_dropx)();
	typedef double       (*_dropy)();
	typedef double       (*_dropz)();
	typedef void         (*_dumpquery)(treenode dumpNode, int asTable);
	typedef double       (*_duniformalias)( int    i,      int    j, int stream);
	typedef double       (*_dynamicsplineall)(treenode start);
	typedef int          (*_edscode)(EventDataStruct* eds);
	typedef void*        (*_edsdata)(EventDataStruct* eds);
	typedef char*        (*_edsstring)(EventDataStruct* eds);
	typedef double       (*_empiricalalias)( char *tablename, int stream);
	typedef int          (*_enablefullhistory)(int enable);
	typedef void         (*_endaggregatedundo)(treenode view, int id);
	typedef void         (*_endignoreundo)();
	typedef int          (*_endoffile)();
	typedef double       (*_endreplication)(int onlyifexperimenting);
	typedef double       (*_endwaittask)(treenode dispatcher);
	typedef double       (*_eq)(double n1, double n2);
	typedef double       (*_erlangalias)( double locate, double scale, double shape, int stream); // same as gamma

	typedef double       (*_eventget)(int index, int thing);
	typedef double       (*_eventmovedown)(int index);
	typedef double       (*_eventmoveup)(int index);
	typedef double       (*_eventqty)();
	typedef double       (*_eventtype)(int);
	typedef int          (*_EXalias)(char *T, char * M, int showsystemconsole);
	typedef double       (*_excelclose)(int save);
	typedef double       (*_excelcreatesheet)(char *name);
	typedef int          (*_exceldeleterange)(char *name);
	typedef double       (*_exceldeletesheet)(char *name, int allowwarning);
	typedef double       (*_excelexportnode)(treenode table, int startrow, int startcol, int numrows, int numcols, char rowchar, char colchar);
	typedef double       (*_excelexporttable)(char *tablename, int startrow, int startcol, int numrows, int numcols, char rowchar, char colchar);
	typedef int          (*_excelgetrangeparam)(char *name, int param);
	typedef char*        (*_excelgetrangesheet)(char *name);
	typedef double       (*_excelimportnodealias1)(treenode table,int startrow, int startcol, int numrows, int numcols);
	typedef double       (*_excelimportnodealias2)(treenode table,int startrow, int startcol, int numrows, int numcols, char rowchar, char colchar);
	typedef double       (*_excelimporttable)(char* globaltablename, int startrow, int startcol, int numrows, int numcols, char rowchar, char colchar);
	typedef int          (*_excellaunchalias1)(char*);
	typedef int          (*_excellaunchalias2)();
	typedef double       (*_excelmacro)(char * m);
	typedef double       (*_excelopenalias)(char * a);
	typedef int          (*_excelquit)();
	typedef char*        (*_excelrangeread)(char *name, int row, int col);
	typedef double       (*_excelrangereadnum)(char* name, int row, int col);
	typedef char*        (*_excelrangereadstr)(char* name, int row, int col);
	typedef int          (*_excelrangewrite)(char *name, char *value, int row, int col);
	typedef double       (*_excelrangewritenum)(char* name, int row, int col, double val);
	typedef double       (*_excelrangewritestr)(char* name, int row, int col, char* val);
	typedef char*        (*_excelread)(int Row, int Col, char rowchar, char colchar);
	typedef double       (*_excelreadnum)(int row, int col);
	typedef char*        (*_excelreadstr)(int row, int col);
	typedef int          (*_excelsave)(char *name);
	typedef int          (*_excelsetrange)(char *name, int startrow, int startcol, int endrow, int endcol);
	typedef double       (*_excelsetsheetalias)(char *sh);
	typedef double       (*_excelupdatepreferences)();
	typedef char*        (*_excelversion)();
	typedef char*        (*_excelwrite)(char *inStr, int Row, int Col, char RowChar, char ColChar);
	typedef double       (*_excelwritenum)(int row, int col, double data);
	typedef double       (*_excelwritestr_importedfunction)(int row, int col, char* data);
	typedef double       (*_executefsnodealias)(treenode ATT,treenode C,treenode I,void *DATA, char *MSG, int nobuild);
	typedef double       (*_executestringalias)(char *str,treenode C,treenode I,void *DATA, char *MSG, int nobuild);
	typedef double       (*_exponentialalias)( double locate, double scale , int stream);
	typedef double       (*_exportdatasetalias)(treenode, char * table, int format, char* wrOption);
	typedef int          (*_exportfullhistory)(char *dbname);
	typedef double       (*_exporttablealias)(treenode, char * table, int usetopgrey, int useleftgrey);
	typedef double       (*_extremevalue1aalias)( double locate, double scale, int stream);
	typedef double       (*_extremevalue1balias)( double locate, double scale, int stream);
	typedef double       (*_factorial)(double n1);
	typedef int          (*_familycreate)(treenode familycontainer, char * name);
	typedef int          (*_familydelete)(treenode familycontainer, char * name);
	typedef treenode     (*_familymember)(treenode familycontainer, char * name, int index);
	typedef int          (*_familymemberadd)(treenode familycontainer, char * name,treenode node);
	typedef int          (*_familymemberdel)(treenode familycontainer, char * name,treenode node);
	typedef int          (*_familymemberqty)(treenode familycontainer, char * name);
	typedef double       (*_fastspline)(treenode spline, double p);
	typedef double       (*_fastsplineall)(treenode start, double res);
	typedef double       (*_fastsplineupdate)(treenode spline, double res);
	typedef void         (*_fglColorAlias)(float r, float g, float b, float a);
	typedef int          (*_fgldebuglevel)(int level);
	typedef void         (*_fglDisable)(GLenum x);
	typedef void         (*_fglEnable)(GLenum x);
	typedef double       (*_fglinfo)(int op, treenode view);
	typedef void         (*_fglLoadIdentity)();
	typedef void         (*_fglMatrixMode)(GLenum mode);
	typedef void         (*_fglNormal)(float x, float y, float z);
	typedef void         (*_fglPopMatrix)();
	typedef void         (*_fglPushMatrix)();
	typedef void         (*_fglRotate)(float angle, float x, float y, float z);
	typedef void         (*_fglScale)(float x, float y, float z);
	typedef void         (*_fglTranslate)(float x, float y, float z);
	typedef char*        (*_filebrowse_importedfunction)(char* ext, char* desc, char* path);
	typedef double       (*_fileclose)();
	typedef int          (*_fileexistsalias)(char *);
	typedef double       (*_fileopenalias)(char * filename, char * mode);
	typedef double       (*_fillwithatts)(treenode object, int attgroup);
	typedef treenode     (*_findnode)(treenode head, char* nodename);
	typedef treenode     (*_findownerobject)(treenode);
	typedef treenode     (*_findundorecordbyid)(treenode, int uniqueid);
	typedef void         (*_finishundorecord)(TreeNode* view, int uniqueid);
	typedef treenode     (*_first)(treenode);
	typedef treenode     (*_flowitembin)();
	typedef int          (*_flyactive)();
	typedef int          (*_flybysimclock)();
	typedef treenode     (*_flyendnode)(treenode thenode);
	typedef int          (*_flypath)(treenode thenode,int,int singlerun);
	typedef int          (*_flypathadd)(treenode thenode,int pathno);
	typedef int          (*_flypathreset)(treenode thenode,int pathno);
	typedef double       (*_flystart)(treenode view);
	typedef double       (*_flystop)();
	typedef double       (*_flyto)(treenode view, double endtime, double x, double y, double z, double rx, double ry, double rz);
	typedef int          (*_flyupdate)();
	typedef int          (*_fpc)(char m);
	typedef int          (*_fpd)(int m);
	typedef int          (*_fpf)(double m);
	typedef double       (*_fpm)(double val);
	typedef int          (*_fpr)();
	typedef double       (*_fps)(double val);
	typedef int          (*_fpt_importedfunction)(char* m);
	typedef double       (*_frac)(double n1);
	typedef double       (*_freeoperators)(treenode dispatcher, treenode involved);
	typedef int          (*_fscheckall)(treenode s);
	typedef double       (*_ft)(double val);
	typedef double       (*_gammaalias)( double locate, double scale, double shape, int stream);
	typedef double       (*_ge)(double n1, double n2);
	typedef unsigned int (*_generateuniqueid)();
	typedef double       (*_geometricalias)( double p, int stream);
	typedef double       (*_get)(treenode attnode);
	typedef treenode     (*_getallocatedfromkey)(treenode tasksequence, int key);
	typedef char*        (*_getapplicationtitle)();
	typedef const char*  (*_getbundlefieldname)(treenode x, int fieldnr);
	typedef int          (*_getbundlefieldnr)(treenode x, char* fieldname);
	typedef int          (*_getbundlefieldtype)(treenode x, int fieldnr);
	typedef int          (*_getbundlenrentries)(treenode x);
	typedef int          (*_getbundlenrfields)(treenode x);
	typedef double       (*_getchecked)(treenode view);
	typedef double       (*_getcolorcomponent)(treenode object, double index);
	typedef treenode     (*_getcoordinatedtasksequence)(treenode dispatcher, int tsrank);
	typedef treenode     (*_getcorefailsafelink)();
	typedef double       (*_getcreationtime)(treenode object);
	typedef HDC          (*_getcurrentscenedc)();
	typedef treenode     (*_getcurrentundorecord)(treenode view);
	typedef double       (*_getcurtask)(treenode tasksequence);
	typedef double       (*_getdatastat_alias1)(int stat, treenode dataset1, treenode dataset2, double p1, double p2, double p3);
	typedef double       (*_getdatastat_alias2)(int stat, int nrSamples, double* samples, double p1, double p2, double p3);
	typedef int          (*_getdatatype)(treenode thenode);
	typedef double       (*_getdrawtextmetric)(char* text, int fontsize, int metric, int a);
	typedef double       (*_getedgedist)(treenode netnode, int edgenum);
	typedef double       (*_getedgespeedlimit)(treenode netnode, int edgenum);
	typedef double       (*_getentrytime)(treenode object);
	typedef double       (*_geteventtime)(char *eventname, double mode);
	typedef double       (*_getfilebrowse)(char *extension,char *extensiondesc, char * buffer);
	typedef double       (*_getframe)(treenode obj);
	typedef double&      (*_getglobalvariableasdouble)(int index);
	typedef doublearray& (*_getglobalvariableasdoublearray)(int index);
	typedef int&         (*_getglobalvariableasint)(int index);
	typedef intarray&    (*_getglobalvariableasintarray)(int index);
	typedef string&      (*_getglobalvariableasstring)(int index);
	typedef stringarray& (*_getglobalvariableasstringarray)(int index);
	typedef treenode&    (*_getglobalvariableastreenode)(int index);
	typedef treenodearray& (*_getglobalvariableastreenodearray)(int index);
	typedef int          (*_getglobalvariableindex)(char* globalvariablename);
	typedef double       (*_getinput)(treenode involved);
	typedef treenode     (*_getiteminvolved)(treenode item);
	typedef int          (*_getitemsendto)(treenode item);
	typedef int          (*_getitemstate)(treenode item);
	typedef double       (*_getitemtype)(treenode object);
	typedef double       (*_getitemvar)(treenode item, int index);
	typedef double       (*_getkinematicsalias)(treenode infonode, unsigned short type, int index, double updatetime);
	typedef double       (*_getlabelnum)(treenode object, char* labelname);
	typedef double       (*_getlastfiletype)();
	typedef double       (*_getlastfiletype)();
	typedef double       (*_getmodelunitnum)(int querytype);
	typedef char*        (*_getmodelunitstr_cstr)(int querytype);
	typedef int          (*_getmodulelicense)(int module, int * version, int * subversion);
	typedef MoveRecord* (*_getmoverecord)(int recordnum);
	typedef double       (*_getmoverecordvalue) (MoveRecord *record,int val);
	typedef treenode     (*_getnetnode)(treenode object, int index);
	typedef treenode     (*_getnetnodespline)(treenode netnode, int outport);
	typedef double       (*_getnetworkdistance)(int fromnn, int tonn);
	typedef int          (*_getnextnetnode)(int fromnn, int tonn);
	typedef int          (*_getnextnetnodeoutport)(int fromnn, int tonn);
	typedef double       (*_getnodenum)(treenode attnode);
	typedef double       (*_getnroftasks)(treenode tasksequence);
	typedef unsigned int (*_getnummoverecords)();
	typedef unsigned int (*_getnumstaterecords)();
	typedef double       (*_getobjectimageindex)(treenode object);
	typedef double       (*_getobjectshapeindex)(treenode object);
	typedef double       (*_getobjecttextureindex)(treenode object);
	typedef treenode     (*_getobjvarfastpointer)(treenode thenode, int offset);
	typedef int          (*_getobjvarfastpointeroffset)(treenode thenode, char* varname);
	typedef double       (*_getoutput)(treenode involved);
	typedef HWND         (*_getparentwindow)(HWND hWnd);
	typedef double       (*_getpickingdrawfocus)(treenode theview, int whattoget, int vftid);
	typedef int          (*_getpickingmode)(treenode theview);
	typedef unsigned int (*_getpreempt)(treenode tasksequence);
	typedef double       (*_getpriority)(treenode tasksequence);
	typedef char*        (*_getproperty)(char *filename, int property);
	typedef double       (*_getquerycolcount)();
	typedef int          (*_getquerymatchcount)();
	typedef int          (*_getquerymatchtablerow)(char* tableName, int matchRow);
	typedef Variant       (*_getqueryvaluealias1)(int row, int col);
	typedef Variant       (*_getqueryvaluealias2)(int row, const char* colName);
	typedef double       (*_getrank)(treenode);
	typedef int          (*_getrunstate)();
	typedef Variant (*_getsdtvalue)(treenode sdtNode, const char* valName);
	typedef double       (*_getshapeindex)(char * thename);
	typedef int          (*_getshapenrframes)(int shapeindex);
	typedef double       (*_getsoundindex)(char * thename);
	typedef double       (*_getstatenum_alias1)(treenode object);
	typedef double       (*_getstatenum_alias2)(treenode object, int profilenr);
	typedef StateRecord* (*_getstaterecord)(int recordnum);
	typedef double       (*_getstaterecordvalue)(StateRecord *record,int val);
	typedef int          (*_getsystemmetric)(int metric, HWND win);
	typedef treenode     (*_gettablecell)(char* globaltablename, int row, int column);
	typedef int          (*_gettablecols)(char* globaltablename);
	typedef double       (*_gettablenumalias)(char * table, int row, int col);
	typedef char*        (*_gettablestr)(char * table, int row, int col);
	typedef treenode     (*_gettaskinvolved)(treenode tasksequence, unsigned int rankrequested, unsigned int involvednum);
	typedef treenode     (*_gettasksequence)(treenode dispatcher, double tsrank);
	typedef treenode     (*_gettasksequencequeue)(treenode dispatcher);
	typedef unsigned int (*_gettasktype)(treenode tasksequence, int rankrequested);
	typedef double       (*_gettaskvariable)(treenode tasksequence, unsigned int rankrequested, unsigned int varnum);
	typedef treenode     (*_gettenetnode)(treenode te);
	typedef double       (*_gettenetworkinfo)(treenode te, treenode destobj, int info);
	typedef double       (*_gettextureindex)(char * thename);
	typedef double       (*_gettotalnroftasks)(treenode tasksequence);
	typedef double       (*_gettreedrawpositionalias)(treenode object, treenode roottree, int* cury, int increment);
	typedef int          (*_getundorecordid)(treenode undorecord);
	typedef treenode     (*_getvarnodeimport)(treenode object, char *varname);
	typedef double       (*_getvarnumalias)(treenode object, char *varname);
	typedef HWND         (*_getviewhwnd)(treenode view, int wndtype);
	typedef HMENU        (*_getviewmenu)(treenode view, int menutype);
	typedef double       (*_getviewscale)(treenode theview);
	typedef char*        (*_getviewtext_cstr)(treenode target);
	typedef int          (*_globalcommand_savebyname)(treenode xx, char *name, int direct);
	typedef double       (*_go)(int fast );
	typedef double       (*_graphtohistogram)(treenode graph, treenode hist, double start, double end, double resolution, int xyformat);
	typedef double       (*_gt)(double n1, double n2);
	typedef double       (*_help)(int mode, char * s1, char * s2);
	typedef double       (*_hideprogressbar)();
	typedef int          (*_highestconnection)();
	typedef char*        (*_highlightviewtext)(treenode target, int pos, int span, int mode);
	typedef double       (*_holditem)(treenode item);
	typedef double       (*_hours)(double val);
	typedef double       (*_howmanyattributes)();
	typedef double       (*_howmanycommands)();
	typedef double       (*_hypergeometricalias)(int sample, int m, int n, int stream);
	typedef double       (*_importdataset)(treenode, char * table, int format);
	typedef double       (*_importtablealias)(treenode, char * table, int usetopgrey, int useleftgrey);
	typedef double       (*_in)(double val);
	typedef double       (*_inc)(treenode attnode, double value);
	typedef double       (*_initialisehistogram)(treenode hist, double resolution);
	typedef void         (*_initkinematicsalias)(treenode infonode, double x, double y, double z, double rx, double ry, double rz, int flags, int unused);
	typedef treenode     (*_inobject)(treenode, int);
	typedef double       (*_inputopen)(treenode obj);
	typedef int          (*_insertallocatetask)(treenode tasksequence, treenode dispatcher, double priority, double preempt, int noblock);
	typedef treenode     (*_insertcopy)(treenode original, treenode container);
	typedef int          (*_insertdeallocatetaskalias)(treenode tasksequence, int executerkey, int noblock);
	typedef int          (*_insertmultiallocatetask)(treenode tasksequence, int range);
	typedef int          (*_insertproxytaskalias1)(treenode tasksequence, unsigned int executerkey, unsigned int  type, treenode involved1, treenode involved2,double var1, double var2 , double var3, double var4);
	typedef int          (*_insertproxytaskalias2)(treenode tasksequence, unsigned int executerkey, unsigned int  type, treenode involved1);
	typedef int          (*_insertproxytaskalias3)(treenode tasksequence, unsigned int executerkey, unsigned int  type, treenode involved1, int involved2,double var1, double var2 , double var3, double var4);
	typedef int          (*_insertproxytaskalias4)(treenode tasksequence, unsigned int executerkey, unsigned int  type);
	typedef int          (*_insertproxytaskalias5)(treenode tasksequence, unsigned int executerkey, unsigned int  type, int involved1, treenode involved2,double var1, double var2 , double var3, double var4);
	typedef int          (*_insertproxytaskalias6)(treenode tasksequence, unsigned int executerkey, unsigned int  type, int involved1);
	typedef int          (*_insertproxytaskalias7)(treenode tasksequence, unsigned int executerkey, unsigned int  type, int involved1, int involved2,double var1, double var2 , double var3, double var4);
	typedef int          (*_insertsynctask)(treenode tasksequence, int taskkey);
	typedef treenode     (*_inserttaskalias)(treenode tasksequence,  unsigned int  type, treenode involved1, treenode involved2 , double var1 , double var2 , double var3 , double var4);
	typedef int          (*_installpackage)(char * packagefile);
	typedef double       (*_inversegaussianalias)( double locate, double scale, double shape , int stream);
	typedef double       (*_inverseweibullalias)( double locate, double scale, double shape, int stream);
	typedef double       (*_invertedweibullalias)( double locate, double scale, double shape, int stream);
	typedef int          (*_ipopen)(treenode object, int index);
	typedef int          (*_ipopno)(treenode, int);
	typedef int          (*_ipready)(treenode object, int index);
	typedef int          (*_isclasstype)(treenode obj, int ctype);
	typedef int          (*_isclasstypealias1)(treenode obj, int classtype);
	typedef int          (*_isclasstypealias2)(treenode obj, char* classtype);
	typedef int          (*_isedgeforward)(treenode netnode, int outport);
	typedef int          (*_iskeydownalias)(int key);
	typedef double       (*_johnsonboundedalias)( double a,      double b,     double shape1,  double shape2 , int stream);
	typedef double       (*_johnsonunboundedalias)( double locate, double scale, double shape1, double shape2, int stream);
	typedef HWND         (*_keyboardfocus)(unsigned int x);
	typedef treenode     (*_label)(treenode object, char* labelname);
	typedef double       (*_laplacealias)( double locate, double scale, int stream);
	typedef treenode     (*_last)(treenode);
	typedef treenode     (*_lastclickednode)();
	typedef double       (*_lastkey)();
	typedef double       (*_lastkeydown)();
	typedef double       (*_lastkeyup)();
	typedef double       (*_le)(double n1, double n2);
	typedef treenode     (*_library)();
	typedef int          (*_license)();
	typedef double       (*_listboxrefresh)(treenode thecombo);
	typedef double       (*_listinlist)(n30argsinterface);
	typedef double       (*_listmax)(n30argsinterface);
	typedef double       (*_listmaximum)(n30argsinterface);
	typedef double       (*_listmean)(n30argsinterface);
	typedef double       (*_listmin)(n30argsinterface);
	typedef double       (*_listminimum)(n30argsinterface);
	typedef double       (*_listmul)(n30argsinterface);
	typedef double       (*_listsub)(n30argsinterface);
	typedef double       (*_listsum)(n30argsinterface);
	typedef treenode     (*_lladd)(treenode x, treenode toadd);
	typedef void         (*_lladddata)(treenode owner, int datatype);
	typedef treenode     (*_llbranch)(treenode thenode);
	typedef void         (*_llcleanup)(treenode x);
	typedef void         (*_lldelete)(treenode x);
	typedef treenode     (*_llfind)(treenode x, char* name);
	typedef int          (*_llgetallocsize)();
	typedef void*        (*_llgetdata)(treenode node);
	typedef void         (*_llinitialize)(treenode);
	typedef double       (*_llinsert)(treenode node, treenode container, treenode newTreeNode);
	typedef treenode     (*_llinsertbranch)(treenode x);
	typedef double       (*_llinsertinto)(treenode node, treenode container, treenode newTreeNode);
	typedef treenode     (*_lllastitem)(treenode x);
	typedef treenode     (*_llnew)();
	typedef size_t       (*_llposition)(treenode x);
	typedef double       (*_llreceivemessage)(treenode , int , EventDataStruct* , char* , int , CallPoint* , treenode );
	typedef void         (*_llremove)(treenode owner, treenode x);
	typedef double*      (*_llsdf)(treenode node);
	typedef int          (*_llsize)(treenode thenode);
	typedef treenode     (*_llstep)(treenode thenode, int stepnum);
	typedef double       (*_loadimage)(char * thefile, char * thename);
	typedef double       (*_loadsound)(char *,char *);
	typedef double       (*_loadthreedobject)(char * thefile, char * thename);
	typedef double*      (*_loc_clock)();
	typedef treenode     (*_loc_medialist)();
	typedef treenode     (*_loc_medialist_images)();
	typedef treenode     (*_loc_medialist_objects)();
	typedef treenode     (*_loc_medialist_sounds)();
	typedef treenode     (*_loc_tools)();
	typedef treenode     (*_loc_undolist)();
	typedef double       (*_logarithmicalias)( double theta, int stream);
	typedef void         (*_logeventalias1)(int _eventcode, treenode object, treenode involved, double p1, double p2, double p3, double p4);
	typedef void         (*_logeventalias2)(char* name, treenode object, treenode involved, double p1, double p2, double p3, double p4);
	typedef double       (*_logisticalias)( double locate, double scale, int stream);
	typedef double       (*_loglaplacealias)( double locate, double scale, double shape, int stream);
	typedef double       (*_loglogisticalias)( double locate, double scale, double shape, int stream);
	typedef double       (*_lognormal2alias)(double locate, double scale, double shape, int stream);
	typedef double       (*_lognormalalias)( double locate, double scale, double shape, int stream);
	typedef double       (*_lt)(double n1, double n2);
	typedef size_t       (*_maintenancealias)(int command, double state, char *info);
	typedef treenode     (*_maintree)();
	typedef double       (*_makeactive)(treenode obj);
	typedef double       (*_makehisto)(treenode data, treenode dest, int nrofbuckets, double minval, double maxval);
	typedef double       (*_maxof) (double a, double b);
	typedef double       (*_mediareset)();
	typedef double       (*_menubelow)(HMENU m, double x);
	typedef double       (*_menucheck)(HMENU m, double x, double y);
	typedef double       (*_menugray)(HMENU m, double x, double y);
	typedef double       (*_menumain)();
	typedef void 		 (*_mesh)(treenode meshnode, unsigned int perVertexAttribs, unsigned int flags);
	typedef int  		 (*_meshaddvertex)(treenode meshnode);
	typedef unsigned int (*_meshaddcustomvertexattrib)(treenode meshnode, const char* name, int componentsPerVertex, GLenum type, bool isNormalized);
	typedef void 		 (*_meshsetvertexattrib)(treenode meshnode, unsigned int vertIndex, unsigned int attribId, float p1, float p2, float p3, float p4);
	typedef void 		 (*_meshsetattrib)(treenode meshnode, unsigned int attribId, float p1, float p2, float p3, float p4);
	typedef void		 (*_meshdraw)(treenode meshnode, int drawMode, int offset, int count, int stride);
	typedef int			 (*_meshaddindex)(treenode meshnode, unsigned int index);
	typedef double		 (*_meshinfo)(treenode meshnode, int type, unsigned int index, unsigned int param);
	typedef double       (*_minof) (double a, double b);
	typedef double       (*_minutes)(double val);
	typedef treenode     (*_model)();
	typedef char*        (*_modeldir_cstr)();
	typedef double       (*_modeleditmode)(int mode);
	typedef double       (*_module)(int cmd, int ptr, char *par, double n);
	typedef int          (*_moveobjectalias1)(treenode client, treenode destination, int port);
	typedef int          (*_moveobjectalias2)(treenode client, treenode destination, int port, int receivingport);
	typedef int          (*_moveobjectstatsupdate_content)(treenode container, unsigned int);
	typedef int          (*_moveobjectstatsupdate_staytime)(treenode container, double * client);
	typedef int          (*_movetablecolalias)(treenode table, int column, int newcolumn);
	typedef int          (*_movetablerowalias)(treenode table, int row, int newrow);
	typedef double       (*_movetasksequence)(treenode tasksequence, treenode dispatcher);
	typedef double       (*_mph)(double val);
	typedef double       (*_msgalias)(char * a, char * b, int mode);
	typedef double       (*_mul)(double n1, double n2);
	typedef char*        ( *_namebbgetbuffer)(treenode node);
	typedef int          (*_namebbgetsize)(treenode node);
	typedef int          (*_namebbsetsize)(treenode node, int size);
	typedef double       (*_nametomodelpath)(treenode toname, treenode thenode);
	typedef unsigned int (*_ncols)(treenode node);
	typedef double       (*_ne)(double n1, double n2);
	typedef double       (*_negbinomialalias)( int    s,      double p  , int stream);
	typedef treenode     (*_netnodefromrank)(int netnoderank);
	typedef treenode     (*_next)(treenode node);
	typedef treenode     (*_nextforobjectselectionset)(treenode curnode, treenode topnode);
	typedef treenode     (*_nextforobjecttreeunder)(treenode curnode, treenode topnode);
	typedef treenode     (*_nodeadddata)(treenode target, int type);
	typedef treenode     (*_nodealias)(char *path,treenode from);
	typedef int          (*_nodealloc)(treenode curnode, unsigned int size);
	typedef double       (*_nodebreak)(treenode attnode);
	typedef treenode     (*_nodedeldata)(treenode target);
	typedef treenode     (*_nodefromwindow)(HWND x);
	typedef treenode     (*_nodeinsertafter)(treenode target);
	typedef treenode     (*_nodeinsertinto)(treenode target);
	typedef double       (*_nodejoin)(treenode attnode, treenode attnode2);
	typedef treenode     (*_nodepoint)(treenode attnode, treenode attnode2);
	typedef char*        (*_nodetomodelpath_cstr)(treenode from, int byname);
	typedef int          (*_nodetotextpath)(treenode node, char * buffer);
	typedef int          (*_nodetotextpath_indexed)(treenode node, char * buffer);
	typedef double       (*_normalalias)( double mean,   double stddev  , int stream);
	typedef double       (*_not)(double);
	typedef double       (*_nrcp)(treenode node);
	typedef double       (*_nrip)(treenode node);
	typedef double       (*_nrop)(treenode node);
	typedef unsigned int (*_nrows)(treenode node);
	typedef double       (*_numconnections)();
	typedef int          (*_objectconnect)(treenode a, treenode b);
	typedef double       (*_objectexists)(treenode);
	typedef int          (*_objectsoundcode)(treenode object, int defaultsound);
	typedef int          (*_odtgetallocsize)();
	typedef int          (*_openallip)(treenode);
	typedef int          (*_openallop)(treenode);
	typedef int          (*_openflexsimchart)(char *file1, char *file2);
	typedef double       (*_openglcolor)(double red, double green, double blue, double alpha);
	typedef double       (*_opengllighting)(double onoff);
	typedef double       (*_openinput)(treenode object);
	typedef double       (*_openip)(treenode node, int index);
	typedef double       (*_opennodeedge)(treenode curnode, int edgenum);
	typedef double       (*_openop)(treenode node, int index);
	typedef double       (*_openoutput)(treenode object);
	typedef int          (*_opipno)(treenode, int);
	typedef int          (*_opopen)(treenode object, int index);
	typedef int          (*_opready)(treenode object, int index);
	typedef double       (*_optimizenetwork)();
	typedef double       (*_optquest)(int command, int action, double numparam, char * strparam, double p1, double p2, double p3, double p4);
	typedef double       (*_or)(double, double);
	typedef treenode     (*_outobject)(treenode, int);
	typedef double       (*_outputopen)(treenode obj);
	typedef double       (*_outputtreecontent)(treenode target, char * filename);
	typedef treenode     (*_ownerobject)(treenode);
	typedef treenode     (*_ownerview)(treenode);
	typedef double       (*_paretoalias)( double min, double scale, int stream);
	typedef char*        (*_parg_cstr)();
	typedef double       (*__parqty)( CallPoint * callpoint);
	typedef int          (*_particlecreate)(treenode c);
	typedef int          (*_particlemove)(treenode client, treenode destination);
	typedef double       (*_particleset)(treenode viewnode, int setno, int cmd, double p1, double p2, double p3, double p4, double p5, double p6);
	typedef int          (*_pc)(char m);
	typedef int          (*_pd)(int m);
	typedef char*        (*_pdir_cstr)();
	typedef double       (*_pearsont5alias)( double locate, double scale, double shape, int stream);
	typedef double       (*_pearsont6alias)( double locate, double scale, double shape1, double shape2, int stream);
	typedef int          (*_pf)(double m);
	typedef char*        (*_pfile_cstr)();
	typedef double       (*_pi)();
	typedef double       (*_pickcolor)(double red, double green, double blue);
	typedef double       (*_pickcolornode)(treenode cnode);
	typedef double       (*_pickedcolorblue)();
	typedef double       (*_pickedcolorgreen)();
	typedef double       (*_pickedcolorred)();
	typedef double       (*_pickfile)(char *extension,char *extensiondesc, char * defaultreturn);
	typedef int          (*_picklistapply)(treenode thecombo);
	typedef double       (*_pickoffsetx)(treenode station, treenode item, treenode otherobject);
	typedef double       (*_pickoffsety)(treenode station, treenode item, treenode otherobject);
	typedef double       (*_pickoffsetz)(treenode station, treenode item, treenode otherobject);
	typedef double       (*_placeoffsetx)(treenode station, treenode item, treenode otherobject);
	typedef double       (*_placeoffsety)(treenode station, treenode item, treenode otherobject);
	typedef double       (*_placeoffsetz)(treenode station, treenode item, treenode otherobject);
	typedef double       (*_poissonalias)( double mean, int stream);
	typedef HMENU        (*_popupmenu)(treenode thenode);
	typedef double       (*_postclosewindowmessage)(treenode viewnode);
	typedef double       (*_postmovewindowupdate)(treenode thenode);
	typedef int          (*_pr)();
	typedef treenode     (*_prev)(treenode node);
	typedef double       (*_profileeventsalias)(int removedevents);
	typedef void         (*_profilekinematics)(treenode infonode, short index);
	typedef double       (*_profiletasksequence)(treenode ts);
	typedef int          (*_pt_importedfunction)(char* m);
	typedef double       (*_qstudentt)(double quant, int df);
	typedef double       (*_rackdrawfilledcell)(treenode rack, int bay, int level, double x, double y, double z, double sx, double sy, double sz, double red, double green, double blue, int glbeginend);
	typedef double       (*_rackdrawvirtualcontent)(treenode rack,double bayfillperc, double levelfillperc, double itemdepth, double red, double green, double blue, double virtualonly);
	typedef double       (*_rackgetbaycontent)(treenode rack, int bay);
	typedef double       (*_rackgetbayloc)(treenode rack,int bay);
	typedef double       (*_rackgetbayofitem)(treenode rack, treenode item);
	typedef double       (*_rackgetbaysize)(treenode rack,int bay);
	typedef double       (*_rackgetcellcontent)(treenode rack, int bay, int level);
	typedef double       (*_rackgetcellvar)(treenode rack, int bay, int level, int varnum, treenode storedlabel);
	typedef treenode     (*_rackgetcontenttable)(treenode object);
	typedef treenode     (*_rackgetitembybaylevel)(treenode rack, int bay, int level, int itemrank);
	typedef double       (*_rackgetlevelloc)(treenode rack,int bay, int level);
	typedef double       (*_rackgetlevelofitem)(treenode rack, treenode item);
	typedef double       (*_rackgetlevelsize)(treenode rack,int bay, int level);
	typedef double       (*_rackgetnrofbays)(treenode rack);
	typedef double       (*_rackgetnroflevels)(treenode rack, int bay);
	typedef double       (*_rackrecycleitem)(treenode rack, treenode item, int binrank);
	typedef treenode     (*_rackrestoreitem)(treenode rack, int binrank, int bay, int level, int position);
	typedef double       (*_racksetcellcontent)(treenode rack, int bay, int level, int contentval);
	typedef double       (*_racksetcellvar)(treenode rack, int bay, int level, int varnum, double value, treenode storedlabel);
	typedef double       (*_radianstodegrees)(double n);
	typedef double       (*_randantithetic)(int on);
	typedef double       (*_randinit)(double stream, double value);
	typedef double       (*_randnext)(double stream);
	typedef double       (*_randomwalkalias)( double locate, double scale, double shape, int stream);
	typedef long         (*_randstate)(int stream );
	typedef treenode     (*_rank)(treenode,int);
	typedef int          (*_rankfromnetnode)(treenode netnode);
	typedef treenode     (*_rankobj)(treenode container, int therank);
	typedef size_t       (*_realtime)(int thing);
	typedef double       (*_reassignnetnode)(treenode taskexecuter, treenode netnode);
	typedef int          (*_rebindobjectattributes)(treenode object);
	typedef double       (*_receiveitem_alias1)(treenode station);
	typedef double       (*_receiveitem_alias2)(treenode station, int port);
	typedef size_t       (*_recover)(int phase);
	typedef double       (*_recycleitem)(treenode item, int binrank);
	typedef double       (*_recyclenode)(treenode node, treenode containerbranch);
	typedef double       (*_redirectconsole)(int console, treenode newwindow);
	typedef double       (*_redirectconsole)(int console, treenode newwindow);
	typedef double       (*_redirectnetworktraveler)(treenode traveler, treenode newdest);
	typedef int          (*_refreshcommand)(treenode commandnode, int structure);
	typedef int          (*_refreshcommandlist)();
	typedef int          (*_refreshglobalvariables)();
	typedef int          (*_refreshview)(treenode xx);
	typedef treenode     (*_reftablealias)(char* globaltablename);
	typedef int          (*_registereventtype)(char* name);
	typedef double       (*_releaseitem_alias1)(treenode item);
	typedef double       (*_releaseitem_alias2)(treenode item, int port);
	typedef double       (*_relloc)(treenode primary, treenode start, int xyz);
	typedef int          (*_removeallcouplingreferences)(treenode xx);
	typedef int 		 (*_removebundleentry)(treenode x, int entrynum);
	typedef int          (*_removeeventsofobjectalias)(treenode object, double simtime, int code, char* data,  treenode involvedobject);
	typedef int          (*_removefirstbundleentry)(treenode x);
	typedef int          (*_removelastbundleentry)(treenode x);
	typedef double       (*_reordertasks)(treenode involved);
	typedef double       (*_repaintall)();
	typedef double       (*_repaintallactive)();
	typedef int          (*_repaintview)(treenode xx);
	typedef double       (*_replacedata_n)(treenode start, double value, double replace);
	typedef double       (*_replacedata_s)(treenode start, char * pattern, char * replace, int replication);
	typedef double       (*_replacename)(treenode start, char * pattern, char * replace, int replaceyesno);
	typedef double       (*_report)(treenode node, char *, int);
	typedef double       (*_reportmode)(int mode);
	typedef void         (*_reportobjectfunctionexception)(char* objectfunctionname, treenode instance, treenode involved, treenode theclass);
	typedef double       (*_repositionhighlightededits)(treenode treeviewnode);
	typedef double       (*_requestoperators)(treenode dispatcher, treenode station, treenode involved, int nrofops, double priority, int preempt);
	typedef double       (*_rerankbesttask)(treenode involved);
	typedef double       (*_reset)();
	typedef double       (*_resetexperiment)();
	typedef double       (*_resetlayer)(treenode curlayer);
	typedef double       (*_resetmodelalias)(int mode);
	typedef double       (*_resetstats)();
	typedef unsigned int (*_resetuniqueid)(treenode theitem);
	typedef int          (*_restoreeventsofobjectalias)(treenode object, double delaytime, double simtime, int code, char* data,  treenode involvedobject);
	typedef void         (*_resumeanimationalias1)(treenode theobject, int animnr, int resumeAtType, double resumeAtVal);
	typedef void         (*_resumeanimationalias2)(treenode theobject, char* animname, int resumeAtType, double resumeAtVal);
	typedef double       (*_resumeinput)(treenode object);
	typedef double       (*_resumeinput)(treenode object);
	typedef double       (*_resumeobjectalias)(treenode involved, int id);
	typedef double       (*_resumeoutput)(treenode object);
	typedef double       (*_resumeoutput)(treenode object);
	typedef double       (*_resumetransportsin)(treenode object, int rank);
	typedef double       (*_resumetransportsout)(treenode object, int rank);
	typedef double       (*_richeditaddtext)(treenode theedit, char * thetext, int protectedflag, int lastone);
	typedef char*        (*_richedittoken)(treenode theedit, int index, ByteBlock * resultblock);
	// round() is a C++11 feature available in vs2013+
	#if _MSC_VER < 1800
	typedef double       (*_roundalias1)(double n1);
	#endif
	typedef double       (*_roundalias2)(double n1, int precision);
	typedef double       (*_rundocument)(char* cmd, char * file);
	typedef double       (*_runexpertfit)();
	typedef double       (*_runfunction)(int noreset );
	typedef double       (*_runprogram)(char * s);
	typedef double       (*_runspeedalias)(double n1, double n2);
	typedef double       (*_savebyname)(treenode tree,char *name);
	typedef double       (*_savestoppedtransportin)(treenode object, treenode transporter);
	typedef double       (*_savestoppedtransportout)(treenode object, treenode transporter);
	typedef double       (*_savetree)(treenode tree, char * extension, char * extensiondesc, char *path);
	typedef int          (*_scaleeventsofobject)(treenode object, double scalefactor, double eventtime, int code);
	typedef double       (*_scalekinematicstotime)(treenode kinematics, int kinematicnr, double totime);
	typedef int          (*_sdtgetbindmode)();
	typedef int          (*_sdtisdisplayverbose)();
	typedef double       (*_searchdata_n)(treenode start, double value);
	typedef double       (*_searchdata_s)(treenode start, char * pattern, int replication);
	typedef treenode     (*_searchfornode)(char* searchstr, treenode rootnode, int nth, int searchobjects);
	typedef double       (*_searchname)(treenode start, char * pattern);
	typedef double       (*_selectedx)(treenode target);
	typedef double       (*_selectedy)(treenode target);
	typedef double       (*_selectedz)(treenode target);
	typedef double       (*_senddelayedmessage)(treenode toobject, double delaytime, treenode fromobject, double par1, double par2, double par3);
	typedef int          (*_sendwindowmessage)(treenode view, int command, WPARAM wParam, LPARAM lParam);
	typedef double       (*_serveraccept)(int sock);
	typedef double       (*_servercloseconnection)(int sock);
	typedef double       (*_serverclosemain)();
	typedef double       (*_servercreatemain)(int sock);
	typedef double       (*_serverreceivealias)(int skt, char *Buf, int BufSize, int NoBlock);
	typedef double       (*_serversendalias)(int skt, char *Msg, int len);
	typedef treenode     (*_set)(treenode attnode, double value);
	typedef int          (*_setapplicationtitle)(char *title);
	typedef int          (*_setbundlevaluealias1)(treenode x, int entrynr, char* fieldname, double val);
	typedef int          (*_setbundlevaluealias2)(treenode x, int entrynr, int fieldnr, double val);
	typedef int          (*_setbundlevaluealias3)(treenode x, int entrynr, char* fieldname, char* val);
	typedef int          (*_setbundlevaluealias4)(treenode x, int entrynr, int fieldnr, char* val);
	typedef double       (*_setcameradirection)(treenode view, double x, double y, double z, double rx, double ry, double rz);
	typedef double       (*_setcameravolume)(treenode view,double w, double h, double nearc, double farc, double mag, double fov, double orthopers, double firstperson);
	typedef double       (*_setcenter)(treenode node, double x, double y, double z);
	typedef double       (*_setchecked)(treenode view, int checked);
	typedef double       (*_setcollisioncheck)(treenode collisionobj, double val,double interval);
	typedef double       (*_setcolor)(treenode involved, double red, double green, double blue);
	typedef int          (*_setcursor)(int cursorid);
	typedef double       (*_setcustomdisplayfunction)(treenode obj, customdisplayfunction);
	typedef double       (*_setdrawnamefunction)(int boxwidth, int boxheight, treenode x, double p1, double p2, double p3);
	typedef double       (*_setdropcoords)(treenode theview);
	typedef void         (*_setdropcoordsmanual)(double x, double y, double z);
	typedef double       (*_seteventtime)(char *eventname, double timeval, double mode, double newevent);
	typedef double       (*_setframe)(treenode obj, int inframe);
	typedef double       (*_setiteminvolved)(treenode item, treenode involved);
	typedef double       (*_setitemsendto)(treenode item, int sendto);
	typedef double       (*_setitemtype)(treenode object, double value);
	typedef double       (*_setitemvar)(treenode item, int index, double val);
	typedef void         (*_setkinematicsrotoffset)(treenode infonode, double _rx, double _ry, double _rz);
	typedef double       (*_setlabelnum)(treenode object, char* labelname, double value);
	typedef double       (*_setloc)(treenode node, double x, double y, double z);
	typedef double       (*_setmessageloopsleep)(double a, double b);
	typedef treenode     (*_setname_alias)(treenode node, char* name);
	typedef treenode     (*_setnodenum)(treenode attnode, double value);
	typedef double       (*_setobjectbillboard)(treenode thenode, int mode);
	typedef double       (*_setobjectimageindex)(treenode object, double index);
	typedef double       (*_setobjectshapeindex)(treenode object, double index);
	typedef double       (*_setobjecttextureindex)(treenode object, double index);
	typedef int          (*_setpickingdrawfocusalias)(treenode theview, treenode focus, int selectiontype, treenode secondaryfocus, int detectdrag);
	typedef double       (*_setpreempt)(treenode tasksequence, unsigned int newpreempt);
	typedef double       (*_setpriority)(treenode tasksequence, double newpriority);
	typedef double       (*_setprogressbar)(double val);
	typedef int          (*_setproperty)(char *filename, int property, char *newvalue);
	typedef void         (*_setquerynode)(treenode queryNode);
	typedef treenode     (*_setrank)(treenode, int);
	typedef double       (*_setresetposition)(treenode obj);
	typedef double       (*_setrot)(treenode involved, double rx, double ry, double rz);
	typedef treenode     (*_setsdtvalue)(treenode sdtNode, const char* valName, Variant toVal);
	typedef double       (*_setselectedobject)(treenode target, treenode newselected);
	typedef double       (*_setsize)(treenode involved, double sx, double sy, double sz);
	typedef int          (*_setstate_s)(treenode , char *);
	typedef int          (*_setstatealias1)(treenode , int);
	typedef int          (*_setstatealias2)(treenode , int, int);
	typedef int          (*_setstatealias3)(treenode , int, const char*);
	typedef int          (*_setstatealias4)(treenode , int, treenode);
	typedef double       (*_settable)(treenode node, unsigned int xsize, unsigned int ysize, double datatype, double overwrite);
	typedef double       (*_settablenumalias)(char * table, int row, int col, double value);
	typedef double       (*_settablesizealias)(char* globaltablename,int nrows,int ncols, int type, int overwrite);
	typedef double       (*_settablestr)(char * table, int row, int col, char * value);
	typedef double       (*_setvarnumalias)(treenode object, char *varname, double val);
	typedef double       (*_setvarstralias)(treenode object, char *varname, char *val);
	typedef double       (*_setviewtextalias)(treenode target, char *);
	typedef double       (*_shiftpressed)();
	typedef double       (*_showcompilerconsole)();
	typedef int          (*_showgraphicinfo)(int showhide, char * file);
	typedef int          (*_showhtmlhelpalias)(char* path);
	typedef double       (*_showprogressbar_importedfunction)(char* text);
	typedef double       (*_sign)(double n1);
	typedef treenode     (*_so)();
	typedef double       (*_socketend)();
	typedef double       (*_socketinit)();
	typedef double       (*_sorttable_alias1)(char *table, int col);
	typedef double       (*_sorttable_alias2)(treenode table, int col);
	typedef double       (*_sorttable_alias3)(int table, int col);
	typedef double       (*_soundchange)(treenode soundnode, double sound, double vol, double pit, double rep, double bal);
	typedef double       (*_soundload)(char *);
	typedef double       (*_soundplay)(treenode soundnode, double sound, double vol, double pit, double rep, double bal);
	typedef double       (*_soundplayfile)(treenode soundnode, char * soundfilename, double vol, double pit, double rep, double bal);
	typedef double       (*_soundstop)(treenode soundnode, double sound);
	typedef double       (*_spacebase)();
	typedef double       (*_spaceglobal)();
	typedef double       (*_spaceobject)();
	typedef double       (*_spacerotate)(double x, double y, double z);
	typedef double       (*_spacescale)(double x, double y, double z);
	typedef double       (*_spacetranslate)(double x, double y, double z);
	typedef double       (*_spline)(treenode spline, double p);
	typedef double       (*_splinedraw)(treenode spline);
	typedef double       (*_splinedrawextrusion)(treenode thespline, double step, double wide, double high, int textop, int texside);
	typedef double       (*_splinelength)();
	typedef double       (*_splineposobject)(treenode object, treenode relative);
	typedef double       (*_splinerx)();
	typedef double       (*_splinery)();
	typedef double       (*_splinerz)();
	typedef double       (*_splinex)();
	typedef double       (*_spliney)();
	typedef double       (*_splinez)();
	typedef void         (*_startanimationalias1)(treenode theobject, int animnr, int durationtype, double duration, int repeattype, double repeatvalue);
	typedef void         (*_startanimationalias2)(treenode theobject, char* animname, int durationtype, double duration, int repeattype, double repeatvalue);
	typedef double       (*_startlisten)(treenode listener);
	typedef double       (*_statisticaltime)();
	typedef double       (*_statsenablemask)(double x);
	typedef double       (*_step)();
	typedef int          (*_stick)(int stickno, int xyzb, unsigned int w, UINT p);
	typedef double       (*_stopalias)(int fast );
	typedef void         (*_stopanimationalias1)(treenode theobject, int animnr);
	typedef void         (*_stopanimationalias2)(treenode theobject, char* animname);
	typedef double       (*_stopinput)(treenode object);
	typedef double       (*_stoplisten)(treenode listener);
	typedef double       (*_stopobject)(treenode involved, int state, int id, double priority);
	typedef double       (*_stopoutput)(treenode object);
	typedef double       (*_stoptimealias)(double n1, double n2);
	typedef double       (*__stringreturn)(char* result, CallPoint * callpoint);
	typedef int          (*_stringsearchalias1)(char* str, char* substr, int startpos);
	typedef int          (*_stringsearchalias2)(char* str, char* substr, int startpos, int flags);
	typedef int          (*_stringsequal)(char *s1, char *s2);
	typedef char*        (*_stringtokenalias)(char* token, char* delimit);
	typedef double       (*_stringtonumalias)(char * str1);
	typedef double       (*_sub)(double n1, double n2);
	typedef double       (*_suspenddraw)(double x);
	typedef treenode     (*_sv)();
	typedef int          (*_swapnoderanks)(treenode, int, int);
	typedef int          (*_swaptablecolsalias)(treenode table, int column, int column2);
	typedef int          (*_swaptablerowsalias)(treenode table, int row, int row2);
	typedef double       (*_switch_activelisteners)(treenode node, int on);
	typedef double       (*_switch_cppfunc)(treenode node, int on);
	typedef double       (*_switch_destroyonreset)(treenode node, int on);
	typedef double       (*_switch_dllfunc)(treenode node, int on);
	typedef double       (*_switch_enablestats)(treenode node, int on);
	typedef double       (*_switch_expanded)(treenode node, int on);
	typedef int          (*_switch_flexscript)(treenode thenode, int toggle);
	typedef double       (*_switch_hidden)(treenode node, int on);
	typedef double       (*_switch_hidebase)(treenode node, int on);
	typedef double       (*_switch_hideconnectors)(treenode node, int on);
	typedef double       (*_switch_hidecontents)(treenode node, int on);
	typedef double       (*_switch_hidelabel)(treenode node, int on);
	typedef double       (*_switch_hideshape)(treenode node, int on);
	typedef double       (*_switch_noselect)(treenode node, int on);
	typedef double       (*_switch_preservecoupling)(treenode node, int on);
	typedef double       (*_switch_orphancoupling)(treenode node, int on);
	typedef double       (*_switch_protected)(treenode node, int on);
	typedef double       (*_switch_selected)(treenode node, int on);
	typedef double       (*_switch_showobject)(treenode node, int on);
	typedef double       (*_switch_statelocked)(treenode node, int on);
	typedef double       (*_switch_stateused)(treenode node, int on);
	typedef double       (*_switch_variable)(treenode object, char * variable, int on);
	typedef HWND         (*_systemwindow)(int window);
	typedef int          (*_templatetocode)(treenode thecode, treenode theedit);
	typedef int          (*_toggleallcodestates)(treenode x, int ascpp);
	typedef treenode     (*_tonodealias1)(size_t x);
	typedef treenode     (*_tonodealias2)(double x);
	typedef treenode     (*_tonodealias3)(char* x);
	typedef treenode     (*_tonodealias4)(void* x);
	typedef void*        (*_toptr)(int x);
	typedef double       (*_tracemaskevents)(double x);
	typedef double       (*_tracemaskobject)(treenode x);
	typedef double       (*_tracemasktime)(double x, double y);
	typedef double       (*_trackpopup)(treenode x);
	typedef double       (*_trafficcontrolinfo)(treenode tc, int info, double _a, double _b);
	typedef double       (*_transfernode)(treenode thenode, treenode newcontainer);
	typedef double       (*_transfernodeobj)(treenode thenode, treenode newcontainer);
	typedef double       (*_transformvectorxy)(double * vector, double matrix[4][4]);
	typedef double       (*_transitionport)();
	typedef double       (*_transportincompletealias)(treenode object, treenode item, int portnumber, treenode transporter);
	typedef double       (*_transportoutcompletealias)(treenode object, treenode item, int portnumber, treenode transporter);
	typedef double       (*_travelto)(treenode object, treenode spline, double x, double y, double z, double vmax, double acc, double dec);
	typedef double       (*_traveltoupdate)(treenode object, treenode spline);
	typedef int          (*_treewin__loadtree)(treenode xx, char * buffera);
	typedef double       (*_triangularalias)( double min,    double max,   double mode, int stream);
	// trunc() is a C++11 feature available in vs2013+
	#if _MSC_VER < 1800
	typedef double       (*_trunc)(double n1);
	#endif
	typedef int          (*_undo)(treenode view);
	typedef int          (*_undos)(int state, int set);
	typedef double       (*_uniformalias)( double a,      double b , int stream);
	typedef treenode     (*_up)(treenode node);
	typedef void         (*_updateanimationalias1)(treenode object);
	typedef void         (*_updateanimationalias2)(treenode object, double updatetime, int animnr);
	typedef void         (*_updatekinematicsalias)(treenode infonode, treenode object, double updatetime);
	typedef double       (*_updatelocations)(treenode object);
	typedef double       (*_updatestate_alias1)(treenode obj);
	typedef double       (*_updatestate_alias2)(treenode obj, int profilenr);
	typedef void         (*_updateundorecord)(TreeNode* view, int uniqueid, int updatetype, double p1, double p2);
	typedef double       (*_uselisteners)(double x);
	typedef char*		 (*_userdatadir_cstr)();
	typedef double       (*_userinput)(treenode variable, char* prompt);
	typedef double       (*_validatenamealias)(treenode current, int isview, treenode obj);
	typedef int          (*_validlink)(treenode , char *);
	typedef double       (*_valuetohistogram)(double val, treenode hist, double start, double end, double resolution, int xyformat, double * _lo, double * _hi);
	typedef treenode     (*_var)(treenode node, int index);
	typedef treenode     (*_var_s)(treenode node, char * name);
	typedef double*      (*_vectorproject)(treenode origin,double xposition, double yposition, double zposition, treenode ontoobject, double * tempvector);
	typedef double       (*_vectorprojectx)(treenode origin,double xposition, double yposition, double zposition, treenode ontoobject);
	typedef double       (*_vectorprojecty)(treenode origin,double xposition, double yposition, double zposition, treenode ontoobject);
	typedef double       (*_vectorprojectz)(treenode origin,double xposition, double yposition, double zposition, treenode ontoobject);
	typedef double       (*_viewdist)(treenode v, treenode ob);
	typedef treenode     (*_views)();
	typedef double       (*_viewtofile_alias1)(treenode theview, char* s);
	typedef double       (*_viewtofile_alias2)(treenode theview, char* s, int w, int h);
	typedef double       (*_webcommandalias)(char* commandname, n10argsinterface);
	typedef double       (*_weibullalias)( double locate, double scale, double shape, int stream);
	typedef HWND         (*_windowfromnode)(treenode x);
	typedef double       (*_windowgray)(HWND control, int gray);
	typedef HMENU        (*_windowmenu)(treenode thenode);
	typedef double       (*_windowmove)(unsigned int w, double a, double b, double c, double d, double refresh);
	typedef double       (*_windowshow)(unsigned int w, double show);
	typedef int          (*_windowstylealias)(treenode view, int style, int doexstyle);
	typedef double       (*_xcenter)(treenode obj);
	typedef double       (*_xloc)(treenode obj);
	typedef double       (*_xrot)(treenode obj);
	typedef double       (*_xsize)(treenode obj);
	typedef double       (*_ycenter)(treenode obj);
	typedef double       (*_yloc)(treenode obj);
	typedef double       (*_yrot)(treenode obj);
	typedef double       (*_ysize)(treenode obj);
	typedef double       (*_zcenter)(treenode obj);
	typedef double       (*_zloc)(treenode obj);
	typedef double       (*_zrot)(treenode obj);
	typedef double       (*_zsize)(treenode obj);

	#if defined COMPILING_FLEXSIM_CONTENT || defined COMPILING_MODULE_DLL
		typedef FSfptr   (*_getcorecommandfunction)(int index);
		typedef portinfo (*_inobjectinfo)(treenode, int);
		typedef portinfo (*_outobjectinfo)(treenode, int);
		typedef void     (*_odtcleanup)(ObjectDataType* x);
		typedef void     (*_odtinitialize)(ObjectDataType*);
		typedef int      (*_odtbindstructure)(ObjectDataType*, treenode, unsigned int);
		typedef void     (*_odtbindvariablebynamealias1)(ObjectDataType* odt, const char* name, double& val);
		typedef void     (*_odtbindvariablebynamealias2)(ObjectDataType* odt, const char* name, ByteBlock& val);
		typedef void     (*_odtbindvariablebynamealias3)(ObjectDataType* odt, const char* name, NodeRef& val);
		typedef void     (*_odtbindvariablebynamealias4)(ObjectDataType* odt, const char* name, TreeNode*& val);
		typedef treenode (*_sdtbindbyname)(SimpleDataType* sdt, const char* name, int asSubNode, int dataType, int * added);
		typedef void     (*_sdtbindnodeptrbyname)(SimpleDataType* sdt, const char* name, treenode& val);
		typedef void     (*_sdtbindobjptrbyname)(SimpleDataType* sdt, const char* name, SimpleDataType*& val);
		typedef void     (*_sdtbindsubnodebyname)(SimpleDataType* sdt, const char* name, treenode& val, int datatype);
		typedef void     (*_sdtbinddoublebyname)(SimpleDataType* sdt, const char* name, double& val, int asSubNode);
		typedef void     (*_sdtbindbyteblockbyname)(SimpleDataType* sdt, const char* name, ByteBlock& val, int asSubNode);
		typedef void     (*_sdtbindnoderefbyname)(SimpleDataType* sdt, const char* name, NodeRef& val, int asSubNode);
		typedef void     (*_sdtbind)(SimpleDataType* sdt, int bindMode);
		typedef treenode (*_sdtgetbindtree)(SimpleDataType* sdt);
		typedef treenode (*_nodeaddsimpledata)(treenode x, SimpleDataType* sdt, int bind);
		typedef treenode (*_nodeaddcouplingdata)(treenode x, CouplingDataType* sdt, int bind);
		typedef treenode (*_nodedetachsimpledata)(treenode target);
		typedef void     (*_sdtappendtodisplaystr)(const char* text);
		typedef char*    (*_sdttostring)(SimpleDataType* sdt, int verbose);
		typedef Variant&  (*_sdtgetcurvalue)();
		typedef char*    (*_sdtgetcurvaluename)();
		typedef void     (*_sdtsetvalue)(SimpleDataType* sdt, const char* valName, Variant toVal);
		typedef Variant   (*_sdtgetvalue)(SimpleDataType* sdt, const char* valName);
		typedef char*    (*_couplingtostring)(CouplingDataType* sdt, int verbose);
		typedef void     (*_flexsimeventbind)(FlexSimEvent* e);
		typedef void     (*_flexsimeventexecute)(FlexSimEvent* e);
		typedef void     (*_flexsimeventgetdescription)(FlexSimEvent* e, char* toStr, size_t maxSize);
		typedef treenode (*_createeventalias2)(FlexSimEvent* e);
		typedef void (*_byteblock_write1)(ByteBlock* x, const char *source);
		typedef void (*_byteblock_write2)(ByteBlock* x, const char *source, long unsigned intsize, int nullterminate);
		typedef void (*_byteblock_append)(ByteBlock* x, const char *source);
		typedef bool (*_byteblock_setsize)(ByteBlock* x, long unsigned int size);
		typedef unsigned int (*_byteblock_getsize)(ByteBlock* x);
		typedef char* (*_byteblock_getbuffer)(ByteBlock* x);

		typedef  void (*_mesh_bind)(Mesh* m);
		typedef  void (*_mesh_init)(Mesh* m, unsigned int nrVerts, unsigned int perVertFlags, unsigned int generalFlags);
		typedef  void (*_mesh_cleanup)(Mesh* m, bool isDestructor);
		typedef  void(*_mesh_definevertexattribs)(Mesh* m, unsigned int attribId, float* verts);
		typedef  unsigned int(*_mesh_addcustomvertexattrib)(Mesh* m, const char* name, int componentsPerVertex, GLenum type, bool isNormalized);
		typedef  unsigned int (*_mesh_setvertexattrib)(Mesh* m, int vertIndex, unsigned int attribId, float* vert);
		typedef  void (*_mesh_setmeshattrib)(Mesh* m, unsigned int attribId, float* vert);
		typedef  int (*_mesh_addvertex)(Mesh* m);
		typedef  void (*_mesh_draw)(Mesh* m, int drawMode, int vertOffset, int vertCount, int vertStride);

		typedef void (*_indexedmesh_bind)(IndexedMesh* m);
		typedef void (*_indexedmesh_defineindexbuffer)(IndexedMesh* m, int nr, unsigned int * buffer);
		typedef unsigned int (*_indexedmesh_addindex)(IndexedMesh* m, unsigned int index);
		typedef void (*_indexedmesh_draw)(IndexedMesh* m, int drawMode, int count, int start);
		typedef void (*_indexedmesh_cleanupindexbuffer)(IndexedMesh* m, bool isDestructor);

		typedef Variant(*_fglInfo)(int op, treenode view);
		
	#else
		typedef void (*_flexsimfree)(void*);
		typedef void* (*_flexsimmalloc)(size_t);
		typedef void* (*_flexsimrealloc)(void*, size_t);
		typedef double (*_transportincompletealias)(treenode object, treenode item, int portnumber, treenode transporter);
		typedef double (*_transportoutcompletealias)(treenode object, treenode item, int portnumber, treenode transporter);
	#endif
	
#endif

/*** FLEXSIM FUNCTIONS ***/
DECLARE_FLEXSIM_FUNCTION_1(_executefsfile)
DECLARE_FLEXSIM_FUNCTION_1(_inheritcode)
DECLARE_FLEXSIM_FUNCTION_1(_mpd)
DECLARE_FLEXSIM_FUNCTION_1(_mpf)
DECLARE_FLEXSIM_FUNCTION_1(_mpr)
DECLARE_FLEXSIM_FUNCTION_1(_mpt)
#if FLEXSIM_TARGET_VERSION >= 710
DECLARE_FLEXSIM_FUNCTION_1(_partype)
#endif
DECLARE_FLEXSIM_FUNCTION_1(_parval)
DECLARE_FLEXSIM_FUNCTION_1(_parnode)
DECLARE_FLEXSIM_FUNCTION_1(__parstr)
DECLARE_FLEXSIM_FUNCTION_1(_param)
DECLARE_FLEXSIM_FUNCTION_1(activateview)
DECLARE_FLEXSIM_FUNCTION_1(activedocumentview)
DECLARE_FLEXSIM_FUNCTION_1(activeview)
DECLARE_FLEXSIM_FUNCTION_2(addbundlefieldalias, "addbundlefield");
DECLARE_FLEXSIM_FUNCTION_1(addcommand)
DECLARE_FLEXSIM_FUNCTION_1(addfullhistorymoverecord)
DECLARE_FLEXSIM_FUNCTION_2(addkinematicalias, "addkinematic")
DECLARE_FLEXSIM_FUNCTION_2(addlabel_importedfunction, "addlabel")
DECLARE_FLEXSIM_FUNCTION_2(addtablecolalias, "addtablecol");
DECLARE_FLEXSIM_FUNCTION_2(addtablerowalias, "addtablerow");
DECLARE_FLEXSIM_FUNCTION_2(addtoeventtypelegendalias1,"addtoeventtypelegend")
DECLARE_FLEXSIM_FUNCTION_3(addtoeventtypelegendalias2,"?addtoeventtypelegend@@YAXPADHH0@Z","?addtoeventtypelegend@@YAXPEADHH0@Z")
DECLARE_FLEXSIM_FUNCTION_2(addviewtextalias, "addviewtext")
DECLARE_FLEXSIM_FUNCTION_2(aggregateundorecordsalias, "aggregateundorecords")
DECLARE_FLEXSIM_FUNCTION_1(applyeditstonode)
DECLARE_FLEXSIM_FUNCTION_1(applylinks)
DECLARE_FLEXSIM_FUNCTION_1(applyshapefactors)
DECLARE_FLEXSIM_FUNCTION_1(applytoedits)
DECLARE_FLEXSIM_FUNCTION_2(assertattributealias, "assertattribute")
DECLARE_FLEXSIM_FUNCTION_2(assertlabelalias, "assertlabel")
DECLARE_FLEXSIM_FUNCTION_2(assertsubnodealias, "assertsubnode")
DECLARE_FLEXSIM_FUNCTION_2(assertvariablealias, "assertvariable")
DECLARE_FLEXSIM_FUNCTION_1(attlink)
DECLARE_FLEXSIM_FUNCTION_1(autoloadallmedia)
DECLARE_FLEXSIM_FUNCTION_1(autoloadimages)
DECLARE_FLEXSIM_FUNCTION_1(autoloadshapes)
DECLARE_FLEXSIM_FUNCTION_1(autoloadsounds)
DECLARE_FLEXSIM_FUNCTION_1(aviadd)
DECLARE_FLEXSIM_FUNCTION_1(avifinish)
DECLARE_FLEXSIM_FUNCTION_2(avistart_importedfunction, "avistart")
DECLARE_FLEXSIM_FUNCTION_1(bbgetbuffer)
DECLARE_FLEXSIM_FUNCTION_1(bbgetsize)
DECLARE_FLEXSIM_FUNCTION_1(bbsetsize)
DECLARE_FLEXSIM_FUNCTION_1(beginaggregatedundo)
DECLARE_FLEXSIM_FUNCTION_1(beginignoreundo)
DECLARE_FLEXSIM_FUNCTION_2(bernoullialias, "bernoulli")
DECLARE_FLEXSIM_FUNCTION_2(betaalias, "beta")
DECLARE_FLEXSIM_FUNCTION_1(bindobjectclassvariable)
DECLARE_FLEXSIM_FUNCTION_1(bindtexture)
DECLARE_FLEXSIM_FUNCTION_2(binomialalias, "binomial")
DECLARE_FLEXSIM_FUNCTION_1(bitwiseand)
DECLARE_FLEXSIM_FUNCTION_1(bitwisenot)
DECLARE_FLEXSIM_FUNCTION_1(bitwiseor)
DECLARE_FLEXSIM_FUNCTION_1(buildall)
DECLARE_FLEXSIM_FUNCTION_1(buildnodeflexscript)
DECLARE_FLEXSIM_FUNCTION_1(calculate6DOFrobotinversekinematics)
DECLARE_FLEXSIM_FUNCTION_1(calculateconfidence)
DECLARE_FLEXSIM_FUNCTION_1(callwebscriptmethod)
DECLARE_FLEXSIM_FUNCTION_2(cauchyalias, "cauchy")
DECLARE_FLEXSIM_FUNCTION_1(cdir_cstr)
DECLARE_FLEXSIM_FUNCTION_2(cempiricalalias, "cempirical")
DECLARE_FLEXSIM_FUNCTION_1(centerobject)
DECLARE_FLEXSIM_FUNCTION_1(changedisplay)
DECLARE_FLEXSIM_FUNCTION_1(checkdllconnection)
DECLARE_FLEXSIM_FUNCTION_1(checkoutmodulefeature)
DECLARE_FLEXSIM_FUNCTION_1(classobject)
DECLARE_FLEXSIM_FUNCTION_2(clearbundlealias, "clearbundle");
DECLARE_FLEXSIM_FUNCTION_1(clearconsole)
DECLARE_FLEXSIM_FUNCTION_1(clearcontents)
DECLARE_FLEXSIM_FUNCTION_2(clearglobaltable_alias1, "clearglobaltable")
DECLARE_FLEXSIM_FUNCTION_3(clearglobaltable_alias2, "?clearglobaltable@@YANPAVTreeNode@@@Z","?clearglobaltable@@YANPEAVTreeNode@@@Z")
DECLARE_FLEXSIM_FUNCTION_2(clearglobaltable_alias3, "?clearglobaltable@@YANH@Z")
DECLARE_FLEXSIM_FUNCTION_1(clickcode)
DECLARE_FLEXSIM_FUNCTION_1(clientclose)
DECLARE_FLEXSIM_FUNCTION_2(clientconnectalias, "clientconnect")
DECLARE_FLEXSIM_FUNCTION_1(clientcreate)
DECLARE_FLEXSIM_FUNCTION_2(clientreceivealias, "clientreceive")
DECLARE_FLEXSIM_FUNCTION_2(clientsendalias, "clientsend")
DECLARE_FLEXSIM_FUNCTION_1(closeallip)
DECLARE_FLEXSIM_FUNCTION_1(closeallop)
DECLARE_FLEXSIM_FUNCTION_1(closeinput)
DECLARE_FLEXSIM_FUNCTION_1(closeip)
DECLARE_FLEXSIM_FUNCTION_1(closeop)
DECLARE_FLEXSIM_FUNCTION_1(closeoutput)
DECLARE_FLEXSIM_FUNCTION_1(closeview)
DECLARE_FLEXSIM_FUNCTION_1(cm)
DECLARE_FLEXSIM_FUNCTION_1(cmdcompile)
DECLARE_FLEXSIM_FUNCTION_1(cmddelete)
DECLARE_FLEXSIM_FUNCTION_1(cmdexit)
DECLARE_FLEXSIM_FUNCTION_1(cmdloadbyextension)
DECLARE_FLEXSIM_FUNCTION_1(cmdloadsession)
DECLARE_FLEXSIM_FUNCTION_1(cmdloadtree)
DECLARE_FLEXSIM_FUNCTION_1(cmdnew)
DECLARE_FLEXSIM_FUNCTION_1(cmdopen)
DECLARE_FLEXSIM_FUNCTION_1(cmdsaveas)
DECLARE_FLEXSIM_FUNCTION_1(cmdsavesession)
DECLARE_FLEXSIM_FUNCTION_1(cmdsavetree)
DECLARE_FLEXSIM_FUNCTION_1(codetotemplate)
DECLARE_FLEXSIM_FUNCTION_1(codetotemplatetext_cstr)
DECLARE_FLEXSIM_FUNCTION_1(coloraqua)
DECLARE_FLEXSIM_FUNCTION_2(colorarrayalias1, "colorarray")
DECLARE_FLEXSIM_FUNCTION_3(colorarrayalias2, "?colorarray@@YAXHPAN@Z","?colorarray@@YAXHPEAN@Z")
DECLARE_FLEXSIM_FUNCTION_1(colorblack)
DECLARE_FLEXSIM_FUNCTION_1(colorblue)
DECLARE_FLEXSIM_FUNCTION_1(colorbrown)
DECLARE_FLEXSIM_FUNCTION_1(colorgray)
DECLARE_FLEXSIM_FUNCTION_1(colorgreen)
DECLARE_FLEXSIM_FUNCTION_1(colorlightblue)
DECLARE_FLEXSIM_FUNCTION_1(colorlime)
DECLARE_FLEXSIM_FUNCTION_1(colororange)
DECLARE_FLEXSIM_FUNCTION_1(colorpink)
DECLARE_FLEXSIM_FUNCTION_1(colorpurple)
DECLARE_FLEXSIM_FUNCTION_1(colorrandom)
DECLARE_FLEXSIM_FUNCTION_1(colorred)
DECLARE_FLEXSIM_FUNCTION_1(colorsilver)
DECLARE_FLEXSIM_FUNCTION_1(colorteal)
DECLARE_FLEXSIM_FUNCTION_1(colorwhite)
DECLARE_FLEXSIM_FUNCTION_1(coloryellow)
DECLARE_FLEXSIM_FUNCTION_1(combocurrentnode)
DECLARE_FLEXSIM_FUNCTION_1(comborefresh)
DECLARE_FLEXSIM_FUNCTION_1(commandlineparam)
DECLARE_FLEXSIM_FUNCTION_3(comparetextalias1, "?comparetext@@YAHPAD0H@Z", "?comparetext@@YAHPEAD0H@Z")
DECLARE_FLEXSIM_FUNCTION_1(comparetrees)
DECLARE_FLEXSIM_FUNCTION_1(consoleexecutefs)
DECLARE_FLEXSIM_FUNCTION_1(content)
DECLARE_FLEXSIM_FUNCTION_1(contentobj)
DECLARE_FLEXSIM_FUNCTION_2(contentunderalias, "contentunder")
DECLARE_FLEXSIM_FUNCTION_1(controlpressed)
DECLARE_FLEXSIM_FUNCTION_1(copyattributes)
DECLARE_FLEXSIM_FUNCTION_1(cpcpno)
DECLARE_FLEXSIM_FUNCTION_2(createcopyalias, "createcopy")
DECLARE_FLEXSIM_FUNCTION_1(createcoupling)
DECLARE_FLEXSIM_FUNCTION_1(createeds)
DECLARE_FLEXSIM_FUNCTION_2(createeventalias1, "createevent")
DECLARE_FLEXSIM_FUNCTION_1(createeventex)
DECLARE_FLEXSIM_FUNCTION_2(createinstancealias, "createinstance")
DECLARE_FLEXSIM_FUNCTION_1(createpopup)
DECLARE_FLEXSIM_FUNCTION_1(createundorecord)
DECLARE_FLEXSIM_FUNCTION_1(createview)
DECLARE_FLEXSIM_FUNCTION_1(currentfile_cstr)
DECLARE_FLEXSIM_FUNCTION_1(cursorinfo)
DECLARE_FLEXSIM_FUNCTION_1(daemonstate)
DECLARE_FLEXSIM_FUNCTION_1(dataplot)
DECLARE_FLEXSIM_FUNCTION_1(days)
DECLARE_FLEXSIM_FUNCTION_1(dbchangetable)
DECLARE_FLEXSIM_FUNCTION_1(dbclose)
DECLARE_FLEXSIM_FUNCTION_1(dbexportnode)
DECLARE_FLEXSIM_FUNCTION_1(dbexporttable)
DECLARE_FLEXSIM_FUNCTION_1(dbgetfieldname)
DECLARE_FLEXSIM_FUNCTION_1(dbgetmetrics)
DECLARE_FLEXSIM_FUNCTION_1(dbgetmode)
DECLARE_FLEXSIM_FUNCTION_1(dbnextrow)
DECLARE_FLEXSIM_FUNCTION_1(dbgetnumcols)
DECLARE_FLEXSIM_FUNCTION_1(dbgetnumrows)
DECLARE_FLEXSIM_FUNCTION_1(dbgettablecell)
DECLARE_FLEXSIM_FUNCTION_1(dbgettablenum)
DECLARE_FLEXSIM_FUNCTION_1(dbgettablestr)
DECLARE_FLEXSIM_FUNCTION_1(dbimportnode)
DECLARE_FLEXSIM_FUNCTION_1(dbimporttable)
DECLARE_FLEXSIM_FUNCTION_2(dbopenalias, "dbopen")
DECLARE_FLEXSIM_FUNCTION_1(dbsettablecell)
DECLARE_FLEXSIM_FUNCTION_1(dbsettablenum)
DECLARE_FLEXSIM_FUNCTION_1(dbsettablestr)
DECLARE_FLEXSIM_FUNCTION_3(dbsqlqueryalias, "?dbsqlquery@@YAHPADH@Z", "?dbsqlquery@@YAHPEADH@Z")
DECLARE_FLEXSIM_FUNCTION_2(dbusernamealias, "dbusername")
DECLARE_FLEXSIM_FUNCTION_1(dbviewtable)
DECLARE_FLEXSIM_FUNCTION_1(deactivatekinematics)
DECLARE_FLEXSIM_FUNCTION_1(degreestoradians)
DECLARE_FLEXSIM_FUNCTION_1(delayevents)
DECLARE_FLEXSIM_FUNCTION_1(delayeventsofobject)
DECLARE_FLEXSIM_FUNCTION_1(deleteeds)
DECLARE_FLEXSIM_FUNCTION_2(deletetablecolalias, "deletetablecol");
DECLARE_FLEXSIM_FUNCTION_2(deletetablerowalias, "deletetablerow");
DECLARE_FLEXSIM_FUNCTION_1(dellabel)
DECLARE_FLEXSIM_FUNCTION_2(dempiricalalias, "dempirical")
DECLARE_FLEXSIM_FUNCTION_1(deselectall)
DECLARE_FLEXSIM_FUNCTION_1(destroyevent)
DECLARE_FLEXSIM_FUNCTION_3(destroyeventsofobjectalias1, "?destroyeventsofobject@@YANPAVTreeNode@@@Z","?destroyeventsofobject@@YANPEAVTreeNode@@@Z")
DECLARE_FLEXSIM_FUNCTION_2(destroyeventsofobjectalias2, "destroyeventsofobject")
DECLARE_FLEXSIM_FUNCTION_3(destroyeventsofobjectalias3, "?destroyeventsofobject@@YANPAVTreeNode@@NHPAD0P6AH0NHPAX0@Z@Z","?destroyeventsofobject@@YANPEAVTreeNode@@NHPEAD0P6AH0NHPEAX0@Z@Z")
DECLARE_FLEXSIM_FUNCTION_1(destroynode)
DECLARE_FLEXSIM_FUNCTION_1(destroyobject)
DECLARE_FLEXSIM_FUNCTION_1(diffsign)
DECLARE_FLEXSIM_FUNCTION_1(distfromviewpoint)
DECLARE_FLEXSIM_FUNCTION_1(documentsdir_cstr)
DECLARE_FLEXSIM_FUNCTION_1(documentusercommands)
DECLARE_FLEXSIM_FUNCTION_2(draginfoalias, "draginfo")
DECLARE_FLEXSIM_FUNCTION_1(draw2dcurve)
DECLARE_FLEXSIM_FUNCTION_1(draw3dtext)
DECLARE_FLEXSIM_FUNCTION_1(drawbox)
DECLARE_FLEXSIM_FUNCTION_1(drawcolumn)
DECLARE_FLEXSIM_FUNCTION_2(drawcubealias1, "drawcube")
DECLARE_FLEXSIM_FUNCTION_2(drawcubealias2, "?drawcube@@YANNNNNNNNNNNNN@Z")
DECLARE_FLEXSIM_FUNCTION_2(drawcylinderalias1, "drawcylinder")
DECLARE_FLEXSIM_FUNCTION_2(drawcylinderalias2, "?drawcylinder@@YANNNNNNNNNNNNN@Z")
DECLARE_FLEXSIM_FUNCTION_1(drawdisk)
DECLARE_FLEXSIM_FUNCTION_1(drawflattext)
DECLARE_FLEXSIM_FUNCTION_1(drawfont)
DECLARE_FLEXSIM_FUNCTION_1(drawline)
DECLARE_FLEXSIM_FUNCTION_1(drawobjectpart)
DECLARE_FLEXSIM_FUNCTION_1(drawpie)
DECLARE_FLEXSIM_FUNCTION_1(drawquad)
DECLARE_FLEXSIM_FUNCTION_2(drawrectanglealias1, "drawrectangle")
DECLARE_FLEXSIM_FUNCTION_2(drawrectanglealias2, "?drawrectangle@@YANNNNNNNNNNNN@Z")
DECLARE_FLEXSIM_FUNCTION_1(drawshadow)
DECLARE_FLEXSIM_FUNCTION_2(drawspherealias, "drawsphere")
DECLARE_FLEXSIM_FUNCTION_2(drawtextalias, "drawtext")
DECLARE_FLEXSIM_FUNCTION_1(drawtomodelscale)
DECLARE_FLEXSIM_FUNCTION_1(drawtoobjectscale)
DECLARE_FLEXSIM_FUNCTION_1(drawtriangle)
DECLARE_FLEXSIM_FUNCTION_1(dropnodefrom)
DECLARE_FLEXSIM_FUNCTION_1(dropnodeto)
DECLARE_FLEXSIM_FUNCTION_1(dropx)
DECLARE_FLEXSIM_FUNCTION_1(dropy)
DECLARE_FLEXSIM_FUNCTION_1(dropz)
DECLARE_FLEXSIM_FUNCTION_1(dumpquery)
DECLARE_FLEXSIM_FUNCTION_2(duniformalias, "duniform")
DECLARE_FLEXSIM_FUNCTION_1(dynamicsplineall)
DECLARE_FLEXSIM_FUNCTION_1(edscode)
DECLARE_FLEXSIM_FUNCTION_1(edsdata)
DECLARE_FLEXSIM_FUNCTION_1(edsstring)
DECLARE_FLEXSIM_FUNCTION_2(empiricalalias, "empirical")
DECLARE_FLEXSIM_FUNCTION_1(endaggregatedundo)
DECLARE_FLEXSIM_FUNCTION_1(endignoreundo)
DECLARE_FLEXSIM_FUNCTION_1(endoffile)
DECLARE_FLEXSIM_FUNCTION_1(endreplication)
DECLARE_FLEXSIM_FUNCTION_2(erlangalias, "erlang")
DECLARE_FLEXSIM_FUNCTION_1(eventget)
DECLARE_FLEXSIM_FUNCTION_1(eventmovedown)
DECLARE_FLEXSIM_FUNCTION_1(eventmoveup)
DECLARE_FLEXSIM_FUNCTION_1(eventqty)
DECLARE_FLEXSIM_FUNCTION_1(eventtype)
DECLARE_FLEXSIM_FUNCTION_2(EXalias, "EX")
DECLARE_FLEXSIM_FUNCTION_1(excelclose)
DECLARE_FLEXSIM_FUNCTION_1(excelcreatesheet)
DECLARE_FLEXSIM_FUNCTION_1(exceldeleterange)
DECLARE_FLEXSIM_FUNCTION_1(exceldeletesheet)
DECLARE_FLEXSIM_FUNCTION_1(excelexporttable)
DECLARE_FLEXSIM_FUNCTION_1(excelgetrangeparam)
DECLARE_FLEXSIM_FUNCTION_1(excelgetrangesheet)
DECLARE_FLEXSIM_FUNCTION_1(excelimporttable)
DECLARE_FLEXSIM_FUNCTION_2(excellaunchalias1, "excellaunch")
DECLARE_FLEXSIM_FUNCTION_2(excellaunchalias2, "?excellaunch@@YANXZ")
DECLARE_FLEXSIM_FUNCTION_1(excelmacro)
DECLARE_FLEXSIM_FUNCTION_2(excelopenalias, "excelopen")
DECLARE_FLEXSIM_FUNCTION_1(excelquit)
DECLARE_FLEXSIM_FUNCTION_1(excelrangereadnum)
DECLARE_FLEXSIM_FUNCTION_1(excelrangereadstr)
DECLARE_FLEXSIM_FUNCTION_1(excelrangewritenum)
DECLARE_FLEXSIM_FUNCTION_1(excelrangewritestr)
DECLARE_FLEXSIM_FUNCTION_1(excelreadnum)
DECLARE_FLEXSIM_FUNCTION_1(excelreadstr)
DECLARE_FLEXSIM_FUNCTION_1(excelsave)
DECLARE_FLEXSIM_FUNCTION_1(excelsetrange)
DECLARE_FLEXSIM_FUNCTION_2(excelsetsheetalias, "excelsetsheet")
DECLARE_FLEXSIM_FUNCTION_1(excelupdatepreferences)
DECLARE_FLEXSIM_FUNCTION_1(excelversion)
DECLARE_FLEXSIM_FUNCTION_1(excelwritenum)
DECLARE_FLEXSIM_FUNCTION_2(excelwritestr_importedfunction, "excelwritestr")
DECLARE_FLEXSIM_FUNCTION_2(executefsnodealias, "executefsnode")
DECLARE_FLEXSIM_FUNCTION_2(executestringalias, "executestring")
DECLARE_FLEXSIM_FUNCTION_2(exponentialalias, "exponential")
DECLARE_FLEXSIM_FUNCTION_2(exportdatasetalias, "exportdataset")
DECLARE_FLEXSIM_FUNCTION_1(exportfullhistory)
DECLARE_FLEXSIM_FUNCTION_2(exporttablealias, "exporttable")
DECLARE_FLEXSIM_FUNCTION_2(extremevalue1aalias, "extremevalue1a")
DECLARE_FLEXSIM_FUNCTION_2(extremevalue1balias, "extremevalue1b")
DECLARE_FLEXSIM_FUNCTION_1(factorial)
DECLARE_FLEXSIM_FUNCTION_1(familycreate)
DECLARE_FLEXSIM_FUNCTION_1(familydelete)
DECLARE_FLEXSIM_FUNCTION_1(familymember)
DECLARE_FLEXSIM_FUNCTION_1(familymemberadd)
DECLARE_FLEXSIM_FUNCTION_1(familymemberdel)
DECLARE_FLEXSIM_FUNCTION_1(familymemberqty)
DECLARE_FLEXSIM_FUNCTION_1(fastspline)
DECLARE_FLEXSIM_FUNCTION_1(fastsplineall)
DECLARE_FLEXSIM_FUNCTION_1(fastsplineupdate)
DECLARE_FLEXSIM_FUNCTION_2(fglColorAlias, "fglColor")
DECLARE_FLEXSIM_FUNCTION_1(fgldebuglevel)
DECLARE_FLEXSIM_FUNCTION_1(fglDisable)
DECLARE_FLEXSIM_FUNCTION_1(fglEnable)
DECLARE_FLEXSIM_FUNCTION_1(fglLoadIdentity)
DECLARE_FLEXSIM_FUNCTION_1(fglMatrixMode)
DECLARE_FLEXSIM_FUNCTION_1(fglNormal)
DECLARE_FLEXSIM_FUNCTION_1(fglPopMatrix)
DECLARE_FLEXSIM_FUNCTION_1(fglPushMatrix)
DECLARE_FLEXSIM_FUNCTION_1(fglRotate)
DECLARE_FLEXSIM_FUNCTION_1(fglScale)
DECLARE_FLEXSIM_FUNCTION_1(fglTranslate)
DECLARE_FLEXSIM_FUNCTION_2(filebrowse_importedfunction, "filebrowse")
DECLARE_FLEXSIM_FUNCTION_1(fileclose)
DECLARE_FLEXSIM_FUNCTION_2(fileexistsalias, "fileexists")
DECLARE_FLEXSIM_FUNCTION_2(fileopenalias, "fileopen")
DECLARE_FLEXSIM_FUNCTION_1(fillwithatts)
DECLARE_FLEXSIM_FUNCTION_1(findnode)
DECLARE_FLEXSIM_FUNCTION_1(findownerobject)
DECLARE_FLEXSIM_FUNCTION_1(findundorecordbyid)
DECLARE_FLEXSIM_FUNCTION_1(finishundorecord)
DECLARE_FLEXSIM_FUNCTION_1(first)
DECLARE_FLEXSIM_FUNCTION_1(flowitembin)
DECLARE_FLEXSIM_FUNCTION_1(flyactive)
DECLARE_FLEXSIM_FUNCTION_1(flybysimclock)
DECLARE_FLEXSIM_FUNCTION_1(flyendnode)
DECLARE_FLEXSIM_FUNCTION_1(flypath)
DECLARE_FLEXSIM_FUNCTION_1(flypathadd)
DECLARE_FLEXSIM_FUNCTION_1(flypathreset)
DECLARE_FLEXSIM_FUNCTION_1(flystart)
DECLARE_FLEXSIM_FUNCTION_1(flystop)
DECLARE_FLEXSIM_FUNCTION_1(flyto)
DECLARE_FLEXSIM_FUNCTION_1(flyupdate)
DECLARE_FLEXSIM_FUNCTION_1(fpc)
DECLARE_FLEXSIM_FUNCTION_1(fpd)
DECLARE_FLEXSIM_FUNCTION_1(fpf)
DECLARE_FLEXSIM_FUNCTION_1(fpm)
DECLARE_FLEXSIM_FUNCTION_1(fpr)
DECLARE_FLEXSIM_FUNCTION_1(fps)
DECLARE_FLEXSIM_FUNCTION_2(fpt_importedfunction, "fpt")
DECLARE_FLEXSIM_FUNCTION_1(frac)
DECLARE_FLEXSIM_FUNCTION_1(fscheckall)
DECLARE_FLEXSIM_FUNCTION_1(ft)
DECLARE_FLEXSIM_FUNCTION_2(gammaalias, "gamma")
DECLARE_FLEXSIM_FUNCTION_1(generateuniqueid)
DECLARE_FLEXSIM_FUNCTION_2(geometricalias, "geometric")
DECLARE_FLEXSIM_FUNCTION_1(get)
DECLARE_FLEXSIM_FUNCTION_1(getapplicationtitle)
DECLARE_FLEXSIM_FUNCTION_1(getbundlefieldname);
DECLARE_FLEXSIM_FUNCTION_1(getbundlefieldnr);
DECLARE_FLEXSIM_FUNCTION_1(getbundlefieldtype);
DECLARE_FLEXSIM_FUNCTION_1(getbundlenrentries);
DECLARE_FLEXSIM_FUNCTION_1(getbundlenrfields);
DECLARE_FLEXSIM_FUNCTION_1(getchecked)
DECLARE_FLEXSIM_FUNCTION_1(getcolorcomponent)
DECLARE_FLEXSIM_FUNCTION_1(getcorefailsafelink)
DECLARE_FLEXSIM_FUNCTION_1(getcreationtime)
DECLARE_FLEXSIM_FUNCTION_1(getcurrentscenedc)
DECLARE_FLEXSIM_FUNCTION_1(getcurrentundorecord)
DECLARE_FLEXSIM_FUNCTION_2(getdatastat_alias1, "getdatastat")
DECLARE_FLEXSIM_FUNCTION_3(getdatastat_alias2, "?getdatastat@@YANHHPANNNN@Z", "?getdatastat@@YANHHPEANNNN@Z")
DECLARE_FLEXSIM_FUNCTION_1(getdatatype)
DECLARE_FLEXSIM_FUNCTION_1(getdrawtextmetric)
DECLARE_FLEXSIM_FUNCTION_1(getentrytime)
DECLARE_FLEXSIM_FUNCTION_1(getfilebrowse)
DECLARE_FLEXSIM_FUNCTION_1(getframe)
DECLARE_FLEXSIM_FUNCTION_1(getglobalvariableasdouble)
DECLARE_FLEXSIM_FUNCTION_1(getglobalvariableasdoublearray)
DECLARE_FLEXSIM_FUNCTION_1(getglobalvariableasint)
DECLARE_FLEXSIM_FUNCTION_1(getglobalvariableasintarray)
DECLARE_FLEXSIM_FUNCTION_1(getglobalvariableasstring)
DECLARE_FLEXSIM_FUNCTION_1(getglobalvariableasstringarray)
DECLARE_FLEXSIM_FUNCTION_1(getglobalvariableastreenode)
DECLARE_FLEXSIM_FUNCTION_1(getglobalvariableastreenodearray)
DECLARE_FLEXSIM_FUNCTION_1(getglobalvariableindex)
DECLARE_FLEXSIM_FUNCTION_1(getinput)
DECLARE_FLEXSIM_FUNCTION_1(getitemtype)
DECLARE_FLEXSIM_FUNCTION_2(getkinematicsalias, "getkinematics")
DECLARE_FLEXSIM_FUNCTION_1(getlastfiletype)
DECLARE_FLEXSIM_FUNCTION_1(getmodelunitnum)
DECLARE_FLEXSIM_FUNCTION_1(getmodelunitstr_cstr)
DECLARE_FLEXSIM_FUNCTION_1(getnodenum)
DECLARE_FLEXSIM_FUNCTION_1(getobjectimageindex)
DECLARE_FLEXSIM_FUNCTION_1(getobjectshapeindex)
DECLARE_FLEXSIM_FUNCTION_1(getobjecttextureindex)
DECLARE_FLEXSIM_FUNCTION_1(getoutput)
DECLARE_FLEXSIM_FUNCTION_1(getparentwindow)
DECLARE_FLEXSIM_FUNCTION_1(getpickingdrawfocus)
DECLARE_FLEXSIM_FUNCTION_1(getpickingmode)
DECLARE_FLEXSIM_FUNCTION_1(getproperty)
DECLARE_FLEXSIM_FUNCTION_1(getquerycolcount)
DECLARE_FLEXSIM_FUNCTION_1(getquerymatchcount)
DECLARE_FLEXSIM_FUNCTION_1(getquerymatchtablerow)
DECLARE_FLEXSIM_FUNCTION_3(getqueryvaluealias1, "?getqueryvalue@@YA?AVVariant@@HH@Z", "?getqueryvalue@@YA?AVVariant@@HH@Z")
DECLARE_FLEXSIM_FUNCTION_3(getqueryvaluealias2,  "?getqueryvalue@@YA?AVVariant@@HPAD@Z", "?getqueryvalue@@YA?AVVariant@@HPEAD@Z")
DECLARE_FLEXSIM_FUNCTION_1(getrank)
DECLARE_FLEXSIM_FUNCTION_1(getrunstate)
DECLARE_FLEXSIM_FUNCTION_1(getsdtvalue)
DECLARE_FLEXSIM_FUNCTION_1(getshapeindex)
DECLARE_FLEXSIM_FUNCTION_1(getshapenrframes)
DECLARE_FLEXSIM_FUNCTION_1(getsoundindex)
DECLARE_FLEXSIM_FUNCTION_2(getstatenum_alias1, "getstatenum")
DECLARE_FLEXSIM_FUNCTION_3(getstatenum_alias2, "?getstatenum@@YANPAVTreeNode@@H@Z","?getstatenum@@YANPEAVTreeNode@@H@Z")
DECLARE_FLEXSIM_FUNCTION_1(getsystemmetric)
DECLARE_FLEXSIM_FUNCTION_2(gettablenumalias, "gettablenum");
DECLARE_FLEXSIM_FUNCTION_1(gettextureindex)
DECLARE_FLEXSIM_FUNCTION_1(getundorecordid)
DECLARE_FLEXSIM_FUNCTION_2(getvarnodeimport,"getvarnode")
DECLARE_FLEXSIM_FUNCTION_2(getvarnumalias, "getvarnum")
DECLARE_FLEXSIM_FUNCTION_1(getviewhwnd)
DECLARE_FLEXSIM_FUNCTION_1(getviewmenu)
DECLARE_FLEXSIM_FUNCTION_1(getviewscale)
DECLARE_FLEXSIM_FUNCTION_1(getviewtext_cstr)
DECLARE_FLEXSIM_FUNCTION_1(globalcommand_savebyname)
DECLARE_FLEXSIM_FUNCTION_1(go)
DECLARE_FLEXSIM_FUNCTION_1(graphtohistogram)
DECLARE_FLEXSIM_FUNCTION_1(help)
DECLARE_FLEXSIM_FUNCTION_1(hideprogressbar)
DECLARE_FLEXSIM_FUNCTION_1(highestconnection)
DECLARE_FLEXSIM_FUNCTION_1(highlightviewtext)
DECLARE_FLEXSIM_FUNCTION_1(hours)
DECLARE_FLEXSIM_FUNCTION_1(howmanyattributes)
DECLARE_FLEXSIM_FUNCTION_1(howmanycommands)
DECLARE_FLEXSIM_FUNCTION_2(hypergeometricalias, "hypergeometric")
DECLARE_FLEXSIM_FUNCTION_1(importdataset)
DECLARE_FLEXSIM_FUNCTION_2(importtablealias, "importtable")
DECLARE_FLEXSIM_FUNCTION_1(in)
DECLARE_FLEXSIM_FUNCTION_1(inc)
DECLARE_FLEXSIM_FUNCTION_1(initialisehistogram)
DECLARE_FLEXSIM_FUNCTION_2(initkinematicsalias, "initkinematics")
DECLARE_FLEXSIM_FUNCTION_1(inobject)
DECLARE_FLEXSIM_FUNCTION_1(inputopen)
DECLARE_FLEXSIM_FUNCTION_1(insertcopy)
DECLARE_FLEXSIM_FUNCTION_2(inversegaussianalias, "inversegaussian")
DECLARE_FLEXSIM_FUNCTION_2(inverseweibullalias, "inverseweibull")
DECLARE_FLEXSIM_FUNCTION_2(invertedweibullalias, "invertedweibull")
DECLARE_FLEXSIM_FUNCTION_1(ipopen)
DECLARE_FLEXSIM_FUNCTION_1(ipopno)
DECLARE_FLEXSIM_FUNCTION_1(ipready)
DECLARE_FLEXSIM_FUNCTION_2(isclasstypealias1, "isclasstype")
DECLARE_FLEXSIM_FUNCTION_3(isclasstypealias2, "?isclasstype@@YAHPAVTreeNode@@PAD@Z","?isclasstype@@YAHPEAVTreeNode@@PEAD@Z")
DECLARE_FLEXSIM_FUNCTION_2(iskeydownalias, "iskeydown")
DECLARE_FLEXSIM_FUNCTION_2(johnsonboundedalias, "johnsonbounded")
DECLARE_FLEXSIM_FUNCTION_2(johnsonunboundedalias, "johnsonunbounded")
DECLARE_FLEXSIM_FUNCTION_1(keyboardfocus)
DECLARE_FLEXSIM_FUNCTION_2(laplacealias, "laplace")
DECLARE_FLEXSIM_FUNCTION_1(last)
DECLARE_FLEXSIM_FUNCTION_1(lastclickednode)
DECLARE_FLEXSIM_FUNCTION_1(lastkey)
DECLARE_FLEXSIM_FUNCTION_1(lastkeydown)
DECLARE_FLEXSIM_FUNCTION_1(lastkeyup)
DECLARE_FLEXSIM_FUNCTION_1(library)
DECLARE_FLEXSIM_FUNCTION_1(listboxrefresh)
DECLARE_FLEXSIM_FUNCTION_1(listinlist)
DECLARE_FLEXSIM_FUNCTION_1(listmax)
DECLARE_FLEXSIM_FUNCTION_1(listmaximum)
DECLARE_FLEXSIM_FUNCTION_1(listmean)
DECLARE_FLEXSIM_FUNCTION_1(listmin)
DECLARE_FLEXSIM_FUNCTION_1(listminimum)
DECLARE_FLEXSIM_FUNCTION_1(listmul)
DECLARE_FLEXSIM_FUNCTION_1(listsub)
DECLARE_FLEXSIM_FUNCTION_1(listsum)
DECLARE_FLEXSIM_FUNCTION_1(lladd)
DECLARE_FLEXSIM_FUNCTION_1(lladddata)
DECLARE_FLEXSIM_FUNCTION_1(llbranch)
DECLARE_FLEXSIM_FUNCTION_1(llcleanup)
DECLARE_FLEXSIM_FUNCTION_1(lldelete)
DECLARE_FLEXSIM_FUNCTION_1(llfind)
DECLARE_FLEXSIM_FUNCTION_1(llgetallocsize)
DECLARE_FLEXSIM_FUNCTION_1(llgetdata)
DECLARE_FLEXSIM_FUNCTION_1(llinsert)
DECLARE_FLEXSIM_FUNCTION_1(llinsertbranch)
DECLARE_FLEXSIM_FUNCTION_1(llinsertinto)
DECLARE_FLEXSIM_FUNCTION_1(lllastitem)
DECLARE_FLEXSIM_FUNCTION_1(llnew)
DECLARE_FLEXSIM_FUNCTION_1(llposition)
DECLARE_FLEXSIM_FUNCTION_1(llreceivemessage)
DECLARE_FLEXSIM_FUNCTION_1(llremove)
DECLARE_FLEXSIM_FUNCTION_1(llsdf)
DECLARE_FLEXSIM_FUNCTION_1(llsize)
DECLARE_FLEXSIM_FUNCTION_1(llstep)
DECLARE_FLEXSIM_FUNCTION_1(loadimage)
DECLARE_FLEXSIM_FUNCTION_1(loadthreedobject)
DECLARE_FLEXSIM_FUNCTION_1(loc_clock)
DECLARE_FLEXSIM_FUNCTION_1(loc_medialist)
DECLARE_FLEXSIM_FUNCTION_1(loc_medialist_images)
DECLARE_FLEXSIM_FUNCTION_1(loc_medialist_objects)
DECLARE_FLEXSIM_FUNCTION_1(loc_medialist_sounds)
DECLARE_FLEXSIM_FUNCTION_1(loc_tools)
DECLARE_FLEXSIM_FUNCTION_1(loc_undolist)
DECLARE_FLEXSIM_FUNCTION_2(logarithmicalias, "logarithmic")
DECLARE_FLEXSIM_FUNCTION_2(logeventalias1,"logevent")
DECLARE_FLEXSIM_FUNCTION_3(logeventalias2,"?logevent@@YAXPADPAVTreeNode@@1NNNN@Z","?logevent@@YAXPEADPEAVTreeNode@@1NNNN@Z")
DECLARE_FLEXSIM_FUNCTION_2(logisticalias, "logistic")
DECLARE_FLEXSIM_FUNCTION_2(loglaplacealias, "loglaplace")
DECLARE_FLEXSIM_FUNCTION_2(loglogisticalias, "loglogistic")
DECLARE_FLEXSIM_FUNCTION_2(lognormal2alias, "lognormal2")
DECLARE_FLEXSIM_FUNCTION_2(lognormalalias, "lognormal")
DECLARE_FLEXSIM_FUNCTION_2(maintenancealias, "maintenance")
DECLARE_FLEXSIM_FUNCTION_1(maintree)
DECLARE_FLEXSIM_FUNCTION_1(makeactive)
DECLARE_FLEXSIM_FUNCTION_1(makehisto)
DECLARE_FLEXSIM_FUNCTION_1(maxof)
DECLARE_FLEXSIM_FUNCTION_1(mediareset)
DECLARE_FLEXSIM_FUNCTION_1(menubelow)
DECLARE_FLEXSIM_FUNCTION_1(menucheck)
DECLARE_FLEXSIM_FUNCTION_1(menugray)
DECLARE_FLEXSIM_FUNCTION_1(menumain)
DECLARE_FLEXSIM_FUNCTION_1(mesh)
DECLARE_FLEXSIM_FUNCTION_1(meshaddvertex)
DECLARE_FLEXSIM_FUNCTION_1(meshaddcustomvertexattrib)
DECLARE_FLEXSIM_FUNCTION_1(meshsetvertexattrib)
DECLARE_FLEXSIM_FUNCTION_1(meshdraw)
DECLARE_FLEXSIM_FUNCTION_1(meshaddindex)
DECLARE_FLEXSIM_FUNCTION_1(meshinfo)
DECLARE_FLEXSIM_FUNCTION_1(minof)
DECLARE_FLEXSIM_FUNCTION_1(minutes)
DECLARE_FLEXSIM_FUNCTION_1(model)
DECLARE_FLEXSIM_FUNCTION_1(modeldir_cstr)
DECLARE_FLEXSIM_FUNCTION_1(modeleditmode)
DECLARE_FLEXSIM_FUNCTION_2(moveobjectalias1, "moveobject")
DECLARE_FLEXSIM_FUNCTION_3(moveobjectalias2, "?moveobject@@YAHPAVTreeNode@@0HH@Z","?moveobject@@YAHPEAVTreeNode@@0HH@Z")
DECLARE_FLEXSIM_FUNCTION_1(moveobjectstatsupdate_content)
DECLARE_FLEXSIM_FUNCTION_1(moveobjectstatsupdate_staytime)
DECLARE_FLEXSIM_FUNCTION_2(movetablecolalias, "movetablecol");
DECLARE_FLEXSIM_FUNCTION_2(movetablerowalias, "movetablerow");
DECLARE_FLEXSIM_FUNCTION_1(mph)
DECLARE_FLEXSIM_FUNCTION_2(msgalias, "msg")
DECLARE_FLEXSIM_FUNCTION_1(namebbgetbuffer)
DECLARE_FLEXSIM_FUNCTION_1(namebbgetsize)
DECLARE_FLEXSIM_FUNCTION_1(namebbsetsize)
DECLARE_FLEXSIM_FUNCTION_1(nametomodelpath)
DECLARE_FLEXSIM_FUNCTION_2(negbinomialalias, "negbinomial")
DECLARE_FLEXSIM_FUNCTION_1(next)
DECLARE_FLEXSIM_FUNCTION_1(nextforobjectselectionset)
DECLARE_FLEXSIM_FUNCTION_3(nextforobjecttreeunder, "?nextforobjecttreeunder@@YAPAVTreeNode@@PAV1@0@Z", "?nextforobjecttreeunder@@YAPEAVTreeNode@@PEAV1@0@Z")
DECLARE_FLEXSIM_FUNCTION_1(nodeadddata)
DECLARE_FLEXSIM_FUNCTION_2(nodealias, "node")
DECLARE_FLEXSIM_FUNCTION_1(nodealloc)
DECLARE_FLEXSIM_FUNCTION_1(nodebreak)
DECLARE_FLEXSIM_FUNCTION_1(nodedeldata)
DECLARE_FLEXSIM_FUNCTION_3(nodefromwindow, "?nodefromwindow@@YAPAVTreeNode@@PAUHWND__@@@Z", "?nodefromwindow@@YAPEAVTreeNode@@PEAUHWND__@@@Z")
DECLARE_FLEXSIM_FUNCTION_1(nodeinsertafter)
DECLARE_FLEXSIM_FUNCTION_1(nodeinsertinto)
DECLARE_FLEXSIM_FUNCTION_1(nodejoin)
DECLARE_FLEXSIM_FUNCTION_1(nodepoint)
DECLARE_FLEXSIM_FUNCTION_1(nodetomodelpath_cstr)
DECLARE_FLEXSIM_FUNCTION_1(nodetotextpath)
DECLARE_FLEXSIM_FUNCTION_1(nodetotextpath_indexed)
DECLARE_FLEXSIM_FUNCTION_2(normalalias, "normal")
DECLARE_FLEXSIM_FUNCTION_1(nrcp)
DECLARE_FLEXSIM_FUNCTION_1(nrip)
DECLARE_FLEXSIM_FUNCTION_1(nrop)
DECLARE_FLEXSIM_FUNCTION_1(numconnections)
DECLARE_FLEXSIM_FUNCTION_1(objectexists)
DECLARE_FLEXSIM_FUNCTION_1(objectsoundcode)
DECLARE_FLEXSIM_FUNCTION_1(odtgetallocsize)
DECLARE_FLEXSIM_FUNCTION_1(openallip)
DECLARE_FLEXSIM_FUNCTION_1(openallop)
DECLARE_FLEXSIM_FUNCTION_1(openflexsimchart)
DECLARE_FLEXSIM_FUNCTION_1(openglcolor)
DECLARE_FLEXSIM_FUNCTION_1(opengllighting)
DECLARE_FLEXSIM_FUNCTION_1(openinput)
DECLARE_FLEXSIM_FUNCTION_1(openip)
DECLARE_FLEXSIM_FUNCTION_1(openop)
DECLARE_FLEXSIM_FUNCTION_1(openoutput)
DECLARE_FLEXSIM_FUNCTION_1(opipno)
DECLARE_FLEXSIM_FUNCTION_1(opopen)
DECLARE_FLEXSIM_FUNCTION_1(opready)
DECLARE_FLEXSIM_FUNCTION_1(optquest)
DECLARE_FLEXSIM_FUNCTION_1(outobject)
DECLARE_FLEXSIM_FUNCTION_1(outputopen)
DECLARE_FLEXSIM_FUNCTION_1(outputtreecontent)
DECLARE_FLEXSIM_FUNCTION_1(ownerobject)
DECLARE_FLEXSIM_FUNCTION_1(ownerview)
DECLARE_FLEXSIM_FUNCTION_2(paretoalias, "pareto")
DECLARE_FLEXSIM_FUNCTION_1(parg_cstr)
DECLARE_FLEXSIM_FUNCTION_2(_parqty, "parqty")
DECLARE_FLEXSIM_FUNCTION_1(particlecreate)
DECLARE_FLEXSIM_FUNCTION_1(particlemove)
DECLARE_FLEXSIM_FUNCTION_1(pc)
DECLARE_FLEXSIM_FUNCTION_1(pd)
DECLARE_FLEXSIM_FUNCTION_1(pdir_cstr)
DECLARE_FLEXSIM_FUNCTION_2(pearsont5alias, "pearsont5")
DECLARE_FLEXSIM_FUNCTION_2(pearsont6alias, "pearsont6")
DECLARE_FLEXSIM_FUNCTION_1(pf)
DECLARE_FLEXSIM_FUNCTION_1(pfile_cstr)
DECLARE_FLEXSIM_FUNCTION_1(pi)
DECLARE_FLEXSIM_FUNCTION_1(pickcolor)
DECLARE_FLEXSIM_FUNCTION_1(pickcolornode)
DECLARE_FLEXSIM_FUNCTION_1(pickedcolorblue)
DECLARE_FLEXSIM_FUNCTION_1(pickedcolorgreen)
DECLARE_FLEXSIM_FUNCTION_1(pickedcolorred)
DECLARE_FLEXSIM_FUNCTION_1(pickfile)
DECLARE_FLEXSIM_FUNCTION_1(picklistapply)
DECLARE_FLEXSIM_FUNCTION_2(poissonalias, "poisson")
DECLARE_FLEXSIM_FUNCTION_1(popupmenu)
DECLARE_FLEXSIM_FUNCTION_1(postclosewindowmessage)
DECLARE_FLEXSIM_FUNCTION_1(postmovewindowupdate)
DECLARE_FLEXSIM_FUNCTION_1(pr)
DECLARE_FLEXSIM_FUNCTION_1(prev)
DECLARE_FLEXSIM_FUNCTION_2(profileeventsalias, "profileevents")
DECLARE_FLEXSIM_FUNCTION_1(profilekinematics)
DECLARE_FLEXSIM_FUNCTION_2(pt_importedfunction, "pt")
DECLARE_FLEXSIM_FUNCTION_1(qstudentt)
DECLARE_FLEXSIM_FUNCTION_1(radianstodegrees)
DECLARE_FLEXSIM_FUNCTION_1(randantithetic)
DECLARE_FLEXSIM_FUNCTION_1(randinit)
DECLARE_FLEXSIM_FUNCTION_1(randnext)
DECLARE_FLEXSIM_FUNCTION_2(randomwalkalias, "randomwalk")
DECLARE_FLEXSIM_FUNCTION_1(randstate)
DECLARE_FLEXSIM_FUNCTION_1(rank)
DECLARE_FLEXSIM_FUNCTION_1(rankobj)
DECLARE_FLEXSIM_FUNCTION_1(realtime)
DECLARE_FLEXSIM_FUNCTION_1(rebindobjectattributes)
DECLARE_FLEXSIM_FUNCTION_1(recover)
DECLARE_FLEXSIM_FUNCTION_1(redirectconsole)
DECLARE_FLEXSIM_FUNCTION_1(refreshcommand)
DECLARE_FLEXSIM_FUNCTION_1(refreshcommandlist)
DECLARE_FLEXSIM_FUNCTION_1(refreshglobalvariables)
DECLARE_FLEXSIM_FUNCTION_1(refreshview)
DECLARE_FLEXSIM_FUNCTION_2(reftablealias, "reftable");
DECLARE_FLEXSIM_FUNCTION_1(registereventtype)
DECLARE_FLEXSIM_FUNCTION_1(removeallcouplingreferences)
DECLARE_FLEXSIM_FUNCTION_1(removebundleentry)
DECLARE_FLEXSIM_FUNCTION_2(removeeventsofobjectalias, "removeeventsofobject")
DECLARE_FLEXSIM_FUNCTION_1(removefirstbundleentry);
DECLARE_FLEXSIM_FUNCTION_1(removelastbundleentry);
DECLARE_FLEXSIM_FUNCTION_1(repaintall)
DECLARE_FLEXSIM_FUNCTION_1(repaintallactive)
DECLARE_FLEXSIM_FUNCTION_1(repaintview)
DECLARE_FLEXSIM_FUNCTION_1(replacedata_n)
DECLARE_FLEXSIM_FUNCTION_1(replacedata_s)
DECLARE_FLEXSIM_FUNCTION_1(replacename)
DECLARE_FLEXSIM_FUNCTION_1(report)
DECLARE_FLEXSIM_FUNCTION_1(reportmode)
DECLARE_FLEXSIM_FUNCTION_1(reportobjectfunctionexception)
DECLARE_FLEXSIM_FUNCTION_1(repositionhighlightededits)
DECLARE_FLEXSIM_FUNCTION_1(resetexperiment)
DECLARE_FLEXSIM_FUNCTION_1(resetlayer)
DECLARE_FLEXSIM_FUNCTION_1(resetstats)
DECLARE_FLEXSIM_FUNCTION_1(resetuniqueid)
DECLARE_FLEXSIM_FUNCTION_2(restoreeventsofobjectalias, "restoreeventsofobject")
DECLARE_FLEXSIM_FUNCTION_2(resumeanimationalias1, "resumeanimation")
DECLARE_FLEXSIM_FUNCTION_3(resumeanimationalias2, "?resumeanimation@@YAXPAVTreeNode@@PADHN@Z", "?resumeanimation@@YAXPEAVTreeNode@@PEADHN@Z")
DECLARE_FLEXSIM_FUNCTION_1(resumeinput)
DECLARE_FLEXSIM_FUNCTION_1(resumeoutput)
#if _MSC_VER < 1800
DECLARE_FLEXSIM_FUNCTION_2(roundalias1, "round")
#endif
DECLARE_FLEXSIM_FUNCTION_2(roundalias2, "?round@@YANNH@Z")
DECLARE_FLEXSIM_FUNCTION_1(rundocument)
DECLARE_FLEXSIM_FUNCTION_1(runexpertfit)
DECLARE_FLEXSIM_FUNCTION_1(runfunction)
DECLARE_FLEXSIM_FUNCTION_1(runprogram)
DECLARE_FLEXSIM_FUNCTION_2(runspeedalias, "runspeed")
DECLARE_FLEXSIM_FUNCTION_1(savetree)
DECLARE_FLEXSIM_FUNCTION_1(scaleeventsofobject)
DECLARE_FLEXSIM_FUNCTION_1(scalekinematicstotime)
DECLARE_FLEXSIM_FUNCTION_1(sdtgetbindmode)
DECLARE_FLEXSIM_FUNCTION_1(searchdata_n)
DECLARE_FLEXSIM_FUNCTION_1(searchdata_s)
DECLARE_FLEXSIM_FUNCTION_1(searchfornode)
DECLARE_FLEXSIM_FUNCTION_1(searchname)
DECLARE_FLEXSIM_FUNCTION_1(selectedx)
DECLARE_FLEXSIM_FUNCTION_1(selectedy)
DECLARE_FLEXSIM_FUNCTION_1(selectedz)
DECLARE_FLEXSIM_FUNCTION_1(sendwindowmessage)
DECLARE_FLEXSIM_FUNCTION_1(serveraccept)
DECLARE_FLEXSIM_FUNCTION_1(servercloseconnection)
DECLARE_FLEXSIM_FUNCTION_1(serverclosemain)
DECLARE_FLEXSIM_FUNCTION_1(servercreatemain)
DECLARE_FLEXSIM_FUNCTION_2(serverreceivealias, "serverreceive")
DECLARE_FLEXSIM_FUNCTION_2(serversendalias, "serversend")
DECLARE_FLEXSIM_FUNCTION_1(set)
DECLARE_FLEXSIM_FUNCTION_1(setapplicationtitle)
DECLARE_FLEXSIM_FUNCTION_2(setbundlevaluealias1, "setbundlevalue");
DECLARE_FLEXSIM_FUNCTION_3(setbundlevaluealias2, "?setbundlevalue@@YAHPAVTreeNode@@HHN@Z","?setbundlevalue@@YAHPEAVTreeNode@@HHN@Z");
DECLARE_FLEXSIM_FUNCTION_3(setbundlevaluealias3, "?setbundlevalue@@YAHPAVTreeNode@@HPAD1@Z","?setbundlevalue@@YAHPEAVTreeNode@@HPEAD1@Z");
DECLARE_FLEXSIM_FUNCTION_3(setbundlevaluealias4, "?setbundlevalue@@YAHPAVTreeNode@@HHPAD@Z","?setbundlevalue@@YAHPEAVTreeNode@@HHPEAD@Z");
DECLARE_FLEXSIM_FUNCTION_1(setcameradirection)
DECLARE_FLEXSIM_FUNCTION_1(setcameravolume)
DECLARE_FLEXSIM_FUNCTION_1(setcenter)
DECLARE_FLEXSIM_FUNCTION_1(setchecked)
DECLARE_FLEXSIM_FUNCTION_1(setcolor)
DECLARE_FLEXSIM_FUNCTION_1(setcursor)
DECLARE_FLEXSIM_FUNCTION_1(setcustomdisplayfunction)
DECLARE_FLEXSIM_FUNCTION_1(setdrawnamefunction)
DECLARE_FLEXSIM_FUNCTION_1(setdropcoords)
DECLARE_FLEXSIM_FUNCTION_1(setdropcoordsmanual)
DECLARE_FLEXSIM_FUNCTION_1(setframe)
DECLARE_FLEXSIM_FUNCTION_1(setitemtype)
DECLARE_FLEXSIM_FUNCTION_1(setkinematicsrotoffset)
DECLARE_FLEXSIM_FUNCTION_1(setloc)
DECLARE_FLEXSIM_FUNCTION_1(setmessageloopsleep)
DECLARE_FLEXSIM_FUNCTION_2(setname_alias, "setname")
DECLARE_FLEXSIM_FUNCTION_1(setnodenum)
DECLARE_FLEXSIM_FUNCTION_1(setobjectbillboard)
DECLARE_FLEXSIM_FUNCTION_1(setobjectimageindex)
DECLARE_FLEXSIM_FUNCTION_1(setobjectshapeindex)
DECLARE_FLEXSIM_FUNCTION_1(setobjecttextureindex)
DECLARE_FLEXSIM_FUNCTION_2(setpickingdrawfocusalias, "setpickingdrawfocus")
DECLARE_FLEXSIM_FUNCTION_1(setprogressbar)
DECLARE_FLEXSIM_FUNCTION_1(setproperty)
DECLARE_FLEXSIM_FUNCTION_1(setquerynode)
DECLARE_FLEXSIM_FUNCTION_1(setrank)
DECLARE_FLEXSIM_FUNCTION_1(setrot)
DECLARE_FLEXSIM_FUNCTION_1(setsdtvalue)
DECLARE_FLEXSIM_FUNCTION_1(setselectedobject)
DECLARE_FLEXSIM_FUNCTION_1(setsize)
DECLARE_FLEXSIM_FUNCTION_1(setstate_s)
DECLARE_FLEXSIM_FUNCTION_2(setstatealias1, "setstate")
DECLARE_FLEXSIM_FUNCTION_3(setstatealias2, "?setstate@@YAHPAVTreeNode@@HH@Z","?setstate@@YAHPEAVTreeNode@@HH@Z")
DECLARE_FLEXSIM_FUNCTION_3(setstatealias3, "?setstate@@YAHPAVTreeNode@@HPBD@Z","?setstate@@YAHPEAVTreeNode@@HPEBD@Z")
DECLARE_FLEXSIM_FUNCTION_3(setstatealias4, "?setstate@@YAHPAVTreeNode@@H0@Z","?setstate@@YAHPEAVTreeNode@@H0@Z")
DECLARE_FLEXSIM_FUNCTION_2(settablenumalias, "settablenum");
DECLARE_FLEXSIM_FUNCTION_2(settablesizealias, "settablesize");
DECLARE_FLEXSIM_FUNCTION_2(setvarnumalias, "setvarnum")
DECLARE_FLEXSIM_FUNCTION_2(setvarstralias, "setvarstr")
DECLARE_FLEXSIM_FUNCTION_2(setviewtextalias, "setviewtext")
DECLARE_FLEXSIM_FUNCTION_1(shiftpressed)
DECLARE_FLEXSIM_FUNCTION_1(showcompilerconsole)
DECLARE_FLEXSIM_FUNCTION_2(showhtmlhelpalias, "showhtmlhelp")
DECLARE_FLEXSIM_FUNCTION_2(showprogressbar_importedfunction, "showprogressbar")
DECLARE_FLEXSIM_FUNCTION_1(sign)
DECLARE_FLEXSIM_FUNCTION_1(so)
DECLARE_FLEXSIM_FUNCTION_1(socketend)
DECLARE_FLEXSIM_FUNCTION_1(socketinit)
DECLARE_FLEXSIM_FUNCTION_2(sorttable_alias1,"sorttable")
DECLARE_FLEXSIM_FUNCTION_3(sorttable_alias2, "?sorttable@@YANPAVTreeNode@@H@Z","?sorttable@@YANPEAVTreeNode@@H@Z")
DECLARE_FLEXSIM_FUNCTION_2(sorttable_alias3, "?sorttable@@YANHH@Z")
DECLARE_FLEXSIM_FUNCTION_1(soundchange)
DECLARE_FLEXSIM_FUNCTION_1(soundload)
DECLARE_FLEXSIM_FUNCTION_1(soundplay)
DECLARE_FLEXSIM_FUNCTION_1(soundplayfile)
DECLARE_FLEXSIM_FUNCTION_1(soundstop)
DECLARE_FLEXSIM_FUNCTION_1(spacebase)
DECLARE_FLEXSIM_FUNCTION_1(spacerotate)
DECLARE_FLEXSIM_FUNCTION_1(spacescale)
DECLARE_FLEXSIM_FUNCTION_1(spacetranslate)
DECLARE_FLEXSIM_FUNCTION_1(spline)
DECLARE_FLEXSIM_FUNCTION_1(splinedraw)
DECLARE_FLEXSIM_FUNCTION_1(splinedrawextrusion)
DECLARE_FLEXSIM_FUNCTION_1(splinelength)
DECLARE_FLEXSIM_FUNCTION_1(splineposobject)
DECLARE_FLEXSIM_FUNCTION_1(splinerx)
DECLARE_FLEXSIM_FUNCTION_1(splinery)
DECLARE_FLEXSIM_FUNCTION_1(splinerz)
DECLARE_FLEXSIM_FUNCTION_1(splinex)
DECLARE_FLEXSIM_FUNCTION_1(spliney)
DECLARE_FLEXSIM_FUNCTION_1(splinez)
DECLARE_FLEXSIM_FUNCTION_2(startanimationalias1, "startanimation")
DECLARE_FLEXSIM_FUNCTION_3(startanimationalias2, "?startanimation@@YAXPAVTreeNode@@PADHNHN@Z","?startanimation@@YAXPEAVTreeNode@@PEADHNHN@Z")
DECLARE_FLEXSIM_FUNCTION_1(startlisten)
DECLARE_FLEXSIM_FUNCTION_1(statisticaltime)
DECLARE_FLEXSIM_FUNCTION_1(statsenablemask)
DECLARE_FLEXSIM_FUNCTION_1(step)
DECLARE_FLEXSIM_FUNCTION_1(stick)
DECLARE_FLEXSIM_FUNCTION_2(stopalias, "stop")
DECLARE_FLEXSIM_FUNCTION_2(stopanimationalias1, "stopanimation")
DECLARE_FLEXSIM_FUNCTION_3(stopanimationalias2, "?stopanimation@@YAXPAVTreeNode@@PAD@Z","?stopanimation@@YAXPEAVTreeNode@@PEAD@Z")
DECLARE_FLEXSIM_FUNCTION_1(stopinput)
DECLARE_FLEXSIM_FUNCTION_1(stoplisten)
DECLARE_FLEXSIM_FUNCTION_1(stopoutput)
DECLARE_FLEXSIM_FUNCTION_2(stoptimealias, "stoptime")
DECLARE_FLEXSIM_FUNCTION_2(_stringreturn, "stringreturn")
DECLARE_FLEXSIM_FUNCTION_2(stringsearchalias1, "stringsearch")
DECLARE_FLEXSIM_FUNCTION_3(stringsearchalias2, "?stringsearch@@YAHPAD0HH@Z", "?stringsearch@@YAHPEAD0HH@Z")
DECLARE_FLEXSIM_FUNCTION_1(stringsequal)
DECLARE_FLEXSIM_FUNCTION_2(stringtokenalias, "stringtoken")
DECLARE_FLEXSIM_FUNCTION_2(stringtonumalias, "stringtonum")
DECLARE_FLEXSIM_FUNCTION_1(suspenddraw)
DECLARE_FLEXSIM_FUNCTION_1(sv)
DECLARE_FLEXSIM_FUNCTION_1(swapnoderanks)
DECLARE_FLEXSIM_FUNCTION_2(swaptablecolsalias, "swaptablecols");
DECLARE_FLEXSIM_FUNCTION_2(swaptablerowsalias, "swaptablerows");
DECLARE_FLEXSIM_FUNCTION_1(switch_activelisteners)
DECLARE_FLEXSIM_FUNCTION_1(switch_cppfunc)
DECLARE_FLEXSIM_FUNCTION_1(switch_destroyonreset)
DECLARE_FLEXSIM_FUNCTION_1(switch_dllfunc)
DECLARE_FLEXSIM_FUNCTION_1(switch_enablestats)
DECLARE_FLEXSIM_FUNCTION_1(switch_expanded)
DECLARE_FLEXSIM_FUNCTION_1(switch_flexscript)
DECLARE_FLEXSIM_FUNCTION_1(switch_hidden)
DECLARE_FLEXSIM_FUNCTION_1(switch_hidebase)
DECLARE_FLEXSIM_FUNCTION_1(switch_hideconnectors)
DECLARE_FLEXSIM_FUNCTION_1(switch_hidecontents)
DECLARE_FLEXSIM_FUNCTION_1(switch_hidelabel)
DECLARE_FLEXSIM_FUNCTION_1(switch_hideshape)
DECLARE_FLEXSIM_FUNCTION_1(switch_noselect)
DECLARE_FLEXSIM_FUNCTION_1(switch_preservecoupling)
DECLARE_FLEXSIM_FUNCTION_1(switch_orphancoupling)
DECLARE_FLEXSIM_FUNCTION_1(switch_protected)
DECLARE_FLEXSIM_FUNCTION_1(switch_selected)
DECLARE_FLEXSIM_FUNCTION_1(switch_showobject)
DECLARE_FLEXSIM_FUNCTION_1(switch_statelocked)
DECLARE_FLEXSIM_FUNCTION_1(switch_stateused)
DECLARE_FLEXSIM_FUNCTION_1(switch_variable)
DECLARE_FLEXSIM_FUNCTION_1(systemwindow)
DECLARE_FLEXSIM_FUNCTION_1(templatetocode)
DECLARE_FLEXSIM_FUNCTION_1(toggleallcodestates)
DECLARE_FLEXSIM_FUNCTION_2(tonodealias1, "tonode")
DECLARE_FLEXSIM_FUNCTION_3(tonodealias2, "?tonode@@YAPAVTreeNode@@N@Z","?tonode@@YAPEAVTreeNode@@N@Z")
DECLARE_FLEXSIM_FUNCTION_3(tonodealias3, "?tonode@@YAPAVTreeNode@@PAD@Z","?tonode@@YAPEAVTreeNode@@PEAD@Z")
DECLARE_FLEXSIM_FUNCTION_3(tonodealias4, "?tonode@@YAPAVTreeNode@@PAX@Z","?tonode@@YAPEAVTreeNode@@PEAX@Z")
DECLARE_FLEXSIM_FUNCTION_1(toptr)
DECLARE_FLEXSIM_FUNCTION_1(tracemaskevents)
DECLARE_FLEXSIM_FUNCTION_1(tracemaskobject)
DECLARE_FLEXSIM_FUNCTION_1(tracemasktime)
DECLARE_FLEXSIM_FUNCTION_1(trackpopup)
DECLARE_FLEXSIM_FUNCTION_1(transfernode)
DECLARE_FLEXSIM_FUNCTION_1(transfernodeobj)
DECLARE_FLEXSIM_FUNCTION_1(transformvectorxy)
DECLARE_FLEXSIM_FUNCTION_1(transitionport)
DECLARE_FLEXSIM_FUNCTION_1(treewin__loadtree)
DECLARE_FLEXSIM_FUNCTION_2(triangularalias, "triangular")
#if _MSC_VER < 1800
DECLARE_FLEXSIM_FUNCTION_1(trunc)
#endif
DECLARE_FLEXSIM_FUNCTION_2(uniformalias, "uniform")
DECLARE_FLEXSIM_FUNCTION_1(up)
DECLARE_FLEXSIM_FUNCTION_2(updateanimationalias1, "updateanimation")
DECLARE_FLEXSIM_FUNCTION_3(updateanimationalias2, "?updateanimation@@YAXPAVTreeNode@@NH@Z","?updateanimation@@YAXPEAVTreeNode@@NH@Z")
DECLARE_FLEXSIM_FUNCTION_2(updatekinematicsalias, "updatekinematics")
DECLARE_FLEXSIM_FUNCTION_2(updatestate_alias1, "updatestate")
DECLARE_FLEXSIM_FUNCTION_3(updatestate_alias2, "?updatestate@@YANPAVTreeNode@@H@Z","?updatestate@@YANPEAVTreeNode@@H@Z")
DECLARE_FLEXSIM_FUNCTION_1(updateundorecord)
DECLARE_FLEXSIM_FUNCTION_1(uselisteners)
DECLARE_FLEXSIM_FUNCTION_1(userinput)
DECLARE_FLEXSIM_FUNCTION_1(userdatadir_cstr)
DECLARE_FLEXSIM_FUNCTION_2(validatenamealias, "validatename")
DECLARE_FLEXSIM_FUNCTION_1(validlink)
DECLARE_FLEXSIM_FUNCTION_1(valuetohistogram)
DECLARE_FLEXSIM_FUNCTION_1(vectorproject)
DECLARE_FLEXSIM_FUNCTION_1(vectorprojectx)
DECLARE_FLEXSIM_FUNCTION_1(vectorprojecty)
DECLARE_FLEXSIM_FUNCTION_1(vectorprojectz)
DECLARE_FLEXSIM_FUNCTION_1(viewdist)
DECLARE_FLEXSIM_FUNCTION_1(views)
DECLARE_FLEXSIM_FUNCTION_2(viewtofile_alias1, "viewtofile")
DECLARE_FLEXSIM_FUNCTION_3(viewtofile_alias2, "?viewtofile@@YANPAVTreeNode@@PADHH@Z", "?viewtofile@@YANPEAVTreeNode@@PEADHH@Z")
DECLARE_FLEXSIM_FUNCTION_2(webcommandalias, "webcommand")
DECLARE_FLEXSIM_FUNCTION_2(weibullalias, "weibull")
DECLARE_FLEXSIM_FUNCTION_1(windowfromnode)
DECLARE_FLEXSIM_FUNCTION_1(windowgray)
DECLARE_FLEXSIM_FUNCTION_1(windowmenu)
DECLARE_FLEXSIM_FUNCTION_1(windowmove)
DECLARE_FLEXSIM_FUNCTION_1(windowshow)
DECLARE_FLEXSIM_FUNCTION_2(windowstylealias, "windowstyle")
DECLARE_FLEXSIM_FUNCTION_1(xcenter)
DECLARE_FLEXSIM_FUNCTION_1(xloc)
DECLARE_FLEXSIM_FUNCTION_1(xrot)
DECLARE_FLEXSIM_FUNCTION_1(xsize)
DECLARE_FLEXSIM_FUNCTION_1(ycenter)
DECLARE_FLEXSIM_FUNCTION_1(yloc)
DECLARE_FLEXSIM_FUNCTION_1(yrot)
DECLARE_FLEXSIM_FUNCTION_1(ysize)
DECLARE_FLEXSIM_FUNCTION_1(zcenter)
DECLARE_FLEXSIM_FUNCTION_1(zloc)
DECLARE_FLEXSIM_FUNCTION_1(zrot)
DECLARE_FLEXSIM_FUNCTION_1(zsize)

/*** DEPRECATED FUNCTIONS ***/
DECLARE_FLEXSIM_FUNCTION_1(add)
DECLARE_FLEXSIM_FUNCTION_1(and)
DECLARE_FLEXSIM_FUNCTION_1(anode)
DECLARE_FLEXSIM_FUNCTION_1(anum)
DECLARE_FLEXSIM_FUNCTION_1(aptr)
DECLARE_FLEXSIM_FUNCTION_1(att)
DECLARE_FLEXSIM_FUNCTION_1(att_s)
DECLARE_FLEXSIM_FUNCTION_1(cell)
DECLARE_FLEXSIM_FUNCTION_1(cellrowcolumn)
DECLARE_FLEXSIM_FUNCTION_1(colorrgb)
DECLARE_FLEXSIM_FUNCTION_1(cppgetnumtokens)
DECLARE_FLEXSIM_FUNCTION_1(cppgetphrasetoken)
DECLARE_FLEXSIM_FUNCTION_1(cppgettitletoken)
DECLARE_FLEXSIM_FUNCTION_1(cppgettoken)
DECLARE_FLEXSIM_FUNCTION_1(cppsettitletoken)
DECLARE_FLEXSIM_FUNCTION_1(cppsettoken)
#if _MSC_VER >= 1600
DECLARE_FLEXSIM_FUNCTION_2(cpp_queryalias, "cpp_query")
#endif
DECLARE_FLEXSIM_FUNCTION_1(dbwritechanges)
DECLARE_FLEXSIM_FUNCTION_1(divide)
DECLARE_FLEXSIM_FUNCTION_1(drawrect)
DECLARE_FLEXSIM_FUNCTION_1(eq)
DECLARE_FLEXSIM_FUNCTION_1(excelexportnode)
DECLARE_FLEXSIM_FUNCTION_3(excelimportnodealias1, "?excelimportnode@@YANPAVTreeNode@@HHHH@Z","?excelimportnode@@YANPEAVTreeNode@@HHHH@Z")
DECLARE_FLEXSIM_FUNCTION_2(excelimportnodealias2, "excelimportnode")
DECLARE_FLEXSIM_FUNCTION_1(excelrangeread)
DECLARE_FLEXSIM_FUNCTION_1(excelrangewrite)
DECLARE_FLEXSIM_FUNCTION_1(excelread)
DECLARE_FLEXSIM_FUNCTION_1(excelwrite)
DECLARE_FLEXSIM_FUNCTION_1(ge)
DECLARE_FLEXSIM_FUNCTION_1(gt)
DECLARE_FLEXSIM_FUNCTION_1(installpackage)
DECLARE_FLEXSIM_FUNCTION_1(le)
DECLARE_FLEXSIM_FUNCTION_1(loadsound)
DECLARE_FLEXSIM_FUNCTION_1(lt)
DECLARE_FLEXSIM_FUNCTION_1(module)
DECLARE_FLEXSIM_FUNCTION_1(mul)
DECLARE_FLEXSIM_FUNCTION_1(ncols)
DECLARE_FLEXSIM_FUNCTION_1(ne)
DECLARE_FLEXSIM_FUNCTION_1(not)
DECLARE_FLEXSIM_FUNCTION_1(nrows)
DECLARE_FLEXSIM_FUNCTION_1(objectconnect)
DECLARE_FLEXSIM_FUNCTION_1(or)
DECLARE_FLEXSIM_FUNCTION_1(particleset)
DECLARE_FLEXSIM_FUNCTION_1(relloc)
DECLARE_FLEXSIM_FUNCTION_1(reset)
DECLARE_FLEXSIM_FUNCTION_2(resetmodelalias, "resetmodel")
DECLARE_FLEXSIM_FUNCTION_1(richeditaddtext)
DECLARE_FLEXSIM_FUNCTION_1(richedittoken)
DECLARE_FLEXSIM_FUNCTION_1(settable)
DECLARE_FLEXSIM_FUNCTION_1(showgraphicinfo)
DECLARE_FLEXSIM_FUNCTION_1(spaceglobal)
DECLARE_FLEXSIM_FUNCTION_1(spaceobject)
DECLARE_FLEXSIM_FUNCTION_1(sub)
DECLARE_FLEXSIM_FUNCTION_1(undos)
DECLARE_FLEXSIM_FUNCTION_1(var)
DECLARE_FLEXSIM_FUNCTION_1(var_s)

/*** FUNCTIONS ONLY REQUIRED FOR CONTENT DLL ***/
#if defined COMPILING_FLEXSIM_CONTENT || defined COMPILING_MODULE_DLL
	DECLARE_FLEXSIM_FUNCTION_1(bbgetstaticblock)
	DECLARE_FLEXSIM_FUNCTION_1(flexsimeventbind)
	DECLARE_FLEXSIM_FUNCTION_1(flexsimeventexecute)
	DECLARE_FLEXSIM_FUNCTION_1(flexsimeventgetdescription)
	DECLARE_FLEXSIM_FUNCTION_1(getcorecommandfunction)
	DECLARE_FLEXSIM_FUNCTION_1(inobjectinfo)
	DECLARE_FLEXSIM_FUNCTION_1(llinitialize)
	DECLARE_FLEXSIM_FUNCTION_1(nodeaddcouplingdata)
	DECLARE_FLEXSIM_FUNCTION_1(nodeaddsimpledata)
	DECLARE_FLEXSIM_FUNCTION_1(nodedetachsimpledata)
	DECLARE_FLEXSIM_FUNCTION_1(odtbindstructure)
	DECLARE_FLEXSIM_FUNCTION_1(odtcleanup)
	DECLARE_FLEXSIM_FUNCTION_1(odtinitialize)
	DECLARE_FLEXSIM_FUNCTION_3(odtbindvariablebynamealias1, "?odtbindvariablebyname@@YAXPAVObjectDataType@@PBDAAN@Z","?odtbindvariablebyname@@YAXPEAVObjectDataType@@PEBDAEAN@Z")
 	DECLARE_FLEXSIM_FUNCTION_3(odtbindvariablebynamealias2, "?odtbindvariablebyname@@YAXPAVObjectDataType@@PBDAAVByteBlock@@@Z","?odtbindvariablebyname@@YAXPEAVObjectDataType@@PEBDAEAVByteBlock@@@Z")
	DECLARE_FLEXSIM_FUNCTION_3(odtbindvariablebynamealias3, "?odtbindvariablebyname@@YAXPAVObjectDataType@@PBDAAVNodeRef@@@Z", "?odtbindvariablebyname@@YAXPEAVObjectDataType@@PEBDAEAVNodeRef@@@Z")
	DECLARE_FLEXSIM_FUNCTION_3(odtbindvariablebynamealias4, "?odtbindvariablebyname@@YAXPAVObjectDataType@@PBDAAPAVTreeNode@@@Z","?odtbindvariablebyname@@YAXPEAVObjectDataType@@PEBDAEAPEAVTreeNode@@@Z")
	DECLARE_FLEXSIM_FUNCTION_1(outobjectinfo)
	DECLARE_FLEXSIM_FUNCTION_1(sdtappendtodisplaystr)
	DECLARE_FLEXSIM_FUNCTION_1(sdtbind)
	DECLARE_FLEXSIM_FUNCTION_1(sdtbindbyname)
	DECLARE_FLEXSIM_FUNCTION_1(sdtbinddoublebyname)
	DECLARE_FLEXSIM_FUNCTION_1(sdtbindbyteblockbyname)
	DECLARE_FLEXSIM_FUNCTION_1(sdtbindnodeptrbyname)
	DECLARE_FLEXSIM_FUNCTION_1(sdtbindnoderefbyname)
	DECLARE_FLEXSIM_FUNCTION_1(sdtbindobjptrbyname)
	DECLARE_FLEXSIM_FUNCTION_1(sdtbindsubnodebyname)
	DECLARE_FLEXSIM_FUNCTION_1(sdtgetbindtree)
	DECLARE_FLEXSIM_FUNCTION_1(sdtgetcurvalue)
	DECLARE_FLEXSIM_FUNCTION_1(sdtgetcurvaluename)
	DECLARE_FLEXSIM_FUNCTION_1(sdtgetvalue)
	DECLARE_FLEXSIM_FUNCTION_1(sdtsetvalue)
	DECLARE_FLEXSIM_FUNCTION_1(sdtisdisplayverbose)
	DECLARE_FLEXSIM_FUNCTION_1(sdttostring)
	DECLARE_FLEXSIM_FUNCTION_1(couplingtostring)
	DECLARE_FLEXSIM_FUNCTION_3(createeventalias2, "?createevent@@YAPAVTreeNode@@PAVFlexSimEvent@@@Z", "?createevent@@YAPEAVTreeNode@@PEAVFlexSimEvent@@@Z")
	DECLARE_FLEXSIM_FUNCTION_1(byteblock_write1)
	DECLARE_FLEXSIM_FUNCTION_1(byteblock_write2)
	DECLARE_FLEXSIM_FUNCTION_1(byteblock_append)
	DECLARE_FLEXSIM_FUNCTION_1(byteblock_setsize)
	DECLARE_FLEXSIM_FUNCTION_1(byteblock_getsize)
	DECLARE_FLEXSIM_FUNCTION_1(byteblock_getbuffer)
	DECLARE_FLEXSIM_FUNCTION_1(mesh_bind)
	DECLARE_FLEXSIM_FUNCTION_1(mesh_init)
	DECLARE_FLEXSIM_FUNCTION_1(mesh_cleanup)
	DECLARE_FLEXSIM_FUNCTION_1(mesh_definevertexattribs)
	DECLARE_FLEXSIM_FUNCTION_1(mesh_addcustomvertexattrib)
	DECLARE_FLEXSIM_FUNCTION_1(mesh_setvertexattrib)
	DECLARE_FLEXSIM_FUNCTION_1(mesh_setmeshattrib)
	DECLARE_FLEXSIM_FUNCTION_1(mesh_addvertex)
	DECLARE_FLEXSIM_FUNCTION_1(mesh_draw)
	DECLARE_FLEXSIM_FUNCTION_1(indexedmesh_bind)
	DECLARE_FLEXSIM_FUNCTION_1(indexedmesh_defineindexbuffer)
	DECLARE_FLEXSIM_FUNCTION_1(indexedmesh_addindex)
	DECLARE_FLEXSIM_FUNCTION_1(indexedmesh_draw)
	DECLARE_FLEXSIM_FUNCTION_1(indexedmesh_cleanupindexbuffer)
	DECLARE_FLEXSIM_FUNCTION_1(fglInfo)


	
/*** FUNCTIONS ONLY REQUIRED FOR DLL PROJECT***/
#else
	DECLARE_FLEXSIM_FUNCTION_1(addsphere)
	DECLARE_FLEXSIM_FUNCTION_1(backupfile)
	DECLARE_FLEXSIM_FUNCTION_1(bcgetitemkinematics)
	DECLARE_FLEXSIM_FUNCTION_1(bcgetitemposition)
	DECLARE_FLEXSIM_FUNCTION_1(bcsetdirection)
	DECLARE_FLEXSIM_FUNCTION_1(bcsetitemconveystate)
	DECLARE_FLEXSIM_FUNCTION_1(changeconveyorspeed)
	DECLARE_FLEXSIM_FUNCTION_1(changetask)
	DECLARE_FLEXSIM_FUNCTION_1(closenodeedge)
	DECLARE_FLEXSIM_FUNCTION_1(codetotemplatetext)
	DECLARE_FLEXSIM_FUNCTION_1(consoleexecutecpp)
	DECLARE_FLEXSIM_FUNCTION_1(containerentry)
	DECLARE_FLEXSIM_FUNCTION_1(containerexit)
	DECLARE_FLEXSIM_FUNCTION_1(contextdragconnection)
	DECLARE_FLEXSIM_FUNCTION_1(createcoordinatedtasksequence)
	DECLARE_FLEXSIM_FUNCTION_1(createemptytasksequence)
	DECLARE_FLEXSIM_FUNCTION_1(distancetotravel)
	DECLARE_FLEXSIM_FUNCTION_1(drawspheres)
	DECLARE_FLEXSIM_FUNCTION_1(enablefullhistory)
	DECLARE_FLEXSIM_FUNCTION_1(fglinfo)
	DECLARE_FLEXSIM_FUNCTION_1(flexsimfree)
	DECLARE_FLEXSIM_FUNCTION_1(flexsimmalloc)
	DECLARE_FLEXSIM_FUNCTION_1(flexsimrealloc)
	DECLARE_FLEXSIM_FUNCTION_1(freeoperators)
	DECLARE_FLEXSIM_FUNCTION_1(getallocatedfromkey)
	DECLARE_FLEXSIM_FUNCTION_1(getcoordinatedtasksequence)
	DECLARE_FLEXSIM_FUNCTION_1(getcurtask)
	DECLARE_FLEXSIM_FUNCTION_1(getedgedist)
	DECLARE_FLEXSIM_FUNCTION_1(getedgespeedlimit)
	DECLARE_FLEXSIM_FUNCTION_1(geteventtime)
	DECLARE_FLEXSIM_FUNCTION_1(getiteminvolved)
	DECLARE_FLEXSIM_FUNCTION_1(getitemsendto)
	DECLARE_FLEXSIM_FUNCTION_1(getitemstate)
	DECLARE_FLEXSIM_FUNCTION_1(getitemvar)
	DECLARE_FLEXSIM_FUNCTION_1(getmodulelicense)
	DECLARE_FLEXSIM_FUNCTION_1(getmoverecord)
	DECLARE_FLEXSIM_FUNCTION_1(getmoverecordvalue)
	DECLARE_FLEXSIM_FUNCTION_1(getnetnode)
	DECLARE_FLEXSIM_FUNCTION_1(getnetnodespline)
	DECLARE_FLEXSIM_FUNCTION_1(getnetworkdistance)
	DECLARE_FLEXSIM_FUNCTION_1(getnextnetnode)
	DECLARE_FLEXSIM_FUNCTION_1(getnextnetnodeoutport)
	DECLARE_FLEXSIM_FUNCTION_1(getnroftasks)
	DECLARE_FLEXSIM_FUNCTION_1(getnummoverecords)
	DECLARE_FLEXSIM_FUNCTION_1(getnumstaterecords)
	DECLARE_FLEXSIM_FUNCTION_1(getobjvarfastpointer)
	DECLARE_FLEXSIM_FUNCTION_1(getobjvarfastpointeroffset)
	DECLARE_FLEXSIM_FUNCTION_1(getpreempt)
	DECLARE_FLEXSIM_FUNCTION_1(getpriority)
	DECLARE_FLEXSIM_FUNCTION_1(getstaterecord)
	DECLARE_FLEXSIM_FUNCTION_1(getstaterecordvalue)
	DECLARE_FLEXSIM_FUNCTION_1(gettaskinvolved)
	DECLARE_FLEXSIM_FUNCTION_1(gettasksequence)
	DECLARE_FLEXSIM_FUNCTION_1(gettasksequencequeue)
	DECLARE_FLEXSIM_FUNCTION_1(gettasktype)
	DECLARE_FLEXSIM_FUNCTION_1(gettaskvariable)
	DECLARE_FLEXSIM_FUNCTION_1(gettenetnode)
	DECLARE_FLEXSIM_FUNCTION_1(gettotalnroftasks)
	DECLARE_FLEXSIM_FUNCTION_1(holditem)
	DECLARE_FLEXSIM_FUNCTION_1(insertallocatetask)
	DECLARE_FLEXSIM_FUNCTION_1(insertmultiallocatetask)
	DECLARE_FLEXSIM_FUNCTION_1(insertsynctask)
	DECLARE_FLEXSIM_FUNCTION_1(isedgeforward)
	DECLARE_FLEXSIM_FUNCTION_1(license)
	DECLARE_FLEXSIM_FUNCTION_1(movetasksequence)
	DECLARE_FLEXSIM_FUNCTION_1(netnodefromrank)
	DECLARE_FLEXSIM_FUNCTION_1(opennodeedge)
	DECLARE_FLEXSIM_FUNCTION_1(optimizenetwork)
	DECLARE_FLEXSIM_FUNCTION_1(pickoffsetx)
	DECLARE_FLEXSIM_FUNCTION_1(pickoffsety)
	DECLARE_FLEXSIM_FUNCTION_1(pickoffsetz)
	DECLARE_FLEXSIM_FUNCTION_1(placeoffsetx)
	DECLARE_FLEXSIM_FUNCTION_1(placeoffsety)
	DECLARE_FLEXSIM_FUNCTION_1(placeoffsetz)
	DECLARE_FLEXSIM_FUNCTION_1(profiletasksequence)
	DECLARE_FLEXSIM_FUNCTION_1(rackdrawfilledcell)
	DECLARE_FLEXSIM_FUNCTION_1(rackdrawvirtualcontent)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetbaycontent)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetbayloc)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetbayofitem)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetbaysize)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetcellcontent)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetcellvar)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetcontenttable)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetitembybaylevel)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetlevelloc)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetlevelofitem)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetlevelsize)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetnrofbays)
	DECLARE_FLEXSIM_FUNCTION_1(rackgetnroflevels)
	DECLARE_FLEXSIM_FUNCTION_1(rackrecycleitem)
	DECLARE_FLEXSIM_FUNCTION_1(rackrestoreitem)
	DECLARE_FLEXSIM_FUNCTION_1(racksetcellcontent)
	DECLARE_FLEXSIM_FUNCTION_1(racksetcellvar)
	DECLARE_FLEXSIM_FUNCTION_1(rankfromnetnode)
	DECLARE_FLEXSIM_FUNCTION_1(reassignnetnode)
	DECLARE_FLEXSIM_FUNCTION_2(receiveitem_alias1, "receiveitem")
	DECLARE_FLEXSIM_FUNCTION_3(receiveitem_alias2, "?releaseitem@@YANPAVTreeNode@@H@Z", "?releaseitem@@YANPEAVTreeNode@@H@Z")
	DECLARE_FLEXSIM_FUNCTION_1(recycleitem)
	DECLARE_FLEXSIM_FUNCTION_1(recyclenode)
	DECLARE_FLEXSIM_FUNCTION_1(redirectnetworktraveler);
	DECLARE_FLEXSIM_FUNCTION_2(releaseitem_alias1, "releaseitem")
	DECLARE_FLEXSIM_FUNCTION_3(releaseitem_alias2, "?releaseitem@@YANPAVTreeNode@@H@Z", "?releaseitem@@YANPEAVTreeNode@@H@Z")
	DECLARE_FLEXSIM_FUNCTION_1(reordertasks)
	DECLARE_FLEXSIM_FUNCTION_1(requestoperators)
	DECLARE_FLEXSIM_FUNCTION_1(rerankbesttask)
	DECLARE_FLEXSIM_FUNCTION_1(resumeobjectalias)
	DECLARE_FLEXSIM_FUNCTION_1(resumetransportsin)
	DECLARE_FLEXSIM_FUNCTION_1(resumetransportsout)
	DECLARE_FLEXSIM_FUNCTION_1(savebyname)
	DECLARE_FLEXSIM_FUNCTION_1(savestoppedtransportin)
	DECLARE_FLEXSIM_FUNCTION_1(savestoppedtransportout)
	DECLARE_FLEXSIM_FUNCTION_1(senddelayedmessage)
	DECLARE_FLEXSIM_FUNCTION_1(setcollisioncheck)
	DECLARE_FLEXSIM_FUNCTION_1(seteventtime)
	DECLARE_FLEXSIM_FUNCTION_1(setiteminvolved)
	DECLARE_FLEXSIM_FUNCTION_1(setitemsendto)
	DECLARE_FLEXSIM_FUNCTION_1(setitemvar)
	DECLARE_FLEXSIM_FUNCTION_1(setpreempt)
	DECLARE_FLEXSIM_FUNCTION_1(setpriority)
	DECLARE_FLEXSIM_FUNCTION_1(setresetposition)
	DECLARE_FLEXSIM_FUNCTION_1(stopobject)
	DECLARE_FLEXSIM_FUNCTION_1(trafficcontrolinfo)
	DECLARE_FLEXSIM_FUNCTION_1(updatelocations)
	DECLARE_FLEXSIM_FUNCTION_2(dispatchcoordinatedtasksequencealias, "dispatchcoordinatedtasksequence")
	DECLARE_FLEXSIM_FUNCTION_2(dispatchtasksequencealias, "dispatchtasksequence")
	DECLARE_FLEXSIM_FUNCTION_2(gettreedrawpositionalias, "gettreedrawposition")
	DECLARE_FLEXSIM_FUNCTION_2(insertdeallocatetaskalias, "insertdeallocatetask")
	DECLARE_FLEXSIM_FUNCTION_2(insertproxytaskalias1, "insertproxytask")
	DECLARE_FLEXSIM_FUNCTION_3(insertproxytaskalias2, "?insertproxytask@@YAHPAVTreeNode@@II0@Z", "?insertproxytask@@YAHPEAVTreeNode@@II0@Z")
	DECLARE_FLEXSIM_FUNCTION_3(insertproxytaskalias3, "?insertproxytask@@YAHPAVTreeNode@@II0HNNNN@Z", "?insertproxytask@@YAHPEAVTreeNode@@II0HNNNN@Z")
	DECLARE_FLEXSIM_FUNCTION_3(insertproxytaskalias4, "?insertproxytask@@YAHPAVTreeNode@@II@Z", "?insertproxytask@@YAHPEAVTreeNode@@II@Z")
	DECLARE_FLEXSIM_FUNCTION_3(insertproxytaskalias5, "?insertproxytask@@YAHPAVTreeNode@@IIH0NNNN@Z", "?insertproxytask@@YAHPEAVTreeNode@@IIH0NNNN@Z")
	DECLARE_FLEXSIM_FUNCTION_3(insertproxytaskalias6, "?insertproxytask@@YAHPAVTreeNode@@IIH@Z", "?insertproxytask@@YAHPEAVTreeNode@@IIH@Z")
	DECLARE_FLEXSIM_FUNCTION_3(insertproxytaskalias7, "?insertproxytask@@YAHPAVTreeNode@@IIHHNNNN@Z", "?insertproxytask@@YAHPEAVTreeNode@@IIHHNNNN@Z")
	DECLARE_FLEXSIM_FUNCTION_2(inserttaskalias, "inserttask")
	DECLARE_FLEXSIM_FUNCTION_2(transportincompletealias, "transportincomplete")
	DECLARE_FLEXSIM_FUNCTION_2(transportoutcompletealias, "transportoutcomplete")
#endif

/*** FLEXSIM ATTRIBUTES ***/
DECLARE_FLEXSIM_ATTRIBUTE(alignbottommargin)
DECLARE_FLEXSIM_ATTRIBUTE(alignbottomposition)
DECLARE_FLEXSIM_ATTRIBUTE(aligncenterx)
DECLARE_FLEXSIM_ATTRIBUTE(aligncentery)
DECLARE_FLEXSIM_ATTRIBUTE(alignrightmargin)
DECLARE_FLEXSIM_ATTRIBUTE(alignrightposition)
DECLARE_FLEXSIM_ATTRIBUTE(animationinfo)
DECLARE_FLEXSIM_ATTRIBUTE(assertupdate)
DECLARE_FLEXSIM_ATTRIBUTE(behaviour)
DECLARE_FLEXSIM_ATTRIBUTE(beveltype)
DECLARE_FLEXSIM_ATTRIBUTE(bitmap)
DECLARE_FLEXSIM_ATTRIBUTE(cellheight)
DECLARE_FLEXSIM_ATTRIBUTE(cellwidth)
DECLARE_FLEXSIM_ATTRIBUTE(centroid)
DECLARE_FLEXSIM_ATTRIBUTE(classes)
DECLARE_FLEXSIM_ATTRIBUTE(coldlink)
DECLARE_FLEXSIM_ATTRIBUTE(coldlinkname)
DECLARE_FLEXSIM_ATTRIBUTE(coldlinknamex)
DECLARE_FLEXSIM_ATTRIBUTE(coldlinkx)
DECLARE_FLEXSIM_ATTRIBUTE(color)
DECLARE_FLEXSIM_ATTRIBUTE(connections)
DECLARE_FLEXSIM_ATTRIBUTE(connectionscenter)
DECLARE_FLEXSIM_ATTRIBUTE(connectionsin)
DECLARE_FLEXSIM_ATTRIBUTE(connectionsout)
DECLARE_FLEXSIM_ATTRIBUTE(connectorsize)
DECLARE_FLEXSIM_ATTRIBUTE(connectorstyle)
DECLARE_FLEXSIM_ATTRIBUTE(cppfunctions)
DECLARE_FLEXSIM_ATTRIBUTE(cppvariables)
DECLARE_FLEXSIM_ATTRIBUTE(customaction)
DECLARE_FLEXSIM_ATTRIBUTE(deassertupdate)
DECLARE_FLEXSIM_ATTRIBUTE(description)
DECLARE_FLEXSIM_ATTRIBUTE(drawsurrogate)
DECLARE_FLEXSIM_ATTRIBUTE(eventfunctions)
DECLARE_FLEXSIM_ATTRIBUTE(frame)
DECLARE_FLEXSIM_ATTRIBUTE(graphannotate)
DECLARE_FLEXSIM_ATTRIBUTE(graphaxes)
DECLARE_FLEXSIM_ATTRIBUTE(graphbars)
DECLARE_FLEXSIM_ATTRIBUTE(graphgrid)
DECLARE_FLEXSIM_ATTRIBUTE(graphhistodata)
DECLARE_FLEXSIM_ATTRIBUTE(graphlegend)
DECLARE_FLEXSIM_ATTRIBUTE(graphlegendhisto)
DECLARE_FLEXSIM_ATTRIBUTE(graphlines)
DECLARE_FLEXSIM_ATTRIBUTE(graphmaxpoints)
DECLARE_FLEXSIM_ATTRIBUTE(graphpie)
DECLARE_FLEXSIM_ATTRIBUTE(graphpiedata)
DECLARE_FLEXSIM_ATTRIBUTE(graphpoints)
DECLARE_FLEXSIM_ATTRIBUTE(graphstep)
DECLARE_FLEXSIM_ATTRIBUTE(graphtitle)
DECLARE_FLEXSIM_ATTRIBUTE(graphxy)
DECLARE_FLEXSIM_ATTRIBUTE(grayed)
DECLARE_FLEXSIM_ATTRIBUTE(gridfog)
DECLARE_FLEXSIM_ATTRIBUTE(gridlinecolor)
DECLARE_FLEXSIM_ATTRIBUTE(gridlinewidth)
DECLARE_FLEXSIM_ATTRIBUTE(gridx)
DECLARE_FLEXSIM_ATTRIBUTE(gridy)
DECLARE_FLEXSIM_ATTRIBUTE(gridz)
DECLARE_FLEXSIM_ATTRIBUTE(guifocus)
DECLARE_FLEXSIM_ATTRIBUTE(guifocusclass)
DECLARE_FLEXSIM_ATTRIBUTE(hidden)
DECLARE_FLEXSIM_ATTRIBUTE(hotlink)
DECLARE_FLEXSIM_ATTRIBUTE(hotlinkname)
DECLARE_FLEXSIM_ATTRIBUTE(hotlinknamex)
DECLARE_FLEXSIM_ATTRIBUTE(hotlinkx)
DECLARE_FLEXSIM_ATTRIBUTE(imagebase)
DECLARE_FLEXSIM_ATTRIBUTE(imageindexbase)
DECLARE_FLEXSIM_ATTRIBUTE(imageindexobject)
DECLARE_FLEXSIM_ATTRIBUTE(imageobject)
DECLARE_FLEXSIM_ATTRIBUTE(initialtext)
DECLARE_FLEXSIM_ATTRIBUTE(itemcurrent)
DECLARE_FLEXSIM_ATTRIBUTE(items)
DECLARE_FLEXSIM_ATTRIBUTE(itemtype)
DECLARE_FLEXSIM_ATTRIBUTE(labels)
DECLARE_FLEXSIM_ATTRIBUTE(labelscale)
DECLARE_FLEXSIM_ATTRIBUTE(listeners)
DECLARE_FLEXSIM_ATTRIBUTE(menucustom)
DECLARE_FLEXSIM_ATTRIBUTE(menupopup)
DECLARE_FLEXSIM_ATTRIBUTE(menuview)
DECLARE_FLEXSIM_ATTRIBUTE(noformat)
DECLARE_FLEXSIM_ATTRIBUTE(objectfocus)
DECLARE_FLEXSIM_ATTRIBUTE(objectinfo)
DECLARE_FLEXSIM_ATTRIBUTE(offsetrx)
DECLARE_FLEXSIM_ATTRIBUTE(offsetry)
DECLARE_FLEXSIM_ATTRIBUTE(offsetrz)
DECLARE_FLEXSIM_ATTRIBUTE(offsetsx)
DECLARE_FLEXSIM_ATTRIBUTE(offsetsy)
DECLARE_FLEXSIM_ATTRIBUTE(offsetsz)
DECLARE_FLEXSIM_ATTRIBUTE(offsetx)
DECLARE_FLEXSIM_ATTRIBUTE(offsety)
DECLARE_FLEXSIM_ATTRIBUTE(offsetz)
DECLARE_FLEXSIM_ATTRIBUTE(OnClick)
DECLARE_FLEXSIM_ATTRIBUTE(OnClose)
DECLARE_FLEXSIM_ATTRIBUTE(OnCompile)
DECLARE_FLEXSIM_ATTRIBUTE(OnCreate)
DECLARE_FLEXSIM_ATTRIBUTE(OnDestroy)
DECLARE_FLEXSIM_ATTRIBUTE(OnDrag)
DECLARE_FLEXSIM_ATTRIBUTE(OnDraw)
DECLARE_FLEXSIM_ATTRIBUTE(OnDrawPlanar)
DECLARE_FLEXSIM_ATTRIBUTE(OnDrop)
DECLARE_FLEXSIM_ATTRIBUTE(OnDropFile)
DECLARE_FLEXSIM_ATTRIBUTE(OnDropNode)
DECLARE_FLEXSIM_ATTRIBUTE(OnEntering)
DECLARE_FLEXSIM_ATTRIBUTE(OnExiting)
DECLARE_FLEXSIM_ATTRIBUTE(OnInOpen)
DECLARE_FLEXSIM_ATTRIBUTE(OnKeyDown)
DECLARE_FLEXSIM_ATTRIBUTE(OnKeyUp)
DECLARE_FLEXSIM_ATTRIBUTE(OnListen)
DECLARE_FLEXSIM_ATTRIBUTE(OnLoad)
DECLARE_FLEXSIM_ATTRIBUTE(OnMessage)
DECLARE_FLEXSIM_ATTRIBUTE(OnMouseButtonDown)
DECLARE_FLEXSIM_ATTRIBUTE(OnMouseButtonUp)
DECLARE_FLEXSIM_ATTRIBUTE(OnMouseMove)
DECLARE_FLEXSIM_ATTRIBUTE(OnMouseWheel)
DECLARE_FLEXSIM_ATTRIBUTE(OnOpen)
DECLARE_FLEXSIM_ATTRIBUTE(OnOutOpen)
DECLARE_FLEXSIM_ATTRIBUTE(OnPreDraw)
DECLARE_FLEXSIM_ATTRIBUTE(OnPreDrawPlanar)
DECLARE_FLEXSIM_ATTRIBUTE(OnPreListen)
DECLARE_FLEXSIM_ATTRIBUTE(OnPreOpen)
DECLARE_FLEXSIM_ATTRIBUTE(OnPress)
DECLARE_FLEXSIM_ATTRIBUTE(OnReceive)
DECLARE_FLEXSIM_ATTRIBUTE(OnReset)
DECLARE_FLEXSIM_ATTRIBUTE(OnRunEnd)
DECLARE_FLEXSIM_ATTRIBUTE(OnRunStart)
DECLARE_FLEXSIM_ATTRIBUTE(OnSelect)
DECLARE_FLEXSIM_ATTRIBUTE(OnSend)
DECLARE_FLEXSIM_ATTRIBUTE(OnStateChange)
DECLARE_FLEXSIM_ATTRIBUTE(OnStick)
DECLARE_FLEXSIM_ATTRIBUTE(OnTimerEvent)
DECLARE_FLEXSIM_ATTRIBUTE(pagelist)
DECLARE_FLEXSIM_ATTRIBUTE(palettewindow)
DECLARE_FLEXSIM_ATTRIBUTE(pickcopydataonly)
DECLARE_FLEXSIM_ATTRIBUTE(pickitem)
DECLARE_FLEXSIM_ATTRIBUTE(picklist)
DECLARE_FLEXSIM_ATTRIBUTE(picklistnameonly)
DECLARE_FLEXSIM_ATTRIBUTE(pickprimary)
DECLARE_FLEXSIM_ATTRIBUTE(picture)
DECLARE_FLEXSIM_ATTRIBUTE(rangeexp)
DECLARE_FLEXSIM_ATTRIBUTE(rangemax)
DECLARE_FLEXSIM_ATTRIBUTE(rangemin)
DECLARE_FLEXSIM_ATTRIBUTE(resizeinfo)
DECLARE_FLEXSIM_ATTRIBUTE(shape)
DECLARE_FLEXSIM_ATTRIBUTE(shapeindex)
DECLARE_FLEXSIM_ATTRIBUTE(sound)
DECLARE_FLEXSIM_ATTRIBUTE(soundindex)
DECLARE_FLEXSIM_ATTRIBUTE(spatialrx)
DECLARE_FLEXSIM_ATTRIBUTE(spatialry)
DECLARE_FLEXSIM_ATTRIBUTE(spatialrz)
DECLARE_FLEXSIM_ATTRIBUTE(spatialsx)
DECLARE_FLEXSIM_ATTRIBUTE(spatialsy)
DECLARE_FLEXSIM_ATTRIBUTE(spatialsz)
DECLARE_FLEXSIM_ATTRIBUTE(spatialx)
DECLARE_FLEXSIM_ATTRIBUTE(spatialy)
DECLARE_FLEXSIM_ATTRIBUTE(spatialz)
DECLARE_FLEXSIM_ATTRIBUTE(state_current)
DECLARE_FLEXSIM_ATTRIBUTE(state_profile)
DECLARE_FLEXSIM_ATTRIBUTE(state_profiles)
DECLARE_FLEXSIM_ATTRIBUTE(state_since)
DECLARE_FLEXSIM_ATTRIBUTE(stats_content)
DECLARE_FLEXSIM_ATTRIBUTE(stats_contentavg)
DECLARE_FLEXSIM_ATTRIBUTE(stats_contentgraph)
DECLARE_FLEXSIM_ATTRIBUTE(stats_contentgraphmaxpoints)
DECLARE_FLEXSIM_ATTRIBUTE(stats_contentmax)
DECLARE_FLEXSIM_ATTRIBUTE(stats_contentmin)
DECLARE_FLEXSIM_ATTRIBUTE(stats_contentsince)
DECLARE_FLEXSIM_ATTRIBUTE(stats_contentupdates)
DECLARE_FLEXSIM_ATTRIBUTE(stats_creationtime)
DECLARE_FLEXSIM_ATTRIBUTE(stats_input)
DECLARE_FLEXSIM_ATTRIBUTE(stats_lastmovetime)
DECLARE_FLEXSIM_ATTRIBUTE(stats_output)
DECLARE_FLEXSIM_ATTRIBUTE(stats_staytime)
DECLARE_FLEXSIM_ATTRIBUTE(stats_staytimeavg)
DECLARE_FLEXSIM_ATTRIBUTE(stats_staytimegraph)
DECLARE_FLEXSIM_ATTRIBUTE(stats_staytimegraphmaxpoints)
DECLARE_FLEXSIM_ATTRIBUTE(stats_staytimehisto)
DECLARE_FLEXSIM_ATTRIBUTE(stats_staytimemax)
DECLARE_FLEXSIM_ATTRIBUTE(stats_staytimemin)
DECLARE_FLEXSIM_ATTRIBUTE(stats_staytimesince)
DECLARE_FLEXSIM_ATTRIBUTE(stats_staytimeupdates)
DECLARE_FLEXSIM_ATTRIBUTE(stats_throughput)
DECLARE_FLEXSIM_ATTRIBUTE(statusbar)
DECLARE_FLEXSIM_ATTRIBUTE(stored)
DECLARE_FLEXSIM_ATTRIBUTE(superclasses)
DECLARE_FLEXSIM_ATTRIBUTE(tabwindow)
DECLARE_FLEXSIM_ATTRIBUTE(title)
DECLARE_FLEXSIM_ATTRIBUTE(tooltip)
DECLARE_FLEXSIM_ATTRIBUTE(treeiconhide)
DECLARE_FLEXSIM_ATTRIBUTE(treeiconindex)
DECLARE_FLEXSIM_ATTRIBUTE(treeiconsilentobject)
DECLARE_FLEXSIM_ATTRIBUTE(treeicontitle)
DECLARE_FLEXSIM_ATTRIBUTE(uniqueid)
DECLARE_FLEXSIM_ATTRIBUTE(userfunctions)
DECLARE_FLEXSIM_ATTRIBUTE(variables)
DECLARE_FLEXSIM_ATTRIBUTE(viewautoconnect)
DECLARE_FLEXSIM_ATTRIBUTE(viewbackgroundcolor)
DECLARE_FLEXSIM_ATTRIBUTE(viewconnectioncolor)
DECLARE_FLEXSIM_ATTRIBUTE(viewfar)
DECLARE_FLEXSIM_ATTRIBUTE(viewfield)
DECLARE_FLEXSIM_ATTRIBUTE(viewfirstperson)
DECLARE_FLEXSIM_ATTRIBUTE(viewfocus)
DECLARE_FLEXSIM_ATTRIBUTE(viewfog)
DECLARE_FLEXSIM_ATTRIBUTE(viewfull)
DECLARE_FLEXSIM_ATTRIBUTE(viewhideallbases)
DECLARE_FLEXSIM_ATTRIBUTE(viewhideallconnectors)
DECLARE_FLEXSIM_ATTRIBUTE(viewhidealldrawcontent)
DECLARE_FLEXSIM_ATTRIBUTE(viewhidealllabels)
DECLARE_FLEXSIM_ATTRIBUTE(viewhiderouting)
DECLARE_FLEXSIM_ATTRIBUTE(viewignoreobjects)
DECLARE_FLEXSIM_ATTRIBUTE(viewlabelalignment)
DECLARE_FLEXSIM_ATTRIBUTE(viewlights)
DECLARE_FLEXSIM_ATTRIBUTE(viewmagnification)
DECLARE_FLEXSIM_ATTRIBUTE(viewnear)
DECLARE_FLEXSIM_ATTRIBUTE(viewpointradius)
DECLARE_FLEXSIM_ATTRIBUTE(viewpointrx)
DECLARE_FLEXSIM_ATTRIBUTE(viewpointry)
DECLARE_FLEXSIM_ATTRIBUTE(viewpointrz)
DECLARE_FLEXSIM_ATTRIBUTE(viewpointx)
DECLARE_FLEXSIM_ATTRIBUTE(viewpointy)
DECLARE_FLEXSIM_ATTRIBUTE(viewpointz)
DECLARE_FLEXSIM_ATTRIBUTE(viewprojectiontype)
DECLARE_FLEXSIM_ATTRIBUTE(viewshowgrid)
DECLARE_FLEXSIM_ATTRIBUTE(viewshowheads)
DECLARE_FLEXSIM_ATTRIBUTE(viewsnaptogrid)
DECLARE_FLEXSIM_ATTRIBUTE(viewsyncupdate)
DECLARE_FLEXSIM_ATTRIBUTE(viewwindowclean)
DECLARE_FLEXSIM_ATTRIBUTE(viewwindowopen)
DECLARE_FLEXSIM_ATTRIBUTE(viewwindowsource)
DECLARE_FLEXSIM_ATTRIBUTE(viewwindowtype)
DECLARE_FLEXSIM_ATTRIBUTE(windowtitle)
DECLARE_FLEXSIM_ATTRIBUTE(wordwrap)

#if DECLARATIONTYPE == FLEXSIM_DECLARATION_PHASE
	#include "declaration.h"
#elif DECLARATIONTYPE == FLEXSIM_DEFINITION_PHASE
	#include "definition.h"
#endif

#if !defined COMPILING_FLEXSIM_CONTENT && !defined COMPILING_MODULE_DLL
	#include "UserFuncs.h"
#endif
