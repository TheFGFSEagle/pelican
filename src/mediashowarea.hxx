#ifndef PELICAN_MEDIASHOWAREА_HXX
#define PELICAN_MEDIASHOWAREА_HXX

#include <QLabel>
#include <QResizeEvent>
#include <QWidget>

#include "singleton.hxx"

#include "media.hxx"

namespace pelican {
	class MediaShowArea: public Singleton<MediaShowArea, QWidget> {
		Q_OBJECT
		public:
			MediaShowArea();
			
			void setMedia(MediaPtr media);
			
			virtual void resizeEvent(QResizeEvent* event) override;
		
		protected:
			void showMedia();
		
		private:
			MediaPtr _media;
			QLabel _mediaLabel;
			QPixmap _image;
	};
}

#endif

