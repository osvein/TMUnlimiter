#pragma once

namespace Hooks { namespace Editor {

    class EnvironmentMixHooks : public HooksBase
    {
    public:
                                    EnvironmentMixHooks                     () {}
        virtual                     ~EnvironmentMixHooks                    () {}

        virtual void                Init                                    ();

    private:
        static void                 hook_LoadCollectionAndDecoration        ();
        static void                 handle_LoadCollectionAndDecoration      ( TrackMania::CGameCtnChallenge* pChallenge );

        static void                 hook_CGameCtnArticle__ParsePagePath     ();
        static void                 handle_CGameCtnArticle__ParsePagePath   ( TrackMania::CGameCtnArticle* pArticle );

        static void                 hook_ReadWriteBlock                     ();
        static dword                handle_ReadWriteBlock                   ( TrackMania::CGameCtnBlock* pBlock, TrackMania::StringKey skChallengeEnvironment );

        static void                 hook_GetArticleByMeta                   ();
        static void                 hook_GetCollectorByMeta                 ();
        static TrackMania::CGameCtnCollection* handle_GetCollectorByMeta    ( TrackMania::CGameCtnCollection* pCollection, TrackMania::NodeMeta* pMeta );

        static void                 hook_ShouldSwitchToTerrainEditor        ();
        static bool                 handle_ShouldSwitchToTerrainEditor      ( TrackMania::CTrackManiaEditor* pEditor );

        static void                 hook_CleanupEditorInterface             ();
        static void                 handle_CleanupEditorInterface           ( TrackMania::CTrackManiaEditorInterface* pInterface );

        static void                 hook_SetEditor                          ();
        static void                 handle_SetEditor                        ( TrackMania::CTrackManiaEditor* pOldEditor, TrackMania::CTrackManiaEditor* pNewEditor );

        static void                 hook_InitEditorGUI                      ();
        static void                 handle_InitEditorGUI                    ( TrackMania::CTrackManiaEditorInterface* pEditorInterface, void* pGameInterface, TrackMania::CGameCtnCollection* pCollection, TrackMania::CGameCtnDecoration* pDecoration, TrackMania::CGameCtnCollectorList* pCollectorList );

        static void                 hook_GetZoneByBlockInfo                 ();

        static void                 hook_SetUpPylon                         ();
        static void                 handle_SetUpPylon                       ( TrackMania::CGameCtnPylonColumn* pPylon, int iBottomY, int iTopY );

        static float                ms_fPylonHeightRatio;
        static bool                 ms_bInEditor;
        static std::vector < int >  ms_SelectedIconPathBackup;
    };

} }
