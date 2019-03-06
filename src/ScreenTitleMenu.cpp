#include "global.h"
#include "Etterna/Singletons/AnnouncerManager.h"
#include "CodeDetector.h"
#include "Game.h"
#include "GameLoop.h"
#include "GamePreferences.h"
#include "Etterna/Singletons/GameSoundManager.h"
#include "Etterna/Singletons/GameState.h"
#include "InputEventPlus.h"
#include "Etterna/Singletons/InputMapper.h"
#include "LocalizedString.h"
#include "RageUtil/Misc/RageLog.h"
#include "RageUtil/Utils/RageUtil.h"
#include "Etterna/Singletons/ScreenManager.h"
#include "ScreenTitleMenu.h"
#include "Etterna/Singletons/ThemeManager.h"

#define COIN_MODE_CHANGE_SCREEN                                                \
	THEME->GetMetric(m_sName, "CoinModeChangeScreen")

REGISTER_SCREEN_CLASS(ScreenTitleMenu);
ScreenTitleMenu::ScreenTitleMenu()
{
	/* XXX We really need two common calls:
	 * 1) something run when exiting from gameplay (to do this reset),
	 * and 2) something run when entering gameplay, to apply default options.
	 * Having special cases in attract screens and the title menu to reset
	 * things stinks ...
	 * [aj] Well... Can't #2 be done in Lua nowadays? and #1 as well? (hi shake)
	 */
	GAMESTATE->Reset();
}

void
ScreenTitleMenu::Init()
{
	ScreenSelectMaster::Init();

	SOUND->PlayOnceFromAnnouncer("title menu game name");
}

static LocalizedString THEME_("ScreenTitleMenu", "Theme");
static LocalizedString ANNOUNCER_("ScreenTitleMenu", "Announcer");
bool
ScreenTitleMenu::Input(const InputEventPlus& input)
{
#if defined(DEBUG)
	LOG->Trace("ScreenTitleMenu::Input( %d-%d )",
			   input.DeviceI.device,
			   input.DeviceI.button); // debugging gameport joystick problem
#endif

	if (m_In.IsTransitioning() || m_Cancel.IsTransitioning()) /* not m_Out */
		return false;

	bool bHandled = false;

	return ScreenSelectMaster::Input(input) || bHandled;
}

void
ScreenTitleMenu::HandleMessage(const Message& msg)
{
	ScreenSelectMaster::HandleMessage(msg);
}

/*
 * (c) 2001-2004 Chris Danford
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
