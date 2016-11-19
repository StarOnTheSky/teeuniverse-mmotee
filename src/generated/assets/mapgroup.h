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

#ifndef __CLIENT_ASSETS_MAPGROUP__
#define __CLIENT_ASSETS_MAPGROUP__

#include <shared/assets/asset.h>
#include <shared/tl/array.h>
#include <shared/math/vector.h>

class CAsset_MapGroup : public CAsset
{
public:
	static const int TypeId = 15;
	
	enum
	{
		TYPE_LAYER,
	};
	
	static inline CSubPath SubPath_Layer(int Id0) { return CSubPath(TYPE_LAYER, Id0, 0, 0); }
	
	enum
	{
		NAME = CAsset::NAME,
		LAYER_ARRAYSIZE,
		LAYER_PTR,
		LAYER_ARRAY,
		LAYER,
		POSITION_X,
		POSITION_Y,
		POSITION,
		HARDPARALLAX_X,
		HARDPARALLAX_Y,
		HARDPARALLAX,
	};
	
	class CIteratorLayer
	{
	protected:
		int m_Index;
		bool m_Reverse;
	public:
		CIteratorLayer() : m_Index(0), m_Reverse(false) {}
		CIteratorLayer(int Index, bool Reverse) : m_Index(Index), m_Reverse(Reverse) {}
		CIteratorLayer& operator++() { if(m_Reverse) m_Index--; else m_Index++; return *this; }
		CSubPath operator*() { return SubPath_Layer(m_Index); }
		bool operator==(const CIteratorLayer& Iter2) { return Iter2.m_Index == m_Index; }
		bool operator!=(const CIteratorLayer& Iter2) { return Iter2.m_Index != m_Index; }
	};
	
	CIteratorLayer BeginLayer() const { return CIteratorLayer(0, false); }
	CIteratorLayer EndLayer() const { return CIteratorLayer(m_Layer.size(), false); }
	CIteratorLayer ReverseBeginLayer() const { return CIteratorLayer(m_Layer.size()-1, true); }
	CIteratorLayer ReverseEndLayer() const { return CIteratorLayer(-1, true); }
	
	class CTuaType : public CAsset::CTuaType
	{
	public:
		CTuaArray m_Layer;
		CTuaVec2 m_Position;
		CTuaVec2 m_HardParallax;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType& TuaType, CAsset_MapGroup& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapGroup& SysType, CTuaType& TuaType);
	};
	

private:
	array< CAssetPath, allocator_default<CAssetPath> > m_Layer;
	vec2 m_Position;
	vec2 m_HardParallax;

public:
	template<typename T>
	T GetValue(int ValueType, const CSubPath& SubPath, T DefaultValue) const
	{
		return CAsset::GetValue<T>(ValueType, SubPath, DefaultValue);
	}
	
	template<typename T>
	bool SetValue(int ValueType, const CSubPath& SubPath, T Value)
	{
		return CAsset::SetValue<T>(ValueType, SubPath, Value);
	}
	
	
	CAsset_MapGroup();
	void copy(const CAsset_MapGroup& Item)
	{
		CAsset::copy(Item);
		m_Layer.copy(Item.m_Layer);
		m_Position = Item.m_Position;
		m_HardParallax = Item.m_HardParallax;
	}
	
	void transfert(CAsset_MapGroup& Item)
	{
		CAsset::transfert(Item);
		m_Layer.transfert(Item.m_Layer);
		m_Position = Item.m_Position;
		m_HardParallax = Item.m_HardParallax;
	}
	
	inline int GetLayerArraySize() const { return m_Layer.size(); }
	
	inline const CAssetPath* GetLayerPtr() const { return m_Layer.base_ptr(); }
	
	inline const array< CAssetPath, allocator_default<CAssetPath> >& GetLayerArray() const { return m_Layer; }
	inline array< CAssetPath, allocator_default<CAssetPath> >& GetLayerArray() { return m_Layer; }
	
	inline CAssetPath GetLayer(const CSubPath& SubPath) const { return m_Layer[SubPath.GetId()]; }
	
	inline vec2 GetPosition() const { return m_Position; }
	
	inline float GetPositionX() const { return m_Position.x; }
	
	inline float GetPositionY() const { return m_Position.y; }
	
	inline vec2 GetHardParallax() const { return m_HardParallax; }
	
	inline float GetHardParallaxX() const { return m_HardParallax.x; }
	
	inline float GetHardParallaxY() const { return m_HardParallax.y; }
	
	inline void SetLayerArraySize(int Value) { m_Layer.resize(Value); }
	
	inline void SetLayer(const CSubPath& SubPath, const CAssetPath& Value) { m_Layer[SubPath.GetId()] = Value; }
	
	inline void SetPosition(vec2 Value) { m_Position = Value; }
	
	inline void SetPositionX(float Value) { m_Position.x = Value; }
	
	inline void SetPositionY(float Value) { m_Position.y = Value; }
	
	inline void SetHardParallax(vec2 Value) { m_HardParallax = Value; }
	
	inline void SetHardParallaxX(float Value) { m_HardParallax.x = Value; }
	
	inline void SetHardParallaxY(float Value) { m_HardParallax.y = Value; }
	
	inline int AddLayer()
	{
		int Id = m_Layer.size();
		m_Layer.increment();
		return Id;
	}
	
	inline bool IsValidLayer(const CSubPath& SubPath) const { return (SubPath.GetId() >= 0 && SubPath.GetId() < m_Layer.size()); }
	
	void AssetPathOperation(const CAssetPath::COperation& Operation)
	{
		{
			int Shift = 0;
			for(int i=0; i<m_Layer.size(); i++)
			{
				if(Operation.MustBeDeleted(m_Layer[i]))
					Shift++;
				else if(Shift > 0)
					m_Layer[i-Shift] = m_Layer[i];
			}
			m_Layer.resize(m_Layer.size()-Shift);
		}
		for(int i=0; i<m_Layer.size(); i++)
		{
			Operation.Apply(m_Layer[i]);
		}
	}
	
};

#endif
