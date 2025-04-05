#include "main.h"

int Utils::WorldToScreen(Vector3 worldPos, Vector3 &screenPos, std::vector<float>& viewMatrix, Vector2 windowSize) {
    float clipX = worldPos.x * viewMatrix[0] + worldPos.y * viewMatrix[4] + worldPos.z * viewMatrix[8] + viewMatrix[12];
    float clipY = worldPos.x * viewMatrix[1] + worldPos.y * viewMatrix[5] + worldPos.z * viewMatrix[9] + viewMatrix[13];
    //float clipZ = worldPos.x * viewMatrix[2] + worldPos.y * viewMatrix[6] + worldPos.z * viewMatrix[10] + viewMatrix[14];
    float w     = worldPos.x * viewMatrix[3] + worldPos.y * viewMatrix[7] + worldPos.z * viewMatrix[11] + viewMatrix[15];

    if (w < 0.1f) return 1; // Behind camera

    clipX /= w; clipY /= w;

    screenPos.x = (windowSize.x / 2.0f) * (clipX + 1.0f);
    screenPos.y = (windowSize.y / 2.0f) * (1.0f - clipY);
    screenPos.z = w;
    return 0;
};

float Utils::GetVector2Distance(const Vector2& a, const Vector2& b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
};

Vector2 Utils::GetYawPitchFromWorldPos(const Vector3& worldPos, const Vector3& cameraPos) {
    Vector3 dir = { worldPos.x - cameraPos.x, worldPos.y - cameraPos.y, worldPos.z - cameraPos.z };

    float yaw = 180 - (atan2(dir.x, dir.y) * (180.0f / M_PI));
    if (yaw < 0) yaw += 360; // 0-360

    float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
    float pitch = atan2(dir.z, hyp) * (180.0f / M_PI);
    
    return Vector2 {yaw, pitch};
};

Vector2 Utils::Lerp(const Vector2& a, const Vector2& b, float t) {
    return Vector2 {
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t
    };
};