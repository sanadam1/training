// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "StreamlineSettings.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STREAMLINERHI_StreamlineSettings_generated_h
#error "StreamlineSettings.generated.h already included, missing '#pragma once' in StreamlineSettings.h"
#endif
#define STREAMLINERHI_StreamlineSettings_generated_h

#define FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_32_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUStreamlineOverrideSettings(); \
	friend struct Z_Construct_UClass_UStreamlineOverrideSettings_Statics; \
public: \
	DECLARE_CLASS(UStreamlineOverrideSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_ProjectUserConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/StreamlineRHI"), STREAMLINERHI_API) \
	DECLARE_SERIALIZER(UStreamlineOverrideSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Engine");} \



#define FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_32_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	STREAMLINERHI_API UStreamlineOverrideSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UStreamlineOverrideSettings(UStreamlineOverrideSettings&&); \
	UStreamlineOverrideSettings(const UStreamlineOverrideSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(STREAMLINERHI_API, UStreamlineOverrideSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStreamlineOverrideSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UStreamlineOverrideSettings) \
	STREAMLINERHI_API virtual ~UStreamlineOverrideSettings();


#define FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_29_PROLOG
#define FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_32_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_32_INCLASS_NO_PURE_DECLS \
	FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_32_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STREAMLINERHI_API UClass* StaticClass<class UStreamlineOverrideSettings>();

#define FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_64_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUStreamlineSettings(); \
	friend struct Z_Construct_UClass_UStreamlineSettings_Statics; \
public: \
	DECLARE_CLASS(UStreamlineSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/StreamlineRHI"), STREAMLINERHI_API) \
	DECLARE_SERIALIZER(UStreamlineSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Engine");} \



#define FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_64_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	STREAMLINERHI_API UStreamlineSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UStreamlineSettings(UStreamlineSettings&&); \
	UStreamlineSettings(const UStreamlineSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(STREAMLINERHI_API, UStreamlineSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStreamlineSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UStreamlineSettings) \
	STREAMLINERHI_API virtual ~UStreamlineSettings();


#define FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_61_PROLOG
#define FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_64_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_64_INCLASS_NO_PURE_DECLS \
	FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h_64_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STREAMLINERHI_API UClass* StaticClass<class UStreamlineSettings>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MyProject_Plugins_StreamlineCore_Source_StreamlineRHI_Public_StreamlineSettings_h


#define FOREACH_ENUM_ESTREAMLINESETTINGOVERRIDE(op) \
	op(EStreamlineSettingOverride::Enabled) \
	op(EStreamlineSettingOverride::Disabled) \
	op(EStreamlineSettingOverride::UseProjectSettings) 

enum class EStreamlineSettingOverride : uint8;
template<> struct TIsUEnumClass<EStreamlineSettingOverride> { enum { Value = true }; };
template<> STREAMLINERHI_API UEnum* StaticEnum<EStreamlineSettingOverride>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
