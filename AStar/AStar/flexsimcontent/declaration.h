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

#ifndef DECLARATION_H
#define DECLARATION_H

int bindflexsimfunctions();

// The following are special types of definition. Add your own special function definitions
// to the end of this file.
inline TreeNode* sets(treenode attnode, string s){
	bbsetsize(attnode, s.length() + 1);
	char* deststr = bbgetbuffer(attnode);
	strcpy(deststr, s.c_str());
	return attnode;
}
inline string concat(string p1,string p2,string p3="",string p4="",string p5="",string p6="",string p7="",string p8="",string p9="",string p10="",string p11="",string p12="",string p13="",string p14="",string p15="",string p16="",string p17="",string p18="",string p19="",string p20="")
	{string x = "";x.append(p1);x.append(p2);x.append(p3);x.append(p4);x.append(p5);x.append(p6);x.append(p7);x.append(p8);x.append(p9);x.append(p10);x.append(p11);x.append(p12);x.append(p13);x.append(p14);x.append(p15);x.append(p16);x.append(p17);x.append(p18);x.append(p19);x.append(p20);return x;}
inline treenode node(string path, treenode from = NULL){return nodealias((char*)path.c_str(), from);}
inline string gets(treenode thenode){char* x = bbgetbuffer(thenode);if(x) return string(x); else return string("");}
inline string getnodestr(treenode thenode){string x = bbgetbuffer(thenode);return x;}
inline treenode reftable(string globaltablename){return reftablealias((char*)globaltablename.c_str());}
inline string numtostring(double val, int wid=0, int prec=0)
{
  char buffer[1024];
  sprintf(buffer,"%*.*f",wid,prec,val);
  string x=buffer;
  return x;
}
inline treenode reftable(int globaltablerank){
	string nodestr = concat("/Tools/GlobalTables/",numtostring(globaltablerank,0,0),">variables/data");
	return node((char*)nodestr.c_str(),model());

}
inline int moveobject(treenode client, treenode destination, int port=0){return moveobjectalias1(client, destination, port);}
inline int moveobject(treenode client, treenode destination, int port, int receivingport){return moveobjectalias2(client, destination, port, receivingport);}

inline treenode label(treenode obj, int labelrank){return rank(labels(obj), labelrank);}
inline treenode addlabel(treenode obj, string labelname, double value = 0){return addlabel_importedfunction(obj, (char*)labelname.c_str(), value);}
inline treenode addlabel(treenode obj, string labelname, string value){treenode label = addlabel_importedfunction(obj, (char*)labelname.c_str(), 0);nodeadddata(label, DATA_BYTEBLOCK);sets(label, value);return label;}
inline treenode label(treenode object, string labelname){string path = concat("/",labelname); return node((char*)(path.c_str()), labels(object));}
inline double getlabelnum(treenode object, int labelrank){return get(rank(labels(object), labelrank));}
inline double getlabelnum(treenode object, string labelname){string path = concat("/",labelname); return getnodenum(node((char*)(path.c_str()), labels(object)));}
inline string getlabelstr(treenode object, int labelrank){return gets(rank(labels(object), labelrank));}
inline string getlabelstr(treenode object, string labelname){string path = concat("/",labelname); return gets(node((char*)(path.c_str()), labels(object)));}
inline double setlabelnum(treenode object, int labelrank, double val){set(rank(labels(object), labelrank), val);return 0;}
inline double setlabelnum(treenode object, string labelname, double val){string path = concat("/",labelname); set(node((char*)(path.c_str()), labels(object)), val);return 0;}
inline double setlabelstr(treenode object, int labelrank, string val){sets(rank(labels(object), labelrank), val);return 0;}
inline double setlabelstr(treenode object, string labelname, string val){sets(label(object, labelname), val);return 0;}
inline double gettablenum(treenode thetable, int row, int col){return get(cellrc(thetable, row, col));}
inline double gettablenum(string tablename, int row, int col){return gettablenumalias((char*)tablename.c_str(), row, col);}
inline treenode gettablecell(treenode thetable, int row, int col){return cellrc(thetable, row, col);}
inline treenode gettablecell(string tablename, int row, int col){return cellrc(reftable(tablename), row, col);}
inline treenode gettablecell(int table, int row, int col){return cellrc(reftable(table), row, col);}
inline string gettablestr(treenode thetable, int row, int col){return gets(cellrc(thetable, row, col));}
inline string gettablestr(string tablename, int row, int col){return gets(cellrc(reftable(tablename), row, col));}
inline string gettablestr(int table, int row, int col){return gets(cellrc(reftable(table), row, col));}
inline double settablenum(treenode thetable, int row, int col, double val){set(cellrc(thetable, row, col), val);return 0;}
inline double settablenum(string tablename, int row, int col, double val){settablenumalias((char*)tablename.c_str(), row, col, val);return 0;}
inline double settablestr(treenode thetable, int row, int col, char* val){sets(cellrc(thetable, row, col), val);return 0;}
inline double settablestr(treenode thetable, int row, int col, string val){sets(cellrc(thetable, row, col), val);return 0;}
inline double settablestr(string tablename, int row, int col, string val){sets(cellrc(reftable(tablename), row, col), val);return 0;}
inline double settablestr(int table, int row, int col, char* val){sets(cellrc(reftable(table), row, col), val);return 0;}
inline treenode addtablerow(treenode table, int row=0, int datatype=0){return addtablerowalias(table,row,datatype);}
inline treenode addtablerow(char* tablename, int row=0, int datatype=0){return addtablerowalias(reftable(tablename),row,datatype);}
inline treenode addtablerow(int table, int row=0, int datatype=0){return addtablerowalias(reftable(table),row,datatype);}
inline treenode addtablerow(string tablename, int row=0, int datatype=0){return addtablerowalias(reftable(tablename),row,datatype);}
inline int deletetablerow(treenode table, int row=0){return deletetablerowalias(table,row);}
inline int deletetablerow(char* tablename, int row=0){return deletetablerowalias(reftable(tablename),row);}
inline int deletetablerow(int table, int row=0){return deletetablerowalias(reftable(table),row);}
inline int deletetablerow(string tablename, int row=0){return deletetablerowalias(reftable(tablename),row);}
inline int movetablerow(treenode table, int row, int newrow){return movetablerowalias(table,row,newrow);}
inline int movetablerow(char* tablename, int row, int newrow){return movetablerowalias(reftable(tablename),row,newrow);}
inline int movetablerow(int table, int row, int newrow){return movetablerowalias(reftable(table),row,newrow);}
inline int movetablerow(string tablename, int row, int newrow){return movetablerowalias(reftable(tablename),row,newrow);}
inline int swaptablerows(treenode table, int row, int row2){return swaptablerowsalias(table,row,row2);}
inline int swaptablerows(char* tablename, int row, int row2){return swaptablerowsalias(reftable(tablename),row,row2);}
inline int swaptablerows(int table, int row, int row2){return swaptablerowsalias(reftable(table),row,row2);}
inline int swaptablerows(string tablename, int row, int row2){return swaptablerowsalias(reftable(tablename),row,row2);}
inline treenode addtablecol(treenode table, int col=0, int datatype=0){return addtablecolalias(table,col,datatype);}
inline treenode addtablecol(char* tablename, int col=0, int datatype=0){return addtablecolalias(reftable(tablename),col,datatype);}
inline treenode addtablecol(int table, int col=0, int datatype=0){return addtablecolalias(reftable(table),col,datatype);}
inline treenode addtablecol(string tablename, int col=0, int datatype=0){return addtablecolalias(reftable(tablename),col,datatype);}
inline int deletetablecol(treenode table, int col=0){return deletetablecolalias(table,col);}
inline int deletetablecol(char* tablename, int col=0){return deletetablecolalias(reftable(tablename),col);}
inline int deletetablecol(int table, int col=0){return deletetablecolalias(reftable(table),col);}
inline int deletetablecol(string tablename, int col=0){return deletetablecolalias(reftable(tablename),col);}
inline int movetablecol(treenode table, int col, int newcol){return movetablecolalias(table,col,newcol);}
inline int movetablecol(char* tablename, int col, int newcol){return movetablecolalias(reftable(tablename),col,newcol);}
inline int movetablecol(int table, int col, int newcol){return movetablecolalias(reftable(table),col,newcol);}
inline int movetablecol(string tablename, int col, int newcol){return movetablecolalias(reftable(tablename),col,newcol);}
inline int swaptablecols(treenode table, int col, int col2){return swaptablecolsalias(table,col,col2);}
inline int swaptablecols(char* tablename, int col, int col2){return swaptablecolsalias(reftable(tablename),col,col2);}
inline int swaptablecols(int table, int col, int col2){return swaptablecolsalias(reftable(table),col,col2);}
inline int swaptablecols(string tablename, int col, int col2){return swaptablecolsalias(reftable(tablename),col,col2);}

