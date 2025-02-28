﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: SocketSubsystemEOS

#include "Basic.hpp"

#include "OnlineSubsystemUtils_classes.hpp"


namespace SDK
{

// Class SocketSubsystemEOS.NetConnectionEOS
// 0x0010 (0x2250 - 0x2240)
class UNetConnectionEOS final : public UIpConnection
{
public:
	uint8                                         Pad_2240[0x10];                                    // 0x2240(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"NetConnectionEOS">();
	}
	static class UNetConnectionEOS* GetDefaultObj()
	{
		return GetDefaultObjImpl<UNetConnectionEOS>();
	}
};

// Class SocketSubsystemEOS.NetDriverEOSBase
// 0x0010 (0x0BA0 - 0x0B90)
class UNetDriverEOSBase : public UIpNetDriver
{
public:
	bool                                          bIsPassthrough;                                    // 0x0B90(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bIsUsingP2PSockets;                                // 0x0B91(0x0001)(ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_B92[0xE];                                      // 0x0B92(0x000E)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"NetDriverEOSBase">();
	}
	static class UNetDriverEOSBase* GetDefaultObj()
	{
		return GetDefaultObjImpl<UNetDriverEOSBase>();
	}
};

}

