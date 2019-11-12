# MessageHandler
Handle your packets/messages from networking easilly.

## Dependencies
* C++ 17
* Unordered Map C++ STD Library
* Vector C++ STD Library
* Functional C++ STD Library

## Usage

### Including library ###
For use this you just need to include "MessageHandler.h" file into your project.

### Implementing ###
How each network interface is implemented on different ways, you will need to modify the code places where uses the **Connection** (pointer for the sender of message) & **MemoryBuffer** (pointer for the message buffer) classes.

Also, you will need to customize your packet handler (where messages from socket are received). This is made on **Message::HandleMessage** function, and you are free to let this how you want.

### Example ###
```c++
//Instantiating Message Handler
Handler::Message messageHandler;

//Adding Global Validations (will validate every message handled from this instance)
messageHandler.AddValidation( std::bind( &GlobalValidation1, std::placeholders::_1 ) );
messageHandler.AddValidation( std::bind( &GlobalValidation2, std::placeholders::_1 ) );

//Adding Global Handling (will handle every message handled from this instance)
messageHandler.AddProcessing( std::bind( &GlobalProcessing1, std::placeholders::_1, std::placeholders::_2 ) );

//Handler for specific messages
messageHandler.Handle( 1 ).Validate( std::bind( &Message1Validation1, std::placeholders::_1 ), std::bind( &Message1Validation2, std::placeholders::_1 ) );
messageHandler.Handle( 2 ).Validate( std::bind( &Message2Validation1, std::placeholders::_1 ) );
messageHandler.Handle( 3 ).Process( std::bind( &Message3Process1, std::placeholders::_1 ) );
messageHandler.Handle( 4 );

//Testing
messageHandler.HandleMessage( 1, nullptr );
messageHandler.HandleMessage( 2, nullptr );
messageHandler.HandleMessage( 3, nullptr );
messageHandler.HandleMessage( 4, nullptr );
```

## Observations
Is important that you adapt the library code for your networking structure. Code files used here is just an example, and a guide for you know what to do.

## Credits
* Library idea very inspired by [TransportLayer](https://github.com/leomachado73/TransportLayer)