inline double time(){return loc_clock()[0];}
inline double stop(int fast = 0){return stopalias(fast);}
inline double msg(char* a, char* b, int mode = 0){return msgalias(a,b,mode);}
inline double msg(string a, string b, int mode = 0){return msgalias((char*)a.c_str(),(char*)b.c_str(),mode);}
inline double sqr(double n1){return n1*n1;}
inline int avistart(string s, treenode winnode, double fps, double uc);

inline TreeNode* setnodestr(treenode attnode, string s){
	bbsetsize(attnode, s.length() + 1);
	char* deststr = bbgetbuffer(attnode);
	strcpy(deststr, s.c_str());
	return attnode;
}

inline void initkinematics(treenode infonode, treenode obj, int _managerotation = 0, int _relativelocs = 0)
	{initkinematicsalias(infonode, xloc(obj), yloc(obj), zloc(obj), xrot(obj), yrot(obj), zrot(obj), _managerotation, _relativelocs);}
inline void initkinematics(treenode infonode, double x, double y, double z, double rx = 0, double ry = 0, double rz = 0, int _managerotation = 0, int _relativelocs = 0)
	{initkinematicsalias(infonode, x,y,z,rx,ry,rz,_managerotation,_relativelocs);}


inline double nodefunction(treenode thenode, double p1=0, double p2=0, double p3=0, double p4=0, double p5=0, double p6=0, double p7=0, double p8=0, double p9=0, double p10=0)
	{return importednodefunction(thenode, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10);}
inline treenode delayednodefunction(treenode theNode, double timeOffset, double p1=0, double p2=0, double p3=0, double p4=0, double p5=0, double p6=0, double p7=0, double p8=0, double p9=0, double p10=0)
	{return delayednodefunctionalias(theNode, timeOffset, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10);}
inline treenode nodefunctionlisten(treenode theNode, treenode relayNode, int flags = 0, double p1=0, double p2=0, double p3=0, double p4=0, double p5=0, double p6=0, double p7=0, double p8=0, double p9=0, double p10=0)
	{return nodefunctionlistenalias(theNode, relayNode, flags, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10);}
inline double dllstop(){return stop(0);}
inline int dllmoveobject(treenode client, treenode destination){return moveobject(client, destination, 0);}

inline TreeNode* setname(treenode obj, string name)
{
	return setname_alias(obj, (char*)name.c_str());
}
inline TreeNode* setnodename(treenode obj, string name)
{
	return setname_alias(obj, (char*)name.c_str());
}
inline string getname(treenode obj)
{
  string x="NULL";
  if(validlink(obj,"getname")) x=namebbgetbuffer(obj);
  return x;
}
inline string getnodename(treenode obj)
{
	string s = namebbgetbuffer(obj);
	return s;
}
inline string nodetopath(treenode from, int byname = 0)
{
	string s;
	if(!objectexists(from)) return "";
	char buffer[1024];
	if(byname)
		nodetotextpath(from,buffer);
	else nodetotextpath_indexed(from,buffer);

	s=buffer;
	return s;
}
inline string nodetomodelpath(treenode from, int byname = 0)
{
	string s = nodetomodelpath_cstr(from, byname);
	return s;
}

