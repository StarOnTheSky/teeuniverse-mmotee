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

#ifndef __CLIENT_ASSETS_WEAPON__
#define __CLIENT_ASSETS_WEAPON__

#include <shared/assets/asset.h>
#include <shared/assets/assetpath.h>

class CAsset_Weapon : public CAsset
{
public:
	static const int TypeId = 23;
	
	enum
	{
		NAME = CAsset::NAME,
		CHARACTERPATH,
		CURSORPATH,
		SKINPATH,
		ATTACKANIMATIONPATH,
	};
	
	class CTuaType : public CAsset::CTuaType
	{
	public:
		CAssetPath::CTuaType m_CharacterPath;
		CAssetPath::CTuaType m_CursorPath;
		CAssetPath::CTuaType m_SkinPath;
		CAssetPath::CTuaType m_AttackAnimationPath;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType& TuaType, CAsset_Weapon& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Weapon& SysType, CTuaType& TuaType);
	};
	

private:
	CAssetPath m_CharacterPath;
	CAssetPath m_CursorPath;
	CAssetPath m_SkinPath;
	CAssetPath m_AttackAnimationPath;

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
	
	
	void copy(const CAsset_Weapon& Item)
	{
		CAsset::copy(Item);
		m_CharacterPath = Item.m_CharacterPath;
		m_CursorPath = Item.m_CursorPath;
		m_SkinPath = Item.m_SkinPath;
		m_AttackAnimationPath = Item.m_AttackAnimationPath;
	}
	
	void transfert(CAsset_Weapon& Item)
	{
		CAsset::transfert(Item);
		m_CharacterPath = Item.m_CharacterPath;
		m_CursorPath = Item.m_CursorPath;
		m_SkinPath = Item.m_SkinPath;
		m_AttackAnimationPath = Item.m_AttackAnimationPath;
	}
	
	inline CAssetPath GetCharacterPath() const { return m_CharacterPath; }
	
	inline CAssetPath GetCursorPath() const { return m_CursorPath; }
	
	inline CAssetPath GetSkinPath() const { return m_SkinPath; }
	
	inline CAssetPath GetAttackAnimationPath() const { return m_AttackAnimationPath; }
	
	inline void SetCharacterPath(const CAssetPath& Value) { m_CharacterPath = Value; }
	
	inline void SetCursorPath(const CAssetPath& Value) { m_CursorPath = Value; }
	
	inline void SetSkinPath(const CAssetPath& Value) { m_SkinPath = Value; }
	
	inline void SetAttackAnimationPath(const CAssetPath& Value) { m_AttackAnimationPath = Value; }
	
	void AssetPathOperation(const CAssetPath::COperation& Operation)
	{
		Operation.Apply(m_CharacterPath);
		Operation.Apply(m_CursorPath);
		Operation.Apply(m_SkinPath);
		Operation.Apply(m_AttackAnimationPath);
	}
	
};

#endif
