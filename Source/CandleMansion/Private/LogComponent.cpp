// Fill out your copyright notice in the Description page of Project Settings.


#include "LogComponent.h"

// Sets default values for this component's properties
ULogComponent::ULogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULogComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//get unix time, should be unique everytime shit is created.
	FDateTime DT = FDateTime::Now();
	UniqueName = FString::FromInt(DT.ToUnixTimestamp());
	
	//should get game directory + file name. no idea how this trash will work with network drives in the game lab.
	FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + TEXT("/GameplayLogs/" + UniqueName + ".txt"); 

	CreateNewLogFile();
}


// Called every frame
void ULogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// now that think about it, this func is completely useless since file will be created anyway lol.
void ULogComponent::CreateNewLogFile(){
	FFileHelper::SaveStringToFile("\n[" + GetCurrentTime() + "] " + "Game log for ID: " + UniqueName, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void ULogComponent::LogGameTimeInSeconds(){
	int GameTimeSeconds = GetWorld()->GetTimeSeconds();
	FString LevelName = GetWorld()->GetMapName();
	FString StringToLog = "\n[" + GetCurrentTime() + "] " + LevelName + " has been completed in: " + FString::FromInt(GameTimeSeconds) + " seconds.";
	FFileHelper::SaveStringToFile(StringToLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void ULogComponent::LogStartCollision(FString objectname){
	FString StringToLog = "\n[" + GetCurrentTime() + "] " + "Player has collided with " + objectname;
	FFileHelper::SaveStringToFile(StringToLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void ULogComponent::LogStopCollision(FString objectname){
	FString StringToLog = "\n[" + GetCurrentTime() + "] " + "Player has stopped colliding with " + objectname;
	FFileHelper::SaveStringToFile(StringToLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void ULogComponent::LogCandleSuccess(){
	FString StringToLog = "\n[" + GetCurrentTime() + "] " + "Player has found a candle and extinguished it";
	FFileHelper::SaveStringToFile(StringToLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void ULogComponent::LogCandleTry(){
	FString StringToLog = "\n[" + GetCurrentTime() + "] " + "Player tried to extinguish a candle";
	FFileHelper::SaveStringToFile(StringToLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void ULogComponent::LogCandleTries(int candletries){
	FString StringToLog = "\n[" + GetCurrentTime() + "] " + "Total candle extinguish tries: " + FString::FromInt(candletries);
	FFileHelper::SaveStringToFile(StringToLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void ULogComponent::LogObjectDetectedBoxTrace(FString objtype){
	FString StringToLog = "\n[" + GetCurrentTime() + "] " + "Player detected an object with the box trace: " + objtype;
	FFileHelper::SaveStringToFile(StringToLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void ULogComponent::LogObjectDetectionTry(){
	FString StringToLog = "\n[" + GetCurrentTime() + "] " + "Player tried to detect an object";
	FFileHelper::SaveStringToFile(StringToLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void ULogComponent::LogObjectDetectionTries(int detecttries){
	FString StringToLog = "\n[" + GetCurrentTime() + "] " + "Total object detection tries: " + FString::FromInt(detecttries);
	FFileHelper::SaveStringToFile(StringToLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void ULogComponent::LogObjectDetectionLineTrace(FString objectname){
	FString StringToLog = "\n[" + GetCurrentTime() + "] " + "Player detected " + objectname + " with line trace";
	FFileHelper::SaveStringToFile(StringToLog, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

FString ULogComponent::GetCurrentTime(){
	FDateTime RealTime = FDateTime::Now();
	int Hour = RealTime.GetHour();
	int Minute = RealTime.GetMinute();
	int Second = RealTime.GetSecond();
	int Millisecond = RealTime.GetMillisecond();
	FString Time = FString::FromInt(Hour) + ":" + FString::FromInt(Minute) + ":" + FString::FromInt(Second) + "." + FString::FromInt(Millisecond);
	
	return Time;
}