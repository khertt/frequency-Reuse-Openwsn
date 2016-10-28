import os
import sys
here = sys.path[0]
print here
sys.path.insert(0,os.path.join(here,'..','..','..','..','..','..','coap'))

from coap import coap

MOTE_IP = 'bbbb::1415:92cc:0:3'

c = coap.coap()

# read status of debug LED
p = c.GET('coap://[{0}]/l'.format(MOTE_IP))

print p
print p[0]
 
print ''.join([chr(b) for b in p])


print ''.join(['%02x'%b for b in p])

#p = c.PUT('coap://[{0}]/l'.format(MOTE_IP),payload = [ord('1')],)


c.close()
