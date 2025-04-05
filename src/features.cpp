#include "main.h"
#include "features.h"
#include "programdata.h"
#include "ui.h"

void renderEsp(ProgramData& programData, UIData& uiData, ImDrawList* draw_list, std::vector<Entity>& entityList, std::vector<std::pair<Vector3, Vector3>>& posList) {
    Vector2 windowSize = programData.windowSize;
    Vector2 windowPosition = programData.windowPos;

    ImVec2 windowBottomHalfPoint(windowPosition.x + windowSize.x / 2, windowPosition.y + windowSize.y);
    float baseSize = (windowSize.x + windowSize.y)/2 * 0.2f;

    std::vector<float>& viewMatrix = programData.viewMatrix;

    int index = 0;
    for (Entity& entity : entityList) {
        int32_t health = entity.getHealth();
        int32_t armor = entity.getArmor();
        if (health <= 0) {
            index++;
            continue;
        };

        std::pair<Vector3, Vector3>& entityPositions = posList[index];
        Vector3 headPosition = entityPositions.first;
        Vector3 bodyPosition = entityPositions.second;

        float size = baseSize / (bodyPosition.z * 0.1f);
        float halfSize = size / 2.0f;

        ImVec2 topLeft(bodyPosition.x - halfSize, bodyPosition.y - size);
        ImVec2 bottomRight(bodyPosition.x + halfSize, bodyPosition.y + size);

        float hNormalized = std::clamp(health / 100.0f, 0.0f, 1.0f);
        float reverseHNormalized = 1.0f - hNormalized;
        int hRed = (int)(reverseHNormalized * 255);
        int hGreen = (int)(hNormalized * 255);

        ImColor healthBarColor(hRed, hGreen, 0, 255);

        if (uiData.statusBarsEnabled) {
            float calculatedBarOutlineWidth = 10.0f + size * 0.05f;
            float barHeightGap = size * 0.01f;

            ImVec2 barOutlineTopLeft(bodyPosition.x + halfSize, topLeft.y);
            ImVec2 barOutlineBottomRight(bottomRight.x + calculatedBarOutlineWidth, bottomRight.y);

            float barGap = calculatedBarOutlineWidth / 7.0f;
            float barWidth = barGap * 2.0f;

            float aNormalized = std::clamp(armor / 100.0f, 0.0f, 1.0f);
            float reverseANormalized = 1.0f - aNormalized;

            float barTopY = barOutlineTopLeft.y + barHeightGap;
            float barBottomY = barOutlineBottomRight.y - barHeightGap;
            float healthLeftX = barOutlineTopLeft.x + barGap;
            float healthRightX = healthLeftX + barWidth;
            float armorLeftX = healthRightX + barGap;
            float armorRightX = armorLeftX + barWidth;

            float barHeight = barBottomY - barTopY;
            float healthBarHeight = barHeight * reverseHNormalized;
            float armorBarHeight = barHeight * reverseANormalized;
            
            ImVec2 healthBarTopLeft(healthLeftX, barTopY + healthBarHeight);
            ImVec2 healthBarBottomRight(healthRightX, barBottomY);
            ImVec2 armorBarTopLeft(armorLeftX, barTopY + armorBarHeight);
            ImVec2 armorBarBottomRight(armorRightX, barBottomY);

            ImColor barOutlineColor(60, 135, 255, 255);
            ImColor armorBarColor(200, 200, 0, 255);

            draw_list->AddRect(barOutlineTopLeft, barOutlineBottomRight, barOutlineColor, 0.0f, 0, 1.0f);
            draw_list->AddRectFilled(healthBarTopLeft, healthBarBottomRight, healthBarColor, 0.0f, 0);
            draw_list->AddRectFilled(armorBarTopLeft, armorBarBottomRight, armorBarColor, 0.0f, 0);
        };

        float normalized = std::clamp(bodyPosition.z / 100.0f, 0.0f, 1.0f);
        int red = (int)(normalized * 255);
        int green = (int)((1.0f - normalized) * 255);

        ImColor distanceColor(red, green, 0, 255);
    
        draw_list->AddRect(topLeft, bottomRight, healthBarColor, 0.0f, 0, 2.0f);
        if (uiData.headCircleEnabled) {
            draw_list->AddCircle(ImVec2(headPosition.x, headPosition.y), size/5.0f, healthBarColor, 0, 2.0f);
        };
        if (uiData.tracerLinesEnabled) {
            draw_list->AddLine(ImVec2(bodyPosition.x, bottomRight.y), windowBottomHalfPoint, distanceColor);
        };
        index++;
    };
};

void renderAimBot(ProgramData& programData, UIData& uiData, ImDrawList* draw_list) {
    Vector2 winPos = programData.windowPos;
    Vector2 winSize = programData.windowSize;

    ImVec2 center(winPos.x + (winSize.x / 2), winPos.y + (winSize.y / 2));
    ImColor circleColor = programData.aimBotLocked ? ImColor(255, 0, 0, 255) : ImColor(190, 210, 20, 255);

    draw_list->AddCircle(center, uiData.aimBotDistance, circleColor, 0, 2.0f);
};

void runAimBot(ProgramData& programData, UIData& uiData, std::vector<Entity>& entityList, Entity& localPlayer, std::vector<std::pair<Vector3, Vector3>>& posList) {
    double now = std::chrono::duration<double>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    if (programData.lastAimBotTick + 0.01 > now) return;
    programData.lastAimBotTick = now;

    Vector2 winSize = programData.windowSize;
    Vector2 winPos = programData.windowPos;
    std::vector<Entity*> entitiesInDistance;

    Vector2 center(winPos.x + (winSize.x / 2), winPos.y + (winSize.y / 2));

    int index = 0;
    for (Entity& entity : entityList) {
        std::pair<Vector3, Vector3>& entityPositions = posList[index];
        Vector3 entityHeadPos = entityPositions.first;
        Vector2 rawEntityHeadPos = { entityHeadPos.x, entityHeadPos.y };
        if (Utils::GetVector2Distance(rawEntityHeadPos, center) <= uiData.aimBotDistance)
        {
            if (entity.getHealth() > 0) {
                entitiesInDistance.push_back(&entity);
            };
        };
        index++;
    };

    auto min_it = std::min_element(entitiesInDistance.begin(), entitiesInDistance.end(),
        [](const auto& a, const auto& b) {
            return a->getHealth() < b->getHealth();
        }
    );
    
    Entity* selectedEntity = nullptr;
    if (min_it != entitiesInDistance.end()) {
        selectedEntity = *min_it;
    } else {
        return;
    };
    programData.aimBotLocked = true;
    Vector3 localPlrHeadPos = localPlayer.getHeadPosition();
    Vector2 localPlrCamPos = localPlayer.getCameraPosition();
    Vector2 calculatedYawAndPitch = Utils::GetYawPitchFromWorldPos(selectedEntity->getHeadPosition(), localPlayer.getHeadPosition());
    float calculatedAlpha = 1.0f - pow(uiData.aimBotAlpha, 0.1f);
    Vector2 targetCamPos = Utils::Lerp(localPlrCamPos, calculatedYawAndPitch, calculatedAlpha);

    localPlayer.setCameraPosition(programData.handle, targetCamPos);
};