inline int stringlen(string str)
{
	return str.length();
}
inline double stringtonum(string str)
{
	return stringtonumalias((char*)str.c_str());
}
inline TreeNode* tonode(FlexSimValue& x) { return (TreeNode*)x; }
inline TreeNode* tonode(TreeNode* x) { return x; }
inline TreeNode* tonode(size_t x) { return tonodealias1(x); }
inline TreeNode* tonode(double x) { return tonodealias2(x); }
inline TreeNode* tonode(char* x) { return tonodealias3(x); }
inline TreeNode* tonode(void* x) { return tonodealias4(x); }
inline double tonum(FlexSimValue& x) {return x.asDouble;}
inline double tonum(double x) {return x;}
inline double tonum(treenode x) {return ptrtodouble((void*)x);}
inline double tonum(char* x) {return ptrtodouble((void*)x);}
inline double tonum(std::string& x) {return ptrtodouble((void*)x.c_str());}
inline string stringcopy(string str1, int start, int len)
{
  char *buffer=new char[len+5];
  strncpy(buffer,str1.c_str()+start-1,len);
  buffer[len]=0;
  string x=buffer;
  delete [] buffer;
  return x;
}
inline string stringpart(string str1, int start, int len)
{
  char *buffer=new char[len+5];
  strncpy(buffer,str1.c_str()+start,len);
  buffer[len]=0;
  string x=buffer;
  delete [] buffer;
  return x;
}
inline string tostring(char * c)
{
  string x=c;
  return x;
}
inline int comparetext(string str1, string str2)
{
  return str1==str2;
}
inline int comparetext(string str1, string str2, int ignorecase){return comparetextalias1((char*)str1.c_str(), (char*)str2.c_str(), ignorecase);}
inline int stringcompare(string str1, string str2)
{
  return strcmp((char*)str1.c_str(),(char*)str2.c_str());
}
inline char *stringtopchar(string & s){return ((char*)s.c_str());}
inline string getviewtext(treenode target)
{
	string s = getviewtext_cstr(target);
	return s;
}
inline char * apchar(string &s){return ((char*)s.c_str());}
inline char * apchar(void *s){return (char*)s;}
inline string pfile(){return (string)pfile_cstr();}
inline string parg(){return (string)parg_cstr();}
inline string strascii(int c)
{
  char cc[2];
  sprintf(cc,"%c",c);
  string ss=cc;
  return ss;
}
inline string strquote(string s)
{
  string ss="";
  ss = "\""+ s + "\"";
  return s;
}
inline int executefsfile(string s, int direct = 0){return _executefsfile((char*)s.c_str(), direct);}
inline int avistart(string s, treenode winnode, double fps, double uc){return avistart_importedfunction((char*)s.c_str(), winnode, fps, uc);}
inline string pdir(){return (string)pdir_cstr();}
inline string cdir(){return (string)cdir_cstr();}
inline string modeldir() {return (string)modeldir_cstr();}
inline string currentfile() {return (string)currentfile_cstr();}
inline int pt(string s){return pt_importedfunction((char*)s.c_str());}
inline int fpt(string s){return fpt_importedfunction((char*)s.c_str());}
inline double excelwritestr(int row, int col, string data){return excelwritestr_importedfunction(row, col, (char*)data.c_str());}
inline char * filebrowse(string ext, string desc, string path){return filebrowse_importedfunction((char*)ext.c_str(), (char*)desc.c_str(), (char*)path.c_str());}
inline string getmodelunitstr(int querytype){return (string)getmodelunitstr_cstr(querytype);}
inline string getstatestr(treenode object){return getname(rank(state_profile(object),(int)getnodenum(state_current(object))));}
inline string getvarstr(treenode object, char *varname){return getnodestr(var_s(object,varname));}
inline string getvarstr(treenode object, int varrank){return getnodestr(var(object,varrank));}
inline double getvarnum(treenode object, char* varname){return getnodenum(var_s(object,varname));}
inline double getvarnum(treenode object, int varrank){return getnodenum(var(object,varrank));}
inline double setvarstr(treenode object, string varname, string val){return setvarstralias(object, (char*)varname.c_str(), (char*)varname.c_str());}
inline double setvarstr(treenode object, int varrank, string val){setnodestr(var(object,varrank), val);return 0;}
inline double setvarnum(treenode object, string varname, double val){return setvarnumalias(object,(char*)varname.c_str(),val);}
inline double setvarnum(treenode object, int varrank, double val){setnodenum(var(object,varrank), val);return 0;}
inline treenode getvarnode(treenode thenode, char* thename){return getvarnodeimport(thenode, thename);}
inline treenode getvarnode(treenode thenode, int therank){return rank(variables(thenode), therank);}
inline double showprogressbar(string text){return showprogressbar_importedfunction((char*)text.c_str());}
//double userinput(treenode variable, string prompt){return userinput_importedfunction(variable, (char*)prompt.c_str());}
inline string gettableheader(treenode table, int roworcol, int rowcolnr){
	if(!objectexists(table)) return "Error: table not exists in gettableheader.";
	if(roworcol==1)	// return row header
		return getname(rank(table, rowcolnr));
	else				// return col header
		return getname(rank(rank(table, 1),rowcolnr));
}
inline string gettableheader(string table, int roworcol, int rowcolnr){
	return gettableheader(reftable((char*)table.c_str()), roworcol, rowcolnr);
}
inline string gettableheader(int table, int roworcol, int rowcolnr){
	return gettableheader(reftable(table), roworcol, rowcolnr);
}
inline int settableheader(treenode table, int roworcol, int rowcolnr, string value){
	if(!objectexists(table)) return 0;
	if(roworcol==1){	// set row header
		setname(rank(table, rowcolnr), value);
		return 1;
	}
	else{				// set col header
		setname(rank(rank(table, 1),rowcolnr), value);
		return 1;
	}
}
inline int settableheader(string table, int roworcol, int rowcolnr, string value){return settableheader(reftable(table), roworcol, rowcolnr, value);}
inline int settableheader(int table, int roworcol, int rowcolnr, string value){return settableheader(reftable(table), roworcol, rowcolnr, value);}

