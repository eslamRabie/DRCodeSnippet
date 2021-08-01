// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/ShopMenuWidget.h"

#include "DRGameState.h"
#include "DRInGamePlayerState.h"

#include "InGameUI/ShopItemListWidget.h"

bool UShopMenuWidget::Initialize()
{
	Super::Initialize();

	if (!BuyItemButton || !ItemImage || !ItemPriceText || !ItemDescriptionText || !ShopTileView || !ExitButton)
	{
		UE_LOG(LogTemp, Error, TEXT("Some Widgets Was Not Assigned In BP in: UShopMenuWidget::Initialize"));
		return false;
	}
	if (!ShopItemListWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ShopItemListWidgetClass Was Not Assigned In BP in: UShopMenuWidget::Initialize"));
		return false;
	}

	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("Cant GetWorld in:ADRGameState::BeginPlay"))
		return false;
	}

	Shop = NewObject<UShop>(GetWorld(), GameShopClass);

	if (!Shop)
	{
		UE_LOG(LogTemp, Error, TEXT("Cat Get Shop in: UShopMenuWidget::Initialize "))
		return false;
	}

	for (auto ShopItem : Shop->GetShopItemsList())
	{
		CreateShopItemListWidget(ShopItem);
	}

	BuyItemButton->OnClicked.AddDynamic(this, &UShopMenuWidget::OnBuyItemButtonClicked);
	ExitButton->OnClicked.AddDynamic(this, &UShopMenuWidget::OnExit);

	return true;
}

void UShopMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UShopMenuWidget::CreateShopItemListWidget(FShopItem* ShopItem)
{
	if (!ShopItemListWidgetClass)
	{
		UE_LOG(LogTemp, Error,
		       TEXT("ShopItemListWidgetClass was not assinged in BP in: UShopMenuWidget::CreateShopItemListWidget"));
		return;
	}

	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get World in >> UShopMenuWidget::CreateShopItemListWidget"));
		return;
	}

	auto ItemWidget = CreateWidget<UShopItemListWidget>(GetWorld(), ShopItemListWidgetClass);

	if (!ItemWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Create ItemWidget >> UShopMenuWidget::CreateShopItemListWidget"));
		return;
	}
	ItemWidget->Init(this, ShopItem);
	ShopTileView->AddChild(ItemWidget);
}

void UShopMenuWidget::OnBuyItemButtonClicked()
{
	if (!CurrentShopItem || !CurrentShopItem->ShopItem)
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentShopItem Is Null in: UShopMenuWidget::OnBuyItemButtonClicked"));
		return;
	}

	auto PlayerState = GetOwningPlayerState<ADRInGamePlayerState>();

	if (!GetOwningPlayerState<ADRInGamePlayerState>())
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerState is Null in: UShopMenuWidget::OnBuyItemButtonClicked"));
		return;
	}


	auto Inventory = PlayerState->GetInventory();

	if (!Inventory)
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory is Null in: UShopMenuWidget::OnBuyItemButtonClicked"));
		return;
	}

	auto PowerUpClass = CurrentShopItem->ShopItem->PowerUpClass;

	if (!PowerUpClass)
	{
		UE_LOG(LogTemp, Error, TEXT("PowerUpClass is Null in: UShopMenuWidget::OnBuyItemButtonClicked"));
		return;
	}


	if (Shop->BuyItem(PowerUpClass, Inventory))
	{
		PlayerState->UpdateInventoryView();
		PlayerState->OnUpdateCoins(-1);
	}
}

void UShopMenuWidget::OnExit()
{
	auto Parent = GetParent();
	if (Parent)
		Parent->SetVisibility(ESlateVisibility::Collapsed);
	else
		RemoveFromViewport();
}
