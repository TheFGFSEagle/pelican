#ifndef PELICAN_COMMANDS_HXX
#define PELICAN_COMMANDS_HXX

#include <easyqt/commands.hxx>

namespace pelican {
	EASYQTCOMMAND_GEN_DEF(MediaViewSelectAllCommand);
	EASYQTCOMMAND_GEN_DEF(MediaViewInvertSelectionCommand);
	
	void addCommands();
}

#endif