inline int gettablerows(treenode table){return content(table);}
inline int gettablerows(string table){return gettablerows(reftable(table));}
inline int gettablerows(int table){return gettablerows(reftable(table));}

inline double settablesize(char* table,int nrows,int ncols, int type = 1, int overwrite = 0){return settablesizealias(table, nrows, ncols, type, overwrite);}
inline double settablesize(string table,int nrows,int ncols, int type = 1, int overwrite = 0){return settablesizealias((char*)table.c_str(), nrows, ncols, type, overwrite);}
inline double settablesize(treenode table,int nrows,int ncols, int type = 1, int overwrite = 0){return settable(table, ncols, nrows, type, overwrite);}

inline double importtable(treenode node, char * table, int usetopgrey, int useleftgrey) {return importtablealias(node, table, usetopgrey, useleftgrey);}
inline double importtable(treenode node, char * table) {return importtablealias(node, table, 0, 0);}
inline double exporttable(treenode node, char * table, int usetopgrey, int useleftgrey) {return exporttablealias(node, table, usetopgrey, useleftgrey);}
inline double exporttable(treenode node, char * table) {return exporttablealias(node, table, 0, 0);}

inline double clearglobaltable(string table){return clearglobaltable_alias1((char*)table.c_str());}
inline double clearglobaltable(treenode table){return clearglobaltable_alias2(table);}
inline double clearglobaltable(int table){return clearglobaltable_alias3(table);}

inline double sorttable(string table, int col){return sorttable_alias1((char*)table.c_str(), col);}
inline double sorttable(treenode table, int col){return sorttable_alias2(table, col);}
inline double sorttable(int table, int col)
{
	return sorttable_alias3(table, col);
}

inline int gettablecols(treenode table)
{
	return content(first(table));
}
inline int gettablecols(string table)
{
	return gettablecols(reftable(table));
}

inline int gettablecols(int table)
{
	return gettablecols(reftable(table));
}

inline double sendmessage(treenode node, treenode associated, double n1=0, double n2=0, double n3=0, double n4=0,
	double n5=0, double n6=0, double n7=0, double n8=0, double n9=0, double n10=0)
{
	return sendmessagealias(node, associated, n1, n2, n3, n4, n5, n6, n7, n8, n9, n10);
}


inline int makearray(int size){return size;}

inline double executestring(string str, treenode C = NULL, treenode I = NULL, void *DATA = NULL, char *MSG = 0, int nobuild = 0)
{
	return executestringalias((char*)str.c_str(), C, I, DATA, MSG, nobuild);
}
inline double executefsnode(treenode ATT, treenode C = NULL, treenode I = NULL, void *DATA = NULL, char *MSG = 0, int nobuild = 0)
{
	return executefsnodealias(ATT, C, I, DATA, MSG, nobuild);
}

inline int iskeydown(int key=0){return iskeydownalias(key);}

inline int windowstyle(treenode view, int style, int doexstyle = 0){return windowstylealias(view,style,doexstyle);}

inline double lognormal2(double locate, double scale, double shape, int stream=0){return lognormal2alias(locate, scale, shape, stream);}

inline treenode  createinstance(treenode CLASSNODE, treenode  CONTAINERNODE, int nocreatemessage=0)
	{return createinstancealias(CLASSNODE,CONTAINERNODE,nocreatemessage);}

inline size_t maintenance(int command, double state = 0, char *info = 0){return maintenancealias(command, state, info);}
inline int EX(char *T, char * M = 0, int showsystemconsole = 0){return EXalias(T,M,showsystemconsole);}
inline double destroyeventsofobject(treenode object, double simtime, int code = 0, char* data = NULL,  treenode involvedobject = NULL)
	{return destroyeventsofobjectalias2(object, simtime, code, data, involvedobject);}
inline double destroyeventsofobject(treenode object){return destroyeventsofobjectalias1(object);}
inline double destroyeventsofobject(treenode object, double simtime, int code, char* data,  treenode involvedobject, customeventfilter filter)
	{return destroyeventsofobjectalias3(object, simtime, code, data, involvedobject, filter);}

inline double createevent(treenode  client, double time, unsigned int code, void *data=0, treenode  involved=0)
	{return createeventalias1(client, time, code, data, involved);}
inline int removeeventsofobject(treenode object, double simtime = -1, int code =0, char* data =NULL,  treenode involvedobject = NULL)
	{return removeeventsofobjectalias(object, simtime, code, data, involvedobject);}
inline int restoreeventsofobject(treenode object, double delaytime, double simtime = -1, int code =0, char* data =NULL,  treenode involvedobject =NULL)
	{return restoreeventsofobjectalias(object, delaytime, simtime, code, data, involvedobject);}
inline double drawtext(treenode  windownode, char * text, double x, double y, double z, double sx=1, double sy=1, double sz=1, 
					   double rx=0, double ry=0, double rz=0, double red=0, double green=0, double blue=0, double alpha=1)
	{return drawtextalias(windownode, text, x, y, z, sx, sy, sz, rx, ry, rz, red, green, blue, alpha);}
inline double drawtext(treenode  windownode, string text, double x, double y, double z, double sx=1, double sy=1, double sz=1, 
					   double rx=0, double ry=0, double rz=0, double red=0, double green=0, double blue=0, double alpha=1)
	{return drawtextalias(windownode, (char*)text.c_str(), x, y, z, sx, sy, sz, rx, ry, rz, red, green, blue, alpha);}

inline void updatekinematics(treenode infonode, treenode object, double updatetime = -1.0)
	{return updatekinematicsalias(infonode, object, updatetime);}

inline treenode createcopy(treenode classobject, treenode instancecontainer, int samename = 0, int inobject=0, int cached=0, int replace=0)
	{return createcopyalias(classobject, instancecontainer, samename, inobject, cached, replace);}
