#ifndef HASHTABLE_H
#define HASHTABLE_H

template< class elementtype>
class HashTable
{
private:
		int listsize;
		int mask;
		struct hashentry{
			char * key;
			elementtype * value;
		};
		struct listhead
		{
			int size;
			int maxsize;
			hashentry values[1];	
		};
		listhead ** list;

		void initialize()
		{
			list = (listhead**) malloc(listsize * sizeof(listhead*));
			for(int i = 0; i < listsize; i++)
			{
				list[i] = (listhead*)malloc(sizeof(listhead)+7*sizeof(hashentry));
				list[i]->size = 0;
				list[i]->maxsize = 8;
			}
			mask = 1;
			while(mask < listsize)
			{
				mask <<= 1;
				mask |= 1;
			}
			mask>>=1;
		}

		inline int hash(const char* key)
		{
			unsigned int _Val = 2166136261U;
			while(*key)
				_Val = 16777619U * _Val ^ (unsigned int)*key++;
			return _Val & mask;
			/*
			try{
				int index = 0;
				for(int i = 0; key[i] != 0; i++)
					index += key[i]*(i+1);
				return index & mask;
			}
			catch(...)
			{
				//string errormsg = "Exception caught in HashTable::hash(";
				//errormsg.append(key);
				//errormsg.append(") Continuing throw...");
				//EX((char*)errormsg.c_str(),"");
				throw;
			}
			*/
		}

public:

		HashTable(int size)
		{
			listsize = size;
			initialize();
		}
		HashTable()
		{
			listsize = 2048;
			initialize();
		}
		~HashTable()
		{
			for(int i = 0; i < listsize; i++)
			{
				listhead* curhead = list[i];
				for(int j = 0; j < curhead->size; j++)
				{
					hashentry * entry = &(curhead->values[j]);
					delete [] entry->key;
					delete entry->value;
				}
				free(list[i]);
			}
			free(list);
		}

		int clear()
		{
			try{
				for(int i = 0; i < listsize; i++)
				{
					listhead* curhead = list[i];
					for(int j = 0; j < curhead->size; j++)
					{
						hashentry * entry = &(curhead->values[j]);
						delete [] entry->key;
						delete entry->value;
					}
					list[i]->size = 0;
				}
				return 0;
			}
			catch(...)
			{
				//EX("Exception caught int HashTable::clear(). Continuing throw...","");
				throw;
			}
		}

		elementtype& operator[](const char * key)
		{
			try{
				int index = hash(key);
				listhead* head = list[index];
				for(int i = 0; i < head->size; i++)
				{
					char* cmpstr = head->values[i].key;
					if(strcmp(cmpstr,key)==0)
						return *head->values[i].value;
				}
				return add(key);
			}
			catch(...)
			{
				//string errormsg = "Exception caught in HashTable::operator[](";
				//errormsg.append(key);
				//errormsg.append(") Continuing throw...");
				//EX((char*)errormsg.c_str(),"");
				throw;
			}
		}

		elementtype& add(const char * key)
		{
			try{
				int index = hash(key);
				listhead* head = list[index];
				if(head->size >= head->maxsize)
				{
					head->maxsize *= 2;
					list[index] = (listhead*)realloc(list[index], sizeof(listhead)+(head->maxsize-1)*sizeof(hashentry));
					head = list[index];
				}
				head->values[head->size].key = new char[strlen(key) + 4];
				strcpy(head->values[head->size].key, key);
				head->values[head->size].value = new elementtype;
				return *head->values[head->size++].value;
			}
			catch(...)
			{
				//string errormsg = "Exception caught in HashTable::add(";
				//errormsg.append(key);
				//errormsg.append(") Continuing throw...");
				//EX((char*)errormsg.c_str(),"");
				throw;
			}
		}

		int ismember(const char * key, elementtype** returnval)
		{
			try{
				int index = hash(key);
				listhead* head = list[index];
				for(int i = 0; i < head->size; i++)
				{
					if(strcmp(head->values[i].key,key)==0)
					{
						*returnval = head->values[i].value;
						return 1;
					}
				}
				return 0;
			}
			catch(...)
			{
				//string errormsg = "Exception caught in HashTable::ismember(";
				//errormsg.append(key);
				//errormsg.append(") Continuing throw...");
				//EX((char*)errormsg.c_str(),"");
				throw;
			}
		}

