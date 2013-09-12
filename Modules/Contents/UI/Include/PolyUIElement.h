/*
 Copyright (C) 2012 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#pragma once
#include "PolyGlobals.h"
#include "PolyEntity.h"
#include "PolySceneImage.h"
#include "PolySceneLabel.h"

namespace Polycode {
	/*
	 * Base class for all UI widgets.
	 *
	 * processInputEvent is set to true by default.
	 */
	class _PolyExport UIElement : public Entity {
		public:
			UIElement();
			UIElement(Number width, Number height);
			virtual ~UIElement();
			
			virtual void Resize(Number width, Number height);
						
			bool hasFocus;
			bool focusable;
			
			void addChild(Entity *child);
			
			void setDragLimits(Rectangle rect);
			void clearDragLimits();
			bool isDragged();
			void startDrag(Number xOffset, Number yOffset);
			void stopDrag();
			
			void focusChild(UIElement *child);
			void focusNextChild();
			bool isFocusable();
			void focusSelf();
									
			virtual void onLoseFocus() {}
			virtual void onGainFocus() {}
			
			void addFocusChild(UIElement *element);			
			void setFocusParent(UIElement *element);

			MouseEventResult onMouseMove(const Ray &ray, int timestamp);

			bool dragged;
			
			static UIElement *globalFocusedChild;

		protected:
		
			Polycode::Rectangle dragLimits;
			bool hasDragLimits;
		
			Number dragOffsetX;
			Number dragOffsetY;
			
			std::vector<UIElement*> focusChildren;
			UIElement *focusParent;
			
	};

	class _PolyExport UIRect : public UIElement {
		public:
			UIRect(String fileName);
			UIRect(Number width, Number height);
			void initRect(Number width, Number height);
			~UIRect();
			void Resize(Number width, Number height);
			void Render();
			void loadTexture(String fileName);
			void setTexture(Texture *texture);
			void setImageCoordinates(Number x, Number y, Number width, Number height);
			Number getImageWidth() const;
			Number getImageHeight() const;
						
			Texture *getTexture();			
		protected:
		
			Number imageWidth;
			Number imageHeight;
			
			Mesh *rectMesh;
			Texture *texture;
			
	};
	
	class _PolyExport UILabel : public UIElement {
		public:
			UILabel(const String& text, int size, const String& fontName = "sans", int amode = 0);			
			void setText(const String& text);
			Label *getLabel();
			String getText();
			
			~UILabel();			
		protected:
			SceneLabel *label;
	};

	
	class _PolyExport UIImage : public UIElement {
		public:
			UIImage(String imagePath);
			SceneImage *getImage();
		protected:
			SceneImage *image;
	};
	
}
