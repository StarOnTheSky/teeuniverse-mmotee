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

#include <editor/gui/assetslist.h>
#include <editor/components/gui.h>
#include <shared/components/assetsmanager.h>
#include <client/gui/expand.h>
#include <client/gui/popup.h>
#include <client/gui/text-edit.h>
#include <shared/components/localization.h>
#include <shared/components/storage.h>

/* PACKAGE ITEM *******************************************************/

class CPackageItem : public gui::CButton
{
protected:
	class CCloseButton : public gui::CButton
	{
	protected:
		CGuiEditor* m_pAssetsEditor;
		CContextMenu* m_pContextMenu;
		int m_PackageId;
		
	protected:
		virtual void MouseClickAction()
		{
			AssetsManager()->ClosePackage(m_PackageId);
			m_pContextMenu->Close();
		}

	public:
		CCloseButton(CGuiEditor* pAssetsEditor, CContextMenu* pContextMenu, int PackageId) :
			gui::CButton(pAssetsEditor, "Close"),
			m_pAssetsEditor(pAssetsEditor),
			m_pContextMenu(pContextMenu),
			m_PackageId(PackageId)
		{
			SetButtonStyle(m_pAssetsEditor->m_Path_Button_Toolbar);
		}
	};

protected:
	CGuiEditor* m_pAssetsEditor;
	int m_PackageId;
	
protected:
	virtual void MouseClickAction()
	{
		m_pAssetsEditor->SetEditedPackage(m_PackageId);
	}

public:
	CPackageItem(CGuiEditor* pAssetsEditor, int PackageId) :
		gui::CButton(pAssetsEditor, "", CAssetPath::Null()),
		m_pAssetsEditor(pAssetsEditor),
		m_PackageId(PackageId)
	{
		SetButtonStyle(m_pAssetsEditor->m_Path_Button_ListItem);
		SetIcon(m_pAssetsEditor->m_Path_Sprite_IconFolder);
	}
	
	virtual void Update(bool ParentEnabled)
	{
		SetText(AssetsManager()->GetPackageName(m_PackageId));
		
		if(m_pAssetsEditor->GetEditedPackageId() == m_PackageId)
			SetButtonStyle(m_pAssetsEditor->m_Path_Button_ListItemHL);
		else
			SetButtonStyle(m_pAssetsEditor->m_Path_Button_ListItem);
		
		gui::CButton::Update(ParentEnabled);
	}
	
	virtual void OnButtonClick(int Button)
	{
		if(Button == KEY_MOUSE_2)
		{
			if(m_DrawRect.IsInside(Context()->GetMousePos()))
			{
				CContextMenu* pMenu = new CContextMenu(m_pAssetsEditor);
			
				pMenu->List()->Add(new CCloseButton(m_pAssetsEditor, pMenu, m_PackageId));
				
				m_pAssetsEditor->DisplayPopup(pMenu);
				return;
			}
		}
		
		gui::CButton::OnButtonClick(Button);
	}
};

/* INACTIVE ITEM ******************************************************/

class CInactiveText : public gui::CLabel
{
public:
	CInactiveText(CGuiEditor* pAssetsEditor, const char* pText, const CAssetPath& IconPath) :
		gui::CLabel(pAssetsEditor, pText, IconPath)
	{
		SetLabelStyle(pAssetsEditor->m_Path_Label_InactiveListItem);
	}
};

class CInactiveItem : public gui::CLabel
{
protected:
	CGuiEditor* m_pAssetsEditor;
	CAssetPath m_AssetPath;
	CSubPath m_SubPath;

public:
	CInactiveItem(CGuiEditor* pAssetsEditor, CAssetPath AssetPath, CSubPath SubPath) :
		gui::CLabel(pAssetsEditor, "", CAssetPath::Null()),
		m_pAssetsEditor(pAssetsEditor),
		m_AssetPath(AssetPath),
		m_SubPath(SubPath)
	{
		SetLabelStyle(m_pAssetsEditor->m_Path_Label_InactiveListItem);
		SetIcon(m_pAssetsEditor->GetItemIcon(m_AssetPath, m_SubPath));
	}
	
	virtual void Update(bool ParentEnabled)
	{
		SetText(m_pAssetsEditor->GetItemName(m_AssetPath, m_SubPath));
		
		gui::CLabel::Update(ParentEnabled);
	}
};

