#include "commands.hxx"
#include "mediaview.hxx"

namespace pelican {
	EASYQTCOMMAND_GEN_IMPL(
		MediaViewSelectAllCommand, "mediaview-select-all",
		MediaView::instance()->selectAll()
	);
	EASYQTCOMMAND_GEN_IMPL(
		MediaViewInvertSelectionCommand, "mediaview-invert-selection",
		MediaView::instance()->invertSelection()
	);
	
	void addCommands() {
		easyqt::addCommand(MediaViewSelectAllCommand::instance());
		easyqt::addCommand(MediaViewInvertSelectionCommand::instance());
	}
}

