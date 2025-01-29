#pragma once

bool ShowMenu = true;
std::vector<std::string> function_log;
SDK::UMaterialInterface* target_mat = nullptr;
std::string target_material_name;

void RenderMenu()
{
	if (GetAsyncKeyState(VK_INSERT) & 1) ShowMenu = !ShowMenu;
	if (GetAsyncKeyState(VK_F1) & 1) ShowMenu = !ShowMenu;

	if (!ShowMenu) return;

	ImGui::SetNextWindowPos(ImVec2(100, 50), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowBgAlpha(0.5f);

	ImGui::Begin("Menu", nullptr);
	
	ImGui::Checkbox("ESP", &c::esp);
	ImGui::Checkbox("Box", &c::box);
	ImGui::Checkbox("Debug Bones", &c::debug_bones);
	ImGui::Checkbox("Bone Names", &c::bone_names);
	ImGui::Checkbox("Chams", &c::chams);

	ImGui::Checkbox("Aimbot", &c::aimbot);
	ImGui::Checkbox("Bullet TP", &c::bullet_tp);
	ImGui::SliderInt("FOV", &c::fov, 1, 360);
	ImGui::SliderInt("Smoothing", &c::smoothing, 1, 100);

	ImGui::Checkbox("FOV Changer", &c::fov_changer);
	ImGui::SliderInt("FOV##1", &c::fov_changer_fov, 1, 180);

	ImGui::Checkbox("Remove Shake", &c::remove_shake);

	ImGui::Checkbox("Function Log", &c::func_log);

	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(1000, 100), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(600, 900), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowBgAlpha(0.5f);
	ImGui::Begin("Function Log", nullptr);
	if (ImGui::Button("Reset"))
		function_log.clear();
	ImGui::Separator();
	auto temp_list = function_log;
	if (!temp_list.empty())
	{
		for (int i = 0; i < temp_list.size(); i++)
		{
			if (temp_list.at(i).empty()) continue;
			ImGui::Text(temp_list.at(i).c_str());
		}
	}
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(100, 450), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowBgAlpha(0.5f);
	ImGui::Begin("Material Log");
	for (int i = 0; i < SDK::UObject::GObjects->Num(); i++)
	{
		SDK::UObject* Obj = SDK::UObject::GObjects->GetByIndex(i);

		if (!Obj)
			continue;

		if (Obj->IsA(SDK::UMaterialInterface::StaticClass()) && !Obj->IsDefaultObject())
		{
			std::string name = Obj->GetFullName();
			ImGui::Text(name.c_str());
			ImGui::SameLine();
			if (ImGui::Button("Select"))
			{
				target_material_name = name;
				target_mat = (SDK::UMaterialInterface*)Obj;
			}
		}
	}
	ImGui::End();
}

SDK::AMarvelPlayerState* closest_target = nullptr;
float closest_distance = FLT_MAX;

void RenderCheat()
{
	try
	{
		closest_distance = FLT_MAX;
		closest_target = nullptr;

		ImGui::GetForegroundDrawList()->AddText(ImVec2(10, 10), ImColor(255, 255, 255), "kaleb is a paki");
		if (c::aimbot)
			ImGui::GetForegroundDrawList()->AddCircle(ImVec2(1920 / 2, 1080 / 2), c::fov * 3, ImColor(255, 255, 255));

		auto World = SDK::UWorld::GetWorld();
		if (!World) return;

		auto GameState = World->GameState;
		if (!GameState) return;

		auto Instance = World->OwningGameInstance;
		if (!Instance) return;

		auto Controller = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
		if (!Controller) return;
		Globals::MyController = Controller;

		auto Pawn = Controller->AcknowledgedPawn;
		if (!Pawn) return;

		auto Camera = Controller->PlayerCameraManager;
		if (!Camera) return;

		auto PlayerState = reinterpret_cast<SDK::AMarvelPlayerState*>(Controller->PlayerState);
		if (!PlayerState) return;
		int LocalTeam = PlayerState->TeamID;

		SDK::FVector ViewLocation{};
		SDK::FRotator ViewRotation{};
		Controller->GetPlayerViewPoint(&ViewLocation, &ViewRotation);

		SDK::TArray<SDK::AActor*> PlayerArray;
		SDK::UGameplayStatics::GetAllActorsOfClass(World, SDK::AMarvelPlayerState::StaticClass(), &PlayerArray);
		if (!PlayerArray || !PlayerArray.IsValid()) return;

		for (int i = 0; i < PlayerArray.Num(); i++)
		{
			if (!PlayerArray.IsValidIndex(i)) continue;

			auto Player = PlayerArray[i];
			if (!Player) continue;

			auto MarvelState = reinterpret_cast<SDK::AMarvelPlayerState*>(Player);
			if (!MarvelState) continue;
			if (MarvelState->GetIsLocalPlayer()) continue;
			if (LocalTeam == MarvelState->TeamID) continue;

			auto Base = MarvelState->MarvelCharacter;
			if (!Base) continue;

			auto Mesh = Base->GetMesh();
			if (!Mesh) continue;

			auto materials = Mesh->GetMaterials();
			if (c::chams && materials && materials.IsValid())
			{
				for (int j = 0; j < materials.Num(); j++)
				{
					if (!materials.IsValidIndex(j)) continue;

					auto material = materials[j]; 
					if (!material) continue;

					if (!target_mat && !target_material_name.empty()) target_mat = SDK::UObject::FindObject<SDK::UMaterialInterface>(target_material_name);
					if (!target_mat) target_material_name = "";
					if (!target_mat) continue;
					if (target_mat == material) continue;

					Mesh->SetMaterial(j, target_mat);
				}
			}

			if (!Base->IsAlive()) continue;

			if (!Mesh->DoesSocketExist(Custom::StrToName(L"Head")) || !Mesh->DoesSocketExist(Custom::StrToName(L"root"))) continue;

			SDK::FVector head_bone_pos = Mesh->GetSocketLocation(Custom::StrToName(L"Head"));
			SDK::FVector feet_bone_pos = Mesh->GetSocketLocation(Custom::StrToName(L"root"));

			SDK::FVector feet_middle_pos = { head_bone_pos.X, head_bone_pos.Y, feet_bone_pos.Z };

			SDK::FVector2D Top{}, Bottom{};
			if (!Controller->ProjectWorldLocationToScreen(head_bone_pos, &Top, true) ||
				!Controller->ProjectWorldLocationToScreen(feet_middle_pos, &Bottom, true))
				continue;

			const float h = std::abs(Top.Y - Bottom.Y);
			const float w = h * 0.5f;

			auto Colour = Mesh->WasRecentlyRendered(SDK::ERecentlyRenderedType::OnScreen, 0.f) ? ImColor(0, 255, 0) : ImColor(0, 0, 255);

			double dist = Top.GetDistanceTo(SDK::FVector2D(1920 / 2, 1080 / 2));
			if (dist < c::fov * 3 && dist < closest_distance)
			{
				closest_distance = dist;
				closest_target = MarvelState;
			}

			if (c::esp)
			{
				if (c::box)
				{
					ImGui::GetForegroundDrawList()->AddRect(ImVec2(Top.X - w, Top.Y), ImVec2(Bottom.X + w, Bottom.Y), Colour);
				}

				if (c::debug_bones)
				{
					auto BoneNames = Mesh->GetAllSocketNames();
					if (BoneNames.IsValid())
					{
						for (int i = 0; i < BoneNames.Num(); i++)
						{
							SDK::FVector BonePos = Mesh->GetSocketLocation(BoneNames[i]);
							SDK::FVector2D Pos{};
							if (Controller->ProjectWorldLocationToScreen(BonePos, &Pos, true))
							{
								if (c::debug_bones)
								{
									ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(Pos.X, Pos.Y), 1.f, Colour);
								}
								if (c::bone_names)
								{
									auto Name = BoneNames[i].ToString();
									ImGui::GetForegroundDrawList()->AddText(ImVec2(Pos.X + 1, Pos.Y), Colour, Name.c_str());
								}
							}
						}
					}
				}
			}
		}

		if (Controller && PlayerState && closest_target)
		{
			auto Base = closest_target->MarvelCharacter;
			if (!Base) return;

			auto Mesh = Base->GetMesh();
			if (!Mesh) return;

			SDK::FRotator control_rot = Controller->GetControlRotation();
			auto Head_pos = Mesh->GetSocketLocation(Custom::StrToName(L"Head"));
			SDK::FRotator target_rot = SDK::UKismetMathLibrary::FindLookAtRotation(Camera->GetCameraLocation(), Head_pos);

			SDK::FRotator delta = SDK::FRotator(
				target_rot.Pitch - control_rot.Pitch,
				target_rot.Yaw - control_rot.Yaw,
				0
			);

			delta.Pitch /= c::smoothing;
			delta.Yaw /= c::smoothing;

			control_rot.Pitch += delta.Pitch;
			control_rot.Yaw += delta.Yaw;
			control_rot.Roll = 0;

			if (Controller->IsInputKeyDown(Keys::LeftControl) && Mesh->WasRecentlyRendered(SDK::ERecentlyRenderedType::OnScreen, 0.f))
			{
				if (c::aimbot)
					Controller->SetControlRotation(control_rot);
			}

			if (c::bullet_tp)
			{
				SDK::TArray<SDK::AActor*> Bullets;
				SDK::UGameplayStatics::GetAllActorsOfClass(World, SDK::AGameplayAbilityTargetActor::StaticClass(), &Bullets);
				auto TargetPosition = Head_pos - Controller->GetActorForwardVector() * 80.0;

				for (int i = 0; i < Bullets.Num(); i++)
				{
					if (!Bullets.IsValidIndex(i)) continue;

					auto Bullet = Bullets[i];
					if (!Bullet) continue;

					SDK::FHitResult fhit;

					auto bullet_dist_to_head = Head_pos.GetDistanceTo(Bullet->K2_GetActorLocation());

					if (bullet_dist_to_head > 100)
						Bullet->K2_SetActorLocationAndRotation(TargetPosition, SDK::FRotator(90, 0, 0), false, &fhit, false); // teleport bullet above head aiming downwards
				}
			}
		}

		PlayerArray.Clear();
	}
	catch (...) {}
}