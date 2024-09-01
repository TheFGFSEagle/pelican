#ifndef PELICAN_MEDIASHOWAREА_HXX
#define PELICAN_MEDIASHOWAREА_HXX

#include <cmath>

#include <QLabel>
#include <QPoint>
#include <QResizeEvent>
#include <QWidget>

#include "singleton.hxx"

#include "media.hxx"
#include "mediaview.hxx"

namespace pelican {
	class MediaShowArea: public Singleton<MediaShowArea, QWidget> {
		Q_OBJECT
		public:
			MediaShowArea();
			
			void setMedia(MediaPtr media);
			void setMediaScale(double value);
			
			inline void scaleIncrease() {
				setMediaScale((std::ceil(_scale * 10) + 1) / 10);
			}
			inline void scaleDecrease() {
				setMediaScale((std::ceil(_scale * 10) - 1) / 10);
			}
			inline void scaleFit() {
				setMediaScale(_scale);
			}
			
			virtual void resizeEvent(QResizeEvent* event) override;
			virtual void keyPressEvent(QKeyEvent* event) override;
			virtual void mousePressEvent(QMouseEvent* event) override;
			virtual void mouseMoveEvent(QMouseEvent* event) override;
			virtual void mouseReleaseEvent(QMouseEvent* event) override;
		
		protected:
			void showMedia();
		
		private:
			MediaPtr _media;
			QLabel _mediaLabel;
			QPixmap _image;
			double _scale = {-1};
			QPoint _lastMousePosition;
	};
}

#endif

