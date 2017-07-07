//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SCROLLSHEET_H
#define TOY_SCROLLSHEET_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Scrollbar.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT ScrollSurface : public Wedge
	{
	public:
		ScrollSurface(Wedge& parent);

		static Type& cls() { static Type ty("ScrollSurface", Wedge::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT ScrollZone : public Wedge
	{
	public:
		ScrollZone(ScrollSheet& parent);

		ScrollSurface body;

		static Type& cls() { static Type ty("ScrollZone", Wedge::Layout()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT ScrollSheet : public Wedge
	{
	public:
		ScrollSheet(Wedge& parent, Type& type = cls());

		Wedge& body() { return m_scrollzone.body; }

		virtual void dirtyLayout();

		virtual bool mouseWheel(MouseEvent& mouseEvent);

		virtual void makeSolver();

		static Type& cls() { static Type ty("ScrollSheet", Wedge::cls()); return ty; }

	protected:
		ScrollZone m_scrollzone;
		Scrollbar m_scrollbarX;
		Scrollbar m_scrollbarY;
	};

	class _refl_ TOY_UI_EXPORT ScrollPlan : public ScrollSheet
	{
	public:
		ScrollPlan(Wedge& parent, Type& type = cls());

		Wedge& plan() { return m_plan; }

		virtual bool middleDrag(MouseEvent& mouseEvent);
		virtual bool mouseWheel(MouseEvent& mouseEvent);

		virtual void dirtyLayout();

		void updateBounds();

		static Type& cls() { static Type ty("ScrollPlan", ScrollSheet::cls()); return ty; }

		static Type& Plan() { static Type ty("Plan", Wedge::Sheet()); return ty; }
		static Type& Surface() { static Type ty("Surface", Wedge::Sheet()); return ty; }

	protected:
		Wedge& m_plan;
		BoxFloat m_bounds;
		bool m_clamped;
	};

	TOY_UI_EXPORT bool drawGrid(const Frame& frame, Renderer& renderer);
}

#endif // TOY_SCROLLSHEET_H
