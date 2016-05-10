#pragma once

#include <Windows.h>
#include <assert.h>
#include <regex>
#include <string>

typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;

typedef BYTE  byte;
typedef WORD  word;
typedef DWORD dword;

#define INI_FILENAME "TMUnlimiter.ini"
#define INI_TRACKSIZES "NewTrackSizes"

#include "PatternFinder.h"
#include "Address.h"

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
#include "TrackMania/CGameCtnCollector.h"
#include "TrackMania/CGameCtnFieldUnit.h"
#include "TrackMania/CGameCtnBlockUnitInfo.h"
#include "TrackMania/CGameCtnBlockUnit.h"
#include "TrackMania/CGameCtnBlockInfo.h"
#include "TrackMania/CGameCtnBlock.h"
#include "TrackMania/CGameCtnDecorationSize.h"
#include "TrackMania/CGameCtnDecoration.h"
#include "TrackMania/CGameCtnZone.h"
#include "TrackMania/CGameCtnCollection.h"
#include "TrackMania/CGameCtnChallenge.h"
#include "TrackMania/CGameCtnCursor.h"
#include "TrackMania/CGameCtnEditor.h"
#include "TrackMania/CTrackManiaEditor.h"

#include "Settings.h"
#include "Hooks.h"
