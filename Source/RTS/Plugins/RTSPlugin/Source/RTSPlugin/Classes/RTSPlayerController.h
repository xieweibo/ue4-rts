#pragma once

#include "RTSPluginPrivatePCH.h"

#include "GameFramework/PlayerController.h"

#include "RTSPlayerController.generated.h"

class ARTSCameraBoundsVolume;


/**
 * Player controller with RTS features, such as selection and mouse camera movement.
 */
UCLASS()
class ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    /** Movement speed of the camera when moved with keys or mouse, in cm/sec. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS|Camera", meta = (ClampMin = 0))
    float CameraSpeed;

    /** Distance from the screen border at which the mouse cursor causes the camera to move, in pixels. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS|Camera", meta = (ClampMin = 0))
    int CameraScrollThreshold;


	virtual void PlayerTick(float DeltaTime) override;


	/** Gets the actor currently hovered by this player. */
	UFUNCTION(BlueprintCallable)
	AActor* GetHoveredActor();

	/** Gets the list of units currently selected by this player. */
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetSelectedActors();

	/** Casts a ray from the specified screen position and collects the results. */
	bool GetObjectsAtScreenPosition(FVector2D ScreenPosition, TArray<FHitResult>& HitResults);

	/** Casts a ray to find any objects at the specified world position. */
	bool GetObjectsAtWorldPosition(const FVector& WorldPositionXY, TArray<FHitResult>& HitResults);

	/** Gets the current selection frame, in screen space. */
	bool GetSelectionFrame(FIntRect& OutSelectionFrame);


	/** Orders all selected units to attack the specified unit. */
	UFUNCTION(BlueprintCallable)
	void IssueAttackOrder(AActor* Target);

	/** Orders all selected units to move to the specified location. */
	UFUNCTION(BlueprintCallable)
	void IssueMoveOrder(const FVector& TargetLocation);

	/** Orders all selected units to stop all current actions. */
	UFUNCTION(BlueprintCallable)
	void IssueStopOrder();

	/** Selects the specified actors. */
	UFUNCTION(BlueprintCallable)
	void SelectActors(TArray<AActor*> Actors);

	/** Saves the current selection to the specified control group. */
	UFUNCTION(BlueprintCallable)
	void SaveControlGroup(int Index);

	UFUNCTION(BlueprintCallable) void SaveControlGroup0();
	UFUNCTION(BlueprintCallable) void SaveControlGroup1();
	UFUNCTION(BlueprintCallable) void SaveControlGroup2();
	UFUNCTION(BlueprintCallable) void SaveControlGroup3();
	UFUNCTION(BlueprintCallable) void SaveControlGroup4();
	UFUNCTION(BlueprintCallable) void SaveControlGroup5();
	UFUNCTION(BlueprintCallable) void SaveControlGroup6();
	UFUNCTION(BlueprintCallable) void SaveControlGroup7();
	UFUNCTION(BlueprintCallable) void SaveControlGroup8();
	UFUNCTION(BlueprintCallable) void SaveControlGroup9();

	/** Restores the selection saved in the specified control group. */
	UFUNCTION(BlueprintCallable)
	void LoadControlGroup(int Index);

	UFUNCTION(BlueprintCallable) void LoadControlGroup0();
	UFUNCTION(BlueprintCallable) void LoadControlGroup1();
	UFUNCTION(BlueprintCallable) void LoadControlGroup2();
	UFUNCTION(BlueprintCallable) void LoadControlGroup3();
	UFUNCTION(BlueprintCallable) void LoadControlGroup4();
	UFUNCTION(BlueprintCallable) void LoadControlGroup5();
	UFUNCTION(BlueprintCallable) void LoadControlGroup6();
	UFUNCTION(BlueprintCallable) void LoadControlGroup7();
	UFUNCTION(BlueprintCallable) void LoadControlGroup8();
	UFUNCTION(BlueprintCallable) void LoadControlGroup9();

	/** Whether the hotkey for showing all health bars is currently pressed, or not. */
	UFUNCTION(BlueprintCallable)
	bool IsHealthBarHotkeyPressed();


	/** Event when this player is now owning the specified actor. */
	virtual void NotifyOnActorOwnerChanged(AActor* Actor);

	/** Event when an actor has received an attack order. */
	virtual void NotifyOnIssuedAttackOrder(AActor* Actor, AActor* Target);

    /** Event when an actor has received a move order. */
    virtual void NotifyOnIssuedMoveOrder(AActor* Actor, const FVector& TargetLocation);

	/** Event when an actor has received a stop order. */
	virtual void NotifyOnIssuedStopOrder(AActor* Actor);

	/** Event when the player has clicked a spot on the minimap. */
	virtual void NotifyOnMinimapClicked(const FPointerEvent& InMouseEvent, const FVector2D& MinimapPosition, const FVector& WorldPosition);

    /** Event when the set of selected actors of this player has changed. */
    virtual void NotifyOnSelectionChanged(const TArray<AActor*>& Selection);

	/** Event when this player is now owning the specified actor. */
	UFUNCTION(BlueprintImplementableEvent, Category = "RTS|Ownership", meta = (DisplayName = "OnActorOwnerChanged"))
	void ReceiveOnActorOwnerChanged(AActor* Actor);

	/** Event when an actor has received an attack order. */
	UFUNCTION(BlueprintImplementableEvent, Category = "RTS|Orders", meta = (DisplayName = "OnIssuedAttackOrder"))
	void ReceiveOnIssuedAttackOrder(AActor* Actor, AActor* Target);

    /** Event when an actor has received a move order. */
    UFUNCTION(BlueprintImplementableEvent, Category = "RTS|Orders", meta = (DisplayName = "OnIssuedMoveOrder"))
    void ReceiveOnIssuedMoveOrder(AActor* Actor, const FVector& TargetLocation);

	/** Event when an actor has received a stop order. */
	UFUNCTION(BlueprintImplementableEvent, Category = "RTS|Orders", meta = (DisplayName = "OnIssuedStopOrder"))
	void ReceiveOnIssuedStopOrder(AActor* Actor);

	/** Event when the player has clicked a spot on the minimap. */
	UFUNCTION(BlueprintImplementableEvent, Category = "RTS|Minimap", meta = (DisplayName = "NotifyOnMinimapClicked"))
	void ReceiveOnMinimapClicked(const FPointerEvent& InMouseEvent, const FVector2D& MinimapPosition, const FVector& WorldPosition);

    /** Event when the set of selected actors of this player has changed. */
    UFUNCTION(BlueprintImplementableEvent, Category = "RTS|Selection", meta = (DisplayName = "OnSelectionChanged"))
    void ReceiveOnSelectionChanged(const TArray<AActor*>& Selection);


	/** Sets this player as the owner of the specified actor. */
	UFUNCTION(BlueprintCallable)
	void TransferOwnership(AActor* Actor);

