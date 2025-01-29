#pragma once

namespace Custom
{
	void Text(SDK::UCanvas* Canvas, UC::FString text, SDK::FVector2D pos, SDK::FLinearColor colour)
	{
		//Canvas->K2_DrawText(Objects::font, text, pos, vars::font_scale, colour, 1.f, SDK::FLinearColor(0.f, 0.f, 0.f), SDK::FVector2D(1.f, 1.f), false, true, true, SDK::FLinearColor(0.f, 0.f, 0.f));
	}

	SDK::FName StrToName(std::wstring text)
	{
		return SDK::UKismetStringLibrary::Conv_StringToName(SDK::FString(text.c_str()));
	}

	void Circle(SDK::FVector2D pos, float thickness, SDK::FLinearColor colour)
	{
		auto Canvas = SDK::UObject::FindObject<SDK::UCanvas>("Engine.Canvas");
		if (!Canvas) return;
		printf("Found Canvas drawing line\n");
		Canvas->K2_DrawLine(pos, SDK::FVector2D(pos.X + 50, pos.Y), thickness, colour);
	}

	bool LineTraceSingle(SDK::AActor* localplayer, SDK::AActor* target, SDK::FVector Start, SDK::FVector End)
	{
		SDK::TArray<SDK::AActor*> actors;
		actors.Add(localplayer);
		actors.Add(target);
		SDK::FHitResult outhit;
		return SDK::UKismetSystemLibrary::LineTraceSingle(SDK::UWorld::GetWorld(), Start, End, SDK::ETraceTypeQuery::TraceTypeQuery3, true, actors, SDK::EDrawDebugTrace::None, &outhit, true, {0, 0, 0, 0}, {0, 0, 0, 0}, 0.f);
	}

}