/* ITEM ***************************************************************/

class CItem : public gui::CHListLayout
{
protected:
	class CDeleteButton : public gui::CButton
	{
	protected:
		CGuiEditor* m_pAssetsEditor;
		CContextMenu* m_pContextMenu;
		CAssetPath m_AssetPath;
		
	protected:
		virtual void MouseClickAction()
		{
			AssetsManager()->DeleteAsset(m_AssetPath);
			m_pAssetsEditor->SetEditedAsset(CAssetPath::Null(), CSubPath::Null());
			m_pAssetsEditor->RefreshAssetsTree();
			m_pContextMenu->Close();
		}

	public:
		CDeleteButton(CGuiEditor* pAssetsEditor, CContextMenu* pContextMenu, const CAssetPath& AssetPath) :
			gui::CButton(pAssetsEditor, "Delete"),
			m_pAssetsEditor(pAssetsEditor),
			m_pContextMenu(pContextMenu),
			m_AssetPath(AssetPath)
		{
			SetButtonStyle(m_pAssetsEditor->m_Path_Button_Toolbar);
		}
	};
	
	class CViewButton : public gui::CButton
	{
	protected:
		CGuiEditor* m_pAssetsEditor;
		CAssetPath m_AssetPath;
	
	protected:
		virtual void MouseClickAction()
		{
			CAssetState* pState = AssetsManager()->GetAssetState(m_AssetPath);
			if(pState)
				pState->m_Visible = !pState->m_Visible;
		}

	public:
		CViewButton(CGuiEditor* pAssetsEditor, const CAssetPath& AssetPath) :
			gui::CButton(pAssetsEditor, "", pAssetsEditor->m_Path_Sprite_IconView),
			m_pAssetsEditor(pAssetsEditor),
			m_AssetPath(AssetPath)
		{
			
		}
	
		virtual void Update(bool ParentEnabled)
		{
			CAssetState* pState = AssetsManager()->GetAssetState(m_AssetPath);
			if(pState && pState->m_Visible)
				SetIcon(m_pAssetsEditor->m_Path_Sprite_IconView);
			else
				SetIcon(m_pAssetsEditor->m_Path_Sprite_IconHidden);
			
			gui::CButton::Update(ParentEnabled);
		}
	};
	
	class CTitleButton : public gui::CButton
	{
	protected:
		CGuiEditor* m_pAssetsEditor;
		CAssetPath m_AssetPath;
		CSubPath m_SubPath;
	
	protected:
		virtual void MouseClickAction()
		{
			m_pAssetsEditor->SetEditedAsset(m_AssetPath, m_SubPath);
		}

	public:
		CTitleButton(CGuiEditor* pAssetsEditor, const CAssetPath& AssetPath, CSubPath SubPath) :
			gui::CButton(pAssetsEditor, ""),
			m_pAssetsEditor(pAssetsEditor),
			m_AssetPath(AssetPath),
			m_SubPath(SubPath)
		{
			
		}
	
