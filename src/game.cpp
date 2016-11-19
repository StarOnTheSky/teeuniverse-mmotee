#include <shared/system/debug.h>
#include <shared/system/string.h>
#include <game/kernel.h>

/*
 * Copyright (C) 2016 necropotame (necropotame@gmail.com)
 * 
 * This file is part of TeeUniverses.
 * 
 * TeeUniverses is free software: you can redistribute it and/or  modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * TeeUniverses is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with TeeUniverses.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <SDL.h>

#if defined(CONF_PLATFORM_MACOSX)
extern "C" int SDL_main(int argc, char **argv_)
{
	const char **argv = const_cast<const char **>(argv_);
#else
int main(int argc, const char **argv)
{
#endif
	//Init SDL
	{
		if(SDL_Init(0) < 0)
		{
			dbg_msg("SDL", "unable to init SDL base: %s", SDL_GetError());
			return 0;
		}

		atexit(SDL_Quit);
	}
	
	CGameKernel* pKernel = new CGameKernel();
	if(!pKernel->Init(argc, argv))
	{
		dbg_msg("Kernel", "unable to initialize client kernel");
		exit(EXIT_FAILURE);
	}
	
	bool Running = true;
	do
	{
		Running = Running && pKernel->PreUpdate();
		Running = Running && pKernel->PostUpdate();
	}
	while(Running);
	
	pKernel->Shutdown();
	delete pKernel;

	exit(EXIT_SUCCESS);
}
