#ifndef UTILS_HPP
#define UTILS_HPP

#include "../Overlay/imgui/imgui.h"
#include "../Overlay/imgui/imgui_impl_dx9.h"
#include "../Overlay/imgui/imgui_impl_win32.h"
#include "../Overlay/imgui/imgui_internal.h"

#include "Imports.hpp"
#include "Math.hpp"
#include "Driver.hpp"

namespace Utils {
	__forceinline bool __fastcall WorldToScreen(const Vector3& entityPos, Vector2& screenPos)
	{
		Vector3 transVec = Vector3(pViewMatrix._14, pViewMatrix._24, pViewMatrix._34);
		Vector3 rightVec = Vector3(pViewMatrix._11, pViewMatrix._21, pViewMatrix._31);
		Vector3 upVec = Vector3(pViewMatrix._12, pViewMatrix._22, pViewMatrix._32);

		float w = Math::Dot(transVec, entityPos) + pViewMatrix._44;
		if (w < 0.098f) return false;

		float y = Math::Dot(upVec, entityPos) + pViewMatrix._42;
		float x = Math::Dot(rightVec, entityPos) + pViewMatrix._41;

		screenPos = Vector2((screenWidth / 2) * (1.f + x / w), (screenHeight / 2) * (1.f - y / w));
		return true;
	}

	__forceinline Vector3 __fastcall GetPosition(uintptr_t transform)
	{
		if (!transform) return Vector3{ 0.f, 0.f, 0.f };

		struct Matrix34 { BYTE vec0[16]; BYTE vec1[16]; BYTE vec2[16]; };
		const __m128 mulVec0 = { -2.000, 2.000, -2.000, 0.000 };
		const __m128 mulVec1 = { 2.000, -2.000, -2.000, 0.000 };
		const __m128 mulVec2 = { -2.000, -2.000, 2.000, 0.000 };

		int index = Read<int>(transform + 0x40);

		uintptr_t pTransformData = Read<uintptr_t>(transform + 0x38);
		uintptr_t transformData[2];
		ReadString((pTransformData + 0x18), &transformData, 16);

		size_t sizeMatriciesBuf = 48 * index + 48;
		size_t sizeIndicesBuf = 4 * index + 4;

		PVOID pMatriciesBuf = malloc(sizeMatriciesBuf);
		PVOID pIndicesBuf = malloc(sizeIndicesBuf);

		if (pMatriciesBuf && pIndicesBuf) {
			ReadString(transformData[0], pMatriciesBuf, sizeMatriciesBuf);
			ReadString(transformData[1], pIndicesBuf, sizeIndicesBuf);

			__m128 result = *(__m128*)((ULONGLONG)pMatriciesBuf + 0x30 * index);
			int transformIndex = *(int*)((ULONGLONG)pIndicesBuf + 0x4 * index);

			while (transformIndex >= 0) {
				Matrix34 matrix34 = *(Matrix34*)((ULONGLONG)pMatriciesBuf + 0x30 * transformIndex);
				__m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x00));
				__m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x55));
				__m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x8E));
				__m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xDB));
				__m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xAA));
				__m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x71));
				__m128 tmp7 = _mm_mul_ps(*(__m128*)(&matrix34.vec2), result);

				result = _mm_add_ps(
					_mm_add_ps(
						_mm_add_ps(
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps(_mm_mul_ps(xxxx, mulVec1), zwxy),
									_mm_mul_ps(_mm_mul_ps(yyyy, mulVec2), wzyw)),
								_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps(_mm_mul_ps(zzzz, mulVec2), wzyw),
									_mm_mul_ps(_mm_mul_ps(xxxx, mulVec0), yxwy)),
								_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
						_mm_add_ps(
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps(_mm_mul_ps(yyyy, mulVec0), yxwy),
									_mm_mul_ps(_mm_mul_ps(zzzz, mulVec1), zwxy)),
								_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))),
							tmp7)), *(__m128*)(&matrix34.vec0));
				try {
					transformIndex = *(int*)((ULONGLONG)pIndicesBuf + 0x4 * transformIndex);
				}
				catch (...) {
					//Does Nothing
				}
			}

			free(pMatriciesBuf);
			free(pIndicesBuf);

			return Vector3(result.m128_f32[0], result.m128_f32[1], result.m128_f32[2]);
		}
	}

	__forceinline Vector3 __fastcall GetBonePosition(uintptr_t entity, int bone)
	{
		uintptr_t playerModel = Read<uintptr_t>(entity + 0xB8); //BaseEntity -> public Model model;
		uintptr_t boneTransforms = Read<uintptr_t>(playerModel + 0x48); //public class Model -> public Transform[] boneTransforms;
		uintptr_t entityBone = Read<uintptr_t>(boneTransforms + (0x20 + (bone * 0x8))); // 0x20 = public Transform rootBone;

		return GetPosition(Read<uintptr_t>(entityBone + 0x10));
	}
}

#endif