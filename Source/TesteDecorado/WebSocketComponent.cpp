// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocketComponent.h"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
//using websocketpp::lib::bind;


// Sets default values for this component's properties
UWebSocketComponent::UWebSocketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWebSocketComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UWebSocketComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWebSocketComponent::DefaultConnect() {
	this->CustomConnect(this->ServerIP, this->ServerPort);
}

// Allows to connect to a custom server
void UWebSocketComponent::CustomConnect(FString IpAddress, int32 Port) {
	FString address = "ws://" + IpAddress + ":" + FString::FromInt(Port);
	string uri = string(TCHAR_TO_UTF8(*address));

	try {
		this->c.init_asio();
		this->c.set_message_handler(websocketpp::lib::bind(&UWebSocketComponent::on_message, this, &this->c, ::_1, ::_2));

		websocketpp::lib::error_code ec;

		this->con = c.get_connection(uri, ec);
		if (ec) {
			cout << "Could not create connection because: " << ec.message() << endl;
		}
		this->c.connect(con);
	}
	catch (websocketpp::exception const &e) {
		cout << e.what() << endl;
	}
}

// Disconnect from current server
void UWebSocketComponent::Disconnect()
{
	try {
		this->c.pause_reading(con);
		this->c.close(con, 0, "");
	}
	catch (websocketpp::exception const &e) {
		cout << e.what() << endl;
	}
}

// Update data from Server
void UWebSocketComponent::Update() {
	try {
		this->c.run_one();
	}
	catch (websocketpp::exception const &e) {
		cout << e.what() << endl;
	}
}