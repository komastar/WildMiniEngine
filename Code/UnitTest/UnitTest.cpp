#include "pch.h"
#include <format>
#include "CppUnitTest.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(UnitTest)
    {
    public:
        TEST_METHOD(TestVector2)
        {
            Vector2 v1(1.0f, 2.0f);
            Vector2 v2(1.0f, 2.0f);
            Assert::AreEqual(v1, v2);

            Vector2 v3(v1.y, v1.x);
            Assert::AreNotEqual(v1, v3);
        }

        TEST_METHOD(TestVector3)
        {
            Vector3 v1(1.0f);
            Vector3 v2(1.0f);
            Assert::AreEqual(v1, v2);

            Vector3 v3 = v1 * 2.0f;
            Assert::AreNotEqual(v1, v3);
        }

        TEST_METHOD(TestVector4)
        {
            Vector4 v1(1.0f);
            Vector4 v2(1.0f);
            Assert::AreEqual(v1, v2);
        }
    };
}

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<> static std::wstring ToString<Vector2>(const Vector2& t)
            {
                return std::format(L"x : {0}, y : {1}", t.x, t.y);
            }

            template<> static std::wstring ToString<Vector3>(const Vector3& t)
            {
                return std::format(L"x : {0}, y : {1}, z : {2}", t.x, t.y, t.z);
            }

            template<> static std::wstring ToString<Vector4>(const Vector4& t)
            {
                return std::format(L"x : {0}, y : {1}, z : {2}, w : {3}", t.x, t.y, t.z, t.w);
            }
        }
    }
}