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

#include <client/components/assetsrenderer.h>
#include <client/components/graphics.h>

#include "widget.h"
	
namespace gui
{

CWidget::CWidget(CGui *pContext) :
	CGui::CGuest(pContext),
	m_Disabled(false)
{
	
}

void CWidget::Destroy()
{
	Context()->DestroyWidget(this);
}

void CWidget::UpdatePosition(const CRect& BoundingRect, const CRect& VisibilityRect)
{
	m_DrawRect.DRUpdatePosition(BoundingRect, m_BoundingSizeRect);
	m_VisibilityRect = m_DrawRect.Intersection(VisibilityRect);
}

}
