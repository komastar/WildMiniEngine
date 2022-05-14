#pragma once
#include <gtest/gtest.h>

// Expands to the name of the class with namespace that implements the given test.
#define _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name)                     \
  namespace_name##_##test_suite_name##_##test_name##_Test

// Helper macro for defining tests.
#define _GTEST_TEST_(namespace_name, test_suite_name, test_name, parent_class, parent_id)       \
  static_assert(sizeof(GTEST_STRINGIFY_(test_suite_name)) > 1,                                  \
                "test_suite_name must not be empty");                                           \
  static_assert(sizeof(GTEST_STRINGIFY_(test_name)) > 1,                                        \
                "test_name must not be empty");                                                 \
  class _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name)                     \
      : public parent_class {                                                                   \
   public:                                                                                      \
    _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name)() = default;            \
    ~_GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name)() override = default;  \
    _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name)                         \
    (const _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name) &) = delete;     \
    _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name) & operator=(            \
        const _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name,                          \
                                     test_name) &) = delete; /* NOLINT */                       \
    _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name)                         \
    (_GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name) &&) noexcept = delete; \
    _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name) & operator=(            \
        _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name,                                \
                               test_name) &&) noexcept = delete; /* NOLINT */                   \
                                                                                                \
   private:                                                                                     \
    void TestBody() override;                                                                   \
    static ::testing::TestInfo* const test_info_ GTEST_ATTRIBUTE_UNUSED_;                       \
  };                                                                                            \
                                                                                                \
  ::testing::TestInfo* const _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name,           \
                                                    test_name)::test_info_ =                    \
      ::testing::internal::MakeAndRegisterTestInfo(                                             \
          #namespace_name "." #test_suite_name, #test_name, nullptr, nullptr,                   \
          ::testing::internal::CodeLocation(__FILE__, __LINE__), (parent_id),                   \
          ::testing::internal::SuiteApiResolver<                                                \
              parent_class>::GetSetUpCaseOrSuite(__FILE__, __LINE__),                           \
          ::testing::internal::SuiteApiResolver<                                                \
              parent_class>::GetTearDownCaseOrSuite(__FILE__, __LINE__),                        \
          new ::testing::internal::TestFactoryImpl<_GTEST_TEST_CLASS_NAME_(                     \
              namespace_name, test_suite_name, test_name)>);                                    \
  void _GTEST_TEST_CLASS_NAME_(namespace_name, test_suite_name, test_name)::TestBody()


#define _TEST_(namespace_name, test_case_name, test_name) \
  _GTEST_TEST_(namespace_name, test_case_name, test_name, ::testing::Test, ::testing::internal::GetTestTypeId())
