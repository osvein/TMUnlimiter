#pragma once

namespace TrackMania
{

    class CSystemFidFile;

	class CMwNod : public Allocatable
	{
	public:
        dword           AddRef                      () { return ++m_dwRefCount; }
        void            Release                     ();

        virtual void	m0							() {}
        virtual			~CMwNod						() {}
        virtual void*	GetClassInfo				() { return NULL; }
        virtual dword	GetClassID					() { return 0; }
        virtual bool	Is							( dword dwClassID ) { return false; }
        virtual void*	GetMeta						() { return NULL; }
        virtual void	SetUID						( void* pUID ) {}
        virtual void	m1C							() {}
        virtual void	m20							() {}
        virtual void	CustomGetFieldByID			( void* pMwStack, void** ppField ) {}
        virtual void	CustomCallMethod			( void* pMwStack, void** ppResult ) {}
		virtual void	m2C							() {}
		virtual void	m30							() {}
		virtual void	ReadWriteChunks				( void* pClassicArchive ) {}
		virtual void	ReadWriteChunk				( void* pClassicArchive, dword dwClassID ) {}
		virtual dword	GetClassIDLoadFlags			( dword dwClassID ) { return 0; }
		virtual void	m40							() {}
		virtual void	m44							() {}
		virtual void	FinishReadChildren			() {}
		virtual void	m4C							() {}
		virtual void	m50							() {}
		virtual void	m54							() {}
		virtual void	m58							() {}
		virtual void	m5C							() {}
		virtual void	m60							() {}
		virtual void	m64							() {}
		virtual void	m68							() {}
		virtual void	m6C							() {}
		virtual void	m70							() {}
		virtual void	m74							() {}
		virtual void	Evaluate					() {}
		virtual void	m7C							() {}
		virtual void	m80							() {}
		virtual void	SetParent					( CMwNod* pParent ) {}
		virtual void	m88							() {}
		virtual void	m8C							() {}
		virtual void	m90							() {}
		virtual void	m94							() {}
		virtual void	m98							() {}
		virtual void	m9C							() {}
		virtual void	mA0							() {}
		virtual void	mA4							() {}
		virtual void	mA8							() {}
		virtual void	ToString					( StringA* pStr ) {}

	private:
		dword           m_dwRefCount;
		CSystemFidFile* m_pSystemFid;
		void*           m_pChildNodesList;
		dword           m_field10;
	};

}