inline double getkinematics(treenode infonode, unsigned short type, int index = -1, double updatetime = -1.0)
	{return getkinematicsalias(infonode, type, index, updatetime);}
inline double selectedobject(treenode target, int reset = 0){return selectedobjectalias(target, reset);}

inline double addkinematic(treenode infonode,double _x, double _y, double _z, 
		double maxspeed, double acc = 0, double dec = 0, 
		double  _startspeed = 0.0, double  _endspeed = 0.0, double  _starttime = -1.0, unsigned short type = KINEMATIC_TRAVEL)
	{return addkinematicalias(infonode, _x, _y, _z, maxspeed, acc, dec, _startspeed, _endspeed, _starttime, type);}

inline string stringreplace(string text, string searchstr, string repstr)
{
	for(int pos = text.find(searchstr,0); 
		pos >= 0; 
		pos = text.find(searchstr,0)
	)
		text = text.replace(pos, searchstr.size(), repstr);
	return text;
}
inline double drawcube(double LocX, double LocY, double LocZ, double SizeX, double SizeY, double SizeZ, 
				double RotX, double RotY, double RotZ, double Red, double Green, double Blue, 
				double Opacity, double ImageIndexObjectNum, double RepX, double RepY)
{
	return drawcubealias1(LocX, LocY, LocZ, SizeX, SizeY, SizeZ, RotX, RotY, RotZ, Red, Green, Blue, 
		Opacity, ImageIndexObjectNum, RepX, RepY);
}
inline double drawcylinder(double LocX, double LocY, double LocZ, double BaseRadius, 
					double TopRadius, double Height, double RotX, double RotY, 
					double RotZ, double Red, double Green, double Blue, 
					double Opacity, double ImageIndexObjectNum)
{
	return drawcylinderalias1(LocX, LocY, LocZ, BaseRadius, TopRadius, Height, RotX, RotY, RotZ, 
		Red, Green, Blue, Opacity, ImageIndexObjectNum);
}
inline double drawrectangle(double LocX, double LocY, double LocZ, double SizeX, double SizeY, 
					 double RotX, double RotY, double RotZ, double Red, double Green, double Blue, 
					 double Opacity, double ImageIndexObjectNum, double RepX, double RepY)
{
	return drawrectanglealias1(LocX, LocY, LocZ, SizeX, SizeY, RotX, RotY, RotZ, 
		Red, Green, Blue, Opacity, ImageIndexObjectNum, RepX, RepY);
}

inline double drawcube(double LocX, double LocY, double LocZ, double SizeX, double SizeY, double SizeZ, 
				double RotX, double RotY, double RotZ, double Red, double Green, double Blue)
{
	return drawcubealias2(LocX, LocY, LocZ, SizeX, SizeY, SizeZ, RotX, RotY, RotZ, Red, Green, Blue);
}
inline double drawcylinder(double LocX, double LocY, double LocZ, double BaseRadius, double TopRadius, 
					double Height, double RotX, double RotY, double RotZ, double Red, double Green, double Blue)
{
	return drawcylinderalias2(LocX, LocY, LocZ, BaseRadius, TopRadius, Height, RotX, RotY, RotZ, 
		Red, Green, Blue);

}
inline double drawrectangle(double LocX, double LocY, double LocZ, double SizeX, double SizeY, 
					 double RotX, double RotY, double RotZ, double Red, double Green, double Blue)
{
	return drawrectanglealias2(LocX, LocY, LocZ, SizeX, SizeY, RotX, RotY, RotZ, 
		Red, Green, Blue);
}
inline double stoptime(double n1, double n2 = -1)
{
	return stoptimealias(n1, n2);
}
inline double resetmodel(int mode = 0){return resetmodelalias(mode);}
inline string documentsdir(){return documentsdir_cstr();}

inline double excelopen(string a){return excelopenalias((char*)a.c_str());}
inline double excelsetsheet(string a){return excelsetsheetalias((char*)a.c_str());}
inline double excelimportnode(treenode table,int startrow, int startcol, int numrows, int numcols)
{
	return excelimportnodealias1(table, startrow, startcol, numrows, numcols);
}
inline double excelimportnode(treenode table,int startrow, int startcol, int numrows, int numcols, char rowchar, char colchar)
{
	return excelimportnodealias2(table, startrow, startcol, numrows, numcols, rowchar, colchar);
}
inline int fileexists(string a){return fileexistsalias((char*)a.c_str());}


inline double normal( double mean,   double stddev  , int stream=0){return normalalias(mean, stddev, stream);}

inline double lognormal( double locate, double scale, double shape, int stream=0){return lognormalalias(locate, scale, shape, stream);}

inline double uniform( double a,      double b , int stream=0){return uniformalias(a, b, stream);}

inline double exponential( double locate, double scale , int stream=0){return exponentialalias(locate, scale, stream);}

inline double weibull( double locate, double scale, double shape, int stream=0){return weibullalias(locate, scale, shape, stream);}

inline double beta( double a,      double b,     double shape1,    double shape2 , int stream=0){return betaalias(a, b, shape1, shape2, stream);}

inline double erlang( double locate, double scale, double shape, int stream=0){return erlangalias(locate, scale, shape, stream);}

inline double gamma( double locate, double scale, double shape, int stream=0){return gammaalias(locate, scale, shape, stream);}

inline double pearsont5( double locate, double scale, double shape, int stream=0){return pearsont5alias(locate, scale, shape, stream);}

inline double pearsont6( double locate, double scale, double shape1, double shape2, int stream=0){return pearsont6alias(locate, scale, shape1, shape2, stream);}

inline double triangular( double min,    double max,   double mode, int stream=0){return triangularalias(min, max, mode, stream);}

inline double inversegaussian( double locate, double scale, double shape , int stream=0){return inversegaussianalias(locate, scale, shape, stream);}

inline double johnsonbounded( double a,      double b,     double shape1,  double shape2 , int stream=0){return johnsonboundedalias(a, b, shape1, shape2, stream);}

