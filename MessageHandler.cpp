#include "MessageHandler.h"

bool MessageImpl::IsValid( Connection* connection )
{
    //Validate message before to process it
    for( const auto& validation : validations )
        if( !validation( connection ) )
            return false;

    return true;
}

bool MessageImpl::CanProcess( Connection* connection, MemoryBuffer& message )
{
    //Process message
    for( const auto& process : processing )
        if( !process( connection, message ) )
            return false;

    return true;
}

namespace Handler
{
Message::Message()
{
}

Message::~Message()
{
}

MessageImpl& Message::Handle( int messageID )
{
    //Message already exists, so we have to return the existing handler
    if( handlers.find( messageID ) != handlers.end() )
        return *handlers[messageID];

    //Create a new message handler
    MessageImpl* newHandler( new MessageImpl() );
    handlers[messageID] = newHandler;

    //Return message handler pointer
    return *newHandler;
}

bool Message::HandleMessage( int messageID, MemoryBuffer* buffer )
{
    Connection* sender = nullptr;

    //Check if message has any handler
    if( auto it = handlers.find( messageID ); it != handlers.end() )
    {
        auto message = it->second;

        //Validate Message with Global Validations before
        for( const auto& handler : validations )
            if( !handler( sender ) )
                return false;

        //Validate Message Authorization
        if( !message->IsValid( sender ) )
            return false;

        //Process Message with Global Processing Handlers before
        for( const auto& handler : processing )
            if( !handler( sender, *buffer ) )
                return false;

        //Process Message
        if( !message->CanProcess( sender, *buffer ) )
            return false;

        return true;
    }

    return false;
}
}