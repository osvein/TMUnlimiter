#pragma once

namespace TrackMania
{

    class CGameCtnChapter : public CMwNod
    {
    public:
        const char*                     GetName                 () const    { return m_skName.Resolve (); }
        dword                           GetNameKey              () const    { return m_skName.GetKey (); }

        List<CGameCtnArticle*>&         GetArticles             ()          { return m_Articles; }
        CGameCtnArticle*                GetArticleByMeta        ( const NodeMeta* pMeta );

        CSystemFidFile*                 GetCollectionFid        () const    { return m_pCollectionFid; }
        CGameCtnCollection*             GetCollection           () const;
        CGameCtnCollection*             LoadCollection          ();

    private:
        List<CGameCtnArticle*>          m_Articles;
        CSystemFidFile*                 m_pCollectionFid;
        StringA                         m_strDesc;
        StringW                         m_wstrLongDesc;
        dword                           m_dwUnlocked;
        byte                            pad0[0x74];
        StringKey                       m_skName;
    };

}
