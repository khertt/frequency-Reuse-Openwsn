/**
\brief A CoAP resource which allows an application to GET/SET the state of the
   error LED.
*/

#include "opendefs.h"
#include "cleds.h"
#include "opencoap.h"
#include "packetfunctions.h"
#include "leds.h"
#include "openqueue.h"

#include "schedule.h"

//=========================== variables =======================================

cleds_vars_t cleds_vars;

const uint8_t cleds_path0[]       = "l";

//=========================== prototypes ======================================

owerror_t cleds_receive(
   OpenQueueEntry_t* msg,
   coap_header_iht*  coap_header,
   coap_option_iht*  coap_options
);
void     cleds_sendDone(
   OpenQueueEntry_t* msg,
   owerror_t error
);

//=========================== public ==========================================

void cleds__init() {
   
   // prepare the resource descriptor for the /l path
   cleds_vars.desc.path0len            = sizeof(cleds_path0)-1;
   cleds_vars.desc.path0val            = (uint8_t*)(&cleds_path0);
   cleds_vars.desc.path1len            = 0;
   cleds_vars.desc.path1val            = NULL;
   cleds_vars.desc.componentID         = COMPONENT_CLEDS;
   cleds_vars.desc.discoverable        = TRUE;
   cleds_vars.desc.callbackRx          = &cleds_receive;
   cleds_vars.desc.callbackSendDone    = &cleds_sendDone;
   
   schedule_init();
   // calendarizacion 
   // register with the CoAP module
   opencoap_register(&cleds_vars.desc);
}

//=========================== private =========================================

