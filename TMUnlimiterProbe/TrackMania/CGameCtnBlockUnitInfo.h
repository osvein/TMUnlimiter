#pragma once

namespace TrackMania
{

	class CGameCtnBlockInfo;

	class CGameCtnBlockUnitInfo : public CMwNod
	{
	public:

	private:
		dword							m_field14;
		dword							m_field18;
		dword							m_field1C;
		Array<CGameCtnBlockInfo*>		m_BlockInfoClips;
		Vec3Di							m_Offset;
		dword							m_SK1;
		dword							m_field38;
		dword							m_field3C;
		dword							m_field40;
		dword							m_SK2;
		dword							m_field48;
		dword							m_field4C;
		dword							m_SK3;
	};

}