		virtual void Update(bool ParentEnabled)
		{
			SetIcon(m_pAssetsEditor->GetItemIcon(m_AssetPath, m_SubPath));
			SetText(m_pAssetsEditor->GetItemName(m_AssetPath, m_SubPath));
			
			if(m_pAssetsEditor->GetEditedAssetPath() == m_AssetPath)
				SetButtonStyle(m_pAssetsEditor->m_Path_Button_ListItemHL);
			else
				SetButtonStyle(m_pAssetsEditor->m_Path_Button_ListItem);
			
			gui::CButton::Update(ParentEnabled);
		}
	};
	
protected:
	CGuiEditor* m_pAssetsEditor;
	CAssetPath m_AssetPath;
	CSubPath m_SubPath;
	
protected:
	virtual void MouseClickAction()
	{
		m_pAssetsEditor->SetEditedAsset(m_AssetPath, m_SubPath);
	}

public:
	CItem(CGuiEditor* pAssetsEditor, CAssetPath AssetPath, CSubPath SubPath) :
		gui::CHListLayout(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_AssetPath(AssetPath),
		m_SubPath(SubPath)
	{
		CAssetState* pState = AssetsManager()->GetAssetState(m_AssetPath);
		if(pState)
			pState->m_ListedInEditor = true;
		
		Add(new CTitleButton(m_pAssetsEditor, AssetPath, SubPath), true);
		Add(new CViewButton(m_pAssetsEditor, AssetPath), false);
	}
	
	virtual void OnButtonClick(int Button)
	{
		if(Button == KEY_MOUSE_2)
		{
			if(m_DrawRect.IsInside(Context()->GetMousePos()))
			{
				CContextMenu* pMenu = new CContextMenu(m_pAssetsEditor);
			
				pMenu->List()->Add(new CDeleteButton(m_pAssetsEditor, pMenu, m_AssetPath));
				
				m_pAssetsEditor->DisplayPopup(pMenu);
				return;
			}
		}
		
		gui::CHListLayout::OnButtonClick(Button);
	}
};

/* IMAGE ITEM *********************************************************/

class CImageItem : public gui::CExpand
{
protected:
	CGuiEditor* m_pAssetsEditor;
	CAssetPath m_AssetPath;
	int m_PackageId;
	bool m_PackageIdFound;

public:
	CImageItem(CGuiEditor* pAssetsEditor, CAssetPath AssetPath, int PackageId) :
		gui::CExpand(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_PackageId(PackageId),
		m_AssetPath(AssetPath),
		m_PackageIdFound(false)
	{
		if(m_PackageId == m_AssetPath.GetPackageId())
			SetTitle(new CItem(m_pAssetsEditor, m_AssetPath, CSubPath::Null()));
		else
			SetTitle(new CInactiveItem(m_pAssetsEditor, m_AssetPath, CSubPath::Null()));
		
		for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_Sprite>(m_PackageId); i++)
		{
			CAssetPath SpritePath = CAssetPath(CAsset_Sprite::TypeId, m_PackageId, i);
			CAssetPath ImagePath = AssetsManager()->GetAssetValue<CAssetPath>(SpritePath, CSubPath::Null(), CAsset_Sprite::IMAGEPATH, CAssetPath::Null());
			if(ImagePath == m_AssetPath)
			{
				Add(new CItem(m_pAssetsEditor, SpritePath, CSubPath::Null()));
				m_PackageIdFound = true;
			}
		}
	}
	
	bool PackageIdFound()
	{
		return m_PackageIdFound || (m_AssetPath.GetPackageId() == m_PackageId);
	}
};

/* SKELETON ITEM ******************************************************/

class CSkeletonItem : public gui::CExpand
{
protected:
	CGuiEditor* m_pAssetsEditor;
	CAssetPath m_AssetPath;
	int m_PackageId;
	bool m_PackageIdFound;

public:
	CSkeletonItem(CGuiEditor* pAssetsEditor, CAssetPath AssetPath, int PackageId) :
		gui::CExpand(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_PackageId(PackageId),
		m_AssetPath(AssetPath),
		m_PackageIdFound(false)
	{
		if(m_PackageId == m_AssetPath.GetPackageId())
			SetTitle(new CItem(m_pAssetsEditor, m_AssetPath, CSubPath::Null()));
		else
			SetTitle(new CInactiveItem(m_pAssetsEditor, m_AssetPath, CSubPath::Null()));
		
		Clear();
		
		for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_SkeletonAnimation>(m_PackageId); i++)
		{
			CAssetPath Path = CAssetPath(CAsset_SkeletonAnimation::TypeId, m_PackageId, i);
			CAssetPath SkeletonPath = AssetsManager()->GetAssetValue<CAssetPath>(Path, CSubPath::Null(), CAsset_SkeletonAnimation::SKELETONPATH, CAssetPath::Null());
			if(SkeletonPath == m_AssetPath)
			{
				Add(new CItem(m_pAssetsEditor, Path, CSubPath::Null()));
				m_PackageIdFound = true;
			}
		}
		for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_SkeletonSkin>(m_PackageId); i++)
		{
			CAssetPath Path = CAssetPath(CAsset_SkeletonSkin::TypeId, m_PackageId, i);
			CAssetPath SkeletonPath = AssetsManager()->GetAssetValue<CAssetPath>(Path, CSubPath::Null(), CAsset_SkeletonSkin::SKELETONPATH, CAssetPath::Null());
			if(SkeletonPath == m_AssetPath)
			{
				Add(new CItem(m_pAssetsEditor, Path, CSubPath::Null()));
				m_PackageIdFound = true;
			}
		}
	}
	
