#pragma once

#include <Windows.h>
#include <assert.h>
#include <regex>
#include <string>
#include <vector>

typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;

typedef BYTE  byte;
typedef WORD  word;
typedef DWORD dword;

#include "PatternFinder.h"
#include "Address.h"

#include "TrackMania/Allocatable.h"
#include "TrackMania/Color.h"
#include "TrackMania/Array.h"
#include "TrackMania/List.h"
#include "TrackMania/Iso4.h"
#include "TrackMania/Vec2D.h"
#include "TrackMania/Vec3D.h"
#include "TrackMania/Vec3Di.h"
#include "TrackMania/StringA.h"
#include "TrackMania/StringW.h"
#include "TrackMania/StringKey.h"

#include "TrackMania/CMwNod.h"
#include "TrackMania/NodeMeta.h"
#include "TrackMania/SParam.h"
#include "TrackMania/SParam_Id.h"
#include "TrackMania/SParam_Fid_Common.h"
#include "TrackMania/SParam_Fid.h"
#include "TrackMania/SParam_Fids.h"
#include "TrackMania/CSystemFidParameters.h"
#include "TrackMania/CSystemFid.h"
#include "TrackMania/CSystemFids.h"
#include "TrackMania/CSystemFidFile.h"
#include "TrackMania/CSystemFidsFolder.h"
#include "TrackMania/CGameCtnCollector.h"
#include "TrackMania/CGameCtnCollectorList.h"
#include "TrackMania/CGameCtnFieldUnit.h"
#include "TrackMania/CGameCtnBlockUnitInfo.h"
#include "TrackMania/CGameCtnBlockUnit.h"
#include "TrackMania/CGameCtnBlockInfo.h"
#include "TrackMania/CGameCtnBlock.h"
#include "TrackMania/CGameCtnDecorationSize.h"
#include "TrackMania/CGameCtnDecoration.h"
#include "TrackMania/CGameCtnZone.h"
#include "TrackMania/CGameCtnZoneFlat.h"
#include "TrackMania/CGameCtnZoneFrontier.h"
#include "TrackMania/CGameCtnCollection.h"
#include "TrackMania/CGameCtnPylonColumn.h"
#include "TrackMania/CGameCtnChallenge.h"
#include "TrackMania/CGameCtnCursor.h"
#include "TrackMania/CGameCtnArticle.h"
#include "TrackMania/CGameCtnChapter.h"
#include "TrackMania/CGameCtnCatalog.h"
#include "TrackMania/CGameCtnEditor.h"
#include "TrackMania/CTrackManiaEditorIcon.h"
#include "TrackMania/CTrackManiaEditorIconPage.h"
#include "TrackMania/CTrackManiaEditorInterface.h"
#include "TrackMania/CTrackManiaEditor.h"

#include "Settings.h"
#include "Hooks/HooksBase.h"
#include "Hooks/Editor/BlockMixHooks.h"
#include "Hooks/Editor/EnvironmentMixHooks.h"
