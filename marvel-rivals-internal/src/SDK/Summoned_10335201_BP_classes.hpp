﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: Summoned_10335201_BP

#include "Basic.hpp"

#include "PyAbility_103352_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass Summoned_10335201_BP.Summoned_10335201_BP_C
// 0x0010 (0x08B0 - 0x08A0)
class ASummoned_10335201_BP_C final : public APySummoned_10335201
{
public:
	class USummonedAbilitySystemComponent*        SummonedAbilitySystem;                             // 0x0898(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USummonedMovementComponent*             SummonedMovement;                                  // 0x08A0(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"Summoned_10335201_BP_C">();
	}
	static class ASummoned_10335201_BP_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<ASummoned_10335201_BP_C>();
	}
};

}

