#include "BP_HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBP_HUDWidget::UpdateHealthBar(float HealthPercentage)
{
	if (HealthBar)
	{
		// Set the progress bar's fill percentage
		HealthBar->SetPercent(HealthPercentage);
	}
}

void UBP_HUDWidget::UpdateAmmoText(int32 CurrentAmmo)
{
	if (AmmoNumberText)
	{
		AmmoNumberText->SetText(FText::AsNumber(CurrentAmmo));
	}
}