	bool PackageIdFound()
	{
		return m_PackageIdFound || (m_AssetPath.GetPackageId() == m_PackageId);
	}
};

/* CHARACTER ITEM *****************************************************/

class CCharacterPartItem : public gui::CExpand
{
protected:
	CGuiEditor* m_pAssetsEditor;
	CAssetPath m_AssetPath;
	CSubPath m_SubPath;
	int m_PackageId;
	bool m_PackageIdFound;

public:
	CCharacterPartItem(CGuiEditor* pAssetsEditor, CAssetPath AssetPath, CSubPath SubPath, int PackageId) :
		gui::CExpand(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_PackageId(PackageId),
		m_AssetPath(AssetPath),
		m_SubPath(SubPath),
		m_PackageIdFound(false)
	{
		if(m_PackageId == m_AssetPath.GetPackageId())
			SetTitle(new CItem(m_pAssetsEditor, m_AssetPath, m_SubPath));
		else
			SetTitle(new CInactiveItem(m_pAssetsEditor, m_AssetPath, m_SubPath));
		
		Clear();
		
		for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_SkeletonSkin>(m_PackageId); i++)
		{
			CAssetPath Path = CAssetPath(CAsset_CharacterPart::TypeId, m_PackageId, i);
			CAssetPath CharacterPath = AssetsManager()->GetAssetValue<CAssetPath>(Path, CSubPath::Null(), CAsset_CharacterPart::CHARACTERPATH, CAssetPath::Null());
			CSubPath CharacterPart = AssetsManager()->GetAssetValue<CSubPath>(Path, CSubPath::Null(), CAsset_CharacterPart::CHARACTERPART, CSubPath::Null());
			if(CharacterPath == m_AssetPath && CharacterPart == m_SubPath)
			{
				Add(new CItem(m_pAssetsEditor, Path, CSubPath::Null()));
				m_PackageIdFound = true;
			}
		}
	}
	
	bool PackageIdFound()
	{
		return m_PackageIdFound || (m_AssetPath.GetPackageId() == m_PackageId);
	}
};

class CCharacterItem : public gui::CExpand
{
protected:
	CGuiEditor* m_pAssetsEditor;
	CAssetPath m_AssetPath;
	int m_PackageId;
	bool m_PackageIdFound;

public:
	CCharacterItem(CGuiEditor* pAssetsEditor, CAssetPath AssetPath, int PackageId) :
		gui::CExpand(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_PackageId(PackageId),
		m_AssetPath(AssetPath),
		m_PackageIdFound(false)
	{
		if(m_PackageId == m_AssetPath.GetPackageId())
			SetTitle(new CItem(m_pAssetsEditor, m_AssetPath, CSubPath::Null()));
		else
			SetTitle(new CInactiveItem(m_pAssetsEditor, m_AssetPath, CSubPath::Null()));
		
		Clear();
		
		const CAsset_Character* pCharacter = AssetsManager()->GetAsset<CAsset_Character>(m_AssetPath);
		if(pCharacter)
		{
			CAsset_Character::CIteratorPart Iter;
			for(Iter = pCharacter->BeginPart(); Iter != pCharacter->EndPart(); ++Iter)
			{
				CCharacterPartItem* pItem = new CCharacterPartItem(m_pAssetsEditor, m_AssetPath, *Iter, m_PackageId);
				
				if(pItem->PackageIdFound())
				{
					Add(pItem);
					m_PackageIdFound = true;
				}
				else
					delete pItem;
			}
		}
		for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_Weapon>(m_PackageId); i++)
		{
			CAssetPath Path = CAssetPath(CAsset_Weapon::TypeId, m_PackageId, i);
			CAssetPath CharacterPath = AssetsManager()->GetAssetValue<CAssetPath>(Path, CSubPath::Null(), CAsset_Weapon::CHARACTERPATH, CAssetPath::Null());
			if(CharacterPath == m_AssetPath)
			{
				Add(new CItem(m_pAssetsEditor, Path, CSubPath::Null()));
				m_PackageIdFound = true;
			}
		}
	}
	
	bool PackageIdFound()
	{
		return m_PackageIdFound || (m_AssetPath.GetPackageId() == m_PackageId);
	}
};

