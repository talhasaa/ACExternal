#ifndef UTILS_H
#define UTILS_H

#include "main.h"

namespace Utils {
    int WorldToScreen(Vector3 worldPos, Vector3 &screenPos, std::vector<float>& viewMatrix, Vector2 windowSize);
    float GetVector2Distance(const Vector2& a, const Vector2& b);
    Vector2 GetYawPitchFromWorldPos(const Vector3& worldPos, const Vector3& cameraPos);
    Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
};

#endif // UTILS_H