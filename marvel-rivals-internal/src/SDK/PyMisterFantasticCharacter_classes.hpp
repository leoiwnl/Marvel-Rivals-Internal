﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: PyMisterFantasticCharacter

#include "Basic.hpp"

#include "Marvel_structs.hpp"
#include "Hero_1040_classes.hpp"
#include "Engine_structs.hpp"


namespace SDK
{

// PythonClass PyMisterFantasticCharacter.PyMisterFantasticCharacter
// 0x00B0 (0x1950 - 0x18A0)
class APyMisterFantasticCharacter : public AMisterFantasticCharacter
{
public:
	class UMarveSculptConfigComponent*            NormalSculptConfigComponent;                       // 0x18A0(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UMarveSculptConfigComponent*            ExpandSculptConfigComponent;                       // 0x18A8(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UMarveSculptConfigComponent*            WallSculptConfigComponent;                         // 0x18B0(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UMarveSculptConfigComponent*            JumpExpandSculptConfigComponent;                   // 0x18B8(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UMarveSculptConfigComponent*            DashExpandSculptConfigComponent;                   // 0x18C0(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FReplicateTimer                        ScheduleTimer;                                     // 0x18C8(0x0078)(BlueprintVisible, Net, NativeAccessSpecifierPublic)
	TMulticastInlineDelegate<void()>              ExpandTimerClearedDispatcher;                      // 0x1940(0x0010)(ZeroConstructor, InstancedReference, BlueprintAssignable, BlueprintCallable, NativeAccessSpecifierPublic)

public:
	void ReceiveBeginPlay();
	void ReceiveEndPlay(EEndPlayReason EndPlayReason);
	void OnHeroReviving(EPlayerLivingState State);
	void K2_ClearScheduleTimer();
	void OnScheduleTimeout();
	void OnPreDeath(class AController* InSource, class AActor* InSourceAvatar, const struct FAttributeModifierHandle& ModifierParameter);
	void OnReborn(const struct FCharacterRebornParam& RebornParameter);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"PyMisterFantasticCharacter">();
	}
	static class APyMisterFantasticCharacter* GetDefaultObj()
	{
		return GetDefaultObjImpl<APyMisterFantasticCharacter>();
	}
};

}

