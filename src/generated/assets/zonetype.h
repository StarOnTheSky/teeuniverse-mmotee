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

#ifndef __CLIENT_ASSETS_ZONETYPE__
#define __CLIENT_ASSETS_ZONETYPE__

#include <shared/assets/asset.h>
#include <shared/tl/array.h>

class CAsset_ZoneType : public CAsset
{
public:
	static const int TypeId = 24;
	
	enum
	{
		TYPE_INDEX,
	};
	
	static inline CSubPath SubPath_Index(int Id0) { return CSubPath(TYPE_INDEX, Id0, 0, 0); }
	
	enum
	{
		NAME = CAsset::NAME,
		INDEX_ARRAYSIZE,
		INDEX_PTR,
		INDEX_ARRAY,
		INDEX_NAME,
		INDEX_NUMBER,
		INDEX_COLOR,
		INDEX,
	};
	
	class CIteratorIndex
	{
	protected:
		int m_Index;
		bool m_Reverse;
	public:
		CIteratorIndex() : m_Index(0), m_Reverse(false) {}
		CIteratorIndex(int Index, bool Reverse) : m_Index(Index), m_Reverse(Reverse) {}
		CIteratorIndex& operator++() { if(m_Reverse) m_Index--; else m_Index++; return *this; }
		CSubPath operator*() { return SubPath_Index(m_Index); }
		bool operator==(const CIteratorIndex& Iter2) { return Iter2.m_Index == m_Index; }
		bool operator!=(const CIteratorIndex& Iter2) { return Iter2.m_Index != m_Index; }
	};
	
	CIteratorIndex BeginIndex() const { return CIteratorIndex(0, false); }
	CIteratorIndex EndIndex() const { return CIteratorIndex(m_Index.size(), false); }
	CIteratorIndex ReverseBeginIndex() const { return CIteratorIndex(m_Index.size()-1, true); }
	CIteratorIndex ReverseEndIndex() const { return CIteratorIndex(-1, true); }
	
	class CIndex
	{
	public:
		class CTuaType
		{
		public:
			tua_stringid m_Name;
			tua_int32 m_Number;
			tua_uint32 m_Color;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType& TuaType, CAsset_ZoneType::CIndex& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_ZoneType::CIndex& SysType, CTuaType& TuaType);
		};
		
	
	private:
		string< _fixed_string_core<128> > m_Name;
		int m_Number;
		vec4 m_Color;
	
	public:
		CIndex();
		void copy(const CAsset_ZoneType::CIndex& Item)
		{
			m_Name.copy(Item.m_Name);
			m_Number = Item.m_Number;
			m_Color = Item.m_Color;
		}
		
		void transfert(CAsset_ZoneType::CIndex& Item)
		{
			m_Name.transfert(Item.m_Name);
			m_Number = Item.m_Number;
			m_Color = Item.m_Color;
		}
		
		inline const char* GetName() const { return m_Name.buffer(); }
		
		inline int GetNumber() const { return m_Number; }
		
		inline vec4 GetColor() const { return m_Color; }
		
		inline void SetName(const char* Value) { m_Name.copy(Value); }
		
		inline void SetNumber(int Value) { m_Number = Value; }
		
		inline void SetColor(vec4 Value) { m_Color = Value; }
		
		void AssetPathOperation(const CAssetPath::COperation& Operation)
		{
		}
		
	};
	class CTuaType : public CAsset::CTuaType
	{
	public:
		CTuaArray m_Index;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType& TuaType, CAsset_ZoneType& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_ZoneType& SysType, CTuaType& TuaType);
	};
	

private:
	array< CAsset_ZoneType::CIndex, allocator_copy<CAsset_ZoneType::CIndex> > m_Index;

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
	
	
	void copy(const CAsset_ZoneType& Item)
	{
		CAsset::copy(Item);
		m_Index.copy(Item.m_Index);
	}
	
	void transfert(CAsset_ZoneType& Item)
	{
		CAsset::transfert(Item);
		m_Index.transfert(Item.m_Index);
	}
	
	inline int GetIndexArraySize() const { return m_Index.size(); }
	
	inline const CAsset_ZoneType::CIndex* GetIndexPtr() const { return m_Index.base_ptr(); }
	
	inline const array< CAsset_ZoneType::CIndex, allocator_copy<CAsset_ZoneType::CIndex> >& GetIndexArray() const { return m_Index; }
	inline array< CAsset_ZoneType::CIndex, allocator_copy<CAsset_ZoneType::CIndex> >& GetIndexArray() { return m_Index; }
	
	inline const CAsset_ZoneType::CIndex& GetIndex(const CSubPath& SubPath) const { return m_Index[SubPath.GetId()]; }
	
	inline const char* GetIndexName(const CSubPath& SubPath) const { return m_Index[SubPath.GetId()].GetName(); }
	
	inline int GetIndexNumber(const CSubPath& SubPath) const { return m_Index[SubPath.GetId()].GetNumber(); }
	
	inline vec4 GetIndexColor(const CSubPath& SubPath) const { return m_Index[SubPath.GetId()].GetColor(); }
	
	inline void SetIndexArraySize(int Value) { m_Index.resize(Value); }
	
	inline void SetIndex(const CSubPath& SubPath, const CAsset_ZoneType::CIndex& Value) { m_Index[SubPath.GetId()].copy(Value); }
	
	inline void SetIndexName(const CSubPath& SubPath, const char* Value) { m_Index[SubPath.GetId()].SetName(Value); }
	
	inline void SetIndexNumber(const CSubPath& SubPath, int Value) { m_Index[SubPath.GetId()].SetNumber(Value); }
	
	inline void SetIndexColor(const CSubPath& SubPath, vec4 Value) { m_Index[SubPath.GetId()].SetColor(Value); }
	
	inline int AddIndex()
	{
		int Id = m_Index.size();
		m_Index.increment();
		return Id;
	}
	
	inline bool IsValidIndex(const CSubPath& SubPath) const { return (SubPath.GetId() >= 0 && SubPath.GetId() < m_Index.size()); }
	
	void AssetPathOperation(const CAssetPath::COperation& Operation)
	{
		for(int i=0; i<m_Index.size(); i++)
		{
			m_Index[i].AssetPathOperation(Operation);
		}
	}
	
};

#endif
