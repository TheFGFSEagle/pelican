#include "commands.hxx"
#include "mediashowarea.hxx"
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
	EASYQTCOMMAND_GEN_IMPL(
		MediaShowAreaScaleIncreaseCommand, "mediashowarea-scale-increase",
		MediaShowArea::instance()->scaleIncrease()
	);
	EASYQTCOMMAND_GEN_IMPL(
		MediaShowAreaScaleDecreaseCommand, "mediashowarea-scale-decrease",
		MediaShowArea::instance()->scaleDecrease()
	);
	EASYQTCOMMAND_GEN_IMPL(
		MediaShowAreaScaleFitCommand, "mediashowarea-scale-fit",
		MediaShowArea::instance()->scaleFit()
	);
	EASYQTCOMMAND_GEN_IMPL(
		MediaShowAreaScaleOriginalSizeCommand, "mediashowarea-scale-original-size",
		MediaShowArea::instance()->scaleOriginalSize()
	)
	
	void addCommands() {
		easyqt::addCommands({
			MediaViewSelectAllCommand::instance(),
			MediaViewInvertSelectionCommand::instance(),
			MediaShowAreaScaleIncreaseCommand::instance(),
			MediaShowAreaScaleDecreaseCommand::instance(),
			MediaShowAreaScaleFitCommand::instance(),
			MediaShowAreaScaleOriginalSizeCommand::instance(),
		});
	}
}

