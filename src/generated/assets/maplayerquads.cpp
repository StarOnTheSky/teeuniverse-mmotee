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

/*
 * THIS FILE HAS BEEN GENERATED BY A SCRIPT.
 * DO NOT EDIT MANUALLY!
 *
 * Please use the script "scripts/assets/assets.py" to regenerate it.
 *
 * Why this file is generated by a script?
 * Because there is more than 10 files that follow the same format.
 * In addition, each time a new member is added, enums, getter, setters,
 * copy/transfert functions and storage structure must be updated.
 * It's too much to avoid mistakes.
 */

#include <generated/assets/maplayerquads.h>
#include <shared/assets/assetssaveloadcontext.h>
#include <shared/archivefile.h>

CAsset_MapLayerQuads::CQuad::CQuad()
{
	m_Pivot = 0.0f;
	m_Size = 1.0f;
	m_Angle = 0.0f;
	m_Vertex0 = 0.0f;
	m_Vertex1 = 0.0f;
	m_Vertex2 = 0.0f;
	m_Vertex3 = 0.0f;
	m_UV0 = 0.0f;
	m_UV1 = 0.0f;
	m_UV2 = 0.0f;
	m_UV3 = 0.0f;
	m_Color0 = 1.0f;
	m_Color1 = 1.0f;
	m_Color2 = 1.0f;
	m_Color3 = 1.0f;
}


void CAsset_MapLayerQuads::CQuad::CTuaType::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType& TuaType, CAsset_MapLayerQuads::CQuad& SysType)
{
	SysType.m_Pivot.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Pivot.m_X);
	SysType.m_Pivot.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Pivot.m_Y);
	SysType.m_Size.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Size.m_X);
	SysType.m_Size.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Size.m_Y);
	SysType.m_Angle = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Angle);
	SysType.m_Vertex0.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Vertex0.m_X);
	SysType.m_Vertex0.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Vertex0.m_Y);
	SysType.m_Vertex1.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Vertex1.m_X);
	SysType.m_Vertex1.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Vertex1.m_Y);
	SysType.m_Vertex2.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Vertex2.m_X);
	SysType.m_Vertex2.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Vertex2.m_Y);
	SysType.m_Vertex3.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Vertex3.m_X);
	SysType.m_Vertex3.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Vertex3.m_Y);
	SysType.m_UV0.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_UV0.m_X);
	SysType.m_UV0.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_UV0.m_Y);
	SysType.m_UV1.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_UV1.m_X);
	SysType.m_UV1.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_UV1.m_Y);
	SysType.m_UV2.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_UV2.m_X);
	SysType.m_UV2.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_UV2.m_Y);
	SysType.m_UV3.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_UV3.m_X);
	SysType.m_UV3.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_UV3.m_Y);
	SysType.m_Color0 = pLoadingContext->ArchiveFile()->ReadColor(TuaType.m_Color0);
	SysType.m_Color1 = pLoadingContext->ArchiveFile()->ReadColor(TuaType.m_Color1);
	SysType.m_Color2 = pLoadingContext->ArchiveFile()->ReadColor(TuaType.m_Color2);
	SysType.m_Color3 = pLoadingContext->ArchiveFile()->ReadColor(TuaType.m_Color3);
	pLoadingContext->ReadAssetPath(TuaType.m_AnimationPath, SysType.m_AnimationPath);
}

void CAsset_MapLayerQuads::CTuaType::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType& TuaType, CAsset_MapLayerQuads& SysType)
{
	CAsset::CTuaType::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_ImagePath, SysType.m_ImagePath);
	{
		const CAsset_MapLayerQuads::CQuad::CTuaType* pData = (const CAsset_MapLayerQuads::CQuad::CTuaType*) pLoadingContext->ArchiveFile()->GetData(TuaType.m_Quad.m_Data);
		uint32 Size = pLoadingContext->ArchiveFile()->ReadUInt32(TuaType.m_Quad.m_Size);
		SysType.m_Quad.resize(Size);
		for(int i=0; i<Size; i++)
		{
			CAsset_MapLayerQuads::CQuad::CTuaType::Read(pLoadingContext, pData[i], SysType.m_Quad[i]);
		}
	}
	
}