inline double johnsonunbounded( double locate, double scale, double shape1, double shape2, int stream=0){return johnsonunboundedalias(locate, scale, shape1, shape2, stream);}

inline double bernoulli(double prob, double a, double b, int stream=0){return bernoullialias(prob, a, b, stream);}

inline double geometric( double p, int stream=0){return geometricalias(p, stream);}

inline double negbinomial( int    s,      double p  , int stream=0){return negbinomialalias(s, p, stream);}

inline double binomial( int    t,      double p, int stream=0){return binomialalias(t, p, stream);}

inline double poisson( double mean, int stream=0){return poissonalias(mean, stream);}

inline double duniform( int    i,      int    j, int stream=0){return duniformalias(i, j, stream);}

inline double invertedweibull( double locate, double scale, double shape, int stream=0){return invertedweibullalias(locate, scale, shape, stream);}

inline double logistic( double locate, double scale, int stream=0){return logisticalias(locate, scale, stream);}

inline double loglogistic( double locate, double scale, double shape, int stream=0){return loglogisticalias(locate, scale, shape, stream);}

inline double loglaplace( double locate, double scale, double shape, int stream=0){return loglaplacealias(locate, scale, shape, stream);}

inline double randomwalk( double locate, double scale, double shape, int stream=0){return randomwalkalias(locate, scale, shape, stream);}

inline double empirical( char *tablename, int stream=0){return empiricalalias(tablename, stream);}

inline double cempirical( char *tablename, int stream=0){return cempiricalalias(tablename, stream);}

inline double dempirical( char *tablename, int stream=0){return dempiricalalias(tablename, stream);}

inline double applicationcommand(char* commandname, n10argsdefaultinterface){return applicationcommandalias(commandname, n10args);}

inline double webcommand(char* commandname, n10argsdefaultinterface){return webcommandalias(commandname, n10args);}

inline int showhtmlhelp(string path){return showhtmlhelpalias((char*)path.c_str());}

inline void addtoeventtypelegend(int index, int parameter, int value, char* legendname){addtoeventtypelegendalias1(index,parameter,value,legendname);}

inline void addtoeventtypelegend(char* name, int parameter, int value, char* legendname){addtoeventtypelegendalias2(name,parameter,value,legendname);}

inline void logevent(int _eventcode, treenode object = NULL, treenode involved = NULL, double p1 = 0, double p2 = 0, double p3 = 0, double p4 = 0){logeventalias1(_eventcode,object,involved,p1,p2,p3,p4);}

inline void logevent(char * name, treenode object = NULL, treenode involved = NULL, double p1 = 0, double p2 = 0, double p3 = 0, double p4 = 0){logeventalias2(name,object,involved,p1,p2,p3,p4);}

inline double fileopen(char * filename, char * mode = NULL){return fileopenalias(filename, mode);}
inline double setviewtext(treenode target, string text){return setviewtextalias(target, (char*) text.c_str());}
inline double addviewtext(treenode target, string text){return addviewtextalias(target, (char*) text.c_str());}
inline int dbsqlquery(string query, int flags = 0){return dbsqlqueryalias((char*)query.c_str(), flags);}
inline int dbopen(string dbname, string command, int tablemode, int loginprompt = 0){return dbopenalias((char*)dbname.c_str(), (char*)command.c_str(), tablemode, loginprompt);}
inline int dbusername(string username, string password){return dbusernamealias((char*)username.c_str(),(char*)password.c_str());}

inline void startanimation(treenode theobject, int animnr, int durationtype = 0, double duration = 0, int repeattype = 0, double repeatvalue = 0)
	{return startanimationalias1(theobject, animnr, durationtype, duration, repeattype, repeatvalue);}
inline void startanimation(treenode theobject, char* animname, int durationtype = 0, double duration = 0, int repeattype = 0, double repeatvalue = 0)
	{return startanimationalias2(theobject, animname, durationtype, duration, repeattype, repeatvalue);}
inline void stopanimation(treenode theobject, int animnr)
	{return stopanimationalias1(theobject, animnr);}
inline void stopanimation(treenode theobject, char* animname)
	{return stopanimationalias2(theobject, animname);}
inline void resumeanimation(treenode theobject, int animnr, int resumeAtType = 0, double resumeAtVal = 0)
	{return resumeanimationalias1(theobject, animnr, resumeAtType, resumeAtVal);}
inline void resumeanimation(treenode theobject, char* animname, int resumeAtType = 0, double resumeAtVal = 0)
	{return resumeanimationalias2(theobject, animname, resumeAtType, resumeAtVal);}


inline int setpickingdrawfocus(treenode theview, treenode focus, int selectiontype, treenode secondaryfocus = NULL, int detectdrag = 0)
	{return setpickingdrawfocusalias(theview, focus, selectiontype, secondaryfocus, detectdrag);}
inline double draginfo(int op, double val = 0){return draginfoalias(op, val);}

inline char* stringtoken(char* token, char* delimit){return stringtokenalias(token, delimit);}
inline char* stringtoken(char* token, string delimit){return stringtokenalias(token, (char*)delimit.c_str());}
inline char* stringtoken(string token, string delimit){return stringtokenalias((char*)token.c_str(), (char*)delimit.c_str());}
#if _MSC_VER < 1800
inline double round(double n1){return roundalias1(n1);}
#endif
inline double round(double n1, int precision){return roundalias2(n1, precision);}

inline double clientconnect(int skt, string hostname, int port){return clientconnectalias(skt, (char*)hostname.c_str(), port);}
inline double clientconnect(int skt, char* hostname, int port){return clientconnectalias(skt, hostname, port);}
inline double clientreceive(int skt, char *Buf, int BufSize, int NoBlock){return clientreceivealias(skt, Buf, BufSize, NoBlock);}
inline string clientreceive(int skt, int BufSize, int NoBlock)
{
	int mybufsize = BufSize;
	if(mybufsize <= 0) mybufsize = 10000;
	char* mybuf = (char*)malloc(mybufsize + 1);
	mybuf[0] = 0;
	clientreceivealias(skt, mybuf, mybufsize + 1, NoBlock);
	string mystr(mybuf);
	free(mybuf);
	return mystr;
}
inline double clientsend(int skt, char *Msg, int len = 0){return clientsendalias(skt, Msg, len<=0?strlen(Msg):len);}
inline double clientsend(int skt, string Msg){return clientsendalias(skt, (char*)Msg.c_str(), Msg.length()+1);}


