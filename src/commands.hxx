#ifndef PELICAN_COMMANDS_HXX
#define PELICAN_COMMANDS_HXX

#include <easyqt/commands.hxx>

namespace pelican {
	EASYQTCOMMAND_GEN_DEF(MediaViewSelectAllCommand);
	EASYQTCOMMAND_GEN_DEF(MediaViewInvertSelectionCommand);
	EASYQTCOMMAND_GEN_DEF(MediaShowAreaScaleIncreaseCommand);
	EASYQTCOMMAND_GEN_DEF(MediaShowAreaScaleDecreaseCommand);
	EASYQTCOMMAND_GEN_DEF(MediaShowAreaScaleFitCommand);
	EASYQTCOMMAND_GEN_DEF(MediaShowAreaScaleOriginalSizeCommand);
	
	void addCommands();
}

#endif

