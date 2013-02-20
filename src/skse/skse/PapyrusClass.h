#pragma once

// SkyrimScript::Store, derived from BSScript::IStore, derived from BSStorage, derived from BSIntrusiveRefCounted
class VMDataStore
{
public:
	virtual ~VMDataStore();
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual bool	Seek(SInt32 offset, UInt32 base);
	virtual bool	Read(UInt32 len, void * buf);
	virtual bool	Write(UInt32 len, void * buf);

	// BSScript::IStore
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);

//	void	** _vtbl;	// 00

};

// 
class VMClass
{
public:
};

// 20
class VMClassLoader
{
public:
	virtual ~VMClassLoader();
	virtual VMClassLoader *		Create(void);
	virtual void				SetDataStore(VMDataStore ** dataStoreHandle);	// probably a safe ptr
	virtual bool				Load(const char * name, void * out);

	// 10
	struct StringTable
	{
		UInt32	unk00;			// 00
		UInt32	unk04;			// 04
		UInt32	* data;			// 08
		UInt16	numStrings;		// 0C
		UInt8	pad0E[2];		// 0E
	};

//	void		** _vtbl;		// 00
	void		* unk04;		// 04
	VMDataStore	* dataStore;	// 08
	StringTable	stringTable;	// 0C
	UInt8		verMajor;		// 1C
	UInt8		verMinor;		// 1D
	UInt8		flags;			// 1E
	UInt8		pad1F;			// 1F
};