inline double serverreceive(int skt, char *Buf, int BufSize, int NoBlock){return serverreceivealias(skt, Buf, BufSize, NoBlock);}
inline string serverreceive(int skt, int BufSize, int NoBlock)
{
	int mybufsize = BufSize;
	if(mybufsize <= 0) mybufsize = 10000;
	char* mybuf = (char*)malloc(mybufsize + 1);
	mybuf[0] = 0;
	serverreceivealias(skt, mybuf, mybufsize + 1, NoBlock);
	string mystr(mybuf);
	free(mybuf);
	return mystr;
}
inline double serversend(int skt, char *Msg, int len = 0){return serversendalias(skt, Msg, len<=0?strlen(Msg):len);}
inline double serversend(int skt, string Msg){return serversendalias(skt, (char*)Msg.c_str(), Msg.length()+1);}

inline double drawsphere(double x, double y, double z, double radius, double red, double green, double blue, double opacity=1, int textureindex=1)
	{return drawspherealias(x,y,z,radius,red,green,blue,opacity,textureindex);}
inline double excellaunch(char* path){return excellaunchalias1(path);}
inline double excellaunch(){return excellaunchalias2();}
inline int stringsearch(char* str, char* substr, int startpos){return stringsearchalias1(str, substr, startpos);}
inline int stringsearch(char* str, char* substr, int startpos, int flags){return stringsearchalias2(str, substr, startpos, flags);}
inline int stringsearch(string& str, string& substr, int startpos){return stringsearchalias1((char*)str.c_str(), (char*)substr.c_str(), startpos);}
inline int stringsearch(string& str, string& substr, int startpos, int flags){return stringsearchalias2((char*)str.c_str(), (char*)substr.c_str(), startpos, flags);}
inline double runspeed(double n1, double n2 = 0){return runspeedalias(n1,n2);}
inline int fabs(int val){return (int)fabs((double)val);}
inline int isclasstype(treenode obj, int classtype){return isclasstypealias1(obj, classtype);}
inline int isclasstype(treenode obj, char* classtype){return isclasstypealias2(obj, classtype);}
inline int setstate(treenode obj, int statenr){return setstatealias1(obj, statenr);}
inline int setstate(treenode obj, int statenr, int profilenr){return setstatealias2(obj, statenr, profilenr);}
inline int setstate(treenode obj, int statenr, const char* profilename){return setstatealias3(obj, statenr, profilename);}
inline int setstate(treenode obj, int statenr, treenode profile){return setstatealias4(obj, statenr, profile);}

inline int clearbundle(treenode x, int resetflags = 0){return clearbundlealias(x, resetflags);}
inline int addbundlefield(treenode x, char* fieldname, int type, int maxstrsize = 0){return addbundlefieldalias(x, fieldname, type, maxstrsize);}
inline int addbundleentry(treenode x){return addbundleentryalias1(x);}
inline int addbundleentry(treenode x, double n1, double n2=0, double n3=0, double n4=0, 
	double n5=0, double n6=0, double n7=0, double n8=0, double n9=0, double n10=0 )
	{return addbundleentryalias2(x, n10args);}
inline int addbundleentry(treenode x,
	double n1   , double  n2  , double  n3  , double  n4  , double  n5  , double  n6  , double  n7  , double  n8  , double  n9  , double n10  ,
	double n11  , double n12=0, double n13=0, double n14=0, double n15=0, double n16=0, double n17=0, double n18=0, double n19=0, double n20=0,
	double n21=0, double n22=0, double n23=0, double n24=0, double n25=0, double n26=0, double n27=0, double n28=0, double n29=0, double n30=0)
	{return addbundleentryalias3(x, n30args);}
inline int setbundlevalue(treenode x, int entrynr, char* fieldname, double val){return setbundlevaluealias1(x, entrynr, fieldname, val);}
inline int setbundlevalue(treenode x, int entrynr, int fieldnr, double val){return setbundlevaluealias2(x, entrynr, fieldnr, val);}
inline int setbundlevalue(treenode x, int entrynr, char* fieldname, char* val){return setbundlevaluealias3(x, entrynr, fieldname, val);}
inline int setbundlevalue(treenode x, int entrynr, int fieldnr, char* val){return setbundlevaluealias4(x, entrynr, fieldnr, val);}

inline double getbundlevalue(treenode x, int entrynr, char* fieldname){return getbundlevaluealias1(x, entrynr, fieldname);}
inline double getbundlevalue(treenode x, int entrynr, int fieldnr){return getbundlevaluealias2(x, entrynr, fieldnr);}

inline double updatestate(treenode obj, int profilenr){return updatestate_alias2(obj, profilenr);}
inline double updatestate(treenode obj){return updatestate_alias1(obj);}
inline double getstatenum(treenode obj, int profilenr){return getstatenum_alias2(obj, profilenr);}
inline double getstatenum(treenode obj){return getstatenum_alias1(obj);}

inline void updateanimation(treenode object){updateanimationalias1(object);}
inline void updateanimation(treenode object, double updatetime, int animnr = 0){updateanimationalias2(object, updatetime, animnr);}

inline double function_s(treenode node, char * name, n30argsdefaultinterface){return function_s_alias(node, name, n30args);}