protected:
    virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
    /** Volume that restricts the camera movement of this player. */
    ARTSCameraBoundsVolume* CameraBoundsVolume;

    /** Last horizontal axis input applied to camera movement. */
    float CameraLeftRightAxisValue;

    /** Last vertical axis input applied to camera movement. */
    float CameraUpDownAxisValue;


	/** Saved selections of this player. */
	TArray<TArray<AActor*>> ControlGroups;

	/** Actor currently hovered by this player. */
	AActor* HoveredActor;

    /** Actors selected by this player. */
    TArray<AActor*> SelectedActors;


	/** Whether we're currently creating a selection frame by dragging the mouse. */
	bool bCreatingSelectionFrame;

	/** Mouse position on screen when creating the selection frame started. */
	FVector2D SelectionFrameMouseStartPosition;

	/** Whether the hotkey for showing all health bars is currently pressed, or not. */
	bool bHealthBarHotkeyPressed;

    /** Casts a ray from the current mouse position and collects the results. */
    bool GetObjectsAtPointerPosition(TArray<FHitResult>& HitResults);
	
	/** Casts a box from the current selection frame and collects the results. */
	bool GetObjectsInSelectionFrame(TArray<FHitResult>& HitResults);

	/** Traces all relevant objects using the specified ray. */
	bool TraceObjects(const FVector& WorldOrigin, const FVector& WorldDirection, TArray<FHitResult>& HitResults);

	/** Checks whether the specified actor is valid and selectable. */
	bool IsSelectableActor(AActor* Actor);

    /** Automatically issues the most reasonable order for the current pointer position. */
    UFUNCTION()
    void IssueOrder();

	/** Automatically issues the most reasonable order for the specified targets. */
	void IssueOrderTargetingObjects(TArray<FHitResult>& HitResults);

	/** Orders the passed unit to attack the specified unit. */
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerIssueAttackOrder(APawn* OrderedPawn, AActor* Target);

	/** Orders the passed unit to move to the specified location. */
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerIssueMoveOrder(APawn* OrderedPawn, const FVector& TargetLocation);

	/** Orders the passed unit to stop all current actions. */
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerIssueStopOrder(APawn* OrderedPawn);

    /** Applies horizontal axis input to camera movement. */
    void MoveCameraLeftRight(float Value);

    /** Applies vertical axis input to camera movement. */
    void MoveCameraUpDown(float Value);

    /** Remembers the current mouse position for multi-selection, finished by FinishSelectActors. */
    UFUNCTION()
    void StartSelectActors();

	/** Selects all selectable actors within the created selection frame, started by StartSelectActors. */
	UFUNCTION()
	void FinishSelectActors();

	/** Force showing all health bars. */
	UFUNCTION()
	void StartShowingHealthBars();

	/** Stop showing all health bars. */
	UFUNCTION()
	void StopShowingHealthBars();
};
