// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include "WebSocketComponent.generated.h"

using namespace std;

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageDelegate, FString, Data);

//Component to receive data form a WebSocket
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTEDECORADO_API UWebSocketComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWebSocketComponent();

protected:
	client c;
	client::connection_ptr con;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WebSocket|Data")
	FString msgdata = "";

	//Server IP address
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WebSocket|Configuration")
	FString ServerIP = "localhost";

	//Server Port
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WebSocket|Configuration")
	int32 ServerPort = 9002;

	//OnMessage Event
	UPROPERTY(BlueprintAssignable, Category = "WebSocket|Event")
	FOnMessageDelegate OnMessage;

	//Actual on_message callback
	FORCEINLINE void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
		this->OnMessage.Broadcast(FString(msg->get_payload().c_str()));
	};

	//Connect to server configured in the properties
	UFUNCTION(BlueprintCallable, Category = "WebSocket|Connection")
	void DefaultConnect();

	//Connect to a custom server
	UFUNCTION(BlueprintCallable, Category = "WebSocket|Connection")
	void CustomConnect(FString IpAddress, int32 Port);

	//Disconnect from current server
	UFUNCTION(BlueprintCallable, Category = "WebSocket|Connection")
	void Disconnect();

	//Update data from server
	UFUNCTION(BlueprintCallable, Category = "WebSocket|Connection")
	void Update();

};