/* MAPGROUP ITEM ******************************************************/

class CMapGroupItem : public gui::CExpand
{
protected:
	CGuiEditor* m_pAssetsEditor;
	CAssetPath m_AssetPath;
	int m_PackageId;
	bool m_PackageIdFound;

public:
	CMapGroupItem(CGuiEditor* pAssetsEditor, CAssetPath AssetPath, int PackageId) :
		gui::CExpand(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_PackageId(PackageId),
		m_AssetPath(AssetPath),
		m_PackageIdFound(false)
	{
		if(m_PackageId == m_AssetPath.GetPackageId())
			SetTitle(new CItem(m_pAssetsEditor, m_AssetPath, CSubPath::Null()));
		else
			SetTitle(new CInactiveItem(m_pAssetsEditor, m_AssetPath, CSubPath::Null()));
		
		Clear();
		
		const CAsset_MapGroup* pMapGroup = AssetsManager()->GetAsset<CAsset_MapGroup>(m_AssetPath);
		if(pMapGroup)
		{
			CAsset_MapGroup::CIteratorLayer IterLayer;
			for(IterLayer = pMapGroup->BeginLayer(); IterLayer != pMapGroup->EndLayer(); ++IterLayer)
			{
				CAssetPath Child = pMapGroup->GetLayer(*IterLayer);
				if(Child.GetPackageId() == m_PackageId)
				{
					Add(new CItem(m_pAssetsEditor, Child, CSubPath::Null()));
					m_PackageIdFound = true;
				}
			}
		}
		
	}
	
	bool PackageIdFound()
	{
		return m_PackageIdFound || (m_AssetPath.GetPackageId() == m_PackageId);
	}
};


/* MAP ITEM ***********************************************************/

class CMapItem : public gui::CExpand
{
protected:
	CGuiEditor* m_pAssetsEditor;
	CAssetPath m_AssetPath;
	int m_PackageId;
	bool m_PackageIdFound;

public:
	CMapItem(CGuiEditor* pAssetsEditor, CAssetPath AssetPath, int PackageId) :
		gui::CExpand(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_PackageId(PackageId),
		m_AssetPath(AssetPath),
		m_PackageIdFound(false)
	{
		gui::CExpand* pZoneExpand = new gui::CExpand(Context());
		gui::CExpand* pBgExpand = new gui::CExpand(Context());
		gui::CExpand* pFgExpand = new gui::CExpand(Context());
		
		pZoneExpand->SetTitle(new CInactiveText(m_pAssetsEditor, "Zones", m_pAssetsEditor->m_Path_Sprite_IconNone));
		pBgExpand->SetTitle(new CInactiveText(m_pAssetsEditor, "Background Layers", m_pAssetsEditor->m_Path_Sprite_IconNone));
		pFgExpand->SetTitle(new CInactiveText(m_pAssetsEditor, "Foreground Layers", m_pAssetsEditor->m_Path_Sprite_IconNone));
		
		Add(pZoneExpand);
		Add(pBgExpand);
		Add(pFgExpand);
		
		if(m_PackageId == m_AssetPath.GetPackageId())
			SetTitle(new CItem(m_pAssetsEditor, m_AssetPath, CSubPath::Null()));
		else
			SetTitle(new CInactiveItem(m_pAssetsEditor, m_AssetPath, CSubPath::Null()));
		
		const CAsset_Map* pMap = AssetsManager()->GetAsset<CAsset_Map>(m_AssetPath);
		if(pMap)
		{
			CAsset_Map::CIteratorZoneLayer IterZoneLayer;
			for(IterZoneLayer = pMap->BeginZoneLayer(); IterZoneLayer != pMap->EndZoneLayer(); ++IterZoneLayer)
			{
				CAssetPath Child = pMap->GetZoneLayer(*IterZoneLayer);
				if(Child.GetPackageId() == m_PackageId)
				{
					pZoneExpand->Add(new CItem(m_pAssetsEditor, Child, CSubPath::Null()));
					m_PackageIdFound = true;
				}
			}
			
			CAsset_Map::CIteratorBgGroup IterBgGroup;
			for(IterBgGroup = pMap->BeginBgGroup(); IterBgGroup != pMap->EndBgGroup(); ++IterBgGroup)
			{
				CAssetPath Child = pMap->GetBgGroup(*IterBgGroup);
				if(Child.GetPackageId() == m_PackageId)
				{
					pBgExpand->Add(new CMapGroupItem(m_pAssetsEditor, Child, m_PackageId));
					m_PackageIdFound = true;
				}
			}
			
			CAsset_Map::CIteratorFgGroup IterFgGroup;
			for(IterFgGroup = pMap->BeginFgGroup(); IterFgGroup != pMap->EndFgGroup(); ++IterFgGroup)
			{
				CAssetPath Child = pMap->GetFgGroup(*IterFgGroup);
				if(Child.GetPackageId() == m_PackageId)
				{
					pFgExpand->Add(new CMapGroupItem(m_pAssetsEditor, Child, m_PackageId));
					m_PackageIdFound = true;
				}
			}
		}
	}
	
	bool PackageIdFound()
	{
		return m_PackageIdFound || (m_AssetPath.GetPackageId() == m_PackageId);
	}
};

/* PACKAGES TREE ******************************************************/

CPackagesTree::CPackagesTree(CAssetsOrganizer* pAssetsOrganizer) :
	gui::CVScrollLayout(pAssetsOrganizer->AssetsEditor()),
	m_pAssetsOrganizer(pAssetsOrganizer),
	m_pAssetsEditor(pAssetsOrganizer->AssetsEditor()),
	m_NumPackages(0)
{
	SetBoxStyle(AssetsEditor()->m_Path_Box_Panel);
	Refresh();
}

void CPackagesTree::Update(bool ParentEnabled)
{
	int NumValidPackages = 0;
	for(int i=0; i<AssetsManager()->GetNumPackages(); i++)
	{
		if(AssetsManager()->IsValidPackage(i))
			NumValidPackages++;
	}
	
	if(m_NumPackages != NumValidPackages)
	{
		m_NumPackages = NumValidPackages;
		Refresh();
	}
	
	gui::CVScrollLayout::Update(ParentEnabled);
}

void CPackagesTree::Refresh()
{
	Clear();
	
	gui::CExpand* pWriteExpand = new gui::CExpand(Context());
	gui::CExpand* pReadExpand = new gui::CExpand(Context());
	
	pWriteExpand->SetTitle(new CInactiveText(m_pAssetsEditor, "Edited Packages", m_pAssetsEditor->m_Path_Sprite_IconNone));
	pReadExpand->SetTitle(new CInactiveText(m_pAssetsEditor, "Read-Only Packages", m_pAssetsEditor->m_Path_Sprite_IconNone));
	
	Add(pWriteExpand);
	Add(pReadExpand);
	
	for(int i=0; i<AssetsManager()->GetNumPackages(); i++)
	{
		if(AssetsManager()->IsValidPackage(i))
		{
			if(AssetsManager()->IsReadOnlyPackage(i))
				pReadExpand->Add(new CPackageItem(AssetsEditor(), i));
			else
				pWriteExpand->Add(new CPackageItem(AssetsEditor(), i));
		}
	}
}


/* ASSETS TREE ********************************************************/

CAssetsTree::CAssetsTree(CAssetsOrganizer* pAssetsOrganizer) :
	gui::CVScrollLayout(pAssetsOrganizer->AssetsEditor()),
	m_pAssetsOrganizer(pAssetsOrganizer),
	m_pAssetsEditor(pAssetsOrganizer->AssetsEditor()),
	m_PackageId(0)
{
	SetBoxStyle(AssetsEditor()->m_Path_Box_Panel);
}

void CAssetsTree::Update(bool ParentEnabled)
{
	if(m_PackageId != AssetsEditor()->GetEditedPackageId())
	{
		m_PackageId = AssetsEditor()->GetEditedPackageId();
		Refresh();
	}
	
	gui::CVScrollLayout::Update(ParentEnabled);
}

void CAssetsTree::Refresh()
{
	Clear();
	
	{
		CAssetState State;
		State.m_ListedInEditor = false;
		AssetsManager()->InitAssetState(m_PackageId, State);
	}
	
	#define REFRESH_ASSET_LIST(ClassName) {\
		for(int i=0; i<AssetsManager()->GetNumAssets<ClassName>(m_PackageId); i++)\
		{\
			CAssetPath Path = CAssetPath(ClassName::TypeId, m_PackageId, i);\
			CAssetState* pState = AssetsManager()->GetAssetState(Path);\
			if(pState && !pState->m_ListedInEditor)\
			{\
				Add(new CItem(AssetsEditor(), Path, CSubPath::Null()));\
			}\
		}\
	}
	