void CAsset_MapLayerQuads::CQuad::CTuaType::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapLayerQuads::CQuad& SysType, CTuaType& TuaType)
{
	TuaType.m_Pivot.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Pivot.x);
	TuaType.m_Pivot.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Pivot.y);
	TuaType.m_Size.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Size.x);
	TuaType.m_Size.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Size.y);
	TuaType.m_Angle = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Angle);
	TuaType.m_Vertex0.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Vertex0.x);
	TuaType.m_Vertex0.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Vertex0.y);
	TuaType.m_Vertex1.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Vertex1.x);
	TuaType.m_Vertex1.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Vertex1.y);
	TuaType.m_Vertex2.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Vertex2.x);
	TuaType.m_Vertex2.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Vertex2.y);
	TuaType.m_Vertex3.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Vertex3.x);
	TuaType.m_Vertex3.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Vertex3.y);
	TuaType.m_UV0.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_UV0.x);
	TuaType.m_UV0.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_UV0.y);
	TuaType.m_UV1.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_UV1.x);
	TuaType.m_UV1.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_UV1.y);
	TuaType.m_UV2.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_UV2.x);
	TuaType.m_UV2.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_UV2.y);
	TuaType.m_UV3.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_UV3.x);
	TuaType.m_UV3.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_UV3.y);
	TuaType.m_Color0 = pLoadingContext->ArchiveFile()->WriteColor(SysType.m_Color0);
	TuaType.m_Color1 = pLoadingContext->ArchiveFile()->WriteColor(SysType.m_Color1);
	TuaType.m_Color2 = pLoadingContext->ArchiveFile()->WriteColor(SysType.m_Color2);
	TuaType.m_Color3 = pLoadingContext->ArchiveFile()->WriteColor(SysType.m_Color3);
	pLoadingContext->WriteAssetPath(SysType.m_AnimationPath, TuaType.m_AnimationPath);
}

void CAsset_MapLayerQuads::CTuaType::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapLayerQuads& SysType, CTuaType& TuaType)
{
	CAsset::CTuaType::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_ImagePath, TuaType.m_ImagePath);
	{
		TuaType.m_Quad.m_Size = SysType.m_Quad.size();
		CAsset_MapLayerQuads::CQuad::CTuaType* pData = new CAsset_MapLayerQuads::CQuad::CTuaType[SysType.m_Quad.size()];
		for(int i=0; i<SysType.m_Quad.size(); i++)
		{
			CAsset_MapLayerQuads::CQuad::CTuaType::Write(pLoadingContext, SysType.m_Quad[i], pData[i]);
		}
		TuaType.m_Quad.m_Data = pLoadingContext->ArchiveFile()->AddData((uint8*) pData, sizeof(CAsset_MapLayerQuads::CQuad::CTuaType)*SysType.m_Quad.size());
		delete[] pData;
	}
}

