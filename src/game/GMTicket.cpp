#include "StdAfx.h"

void WorldSession::HandleGMTicketCreateOpcode(WorldPacket & recv_data)
{
    uint32 type;
    uint8 unk1;
    float x, y, z;
    std::string message = "";
    std::string message2 = "";
    GM_Ticket *ticket = new GM_Ticket;
    WorldPacket data;

    // recv Data
    recv_data >> type;
    recv_data >> unk1;
    recv_data >> x;
    recv_data >> y;
    recv_data >> z;
    recv_data >> message;
    recv_data >> message2;

    // Create new Ticket and store it
    objmgr.remGMTicket(GetPlayer()->GetGUID());

    ticket->guid = GetPlayer()->GetGUID();
    ticket->type = type;
    ticket->posX = x;
    ticket->posY = y;
    ticket->posZ = z;
    ticket->message = message;
    ticket->timestamp = (uint32)time(NULL);
    ticket->name = GetPlayer()->GetName();
    ticket->level = GetPlayer()->getLevel();

    objmgr.remGMTicket(GetPlayer()->GetGUID());
    objmgr.AddGMTicket(ticket);

    // Response - no errors
    data.Initialize(SMSG_GMTICKET_CREATE);
    data << uint32(2);

    SendPacket(&data);

    // send message indicating new ticket
    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(),GetPlayer());
    if(chn)
    {
        char msg[100];
        snprintf(msg, 100, "GmTicket 5,%s", GetPlayer()->GetName());
        chn->Say(_player, msg, 0);
    }
}

void WorldSession::HandleGMTicketUpdateOpcode(WorldPacket & recv_data)
{
    uint8 unk1;
    std::string message = "";
    WorldPacket data;

    // recv Data
    recv_data >> unk1;
    recv_data >> message;

    // Update Ticket
    GM_Ticket *ticket = objmgr.GetGMTicket(GetPlayer()->GetGUID());
    if(!ticket) // Player doesnt have a GM Ticket yet
    {
        // Response - error couldnt find existing Ticket
        data.Initialize(SMSG_GMTICKET_UPDATETEXT);
        data << uint32(1);

        SendPacket(&data);
        return;
    }
    ticket->message = message;
    ticket->timestamp = (uint32)time(NULL);

    objmgr.remGMTicket(GetPlayer()->GetGUID());
    objmgr.AddGMTicket(ticket);

    // Response - no errors
    data.Initialize(SMSG_GMTICKET_UPDATETEXT);
    data << uint32(2);

    SendPacket(&data);
}

void WorldSession::HandleGMTicketDeleteOpcode(WorldPacket & recv_data)
{
    WorldPacket data;
    // no data

    // remove Ticket
    objmgr.remGMTicket(GetPlayer()->GetGUID());

    // Response - no errors
    data.Initialize(SMSG_GMTICKET_DELETETICKET);
    data << uint32(9);

    SendPacket(&data);
}

void WorldSession::HandleGMTicketGetTicketOpcode(WorldPacket & recv_data)
{
    WorldPacket data;
    // no data

    // get Current Ticket
    GM_Ticket *ticket = objmgr.GetGMTicket(GetPlayer()->GetGUID());

    if(!ticket) // no Current Ticket
    {
        data.Initialize(SMSG_GMTICKET_GETTICKET);
        data << uint32(10);
        SendPacket(&data);
        return;
    }

    // Send current Ticket
    data.Initialize(SMSG_GMTICKET_GETTICKET);
    data << uint32(6); // unk
    data << ticket->message.c_str();
    data << (uint8)ticket->type;

    SendPacket(&data);
}


void WorldSession::HandleGMTicketSystemStatusOpcode(WorldPacket & recv_data)
{
    WorldPacket data;

    // no data

    // Response - System is working Fine
    data.Initialize(SMSG_GMTICKET_SYSTEMSTATUS);
    if(sWorld.getGMTicketStatus())
        data << uint32(1);
    else
        data << uint32(0);

    SendPacket(&data);
}

void WorldSession::HandleGMTicketToggleSystemStatusOpcode(WorldPacket & recv_data)
{
    sWorld.toggleGMTicketStatus();
}