		inline int ismember(const char * key)
		{
			elementtype* temp;
			return ismember(key, &temp);
		}

		inline int remove(const char * key)
		{
			int index = hash(key);
			listhead* head = list[index];
			for(int i = 0; i < head->size; i++)
			{
				if(strcmp(head->values[i].key,key)==0)
				{
					delete [] head->values[i].key;
					delete head->values[i].value;
					head->values[i] = head->values[head->size - 1];
					head->size--;
					return 1;
				}
			}
			return 0;
		}

		inline int gettablesize()
		{
			return listsize;
		}
};

// chashtablefixedkeysize is like a HashTable, but faster because it doesn't do class constructors
// and therefore uses no new/delete's. You can only use it for storing structs and primitive types
// (or classes that don't use a constructor or virtual methods), and the 
// key must be a fixed size. This would be used for creating a hash table where the key is 
// actually binary data
template< class elementtype, int keysize>
class chashtablefixedkeysize
{
private:
		int listsize;
		int mask;
		struct hashentry{
			char key[keysize];
			elementtype value;
		};
		struct listhead
		{
			int size;
			int maxsize;
			hashentry values[1];	
		};
		listhead ** list;

		void initialize()
		{
			list = (listhead**) malloc(listsize * sizeof(listhead*));
			
			for(int i = 0; i < listsize; i++)
				list[i] = NULL;
			mask = 1;
			while(mask < listsize)
			{
				mask <<= 1;
				mask |= 1;
			}
			mask>>=1;
		}

		inline int hash(const void* key) const
		{
			try{
				int index = 0;
				unsigned char* keystr = (unsigned char*)key;
				for(int i = 0; i < keysize; i++)
					index += keystr[i]*(i+1);
				return index & mask;
			}
			catch(...)
			{
				throw;
			}
		}

public:

		chashtablefixedkeysize(const int size)
		{
			listsize = size;
			initialize();
		}
		chashtablefixedkeysize()
		{
			listsize = 2048;
			initialize();
		}
		~chashtablefixedkeysize()
		{
			for(int i = 0; i < listsize; i++)
			{
				listhead* curhead = list[i];
				if(curhead)
					free(curhead);
			}
			free(list);
		}

		int clear()
		{
			try{
				for(int i = 0; i < listsize; i++)
					if(list[i])
						list[i]->size = 0;
				return 0;
			}
			catch(...)
			{
				throw;
			}
		}

		elementtype& operator[](const void * key)
		{
			try{
				int index = hash(key);
				listhead* head = list[index];
				if(head == NULL)
				{
					list[index] = (listhead*)malloc(sizeof(listhead)+8*sizeof(hashentry));
					list[index]->size = 0;
					list[index]->maxsize = 8;
					head = list[index];
				}
				for(int i = 0; i < head->size; i++)
				{
					char* cmpstr = head->values[i].key;
					if(memcmp(key, head->values[i].key, keysize) == 0)
						return head->values[i].value;
				}
				return add(key);
			}
			catch(...)
			{
				throw;
			}
		}

		elementtype& add(const void * key)
		{
			try{
				int index = hash(key);
				listhead* head = list[index];
				if(head == NULL)
				{
					list[index] = (listhead*)malloc(sizeof(listhead)+8*sizeof(hashentry));
					list[index]->size = 0;
					list[index]->maxsize = 8;
					head = list[index];
				}
				if(head->size >= head->maxsize)
				{
					head->maxsize *= 2;
					list[index] = (listhead*)realloc(list[index], sizeof(listhead)+(head->maxsize-1)*sizeof(hashentry));
					head = list[index];
				}
				memcpy(head->values[head->size].key, key, keysize);
				return head->values[head->size++].value;
			}
			catch(...)
			{
				throw;
			}
		}

		int ismember(const void * key, elementtype** returnval) const
		{
			try{
				int index = hash(key);
				listhead* head = list[index];
				if(!head) 
					return 0;
				for(int i = 0; i < head->size; i++)
				{
					if(memcmp(head->values[i].key,key, keysize)==0)
					{
						*returnval = &(head->values[i].value);
						return 1;
					}
				}
				return 0;
			}
			catch(...)
			{
				throw;
			}
		}

		inline int ismember(const void * key) const
		{
			elementtype* temp;
			return ismember(key, &temp);
		}
};

#endif