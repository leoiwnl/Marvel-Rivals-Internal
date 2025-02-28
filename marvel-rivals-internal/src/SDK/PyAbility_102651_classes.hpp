﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: PyAbility_102651

#include "Basic.hpp"

#include "Marvel_structs.hpp"
#include "Marvel_classes.hpp"


namespace SDK
{

// PythonClass PyAbility_102651.PyAbility_102651
// 0x0000 (0x2588 - 0x2588)
class UPyAbility_102651 : public UAbility_108
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"PyAbility_102651">();
	}
	static class UPyAbility_102651* GetDefaultObj()
	{
		return GetDefaultObjImpl<UPyAbility_102651>();
	}
};

// PythonClass PyAbility_102651.PyProjectile_10265101
// 0x0FA0 (0x3FF0 - 0x3050)
class APyProjectile_10265101 : public AMarvelAbilityTargetActor_Projectile
{
public:
	int32                                         ScopeId;                                           // 0x3050(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Offset;                                            // 0x3054(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_3058[0x8];                                     // 0x3058(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	struct FMarvelAbilityTraceContext             TraceContext;                                      // 0x3060(0x0F90)(Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance, NativeAccessSpecifierPublic)

public:
	void K2_OnBeginAgentTask();
	void K2_OnProcessHit(const struct FHitResult& Hit);
	void K2_OnEndAgentTask();

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"PyProjectile_10265101">();
	}
	static class APyProjectile_10265101* GetDefaultObj()
	{
		return GetDefaultObjImpl<APyProjectile_10265101>();
	}
};

// PythonClass PyAbility_102651.PyCue_Scope_Start_10265101
// 0x0010 (0x0378 - 0x0368)
class UPyCue_Scope_Start_10265101 final : public UMarvelCueNotify_Base
{
public:
	float                                         Scale;                                             // 0x0368(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_36C[0x4];                                      // 0x036C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UFXSystemAsset*                         FXSphere;                                          // 0x0370(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)

public:
	void OnExecuteFX(class AActor* MyTarget, const struct FGameplayCueParameters& Parameters) const;

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"PyCue_Scope_Start_10265101">();
	}
	static class UPyCue_Scope_Start_10265101* GetDefaultObj()
	{
		return GetDefaultObjImpl<UPyCue_Scope_Start_10265101>();
	}
};

// PythonClass PyAbility_102651.PyUIController_102651
// 0x0000 (0x0C60 - 0x0C60)
class UPyUIController_102651 final : public UUIC_Ability
{
public:
	void OnInit();

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"PyUIController_102651">();
	}
	static class UPyUIController_102651* GetDefaultObj()
	{
		return GetDefaultObjImpl<UPyUIController_102651>();
	}
};

}

