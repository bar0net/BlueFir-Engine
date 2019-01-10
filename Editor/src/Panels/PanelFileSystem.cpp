#include "PanelFileSystem.h"

void bluefir::editor::PanelFileSystem::Init()
{
	if (!base::FileSystem::ExistsDir(BF_FILESYSTEM_ASSETSDIR))
	{
		LOGDEBUG("No assets folder detected, creating one.");
		base::FileSystem::ExistsDir(BF_FILESYSTEM_ASSETSDIR);
	}

	if (!base::FileSystem::ExistsDir(BF_FILESYSTEM_LIBRARYDIR))
	{
		LOGDEBUG("No library folder detected, creating one.");
		base::FileSystem::ExistsDir(BF_FILESYSTEM_LIBRARYDIR);
	}
}

void bluefir::editor::PanelFileSystem::Draw()
{
}
