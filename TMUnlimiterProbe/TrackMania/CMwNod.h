#pragma once

namespace TrackMania
{

	class CMwNod
	{
	public:
		virtual void	m0							() = 0;
		virtual			~CMwNod						() = 0;
		virtual void*	GetClassInfo				() = 0;
		virtual dword	GetClassID					() = 0;
		virtual bool	Is							( dword dwClassID ) = 0;
		virtual void*	GetMeta						() = 0;
		virtual void	SetUID						( void* pUID ) = 0;
		virtual void	m1C							() = 0;
		virtual void	m20							() = 0;
		virtual void	CustomGetFieldByID			( void* pMwStack, void** ppField ) = 0;
		virtual void	CustomCallMethod			( void* pMwStack, void** ppResult ) = 0;
		virtual void	m2C							() = 0;
		virtual void	m30							() = 0;
		virtual void	ReadWriteChunks				( void* pClassicArchive ) = 0;
		virtual void	ReadWriteChunk				( void* pClassicArchive, dword dwClassID ) = 0;
		virtual dword	GetClassIDLoadFlags			( dword dwClassID ) = 0;
		virtual void	m40							() = 0;
		virtual void	m44							() = 0;
		virtual void	FinishReadChildren			() = 0;
		virtual void	m4C							() = 0;
		virtual void	m50							() = 0;
		virtual void	m54							() = 0;
		virtual void	m58							() = 0;
		virtual void	m5C							() = 0;
		virtual void	m60							() = 0;
		virtual void	m64							() = 0;
		virtual void	m68							() = 0;
		virtual void	m6C							() = 0;
		virtual void	m70							() = 0;
		virtual void	m74							() = 0;
		virtual void	Evaluate					() = 0;
		virtual void	m7C							() = 0;
		virtual void	m80							() = 0;
		virtual void	SetParent					( CMwNod* pParent ) = 0;
		virtual void	m88							() = 0;
		virtual void	m8C							() = 0;
		virtual void	m90							() = 0;
		virtual void	m94							() = 0;
		virtual void	m98							() = 0;
		virtual void	m9C							() = 0;
		virtual void	mA0							() = 0;
		virtual void	mA4							() = 0;
		virtual void	mA8							() = 0;
		virtual void	ToString					( StringA* pStr ) = 0;

	private:
		dword			m_dwRefCount;
		void*			m_pSystemFid;
		void*			m_pChildNodesList;
		dword			m_field10;
	};

}