inline treenode assertattribute(treenode object,char *name, int datatype){return assertattributealias(object, name, datatype);}
inline treenode assertvariable(treenode object,char *name, int datatype = 0){return assertvariablealias(object, name, datatype);}
inline treenode assertlabel(treenode object,char *name, int datatype = 0){return assertlabelalias(object, name, datatype);}
inline treenode assertsubnode(treenode node,char *name, int datatype = 0){return assertsubnodealias(node, name, datatype);}
inline double exportdataset(treenode p1, char * table, int format, char* wrOption = "w"){return exportdatasetalias(p1, table, format, wrOption);}
inline int aggregateundorecords(TreeNode* view, char* description, int id1, int id2, int id3 = 0, int id4 = 0, int id5 = 0, int id6 = 0, int id7 = 0, int id8 = 0);

inline double colorarray(treenode involved, double val){return colorarrayalias1(involved, val);}
inline void  colorarray(int val, double * destcolor){colorarrayalias2(val, destcolor);}

inline void fglColor(float r, float g, float b, float a = 1.0f) {fglColorAlias(r, g, b, a);}
// lambda's are only compatible with visual studio 2010+
#if _MSC_VER >= 1600
extern QueryCallback defQueryCallback;
inline int cpp_query(const char* queryStr, QueryCallback& p1 = defQueryCallback,  QueryCallback& p2 = defQueryCallback, QueryCallback& p3 = defQueryCallback,  QueryCallback& p4 = defQueryCallback,
									QueryCallback& p5 = defQueryCallback,  QueryCallback& p6 = defQueryCallback, QueryCallback& p7 = defQueryCallback,  QueryCallback& p8 = defQueryCallback, QueryCallback& p9 = defQueryCallback)
{
		return cpp_queryalias(queryStr, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}
inline FlexSimValue $iter(int index) {return $iteralias(index);}
#endif
inline FlexSimValue getqueryvalue(int row, int col) {return getqueryvaluealias1(row, col);}
inline FlexSimValue getqueryvalue(int row, const char* colName) {return getqueryvaluealias2(row, colName);}
inline FlexSimValue getqueryvalue(int row, const std::string& colName) {return getqueryvaluealias2(row, colName.c_str());}

#if defined COMPILING_FLEXSIM_CONTENT || defined COMPILING_MODULE_DLL
	inline treenode createevent(FlexSimEvent* e){return createeventalias2(e);}
#else
	inline double   transportincomplete (treenode object, treenode item, int portnumber = 0, treenode transporter = NULL){return transportincompletealias (object,item,portnumber,transporter);}
	inline double   transportoutcomplete(treenode object, treenode item, int portnumber = 0, treenode transporter = NULL){return transportoutcompletealias(object,item,portnumber,transporter);}
	inline double   receiveitem(treenode station, int port){return receiveitem_alias2(station,port);}
	inline double   receiveitem(treenode station){return receiveitem_alias1(station);}
	inline double   releaseitem(treenode station, int port){return releaseitem_alias2(station,port);}
	inline double   releaseitem(treenode station){return releaseitem_alias1(station);}
	inline double   gettreedrawposition(treenode object, treenode roottree, int* cury = NULL, int increment = 0){return gettreedrawpositionalias(object,roottree,cury,increment);}
	inline double   applicationcommand(string commandname, n10argsdefaultinterface){return applicationcommandalias((char*)(commandname.c_str()), n10args);}
	inline double   validatename(treenode current, int isview = 0, treenode obj = NULL){return validatenamealias(current,isview,obj);}
	inline int      insertdeallocatetask(treenode tasksequence, int executerkey, int noblock = 0){return insertdeallocatetaskalias(tasksequence,executerkey,noblock);}
	inline treenode inserttask(treenode tasksequence,  unsigned int  type, treenode involved1, treenode involved2 , double var1 , double var2 , double var3 , double var4){return inserttaskalias(tasksequence,type,involved1,involved2,var1,var2,var3,var4);}
	inline int      contentunder(treenode object, int objectsonly = 0){return contentunderalias(object,objectsonly);}
	inline double   profileevents(int removedevents = 0){return profileeventsalias(removedevents);}
	inline double   dispatchcoordinatedtasksequence(treenode tasksequence, treenode dispatcher = NULL){return dispatchcoordinatedtasksequencealias(tasksequence, dispatcher);}
	inline double   dispatchtasksequence(treenode tasksequence, treenode dispatcher = NULL){return dispatchtasksequencealias(tasksequence, dispatcher);}
#endif

// lambdas only work on visual studio 2010 or later
#if _MSC_VER >= 1600
	template<class NumGetter>
	double cpp_getdatastat(int stat, int nr, NumGetter getter, double p1, double p2, double p3)
	{
		static double * buffer = 0;
		static int bufferSize = 0;
		if (!buffer || bufferSize < nr) {
			if (buffer)
				delete [] buffer;
			bufferSize = nr * 2;
			buffer = new double[bufferSize];
		}
		for (int i = 0; i < nr; i++)
			buffer[i] = getter(i + 1);
		return getdatastat_alias2(
			stat, 
			nr, 
			buffer, 
			p1, 
			p2, 
			p3);
	}

	#define getdatastat(stat, nr, func, p1, p2, p3) \
			(objectexists((treenode)(size_t)nr) \
				? getdatastat_alias1(stat, (treenode)(size_t)nr, (treenode)(size_t)func, p1, p2, p3) \
				: cpp_getdatastat(stat, (int)(size_t)nr, [&](int count) -> double {return (double)func;}, p1, p2, p3))
#else
	inline double getdatastat(int stat, treenode dataset, treenode unused, double p1, double p2, double p3){return getdatastat_alias1(stat, dataset, unused, p1, p2, p3);}
#endif


engine_export Variant getlabel(treenode object, const char* labelName);
inline Variant getlabel(treenode object, const string& labelName) { return getlabel(object, labelName.c_str()); }
engine_export Variant getlabel(treenode object, int labelRank);
engine_export Variant getlabel(treenode object, Variant labelName);

engine_export void setlabel(treenode object, const char* labelName, Variant toVal);
inline void setlabel(treenode object, const string& labelName, Variant toVal) {return setlabel(object, labelName.c_str(), toVal);}
engine_export void setlabel(treenode object, int labelRank, Variant toVal);
engine_export void setlabel(treenode object, Variant labelName, Variant toVal);







#endif