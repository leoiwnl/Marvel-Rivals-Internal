#pragma once

using draw_transition_sim = void(*)(SDK::UGameViewportClient*, void*);
draw_transition_sim draw_transition_o = 0;

void DrawTransition(SDK::UGameViewportClient* ViewportClient, void* Useless)
{
	if (!ViewportClient || !Useless) return draw_transition_o(ViewportClient, Useless);

	//Draw::Text(Canvas, SDK::FString(L"leoiwnl internal"), SDK::FVector2D(10, 10), SDK::FLinearColor(0.5, 0, 0.5));
	
	auto world = ViewportClient->World;
	if (!world) return draw_transition_o(ViewportClient, Useless);

	auto Controller = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
	if (!Controller) return draw_transition_o(ViewportClient, Useless);

	//if (Controller->WasInputKeyJustPressed())
	Custom::Circle(SDK::FVector2D(100, 100), 50.f, SDK::FLinearColor(0.f, 0.f, 0.f, 1.f));

	auto players = world->GameState->PlayerArray;

	for (int i = 0; i < players.Num(); i++)
	{
		auto player = players[i];
		if (!player) continue;
		if (!player->IsA(SDK::AMarvelPlayerState::StaticClass())) continue;

		auto MarvelState = reinterpret_cast<SDK::AMarvelPlayerState*>(players[i]);
		if (!MarvelState) continue;
		if (MarvelState->GetIsLocalPlayer()) continue;

		auto Base = MarvelState->MarvelCharacter;
		if (!Base) continue;

		auto Mesh = Base->GetMesh();
		if (!Mesh) continue;

		if (!Mesh->DoesSocketExist(Custom::StrToName(L"Head")) || !Mesh->DoesSocketExist(Custom::StrToName(L"root"))) continue;

		SDK::FVector head_bone_pos = Mesh->GetSocketLocation(Custom::StrToName(L"Head"));
		SDK::FVector feet_bone_pos = Mesh->GetSocketLocation(Custom::StrToName(L"root"));
		SDK::FVector feet_middle_pos = { feet_bone_pos.X, feet_bone_pos.Y, head_bone_pos.Z };

		SDK::FVector2D Top{}, Bottom{};
		if (!Controller->ProjectWorldLocationToScreen(head_bone_pos, &Top, true) ||
			!Controller->ProjectWorldLocationToScreen(feet_middle_pos, &Bottom, true))
			continue;

		const float h = std::abs(Top.Y - Bottom.Y);
		const float w = h * 0.2f;


	}

	return draw_transition_o(ViewportClient, Useless);
}

using process_event_sim = void(*)(SDK::UObject*, SDK::UFunction*, void*);
process_event_sim process_event_o = 0;

void __cdecl ProcessEventHk(SDK::UObject* Object, SDK::UFunction* Function, void* Params)
{
	if (!Object || !Function) return process_event_o(Object, Function, Params);

	std::string name = Function->GetFullName();
	
	//("%s\n", name.c_str());

	if (function_log.size() >= 100)
	{
		c::func_log = false;
	}
	if (c::func_log)
	{
		function_log.push_back(name);
	}

	if (strstr(name.c_str(), "BlueprintModifyCamera"))
	{
		process_event_o(Object, Function, Params);

		SDK::Params::CameraModifier_BlueprintModifyCamera* params = (SDK::Params::CameraModifier_BlueprintModifyCamera*)Params;

		if (c::fov_changer)
		{
			params->NewFOV = c::fov_changer_fov;
		}

		return;
	}
	if (strstr(name.c_str(), "BlueprintUpdateCameraShake"))
	{
		process_event_o(Object, Function, Params);

		SDK::Params::LegacyCameraShake_BlueprintUpdateCameraShake* params = (SDK::Params::LegacyCameraShake_BlueprintUpdateCameraShake*)Params;

		if (c::remove_shake)
		{
			params->DeltaTime = 0.f;
			params->Alpha = 0.f;
		}

		return;
	}
	if (strstr(name.c_str(), "ServerUpdateCamera"))
	{
		process_event_o(Object, Function, Params);

		SDK::Params::PlayerController_ServerUpdateCamera* params = (SDK::Params::PlayerController_ServerUpdateCamera*)Params;

		return;
	}

	return process_event_o(Object, Function, Params);
}