template<>
int CAsset_MapLayerQuads::GetValue(int ValueType, const CSubPath& SubPath, int DefaultValue) const
{
	switch(ValueType)
	{
		case QUAD_ARRAYSIZE:
			return GetQuadArraySize();
	}
	return CAsset::GetValue<int>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_MapLayerQuads::SetValue(int ValueType, const CSubPath& SubPath, int Value)
{
	switch(ValueType)
	{
		case QUAD_ARRAYSIZE:
			SetQuadArraySize(Value);
			return true;
	}
	return CAsset::SetValue<int>(ValueType, SubPath, Value);
}

template<>
float CAsset_MapLayerQuads::GetValue(int ValueType, const CSubPath& SubPath, float DefaultValue) const
{
	switch(ValueType)
	{
		case QUAD_PIVOT_X:
			return GetQuadPivotX(SubPath);
		case QUAD_PIVOT_Y:
			return GetQuadPivotY(SubPath);
		case QUAD_SIZE_X:
			return GetQuadSizeX(SubPath);
		case QUAD_SIZE_Y:
			return GetQuadSizeY(SubPath);
		case QUAD_ANGLE:
			return GetQuadAngle(SubPath);
		case QUAD_VERTEX0_X:
			return GetQuadVertex0X(SubPath);
		case QUAD_VERTEX0_Y:
			return GetQuadVertex0Y(SubPath);
		case QUAD_VERTEX1_X:
			return GetQuadVertex1X(SubPath);
		case QUAD_VERTEX1_Y:
			return GetQuadVertex1Y(SubPath);
		case QUAD_VERTEX2_X:
			return GetQuadVertex2X(SubPath);
		case QUAD_VERTEX2_Y:
			return GetQuadVertex2Y(SubPath);
		case QUAD_VERTEX3_X:
			return GetQuadVertex3X(SubPath);
		case QUAD_VERTEX3_Y:
			return GetQuadVertex3Y(SubPath);
		case QUAD_UV0_X:
			return GetQuadUV0X(SubPath);
		case QUAD_UV0_Y:
			return GetQuadUV0Y(SubPath);
		case QUAD_UV1_X:
			return GetQuadUV1X(SubPath);
		case QUAD_UV1_Y:
			return GetQuadUV1Y(SubPath);
		case QUAD_UV2_X:
			return GetQuadUV2X(SubPath);
		case QUAD_UV2_Y:
			return GetQuadUV2Y(SubPath);
		case QUAD_UV3_X:
			return GetQuadUV3X(SubPath);
		case QUAD_UV3_Y:
			return GetQuadUV3Y(SubPath);
	}
	return CAsset::GetValue<float>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_MapLayerQuads::SetValue(int ValueType, const CSubPath& SubPath, float Value)
{
	switch(ValueType)
	{
		case QUAD_PIVOT_X:
			SetQuadPivotX(SubPath, Value);
			return true;
		case QUAD_PIVOT_Y:
			SetQuadPivotY(SubPath, Value);
			return true;
		case QUAD_SIZE_X:
			SetQuadSizeX(SubPath, Value);
			return true;
		case QUAD_SIZE_Y:
			SetQuadSizeY(SubPath, Value);
			return true;
		case QUAD_ANGLE:
			SetQuadAngle(SubPath, Value);
			return true;
		case QUAD_VERTEX0_X:
			SetQuadVertex0X(SubPath, Value);
			return true;
		case QUAD_VERTEX0_Y:
			SetQuadVertex0Y(SubPath, Value);
			return true;
		case QUAD_VERTEX1_X:
			SetQuadVertex1X(SubPath, Value);
			return true;
		case QUAD_VERTEX1_Y:
			SetQuadVertex1Y(SubPath, Value);
			return true;
		case QUAD_VERTEX2_X:
			SetQuadVertex2X(SubPath, Value);
			return true;
		case QUAD_VERTEX2_Y:
			SetQuadVertex2Y(SubPath, Value);
			return true;
		case QUAD_VERTEX3_X:
			SetQuadVertex3X(SubPath, Value);
			return true;
		case QUAD_VERTEX3_Y:
			SetQuadVertex3Y(SubPath, Value);
			return true;
		case QUAD_UV0_X:
			SetQuadUV0X(SubPath, Value);
			return true;
		case QUAD_UV0_Y:
			SetQuadUV0Y(SubPath, Value);
			return true;
		case QUAD_UV1_X:
			SetQuadUV1X(SubPath, Value);
			return true;
		case QUAD_UV1_Y:
			SetQuadUV1Y(SubPath, Value);
			return true;
		case QUAD_UV2_X:
			SetQuadUV2X(SubPath, Value);
			return true;
		case QUAD_UV2_Y:
			SetQuadUV2Y(SubPath, Value);
			return true;
		case QUAD_UV3_X:
			SetQuadUV3X(SubPath, Value);
			return true;
		case QUAD_UV3_Y:
			SetQuadUV3Y(SubPath, Value);
			return true;
	}
	return CAsset::SetValue<float>(ValueType, SubPath, Value);
}

template<>
vec2 CAsset_MapLayerQuads::GetValue(int ValueType, const CSubPath& SubPath, vec2 DefaultValue) const
{
	switch(ValueType)
	{
		case QUAD_PIVOT:
			return GetQuadPivot(SubPath);
		case QUAD_SIZE:
			return GetQuadSize(SubPath);
		case QUAD_VERTEX0:
			return GetQuadVertex0(SubPath);
		case QUAD_VERTEX1:
			return GetQuadVertex1(SubPath);
		case QUAD_VERTEX2:
			return GetQuadVertex2(SubPath);
		case QUAD_VERTEX3:
			return GetQuadVertex3(SubPath);
		case QUAD_UV0:
			return GetQuadUV0(SubPath);
		case QUAD_UV1:
			return GetQuadUV1(SubPath);
		case QUAD_UV2:
			return GetQuadUV2(SubPath);
		case QUAD_UV3:
			return GetQuadUV3(SubPath);
	}
	return CAsset::GetValue<vec2>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_MapLayerQuads::SetValue(int ValueType, const CSubPath& SubPath, vec2 Value)
{
	switch(ValueType)
	{
		case QUAD_PIVOT:
			SetQuadPivot(SubPath, Value);
			return true;
		case QUAD_SIZE:
			SetQuadSize(SubPath, Value);
			return true;
		case QUAD_VERTEX0:
			SetQuadVertex0(SubPath, Value);
			return true;
		case QUAD_VERTEX1:
			SetQuadVertex1(SubPath, Value);
			return true;
		case QUAD_VERTEX2:
			SetQuadVertex2(SubPath, Value);
			return true;
		case QUAD_VERTEX3:
			SetQuadVertex3(SubPath, Value);
			return true;
		case QUAD_UV0:
			SetQuadUV0(SubPath, Value);
			return true;
		case QUAD_UV1:
			SetQuadUV1(SubPath, Value);
			return true;
		case QUAD_UV2:
			SetQuadUV2(SubPath, Value);
			return true;
		case QUAD_UV3:
			SetQuadUV3(SubPath, Value);
			return true;
	}
	return CAsset::SetValue<vec2>(ValueType, SubPath, Value);
}

template<>
vec4 CAsset_MapLayerQuads::GetValue(int ValueType, const CSubPath& SubPath, vec4 DefaultValue) const
{
	switch(ValueType)
	{
		case QUAD_COLOR0:
			return GetQuadColor0(SubPath);
		case QUAD_COLOR1:
			return GetQuadColor1(SubPath);
		case QUAD_COLOR2:
			return GetQuadColor2(SubPath);
		case QUAD_COLOR3:
			return GetQuadColor3(SubPath);
	}
	return CAsset::GetValue<vec4>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_MapLayerQuads::SetValue(int ValueType, const CSubPath& SubPath, vec4 Value)
{
	switch(ValueType)
	{
		case QUAD_COLOR0:
			SetQuadColor0(SubPath, Value);
			return true;
		case QUAD_COLOR1:
			SetQuadColor1(SubPath, Value);
			return true;
		case QUAD_COLOR2:
			SetQuadColor2(SubPath, Value);
			return true;
		case QUAD_COLOR3:
			SetQuadColor3(SubPath, Value);
			return true;
	}
	return CAsset::SetValue<vec4>(ValueType, SubPath, Value);
}

template<>
CAssetPath CAsset_MapLayerQuads::GetValue(int ValueType, const CSubPath& SubPath, CAssetPath DefaultValue) const
{
	switch(ValueType)
	{
		case IMAGEPATH:
			return GetImagePath();
		case QUAD_ANIMATIONPATH:
			return GetQuadAnimationPath(SubPath);
	}
	return CAsset::GetValue<CAssetPath>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_MapLayerQuads::SetValue(int ValueType, const CSubPath& SubPath, CAssetPath Value)
{
	switch(ValueType)
	{
		case IMAGEPATH:
			SetImagePath(Value);
			return true;
		case QUAD_ANIMATIONPATH:
			SetQuadAnimationPath(SubPath, Value);
			return true;
	}
	return CAsset::SetValue<CAssetPath>(ValueType, SubPath, Value);
}


