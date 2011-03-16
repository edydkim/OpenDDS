// -*- C++ -*-
//
// $Id$
#include "DCPS/DdsDcps_pch.h" //Only the _pch include should start with DCPS/
#include "TransportSendControlElement.h"
#include "TransportSendListener.h"
#include "dds/DCPS/transport/framework/EntryExit.h"

#if !defined (__ACE_INLINE__)
#include "TransportSendControlElement.inl"
#endif /* __ACE_INLINE__ */


OpenDDS::DCPS::TransportSendControlElement::~TransportSendControlElement()
{
  DBG_ENTRY_LVL("TransportSendControlElement","~TransportSendControlElement",5);
}


bool
OpenDDS::DCPS::TransportSendControlElement::requires_exclusive_packet() const
{
  DBG_ENTRY_LVL("TransportSendControlElement","requires_exclusive_packet",5);
  return true;
}


void
OpenDDS::DCPS::TransportSendControlElement::release_element(bool dropped_by_transport)
{
  ACE_UNUSED_ARG (dropped_by_transport);

  DBG_ENTRY_LVL("TransportSendControlElement","release_element",5);

  if (this->was_dropped())
    {
      this->listener_->control_dropped(this->msg_, dropped_by_transport);
    }
  else
    {
      this->listener_->control_delivered(this->msg_);
    }

  if (allocator_)
    {
      allocator_->free (this);
    }
}


OpenDDS::DCPS::RepoId
OpenDDS::DCPS::TransportSendControlElement::publication_id() const
{
  DBG_ENTRY_LVL("TransportSendControlElement","publication_id",5);
  return this->publisher_id_;
}


const ACE_Message_Block*
OpenDDS::DCPS::TransportSendControlElement::msg() const
{
  DBG_ENTRY_LVL("TransportSendControlElement","msg",5);
  return this->msg_;
}


bool
OpenDDS::DCPS::TransportSendControlElement::is_control(RepoId pub_id) const
{
  return (pub_id == this->publisher_id_);
}
