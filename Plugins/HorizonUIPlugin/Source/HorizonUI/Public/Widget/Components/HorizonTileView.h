// Created by horizon-studio, All Right Reserved

#pragma once

// Core
#include "CoreMinimal.h"

// Engine
#include "Tickable.h"

// UMG
#include "Components/TileView.h"


// HorizonUI
#include "HorizonTileView.generated.h"


UENUM(BlueprintType)
enum class EHorizonTileViewRefreshBehavior : uint8
{
	None,
	ScrollToTop,
	ScrollToBottom,
};
/**
 * 
 */
UCLASS()
class HORIZONUI_API UHorizonTileView : public UTileView, public FTickableGameObject
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInitListItemEvent, UHorizonTileView*, InTileView);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnInitListItemEventNative, UHorizonTileView*);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemEvent, UObject*, InItem);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemEventNative, UObject*);
public:
	UHorizonTileView(const FObjectInitializer& ObjectInitializer);
	virtual void HandleListEntryHovered(UUserWidget& EntryWidget) override;
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void SynchronizeProperties() override;
#if 1 // FTickableGameObject override
public:
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UHorizonTileView, STATGROUP_Tickables); }
	virtual bool IsTickable() const override;
	virtual bool IsTickableInEditor() const override;
	virtual void Tick(float DeltaTime) override;

#endif //  FTickableGameObject override
protected:
	//~ Begin UWidget Interface
	virtual void OnWidgetRebuilt() override;
	//~ End UWidget Interface
	virtual void OnSelectionChangedInternal(UObject* InFirstSelectedItem) override;
	virtual void OnItemClickedInternal(UObject* InItem) override;
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* InItem, TSubclassOf<UUserWidget> InDesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
public:
	UFUNCTION(BlueprintPure, Category = "HorizonPlugin|UI|TileView")
	virtual bool IsFocusable();
	UFUNCTION(BlueprintPure, Category = "HorizonPlugin|UI|TileView")
	virtual bool IsPendingRefresh();
	UFUNCTION(BlueprintPure, Category = "HorizonPlugin|UI|TileView")
	virtual int32 GetNumGeneratedChildren();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void NavigateToAndSelectIndex(int32 InIndex);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void RerouteItemPressed(UObject* InItem);
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void RerouteItemReleased(UObject* InItem);
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void RerouteItemHovered(UObject* InItem);
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void RerouteItemUnhovered(UObject* InItem);
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void RerouteItemClicked(UObject* InItem);

	// InitListItem and RequestRefresh
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void RequestListRefresh();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void InitListItem();
	UFUNCTION(BlueprintPure, Category = "HorizonPlugin|UI|TileView", meta = (DisplayName = "GetEntryWidgetFromItem"))
	virtual UHorizonListViewItemWidget* BP_GetEntryWidgetFromItem(UObject* InItem);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void RemoveItemAndKeepSelectedIndex(UObject* InItem);
#if WITH_EDITOR
public:
	//~ Begin UObject Interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	//~ End UObject Interface
protected:
	virtual void OnRefreshDesignerItems() override;
private:
	void CalculateItemSize();
#endif


public:
	UPROPERTY(BlueprintAssignable)
	FOnInitListItemEvent OnInitListItemEvent;
	FOnInitListItemEventNative OnInitListItemEventNative;

	UPROPERTY(BlueprintAssignable)
	FOnItemEvent OnItemPressedEvent;
	FOnItemEventNative OnItemPressedEventNative;

	UPROPERTY(BlueprintAssignable)
	FOnItemEvent OnItemReleasedEvent;
	FOnItemEventNative OnItemReleasedEventNative;

	UPROPERTY(BlueprintAssignable)
	FOnItemEvent OnItemHoveredEvent;
	FOnItemEventNative OnItemHoveredEventNative;


	UPROPERTY(BlueprintAssignable)
	FOnItemEvent OnItemUnhoveredEvent;
	FOnItemEventNative OnItemUnhoveredEventNative;

	UPROPERTY(BlueprintAssignable)
	FOnItemEvent OnItemClickedEvent;
	FOnItemEventNative OnItemClickedEventNative;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HorizonPlugin|UI|TileView")
	EHorizonTileViewRefreshBehavior RefreshBehavior = EHorizonTileViewRefreshBehavior::ScrollToBottom;
private:
	TWeakObjectPtr<UObject> PreviousSelectedItem;
	int32 RequestedItemSelectionIndex = -1;
};
