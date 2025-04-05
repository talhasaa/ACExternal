#include "main.h"
#include "ui.h"

void mainMenu(UIData& data) {
    ImGui::SetNextWindowSize(ImVec2(400, 300));
    ImGui::Begin("ACExternal #>");

    if (ImGui::CollapsingHeader("Values (Single Player)")) {
        ImGui::PushItemWidth(150.0f);

        data.healthChanged = ImGui::InputInt("Health", &data.health);
        data.armorChanged = ImGui::InputInt("Armor", &data.armor);
        data.currentAmmoChanged = ImGui::InputInt("Current Ammo", &data.currentAmmo);
        data.maxAmmoChanged = ImGui::InputInt("Max Ammo", &data.maxAmmo);

        ImGui::PopItemWidth();
    }

    if (ImGui::CollapsingHeader("ESP")) {
        ImGui::PushItemWidth(150.0f);

        ImGui::Checkbox("ESP Enabled", &data.espEnabled);
        ImGui::Checkbox("Tracer Lines", &data.tracerLinesEnabled);
        ImGui::Checkbox("Status Bars", &data.statusBarsEnabled);
        ImGui::Checkbox("Head Circle", &data.headCircleEnabled);

        ImGui::PopItemWidth();
    };

    if (ImGui::CollapsingHeader("AimBot")) {
        ImGui::PushItemWidth(150.0f);

        ImGui::Checkbox("AimBot Enabled", &data.aimBotEnabled);
        ImGui::SliderFloat("Distance", &data.aimBotDistance, 0.0f, 150.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::SliderFloat("Smoothness", &data.aimBotAlpha, 0.0f, 1.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);

        ImGui::PopItemWidth();
    };
    
    ImGui::End();
};