/**
\brief Called when a CoAP message is received for this resource.

\param[in] msg          The received message. CoAP header and options already
   parsed.
\param[in] coap_header  The CoAP header contained in the message.
\param[in] coap_options The CoAP options contained in the message.

\return Whether the response is prepared successfully.
*/
owerror_t cleds_receive(
      OpenQueueEntry_t* msg,
      coap_header_iht*  coap_header,
      coap_option_iht*  coap_options4
   ) {
   owerror_t outcome;
   
   switch (coap_header->Code) {
      case COAP_CODE_REQ_GET:
         // reset packet payload
         msg->payload                     = &(msg->packet[127]);
         msg->length                      = 0;
         
         // add CoAP payload
         //packetfunctions_reserveHeaderSize(msg,12);
         //msg->payload[0]                  = COAP_PAYLOAD_MARKER;

         //if (leds_error_isOn()==1) {
         uint8_t aux=0;
         uint8_t y=0;
         uint8_t x=0;
         uint8_t i=4;
         uint8_t s=4;
   

         	
         
        while(TRUE){

		if (schedule_vars.scheduleBuf[i].type==1 || schedule_vars.scheduleBuf[i].type==2 ){
			i=i+1;

		}
	        else{
			break;		
		}
                if(i==10){
			break;}
	 }
         
         x=13*(i-4);
         x=x+1;
	 packetfunctions_reserveHeaderSize(msg,x);
         
         msg->payload[0]                  = COAP_PAYLOAD_MARKER;       

         while(TRUE){

	 
		msg->payload[y+1]               = schedule_vars.scheduleBuf[s].neighbor.addr_64b[0];
	 	msg->payload[y+2]               = schedule_vars.scheduleBuf[s].neighbor.addr_64b[1];
	 	msg->payload[y+3]               = schedule_vars.scheduleBuf[s].neighbor.addr_64b[2];
         	msg->payload[y+4]               = schedule_vars.scheduleBuf[s].neighbor.addr_64b[3];
	 	msg->payload[y+5]               = schedule_vars.scheduleBuf[s].neighbor.addr_64b[4];
	 	msg->payload[y+6]               = schedule_vars.scheduleBuf[s].neighbor.addr_64b[5];
	 	msg->payload[y+7]               = schedule_vars.scheduleBuf[s].neighbor.addr_64b[6];
	 	msg->payload[y+8]               = schedule_vars.scheduleBuf[s].neighbor.addr_64b[7];
	 	msg->payload[y+9]               = schedule_vars.scheduleBuf[s].neighbor.addr_64b[8];
	 	msg->payload[y+10]              = schedule_vars.scheduleBuf[s].type;
	 	msg->payload[y+11]		  = schedule_vars.scheduleBuf[s].channelOffset;
	 	msg->payload[y+12]		  = schedule_vars.scheduleBuf[s].slotOffset;
		msg->payload[y+13]		  ='T';


		s=s+1;
		y=y+13;
                if(s>i){
			break;
		}
	
                 
	 
	}


	/* msg->payload[1]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[0];
	 msg->payload[2]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[1];
	 msg->payload[3]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[2];
         msg->payload[4]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[3];
	 msg->payload[5]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[4];
	 msg->payload[6]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[5];
	 msg->payload[7]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[6];
	 msg->payload[8]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[7];
	 msg->payload[9]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[8];
	 msg->payload[10]              = schedule_vars.scheduleBuf[4].type;
	 msg->payload[11]		  = schedule_vars.scheduleBuf[4].channelOffset;
	 msg->payload[12]		  = schedule_vars.scheduleBuf[4].slotOffset
	
	 msg->payload[13]		  ='T';

         msg->payload[14]               = schedule_vars.scheduleBuf[5].neighbor.addr_64b[0];
	 msg->payload[15]               = schedule_vars.scheduleBuf[5].neighbor.addr_64b[1];
	 msg->payload[16]               = schedule_vars.scheduleBuf[5].neighbor.addr_64b[2];
         msg->payload[17]               = schedule_vars.scheduleBuf[5].neighbor.addr_64b[3];
	 msg->payload[18]               = schedule_vars.scheduleBuf[5].neighbor.addr_64b[4];
	 msg->payload[19]               = schedule_vars.scheduleBuf[5].neighbor.addr_64b[5];
	 msg->payload[20]               = schedule_vars.scheduleBuf[5].neighbor.addr_64b[6];
	 msg->payload[21]               = schedule_vars.scheduleBuf[5].neighbor.addr_64b[7];
	 msg->payload[22]               = schedule_vars.scheduleBuf[5].neighbor.addr_64b[8];
	 msg->payload[23]              = schedule_vars.scheduleBuf[5].type;
	 msg->payload[24]		  = schedule_vars.scheduleBuf[5].channelOffset;
         
	 msg->payload[25]		  ='T';
         */  		
        
	    //msg->payload[11]              = schedule_vars.debugPrintRow;
	    //msg->payload[12]              = schedule_vars.maxActiveSlots;
	    //msg->payload[13]              = neighbors_vars.neighbors[0].rssi;
	   
		

         //} else {

		

	    //msg->payload[1]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[0];
	    //msg->payload[2]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[1];
	    //msg->payload[3]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[2];
            //msg->payload[4]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[3];
	    //msg->payload[5]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[4];
	    //msg->payload[6]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[5];
	    //msg->payload[7]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[6];
	    //msg->payload[8]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[7];
	    //msg->payload[9]               = schedule_vars.scheduleBuf[4].neighbor.addr_64b[8];
	    //msg->payload[10]              = schedule_vars.scheduleBuf[4].type;
	    //msg->payload[11]              = schedule_vars.debugPrintRow;
	    //msg->payload[12]              = schedule_vars.maxActiveSlots;
	    //msg->payload[13]              = neighbors_vars.neighbors[0].rssi;
        






         //}
            
         // set the CoAP header
         coap_header->Code                = COAP_CODE_RESP_CONTENT;
         
         outcome                          = E_SUCCESS;
         break;
      
      case COAP_CODE_REQ_PUT:
      
         // change the LED's state
         if (msg->payload[0]=='1') {
            leds_error_on();
	    setCambio_Canal();
	    schedule_vars.scheduleBuf[4].channelOffset=schedule_vars.scheduleBuf[4].channelOffset+1;
         } else if (msg->payload[0]=='2') {
            leds_error_toggle();
         } else {
            leds_error_off();
         }
         
         // reset packet payload
         msg->payload                     = &(msg->packet[127]);
         msg->length                      = 0;
         
         // set the CoAP header
         coap_header->Code                = COAP_CODE_RESP_CHANGED;
         
         outcome                          = E_SUCCESS;
         break;
         
      default:
         outcome                          = E_FAIL;
         break;
   }
   
   return outcome;
}

/**
\brief The stack indicates that the packet was sent.

\param[in] msg The CoAP message just sent.
\param[in] error The outcome of sending it.
*/
void cleds_sendDone(OpenQueueEntry_t* msg, owerror_t error) {
   openqueue_freePacketBuffer(msg);
}
