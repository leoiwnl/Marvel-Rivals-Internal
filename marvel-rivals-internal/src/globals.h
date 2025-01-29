#pragma once

namespace Globals
{
	SDK::APlayerController* MyController;
}

namespace Objects
{
	SDK::UFont* font;
	SDK::UFunction* drawtext;
}

namespace Keys
{
	SDK::FKey Insert;
	SDK::FKey F1;
	SDK::FKey F2;
	SDK::FKey F3;
	SDK::FKey F4;
	SDK::FKey F5;
	SDK::FKey Mouse1;
	SDK::FKey Mouse2;
	SDK::FKey LeftControl;
}

void LoadObjects()
{
	Objects::font = SDK::UObject::FindObject<SDK::UFont>("/Engine/EngineFonts/Roboto.Roboto");
	Objects::drawtext = SDK::UObject::FindObject<SDK::UFunction>("Function Engine.Canvas.K2_DrawText");

	Keys::Insert = SDK::FKey{ Custom::StrToName(L"Insert"), 0 };
	Keys::Mouse1 = SDK::FKey{ Custom::StrToName(L"LeftMouseButton"), 0 };
	Keys::Mouse2 = SDK::FKey{ Custom::StrToName(L"RightMouseButton"), 0 };
	Keys::LeftControl = SDK::FKey{ Custom::StrToName(L"LeftControl"), 0 };
}