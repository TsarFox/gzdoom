/*
**  Renderer multithreading framework
**  Copyright (c) 2016 Magnus Norddahl
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
*/

#include <stdlib.h>
#include "templates.h"
#include "doomdef.h"
#include "m_bbox.h"
#include "i_system.h"
#include "p_lnspec.h"
#include "p_setup.h"
#include "a_sharedglobal.h"
#include "g_level.h"
#include "p_effect.h"
#include "doomstat.h"
#include "r_state.h"
#include "v_palette.h"
#include "r_sky.h"
#include "po_man.h"
#include "r_data/colormaps.h"
#include "r_renderthread.h"
#include "swrenderer/things/r_visiblespritelist.h"
#include "swrenderer/scene/r_portal.h"
#include "swrenderer/scene/r_opaque_pass.h"
#include "swrenderer/scene/r_translucent_pass.h"
#include "swrenderer/scene/r_3dfloors.h"
#include "swrenderer/scene/r_scene.h"
#include "swrenderer/things/r_playersprite.h"
#include "swrenderer/plane/r_visibleplanelist.h"
#include "swrenderer/segments/r_drawsegment.h"
#include "swrenderer/segments/r_clipsegment.h"
#include "r_memory.h"

namespace swrenderer
{
	RenderThread::RenderThread()
	{
		FrameMemory = std::make_unique<RenderMemory>();
		OpaquePass = std::make_unique<RenderOpaquePass>(this);
		TranslucentPass = std::make_unique<RenderTranslucentPass>(this);
		SpriteList = std::make_unique<VisibleSpriteList>();
		Portal = std::make_unique<RenderPortal>(this);
		Clip3DFloors = std::make_unique<swrenderer::Clip3DFloors>(this);
		PlayerSprites = std::make_unique<RenderPlayerSprites>(this);
		PlaneList = std::make_unique<VisiblePlaneList>(this);
		Scene = std::make_unique<RenderScene>(this);
		DrawSegments = std::make_unique<DrawSegmentList>(this);
		ClipSegments = std::make_unique<RenderClipSegment>();
	}

	RenderThread::~RenderThread()
	{
	}
}