	//Images
	//	Sprites
	for(int s=0; s<AssetsManager()->GetNumPackages(); s++)
	{
		for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_Image>(s); i++)
		{
			CAssetPath Path = CAssetPath(CAsset_Image::TypeId, s, i);
			CImageItem* pItem = new CImageItem(AssetsEditor(), Path, m_PackageId);
			if(pItem->PackageIdFound())
				Add(pItem);
			else
				delete pItem;
		}
	}
	
	REFRESH_ASSET_LIST(CAsset_Sprite)
	
	//Maps
	for(int s=0; s<AssetsManager()->GetNumPackages(); s++)
	{
		for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_Map>(s); i++)
		{
			CAssetPath Path = CAssetPath(CAsset_Map::TypeId, s, i);
			CMapItem* pItem = new CMapItem(AssetsEditor(), Path, m_PackageId);
			if(pItem->PackageIdFound())
				Add(pItem);
			else
				delete pItem;
		}
	}
	
	REFRESH_ASSET_LIST(CAsset_MapGroup)
	REFRESH_ASSET_LIST(CAsset_MapLayerTiles)
	REFRESH_ASSET_LIST(CAsset_MapLayerQuads)
	REFRESH_ASSET_LIST(CAsset_MapZoneTiles)
	REFRESH_ASSET_LIST(CAsset_ZoneType)
	
	//Skeletons
	//	SkeletonAnimations
	//	SkeletonSkins
	for(int s=0; s<AssetsManager()->GetNumPackages(); s++)
	{
		for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_Skeleton>(s); i++)
		{
			CAssetPath Path = CAssetPath(CAsset_Skeleton::TypeId, s, i);
			CSkeletonItem* pItem = new CSkeletonItem(AssetsEditor(), Path, m_PackageId);
			if(pItem->PackageIdFound())
				Add(pItem);
			else
				delete pItem;
		}
	}
	
	REFRESH_ASSET_LIST(CAsset_SkeletonAnimation)
	REFRESH_ASSET_LIST(CAsset_SkeletonSkin)
	
	//Charaters
	//	CharacterParts
	//	Weapons
	for(int s=0; s<AssetsManager()->GetNumPackages(); s++)
	{
		for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_Character>(s); i++)
		{
			CAssetPath Path = CAssetPath(CAsset_Character::TypeId, s, i);
			CCharacterItem* pItem = new CCharacterItem(AssetsEditor(), Path, m_PackageId);
			if(pItem->PackageIdFound())
				Add(pItem);
			else
				delete pItem;
		}
	}
	
	REFRESH_ASSET_LIST(CAsset_CharacterPart)
	
	REFRESH_ASSET_LIST(CAsset_GuiRectStyle)
	REFRESH_ASSET_LIST(CAsset_GuiLineStyle)
	REFRESH_ASSET_LIST(CAsset_GuiBoxStyle)
	REFRESH_ASSET_LIST(CAsset_GuiLabelStyle)
	REFRESH_ASSET_LIST(CAsset_GuiButtonStyle)
	REFRESH_ASSET_LIST(CAsset_GuiIntEditStyle)
	REFRESH_ASSET_LIST(CAsset_GuiColorEditStyle)
	REFRESH_ASSET_LIST(CAsset_GuiToggleStyle)
	REFRESH_ASSET_LIST(CAsset_GuiScrollbarStyle)
	REFRESH_ASSET_LIST(CAsset_GuiTabsStyle)
}

/* ASSETS LIST ********************************************************/

CAssetsOrganizer::CAssetsOrganizer(CGuiEditor* pAssetsEditor) :
	gui::CVPanelLayout(pAssetsEditor),
	m_pAssetsEditor(pAssetsEditor)
{
	m_pPackagesTree = new CPackagesTree(this);
	Add(m_pPackagesTree, 200);
	
	m_pAssetsTree = new CAssetsTree(this);
	m_pAssetsEditor->m_pAssetsTree = m_pAssetsTree;
	Add(m_pAssetsTree, -1);
}
