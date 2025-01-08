// © Surgent Studios

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "TypeDrawer/SrgImGuiTypeDrawer.h"

#include "SrgImGuiTypeLibrary.generated.h"

class ISrgImGuiCustomDrawer;

/**
 * This static class provides functionality to default draw various types.
 */
UCLASS()
class SRGIMGUI_API USrgImGuiTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Draws a bool property using a default drawer.
	 * @param Name The name of the bool variable to draw.
	 * @param Value The value of the bool variable to draw.
	 * @param Mutable If true, the value will be editable.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Primitive",
			  meta = (DisplayName = "ImGui - Bool", ReturnDisplayName = "Modified?"))
	static bool DrawBool(const FString& Name, UPARAM(ref) bool& Value, bool Mutable = false);

	/**
	 * Draws an integer property using a default drawer.
	 * @param Name The name of the integer variable to draw.
	 * @param Value The value of the integer variable to draw.
	 * @param Mutable If true, the value will be editable.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Primitive",
			  meta = (DisplayName = "ImGui - Integer", ReturnDisplayName = "Modified?"))
	static bool DrawInt32(const FString& Name, UPARAM(ref) int32& Value, bool Mutable = false);

	/**
	 * Draws a integer 64 property using a default drawer.
	 * @param Name The name of the integer 64 variable to draw.
	 * @param Value The value of the integer 64 variable to draw.
	 * @param Mutable If true, the value will be editable.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Primitive",
			  meta = (DisplayName = "ImGui - Integer 64", ReturnDisplayName = "Modified?"))
	static bool DrawInt64(const FString& Name, UPARAM(ref) int64& Value, bool Mutable = false);

	/**
	 * Draws a byte property using a default drawer.
	 * @param Name The name of the byte variable to draw.
	 * @param Value The value of the byte variable to draw.
	 * @param Mutable If true, the value will be editable.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Primitive",
			  meta = (DisplayName = "ImGui - Byte", ReturnDisplayName = "Modified?"))
	static bool DrawUInt8(const FString& Name, UPARAM(ref) uint8& Value, bool Mutable = false);

	/**
	 * Draws a float property using a default drawer.
	 * Note: In C++ this is actually a double. BP only supports doubles and calls them floats.
	 * @param Name The name of the float variable to draw.
	 * @param Value The value of the float variable to draw.
	 * @param Mutable If true, the value will be editable.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Primitive",
			  meta = (DisplayName = "ImGui - Float", ReturnDisplayName = "Modified?"))
	static bool DrawDouble(const FString& Name, UPARAM(ref) double& Value, bool Mutable = false);

	template <typename PrimitiveType>
	static bool DrawPrimitive(const FString& Name, PrimitiveType& Value, bool Mutable = false)
	{
		DrawVarStart(Name);
		const bool WasModified = SrgImGuiTypeDrawer::DrawPrimitiveValue(Value, Mutable);
		DrawVarEnd();
		return WasModified;
	}

	/**
	 * Draws a string property using a default drawer.
	 * @param Name The name of the string variable to draw.
	 * @param Value The value of the string variable to draw.
	 * @param Mutable If true, the value will be editable.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|String",
			  meta = (DisplayName = "ImGui - String", ReturnDisplayName = "Modified?"))
	static bool DrawString(const FString& Name, UPARAM(ref) FString& Value, bool Mutable = false);
	/**
	 * Draws a name property using a default drawer.
	 * @param Name The name of the name variable to draw.
	 * @param Value The value of the name variable to draw.
	 * @param Mutable If true, the value will be editable.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|String",
			  meta = (DisplayName = "ImGui - Name", ReturnDisplayName = "Modified?"))
	static bool DrawName(const FString& Name, UPARAM(ref) FName& Value, bool Mutable = false);
	/**
	 * Draws a text property using a default drawer.
	 * @param Name The name of the text variable to draw.
	 * @param Value The value of the text variable to draw.
	 * @param Mutable If true, the value will be editable.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|String",
			  meta = (DisplayName = "ImGui - Text", ReturnDisplayName = "Modified?"))
	static bool DrawText(const FString& Name, UPARAM(ref) FText& Value, bool Mutable = false);

	template <typename StringType>
	static bool DrawStringT(const FString& Name, StringType& Value, bool Mutable = false)
	{
		DrawVarStart(Name);
		const bool WasModified = SrgImGuiTypeDrawer::DrawStringValue(Value, Mutable);
		DrawVarEnd();
		return WasModified;
	}

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	static bool DrawEnum_K2Node(const FString& Name, UPARAM(ref) uint8& EnumValue, const FString& EnumClass, bool Mutable);

	template <typename EnumType>
	static bool DrawEnum(const FString& Name, EnumType& Value, bool Mutable = false)
	{
		static_assert(TIsEnum<EnumType>::Value, "Should only call this with enum types");
		static_assert(sizeof(EnumType) == sizeof(uint8), "EnumType is not a uint8");
		static_assert(static_cast<int32>(EnumType(-1)) == 0xFF, "EnumType is not a uint8");
		DrawVarStart(Name);
		const bool WasModified =
			SrgImGuiTypeDrawer::DrawEnumValue(reinterpret_cast<uint8&>(Value), StaticEnum<EnumType>(), Mutable);
		DrawVarEnd();
		return WasModified;
	}

	/**
	 * Draws a class property using a default drawer.
	 * @param Name The name of the class variable to draw.
	 * @param Class The class to draw.
	 * @param Mutable If true, the value will be editable.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Class", BlueprintInternalUseOnly, CustomThunk,
			  meta = (DisplayName = "ImGui - Class", ReturnDisplayName = "Modified?", CustomStructureParam = "Class"))
	static bool DrawClass_K2Node(const FString& Name, const int32& Class, bool Mutable = false);
	DECLARE_FUNCTION(execDrawClass_K2Node);

	/**
	 * Draws a class property using a default drawer.
	 * @param Name The name of the class variable to draw.
	 * @param Class The class to draw.
	 * @param Mutable If true, the value will be editable.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Class", BlueprintInternalUseOnly, CustomThunk,
			  meta = (DisplayName = "ImGui - Soft Class", ReturnDisplayName = "Modified?", CustomStructureParam = "SoftClass"))
	static bool DrawSoftClass_K2Node(const FString& Name, const int32& SoftClass, bool Mutable = false);
	DECLARE_FUNCTION(execDrawSoftClass_K2Node);

	template <typename ClassType>
	static bool DrawClass(const FString& Name, TSubclassOf<ClassType>& Class, bool Mutable = false)
	{
		DrawVarStart(Name);
		UClass* ClassPtr	   = Class.Get();
		const bool WasModified = SrgImGuiTypeDrawer::DrawClassValue(ClassPtr, ClassType::StaticClass(), Mutable);
		if (WasModified)
		{
			Class = ClassPtr;
		}
		DrawVarEnd();
		return WasModified;
	}

	template <typename ClassType>
	static bool DrawClass(const FString& Name, TSoftClassPtr<ClassType>& Class, bool Mutable = false)
	{
		DrawVarStart(Name);
		UClass* ClassPtr	   = Class.Get();
		const bool WasModified = SrgImGuiTypeDrawer::DrawClassValue(ClassPtr, ClassType::StaticClass(), Mutable);
		if (WasModified)
		{
			Class = ClassPtr;
		}
		DrawVarEnd();
		return WasModified;
	}

	/**
	 * Draws a struct property using a default drawer.
	 * @param Name The name of the struct variable to draw.
	 * @param Struct The struct to draw.
	 * @param Mutable If true, the value will be editable.
	 * @param HasCollapsingHeader If true, the struct will be wrapped in an ImGui collapsing header.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Container", BlueprintInternalUseOnly, CustomThunk,
			  meta = (DisplayName = "ImGui - Struct", ReturnDisplayName = "Modified?", CustomStructureParam = "Struct"))
	static bool DrawStruct_K2Node(const FString& Name, const int32& Struct, bool Mutable = false,
								  bool HasCollapsingHeader = true);
	DECLARE_FUNCTION(execDrawStruct_K2Node);

	template <typename StructType>
	static bool DrawStruct(const FString& Name, StructType& Struct, bool Mutable = false, bool HasCollapsingHeader = true)
	{
		DrawVarStart(Name, HasCollapsingHeader);
		const bool WasModified =
			SrgImGuiTypeDrawer::DrawStructValue(&Struct, StructType::StaticStruct(), Mutable, HasCollapsingHeader);
		DrawVarEnd();
		return WasModified;
	}

	/**
	 * Draws an object using a default drawer.
	 * Custom draw behavior per object can be added by implementing SrgImGuiCustomDrawer.
	 * @param Name The name of the object to draw.
	 * @param Object The object to draw.
	 * @param HasCollapsingHeader If true, the object will be wrapped in an ImGui collapsing header.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Container",
			  meta = (DisplayName = "ImGui - Object", ReturnDisplayName = "Modified?"))
	static bool DrawObject(const FString& Name, UObject* Object, bool HasCollapsingHeader = true);

	/**
	 * Draws an array property using a default drawer.
	 * @param Name The name of the array variable to draw.
	 * @param Array The array to draw.
	 * @param Mutable If true, the value will be editable.
	 * @param HasCollapsingHeader If true, the array will be wrapped in an ImGui collapsing header.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Container", CustomThunk,
			  meta = (DisplayName = "ImGui - Array", ReturnDisplayName = "Modified?", ArrayParm = "Array"))
	static bool DrawArray(const FString& Name, const TArray<int32>& Array, bool Mutable = false, bool HasCollapsingHeader = true);
	DECLARE_FUNCTION(execDrawArray);

	/**
	 * Draws a set property using a default drawer.
	 * @param Name The name of the set variable to draw.
	 * @param Set The set to draw.
	 * @param Mutable If true, the value will be editable.
	 * @param HasCollapsingHeader If true, the set will be wrapped in an ImGui collapsing header.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Container", CustomThunk,
			  meta = (DisplayName = "ImGui - Set", ReturnDisplayName = "Modified?", SetParam = "Set"))
	static bool DrawSet(const FString& Name, const TSet<int32>& Set, bool Mutable = false, bool HasCollapsingHeader = true);
	DECLARE_FUNCTION(execDrawSet);

	/**
	 * Draws a map property using a default drawer.
	 * @param Name The name of the map variable to draw.
	 * @param Map The map to draw.
	 * @param Mutable If true, the value will be editable.
	 * @param HasCollapsingHeader If true, the map will be wrapped in an ImGui collapsing header.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Container", CustomThunk,
			  meta = (DisplayName = "ImGui - Map", ReturnDisplayName = "Modified?", MapParam = "Map"))
	static bool DrawMap(const FString& Name, const TMap<int32, int32>& Map, bool Mutable = false,
						bool HasCollapsingHeader = true);
	DECLARE_FUNCTION(execDrawMap);

	/**
	 * Draws a SrgImGuiCustomDrawer object as a default draw object instead of using its custom draw functions.
	 * This can only be used internally by custom drawers in order to draw their default self as part of the custom draw process.
	 * @param Name The name of the custom drawer to draw.
	 * @param HasCollapsingHeader If true, the default custom draw will be wrapped in an ImGui collapsing header.
	 * @return Returns true if the value was modified.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRG ImGui|Type|Custom Drawer",
			  meta = (DisplayName = "ImGui - Default Custom Drawer", ReturnDisplayName = "Modified?", HidePin = "CustomDrawer",
					  DefaultToSelf = "CustomDrawer"))
	static bool DrawDefaultCustomDrawer(const FString& Name, TScriptInterface<ISrgImGuiCustomDrawer> CustomDrawer,
										bool HasCollapsingHeader = true);

	template <typename StructType, typename PropertyType>
	static bool DrawStructProperty(StructType& Struct, PropertyType& PropertyRef, bool Mutable = false,
								   bool HasCollapsingHeader = true, int32 ArrayIndex = 0)
	{
		return DrawContainerProperty(nullptr, &Struct, &PropertyRef, *StructType::StaticStruct(), Mutable, HasCollapsingHeader,
									 ArrayIndex);
	}

	template <typename StructType, typename PropertyType>
	static bool DrawStructProperty(const FString& Name, StructType& Struct, PropertyType& PropertyRef, bool Mutable = false,
								   bool HasCollapsingHeader = true, int32 ArrayIndex = 0)
	{
		return DrawContainerProperty(&Name, &Struct, &PropertyRef, *StructType::StaticStruct(), Mutable, HasCollapsingHeader,
									 ArrayIndex);
	}

	template <typename PropertyType>
	static bool DrawObjectProperty(UObject& Object, PropertyType& PropertyRef, bool Mutable = false,
								   bool HasCollapsingHeader = true, int32 ArrayIndex = 0)
	{
		return DrawContainerProperty(nullptr, &Object, &PropertyRef, *Object.GetClass(), Mutable, HasCollapsingHeader,
									 ArrayIndex);
	}

	template <typename PropertyType>
	static bool DrawObjectProperty(const FString& Name, UObject& Object, PropertyType& PropertyRef, bool Mutable = false,
								   bool HasCollapsingHeader = true, int32 ArrayIndex = 0)
	{
		return DrawContainerProperty(&Name, &Object, &PropertyRef, *Object.GetClass(), Mutable, HasCollapsingHeader, ArrayIndex);
	}

private:
	static bool DrawContainerProperty(const FString* Name, void* ContainerPtr, void* PropertyPtr, UStruct& ContainerClass,
									  bool Mutable, bool HasCollapsingHeader, int32 ArrayIndex);
	static void DrawVarStart(const FString& Name, bool PrintName = true);
	static void DrawVarEnd();
};