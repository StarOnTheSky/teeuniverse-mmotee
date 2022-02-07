/*
 * Copyright (C) 2016 necropotame (necropotame@gmail.com)
 * 
 * This file is part of TeeUniverse.
 * 
 * TeeUniverse is free software: you can redistribute it and/or  modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * TeeUniverse is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with TeeUniverse.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <shared/system/debug.h>
#include <shared/system/string.h>
#include <shared/kernel.h>
#include <shared/components/assetsmanager.h>
#include <shared/components/storage.h>
#include <client/loading_tools.h>

#include <cstdlib>

#define CREATE_SPRITE_PATH(path, packageid, name, image, x, y, w, h) {\
	CAsset_Sprite* pSprite = pKernel->AssetsManager()->NewAsset_Hard<CAsset_Sprite>(&path, packageid);\
	pSprite->SetName(name);\
	pSprite->SetImagePath(image);\
	pSprite->SetX(x);\
	pSprite->SetY(y);\
	pSprite->SetWidth(w);\
	pSprite->SetHeight(h);\
}

int main(int argc, char* argv[])
{
	{
		std::unique_ptr<CSharedKernel> pKernel(new CSharedKernel());
		
		if(!pKernel->Init(argc, (const char**) argv))
		{
			debug::ErrorStream("Kernel") << "unable to initialize shared kernel" << std::endl;
			exit(EXIT_FAILURE);
		}
		
		int PackageId = -1;
		
		PackageId = pKernel->AssetsManager()->NewPackage("mmotee");
		pKernel->AssetsManager()->SetPackageAuthor(PackageId, "Kurosio");
		pKernel->AssetsManager()->SetPackageLicense(PackageId, "CC-BY-SA 3.0");
		pKernel->AssetsManager()->SetPackageVersion(PackageId, "0.0.2");
		
		CAssetPath ImageZonesDamagePath = CreateNewImage(pKernel.get(), PackageId, "damage", "images/univ_infclass/damage.png", CStorage::TYPE_ALL, 16, 16, true, 0);
		CAssetPath ImageZonesTeleportationPath = CreateNewImage(pKernel.get(), PackageId, "teleportation", "images/univ_infclass/teleportation.png", CStorage::TYPE_ALL, 16, 16, true, 0);
		CAssetPath ImageZonesBonusPath = CreateNewImage(pKernel.get(), PackageId, "bonus", "images/univ_infclass/bonus.png", CStorage::TYPE_ALL, 16, 16, true, 0);
		CAssetPath ImageEntitiesPath = CreateNewImage(pKernel.get(), PackageId, "entities", "images/univ_infclass/entities.png", CStorage::TYPE_ALL, 4, 4, true, 0);
		pKernel->AssetsManager()->SetAssetValue_Hard<>(ImageEntitiesPath, CSubPath::Null(), CAsset_Image::TEXELSIZE, 768);
			
		//Zone, damage
		{
			CAssetPath AssetPath;
			CSubPath SubPath;
			
			CAsset_ZoneType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_ZoneType>(&AssetPath, PackageId);
			pAsset->SetName("icDamage");
			pAsset->SetImagePath(ImageZonesDamagePath);
			
			int GroupId_Death = pAsset->AddGroup();
			int GroupId_State = pAsset->AddGroup();
			
			pAsset->SetGroup(CAsset_ZoneType::SubPath_Group(GroupId_Death), "Death");
			pAsset->SetGroup(CAsset_ZoneType::SubPath_Group(GroupId_State), "State change");
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "No damage");
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Death zone");
			pAsset->SetIndexDescription(SubPath, "Any player touching this zone dies instantly");
			pAsset->SetIndexBorderIndex(SubPath, 1);
			pAsset->SetIndexBorderColor(SubPath, vec4(1.0f, 0.0f, 0.0f, 1.0f));
			pAsset->SetIndexGroup(SubPath, GroupId_Death);
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Death zone (non-undead only)");
			pAsset->SetIndexDescription(SubPath, "Any player touching this zone, that is not an undead, dies instantly");
			pAsset->SetIndexBorderIndex(SubPath, 1);
			pAsset->SetIndexBorderColor(SubPath, vec4(1.0f, 164.0f/255.0f, 0.0f, 1.0f));
			pAsset->SetIndexGroup(SubPath, GroupId_Death);
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Death zone (infected only)");
			pAsset->SetIndexDescription(SubPath, "Any infected touching this zone dies instantly");
			pAsset->SetIndexBorderIndex(SubPath, 1);
			pAsset->SetIndexBorderColor(SubPath, vec4(157.0f/255.0f, 0.0f, 1.0f, 1.0f));
			pAsset->SetIndexGroup(SubPath, GroupId_Death);
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Infected area");
			pAsset->SetIndexDescription(SubPath, "Any human touching this zone is immediately infected");
			pAsset->SetIndexBorderIndex(SubPath, 2);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));
			pAsset->SetIndexGroup(SubPath, GroupId_State);
		}	
		//Zone, teleportation
		{
			CAssetPath AssetPath;
			CSubPath SubPath;
			
			CAsset_ZoneType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_ZoneType>(&AssetPath, PackageId);
			pAsset->SetName("icTele");
			pAsset->SetImagePath(ImageZonesTeleportationPath);
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "All accepted");
			pAsset->SetIndexDescription(SubPath, "Witches can spawn infected and scientist can be teleported in this zone");
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "No witch spawn");
			pAsset->SetIndexDescription(SubPath, "Witches can't spawn infected in this zone. This zone is nice to place over spikes and other dangerous parts of the map");
			pAsset->SetIndexBorderIndex(SubPath, 1);
			pAsset->SetIndexBorderColor(SubPath, vec4(1.0f, 0.0f, 0.0f, 1.0f));
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "No scientist teleport");
			pAsset->SetIndexDescription(SubPath, "Scientists can't be teleported in this zone");
			pAsset->SetIndexBorderIndex(SubPath, 2);
			pAsset->SetIndexBorderColor(SubPath, vec4(0.0f, 1.0f, 164.0f/255.0f, 1.0f));
		}
		//Zone, bonus
		{
			CAssetPath AssetPath;
			CSubPath SubPath;
			
			CAsset_ZoneType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_ZoneType>(&AssetPath, PackageId);
			pAsset->SetName("MMOTee区域");
			pAsset->SetImagePath(ImageZonesBonusPath);
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "无效果");
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Boss");
			pAsset->SetIndexDescription(SubPath, "Humans get +5 points each time they accumulated 60 seconds by staying inside this zone");
			pAsset->SetIndexBorderIndex(SubPath, 1);
			pAsset->SetIndexBorderColor(SubPath, vec4(148.0f/255.0f, 0.0f, 1.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "商店");
			pAsset->SetIndexDescription(SubPath, "进入此区域打开商店");
			pAsset->SetIndexBorderIndex(SubPath, 2);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "禁止PVP");
			pAsset->SetIndexDescription(SubPath, "进入此区域关闭PVP");
			pAsset->SetIndexBorderIndex(SubPath, 3);
			pAsset->SetIndexBorderColor(SubPath, vec4(148.0f/255.0f, 0.0f, 1.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "允许PVP");
			pAsset->SetIndexDescription(SubPath, "进入此区域开启PVP");
			pAsset->SetIndexBorderIndex(SubPath, 4);
			pAsset->SetIndexBorderColor(SubPath, vec4(148.0f/255.0f, 0.0f, 1.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "椅子-1");
			pAsset->SetIndexDescription(SubPath, "给与最少的奖励");
			pAsset->SetIndexBorderIndex(SubPath, 5);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "椅子-2");
			pAsset->SetIndexDescription(SubPath, "给与正常的奖励");
			pAsset->SetIndexBorderIndex(SubPath, 6);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "合成");
			pAsset->SetIndexDescription(SubPath, "进入此区域开始合成");
			pAsset->SetIndexBorderIndex(SubPath, 7);
			pAsset->SetIndexBorderColor(SubPath, vec4(1.0f, 164.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "游戏区");
			pAsset->SetIndexDescription(SubPath, "进入此区域加入游戏");
			pAsset->SetIndexBorderIndex(SubPath, 8);
			pAsset->SetIndexBorderColor(SubPath, vec4(1.0f, 164.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "白房间");
			pAsset->SetIndexDescription(SubPath, "进入此区域检查白名单");
			pAsset->SetIndexBorderIndex(SubPath, 9);
			pAsset->SetIndexBorderColor(SubPath, vec4(1.0f, 164.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "任务");
			pAsset->SetIndexDescription(SubPath, "任务区");
			pAsset->SetIndexBorderIndex(SubPath, 10);
			pAsset->SetIndexBorderColor(SubPath, vec4(1.0f, 164.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "水");
			pAsset->SetIndexDescription(SubPath, "水水水淼");
			pAsset->SetIndexBorderIndex(SubPath, 11);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "1号公会大门");
			pAsset->SetIndexDescription(SubPath, "1号公会大门");
			pAsset->SetIndexBorderIndex(SubPath, 12);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "2号公会大门");
			pAsset->SetIndexDescription(SubPath, "2号公会大门");
			pAsset->SetIndexBorderIndex(SubPath, 13);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "1号公会的椅子");
			pAsset->SetIndexDescription(SubPath, "1号公会的椅子");
			pAsset->SetIndexBorderIndex(SubPath, 14);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "2号公会椅子");
			pAsset->SetIndexDescription(SubPath, "2号公会的椅子");
			pAsset->SetIndexBorderIndex(SubPath, 15);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));
				
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "死亡区");
			pAsset->SetIndexDescription(SubPath, "让你死");
			pAsset->SetIndexBorderIndex(SubPath, 15);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "3号公会大门");
			pAsset->SetIndexDescription(SubPath, "关门时只让3号公会的人进入");
			pAsset->SetIndexBorderIndex(SubPath, 13);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "3号公会椅子");
			pAsset->SetIndexDescription(SubPath, "你不会不知道是什么吧？我懒得翻译了");
			pAsset->SetIndexBorderIndex(SubPath, 15);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));	
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "进入太空");
			pAsset->SetIndexDescription(SubPath, "进入太空");
			pAsset->SetIndexBorderIndex(SubPath, 19);
			pAsset->SetIndexBorderColor(SubPath, vec4(255.0f, 164.0f/255.0f, 9.0f, 218.0f));
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "离开太空");
			pAsset->SetIndexDescription(SubPath, "离开太空");
			pAsset->SetIndexBorderIndex(SubPath, 20);
			pAsset->SetIndexBorderColor(SubPath, vec4(255.0f, 164.0f/255.0f, 9.0f, 218.0f));

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "4号公会大门");
			pAsset->SetIndexDescription(SubPath, "关门时只让3号公会的人进入");
			pAsset->SetIndexBorderIndex(SubPath, 13);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "4号公会椅子");
			pAsset->SetIndexDescription(SubPath, "你不会不知道是什么吧？我懒得翻译了");
			pAsset->SetIndexBorderIndex(SubPath, 15);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));	

			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "5号公会大门");
			pAsset->SetIndexDescription(SubPath, "关门时只让3号公会的人进入");
			pAsset->SetIndexBorderIndex(SubPath, 13);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "5号公会椅子");
			pAsset->SetIndexDescription(SubPath, "你不会不知道是什么吧？我懒得翻译了");
			pAsset->SetIndexBorderIndex(SubPath, 15);
			pAsset->SetIndexBorderColor(SubPath, vec4(11.0f/255.0f, 173.0f/255.0f, 0.0f, 1.0f));	
		}
		//EntityType, No Register Spawn
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 0, 3, 1, 1);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("NoRegister");
			pAsset->SetCollisionRadius(64.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, Register
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 1, 3, 1, 1);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("Register");
			pAsset->SetCollisionRadius(64.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, Guard
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoBotSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("Guard");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, Bot1Type
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoBotSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("Bot1Type");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, Jail
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("Jail");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, Bot2Type
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoBotSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("Bot2Type");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, Bot3Type
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoBotSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("Bot3Type");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, WaitBoss
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("WaitBoss");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, BossSpawn
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoBotSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("BossSpawn");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, ArenaInsta
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("ArenaIns");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, NPCSHOP
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoBotSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("NPCSHOP");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, NPCWQUEST
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoBotSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("NPCWQUEST");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, NPCWCRAFT
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoBotSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("NPCWCRAFT");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, ArenaFng
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("ArenaFng");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, NPCFARMER
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoBotSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("NPCFARMER");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, FirstRegSpawn
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("FRSpawn");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, ClanSpawn1
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("ClanSp1");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//EntityType, ClanSpawn2
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("ClanSp2");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//ClanSpawn3
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("ClanSp3");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//ClanSpawn4
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("ClanSp4");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		//ClanSpawn5
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 3, 2, 1, 2);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("ClanSp5");
			pAsset->SetCollisionRadius(42.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		pKernel->AssetsManager()->Save_AssetsFile_SaveDir(PackageId);
		
		pKernel->Shutdown();
	}

	exit(EXIT_SUCCESS);
}