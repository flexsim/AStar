

// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

# ifndef byteblock_cld
# define byteblock_cld
#include "basicclasses.h"
#include <string>

#ifdef FLEXSIM_ENGINE_COMPILE
	#include "msxml3.h"
#endif

#pragma pack(1) //I do my own memory alignment and padding
class ByteBlock
{ 
  //DATA MEMBERS ARE MANUALLY ALIGNED (NO PADDING)
public:
	char *block;                // (4 or 8 bytes)
private:
	long unsigned int blocksize;// (4 bytes)
	unsigned short parity;      // (2 bytes)
public:
	ByteBlock() : parity((unsigned short)(size_t)this), blocksize(1)
	{
		block = getStaticBlock();
	}
	// copy constructor
	ByteBlock(ByteBlock& other) : parity((unsigned short)(size_t)this), blocksize(0), block(0)
	{
		write(other.block, other.blocksize, 0);
	}
	#if _MSC_VER >= 1600
	// move constructor (only available with C++0x, i.e. VS 2010 +
	ByteBlock(ByteBlock&& other) : parity((unsigned short)(size_t)this), blocksize(other.blocksize), block(other.block)
	{
		other.block = 0;
		other.blocksize = 0;
	}
	#endif
	~ByteBlock()
	{
		parity = 0;
		if (block && block!=getStaticBlock()) 
			flexsimfree(block);
	}
	static char* getStaticBlock();
	void write(const char *source);
	void write(const char *source, long unsigned intsize, int nullterminate);
	bool setSize(long unsigned int);
	long unsigned int getSize();
	char *getBuffer();
	void append(const char *source);
	ByteBlock& operator =(const char * c)
		{ write(c); return *this; }
	ByteBlock& operator =(const std::string& c)
		{ write(c.c_str()); return *this; }
	ByteBlock& operator +=(const char * c)
		{ append(c); return *this; }
	ByteBlock& operator +=(const std::string& c)
		{ append(c.c_str()); return *this; }
	ByteBlock& operator=(const ByteBlock& copyfrom)
		{ write(copyfrom.block, copyfrom.blocksize, 0); return *this; }
	operator char*()
		{return getBuffer();}

	#ifdef FLEXSIM_ENGINE_COMPILE
		void* operator new(size_t size);
		void operator delete(void* p);
		inline bool checkParity(){return parity==(unsigned short)(size_t)this;}//true if valid
  
		void write(const char *source, long unsigned intsize);
		void writeFast(const char *source);
		int read(char *dest, long unsigned intsize);
		void append(const char *source, long unsigned intsize, int nullterminate);
  
  
		static char staticBlock[1];
  
		int nullTerminate();
 
		long unsigned int getSaveSize(long unsigned int * savesize);
		bool save(std::ostream& stream);
		bool load(std::istream& stream);
		int save(char* destination, long unsigned int * bytepos);
		int load(char* source     , long unsigned int * bytepos);
  

		int saveXML(MSXML2::IXMLDOMDocumentPtr doc, MSXML2::IXMLDOMElementPtr parentnode, bool isNameBB = false);
		int loadXML(MSXML2::IXMLDOMNodePtr parentnode);
  

		int replaceSubString(int preposition, int position, char *substitute);
		int searchSubString(char *pattern, char *substitute, int rep); // return 1 when not at end; set substringcursor when done

		int parserSearchSubString(char *pattern, char *substitute, int rep); // return 1 when not at end; set substringcursor when done
		int parserSearchSubStringNotWholeWord(char *pattern, char *substitute, int rep); // return 1 when not at end; set substringcursor when done
	#endif
};
#pragma pack()//restore packing to its default value

# endif
















// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.














